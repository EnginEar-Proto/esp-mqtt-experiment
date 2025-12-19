#include <Arduino.h>
#include <WiFi.h>
#include "Secrets.h"
#include <ArduinoOTA.h>

bool connect_to_wifi(const char *ssid, const char *password);

#define INPUT_PIN 4
#define MQTT_TOPIC "esp32/topic"

const char *dummy_msg =  "Hi from silly esp32 :3";
esp_mqtt_client_handle_t handler = esp_mqtt_client_init(&mqtt_config);

void setup() {
    delay(100);
    Serial.begin(115200);

    const bool is_connected = connect_to_wifi(project_ssid, passwd);

    Serial.print(is_connected);

    if(is_connected){
        Serial.println("Connected to WiFi");
        esp_mqtt_client_start(handler);
        ArduinoOTA.begin();
    }

    //Setting up input pin for sensing
    pinMode(INPUT_PIN, INPUT);
}

void loop() {
    ArduinoOTA.handle();

    if(digitalRead(INPUT_PIN) == HIGH){
        esp_mqtt_client_publish(handler, MQTT_TOPIC, dummy_msg, 0, 1, 0);
        delay(100);
    }
    //Serial.println("Paws at you, hi :3");
    delay(5000);

}

bool connect_to_wifi(const char *ssid, const char *password){
    WiFi.begin(ssid, password);
    uint8_t retries = 0;

    for(uint8_t i = 0; i < 10U; i++){
        if(WiFi.status() == WL_CONNECTED)
            return true;
        
        Serial.print(".");
        delay(500);
    }

    return false;
}