#include <Preferences.h>
#include "WiFi.h"
#include <WiFiManager.h>
#include "time.h"

#define wifiReset 5
#define daysReset 4

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -18000;
const int   daylightOffset_sec = 3600;

Preferences credentials;
Preferences times;

String ssid;
String password;

 

void setup() {
    Serial.begin(115200);

    WiFiManager wm;

    Serial.println();
  
    credentials.begin("credentials", false);
 
    ssid = credentials.getString("ssid", ""); 
    password = credentials.getString("password", "");

    if (ssid == "" || password == ""){
        Serial.println("No values saved for ssid or password");
        Serial.println("Press Wifi Reset To add wifi credentials");
    }
    else {
        // Connect to Wi-Fi
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);
        Serial.print("Connecting to WiFi ..");
        while (WiFi.status() != WL_CONNECTED) {
            Serial.print('.');
            delay(500);
        }
        Serial.println(WiFi.localIP());  
        addDay();
        updateScreen();
    }
}

void addDay() {
    //init and get the time
    times.begin("times", false);
    resetTime = times.getString("resetTime", "");
    days = times.getString("days", "");
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    if((&timeinfo, "%H:%M") == resetTime) {
        newDay = days++;
        times.putString("days", newDay);
    }
}

void updateScreen() {
    // E-ink screen stuff.
}

void loop() {
    //Won't Run
}
