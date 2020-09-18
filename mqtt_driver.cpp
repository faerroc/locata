#include "mqtt_driver.h"

MQTTClient client;

volatile MQTTClient_deliveryToken deliveredtoken;

MqttDriver::MqttDriver()
{}

void MqttDriver::delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int MqttDriver::msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    int i;
    char* payloadptr;

    printf("RX  %s\t", topicName);

    payloadptr = (char*) message->payload;
    for(i=0; i<message->payloadlen; i++)
    {
        putchar(*payloadptr++);
    }

    putchar('\n');

    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);

    return 1;
}

void MqttDriver::connlost(void *context, char *cause)
{
    printf("\nConnection lost -> cause: %s\n", cause);
}

int MqttDriver::initialize(void)
{
    int rc = 0;

    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession      = 1;

    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        return -1;      
    }
    
    printf("Subscribing to topic %s\nfor client %s using QoS%d\n\nPress Q<Enter> to quit\n\n", TOPIC_SUB, CLIENTID, QOS);
    MQTTClient_subscribe(client, TOPIC_SUB, QOS);
    
    return 0;
}

void MqttDriver::close(void)
{
    MQTTClient_disconnect(client, TIMEOUT);
    MQTTClient_destroy(&client);
}

int MqttDriver::publish(Location value)
{
    int rc = 0;
    MQTTClient_deliveryToken token;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;

    pubmsg.payload    = (char *) value.getLocationBuffer().c_str();
    pubmsg.payloadlen = (int)strlen(value.getLocationBuffer().c_str());
    pubmsg.qos        = QOS;
    pubmsg.retained   = 0;

    if ((rc = MQTTClient_publishMessage(client, TOPIC_PUB, &pubmsg, &token)) != MQTTCLIENT_SUCCESS)
    {
         printf("Failed to publish message, return code %d\n", rc);
         return -1;
    }    

    printf("Waiting for tx message ...\n");
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token); 

    return rc;
}
