Welcome to Owlhat.
==================

Owlhat is a mutli sensors hat with GSM/GPRS modem connectivity. It can work alone, connected to a PC with an USB cable.
It's also a hat for raspberry pi. It's pi B+/2 hat format compatible (56x65mm). It uses a wide range of sensors for multiples paramaters acquire :

- two gas sensor socket with 5V heater with low/mid impedance
- LSM303D : accelerometer / magentometer
- MPL3115A2 : absolute pressure sensor (barometer/altimeter)
- Si7006 : temperature / relative moisture sensor
- SIM800C GSM/GPRS module to offer a lost cost M2M communication interface (by SMS for example).
- external serial input for laser particle sensor.
- external ADC input,
- few 3.3V free GPIO.

It allow to attach a pi camero directly onto the PCB.

You'll need to install openocd (0.8.0 + patch at least to support SWD) on your pi to download/debug STM32 present onboard and arm-none-eabi-gcc to compile the firmware.

You'll find in this deposit datasheets and application notes, some pieces of firmware and more in the future.

This board is a first release. Some bugs are present in this release, into schematics, pcb, etc. A new version is forecasted with correction of bugs and a more sophisticated and accurate gas sensor stage to be compatible with complex and/or high impedance sensors like MQ131 (ozone) or TGS4161 (carbon dioxide).


It is deliver AS it is, without any kind of garantee.

You can also follow owlhat google+ collection : https://plus.google.com/collection/Ex4dRE

Have fun.

Frederic Pierson
