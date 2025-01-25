# ESP/Arduino Controlled AC Remote Control

## Project Description

The greater vision for this project is to have an ESP network around the house all connected to each other allowing for smart home control of air conditioners from your phone. An ESP8266 will be present in each room with an air conditioner, and they will connect to a central ESP32 that hosts and controls the web app.

The current implementation of this project is to use a singular ESP32 in one room to control the air conditioner. The issue that arises is the power consumption of the ESP in regards to the battery life. However, the plan is to mitigate that by having an always-on device that handles all web requests while the ESP periodically checks the queued requests.

## Components Used

1. ESP32 Dev Board
2. IR Transmitter
3. IR Receiver
4. Lithium-Ion 3.7V 18650 Battery
5. TC4057A Type-C Lithium Battery Charger
6. Battery Holder 18650
7. LM2576T-3.3 Voltage Regulator 3.3V 3A
8. One of each capacitors: 100$\micro F$ and 10$\micro F$
9. Two 10$k \ohm$ resistors 