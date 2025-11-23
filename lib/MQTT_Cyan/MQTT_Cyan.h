#include <mqtt_client.h>

#ifndef MQTT_Cyan_H

#define MQTT_Cyan_H

class MQTTCyan{
    esp_mqtt_client_handle_t client_handler;
public:
    MQTTCyan() {}
    MQTTCyan(const esp_mqtt_client_config_t& config): client_handler(esp_mqtt_client_init(&config)) {
        esp_mqtt_client_start(client_handler);
    }
    void publish(const char *topic, const char *msg, int qos, int retain);
};

#endif