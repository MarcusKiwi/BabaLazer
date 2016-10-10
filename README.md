# BabaLazer

AVR lazer toy for cats. Adjustable game speed and boundaries using LCD screen.

Unfortunately I don't have any schematic files for this yet.

# Bits

* ATmega328p
* 2x SG90 servos
* 5V lazer
* PCD8544/Nokia5110/Nokia3310 LCD
* 3x Microswitch
* LM7805 Regulator
* LM1117 Regulator

# Instructions

Download this project and [AVR-Libs](https://github.com/MarcusKiwi/AVR-Libs). Recreate this folder structure:

```
base
├───AVR-Libs
│   └───project files
└───BabaLazer
    └───project files
```

Run `make` from inside the CompRemote folder to build the HEX file.

Run `make install` to build it flash it to an AVR. Default programmer type is usbasp. This can be changed in the file `base/AVR-Libs/makefile`.