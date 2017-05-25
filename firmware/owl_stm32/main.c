/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/


// I2C peripherals addresses :
//
// Accelerometer / magnetometer LSM303D : 0x3A
// Moisture senser SI7006               : 0x40
// Absolute pressure sensor MPL3115A2   : 0x60
// Dual digital potentiometer AD5242    : 0x58

// RPI ressources :
//
// GPIO17 : STM32/NAD UART selection input (Lo/Hz=STM32 / Hi=NAD)
// GPIO14 : STM32/NAD UART data receiver input
// GPIO15 : STM32/NAD UART data transmitter output
// GPIO24 : STM32 SWDIO data biriectionnal
// GPIO23 : STM32 SWCLK clock input
// GPIO22 : STM32 nRESET input
// GPIO27 : STM32 bootmode input (Hi/Hz=from Flash / Lo=bootloader)

// Toggle Hi GPIO17 in bash to access NAD directly on /dev/ttyAMA0
//
// sudo bash
// echo "17" > /sys/class/gpio/export
// echo "out" > /sys/class/gpio/gpio17/direction
// echo "1" > /sys/class/gpio/gpio17/value

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "ch.h"
#include "hal.h"
#include "test.h"

#include "shell.h"
#include "chprintf.h"

/* ADC matter */
#define ADC_GRP1_NUM_CHANNELS   4
#define ADC_GRP1_BUF_DEPTH      8

#define ADC_GRP2_NUM_CHANNELS   16
#define ADC_GRP2_BUF_DEPTH      16

static adcsample_t samples1[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];
static adcsample_t samples2[ADC_GRP2_NUM_CHANNELS * ADC_GRP2_BUF_DEPTH];

/*
 * ADC streaming callback.
 */
size_t nx = 0, ny = 0;
static void adccallback(ADCDriver *adcp, adcsample_t *buffer, size_t n) {

  (void)adcp;
  if (samples2 == buffer) {
    nx += n;
  }
  else {
    ny += n;
  }
}

static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {

  (void)adcp;
  (void)err;
}

/*
 * ADC conversion group.
 * Mode:        Linear buffer, 8 samples of 2 channels, SW triggered.
 * Channels:    IN7, IN8.
 */
static const ADCConversionGroup adcgrpcfg1 = {
  FALSE,
  ADC_GRP1_NUM_CHANNELS,
  NULL,
  adcerrorcallback,
  ADC_CFGR_CONT,                                                /* CFGR     */
  ADC_TR(0, 4095),                                              /* TR1      */
  ADC_CCR_DUAL(1),                                              /* CCR      */
  {                                                             /* SMPR[2]  */
    0,
    0
  },
  {                                                             /* SQR[4]   */
    ADC_SQR1_SQ1_N(ADC_CHANNEL_IN7) | ADC_SQR1_SQ2_N(ADC_CHANNEL_IN8),
    0,
    0,
    0
  },
  {                                                             /* SSMPR[2] */
    0,
    0
  },
  {                                                             /* SSQR[4]  */
    ADC_SQR1_SQ1_N(ADC_CHANNEL_IN8) | ADC_SQR1_SQ2_N(ADC_CHANNEL_IN7),
    0,
    0,
    0
  }
};

/*
 * ADC conversion group.
 * Mode:        Continuous, 16 samples of 8 channels, SW triggered.
 * Channels:    IN7, IN8, IN7, IN8, IN7, IN8, Sensor, VBat/2.
 */
static const ADCConversionGroup adcgrpcfg2 = {
  TRUE,
  ADC_GRP2_NUM_CHANNELS,
  adccallback,
  adcerrorcallback,
  ADC_CFGR_CONT,                                                /* CFGR     */
  ADC_TR(0, 4095),                                              /* TR1      */
  ADC_CCR_DUAL(1) | ADC_CCR_TSEN | ADC_CCR_VBATEN,              /* CCR      */
  {                                                             /* SMPR[2]  */
    ADC_SMPR1_SMP_AN7(ADC_SMPR_SMP_19P5)
    | ADC_SMPR1_SMP_AN8(ADC_SMPR_SMP_19P5),
    ADC_SMPR2_SMP_AN16(ADC_SMPR_SMP_61P5)
    | ADC_SMPR2_SMP_AN17(ADC_SMPR_SMP_61P5),
  },
  {                                                             /* SQR[4]   */
    ADC_SQR1_SQ1_N(ADC_CHANNEL_IN7)  | ADC_SQR1_SQ2_N(ADC_CHANNEL_IN8) |
    ADC_SQR1_SQ3_N(ADC_CHANNEL_IN7)  | ADC_SQR1_SQ4_N(ADC_CHANNEL_IN8),
    ADC_SQR2_SQ5_N(ADC_CHANNEL_IN7)  | ADC_SQR2_SQ6_N(ADC_CHANNEL_IN8) |
    ADC_SQR2_SQ7_N(ADC_CHANNEL_IN16) | ADC_SQR2_SQ8_N(ADC_CHANNEL_IN17),
    0,
    0
  },
  {                                                             /* SSMPR[2] */
    ADC_SMPR1_SMP_AN1(ADC_SMPR_SMP_19P5)
    | ADC_SMPR1_SMP_AN2(ADC_SMPR_SMP_19P5),
    ADC_SMPR2_SMP_AN16(ADC_SMPR_SMP_61P5)
    | ADC_SMPR2_SMP_AN17(ADC_SMPR_SMP_61P5),
  },
  {                                                             /* SSQR[4]  */
    ADC_SQR1_SQ1_N(ADC_CHANNEL_IN2)  | ADC_SQR1_SQ2_N(ADC_CHANNEL_IN1) |
    ADC_SQR1_SQ3_N(ADC_CHANNEL_IN2)  | ADC_SQR1_SQ4_N(ADC_CHANNEL_IN1),
    ADC_SQR2_SQ5_N(ADC_CHANNEL_IN2)  | ADC_SQR2_SQ6_N(ADC_CHANNEL_IN1) |
    ADC_SQR2_SQ7_N(ADC_CHANNEL_IN17) | ADC_SQR2_SQ8_N(ADC_CHANNEL_IN16),
    0,
    0
  }
};


/* I2C1 */
static const I2CConfig i2cfg1 = {
  STM32_TIMINGR_PRESC(15U) |
  STM32_TIMINGR_SCLDEL(4U) | STM32_TIMINGR_SDADEL(2U) |
  STM32_TIMINGR_SCLH(15U)  | STM32_TIMINGR_SCLL(21U),
  0,
  0
};

/*
 * PWM configuration structure.
 * Cyclic callback enabled, channels 1 and 4 enabled without callbacks,
 * the active state is a logic one.
 */
static const PWMConfig pwmcfg = {
	100000,		/* 100kHz PWM clock frequency.  */
	256,		/* PWM period is 128 cycles.    */
	NULL,
	{
		{PWM_OUTPUT_ACTIVE_HIGH, NULL},
		{PWM_OUTPUT_ACTIVE_HIGH, NULL},
		{PWM_OUTPUT_ACTIVE_HIGH, NULL},
		{PWM_OUTPUT_DISABLED, NULL}
	},
	/* HW dependent part.*/
	0,
	0
};

/*
 * Global user variables
 */
uint8_t log_active=0;
uint8_t rgb_co2ppm=1;
uint16_t co2_ppm;
float_t pressure;
float_t temperature1;
float_t rhumidity;
float_t temperature2;

/*===========================================================================*/
/* Command line related.                                                     */
/*===========================================================================*/

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)

static void cmd_mem(BaseSequentialStream *chp, int argc, char *argv[]) {
  size_t n, size;

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: mem\r\n");
    return;
  }
  n = chHeapStatus(NULL, &size);
  chprintf(chp, "core free memory : %u bytes\r\n", chCoreGetStatusX());
  chprintf(chp, "heap fragments   : %u\r\n", n);
  chprintf(chp, "heap free total  : %u bytes\r\n", size);
}

static void cmd_threads(BaseSequentialStream *chp, int argc, char *argv[]) {
  static const char *states[] = {CH_STATE_NAMES};
  thread_t *tp;

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: threads\r\n");
    return;
  }
  chprintf(chp, "    addr    stack prio refs     state\r\n");
  tp = chRegFirstThread();
  do {
    chprintf(chp, "%08lx %08lx %4lu %4lu %9s %lu\r\n",
             (uint32_t)tp, (uint32_t)tp->p_ctx.r13,
             (uint32_t)tp->p_prio, (uint32_t)(tp->p_refs - 1),
             states[tp->p_state]);
    tp = chRegNextThread(tp);
  } while (tp != NULL);
}

static void cmd_serial(BaseSequentialStream *chp, int argc, char *argv[]) {

	(void)argv;
	if (argc > 0) {
		chprintf(chp, "Usage: serial\r\n");
		return;
	}
	// for STM32F042
	chprintf(chp, "MCU serial : %08x%08x%08x\r\n", \
					*(__IO uint32_t*)(0x1FFFF7B4), \
					*(__IO uint32_t*)(0x1FFFF7B0), \
					*(__IO uint32_t*)(0x1FFFF7AC));
	// for STM32F303
	//chprintf(chp, "MCU serial : %08x%08x%08x\r\n", \
					*(__IO uint32_t*)(0x1FFFF7B4), \
					*(__IO uint32_t*)(0x1FFFF7B0), \
					*(__IO uint32_t*)(0x1FFFF7AC));
	// for STM32L152
	//chprintf(chp, "MCU serial : %08x%08x%08x\r\n", \
					*(__IO uint32_t*)(0x1FF80064),\
					*(__IO uint32_t*)(0x1FF80054),\
					*(__IO uint32_t*)(0x1FF80050));
}

static void cmd_i2c(BaseSequentialStream *chp, int argc, char *argv[]) {
	uint8_t i2c_device_address, loop;
	static msg_t status = MSG_OK;
	static i2cflags_t errors = 0;

	systime_t tmo = MS2ST(4);
	uint8_t i2c_rx_data[16];
	uint8_t i2c_tx_data[2];

	(void)argv;
	if (argc != 4 || !((*argv[0]=='r') || (*argv[0]=='w')) )
	{
		chprintf(chp, "Usage: i2c [w|r] [device_addr] [reg_addr] [data|nb bytes to read]\r\n");
		return;
	}
	else
	{
		i2c_device_address=(uint8_t)strtol(argv[1], NULL,16);	// device address
		i2c_device_address &= 0xFE;
		i2c_device_address >>= 1;
		i2c_tx_data[0]=(uint8_t)strtol(argv[2], NULL,16);		// register address
		i2c_tx_data[1]=(uint8_t)strtol(argv[3], NULL,16);		// data to write or nb byte to read
		if(*argv[0]=='r')	// read command
		{
			i2cAcquireBus(&I2CD1);
			status = i2cMasterTransmitTimeout(&I2CD1, i2c_device_address, i2c_tx_data, 1, i2c_rx_data, i2c_tx_data[1], tmo);
			if (status != MSG_OK)
			{
				errors = i2cGetErrors(&I2CD1);
				chprintf(chp, "error : %02.2x\r\n", errors);
			}
			else
			{
				chprintf(chp, "%02.2xr%02.2x> ", i2c_device_address<<1, i2c_tx_data[0]);
				for (loop=0; loop<i2c_tx_data[1];)
				{
					chprintf(chp, "%02.2x", i2c_rx_data[loop]);
					if (++loop<i2c_tx_data[1])
					{
						if(loop % 2)
							chprintf(chp, ",");
						else
							chprintf(chp, ";");
					}
				}
				chprintf(chp,"\r\n");
			}
			i2cReleaseBus(&I2CD1);
		}
		else	// write command
		{
			i2cAcquireBus(&I2CD1);
			status = i2cMasterTransmitTimeout(&I2CD1, i2c_device_address, i2c_tx_data, 2, i2c_rx_data, 0, tmo);
			if (status != MSG_OK)
			{
				errors = i2cGetErrors(&I2CD1);
				chprintf(chp, "error : %02.2x\r\n", errors);
			}
			else
			{
				chprintf(chp, "%02.2xr%02.2x<%02.2x\r\n", i2c_device_address<<1, i2c_tx_data[0], i2c_tx_data[1]);
			}
			i2cReleaseBus(&I2CD1);
		}
	}
}

static void cmd_log(BaseSequentialStream *chp, int argc, char *argv[]) {
	(void)argv;
	if (argc != 1 || !((*argv[0]=='1') || (*argv[0]=='0')) )
	{
		chprintf(chp, "Usage: log [1|0]\r\n");
		return;
	}
	else
	{
		if (*argv[0]=='1')
			log_active=1;
		else
			log_active=0;
	}
}

static void cmd_rgb(BaseSequentialStream *chp, int argc, char *argv[]) {
	(void)argv;
	uint32_t rgb_value;
	
	if (	argc != 1 || strlen(argv[0]) != 6 || \
			!isxdigit((int)argv[0][0]) || !isxdigit((int)argv[0][1]) ||\
			!isxdigit((int)argv[0][2]) || !isxdigit((int)argv[0][3]) ||\
			!isxdigit((int)argv[0][4]) || !isxdigit((int)argv[0][5]) )
			
	{
		chprintf(chp, "Usage: rgb <24bits_hex_value>\r\n");
		return;
	}
	else
	{
		rgb_co2ppm=0;
		rgb_value = strtol(argv[0], NULL, 16);
		/* LED_RED : TIM3 CH2 PA7 */
		pwmEnableChannel(&PWMD3, 1, (pwmcnt_t)((rgb_value>>16)&0xFF));
		/* LED_GREEN: TIM3 CH3 PB0 */
		pwmEnableChannel(&PWMD3, 2, (pwmcnt_t)((rgb_value>>8)&0xFF));
		/* LED_BLUE : TIM3 CH1 PA6 */
		pwmEnableChannel(&PWMD3, 0, (pwmcnt_t)((rgb_value)&0xFF));
	}
}


static void cmd_nadpkey(BaseSequentialStream *chp, int argc, char *argv[]) {
	(void)argv;

	if (argc != 0)
	{
		chprintf(chp, "Usage: nadpkey\r\n");
		return;
	}
	else
	{
		palClearPad(GPIOA, GPIOA_NAD_PKEY);
		chThdSleepMilliseconds(1200);
		palSetPad(GPIOA, GPIOA_NAD_PKEY);
	}
}


static void cmd_gas(BaseSequentialStream *chp, int argc, char *argv[]) {
	(void)argv;

	if (argc != 2)
	{
		chprintf(chp, "Usage: gas <sensor_nb> [1|0|r]\r\n");
		return;
	}
	else
	{
		if (*argv[0]=='1')
		{
			if (*argv[1]=='1')
			{
				palSetPad(GPIOC, GPIOC_GS1_HON);
				palSetPad(GPIOC, GPIOC_GS1_SON);
				chprintf(chp, "Power ON GS1\r\n");
			}
			else if (*argv[1]=='0')
			{
				palClearPad(GPIOC, GPIOC_GS1_HON);
				palClearPad(GPIOC, GPIOC_GS1_SON);
				chprintf(chp, "Power OFF GS1\r\n");
			}
		}
		else if (*argv[0]=='2')
		{
			if (*argv[1]=='1')
			{
				palSetPad(GPIOB, GPIOB_GS2_HON);
				palSetPad(GPIOC, GPIOC_GS2_SON);
				chprintf(chp, "Power ON GS2\r\n");
			}
			else if (*argv[1]=='0')
			{
				palClearPad(GPIOB, GPIOB_GS2_HON);
				palClearPad(GPIOC, GPIOC_GS2_SON);
				chprintf(chp, "Power OFF GS2\r\n");
			}
		}
	}
}

static void cmd_reboot(BaseSequentialStream *chp, int argc, char *argv[]) {
	(void)argv;

	if (argc > 0)
	{
		chprintf(chp, "Usage: reboot\r\n");
		return;
	}
	else
	{
		chprintf(chp, "Rebooting...\r\n");
		NVIC_SystemReset();
	}
}

static const ShellCommand commands[] = {
  {"mem", cmd_mem},
  {"threads", cmd_threads},
  {"serial", cmd_serial},
  {"i2c", cmd_i2c},
  {"log", cmd_log},
  {"rgb", cmd_rgb},
  {"nadpkey", cmd_nadpkey},
  {"gas", cmd_gas},
  {"reboot", cmd_reboot},
  {NULL, NULL}
};

static const ShellConfig shell_cfg1 = {
  (BaseSequentialStream *)&SD1,
  commands
};

/*
 * RGB LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg)
{
	(void)arg;
	chRegSetThreadName("blinker1");

	/*
	 * Initializes PWM driver 3, routes the TIM3 outputs to the RGB LEDs.
	 */
	//pwmStart(&PWMD3, &pwmcfg);
	//palSetPadMode(GPIOA, GPIOA_LED_BLUE, PAL_MODE_ALTERNATE(2));  /* Blue. */
	//palSetPadMode(GPIOA, GPIOA_LED_RED, PAL_MODE_ALTERNATE(2));   /* Red   */
	//palSetPadMode(GPIOB, GPIOB_LED_GREEN, PAL_MODE_ALTERNATE(2)); /* Green */

	/* just to check dust sensor outputs */
	while (1)
	{
		palClearPad(GPIOB, GPIOB_LED_GREEN);
		
		if (palReadPad(GPIOA, GPIOA_PIN0))
			palClearPad(GPIOA, GPIOA_LED_RED);
		else	
			palSetPad(GPIOA, GPIOA_LED_RED);

		if (palReadPad(GPIOA, GPIOA_PIN1))
			palClearPad(GPIOA, GPIOA_LED_BLUE);
		else
		{	
			palSetPad(GPIOA, GPIOA_LED_BLUE);
			palClearPad(GPIOA, GPIOA_LED_RED);
		}

		chThdSleepMilliseconds(2);
	}

	while(rgb_co2ppm)
	{
		/* LED_BLUE : TIM3 CH1 PA6 */
		pwmEnableChannel(&PWMD3, 0, (pwmcnt_t)0);

		if ( (co2_ppm > 399) && (co2_ppm < 2400) )
		{
			/* LED_RED : TIM3 CH2 PA7 */
			pwmEnableChannel(&PWMD3, 1, (pwmcnt_t) ((co2_ppm-400) / 40));
	
			/* LED_GREEN: TIM3 CH3 PB0 */
			pwmEnableChannel(&PWMD3, 2, (pwmcnt_t) ((2400 - (co2_ppm-400)) / 40));
		}
		else if (co2_ppm < 400)
		{
			/* LED_RED : TIM3 CH2 PA7 */
			pwmEnableChannel(&PWMD3, 1, (pwmcnt_t)0);
	
			/* LED_GREEN: TIM3 CH3 PB0 */
			pwmEnableChannel(&PWMD3, 2, (pwmcnt_t)60);
		}
		else
		{
			/* LED_RED : TIM3 CH2 PA7 */
			pwmEnableChannel(&PWMD3, 1, (pwmcnt_t)60);
	
			/* LED_GREEN: TIM3 CH3 PB0 */
			pwmEnableChannel(&PWMD3, 2, (pwmcnt_t)0);
		}
	}
	chThdSleepMilliseconds(2000);
}

/*
 * MH-Z14 CO2 NDIR sensor module readout
 */
static THD_WORKING_AREA(waThread2, 128);
static THD_FUNCTION(Thread2, arg)
{
	(void)arg;
	chRegSetThreadName("co2_read");
	
	uint8_t to_mhz14[9]={ 0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x79 };
	uint8_t from_mhz14[9];
	
	/*
	 * Activates the serial driver 2 using the driver default configuration.
	 * PA2 and PA3 are routed to USART2 and MH-Z14 CO2 NDIR sensor module.
	 * 9600, 8, N , 1 settings.
	 */
	const SerialConfig SD2_config = { 
		9600,
		0,
		USART_CR2_STOP1_BITS | USART_CR2_LINEN,
		0 };
	sdStart(&SD2, &SD2_config);
	palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7));	/* USART2 TX. */
	palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7));	/* USART3 RX. */

	while (true) {
		sdWrite(&SD2, to_mhz14, 9);
		chThdSleepMilliseconds(800);
		sdRead(&SD2, from_mhz14, 9);
		co2_ppm = (uint16_t)(from_mhz14[2]<<8) | (uint16_t)from_mhz14[3];
		chThdSleepMilliseconds(500);
	}
}

/*
 * MPL3115A2 absolute pressure sensor readout
 */
static THD_WORKING_AREA(waThread3, 128);
static THD_FUNCTION(Thread3, arg)
{
	(void)arg;
	chRegSetThreadName("pressure_read");
	
	/* For I2C **/
	uint8_t i2c_device_address = 0x60;  /* MPL2115A2 address */
	static msg_t status = MSG_OK;
	static i2cflags_t errors = 0;
	systime_t tmo = MS2ST(4);
	uint8_t i2c_rx_data[5];
	uint8_t i2c_tx_data[3];
	/* EOF For I2C **/

	uint32_t tempPressure;
	int16_t tempTemperature;
	
	/*
	 * Initialization of the sensor
	 */
	i2cAcquireBus(&I2CD1);

	i2c_tx_data[0]=0x26;   // CTRL_REG1 register
	i2c_tx_data[1]=0x3B;   // ALT=0, RAW=0, OS=111, RST=0, OST=1, SBYB=1
	status = i2cMasterTransmitTimeout(&I2CD1, i2c_device_address, i2c_tx_data, 2, i2c_rx_data, 0, tmo);
	if (status != MSG_OK) {
		errors = i2cGetErrors(&I2CD1);
		chprintf((BaseSequentialStream *)&SD1, "[%010d] i2c error : %02.2x at address %02.2x\r\n", chVTGetSystemTime(), errors, i2c_device_address); 
	}

	i2cReleaseBus(&I2CD1);
	chThdSleepMilliseconds(1100);
	
	while (true) {
		i2cAcquireBus(&I2CD1);
		i2c_tx_data[0]=0x01;   // PRESS_OUT_XL register, auto-increment
		i2c_tx_data[1]=5;      // nb byte to read
		status = i2cMasterTransmitTimeout(&I2CD1, i2c_device_address, i2c_tx_data, 1, i2c_rx_data, i2c_tx_data[1], tmo);
		if (status != MSG_OK) {
			errors = i2cGetErrors(&I2CD1);
			chprintf((BaseSequentialStream *)&SD1, "[%010d] i2c error : %02.2x at address %02.2x\r\n", chVTGetSystemTime(), errors, i2c_device_address); 
		}
		else
		{
			/* Build the resulting data into float 18bits.2bits pascals */
			tempPressure = (((uint32_t) i2c_rx_data[0]) << 12);
			tempPressure |= (((uint32_t) i2c_rx_data[1]) << 4);
			tempPressure |= (((uint32_t) (i2c_rx_data[2] & 0xF0)) >> 4);
			pressure = ((float_t) tempPressure) / 4;

			tempTemperature = (((int16_t) i2c_rx_data[3]) << 4);
			tempTemperature |= (((int16_t) i2c_rx_data[4]&0xF0) >> 4);
			if(tempTemperature & 0x1000)
			{
				tempTemperature=~(tempTemperature & 0x1FFF) +1;
				tempTemperature=(tempTemperature & 0x1FFF) * -1;
			}
			temperature1 = ((float_t)tempTemperature/16);
		}
		i2cReleaseBus(&I2CD1);
		chThdSleepMilliseconds(1100);
	}
}

/*
 * Si7006 relative himidity sensor readout
 */
static THD_WORKING_AREA(waThread4, 128);
static THD_FUNCTION(Thread4, arg)
{
	(void)arg;
	chRegSetThreadName("humidity_read");
	
	/* For I2C **/
	uint8_t i2c_device_address = 0x40;  /* Si7006 address */
	static msg_t status = MSG_OK;
	static i2cflags_t errors = 0;
	systime_t tmo = MS2ST(4);
	uint8_t i2c_rx_data[3];
	uint8_t i2c_tx_data[2];
	/* EOF For I2C **/

	uint32_t retry;
	uint16_t tempRHumidity, tempTemperature;
	
	/*
	 * Initialization of the sensor
	 */
	i2cAcquireBus(&I2CD1);

	i2cReleaseBus(&I2CD1);
	
	while (true) {
		i2cAcquireBus(&I2CD1);
		i2c_tx_data[0]=0xF5;   // measure RH, no hold master mode
		i2c_tx_data[1]=0;      // nb byte to read
		status = i2cMasterTransmitTimeout(&I2CD1, i2c_device_address, i2c_tx_data, 1, NULL, 0, tmo);
		if (status != MSG_OK) {
			errors = i2cGetErrors(&I2CD1);
			chprintf((BaseSequentialStream *)&SD1, "[%010d] i2c write error : %02.2x at address %02.2x\r\n", chVTGetSystemTime(), errors, i2c_device_address); 
		}
		else
		{
			for(retry=0; retry<=150; retry++)
			{
				status = i2cMasterReceiveTimeout(&I2CD1, i2c_device_address, i2c_rx_data, 3, tmo);
				if (status != MSG_OK) {
					errors = i2cGetErrors(&I2CD1);
				}
				else
				{
					tempRHumidity = (((uint16_t) i2c_rx_data[0]) << 8);
					tempRHumidity |= ((uint16_t) i2c_rx_data[1]);
					rhumidity = (((float_t)tempRHumidity * 125.0) / 65536.0) - 6.0;
					break;
				}
				chThdSleepMilliseconds(1);
			}
			if(retry > 150)
			{
				chprintf((BaseSequentialStream *)&SD1, "[%010d] i2c read error : %02.2x at address %02.2x\r\n", chVTGetSystemTime(), errors, i2c_device_address);
			}
			else
			{ 
				//	chprintf((BaseSequentialStream *)&SD1, "[%010d] Si7006 readout after retry %d\r\n", chVTGetSystemTime(), retry);
				i2c_tx_data[0]=0xE0;   // read temperature value from previous RH measurement
				i2c_tx_data[1]=2;      // nb byte to read
				status = i2cMasterTransmitTimeout(&I2CD1, i2c_device_address, i2c_tx_data, 1, i2c_rx_data, i2c_tx_data[1], tmo);
				if (status != MSG_OK) {
					errors = i2cGetErrors(&I2CD1);
					chprintf((BaseSequentialStream *)&SD1, "[%010d] i2c error : %02.2x at address %02.2x\r\n", chVTGetSystemTime(), errors, i2c_device_address);
				}
				else
				{
					tempTemperature = (((uint16_t) i2c_rx_data[0]) << 8);
					tempTemperature |= ((uint16_t) i2c_rx_data[1]);
					temperature2 = (((float_t)tempTemperature * 175.72) / 65536.0) - 46.85;
				}
			}
		}
		i2cReleaseBus(&I2CD1);
		chThdSleepMilliseconds(1050);
	}
}

/*
 * GAS sensor test thread
 */
static THD_WORKING_AREA(waThread5, 128);
static THD_FUNCTION(Thread5, arg)
{
	(void)arg;
	chRegSetThreadName("gas_sensor_tst");
	
	while(TRUE)
	{
		chThdSleepMilliseconds(30);

		//palSetPad(GPIOB, GPIOB_GS2_HON);
		//chThdSleepMilliseconds(30);
		//palClearPad(GPIOB, GPIOB_GS2_HON);
		
		//palSetPad(GPIOC, GPIOC_GS2_SON);
		//chThdSleepMilliseconds(30);
		//palClearPad(GPIOC, GPIOC_GS2_SON);
		
		//palSetPad(GPIOC, GPIOC_GS1_HON);
		//chThdSleepMilliseconds(30);
		//palClearPad(GPIOC, GPIOC_GS1_HON);
		
		//palSetPad(GPIOC, GPIOC_GS1_SON);
		//chThdSleepMilliseconds(30);
		//palClearPad(GPIOC, GPIOC_GS1_SON);
	}	
}

/*
 * Application entry point.
 */
int main(void) {
  thread_t *shelltp1 = NULL;
	/*
	 * System initializations.
	 * - HAL initialization, this also initializes the configured device drivers
	 *   and performs the board-specific initializations.
	 * - Kernel initialization, the main() function becomes a thread and the
	 *   RTOS is active.
	 */
	halInit();
	chSysInit();

	// declared in board.h
	//palSetPadMode(GPIOA, 5, PAL_MODE_OUTPUT_PUSHPULL);

	/*
	 * Activates the serial driver 1 using the driver default configuration.
	 * PA9 and PA10 are routed to USART1.
	 */
	const SerialConfig SD1_config = { 
		115200,
		0,
		USART_CR2_STOP1_BITS | USART_CR2_LINEN,
		0 };
	sdStart(&SD1, &SD1_config);
	//palSetPadMode(GPIOA, 9, PAL_MODE_ALTERNATE(7));	/* USART1 TX. */
	//palSetPadMode(GPIOA, 10, PAL_MODE_ALTERNATE(7));	/* USART1 RX. */

	// I2C driver init
	i2cInit();
	i2cStart(&I2CD1, &i2cfg1);
	//palSetPadMode(GPIOB, 6, PAL_MODE_ALTERNATE(4));	/* I2C1 SCL */
	//palSetPadMode(GPIOB, 7, PAL_MODE_ALTERNATE(4));	/* I2C1 SDA */

   /*
   * Activates the ADC1 driver and the temperature sensor.
   */
  adcStart(&ADCD1, NULL);

  /*
   * Linear conversion.
   */
  adcConvert(&ADCD1, &adcgrpcfg1, samples1, ADC_GRP1_BUF_DEPTH);
  chThdSleepMilliseconds(1000);

  /*
   * Starts an ADC continuous conversion.
   */
  adcStartConversion(&ADCD1, &adcgrpcfg2, samples2, ADC_GRP2_BUF_DEPTH);

  /*
   * Shell manager initialization.
   */
  shellInit();

	/* Creates RGB LED blinker thread */
	chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

	/* Creates MH-Z14 CO2 NDIR sensor module readout thread */
	chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);

	/* Creates MPL3115A2 absolute pressure sensor readout thread */
	chThdCreateStatic(waThread3, sizeof(waThread3), NORMALPRIO, Thread3, NULL);

	/* Creates Si7006 relative himidity sensor readout thread */
	chThdCreateStatic(waThread4, sizeof(waThread4), NORMALPRIO, Thread4, NULL);

	/* Creates gas sensors test thread */
	chThdCreateStatic(waThread5, sizeof(waThread5), NORMALPRIO, Thread5, NULL);

	/*
	 * Normal main() thread activity, in this demo it does nothing except
	 * sleeping in a loop and check the button state, when the button is
	 * pressed the test procedure is launched with output on the serial
	 * driver 1.
	 */
	while (true) {
		if (!shelltp1)
			shelltp1 = shellCreate(&shell_cfg1, SHELL_WA_SIZE, NORMALPRIO);
		else if (chThdTerminatedX(shelltp1)) {
			chThdRelease(shelltp1);   /* Recovers memory of the previous shell.   */
			shelltp1 = NULL;          /* Triggers spawning of a new shell.        */
		}
		if ( log_active==1 ) {
			chprintf((BaseSequentialStream *)&SD1, "\n[%010d] CO2 concentration : %d ppm\r\n", chVTGetSystemTime(), co2_ppm);
			chprintf((BaseSequentialStream *)&SD1, "[%010d] absolute pressure : %6.2f Pa (%3.2f mmHg)\r\n", chVTGetSystemTime(), pressure, pressure*0.0075006375541921);
			chprintf((BaseSequentialStream *)&SD1, "[%010d] temperature 1     : %2.2f deg. C (%3.2f deg. F)\r\n", chVTGetSystemTime(), temperature1, (temperature1*1.8)+32.0);
			chprintf((BaseSequentialStream *)&SD1, "[%010d] relative humidity : %2.2f percent\r\n", chVTGetSystemTime(), rhumidity);
			chprintf((BaseSequentialStream *)&SD1, "[%010d] temperature 2     : %2.2f deg. C (%3.2f deg. F)\r\n", chVTGetSystemTime(), temperature2, (temperature2*1.8)+32.0);
			chprintf((BaseSequentialStream *)&SD1, "[%010d] GAS1 ADC raw      : 0x%03.3x\r\n", chVTGetSystemTime(), samples2[1]);
			chprintf((BaseSequentialStream *)&SD1, "[%010d] GAS2 ADC raw      : 0x%03.3x\r\n", chVTGetSystemTime(), samples2[3]);
			chprintf((BaseSequentialStream *)&SD1, "[%010d] GAS1 ADC volt     : %01.3f V\r\n", chVTGetSystemTime(), ((float_t)samples2[1]*3.29)/4096);
			chprintf((BaseSequentialStream *)&SD1, "[%010d] GAS2 ADC volt     : %01.3f V\r\n", chVTGetSystemTime(), ((float_t)samples2[3]*3.29)/4096);

			chThdSleepMilliseconds(2000);
		}
	}
}
