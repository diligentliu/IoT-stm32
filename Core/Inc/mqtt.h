#ifndef STM32_STD_MQTT_H
#define STM32_STD_MQTT_H

#include "main.h"

#define PRODUCT_KEY         "k0t9dhX9iwS"
#define DEVICE_NAME         "DHT11"
#define DEVICE_SECRET       "a17482225d183a76280cc434742ea0be"
#define DEVICE_SECRET_LEN   strlen(DEVICE_SECRET)

void mqtt_data_init();
void mqtt_connect_message();


#endif //STM32_STD_MQTT_H
