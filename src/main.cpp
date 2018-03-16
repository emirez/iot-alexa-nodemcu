#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"

#define WIFI_SSID "belkin.36ef"
#define WIFI_PASS "34e966fb"
#define SERIAL_BAUDRATE 9600

fauxmoESP fauxmo;

void wifiSetup() {

    WiFi.mode(WIFI_STA);
    Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();

    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

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

void setup() {
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println("FauxMo demo sketch");
    Serial.println("After connection, ask Alexa/Echo to 'turn <devicename> on' or 'off'");
    pinMode(D3, OUTPUT);

    wifiSetup();

    // Fauxmo
    fauxmo.addDevice("relay");
    //fauxmo.addDevice("pixels");
    fauxmo.onMessage(callback);
}

void loop() {
    fauxmo.handle();
}
