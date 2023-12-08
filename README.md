# WPID: A Simple PID Library for VEX

WPID is a high level PID library built for the V5 system, written using the **VEXcode API**. WPID was built with ease of use in mind, and allows teams to quickly implement the library and start moving their robot autonomously. With functions like `Chassis::straight()` and `Mechanism::moveRelative()`, teams can quickly create an autonomous routine that takes advantage of a robust PID algorithm, and leverages many extra utilities to improve consistency.

Documentation for the library is in progress.

> Disclaimer: this will not win you worlds, nor is it intended to... but if it does let us know!
---

## Features

The WPID library has two unique classes that leverage a PID algorithm to achieve autonomous motion. Those classes are:

### Mechanism

The **Mechanism** class is essentially a wrapper class for `vex::motor_group`s that uses our custom PID algorithm and utility functions. **Mechanism** has other unique methods to change the behavior of the motors such as adding a maximum acceleration for ramping up the speed at the start of a `moveRelative()` call. You can also change attributes such as a timeout to limit the amount of time a motion takes, an offset value to offset constant error, and setting driver control limits.

### Chassis

The **Chassis** class utilizes **Mechanism** to control motor groups for the chassis. Because of this, **Chassis** inherits many of the same changeable attributes that **Mechanism** has. The **Chassis** class utilizes this functionality to allow accurate PID motion for **Tank** drive setups and **HDrive** setups. More chassis types may be added in the future.

### Example Implementation

Here is an example of using the library. We include the api, create a **Tank** chassis object, and a lift **Mechanism** object.

```c++
#include "wpid.h"

// motors setup
motor_group* driveLeft = new motor_group(...)
motor_group* driveRight = new motor_group(...)
motor_group* liftMotors = new motor_group(...)

// Chassis and Mechanism setup
Tank* chassis = new Tank(trackWidth, wheelRadius, &driveLeft, &driveRight);
Mechanism* lift = new Mechanism(&liftMotors, 2.0);

PID drivePID = PID(1, .25, .02);
PID liftPID  = PID(2, .15, .03);

int main(){
  // set the PID constants
  chassis->setStraightPID(drivePID);
  fourBar->setPID(liftPID);

  // drive the chassis forward 24 inches at 50% speed
  chassis->straight(24.0, 50);

  // move the lift to 90 degrees @ 20% speed
  fourBar->moveRelative(90.0, 20);
}
```

---

## Installation

The required files for installation are located in the releases tab. A dedicated tutorial on how to install the library is [located here](https://wpidlib.github.io/WPID-Library-Docs/tutorial/tutorials.html).

> In short: Add the header files to your include folder, and the archive file to your project folder.
Then add the name of the archive file to the LIB flag in your mkenv.env file.

---

## Who are we?

We are a group of students from Worcester Polytechnic Institute pursuing degrees in Computer Science and Robotics Engineering. As part of our Major Qualifying Project, we decided to develop a simple and effective VEX library for teams to improve their autonomous period. The target audience for this project is intended for beginner to intermediate teams, as a large-scale website hosting tutorials and documentation will supplement this library. Thank you for checking us out, we hope that our materials will accelerate your robotics journey!

### Authors

- Brianna Sahagian
- Jair Meza
- Austin Rebello

## Acknowledgments

- George Heineman, MQP Advisor
