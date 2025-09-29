#include <AFMotor.h>

// M1 and M2 share the MOTOR12_* PWM group; M3 and M4 share MOTOR34_*.
AF_DCMotor m1(1, MOTOR12_64KHZ);
AF_DCMotor m2(2, MOTOR12_64KHZ);
AF_DCMotor m3(3, MOTOR34_64KHZ);
AF_DCMotor m4(4, MOTOR34_64KHZ);

// Half-speed relative to prior 200 → use ~100 (0–255 range) Your Ma Li (Horse Power)
const uint8_t SPEED_M1 = 100;  //M1 Front Right 
const uint8_t SPEED_M2 = 100;  //M2 Front LEft
const uint8_t SPEED_M3 = 100;  //M3 Rear Left
const uint8_t SPEED_M4 = 100; //M4 Rear Right

void setup() {
  // Set PWM duty (speed) per motor
  m1.setSpeed(SPEED_M1);
  m2.setSpeed(SPEED_M2);
  m3.setSpeed(SPEED_M3);
  m4.setSpeed(SPEED_M4);

  // Ensure all motors are stopped at start
  stopAll();
}

void loop() {
  static uint8_t cycles = 0;

  if (cycles < 2) {
    // Forward phase: all four together
    runAll(FORWARD);
    delay(2000);

    // Stop/coast
    stopAll();
    delay(1000);

    // Backward phase: all four together
    runAll(BACKWARD);
    delay(2000);

    // Stop/coast
    stopAll();
    delay(1000);

    cycles++;
  } else {
    // Permanently stop after two cycles
    stopAll();
    // Idle forever until reset/reupload
    while (true) {
      delay(1000);
    }
  }
}

void runAll(uint8_t dir) {
  m1.run(dir);
  m2.run(dir);
  m3.run(dir);
  m4.run(dir);
}

void stopAll() {
  // RELEASE = coast stop for DC motors on AFMotor v1
  m1.run(RELEASE);
  m2.run(RELEASE);
  m3.run(RELEASE);
  m4.run(RELEASE);
}
