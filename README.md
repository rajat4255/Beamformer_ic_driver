# Beamformer_ic_driver
 ADAR1000 Ic Dummy linux driver code

#IC Selected
 ADAR1000 – Analog Devices Beamformer IC

# Driver Overview
This project implements a simplified firmware-style Linux driver
demonstrating beamformer control logic without real hardware access.

# Driver Structure
- beamformer_driver.c/h
- Abstracted SPI write functions
- Clear init/deinit lifecycle
- Dynamic allocation used per-channel configuration storage

# Device Tree
A minimal SPI device node is provided for integration reference.
- Spi0 controller used to communicate with ic.
- Ic SPI chip-select number (CS0)
- Set spi maximum clock frequency 1 MHz

# User-Space Tool
`beamctl is a CLI application that directly calls driver APIs,
 By commands we can set per channel phase gain and beam angle from user space.
