This project utilizes an ESP8266 microcontroller along with a light sensor and an I2C LCD display to decode Morse code signals. The decoded messages are then translated into the Latin alphabet and displayed on the LCD screen in real time.

Features->
Light Sensor Integration: Employs a light sensor to capture Morse code flashes.
Morse to Text Translation: Transforms Morse code signals into readable text.
I2C LCD Display Output: Displays the translated text on an LCD screen for clear visibility.
Real-Time Decoding: Instantaneously interprets and displays Morse code messages as they are received.

Components:
ESP8266 microcontroller
Light sensor (LDR)
I2C LCD display
Breadboard and jumper wires
Appropriate power supply for ESP8266

Setup and Installation->
Assemble the Hardware:
Connect the light sensor and LCD display to the ESP8266 according to the schematic provided. Ensure the I2C pins (SDA and SCL) are connected to the corresponding I2C interface on the LCD.
Adjust the light sensor sensitivity using the blue trimmer to match your environment. The sensor should only detect Morse code light signals without background interference.

Configure the LCD Display:
If the LCD screen appears blank, adjust the contrast using the blue adjustment screw on the back of the LCD to improve visibility.

Flash the ESP8266:
Upload the provided Arduino sketch to the ESP8266 using the Arduino IDE to handle the decoding and display logic.

Power the Device:
Connect the ESP8266 to a suitable power source such as a USB power adapter or battery pack.

Hardware Schema:
![image](https://github.com/hilmiserttas/MorseCodeReceiver/assets/170796718/da41678c-cdd7-4e58-94bc-d63614568020)

