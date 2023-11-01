# WPID: A Simple PID Library for VEX

WPID is a high level PID library built for the V5 system, written using the VEXcode API. WPID was built with ease of use in mind, and allows teams to quickly implement the library and start moving their robot autonomously. With functions like `Chassis::forward()` and `Mechanism::setPosition()`, teams can quickly create an autonomous routine that takes advantage of a robust PID algorithm, and leverages many extra utilities to improve consistency.

Documentation for the library is in progress.

---

## Features
The WPID library has two unique classes. 

### Mechanism
The Mechanism class is essentially a replacement of `vex::motor_group`s that uses our custom PID algorithm and utility functions. Mechanism has other unique methods to change the behavior of the motors such as adding a maximum acceleration for ramping up the speed at the start of a `setPosition()` call. You can also change attributes such as a timeout to limit the amount of time a motion takes, an offset value to offset constant error, and debug logging. 

### Chassis
The Chassis class utilizes Mechanism to control motor groups for the chassis. Because of this, Chassis inherits many of the same changeable attributes that Mechanism has such as timeouts, ramp speed and offsets. The Chassis class utilizes this functionality to allow accurate PID motion in the forward and backward axis, as well as on the spot turns for Tank drive, and also diagonal and sideways motion for HDrive chassis.

There are two types of Chassis models avaliable. Tank (aka Skidsteer), and HDrive.

### Example Implementation
Here is an example of using the library. We include the api, create a Tank chassis object, and a lift Mechanism object. 
```c++
// Chassis
#include "wpid.h"

motor_group* driveLeft = new motor_group(...)
motor_group* driveRight = new motor_group(...)
Tank* chassis = new Chassis(
    trackWidth, wheelRadius, &driveLeft, &driveRight
  );

// Lift
motor_group* liftMotors = new motor_group(...)
Mechanism* lift = new Mechanism(&liftMotors, 1.0);

int main(){
  // move the lift 90 degrees @ 20% speed
  fourBar->setPosition(90.0, 20);

  // drive the chassis forward 24 inches at 25% speed
  chassis->straight(24.0, 25);
}
```
---

## Installing - WIP
A dedicated tutorial on installing and using the library will be hosted on our website.

1. Copy over all `.h` files associated with the library into the `include` folder
2. Copy over the `.a` archive file that you created in the `build` folder of the library's project (provided if someone else made it)
3. In `vex/mkenv` add the `.a` file's name to the `LIB` variable

If you include our library it should look like this:

`vex/mkenv.mk` line `105`:

![Alt text](image-1.png)

The .a file and header files (WPID folder) in the project:

![Alt text](image.png)

---

## Who are we?
We are a group of students from Worcester Polytechnic Institute pursuing degrees in Computer Science and Robotics Engineering. As part of our Major Qualifying Project, we decided to develop a simple and effective VEX library for teams to improve their autonomous period. The target audience for this project is intended for beginner to intermediate teams, as a large-scale website hosting tutorials and documentation will supplement this library. Thank you for checking us out, we hope that our materials will accelerate your robotics journey!

#### Authors:
- Brianna Sahagian
- Austin Rebello
- Jair Meza

## Acknowledgments
- George Heineman, MQP Advisor

#### This README, as well as every other supporting document and the library as a whole, is still a work in progress. Completion is expected by March, 2024.

### Features to come
- Finish unit conversion class
- Integrate Mechanism into Chassis
- Async motion (might happen with Mechanism integration)
- Debug logging
- Pace modes
- External Encoders for Mechanism (and by extension all of chassis)
- PID Filtering for Derrivative
- Engage function
- Test library importing