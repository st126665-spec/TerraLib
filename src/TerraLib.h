/*
 TerraLib.h - A simple client for MQTT (from-scratch clone of PubSubClient API).
*/

#ifndef TerraLib_h
#define TerraLib_h

#include <Arduino.h>
#include "IPAddress.h"
#include "Client.h"
#include "Stream.h"

#define TERRAMQTT_VERSION_3_1 3
#define TERRAMQTT_VERSION_3_1_1 4

#ifndef TERRAMQTT_VERSION
#define TERRAMQTT_VERSION TERRAMQTT_VERSION_3_1_1
#endif

#ifndef TERRAMQTT_MAX_PACKET_SIZE
#define TERRAMQTT_MAX_PACKET_SIZE 256
#endif

#ifndef TERRAMQTT_KEEPALIVE
#define TERRAMQTT_KEEPALIVE 15
#endif

#ifndef TERRAMQTT_SOCKET_TIMEOUT
#define TERRAMQTT_SOCKET_TIMEOUT 15
#endif

#define TERRAMQTT_CONNECTION_TIMEOUT -4
#define TERRAMQTT_CONNECTION_LOST -3
#define TERRAMQTT_CONNECT_FAILED -2
#define TERRAMQTT_DISCONNECTED -1
#define TERRAMQTT_CONNECTED 0
#define TERRAMQTT_CONNECT_BAD_PROTOCOL 1
#define TERRAMQTT_CONNECT_BAD_CLIENT_ID 2
#define TERRAMQTT_CONNECT_UNAVAILABLE 3
#define TERRAMQTT_CONNECT_BAD_CREDENTIALS 4
#define TERRAMQTT_CONNECT_UNAUTHORIZED 5

#define TERRAMQTTCONNECT 1 << 4
#define TERRAMQTTCONNACK 2 << 4
#define TERRAMQTTPUBLISH 3 << 4
#define TERRAMQTTPUBACK 4 << 4
#define TERRAMQTTPUBREC 5 << 4
#define TERRAMQTTPUBREL 6 << 4
#define TERRAMQTTPUBCOMP 7 << 4
#define TERRAMQTTSUBSCRIBE 8 << 4
#define TERRAMQTTSUBACK 9 << 4
#define TERRAMQTTUNSUBSCRIBE 10 << 4
#define TERRAMQTTUNSUBACK 11 << 4
#define TERRAMQTTPINGREQ 12 << 4
#define TERRAMQTTPINGRESP 13 << 4
#define TERRAMQTTDISCONNECT 14 << 4
#define TERRAMQTTReserved 15 << 4

#define TERRAMQTTQOS0 (0 << 1)
#define TERRAMQTTQOS1 (1 << 1)
#define TERRAMQTTQOS2 (2 << 1)

#define TERRAMQTT_MAX_HEADER_SIZE 5

#if defined(ESP8266) || defined(ESP32)
#include <functional>
#define TERRAMQTT_CALLBACK_SIGNATURE std::function<void(char *, uint8_t *, unsigned int)> callback
#else
#define TERRAMQTT_CALLBACK_SIGNATURE void (*callback)(char *, uint8_t *, unsigned int)
#endif

#define MYCHECK_STRING_LENGTH(l, s)                              \
    if (l + 2 + strnlen(s, this->bufferSize) > this->bufferSize) \
    {                                                            \
        _client->stop();                                         \
        return false;                                            \
    }

class TerraLib : public Print
{
private:
    Client *_client;
    uint8_t *buffer;
    uint16_t bufferSize;
    uint16_t keepAlive;
    uint16_t socketTimeout;
    uint16_t nextMsgId;
    unsigned long lastOutActivity;
    unsigned long lastInActivity;
    bool pingOutstanding;
    TERRAMQTT_CALLBACK_SIGNATURE;
    uint32_t readPacket(uint8_t *);
    boolean readByte(uint8_t *result);
    boolean readByte(uint8_t *result, uint16_t *index);
    boolean write(uint8_t header, uint8_t *buf, uint16_t length);
    uint16_t writeString(const char *string, uint8_t *buf, uint16_t pos);
    size_t buildHeader(uint8_t header, uint8_t *buf, uint16_t length);
    IPAddress ip;
    const char *domain;
    uint16_t port;
    Stream *stream;
    int _state;

public:
    TerraLib();
    TerraLib(Client &client);
    TerraLib(IPAddress, uint16_t, Client &client);
    TerraLib(IPAddress, uint16_t, Client &client, Stream &);
    TerraLib(IPAddress, uint16_t, TERRAMQTT_CALLBACK_SIGNATURE, Client &client);
    TerraLib(IPAddress, uint16_t, TERRAMQTT_CALLBACK_SIGNATURE, Client &client, Stream &);
    TerraLib(uint8_t *, uint16_t, Client &client);
    TerraLib(uint8_t *, uint16_t, Client &client, Stream &);
    TerraLib(uint8_t *, uint16_t, TERRAMQTT_CALLBACK_SIGNATURE, Client &client);
    TerraLib(uint8_t *, uint16_t, TERRAMQTT_CALLBACK_SIGNATURE, Client &client, Stream &);
    TerraLib(const char *, uint16_t, Client &client);
    TerraLib(const char *, uint16_t, Client &client, Stream &);
    TerraLib(const char *, uint16_t, TERRAMQTT_CALLBACK_SIGNATURE, Client &client);
    TerraLib(const char *, uint16_t, TERRAMQTT_CALLBACK_SIGNATURE, Client &client, Stream &);

    ~TerraLib();

    TerraLib &setServer(IPAddress ip, uint16_t port);
    TerraLib &setServer(uint8_t *ip, uint16_t port);
    TerraLib &setServer(const char *domain, uint16_t port);
    TerraLib &setCallback(TERRAMQTT_CALLBACK_SIGNATURE);
    TerraLib &setClient(Client &client);
    TerraLib &setStream(Stream &stream);
    TerraLib &setKeepAlive(uint16_t keepAlive);
    TerraLib &setSocketTimeout(uint16_t timeout);

    boolean setBufferSize(uint16_t size);
    uint16_t getBufferSize();

    boolean connect(const char *id);
    boolean connect(const char *id, const char *user, const char *pass);
    boolean connect(const char *id, const char *willTopic, uint8_t willQos, boolean willRetain, const char *willMessage);
    boolean connect(const char *id, const char *user, const char *pass, const char *willTopic, uint8_t willQos, boolean willRetain, const char *willMessage);
    boolean connect(const char *id, const char *user, const char *pass, const char *willTopic, uint8_t willQos, boolean willRetain, const char *willMessage, boolean cleanSession);
    void disconnect();
    boolean link(const char *id) { return connect(id); }
    boolean unlink()
    {
        disconnect();
        return true;
    }
    boolean give(const char *topic, const char *payload) { return publish(topic, payload); }
    boolean give(const char *topic, const char *payload, boolean retained) { return publish(topic, payload, retained); }
    boolean give(const char *topic, const uint8_t *payload, unsigned int plength) { return publish(topic, payload, plength); }
    boolean give(const char *topic, const uint8_t *payload, unsigned int plength, boolean retained) { return publish(topic, payload, plength, retained); }
    boolean publish(const char *topic, const char *payload);
    boolean publish(const char *topic, const char *payload, boolean retained);
    boolean publish(const char *topic, const uint8_t *payload, unsigned int plength);
    boolean publish(const char *topic, const uint8_t *payload, unsigned int plength, boolean retained);
    boolean publish_P(const char *topic, const char *payload, boolean retained);
    boolean publish_P(const char *topic, const uint8_t *payload, unsigned int plength, boolean retained);
    boolean beginPublish(const char *topic, unsigned int plength, boolean retained);
    int endPublish();
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *buffer, size_t size);
    boolean get(const char *topic) { return subscribe(topic); }
    boolean get(const char *topic, uint8_t qos) { return subscribe(topic, qos); }
    boolean unget(const char *topic) { return unsubscribe(topic); }
    boolean subscribe(const char *topic);
    boolean subscribe(const char *topic, uint8_t qos);
    boolean unsubscribe(const char *topic);
    boolean loop();
    boolean connected();
    int state();
};

#endif
