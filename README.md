# 📡 GPS Location Tracker

## Overview
This project implements a **GPS-based location tracking system** using the **TM4C123GH6PM microcontroller**.  
The system reads GPS data via UART, parses the location, displays it on an LCD, and identifies the nearest predefined location using the Haversine formula.

---

## 🎯 Features

- ✅ Real-time GPS coordinate display on a 16x2 LCD  
- ✅ Conversion of NMEA GPS data to **decimal degrees**  
- ✅ Calculation of distance using **Haversine formula**  
- ✅ Detection of nearest known location  
- ✅ **Buzzer notification** when approaching a new location  
- ✅ **Button interrupt** support for extra features  

---

## ⚙ Hardware Requirements

- TM4C123GH6PM LaunchPad Development Board
- GPS module (UART interface, connected to UART5)
- 16x2 LCD display (4-bit mode, Port B)
- Buzzer (Port D)
- Push buttons (Port F)

---

## 🔗 Pin Connections

### LCD Display (16x2, 4-bit Mode)

| LCD Pin  | TM4C123 Pin | Function                         |
|----------|-------------|----------------------------------|
| VSS      | GND         | Ground                          |
| VDD      | 3.3V        | Power supply                    |
| V0       | Potentiometer to GND | Contrast adjustment     |
| RS       | PB4         | Register Select                 |
| RW       | GND         | Read/Write (always Write)       |
| E        | PB5         | Enable                          |
| D4       | PB0         | Data bit 4                      |
| D5       | PB1         | Data bit 5                      |
| D6       | PB2         | Data bit 6                      |
| D7       | PB3         | Data bit 7                      |
| A        | 3.3V        | Backlight anode (+)             |
| K        | GND         | Backlight cathode (-)           |

### GPS Module (UART5)

| GPS Pin | TM4C123 Pin | Function                          |
|---------|-------------|-----------------------------------|
| VCC     | 3.3V        | Power supply                      |
| GND     | GND         | Ground                            |
| TX      | PE4         | GPS TX → MCU RX (UART5)           |
| RX      | PE5         | GPS RX ← MCU TX (UART5, optional) |

### Buzzer

| Buzzer Pin | TM4C123 Pin | Function      |
|------------|-------------|---------------|
| Positive    | PD0         | Buzzer control|
| Negative    | GND         | Ground        |

### Push Buttons (LaunchPad onboard)

| Button | Pin  | Notes                             |
|--------|------|-----------------------------------|
| SW2    | PF0  | Requires unlocking in code        |
| SW1    | PF4  | Direct use                        |

### Potentiometer for LCD Contrast

| Potentiometer End | Connection |
|-------------------|------------|
| One End           | 3.3V       |
| Other End         | GND        |
| Wiper             | LCD V0     |

---

## 💡 Software Architecture

| Module        | Description                                  |
|---------------|----------------------------------------------|
| `main.c`      | Application entry point and main loop       |
| `gps.c/h`     | GPS data parsing and calculations           |
| `lcd.c/h`     | LCD interface                               |
| `uart.c/h`    | UART communication                          |
| `gpio.c/h`    | GPIO setup for buzzer, buttons, LEDs        |
| `systick.c/h` | Timing and delay functions                  |

---

## 🔄 How It Works

1. System initializes all peripherals (UART, LCD, GPIO, etc.).
2. Reads GPS data via **UART5**.
3. Parses and converts NMEA data to **decimal degrees**.
4. Displays coordinates on LCD.
5. Calculates the distance to each known location.
6. Identifies and shows the nearest location.
7. Triggers buzzer if a new nearest location is detected.



