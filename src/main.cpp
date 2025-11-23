#include <Arduino.h>
#include <WiFi.h>
#include "MQTT_Cyan.h"
#include "Secrets.h"

void connect_to_wifi(const char *ssid, const char *password);

#define INPUT_PIN 4

MQTTCyan *client1 = new MQTTCyan(mqtt_config);
const char *dummy_msg =  "Hi from silly esp32 :3";

void setup() {
    delay(100);
    Serial.begin(115200);

    connect_to_wifi(project_ssid, passwd);

    //Setting up input pin for sensing
    pinMode(INPUT_PIN, INPUT);
}

void loop() {
    if(digitalRead(INPUT_PIN) == HIGH){
        client1->publish("esp32/topic", dummy_msg, 1, 0);
        delay(100);
    }
}

void connect_to_wifi(const char *ssid, const char *password){
    WiFi.begin(ssid, password);
    uint8_t retries = 0;

    for(uint8_t i = 0; i < 10U; i++){
        if(WiFi.status() == WL_CONNECTED)
            break;
        
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.printf("Successfully connected to %s\n", ssid);
    Serial.printf("IP address: %s", WiFi.localIP());
}