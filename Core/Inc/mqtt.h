#ifndef STM32_STD_MQTT_H
#define STM32_STD_MQTT_H

#include "main.h"

#define PRODUCT_KEY         "k0t9dhX9iwS"
#define DEVICE_NAME         "DHT11"
#define DEVICE_SECRET       "a17482225d183a76280cc434742ea0be"
#define DEVICE_SECRET_LEN   strlen(DEVICE_SECRET)
// #define SERVER_IP           "iot-06z00d8jolur3uo.mqtt.iothub.aliyuncs.com"
// #define SERVER_PORT         1883

#define  mqtt_tx_data(x)       u2_TxData(x)

extern u_char mqtt_tx_buff[7][400];
extern u_char* mqtt_tx_in_ptr;
extern u_char* mqtt_tx_out_ptr;
extern u_char* mqtt_tx_end_ptr;

void mqtt_data_init();
void mqtt_connect_message();
void mqtt_deal_tx_data(u_char *data, int size);

#endif //STM32_STD_MQTT_H
