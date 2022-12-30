// Include the AccelStepper Library
#include <AccelStepper.h>

// Define step constant
#define FULLSTEP 4

// Creates an instance
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper myStepper(FULLSTEP, 8, 10, 9, 11);

void setup() {
  Serial.begin(9600);
  Serial.println("Setup:");
	// set the maximum speed, acceleration factor,
	// initial speed and the target position
	myStepper.setMaxSpeed(1000.0);
	myStepper.setAcceleration(50.0);
	myStepper.setSpeed(100);
	myStepper.moveTo(2038);
}

void loop() {
  Serial.println("dtg:");
  Serial.println(myStepper.distanceToGo());
	// Change direction once the motor reaches target position
	if (myStepper.distanceToGo() == 0) 
		myStepper.moveTo(-myStepper.currentPosition());

	// Move the motor one step
	myStepper.run();

  
}




// //Arduino Code - Rotary Encoder w push button

// // Need to install ButttonFever in the Library Manager of the IDE.
// #include <BfButton.h>
// #include <Stepper.h>

// #define STEPS 2038 
// // create an instance of the stepper class, specifying
// // the number of steps of the motor and the pins it's
// // attached to
// Stepper stepper(STEPS, 8, 9, 10, 11);

// // the previous stepper reading from the analog input
// int previous = 0;


// int DT=4; //GPIO #4-DT on encoder (Output B)
// int CLK=5; //GPIO #5-CLK on encoder (Output A)
// int counter = 0;
// int angle = 0; 
// int aState;
// int aLastState;  



// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
//   Serial.println(angle);
//   pinMode(CLK,INPUT_PULLUP);
//   pinMode(DT,INPUT_PULLUP);
//   aLastState = digitalRead(CLK);
//   stepper.setSpeed(50);
//   stepper.step(-2038);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
  
//   aState = digitalRead(CLK);

//   //Encoder rotation tracking
//   if (aState != aLastState){     
//      previous = counter;
//      if (digitalRead(DT) != aState) { 
//        counter ++;
//        angle ++;
//      }
//      else {
//        counter--;
//        angle --;
//      }
//      if (counter >=100 ) {
//        counter =100;
//      }
//      if (counter <=-100 ) {
//        counter =-100;
//      }
//     //  int delta = counter - previous;
//     //  Serial.print(delta); 
//     //  Serial.println(" delta");
//     //  stepper.step(delta * 100);
//   }
//   aLastState = aState;
// }