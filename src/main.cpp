#include <Arduino.h>
#include <WiFi.h>
#include "MQTT_Cyan.h"

const char *project_ssid = "Telekom-phLSrW";
const char *passwd = "xhd145f1auj";

void connect_to_wifi(const char *ssid, const char *password);

const esp_mqtt_client_config_t mqtt_config = {
        .host="49.13.17.225",
        .port=1883,
        .username="enginear",
        .password="RAM4Protogen"
    };

MQTTCyan *client1 = new MQTTCyan(mqtt_config);
const char *dummy_msg =  "Hi from silly esp32 :3";

void setup() {
    delay(100);
    Serial.begin(115200);

    connect_to_wifi(project_ssid, passwd);

    //Setting up pin D4 for sensing
    pinMode(4, OUTPUT);
}

void loop() {
    if(digitalRead(4) == HIGH){
        client1->publish("esp32/topic", dummy_msg, 1, 0);
        delay(100);
    }
}

void connect_to_wifi(const char *ssid, const char *password){
    WiFi.begin(ssid, password);

    if(WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.printf("Successfully connected to %s\n", ssid);
    Serial.printf("IP address: %s", WiFi.localIP());
}