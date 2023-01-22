// #include <ArduinoJson.h>
// #include <Ethernet.h>
// #include <SPI.h>
// #include <ezButton.h>

// ezButton limitSwitch(40); 

// void setup() {
//   Serial.println("Setting up");
//   // Initialize Serial port
//   Serial.begin(9600);
//   while (!Serial) continue;

//   limitSwitch.setDebounceTime(50); // set debounce time to 50 milliseconds

//   Serial.println("done");
// }

// void loop() {
//   limitSwitch.loop(); // MUST call the loop() function first

//   if(limitSwitch.isPressed())
//     Serial.println("The limit switch: UNTOUCHED -> TOUCHED");

//   if(limitSwitch.isReleased())
//     Serial.println("The limit switch: TOUCHED -> UNTOUCHED");

//   int state = limitSwitch.getState();
//   if(state == HIGH)
//     Serial.println("The limit switch: UNTOUCHED");
//   else
//     Serial.println("The limit switch: TOUCHED");
// }