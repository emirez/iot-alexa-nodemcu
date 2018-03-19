#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"

#define WIFI_SSID "SSIDname"
#define WIFI_PASS "PASSWORD"
#define SERIAL_BAUDRATE 9600

//
fauxmoESP fauxmo;

void wifiSetup() {
    //Set WiFi module to STA module, connect and print on serial monitor
    WiFi.mode(WIFI_STA);
    Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    
    // Wait until see whether it is connected
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();
    
    // Print out the SSID name and IP address
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

    // Callback function to switch the LED on/off
    // According to voice command, state varies from true to false
void callback(uint8_t device_id, const char * device_name, bool state) {
    Serial.print("Device ");
    Serial.print(device_name);
    Serial.print(" state: ");
    if (state) {
        Serial.println("ON");
        digitalWrite(D3, HIGH);
    } else {
        Serial.println("OFF");
        digitalWrite(D3, LOW);
    }
}
    // Setup function calls WiFi and callback functions.
    // Fauxmo library emulates Belkin WeMo devices for using them with Alexa Echo
void setup() {
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println("FauxMo demo sketch");
    Serial.println("After connection, ask Alexa/Echo to 'turn <devicename> on' or 'off'");
    pinMode(D3, OUTPUT);

    wifiSetup();

    // Device is added and the name is chosen as "MeinLicht"
    fauxmo.addDevice("MeinLicht");
    fauxmo.onMessage(callback);
}

void loop() {
    fauxmo.handle();
}
