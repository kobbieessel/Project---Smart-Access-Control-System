# Smart Access Control System

A smart IoT-based access control solution using **Arduino** and **Raspberry Pi** to monitor and manage door entry securely and remotely. This system uses computer vision, servo-controlled door movement, LED indicators, a buzzer, and a Telegram bot for real-time alerts and remote access control.

---

## Project Goal

The goal of this project is to enhance physical access security by:

- Detecting visitor presence via a push button.
- Capturing the visitor’s image using a camera.
- Sending the image to a designated Telegram chat for human verification.
- Allowing a remote user to grant or deny access using `/open` or `/deny` Telegram commands.
- Automatically actuating a servo to open or close the door based on the decision.

---

## Components Required

### Hardware

| Component                               | Description                                   |
| --------------------------------------- | --------------------------------------------- |
| Arduino Uno                             | Controls button, servo, LEDs, buzzer          |
| Raspberry Pi                            | Captures images and communicates via Telegram |
| Servo Motor                             | Mechanically opens/closes the door            |
| Push Button                             | Triggered by visitor                          |
| Buzzer                                  | Provides audio feedback                       |
| RGB LEDs (Red, Green, Blue)             | Indicates access status                       |
| I2C LCD Display (16x2)                  | Displays user messages                        |
| 4 Resistor (3x330 ohms and 1k resistor) | Current control                       |
| Jumper Wires                            | For circuit connections                       |
| Breadboard / PCB                        | For assembling the circuit                    |
| USB Cable                               | For Arduino–Raspberry Pi serial communication |

### Software

- [Arduino IDE](https://www.arduino.cc/en/software)
- Python 3
- OpenCV (`cv2`)
- `python-telegram-bot` library
- Telegram bot with bot token and chat ID
- Serial communication via PySerial

---

## How It Works

1. **Standby Mode:**

   - LCD prompts visitor to press the button.
   - Blue LED stays ON indicating system readiness.

2. **Button Press Detected:**

   - Arduino sends signal to Raspberry Pi.
   - Raspberry Pi captures a photo using a webcam.
   - Image is sent to a predefined Telegram group or user.

3. **Remote Decision via Telegram:**
   - Remote user replies `/open` or `/deny`.
   - Raspberry Pi sends the command to Arduino.
   - Arduino:
     - Opens door with servo if allowed.
     - Flashes green/red LEDs and buzzer accordingly.
     - Displays status message on the LCD.

---

## Features

- Real-time visitor photo capture and remote access control
- Simple Telegram interface for authorized users
- Modular design (easily extendable with RFID, facial recognition, etc.)
- Visual and audio feedback using LEDs and buzzer
- Local LCD display for user prompts and system status

---

## Project Structure

```plaintext
.
├── arduino_code.ino           # Arduino sketch controlling hardware logic
├── raspberry_pi_script.py     # Python script running on Raspberry Pi
├── images/                    # Folder to store captured images
├── .telegram_bot_token        # Stores Telegram bot token (keep private)
├── README.md                  # Project documentation
```
