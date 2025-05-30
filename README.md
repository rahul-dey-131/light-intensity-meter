# Light Intensity Meter with Visual Indicator

A compact Arduino-based system that reads ambient light levels using an LDR sensor, displays the measured illuminance (in lux) on a 16×2 LCD, and provides a color-coded visual indicator via an RGB LED. Ideal for both indoor and outdoor applications (by adjusting the fixed resistor for different measurement ranges).

📽 Have a look at how it works:

👉 Tinker of your own: https://www.tinkercad.com/things/4nvdTqW6fQn-light-intensity-measurement-using-ldr-sensor

---

## Features

* 📊 **Numeric Readout**: Real-time display of light intensity in lux on a 16×2 LCD.
* 🌈 **Color Feedback**: RGB LED transitions smoothly from red (dark) → green (moderate) → blue (bright).
* 🔧 **Outdoor Compatibility**: Change the fixed resistor (e.g., to 10–20 kΩ) in the LDR voltage divider to extend the range for sunlight.
* 💾 **Serial Logging**: Sends raw sensor values over Serial at 9600 baud for debugging or external logging.
* 🛠️ **Easy Calibration**: Map sensor output bands in `RGBController(...)` and adjust thresholds in code.

---

## Hardware Requirements

| Component            | Quantity                            | Notes                                                  |
| -------------------- | ----------------------------------- | ------------------------------------------------------ |
| Arduino Uno          | 1                                   | USB-powered development board                          |
| LDR (Photoresistor)  | 1                                   | Used in a voltage divider on A0                        |
| Resistors            | 1×4 kΩ (default), optional 10–20 kΩ | Fixed resistor for LDR divider; changeable for range ✔ |
| 16×2 LCD Display     | 1                                   | HD44780-compatible                                     |
| RGB LED              | 1                                   | Common-cathode, driven via PWM                         |
| Resistors            | 3×220 Ω                             | Resistors for Red, Green, and Blue Pins
| Breadboard & Jumpers | —                                   | For prototyping connections                            |

---

## Circuit Diagram

> ![image](https://github.com/user-attachments/assets/bedbb8b3-8334-40a5-a457-782154a01099)
> ![Circuit_Schematic](https://github.com/user-attachments/assets/a6eb9789-e2a9-4b23-a967-e58cf3b22e5d)

---

## Software Setup

1. Install the Arduino IDE (version 1.8+).
2. Open **File → Preferences** and add any additional board URLs if needed.
3. Connect your Arduino Uno via USB.

---

## Installation

1. Clone this repo:

   ```bash
   git clone https://github.com/yourusername/light-intensity-meter.git
   cd light-intensity-meter
   ```
2. Open `Simulator_Code.ino` in the Arduino IDE.
3. Verify and upload to the connected board.

---

## Usage

1. Power on the setup; the LCD will show:

   ```
   Light Intensity:
   0.00 Lux
   ```
2. Vary ambient light—observe the lux value update every 250 ms.
3. Watch the RGB LED change color according to brightness.
4. (Optional) Open the Serial Monitor (9600 baud) to view raw ADC values.

---

## Code Structure

* `setup()`
  Initializes Serial, configures outputs, and prints the LCD header.

* `loop()`
  Reads A0, calls `RGBController(value)`, updates the LCD via `luxConverter(value)`, and delays 250 ms.

* `RGBController(int value)`
  Maps raw ADC bands (0–1023) to RGB PWM outputs for intuitive color feedback.

* `float luxConverter(int ldrValue)`
  Converts the raw reading to a voltage, calculates LDR resistance, and applies an empirical formula to estimate lux.

---

## Customization

* **Thresholds & Colors**: Modify the ranges and PWM maps in `RGBController(...)` to adjust color transitions.
* **Resistor Value**: Swap the fixed resistor in hardware and update the formula in `luxConverter(...)` for different LDR characteristics.
* **Display Text**: Change the LCD messages in `setup()` and `loop()` to suit your project.
