//#include <Arduino_JSON.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <time.h>
#include "pin_config.h"
#include <Adafruit_GFX.h>

#define WAIT 1000

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5,0,0)
#error  "The current version is not supported for the time being, please use a version below Arduino ESP32 3.0"
#endif

// Initialize TFT display
TFT_eSPI tft = TFT_eSPI();

// WiFi credentials
const char* ssid = "IT hurts when IP";
const char* password = "yourPWD";

// OpenWeatherMap API key
String openWeatherMapApiKey = "yourAPI";
String city = "yourCity";
String countryCode = "yourCountryCode";
String jsonBuffer;

// Variables to store weather data
String temperatureCelcius;
String pressure;
String humidity;
String windSpeed;
String sunrise;
String sunset;

// Update interval for weather data (milliseconds)
unsigned long timerDelay = 60000;
unsigned long lastTime = 0;
unsigned long targetTime = 0;

// RGB color values for dynamic background
byte red = 31;
byte green = 0;
byte blue = 0;
byte state = 0;
unsigned int colour = red << 11;

// Timer for dynamic background
uint32_t runing = 0;

// Function to send HTTP GET request and receive response
String httpGETRequest(const char* serverName) {
    WiFiClient client;
    HTTPClient http;
    
    http.begin(client, serverName);
  
    int httpResponseCode = http.GET();
  
    String payload = "{}"; 
  
    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    
    http.end();

    return payload;
}

// Function to format and print time
void printFormattedTime(long epochTime, String& formattedTime) {
  struct tm *timeinfo = gmtime(&epochTime);
  char buffer[20];
  strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
  Serial.println(buffer);
  formattedTime = String(buffer);
}

void setup(void)
{
    Serial.begin(115200);

    // Set pin mode for TFT power
    pinMode(PIN_POWER_ON, OUTPUT);
    digitalWrite(PIN_POWER_ON, HIGH);

    // Initialize time
    configTime(3600, 0, "pool.ntp.org");

    // Initialize TFT display
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    
    // Set font and cursor position for greeting
    tft.setFreeFont(&FreeSansBold12pt7b);
    tft.setCursor(80,30);
    tft.setTextColor(TFT_RED);

    tft.println("Hello World!");

    targetTime = millis() + 1000;

    // Connect to WiFi
    WiFi.begin(ssid, password);

    delay(1000);
    tft.setTextColor(TFT_SKYBLUE);
    Serial.println("Connecting");
    tft.println("Connecting...");

    // Wait for WiFi connection
    while(WiFi.status() != WL_CONNECTED) {
        delay(2000);
        tft.setTextColor(TFT_RED);
        tft.println("(> ^_^)>");
        delay(2000);
        tft.setTextColor(TFT_SKYBLUE);
        tft.println("                                <(^_^ <)");
    }

    // Display connection status
    tft.println("Connected!");
    Serial.println("");
    tft.fillScreen(TFT_BLACK);
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    // Check if it's time to update weather data
    if ((millis() - targetTime) > timerDelay) {
        if (WiFi.status() == WL_CONNECTED) {
            // Construct API URL
            String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey;

            // Send HTTP GET request
            jsonBuffer = httpGETRequest(serverPath.c_str());
            Serial.println(jsonBuffer);

            // Parse JSON response
            DynamicJsonDocument doc(1024);
            DeserializationError error = deserializeJson(doc, jsonBuffer);

            if (error) {
                Serial.println("Parsing input failed!");
                return;
            }
            // Extract weather data
            JsonVariant myObject = doc.as<JsonVariant>();

            Serial.println(myObject.as<String>());

            // Extract data
            Serial.print("Temperature: ");
            float tempKelvin = myObject["main"]["temp"].as<float>();
            float tempCelsius = tempKelvin - 273.15;

            temperatureCelcius = "Temperature: " + String(tempCelsius) + "C";

            Serial.println(temperatureCelcius);

            Serial.print("Pressure: ");
            Serial.println(myObject["main"]["pressure"].as<float>());

            pressure = "Pressure: " + String(myObject["main"]["pressure"].as<float>()) + "hPa";
            
            Serial.print("Humidity: ");
            Serial.println(myObject["main"]["humidity"].as<float>());

            humidity = "Humidity: " + String(myObject["main"]["humidity"].as<float>()) + "%";
            
            Serial.print("Wind Speed: ");
            Serial.println(myObject["wind"]["speed"].as<float>());

            windSpeed = "Wind Speed: " + String(myObject["wind"]["speed"].as<float>()) + "m/s";

            Serial.print("Sunrise: ");
            long sunriseEpoch = myObject["sys"]["sunrise"].as<long>();
            String formattedTime;
            printFormattedTime(sunriseEpoch, formattedTime);
            
            sunrise = "Sunrise: " + formattedTime;
            
            Serial.print("Sunset: ");
            long sunsetEpock = myObject["sys"]["sunset"].as<long>();
            String formattedTime2;
            printFormattedTime(sunsetEpock, formattedTime2);

            sunset = "Sunset: " + formattedTime2;

        }
        else {
            Serial.println("WiFi Disconnected");
            tft.fillScreen(TFT_BLACK);
            tft.println("WiFi Disconnected");
        }
        targetTime = millis() + timerDelay;
    }
    // Update dynamic background
    if (millis() > runing) {
        Serial.print("Current running ");
        Serial.print(millis());
        Serial.println(" millis");
        runing = millis() + 1000;

        for (int i = 0; i < tft.width(); i++) {
            tft.drawFastVLine(i, 0, tft.height(), colour);
            switch (state) {
                case 0:
                    green += 2;
                    if (green == 64) {
                        green = 63;
                        state = 1;
                    }
                    break;
                case 1:
                    red--;
                    if (red == 255) {
                        red = 0;
                        state = 2;
                    }
                    break;
                case 2:
                    blue++;
                    if (blue == 32) {
                        blue = 31;
                        state = 3;
                    }
                    break;
                case 3:
                    green -= 2;
                    if (green == 255) {
                        green = 0;
                        state = 4;
                    }
                    break;
                case 4:
                    red++;
                    if (red == 32) {
                        red = 31;
                        state = 5;
                    }
                    break;
                case 5:
                    blue--;
                    if (blue == 255) {
                        blue = 0;
                        state = 0;
                    }
                    break;
            }
            colour = red << 11 | green << 5 | blue;
        }
        // Display weather data on TFT screen
        tft.setTextColor(TFT_BLACK, TFT_BLACK);
        tft.setCursor(35, 30);
        tft.println(temperatureCelcius);

        tft.setCursor(35, 55);
        tft.println(pressure);

        tft.setCursor(35, 80);
        tft.println(humidity);

        tft.setCursor(35, 105);
        tft.println(windSpeed);

        tft.setCursor(35, 130);
        tft.println(sunrise);

        tft.setCursor(35, 155);
        tft.println(sunset);
    }
    delay(10000); // Delay to avoid flooding the server with requests
}