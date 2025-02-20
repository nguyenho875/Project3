## Project 3: Enhanced Car Alarm and Windshield Wiper System
Team Members: Nguyen Ho and Nicholas Komisky
<br/>
<br/>

### Description
Our project aims to implement and enhance the ignition alarm and windshield wiper functionalities of a driver education vehicle. 

#### Igniton Subsystem
The ignition subsystem is able to welcome the driver once the seat is occupied, then check if both seats are filled and seatbelts fastened to allow engine startup. Since Driver's Education vehicles require both driver and passenger seats to be occupied and both setabelts fastened, checking for these conditions before allowing the driver to start the engine can help enforce driving safety. In this system, seat occupanies are represented with buttons, and seatbelts are represented by slider switches. If the car is ignited when these conditions aren’t met, the system triggers an alarm and displays a message listing the violations. The serial terminal on the PC acts as the car’s display monitor, and a buzzer is used as the vehicle’s alarm that sounds when an error occurs. When all conditions are met, a green LED is turned on to indicate that the engine is ready for ignition, and the user should be able to turn on the engine without triggering any alarm or warning. A blue LED is used to indicate successful engine ignition. 

#### Windshield Wiper Subsystem
The system's wiper, represented by a servo motor, operates in four modes: HIGH (high speed); LOW (low speed); INT (intermittent or interval); and OFF. In the HIGH and LOW modes, the wiper opens and closes at an angle of approximately 67 degress repeatedly and without any noticeable hestiation, at speeds of 40 rpm for HIGH and 30 rpm for LOW. In the INT mode, after each rotation (wiper ramps up to 67 degrees and back to 0 degrees), there's a delay/hesitation period, selectable by the user. The duration of one cycle (one rotation + hestiation time) can range from short (3s), medium (6s) to long (8s). The wiper is stationary at starting/ending position, or 0 degrees, in OFF mode. Both wiper mode and int delay time selector mechanisms are represented by potentiometers. There's also an LDC display that shows both the mode and int delay time selected by the user. 

<br/>
### Design Alternatives
Teh servo motor choosen for this project to implement the windshield wiper is a positional motor. This was choosen over the rotational motor because this motor provides a set position of the motor depending on the duty cycle of the signal powering it, making its movement and the position of the windshield consistent, and easier to keep track of what position the motor is at. The alternative rotational motor allows controlling both the rotational direction and speed, but there's no defined/set 0 degree or beginning position to the motor, and for the same repeated positional movement requried in this project, it can be hard to keep track of where the motor is at a moment in time and to keep the behavior consistent, without knowing, for the example in this project, where 0 and 67 degrees is. It's still prossible to use a continuous rotational servo motor, but it may require the use of sensors/motor driver to control the movement of the motor and be able to keep track of its position. 


<br/>

### Testing results
- Ignition subsystem

| Specification | Test Result | Comment |
|----------|----------|----------|
| Welcome message for driver when driver is occupied. | Pass   | | |
| Enable engine start (i.e., light the green LED) while both seats are occupied and seatbelts fastened. | Pass   | | |
| Start the engine (i.e., light the blue LED, turn off Green) when ignition is enabled (green LED) and ignition button is pressed.  | Pass   | | |
| If any seat/seatbelt conditions are not satisfied when ignition button is pressed, sound alarm and print appropriate error message.  Allow multiple attempts  | Pass   | | | 
| Keep the engine running even if the driver/passenger should unfasten belt and exit the vehicle.| Pass | | |
| When the engine is running, stop the engine once the ignition button has been pushed and then released. | Pass | | |
