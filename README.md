# ** EV Charging Station Simulation **

## *** Description: *** This project simulates an electric vehicle (EV) charging station using LEDs and buttons. It mimics a real charging process where LEDs indicate the charging status, and the buttons allow you to start, stop, or reset the sequence.


## *** 🛠️ Components: ***
### Breadboard
### 6x 100-ohm Resistors
### 4x Blue LEDs (to indicate charging progress)
### 1x RGB LED (represents the station status)
### 2x Buttons (for start and stop/reset controls)
### 2x 10K-ohm Resistors (for button debouncing)
### Jumper Wires (for connections)


## *** 📖 Project Functionality ***
### Station Free (RGB LED Green): Initially, the RGB LED is green, indicating that the station is free.

### Start Charging (RGB LED Red): When the start button is pressed, the RGB LED turns red, signaling that the station is occupied. The charging sequence begins, with the blue LEDs lighting up progressively. Each LED represents 25% of the charging process.

### Charging Progress: The 4 blue LEDs light up sequentially, blinking for 3 seconds before staying solid. The next LED then blinks, and so on, until all LEDs are solid, indicating the charging is complete.

### Stop Charging: If the stop button is pressed and held for at least 1 second during charging, the sequence stops early. All LEDs will blink 3 times to indicate the end, and the RGB LED will turn green, showing the station is free again.

### Completion: Once charging is complete, the 4 blue LEDs blink 3 times at a slower rate, then turn off. The RGB LED turns green to show the station is free.



## *** ⚙️ Circuit Schematic ***

### ![Mighty Crift](https://github.com/user-attachments/assets/0bad7b16-3226-492f-8633-c373a60ed6aa)

### This schematic shows the connections between the components on the breadboard, ensuring correct functionality.


## *** 🎬 Media *** ##


## *** 🖼️ Simulation Picture: ***
### ![T1Robotica](https://github.com/user-attachments/assets/a0850e66-e9b2-43ab-9263-0e5cdf3e595a)

## *** 📹 Demo Video: ***

### https://github.com/user-attachments/assets/01506d6d-f92c-45d5-90ea-39bc0e491f9d



