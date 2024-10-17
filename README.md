# Smart Home System

This is a smart home system that uses various sensors to monitor and control different aspects of a home. The system includes a light sensor, temperature sensor, smoke detector, and motion sensor.

## Demo
See a demo of this project on YouTube.
![IOT Coursework](https://github.com/user-attachments/assets/1969e769-2eb5-4d4e-bc0f-d3de1a3eaa54)

## Hardware
- Arduino UNO board
- DHT11 temperature and humidity sensor
- Light sensor
- PIR motion sensor
- Smoke sensor
- Buzzer
- LED lights (red, blue, white, yellow, and green)

### Wiring
The following pins were used for the components:

| Component | Pin |
|-----------|-----|
| Light sensor | A0 |
| Buzzer | 2 |
| Red LED | 5 |
| Blue LED | 6 |
| White LED | 7 |
| Smoke sensor | A5 |
| User button | 9 |
| Disable buzzer button | 3 |
| Yellow LED | 10 |
| Green LED | 11 |
| Temperature and humidity sensor | 4 |
| Motion sensor | 8 |

## Usage
The smart home system has the following features:

- UserState control: Allows the user to turn on or off the lights when they are at home or away from home.
- Buzzer control: Triggers the buzzer and turns on the yellow LED if the light sensor detects light when the user is away from home.
- Temperature control: Triggers the buzzer if the temperature is above a certain threshold.
- Motion control: Detects motion using the PIR sensor.

To use the system, connect all the components as described in the Wiring section and upload the code to the Arduino board. The system will automatically monitor the sensors and control the various components based on the conditions specified in the code.

## License
This project is licensed under the MIT License. Feel free to use and modify this code for your own projects.
