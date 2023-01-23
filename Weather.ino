/**
 
 TODO: connect a switch which changes the "currentDay" number from 0 to 1. 
 See if that automatically updates the position of the gauges.

**/


#include <AccelStepper.h>
#include <ArduinoJson.h>
#include <Ethernet.h>
#include <ezButton.h>
#include <SPI.h>
#include <string.h>

#define FULLSTEP 4
#define MAX_POSITION 2038

ezButton limitSwitch(40);
AccelStepper stepper(FULLSTEP, 8, 10, 9, 11);

bool isStopped = false;
bool isResetting = true;

typedef struct  {
  char* forecast;
  int hi;
  int lo;
} dayStruct;

dayStruct days[2];
int currentDay = 0;



void setup() {
  Serial.println("Setting up");
  // Initialize Serial port
  Serial.begin(9600);
  while (!Serial) continue;

  limitSwitch.setDebounceTime(50); // set debounce time to 50 milliseconds

  stepper.setMaxSpeed(400);   // set the maximum speed
  stepper.setAcceleration(250); // set acceleration
  stepper.setSpeed(400);         // set initial speed
  stepper.setCurrentPosition(0); // set position
  stepper.moveTo(MAX_POSITION);
  Serial.println("Initializing Ethernet connection...");

  // Initialize Ethernet library
  byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
  if (!Ethernet.begin(mac)) {
    Serial.println(F("Failed to configure Ethernet"));
    return;
  }
  delay(1000);

  Serial.println(F("Connecting..."));

  // Connect to HTTP server
  EthernetClient client;
  client.setTimeout(10000);
  if (!client.connect("d2boyfgp9fovjg.cloudfront.net", 80)) {
    Serial.println(F("Connection failed"));
    return;
  }

  Serial.println(F("Connected!"));

  // Send HTTP request
  client.println(F("GET /simple-forecast?office=ALY&gridX=52&gridY=15 HTTP/1.0"));
  client.println(F("Host: d2boyfgp9fovjg.cloudfront.net"));
  client.println(F("Connection: close"));
  if (client.println() == 0) {
    Serial.println(F("Failed to send request"));
    client.stop();
    return;
  }

  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
    Serial.print(F("Unexpected response: "));
    Serial.println(status);
    client.stop();
    return;
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)) {
    Serial.println(F("Invalid response"));
    client.stop();
    return;
  }

  // Allocate the JSON document
  // Use arduinojson.org/v6/assistant to compute the capacity.
  DynamicJsonDocument doc(1024);

  // Parse JSON object
  DeserializationError error = deserializeJson(doc, client);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    client.stop();
    return;
  }

  Serial.println("Hello");

  int i = 0;
  for (JsonObject data_item : doc["data"].as<JsonArray>()) {

    int data_item_hi = data_item["hi"]; // 999, 999, 999, 999
    int data_item_lo = data_item["lo"]; // 999, 999, 999, 999
    const char* data_item_forecast = data_item["forecast"]; // "Mostly Cloudy then Slight Chance Light Rain ..."

    days[i].hi = data_item_hi;
    days[i].lo = data_item_lo;
    days[i].forecast = data_item_forecast;

    i = i + 1;
  }
  
  // Disconnect
  client.stop();  
}

void loop() {
  limitSwitch.loop(); // MUST call the loop() function first
  // Serial.println(stepper.distanceToGo());

  // When limit switch is pressed, the stepper is reset.
  if(limitSwitch.isPressed()) {
    // isStopped = true;
    isResetting = false;
    delay(500);
    stepper.setCurrentPosition(0);

    dayStruct d = days[currentDay];
    Serial.println("go to");
    Serial.println(d.forecast);

    int step = 1880; // error
    const char* f = d.forecast;

    if (!strcmp(f, "snow")) {
      step = 180;
    }
    if (!strcmp(f, "sleet")) { 
      step = 413;
    }
    if (!strcmp(f, "wind")) {
      step = 647;
    }
    if (!strcmp(f, "rain")){
      step = 880;
    }
    if (!strcmp(f, "cloud")) {
      step = 1113;
    }
    if (!strcmp(f, "part-sun")) {
      step = 1347;
    }
    if (!strcmp(f, "sun")) {
      step = 1580;
    }

    Serial.println("moving to");
    Serial.println(step);
    Serial.println("day1_forecast");
    Serial.println(day1_forecast);
    Serial.println(f);


    stepper.moveTo(-step); // <-- determine position here for forecast, etc.
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