#include <AccelStepper.h>
#include <ArduinoJson.h>
#include <Ethernet.h>
#include <ezButton.h>
#include <SPI.h>

#define FULLSTEP 4
#define MAX_POSITION 2038

ezButton limitSwitch(40);
AccelStepper stepper(FULLSTEP, 8, 10, 9, 11);

bool isStopped = false;
bool isResetting = true;
int currentState = 0; // 0 - loading, 1 displaying

void setup() {
  Serial.println("Setting up");
  // Initialize Serial port
  Serial.begin(9600);
  while (!Serial) continue;

  limitSwitch.setDebounceTime(50); // set debounce time to 50 milliseconds

  stepper.setMaxSpeed(1000);   // set the maximum speed
  stepper.setAcceleration(1000); // set acceleration
  stepper.setSpeed(1000);         // set initial speed
  stepper.setCurrentPosition(0); // set position
  stepper.moveTo(MAX_POSITION);
  Serial.println("done");
}

void loop() {
  limitSwitch.loop(); // MUST call the loop() function first
  Serial.println(stepper.distanceToGo());

  // When limit switch is pressed, the stepper is reset.
  if(limitSwitch.isPressed()) {
    // isStopped = true;
    isResetting = false;
    delay(500);
    stepper.setCurrentPosition(0);
    stepper.moveTo(-1580); // <-- determine position here for forecast, etc.
    // isStopped = false;
  }

  // if (isStopped == false && isResetting) {
  if (isResetting) {
    //  Serial.println("Not Stopped");
    if (stepper.distanceToGo() == 0) { // loop the motor in case it reaches max before resetting
      stepper.setCurrentPosition(0);   // reset position to 0
      stepper.moveTo(MAX_POSITION);    // move the motor to maximum position again
    }
    //stepper.run();
  } else {
    // without calling stepper.run() function, motor stops immediately
    // NOTE: stepper.stop() function does NOT stops motor immediately
    // Serial.println(F("The stepper motor is STOPPED"));
    //stepper.run();

    
  }
  stepper.run();
}