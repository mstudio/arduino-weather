# Arduino Weather
Weather reporting via National Weather Service API, displayed with dials run by stepper motors on limit switches.

## Data source: National Weather Service

https://www.weather.gov/documentation/services-web-api

The API for this project uses Lambda to clean simplify the response and Cloudfront to create an HTTP endpoint. The Arduino Ethernet lib does not have TLS/HTTPS support.

The API exists at another repository on github here: https://github.com/mstudio/arduino-weather-api