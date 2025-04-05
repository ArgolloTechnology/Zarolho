# Robo Eyes OLED Animation (FluxGarage + Light Sensor + Sound)

This project is based on the [FluxGarage Robo Eyes](https://github.com/FluxGarage/FluxGarage-RoboEyes) library and enhances it with:
- A light sensor that reacts to brightness changes.
- A buzzer to simulate robot emotions with sounds.
- Interaction logic for sleeping, waking up, and getting annoyed depending on the ambient light.
- Status print on Serial Monitor and GPIO input handling.

## 🧠 Features

- OLED display animation using the SSD1306 driver.
- Eyes close slowly in darkness and eventually fall asleep.
- Annoyed reaction with sounds and squinting eyes in bright environments.
- Wake-up animation and sound when brightness increases.
- Custom sound effects using a buzzer.
- Two GPIO inputs for physical interaction (e.g., laying down or standing up).

## 🛠️ Hardware Required

- Arduino Nano R3 or compatible.
- OLED 128x64 display with SSD1306 or SH1106 driver (I2C).
- Light sensor (e.g., LDR with a resistor).
- Piezo buzzer.
- Jumper wires.
- Breadboard.

## 📦 Library Dependencies

- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)
- [FluxGarage RoboEyes](https://github.com/FluxGarage/FluxGarage-RoboEyes)

Install these through the Arduino Library Manager or manually.

## 📷 Screenshots

Coming soon...

## 🚀 Getting Started

1. Connect the components as described in the hardware section.
2. Upload the `main.ino` sketch to your Arduino.
3. Open the Serial Monitor to check GPIO input states.
4. Use a flashlight or cover the light sensor to test the interactions.

## 📁 File Structure
📂 ZarolloBot/ <br>
├ 📂 Rivinbot/ <br>
| └── Rivinbot.ino <br>
├ 📄 README.md <br>
└ 📄 LICENSE<br>


## 📝 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## 📣 Credits

- [FluxGarage](https://www.fluxgarage.com) for the RoboEyes library and concept.
- Inspired by expressive robot projects and robotic pets.


