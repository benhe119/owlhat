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

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for OWL v0.1 board.
 */

/*
 * Board identifier.
 */
#define BOARD_AAAAAAA_OWL_V01
#define BOARD_NAME                  "AAAAAAA OWL v0.1"

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 * NOTE: HSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#define STM32_LSEDRV                (3U << 3U)

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                16000000U
#endif

/* #define STM32_HSE_BYPASS */

/*
 * MCU type as defined in the ST header.
 */
#define STM32F303xC

/*
 * IO pins assignments.
 */
#define GPIOA_PIN0                  0U
#define GPIOA_PIN1                  1U
#define GPIOA_PIN2                  2U
#define GPIOA_PIN3                  3U
#define GPIOA_GS2_OUT               4U
#define GPIOA_GS1_OUT               5U
#define GPIOA_LED_BLUE              6U
#define GPIOA_LED_RED               7U
#define GPIOA_NAD_PKEY              8U
#define GPIOA_RPI_RXD               9U
#define GPIOA_RPI_TXD               10U
#define GPIOA_USB_DM                11U
#define GPIOA_USB_DP                12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_PIN15                 15U

#define GPIOB_LED_GREEN             0U
#define GPIOB_PIN1                  1U
#define GPIOB_NAD_TXBURST           2U
#define GPIOB_PIN3                  3U
#define GPIOB_PIN4                  4U
#define GPIOB_PIN5                  5U
#define GPIOB_SCL                   6U
#define GPIOB_SDA                   7U
#define GPIOB_GS2_HON               8U
#define GPIOB_PIN9                  9U
#define GPIOB_NAD_RXD               10U
#define GPIOB_NAD_TXD               11U
#define GPIOB_PIN12                 12U
#define GPIOB_PIN13                 13U
#define GPIOB_PIN14                 14U
#define GPIOB_NAD_RI                15U

#define GPIOC_PIN0                  0U
#define GPIOC_PIN1                  1U
#define GPIOC_PIN2                  2U
#define GPIOC_PIN3                  3U
#define GPIOC_PIN4                  4U
#define GPIOC_PIN5                  5U
#define GPIOC_PIN6                  6U
#define GPIOC_PIN7                  7U
#define GPIOC_PIN8                  8U
#define GPIOC_PIN9                  9U
#define GPIOC_PIN10                 10U
#define GPIOC_PIN11                 11U
#define GPIOC_PIN12                 12U
#define GPIOC_GS2_SON               13U
#define GPIOC_GS1_SON               14U
#define GPIOC_GS1_HON               15U

#define GPIOD_PIN0                  0U
#define GPIOD_PIN1                  1U
#define GPIOD_PIN2                  2U
#define GPIOD_PIN3                  3U
#define GPIOD_PIN4                  4U
#define GPIOD_PIN5                  5U
#define GPIOD_PIN6                  6U
#define GPIOD_PIN7                  7U
#define GPIOD_PIN8                  8U
#define GPIOD_PIN9                  9U
#define GPIOD_PIN10                 10U
#define GPIOD_PIN11                 11U
#define GPIOD_PIN12                 12U
#define GPIOD_PIN13                 13U
#define GPIOD_PIN14                 14U
#define GPIOD_PIN15                 15U

#define GPIOE_PIN0                  0U
#define GPIOE_PIN1                  1U
#define GPIOE_PIN2                  2U
#define GPIOE_PIN3                  3U
#define GPIOE_PIN4                  4U
#define GPIOE_PIN5                  5U
#define GPIOE_PIN6                  6U
#define GPIOE_PIN7                  7U
#define GPIOE_PIN8                  8U
#define GPIOE_PIN9                  9U
#define GPIOE_PIN10                 10U
#define GPIOE_PIN11                 11U
#define GPIOE_PIN12                 12U
#define GPIOE_PIN13                 13U
#define GPIOE_PIN14                 14U
#define GPIOE_PIN15                 15U

#define GPIOF_OSC_IN                0U
#define GPIOF_OSC_OUT               1U
#define GPIOF_PIN2                  2U
#define GPIOF_PIN3                  3U
#define GPIOF_PIN4                  4U
#define GPIOF_PIN5                  5U
#define GPIOF_PIN6                  6U
#define GPIOF_PIN7                  7U
#define GPIOF_PIN8                  8U
#define GPIOF_PIN9                  9U
#define GPIOF_PIN10                 10U
#define GPIOF_PIN11                 11U
#define GPIOF_PIN12                 12U
#define GPIOF_PIN13                 13U
#define GPIOF_PIN14                 14U
#define GPIOF_PIN15                 15U

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_2M(n)            (0U << ((n) * 2U))
#define PIN_OSPEED_10M(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_40M(n)           (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v##U) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 *
 * PA0  - PIN0                      (input pullup).
 * PA1  - PIN1                      (input pullup).
 * PA2  - PIN2                      (input pullup).
 * PA3  - PIN3                      (input pullup).
 * PA4  - GS2_OUT                   (input analog).
 * PA5  - GS1_OUT                   (input analog).
 * PA6  - LED_BLUE                  (output push-pull).
 * PA7  - LED_RED                   (output push-pull).
 * PA8  - PIN8                      (input pullup).
 * PA9  - PIN9                      (input pullup).
 * PA10 - PIN10                     (input pullup).
 * PA11 - USB_DM                    (alternate 14).
 * PA12 - USB_DP                    (alternate 14).
 * PA13 - SWDIO                     (alternate 0).
 * PA14 - SWCLK                     (alternate 0).
 * PA15 - PIN15                     (input pullup).
 */
#define VAL_GPIOA_MODER        (PIN_MODE_INPUT(GPIOA_PIN0) |           \
                                PIN_MODE_INPUT(GPIOA_PIN1) |           \
                                PIN_MODE_INPUT(GPIOA_PIN2) |           \
                                PIN_MODE_INPUT(GPIOA_PIN3) |           \
                                PIN_MODE_ANALOG(GPIOA_GS2_OUT) |       \
                                PIN_MODE_ANALOG(GPIOA_GS1_OUT) |       \
                                PIN_MODE_OUTPUT(GPIOA_LED_BLUE) |   \
                                PIN_MODE_OUTPUT(GPIOA_LED_RED) |    \
                                PIN_MODE_OUTPUT(GPIOA_NAD_PKEY) |      \
                                PIN_MODE_ALTERNATE(GPIOA_RPI_RXD) |    \
                                PIN_MODE_ALTERNATE(GPIOA_RPI_TXD) |    \
                                PIN_MODE_ALTERNATE(GPIOA_USB_DM) |     \
                                PIN_MODE_ALTERNATE(GPIOA_USB_DP) |     \
                                PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                PIN_MODE_INPUT(GPIOA_PIN15))
#define VAL_GPIOA_OTYPER       (PIN_OTYPE_PUSHPULL(GPIOA_PIN0) |       \
                                PIN_OTYPE_PUSHPULL(GPIOA_PIN1) |       \
                                PIN_OTYPE_PUSHPULL(GPIOA_PIN2) |       \
                                PIN_OTYPE_PUSHPULL(GPIOA_PIN3) |       \
                                PIN_OTYPE_PUSHPULL(GPIOA_GS2_OUT) |    \
                                PIN_OTYPE_PUSHPULL(GPIOA_GS1_OUT) |    \
                                PIN_OTYPE_PUSHPULL(GPIOA_LED_BLUE) |   \
                                PIN_OTYPE_PUSHPULL(GPIOA_LED_RED) |    \
                                PIN_OTYPE_OPENDRAIN(GPIOA_NAD_PKEY) |  \
                                PIN_OTYPE_PUSHPULL(GPIOA_RPI_RXD) |    \
                                PIN_OTYPE_PUSHPULL(GPIOA_RPI_TXD) |    \
                                PIN_OTYPE_PUSHPULL(GPIOA_USB_DM) |     \
                                PIN_OTYPE_PUSHPULL(GPIOA_USB_DP) |     \
                                PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                PIN_OTYPE_PUSHPULL(GPIOA_PIN15))
#define VAL_GPIOA_OSPEEDR      (PIN_OSPEED_2M(GPIOA_PIN0) |            \
                                PIN_OSPEED_2M(GPIOA_PIN1) |            \
                                PIN_OSPEED_2M(GPIOA_PIN2) |            \
                                PIN_OSPEED_2M(GPIOA_PIN3) |            \
                                PIN_OSPEED_2M(GPIOA_GS2_OUT) |         \
                                PIN_OSPEED_2M(GPIOA_GS1_OUT) |         \
                                PIN_OSPEED_2M(GPIOA_LED_BLUE) |        \
                                PIN_OSPEED_2M(GPIOA_LED_RED) |         \
                                PIN_OSPEED_2M(GPIOA_NAD_PKEY) |        \
                                PIN_OSPEED_2M(GPIOA_RPI_RXD) |         \
                                PIN_OSPEED_2M(GPIOA_RPI_TXD) |         \
                                PIN_OSPEED_2M(GPIOA_USB_DM) |          \
                                PIN_OSPEED_2M(GPIOA_USB_DP) |          \
                                PIN_OSPEED_40M(GPIOA_SWDIO) |          \
                                PIN_OSPEED_40M(GPIOA_SWCLK) |          \
                                PIN_OSPEED_2M(GPIOA_PIN15))
#define VAL_GPIOA_PUPDR        (PIN_PUPDR_PULLUP(GPIOA_PIN0) |         \
                                PIN_PUPDR_PULLUP(GPIOA_PIN1) |         \
                                PIN_PUPDR_PULLUP(GPIOA_PIN2) |         \
                                PIN_PUPDR_PULLUP(GPIOA_PIN3) |         \
                                PIN_PUPDR_FLOATING(GPIOA_GS2_OUT) |    \
                                PIN_PUPDR_FLOATING(GPIOA_GS1_OUT) |    \
                                PIN_PUPDR_PULLUP(GPIOA_LED_BLUE) |     \
                                PIN_PUPDR_PULLUP(GPIOA_LED_RED) |      \
                                PIN_PUPDR_FLOATING(GPIOA_NAD_PKEY) |   \
                                PIN_PUPDR_PULLUP(GPIOA_RPI_RXD) |      \
                                PIN_PUPDR_PULLUP(GPIOA_RPI_TXD) |      \
                                PIN_PUPDR_FLOATING(GPIOA_USB_DM) |     \
                                PIN_PUPDR_FLOATING(GPIOA_USB_DP) |     \
                                PIN_PUPDR_PULLUP(GPIOA_SWDIO) |        \
                                PIN_PUPDR_PULLDOWN(GPIOA_SWCLK) |      \
                                PIN_PUPDR_PULLUP(GPIOA_PIN15))
#define VAL_GPIOA_ODR          (PIN_ODR_HIGH(GPIOA_PIN0) |             \
                                PIN_ODR_HIGH(GPIOA_PIN1) |             \
                                PIN_ODR_HIGH(GPIOA_PIN2) |             \
                                PIN_ODR_HIGH(GPIOA_PIN3) |             \
                                PIN_ODR_HIGH(GPIOA_GS2_OUT) |          \
                                PIN_ODR_HIGH(GPIOA_GS1_OUT) |          \
                                PIN_ODR_HIGH(GPIOA_LED_BLUE) |         \
                                PIN_ODR_HIGH(GPIOA_LED_RED) |          \
                                PIN_ODR_HIGH(GPIOA_NAD_PKEY) |         \
                                PIN_ODR_HIGH(GPIOA_RPI_RXD) |          \
                                PIN_ODR_HIGH(GPIOA_RPI_TXD) |          \
                                PIN_ODR_HIGH(GPIOA_USB_DM) |           \
                                PIN_ODR_HIGH(GPIOA_USB_DP) |           \
                                PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                PIN_ODR_HIGH(GPIOA_PIN15))
#define VAL_GPIOA_AFRL         (PIN_AFIO_AF(GPIOA_PIN0, 0) |           \
                                PIN_AFIO_AF(GPIOA_PIN1, 0) |           \
                                PIN_AFIO_AF(GPIOA_PIN2, 0) |           \
                                PIN_AFIO_AF(GPIOA_PIN3, 0) |           \
                                PIN_AFIO_AF(GPIOA_GS2_OUT, 0) |        \
                                PIN_AFIO_AF(GPIOA_GS1_OUT, 0) |        \
                                PIN_AFIO_AF(GPIOA_LED_BLUE, 0) |       \
                                PIN_AFIO_AF(GPIOA_LED_RED, 0))
#define VAL_GPIOA_AFRH         (PIN_AFIO_AF(GPIOA_NAD_PKEY, 0) |       \
                                PIN_AFIO_AF(GPIOA_RPI_RXD, 7) |        \
                                PIN_AFIO_AF(GPIOA_RPI_TXD, 7) |        \
                                PIN_AFIO_AF(GPIOA_USB_DM, 14) |        \
                                PIN_AFIO_AF(GPIOA_USB_DP, 14) |        \
                                PIN_AFIO_AF(GPIOA_SWDIO, 0) |          \
                                PIN_AFIO_AF(GPIOA_SWCLK, 0) |          \
                                PIN_AFIO_AF(GPIOA_PIN15, 0))

/*
 * GPIOB setup:
 *
 * PB0  - LED_GREEN                 (input pullup).
 * PB1  - PIN1                      (input pullup).
 * PB2  - NAD_TXBURST               (input floating).
 * PB3  - PIN3                      (input pullup).
 * PB4  - PIN4                      (input pullup).
 * PB5  - PIN5                      (input pullup).
 * PB6  - SCL                       (alternate 4 ).
 * PB7  - SDA                       (alternate 4 ).
 * PB8  - GS2_HON                   (output pushpull).
 * PB9  - PIN9                      (input pullup).
 * PB10 - NAD_RXD                   (alternate 7).
 * PB11 - NAD_TXD                   (alternate 7).
 * PB12 - PIN12                     (input pullup).
 * PB13 - PIN13                     (input pullup).
 * PB14 - PIN14                     (input pullup).
 * PB15 - NAD_RI                    (input pullup).
 */
#define VAL_GPIOB_MODER        (PIN_MODE_OUTPUT(GPIOB_LED_GREEN) |  \
                                PIN_MODE_INPUT(GPIOB_PIN1) |           \
                                PIN_MODE_INPUT(GPIOB_NAD_TXBURST) |    \
                                PIN_MODE_INPUT(GPIOB_PIN3) |           \
                                PIN_MODE_INPUT(GPIOB_PIN4) |           \
                                PIN_MODE_INPUT(GPIOB_PIN5) |           \
                                PIN_MODE_ALTERNATE(GPIOB_SCL) |        \
                                PIN_MODE_ALTERNATE(GPIOB_SDA) |        \
                                PIN_MODE_OUTPUT(GPIOB_GS2_HON) |       \
                                PIN_MODE_INPUT(GPIOB_PIN9) |           \
                                PIN_MODE_ALTERNATE(GPIOB_NAD_RXD) |    \
                                PIN_MODE_ALTERNATE(GPIOB_NAD_TXD) |    \
                                PIN_MODE_INPUT(GPIOB_PIN12) |          \
                                PIN_MODE_INPUT(GPIOB_PIN13) |          \
                                PIN_MODE_INPUT(GPIOB_PIN14) |          \
                                PIN_MODE_INPUT(GPIOB_NAD_RI))
#define VAL_GPIOB_OTYPER       (PIN_OTYPE_PUSHPULL(GPIOB_LED_GREEN) |  \
                                PIN_OTYPE_PUSHPULL(GPIOB_PIN1) |       \
                                PIN_OTYPE_PUSHPULL(GPIOB_NAD_TXBURST) |\
                                PIN_OTYPE_PUSHPULL(GPIOB_PIN3) |       \
                                PIN_OTYPE_PUSHPULL(GPIOB_PIN4) |       \
                                PIN_OTYPE_PUSHPULL(GPIOB_PIN5) |       \
                                PIN_OTYPE_PUSHPULL(GPIOB_SCL)  |       \
                                PIN_OTYPE_PUSHPULL(GPIOB_SDA)  |       \
                                PIN_OTYPE_PUSHPULL(GPIOB_GS2_HON) |    \
                                PIN_OTYPE_PUSHPULL(GPIOB_PIN9) |       \
                                PIN_OTYPE_PUSHPULL(GPIOB_NAD_RXD) |    \
                                PIN_OTYPE_PUSHPULL(GPIOB_NAD_TXD) |    \
                                PIN_OTYPE_PUSHPULL(GPIOB_PIN12) |      \
                                PIN_OTYPE_PUSHPULL(GPIOB_PIN13) |      \
                                PIN_OTYPE_PUSHPULL(GPIOB_PIN14) |      \
                                PIN_OTYPE_PUSHPULL(GPIOB_NAD_RI))
#define VAL_GPIOB_OSPEEDR      (PIN_OSPEED_2M(GPIOB_LED_GREEN) |       \
                                PIN_OSPEED_2M(GPIOB_PIN1) |            \
                                PIN_OSPEED_2M(GPIOB_NAD_TXBURST) |     \
                                PIN_OSPEED_2M(GPIOB_PIN3) |            \
                                PIN_OSPEED_2M(GPIOB_PIN4) |            \
                                PIN_OSPEED_2M(GPIOB_PIN5) |            \
                                PIN_OSPEED_2M(GPIOB_SCL) |             \
                                PIN_OSPEED_2M(GPIOB_SDA) |             \
                                PIN_OSPEED_2M(GPIOB_GS2_HON) |         \
                                PIN_OSPEED_2M(GPIOB_PIN9) |            \
                                PIN_OSPEED_2M(GPIOB_NAD_RXD) |         \
                                PIN_OSPEED_2M(GPIOB_NAD_TXD) |         \
                                PIN_OSPEED_2M(GPIOB_PIN12) |           \
                                PIN_OSPEED_2M(GPIOB_PIN13) |           \
                                PIN_OSPEED_2M(GPIOB_PIN14) |           \
                                PIN_OSPEED_2M(GPIOB_NAD_RI))
#define VAL_GPIOB_PUPDR        (PIN_PUPDR_PULLUP(GPIOB_LED_GREEN) |    \
                                PIN_PUPDR_PULLUP(GPIOB_PIN1) |         \
                                PIN_PUPDR_FLOATING(GPIOB_NAD_TXBURST) |\
                                PIN_PUPDR_PULLUP(GPIOB_PIN3) |         \
                                PIN_PUPDR_PULLUP(GPIOB_PIN4) |         \
                                PIN_PUPDR_PULLUP(GPIOB_PIN5) |         \
                                PIN_PUPDR_PULLUP(GPIOB_SCL)  |         \
                                PIN_PUPDR_PULLUP(GPIOB_SDA)  |         \
                                PIN_PUPDR_PULLUP(GPIOB_GS2_HON) |      \
                                PIN_PUPDR_PULLUP(GPIOB_PIN9) |         \
                                PIN_PUPDR_PULLUP(GPIOB_NAD_RXD) |      \
                                PIN_PUPDR_PULLUP(GPIOB_NAD_TXD) |      \
                                PIN_PUPDR_PULLUP(GPIOB_PIN12) |        \
                                PIN_PUPDR_PULLUP(GPIOB_PIN13) |        \
                                PIN_PUPDR_PULLUP(GPIOB_PIN14) |        \
                                PIN_PUPDR_FLOATING(GPIOB_NAD_RI))
#define VAL_GPIOB_ODR          (PIN_ODR_HIGH(GPIOB_LED_GREEN) |        \
                                PIN_ODR_HIGH(GPIOB_PIN1) |             \
                                PIN_ODR_HIGH(GPIOB_NAD_TXBURST) |      \
                                PIN_ODR_HIGH(GPIOB_PIN3) |             \
                                PIN_ODR_HIGH(GPIOB_PIN4) |             \
                                PIN_ODR_HIGH(GPIOB_PIN5) |             \
                                PIN_ODR_HIGH(GPIOB_SCL)  |             \
                                PIN_ODR_HIGH(GPIOB_SDA)  |             \
                                PIN_ODR_LOW(GPIOB_GS2_HON) |           \
                                PIN_ODR_HIGH(GPIOB_PIN9) |             \
                                PIN_ODR_HIGH(GPIOB_NAD_RXD) |          \
                                PIN_ODR_HIGH(GPIOB_NAD_TXD) |          \
                                PIN_ODR_HIGH(GPIOB_PIN12) |            \
                                PIN_ODR_HIGH(GPIOB_PIN13) |            \
                                PIN_ODR_HIGH(GPIOB_PIN14) |            \
                                PIN_ODR_HIGH(GPIOB_NAD_RI))
#define VAL_GPIOB_AFRL         (PIN_AFIO_AF(GPIOB_LED_GREEN, 0) |      \
                                PIN_AFIO_AF(GPIOB_PIN1, 0) |           \
                                PIN_AFIO_AF(GPIOB_NAD_TXBURST, 0) |    \
                                PIN_AFIO_AF(GPIOB_PIN3, 0) |           \
                                PIN_AFIO_AF(GPIOB_PIN4, 0) |           \
                                PIN_AFIO_AF(GPIOB_PIN5, 0) |           \
                                PIN_AFIO_AF(GPIOB_SCL, 4)  |           \
                                PIN_AFIO_AF(GPIOB_SDA, 4))
#define VAL_GPIOB_AFRH         (PIN_AFIO_AF(GPIOB_GS2_HON, 0) |        \
                                PIN_AFIO_AF(GPIOB_PIN9, 0) |           \
                                PIN_AFIO_AF(GPIOB_NAD_RXD, 7) |        \
                                PIN_AFIO_AF(GPIOB_NAD_TXD, 7) |        \
                                PIN_AFIO_AF(GPIOB_PIN12, 0) |          \
                                PIN_AFIO_AF(GPIOB_PIN13, 0) |          \
                                PIN_AFIO_AF(GPIOB_PIN14, 0) |          \
                                PIN_AFIO_AF(GPIOB_NAD_RI, 0))

/*
 * GPIOC setup:
 *
 * PC0  - PIN0                      (input pullup).
 * PC1  - PIN1                      (input pullup).
 * PC2  - PIN2                      (input pullup).
 * PC3  - PIN3                      (input pullup).
 * PC4  - PIN4                      (input pullup).
 * PC5  - PIN5                      (input pullup).
 * PC5  - PIN6                      (input pullup).
 * PC5  - PIN7                      (input pullup).
 * PC5  - PIN8                      (input pullup).
 * PC5  - PIN9                      (input pullup).
 * PC10 - PIN10                     (input pullup).
 * PC11 - PIN11                     (input pullup).
 * PC12 - PIN12                     (input pullup).
 * PC13 - GS2_SON                   (output pushpull).
 * PC14 - GS1_SON                   (output pushpull).
 * PC15 - GS1_HON                   (output pushpull).
 */
#define VAL_GPIOC_MODER        (PIN_MODE_INPUT(GPIOC_PIN0) |           \
                                PIN_MODE_INPUT(GPIOC_PIN1) |           \
                                PIN_MODE_INPUT(GPIOC_PIN2) |           \
                                PIN_MODE_INPUT(GPIOC_PIN3) |           \
                                PIN_MODE_INPUT(GPIOC_PIN4) |           \
                                PIN_MODE_INPUT(GPIOC_PIN5) |           \
                                PIN_MODE_INPUT(GPIOC_PIN6) |           \
                                PIN_MODE_INPUT(GPIOC_PIN7) |           \
                                PIN_MODE_INPUT(GPIOC_PIN8) |           \
                                PIN_MODE_INPUT(GPIOC_PIN9) |           \
                                PIN_MODE_INPUT(GPIOC_PIN10) |          \
                                PIN_MODE_INPUT(GPIOC_PIN11) |          \
                                PIN_MODE_INPUT(GPIOC_PIN12) |          \
                                PIN_MODE_OUTPUT(GPIOC_GS2_SON) |       \
                                PIN_MODE_OUTPUT(GPIOC_GS1_SON) |       \
                                PIN_MODE_OUTPUT(GPIOC_GS1_HON))
#define VAL_GPIOC_OTYPER       (PIN_OTYPE_PUSHPULL(GPIOC_PIN0) |       \
                                PIN_OTYPE_PUSHPULL(GPIOC_PIN1) |       \
                                PIN_OTYPE_PUSHPULL(GPIOC_PIN2) |       \
                                PIN_OTYPE_PUSHPULL(GPIOC_PIN3) |       \
                                PIN_OTYPE_PUSHPULL(GPIOC_PIN4) |       \
                                PIN_OTYPE_PUSHPULL(GPIOC_PIN5) |       \
                                PIN_OTYPE_PUSHPULL(GPIOC_PIN6) |       \
                                PIN_OTYPE_PUSHPULL(GPIOC_PIN7) |       \
                                PIN_OTYPE_PUSHPULL(GPIOC_PIN8) |       \
                                PIN_OTYPE_PUSHPULL(GPIOC_PIN9) |       \
                                PIN_OTYPE_PUSHPULL(GPIOC_PIN10) |      \
                                PIN_OTYPE_PUSHPULL(GPIOC_PIN11) |      \
                                PIN_OTYPE_PUSHPULL(GPIOC_PIN12) |      \
                                PIN_OTYPE_PUSHPULL(GPIOC_GS2_SON) |    \
                                PIN_OTYPE_PUSHPULL(GPIOC_GS1_SON) |    \
                                PIN_OTYPE_PUSHPULL(GPIOC_GS1_HON))
#define VAL_GPIOC_OSPEEDR      (PIN_OSPEED_2M(GPIOC_PIN0) |            \
                                PIN_OSPEED_2M(GPIOC_PIN1) |            \
                                PIN_OSPEED_2M(GPIOC_PIN2) |            \
                                PIN_OSPEED_2M(GPIOC_PIN3) |            \
                                PIN_OSPEED_2M(GPIOC_PIN4) |            \
                                PIN_OSPEED_2M(GPIOC_PIN5) |            \
                                PIN_OSPEED_2M(GPIOC_PIN6) |            \
                                PIN_OSPEED_2M(GPIOC_PIN7) |            \
                                PIN_OSPEED_2M(GPIOC_PIN8) |            \
                                PIN_OSPEED_2M(GPIOC_PIN9) |            \
                                PIN_OSPEED_2M(GPIOC_PIN10) |           \
                                PIN_OSPEED_2M(GPIOC_PIN11) |           \
                                PIN_OSPEED_2M(GPIOC_PIN12) |           \
                                PIN_OSPEED_2M(GPIOC_GS2_SON) |         \
                                PIN_OSPEED_2M(GPIOC_GS1_SON) |         \
                                PIN_OSPEED_2M(GPIOC_GS1_HON))
#define VAL_GPIOC_PUPDR        (PIN_PUPDR_FLOATING(GPIOC_PIN0) |       \
                                PIN_PUPDR_PULLUP(GPIOC_PIN1) |         \
                                PIN_PUPDR_PULLUP(GPIOC_PIN2) |         \
                                PIN_PUPDR_PULLUP(GPIOC_PIN3) |         \
                                PIN_PUPDR_PULLUP(GPIOC_PIN4) |         \
                                PIN_PUPDR_PULLUP(GPIOC_PIN5) |         \
                                PIN_PUPDR_PULLUP(GPIOC_PIN6) |         \
                                PIN_PUPDR_PULLUP(GPIOC_PIN7) |         \
                                PIN_PUPDR_PULLUP(GPIOC_PIN8) |         \
                                PIN_PUPDR_PULLUP(GPIOC_PIN9) |         \
                                PIN_PUPDR_PULLUP(GPIOC_PIN10) |        \
                                PIN_PUPDR_PULLUP(GPIOC_PIN11) |        \
                                PIN_PUPDR_PULLUP(GPIOC_PIN12) |        \
                                PIN_PUPDR_PULLUP(GPIOC_GS2_SON) |      \
                                PIN_PUPDR_PULLUP(GPIOC_GS1_SON) |      \
                                PIN_PUPDR_PULLUP(GPIOC_GS1_HON))
#define VAL_GPIOC_ODR          (PIN_ODR_HIGH(GPIOC_PIN0) |             \
                                PIN_ODR_HIGH(GPIOC_PIN1) |             \
                                PIN_ODR_HIGH(GPIOC_PIN2) |             \
                                PIN_ODR_HIGH(GPIOC_PIN3) |             \
                                PIN_ODR_HIGH(GPIOC_PIN4) |             \
                                PIN_ODR_HIGH(GPIOC_PIN5) |             \
                                PIN_ODR_HIGH(GPIOC_PIN6) |             \
                                PIN_ODR_HIGH(GPIOC_PIN7) |             \
                                PIN_ODR_HIGH(GPIOC_PIN8) |             \
                                PIN_ODR_HIGH(GPIOC_PIN9) |             \
                                PIN_ODR_HIGH(GPIOC_PIN10) |            \
                                PIN_ODR_HIGH(GPIOC_PIN11) |            \
                                PIN_ODR_HIGH(GPIOC_PIN12) |            \
                                PIN_ODR_LOW(GPIOC_GS2_SON) |           \
                                PIN_ODR_LOW(GPIOC_GS1_SON) |           \
                                PIN_ODR_LOW(GPIOC_GS1_HON))
#define VAL_GPIOC_AFRL         (PIN_AFIO_AF(GPIOC_PIN0, 0) |           \
                                PIN_AFIO_AF(GPIOC_PIN1, 0) |           \
                                PIN_AFIO_AF(GPIOC_PIN2, 0) |           \
                                PIN_AFIO_AF(GPIOC_PIN3, 0) |           \
                                PIN_AFIO_AF(GPIOC_PIN4, 0) |           \
                                PIN_AFIO_AF(GPIOC_PIN5, 0) |           \
                                PIN_AFIO_AF(GPIOC_PIN6, 0) |           \
                                PIN_AFIO_AF(GPIOC_PIN7, 0))
#define VAL_GPIOC_AFRH         (PIN_AFIO_AF(GPIOC_PIN8, 0) |           \
                                PIN_AFIO_AF(GPIOC_PIN9, 0) |           \
                                PIN_AFIO_AF(GPIOC_PIN10, 0) |          \
                                PIN_AFIO_AF(GPIOC_PIN11, 0) |          \
                                PIN_AFIO_AF(GPIOC_PIN12, 0) |          \
                                PIN_AFIO_AF(GPIOC_GS2_SON, 0) |        \
                                PIN_AFIO_AF(GPIOC_GS1_SON, 0) |        \
                                PIN_AFIO_AF(GPIOC_GS1_HON, 0))

/*
 * GPIOD setup:
 *
 * PD0  - PIN0                  (input pullup).
 * PD1  - PIN1                  (input pullup).
 * PD2  - PIN2                  (input pullup).
 * PD3  - PIN3                  (input pullup).
 * PD4  - PIN4                  (input pullup).
 * PD5  - PIN5                  (input pullup).
 * PD6  - PIN6                  (input pullup).
 * PD7  - PIN7                  (input pullup).
 * PD8  - PIN8                  (input pullup).
 * PD9  - PIN9                  (input pullup).
 * PD10 - PIN10                 (input pullup).
 * PD11 - PIN11                 (input pullup).
 * PD12 - PIN12                 (input pullup).
 * PD13 - PIN13                 (input pullup).
 * PD14 - PIN14                 (input pullup).
 * PD15 - PIN15                 (input pullup).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_INPUT(GPIOD_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN15))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN15))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_2M(GPIOD_PIN0) |            \
                                     PIN_OSPEED_2M(GPIOD_PIN1) |            \
                                     PIN_OSPEED_2M(GPIOD_PIN2) |            \
                                     PIN_OSPEED_2M(GPIOD_PIN3) |            \
                                     PIN_OSPEED_2M(GPIOD_PIN4) |            \
                                     PIN_OSPEED_2M(GPIOD_PIN5) |            \
                                     PIN_OSPEED_2M(GPIOD_PIN6) |            \
                                     PIN_OSPEED_2M(GPIOD_PIN7) |            \
                                     PIN_OSPEED_2M(GPIOD_PIN8) |            \
                                     PIN_OSPEED_2M(GPIOD_PIN9) |            \
                                     PIN_OSPEED_2M(GPIOD_PIN10) |           \
                                     PIN_OSPEED_2M(GPIOD_PIN11) |           \
                                     PIN_OSPEED_2M(GPIOD_PIN12) |           \
                                     PIN_OSPEED_2M(GPIOD_PIN13) |           \
                                     PIN_OSPEED_2M(GPIOD_PIN14) |           \
                                     PIN_OSPEED_2M(GPIOD_PIN15))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_PULLUP(GPIOD_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN15))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN15))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_PIN0, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN6, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN7, 0))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOD_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOD_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOD_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOD_PIN14, 0) |          \
                                     PIN_AFIO_AF(GPIOD_PIN15, 0))

/*
 * GPIOE setup:
 *
 * PE0  - PIN0                      (input pullup).
 * PE1  - PIN1                      (input pullup).
 * PE2  - PIN2                      (input pullup).
 * PE3  - PIN3                      (input pullup).
 * PE4  - PIN4                      (input pullup).
 * PE5  - PIN5                      (input pullup).
 * PE6  - PIN6                      (input pullup).
 * PE7  - PIN7                      (input pullup).
 * PE8  - PIN8                      (input pullup).
 * PE9  - PIN9                      (input pullup).
 * PE10 - PIN10                     (input pullup).
 * PE11 - PIN11                     (input pullup).
 * PE12 - PIN12                     (input pullup).
 * PE13 - PIN13                     (input pullup).
 * PE14 - PIN14                     (input pullup).
 * PE15 - PIN15                     (input pullup).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_INPUT(GPIOE_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN15))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN15))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_2M(GPIOE_PIN0) |            \
                                     PIN_OSPEED_2M(GPIOE_PIN1) |            \
                                     PIN_OSPEED_2M(GPIOE_PIN2) |            \
                                     PIN_OSPEED_2M(GPIOE_PIN3) |            \
                                     PIN_OSPEED_2M(GPIOE_PIN4) |            \
                                     PIN_OSPEED_2M(GPIOE_PIN5) |            \
                                     PIN_OSPEED_2M(GPIOE_PIN6) |            \
                                     PIN_OSPEED_2M(GPIOE_PIN7) |            \
                                     PIN_OSPEED_2M(GPIOE_PIN8) |            \
                                     PIN_OSPEED_2M(GPIOE_PIN9) |            \
                                     PIN_OSPEED_2M(GPIOE_PIN10) |           \
                                     PIN_OSPEED_2M(GPIOE_PIN11) |           \
                                     PIN_OSPEED_2M(GPIOE_PIN12) |           \
                                     PIN_OSPEED_2M(GPIOE_PIN13) |           \
                                     PIN_OSPEED_2M(GPIOE_PIN14) |           \
                                     PIN_OSPEED_2M(GPIOE_PIN15))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_PULLUP(GPIOE_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN15))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN15))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_PIN0, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN6, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN7, 0))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOE_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOE_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOE_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOE_PIN14, 0) |          \
                                     PIN_AFIO_AF(GPIOE_PIN15, 0))

/*
 * GPIOF setup:
 *
 * PF0  - OSC_IN                    (input floating).
 * PF1  - OSC_OUT                   (input floating).
 * PF2  - PIN2                      (input pullup).
 * PF3  - PIN3                      (input pullup).
 * PF4  - PIN4                      (input pullup).
 * PF5  - PIN5                      (input pullup).
 * PF6  - PIN6                      (input pullup).
 * PF7  - PIN7                      (input pullup).
 * PF8  - PIN8                      (input pullup).
 * PF9  - PIN9                      (input pullup).
 * PF10 - PIN10                     (input pullup).
 * PF11 - PIN11                     (input pullup).
 * PF12 - PIN12                     (input pullup).
 * PF13 - PIN13                     (input pullup).
 * PF14 - PIN14                     (input pullup).
 * PF15 - PIN15                     (input pullup).
 */
#define VAL_GPIOF_MODER             (PIN_MODE_INPUT(GPIOF_OSC_IN) |         \
                                     PIN_MODE_INPUT(GPIOF_OSC_OUT) |        \
                                     PIN_MODE_INPUT(GPIOF_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN15))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_OSC_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_OSC_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN15))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_2M(GPIOF_OSC_IN) |          \
                                     PIN_OSPEED_2M(GPIOF_OSC_OUT) |         \
                                     PIN_OSPEED_2M(GPIOF_PIN2) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN3) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN4) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN5) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN6) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN7) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN8) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN9) |            \
                                     PIN_OSPEED_2M(GPIOF_PIN10) |           \
                                     PIN_OSPEED_2M(GPIOF_PIN11) |           \
                                     PIN_OSPEED_2M(GPIOF_PIN12) |           \
                                     PIN_OSPEED_2M(GPIOF_PIN13) |           \
                                     PIN_OSPEED_2M(GPIOF_PIN14) |           \
                                     PIN_OSPEED_2M(GPIOF_PIN15))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_FLOATING(GPIOF_OSC_IN) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_OSC_OUT) |    \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN15))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_OSC_IN) |           \
                                     PIN_ODR_HIGH(GPIOF_OSC_OUT) |          \
                                     PIN_ODR_HIGH(GPIOF_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN15))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_OSC_IN, 0) |         \
                                     PIN_AFIO_AF(GPIOF_OSC_OUT, 0) |        \
                                     PIN_AFIO_AF(GPIOF_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN6, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN7, 0))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN14, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN15, 0))


#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
