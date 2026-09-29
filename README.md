# 🕹️ Arduino Simon Says Game

An interactive, hardware-based clone of the classic electronic memory game built using an Arduino. The game challenges players to memorize and accurately reproduce ever-increasing random sequences of flashing lights and acoustic tones.

---

##  How It Works
1. **The Challenge:** The game boots up, plays a welcome melody, flashes a random LED, and plays its corresponding tone.
2. **The Turn:** The player must press the matching hardware button. 
3. **The Progression:** Every time the player successfully copies the sequence, the game appends one new random step to the pattern and plays it back from the start.
4. **Game Over:** If the player presses the wrong button, a distinct "Game Over" frequency plays, all four LEDs flash in unison, and the level resets back to 1.

---

##  Hardware Components
* **Microcontroller:** Arduino Uno R3 (or compatible)
* **Visuals:** 4x LEDs (Red, Green, Blue, Yellow recommended)
* **Resistors:** 4x 220Ω or 330Ω current-limiting resistors (for LEDs)
* **Inputs:** 4x Pushbuttons (with 10kΩ pull-down resistors)
* **Audio:** 1x Piezo Buzzer
* **Misc:** Breadboard & Jumper wires

---

##  Pin Configuration
To streamline wiring, this project features an **active software-ground** trick for the buzzer. By setting Pin 4 to a continuous `LOW` state via code, you can plug the buzzer directly across Pins 3 and 4 without needing an extra line to the hardware Ground (`GND`) rail.

| Component | Arduino Pin | Connection Type | Description |
| :--- | :--- | :--- | :--- |
| **Buzzer (+)** | **Pin 3** | Digital Output | Sends the audio frequency signals (`tone()`) |
| **Buzzer (-)** | **Pin 4** | Digital Output | Driven `LOW` in software to act as a Ground channel |
| **LED 1** | **Pin 2** | Digital Output | Controls the first LED indicator |
| **LED 2** | **Pin 5** | Digital Output | Controls the second LED indicator |
| **LED 3** | **Pin 12** | Digital Output | Controls the third LED indicator |
| **LED 4** | **Pin 13** | Digital Output | Controls the fourth LED indicator |
| **Button 1** | **Pin 6** | Digital Input | Triggers input for LED 1 |
| **Button 2** | **Pin 7** | Digital Input | Triggers input for LED 2 |
| **Button 3** | **Pin 9** | Digital Input | Triggers input for LED 3 |
| **Button 4** | **Pin 10** | Digital Input | Triggers input for LED 4 |

---

##  Key Software Features
* **True Random Initialization:** Uses a floating, unconnected analog pin (`A0`) to sample ambient atmospheric noise. This seeds the random number generator, ensuring a completely unique sequence every single time the board resets.
* **Input State Locking:** Uses a blocking state loop (`while(digitalRead(...) == HIGH)`) that pauses execution until the player completely lifts their finger from the button. This cleanly eliminates double-triggering or accidental inputs.
* **Scalable Arrays:** Configured out-of-the-box to handle complex memory sequences up to 100 levels deep.

---

## License
This project is open-source and licensed under the **MIT License**. 

You are completely free to:
* **Use** this code for personal, educational, or commercial projects.
* **Modify** the circuits, pins, or features to build your own custom version.
* **Distribute** and share it with anyone.

See the [LICENSE](LICENSE) file for more details, or just take the code and start building! Contributions, tweaks, and optimizations are always welcome.
