![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)
![Board](https://img.shields.io/badge/Board-Teensy%203%2E1-green)
![MCU](https://img.shields.io/badge/MCU-ARM%20Cortex--M4-orange)
![Framework](https://img.shields.io/badge/Framework-Arduino-blue)
![Last Commit](https://img.shields.io/github/last-commit/NenshaM/TeensySnippets)
# Code Snippets for Teensy 3.1

The [Teensy 3.1](https://www.pjrc.com/teensy/teensy31.html) is a compact, high-performance microcontroller development board based on a 32-bit ARM Cortex-M4 processor. It is well suited for embedded systems, real-time control, USB-based applications, and DIY electronics projects.

<div align="center">
  <img src="figures/teensy31_front_small_green.jpg" alt="Teensy 3.1 image" width="300"/>
  <br/>
  <i>Image source: <a href="https://www.pjrc.com/teensy/teensy31.html">www.pjrc.com</a></i>
</div>
  
## What You Need

### Hardware
- [Teensy 3.1](https://www.pjrc.com/teensy/teensy31.html)

### Software
- [Arduino IDE 2.x.x](https://www.arduino.cc/en/software/)
- [Teensyduino](https://www.pjrc.com/teensy/teensyduino.html)

## Repository Contents

This repository contains example code snippets demonstrating different USB-based functionalities using the Teensy 3.1.

### 1. Mouse Jiggler

Simulates small, random mouse movements to prevent a computer from entering sleep mode or activating a screen lock.

**Features:**
- Emulates a USB mouse device
- Randomized pointer movement

### 2. WiP: Reverse Shell Opener

Uses USB keyboard emulation to open a reverse shell on a target machine.

<!-- **Supported Environments:**
- Bash
- Netcat
- Python3
- PowerShell

**Functionality:**

* Emulates a USB keyboard
* Automatically types and executes payload commands
* Supports both Windows and Linux targets -->

## Disclaimer

These code snippets are provided for **educational and research purposes only**.
Use responsibly and only on systems you own or have explicit permission to test.



<!-- Front pinout of Teensy 3.1
![Teensy 3.1 front pinout](figures/teensy31_front_pinout.png)
Source: Image fromm www.pjrc.com

Back pinout of Teensy 3.1
![Teensy 3.1 back pinout](figures/teensy31_back_pinout.png)
Source: Image fromm www.pjrc.com 
