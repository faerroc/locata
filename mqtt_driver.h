#pragma once

#include <stdio.h>
#include <cstring>
#include <MQTTClient.h>

#include "location.h"

#define ADDRESS     "tcp://127.0.0.1:1883"
#define CLIENTID    "fabricio2c"
#define QOS         1
#define TIMEOUT     10000L

#define TOPIC_SUB   "locata/config"
#define TOPIC_PUB   "locata/info"

class MqttDriver
{
public:
    MqttDriver();

    static void delivered(void *context, MQTTClient_deliveryToken dt);
    static int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message);
    static void connlost(void *context, char *cause);
    static int initialize(void);
    static void close(void);
    static int  publish(Location value);

private: 
};
