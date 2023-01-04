// #include <Stepper.h>

// // change this to the number of steps on your motor
// #define STEPS 64 // 5.625 degrees

// // create an instance of the stepper class, specifying
// // the number of steps of the motor and the pins it's
// // attached to
// Stepper stepper(STEPS, 8, 9, 10, 11);

// // the previous reading from the analog input
// int previous = 0;

// void setup() {
//   // set the speed of the motor to 30 RPMs
//   stepper.setSpeed(30);
// }

// void loop() {
//   // get the sensor value
//   int val = analogRead(0);

//   // move a number of steps equal to the change in the
//   // sensor reading
//   stepper.step(val - previous);

//   // remember the previous value of the sensor
//   previous = val;
// }



// #include <AccelStepper.h>

// // Define step constant
// #define FULLSTEP 4

// // Creates an instance
// // Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
// AccelStepper myStepper(FULLSTEP, 8, 10, 9, 11);

// void setup() {
//   Serial.begin(9600);
//   Serial.println("Setup:");
// 	// set the maximum speed, acceleration factor,
// 	// initial speed and the target position
// 	myStepper.setMaxSpeed(1000.0);
// 	myStepper.setAcceleration(50.0);
// 	myStepper.setSpeed(100);
// 	myStepper.moveTo(2038);
// }

// void loop() {
//   Serial.println("dtg:");
//   Serial.println(myStepper.distanceToGo());
// 	// Change direction once the motor reaches target position
// 	if (myStepper.distanceToGo() == 0) 
// 		myStepper.moveTo(-myStepper.currentPosition());

// 	// Move the motor one step
// 	myStepper.run();

  
// }

