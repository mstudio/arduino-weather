#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>

void setup() {
  Serial.println("Setting up");
  // Initialize Serial port
  Serial.begin(9600);
  while (!Serial) continue;

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

  // const char* foo = doc["sensor"];

  // // Extract values
  // Serial.println(F("Response:"));
  // // Serial.println(doc["sensor"]);
  // Serial.println(foo);
  // Serial.println(doc["time"].as<long>());
  // Serial.println(doc["data"][0].as<float>(), 6);
  // Serial.println(doc["data"][1].as<float>(), 6);

  Serial.println("Hello");

  for (JsonObject data_item : doc["data"].as<JsonArray>()) {

    int data_item_hi = data_item["hi"]; // 999, 999, 999, 999
    int data_item_lo = data_item["lo"]; // 999, 999, 999, 999
    const char* data_item_forecast = data_item["forecast"]; // "Mostly Cloudy then Slight Chance Light Rain ..."

    Serial.println(data_item_hi);
    Serial.println(data_item_lo);
    Serial.println(data_item_forecast);

  }


  // Disconnect
  client.stop();
}

void loop() {
  // not used in this example
}