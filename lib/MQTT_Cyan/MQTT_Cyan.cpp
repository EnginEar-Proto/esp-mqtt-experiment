#include "MQTT_Cyan.h"

#ifndef MQTT_Cyan_CPP

#define MQTT_Cyan_CPP

void MQTTCyan::publish(const char *topic, const char *msg, int qos, int retain){
    esp_mqtt_client_publish(this->client_handler, topic, msg, 0, qos, retain);
}

#endif