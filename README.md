This project is an **Arduino Uno-based Obstacle Avoidance Robot** that uses an ultrasonic sensor, a servo motor, and an L298N-based motor driver shield (Adafruit Motor Shield library with four DC motors) to autonomously navigate around obstacles. The code combines standard motor control logic with ultrasonic distance measurement and servo-based scanning to make navigation decisions.

### Features

- **Ultrasonic obstacle detection** using the A0 (Echo) and A1 (Trig) pins to measure distance in front of the robot.
- **Servo motor scanning**: The servo (connected to pin 10) rotates the ultrasonic sensor to scan both left and right for open paths.
- **Four-wheel drive** (using AF_DCMotor library, ports 1-4) for robust motion: supports forward, backward, left turn, right turn, and stop maneuvers.
- **Autonomous navigation** logic:
  - Moves forward until an obstacle (≤ 30 cm) is detected.
  - Stops, then reverses briefly.
  - Scans left and right, measures distance on both sides, and turns toward the direction with greater clearance.
  - If distances on both sides are equal, defaults to left turn.
  - Continues moving forward if no obstacles are detected.

### Pin/Hardware Mapping

- **Echo:** A0  
- **Trig:** A1  
- **Servo PWM:** 10  
- **Motor Driver:** AFMotor Shield (connects to four DC motors on ports 1-4)

### Key Functions

- `ultrasonic()`: Measures distance using the ultrasonic sensor.
- `forward()`, `backward()`, `left()`, `right()`, `Stop()`: Motor control routines.
- `leftsee()`, `rightsee()`: Rotates servo, measures left/right distance.
- Main loop: Calls `Obstacle()` function, which runs the avoidance logic continuously.

### Example Usage Flow

1. Robot moves forward until an obstacle is detected (within 30 cm).
2. It stops, reverses, and scans both left and right.
3. Turns and moves in the direction with the largest open space.
4. Repeats process to dynamically avoid all obstacles in its path.

### Library Dependencies

- `Servo.h`
- `AFMotor.h` (for Adafruit Motor Shield)

***

This information can be directly pasted into the readme file to describe the function and hardware setup of the Obstacle Avoidance Robot project.[1]

[1](https://ppl-ai-file-upload.s3.amazonaws.com/web/direct-files/attachments/91329900/7d683cd7-a95f-43a2-9428-da2079a70aa5/ObstacleAvoidance.ino)
