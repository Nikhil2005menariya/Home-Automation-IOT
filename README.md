# Home-Automation-IOT
🌐 IoT-Based Home Automation using ESP8266
This project demonstrates a simple IoT-based home automation system using the ESP8266 microcontroller. A web-based HTML control interface is embedded in the ESP8266 itself, allowing remote control of home devices such as:

🧑‍🌾 Agriculture Pump

🔥 Gas Regulator (with auto shut-off in case of fire)

💡 Light

🌬️ Fan

The system uses the L298N motor driver to control motors (pump and fan), a relay module for lights, and a servo motor for the gas regulator.

✅ Required Items
🧰 Hardware:
ESP8266 (NodeMCU or similar)

L298N Motor Driver Module

Servo Motor (for gas regulator)

Relay Module (1-channel)

Fan (DC motor)

Pump (DC motor)

Flame Sensor (to detect fire)

Jumper Wires

Breadboard or PCB

Power Supply (suitable for motors)

💻 Software:
Arduino IDE

ESP8266 Board Package (install from Board Manager)

Libraries (pre-installed or install via Library Manager):

ESP8266WiFi.h

Servo.h

🧠 Features
🖥️ Embedded HTML server on ESP8266

📱 Access control interface from any device on same Wi-Fi

💡 Manual control of light using relay

🌬️ Control fan and pump through motor driver

🔥 Fire safety feature: gas regulator turns off automatically when fire is detected

⚙️ Simple UI with toggle buttons for each device

📌 Pin Diagram

Component	Pin on ESP8266	Notes
Pump (Motor A)	D1 (GPIO5)	L298N IN1
Pump (Motor B)	D2 (GPIO4)	L298N IN2
Fan (Motor A)	D5 (GPIO14)	L298N IN3
Fan (Motor B)	D6 (GPIO12)	L298N IN4
Light (Relay)	D7 (GPIO13)	Active LOW Relay control
Servo (Regulator)	D4 (GPIO2)	PWM signal
Flame Sensor	D0 (GPIO16)	Digital pin
📝 Adjust motor driver EN pins based on whether you're using PWM control or not.

🌐 Web Interface Preview
The ESP8266 serves an HTML page that includes buttons like:

🔘 Toggle Pump

🔘 Toggle Fan

🔘 Toggle Light

🔘 Open/Close Gas Regulator

In case fire is detected by the flame sensor, the servo automatically rotates to turn off the regulator.

🚀 How to Upload
Install the ESP8266 board in Arduino IDE.

Connect ESP8266 to PC via USB.

Choose correct board and COM port.

Upload the code (to be added in a separate file).

Open Serial Monitor to get ESP IP address.

Open the IP in browser and start controlling devices!

