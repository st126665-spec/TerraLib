/*
  TerraLib.cpp - A simple client for MQTT (from-scratch clone of PubSubClient API).
*/

#include "TerraLib.h"
#include "Arduino.h"

TerraLib::TerraLib()
{
    this->_state = TERRAMQTT_DISCONNECTED;
    this->_client = NULL;
    this->stream = NULL;
    setCallback(NULL);
    this->bufferSize = 0;
    setBufferSize(TERRAMQTT_MAX_PACKET_SIZE);
    setKeepAlive(TERRAMQTT_KEEPALIVE);
    setSocketTimeout(TERRAMQTT_SOCKET_TIMEOUT);
}

TerraLib::TerraLib(Client &client)
{
    this->_state = TERRAMQTT_DISCONNECTED;
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(TERRAMQTT_MAX_PACKET_SIZE);
    setKeepAlive(TERRAMQTT_KEEPALIVE);
    setSocketTimeout(TERRAMQTT_SOCKET_TIMEOUT);
}

TerraLib::TerraLib(IPAddress addr, uint16_t port, Client &client)
{
    this->_state = TERRAMQTT_DISCONNECTED;
    setServer(addr, port);
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(TERRAMQTT_MAX_PACKET_SIZE);
    setKeepAlive(TERRAMQTT_KEEPALIVE);
    setSocketTimeout(TERRAMQTT_SOCKET_TIMEOUT);
}

TerraLib::TerraLib(IPAddress addr, uint16_t port, Client &client, Stream &stream)
{
    this->_state = TERRAMQTT_DISCONNECTED;
    setServer(addr, port);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(TERRAMQTT_MAX_PACKET_SIZE);
    setKeepAlive(TERRAMQTT_KEEPALIVE);
    setSocketTimeout(TERRAMQTT_SOCKET_TIMEOUT);
}

TerraLib::TerraLib(IPAddress addr, uint16_t port, TERRAMQTT_CALLBACK_SIGNATURE, Client &client)
{
    this->_state = TERRAMQTT_DISCONNECTED;
    setServer(addr, port);
    setCallback(callback);
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(TERRAMQTT_MAX_PACKET_SIZE);
    setKeepAlive(TERRAMQTT_KEEPALIVE);
    setSocketTimeout(TERRAMQTT_SOCKET_TIMEOUT);
}

TerraLib::TerraLib(IPAddress addr, uint16_t port, TERRAMQTT_CALLBACK_SIGNATURE, Client &client, Stream &stream)
{
    this->_state = TERRAMQTT_DISCONNECTED;
    setServer(addr, port);
    setCallback(callback);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(TERRAMQTT_MAX_PACKET_SIZE);
    setKeepAlive(TERRAMQTT_KEEPALIVE);
    setSocketTimeout(TERRAMQTT_SOCKET_TIMEOUT);
}

TerraLib::TerraLib(uint8_t *ip, uint16_t port, Client &client)
{
    this->_state = TERRAMQTT_DISCONNECTED;
    setServer(ip, port);
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(TERRAMQTT_MAX_PACKET_SIZE);
    setKeepAlive(TERRAMQTT_KEEPALIVE);
    setSocketTimeout(TERRAMQTT_SOCKET_TIMEOUT);
}

TerraLib::TerraLib(uint8_t *ip, uint16_t port, Client &client, Stream &stream)
{
    this->_state = TERRAMQTT_DISCONNECTED;
    setServer(ip, port);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(TERRAMQTT_MAX_PACKET_SIZE);
    setKeepAlive(TERRAMQTT_KEEPALIVE);
    setSocketTimeout(TERRAMQTT_SOCKET_TIMEOUT);
}

TerraLib::TerraLib(uint8_t *ip, uint16_t port, TERRAMQTT_CALLBACK_SIGNATURE, Client &client)
{
    this->_state = TERRAMQTT_DISCONNECTED;
    setServer(ip, port);
    setCallback(callback);
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(TERRAMQTT_MAX_PACKET_SIZE);
    setKeepAlive(TERRAMQTT_KEEPALIVE);
    setSocketTimeout(TERRAMQTT_SOCKET_TIMEOUT);
}

TerraLib::TerraLib(uint8_t *ip, uint16_t port, TERRAMQTT_CALLBACK_SIGNATURE, Client &client, Stream &stream)
{
    this->_state = TERRAMQTT_DISCONNECTED;
    setServer(ip, port);
    setCallback(callback);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(TERRAMQTT_MAX_PACKET_SIZE);
    setKeepAlive(TERRAMQTT_KEEPALIVE);
    setSocketTimeout(TERRAMQTT_SOCKET_TIMEOUT);
}

TerraLib::TerraLib(const char *domain, uint16_t port, Client &client)
{
    this->_state = TERRAMQTT_DISCONNECTED;
    setServer(domain, port);
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(TERRAMQTT_MAX_PACKET_SIZE);
    setKeepAlive(TERRAMQTT_KEEPALIVE);
    setSocketTimeout(TERRAMQTT_SOCKET_TIMEOUT);
}

TerraLib::TerraLib(const char *domain, uint16_t port, Client &client, Stream &stream)
{
    this->_state = TERRAMQTT_DISCONNECTED;
    setServer(domain, port);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(TERRAMQTT_MAX_PACKET_SIZE);
    setKeepAlive(TERRAMQTT_KEEPALIVE);
    setSocketTimeout(TERRAMQTT_SOCKET_TIMEOUT);
}

TerraLib::TerraLib(const char *domain, uint16_t port, TERRAMQTT_CALLBACK_SIGNATURE, Client &client)
{
    this->_state = TERRAMQTT_DISCONNECTED;
    setServer(domain, port);
    setCallback(callback);
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(TERRAMQTT_MAX_PACKET_SIZE);
    setKeepAlive(TERRAMQTT_KEEPALIVE);
    setSocketTimeout(TERRAMQTT_SOCKET_TIMEOUT);
}

TerraLib::TerraLib(const char *domain, uint16_t port, TERRAMQTT_CALLBACK_SIGNATURE, Client &client, Stream &stream)
{
    this->_state = TERRAMQTT_DISCONNECTED;
    setServer(domain, port);
    setCallback(callback);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(TERRAMQTT_MAX_PACKET_SIZE);
    setKeepAlive(TERRAMQTT_KEEPALIVE);
    setSocketTimeout(TERRAMQTT_SOCKET_TIMEOUT);
}

TerraLib::~TerraLib()
{
    free(this->buffer);
}

boolean TerraLib::connect(const char *id)
{
    return connect(id, NULL, NULL, 0, 0, 0, 0, 1);
}

boolean TerraLib::connect(const char *id, const char *user, const char *pass)
{
    return connect(id, user, pass, 0, 0, 0, 0, 1);
}

boolean TerraLib::connect(const char *id, const char *willTopic, uint8_t willQos, boolean willRetain, const char *willMessage)
{
    return connect(id, NULL, NULL, willTopic, willQos, willRetain, willMessage, 1);
}

boolean TerraLib::connect(const char *id, const char *user, const char *pass, const char *willTopic, uint8_t willQos, boolean willRetain, const char *willMessage)
{
    return connect(id, user, pass, willTopic, willQos, willRetain, willMessage, 1);
}

boolean TerraLib::connect(const char *id, const char *user, const char *pass, const char *willTopic, uint8_t willQos, boolean willRetain, const char *willMessage, boolean cleanSession)
{
    if (!connected())
    {
        int result = 0;

        if (_client->connected())
        {
            result = 1;
        }
        else
        {
            if (domain != NULL)
            {
                result = _client->connect(this->domain, this->port);
            }
            else
            {
                result = _client->connect(this->ip, this->port);
            }
        }

        if (result == 1)
        {
            nextMsgId = 1;
            uint16_t length = TERRAMQTT_MAX_HEADER_SIZE;
            unsigned int j;

#if TERRAMQTT_VERSION == TERRAMQTT_VERSION_3_1
            uint8_t d[9] = {0x00, 0x06, 'M', 'Q', 'I', 's', 'd', 'p', TERRAMQTT_VERSION};
#define TERRAMQTT_HEADER_VERSION_LENGTH 9
#elif TERRAMQTT_VERSION == TERRAMQTT_VERSION_3_1_1
            uint8_t d[7] = {0x00, 0x04, 'M', 'Q', 'T', 'T', TERRAMQTT_VERSION};
#define TERRAMQTT_HEADER_VERSION_LENGTH 7
#endif
            for (j = 0; j < TERRAMQTT_HEADER_VERSION_LENGTH; j++)
            {
                this->buffer[length++] = d[j];
            }

            uint8_t v;
            if (willTopic)
            {
                v = 0x04 | (willQos << 3) | (willRetain << 5);
            }
            else
            {
                v = 0x00;
            }
            if (cleanSession)
            {
                v = v | 0x02;
            }

            if (user != NULL)
            {
                v = v | 0x80;
                if (pass != NULL)
                {
                    v = v | (0x80 >> 1);
                }
            }
            this->buffer[length++] = v;

            this->buffer[length++] = ((this->keepAlive) >> 8);
            this->buffer[length++] = ((this->keepAlive) & 0xFF);

            MYCHECK_STRING_LENGTH(length, id)
            length = writeString(id, this->buffer, length);
            if (willTopic)
            {
                MYCHECK_STRING_LENGTH(length, willTopic)
                length = writeString(willTopic, this->buffer, length);
                MYCHECK_STRING_LENGTH(length, willMessage)
                length = writeString(willMessage, this->buffer, length);
            }

            if (user != NULL)
            {
                MYCHECK_STRING_LENGTH(length, user)
                length = writeString(user, this->buffer, length);
                if (pass != NULL)
                {
                    MYCHECK_STRING_LENGTH(length, pass)
                    length = writeString(pass, this->buffer, length);
                }
            }

            write(TERRAMQTTCONNECT, this->buffer, length - TERRAMQTT_MAX_HEADER_SIZE);

            lastInActivity = lastOutActivity = millis();

            while (!_client->available())
            {
                unsigned long t = millis();
                if (t - lastInActivity >= ((int32_t)this->socketTimeout * 1000UL))
                {
                    _state = TERRAMQTT_CONNECTION_TIMEOUT;
                    _client->stop();
                    return false;
                }
            }
            uint8_t llen;
            uint32_t len = readPacket(&llen);

            if (len == 4)
            {
                if (buffer[3] == 0)
                {
                    lastInActivity = millis();
                    pingOutstanding = false;
                    _state = TERRAMQTT_CONNECTED;
                    return true;
                }
                else
                {
                    _state = buffer[3];
                }
            }
            _client->stop();
        }
        else
        {
            _state = TERRAMQTT_CONNECT_FAILED;
        }
        return false;
    }
    return true;
}

boolean TerraLib::readByte(uint8_t *result)
{
    uint32_t previousMillis = millis();
    while (!_client->available())
    {
        yield();
        uint32_t currentMillis = millis();
        if (currentMillis - previousMillis >= ((int32_t)this->socketTimeout * 1000))
        {
            return false;
        }
    }
    *result = _client->read();
    return true;
}

boolean TerraLib::readByte(uint8_t *result, uint16_t *index)
{
    uint16_t current_index = *index;
    uint8_t *write_address = &(result[current_index]);
    if (readByte(write_address))
    {
        *index = current_index + 1;
        return true;
    }
    return false;
}

uint32_t TerraLib::readPacket(uint8_t *lengthLength)
{
    uint16_t len = 0;
    if (!readByte(this->buffer, &len))
        return 0;
    bool isPublish = (this->buffer[0] & 0xF0) == TERRAMQTTPUBLISH;
    uint32_t multiplier = 1;
    uint32_t length = 0;
    uint8_t digit = 0;
    uint16_t skip = 0;
    uint32_t start = 0;

    do
    {
        if (len == 5)
        {
            _state = TERRAMQTT_DISCONNECTED;
            _client->stop();
            return 0;
        }
        if (!readByte(&digit))
            return 0;
        this->buffer[len++] = digit;
        length += (digit & 127) * multiplier;
        multiplier <<= 7;
    } while ((digit & 128) != 0);
    *lengthLength = len - 1;

    if (isPublish)
    {
        if (!readByte(this->buffer, &len))
            return 0;
        if (!readByte(this->buffer, &len))
            return 0;
        skip = (this->buffer[*lengthLength + 1] << 8) + this->buffer[*lengthLength + 2];
        start = 2;
        if (this->buffer[0] & TERRAMQTTQOS1)
        {
            skip += 2;
        }
    }
    uint32_t idx = len;

    for (uint32_t i = start; i < length; i++)
    {
        if (!readByte(&digit))
            return 0;
        if (this->stream)
        {
            if (isPublish && idx - *lengthLength - 2 > skip)
            {
                this->stream->write(digit);
            }
        }

        if (len < this->bufferSize)
        {
            this->buffer[len] = digit;
            len++;
        }
        idx++;
    }

    if (!this->stream && idx > this->bufferSize)
    {
        len = 0;
    }
    return len;
}

boolean TerraLib::loop()
{
    if (connected())
    {
        unsigned long t = millis();
        if ((t - lastInActivity > this->keepAlive * 1000UL) || (t - lastOutActivity > this->keepAlive * 1000UL))
        {
            if (pingOutstanding)
            {
                this->_state = TERRAMQTT_CONNECTION_TIMEOUT;
                _client->stop();
                return false;
            }
            else
            {
                this->buffer[0] = TERRAMQTTPINGREQ;
                this->buffer[1] = 0;
                _client->write(this->buffer, 2);
                lastOutActivity = t;
                lastInActivity = t;
                pingOutstanding = true;
            }
        }
        if (_client->available())
        {
            uint8_t llen;
            uint16_t len = readPacket(&llen);
            uint16_t msgId = 0;
            uint8_t *payload;
            if (len > 0)
            {
                lastInActivity = t;
                uint8_t type = this->buffer[0] & 0xF0;
                if (type == TERRAMQTTPUBLISH)
                {
                    if (callback)
                    {
                        uint16_t tl = (this->buffer[llen + 1] << 8) + this->buffer[llen + 2];
                        memmove(this->buffer + llen + 2, this->buffer + llen + 3, tl);
                        this->buffer[llen + 2 + tl] = 0;
                        char *topic = (char *)this->buffer + llen + 2;
                        if ((this->buffer[0] & 0x06) == TERRAMQTTQOS1)
                        {
                            msgId = (this->buffer[llen + 3 + tl] << 8) + this->buffer[llen + 3 + tl + 1];
                            payload = this->buffer + llen + 3 + tl + 2;
                            callback(topic, payload, len - llen - 3 - tl - 2);

                            this->buffer[0] = TERRAMQTTPUBACK;
                            this->buffer[1] = 2;
                            this->buffer[2] = (msgId >> 8);
                            this->buffer[3] = (msgId & 0xFF);
                            _client->write(this->buffer, 4);
                            lastOutActivity = t;
                        }
                        else
                        {
                            payload = this->buffer + llen + 3 + tl;
                            callback(topic, payload, len - llen - 3 - tl);
                        }
                    }
                }
                else if (type == TERRAMQTTPINGREQ)
                {
                    this->buffer[0] = TERRAMQTTPINGRESP;
                    this->buffer[1] = 0;
                    _client->write(this->buffer, 2);
                }
                else if (type == TERRAMQTTPINGRESP)
                {
                    pingOutstanding = false;
                }
            }
            else if (!connected())
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

boolean TerraLib::publish(const char *topic, const char *payload)
{
    return publish(topic, (const uint8_t *)payload, payload ? strnlen(payload, this->bufferSize) : 0, false);
}

boolean TerraLib::publish(const char *topic, const char *payload, boolean retained)
{
    return publish(topic, (const uint8_t *)payload, payload ? strnlen(payload, this->bufferSize) : 0, retained);
}

boolean TerraLib::publish(const char *topic, const uint8_t *payload, unsigned int plength)
{
    return publish(topic, payload, plength, false);
}

boolean TerraLib::publish(const char *topic, const uint8_t *payload, unsigned int plength, boolean retained)
{
    if (connected())
    {
        if (this->bufferSize < TERRAMQTT_MAX_HEADER_SIZE + 2 + strnlen(topic, this->bufferSize) + plength)
        {
            return false;
        }
        uint16_t length = TERRAMQTT_MAX_HEADER_SIZE;
        length = writeString(topic, this->buffer, length);

        for (unsigned int i = 0; i < plength; i++)
        {
            this->buffer[length++] = payload[i];
        }

        uint8_t header = TERRAMQTTPUBLISH;
        if (retained)
        {
            header |= 1;
        }
        return write(header, this->buffer, length - TERRAMQTT_MAX_HEADER_SIZE);
    }
    return false;
}

boolean TerraLib::publish_P(const char *topic, const char *payload, boolean retained)
{
    return publish_P(topic, (const uint8_t *)payload, payload ? strnlen(payload, this->bufferSize) : 0, retained);
}

boolean TerraLib::publish_P(const char *topic, const uint8_t *payload, unsigned int plength, boolean retained)
{
    uint8_t llen = 0;
    uint8_t digit;
    unsigned int rc = 0;
    uint16_t tlen;
    unsigned int pos = 0;
    unsigned int i;
    uint8_t header;
    unsigned int len;
    int expectedLength;

    if (!connected())
    {
        return false;
    }

    tlen = strnlen(topic, this->bufferSize);

    header = TERRAMQTTPUBLISH;
    if (retained)
    {
        header |= 1;
    }
    this->buffer[pos++] = header;
    len = plength + 2 + tlen;
    do
    {
        digit = len & 127;
        len >>= 7;
        if (len > 0)
        {
            digit |= 0x80;
        }
        this->buffer[pos++] = digit;
        llen++;
    } while (len > 0);

    pos = writeString(topic, this->buffer, pos);

    rc += _client->write(this->buffer, pos);

    for (i = 0; i < plength; i++)
    {
#if defined(ARDUINO_ARCH_AVR)
        rc += _client->write((char)pgm_read_byte_near(payload + i));
#else
        rc += _client->write(payload + i, 1);
#endif
    }

    lastOutActivity = millis();

    expectedLength = 1 + llen + 2 + tlen + plength;

    return (rc == expectedLength);
}

boolean TerraLib::beginPublish(const char *topic, unsigned int plength, boolean retained)
{
    if (connected())
    {
        uint16_t length = TERRAMQTT_MAX_HEADER_SIZE;
        length = writeString(topic, this->buffer, length);
        uint8_t header = TERRAMQTTPUBLISH;
        if (retained)
        {
            header |= 1;
        }
        size_t hlen = buildHeader(header, this->buffer, plength + length - TERRAMQTT_MAX_HEADER_SIZE);
        uint16_t rc = _client->write(this->buffer + (TERRAMQTT_MAX_HEADER_SIZE - hlen), length - (TERRAMQTT_MAX_HEADER_SIZE - hlen));
        lastOutActivity = millis();
        return (rc == (length - (TERRAMQTT_MAX_HEADER_SIZE - hlen)));
    }
    return false;
}

int TerraLib::endPublish()
{
    return 1;
}

size_t TerraLib::write(uint8_t data)
{
    lastOutActivity = millis();
    return _client->write(data);
}

size_t TerraLib::write(const uint8_t *buffer, size_t size)
{
    lastOutActivity = millis();
    return _client->write(buffer, size);
}

size_t TerraLib::buildHeader(uint8_t header, uint8_t *buf, uint16_t length)
{
    uint8_t lenBuf[4];
    uint8_t llen = 0;
    uint8_t digit;
    uint8_t pos = 0;
    uint16_t len = length;
    do
    {
        digit = len & 127;
        len >>= 7;
        if (len > 0)
        {
            digit |= 0x80;
        }
        lenBuf[pos++] = digit;
        llen++;
    } while (len > 0);

    buf[4 - llen] = header;
    for (int i = 0; i < llen; i++)
    {
        buf[TERRAMQTT_MAX_HEADER_SIZE - llen + i] = lenBuf[i];
    }
    return llen + 1;
}

boolean TerraLib::write(uint8_t header, uint8_t *buf, uint16_t length)
{
    uint16_t rc;
    uint8_t hlen = buildHeader(header, buf, length);

#ifdef TERRAMQTT_MAX_TRANSFER_SIZE
    uint8_t *writeBuf = buf + (TERRAMQTT_MAX_HEADER_SIZE - hlen);
    uint16_t bytesRemaining = length + hlen;
    uint8_t bytesToWrite;
    boolean result = true;
    while ((bytesRemaining > 0) && result)
    {
        bytesToWrite = (bytesRemaining > TERRAMQTT_MAX_TRANSFER_SIZE) ? TERRAMQTT_MAX_TRANSFER_SIZE : bytesRemaining;
        rc = _client->write(writeBuf, bytesToWrite);
        result = (rc == bytesToWrite);
        bytesRemaining -= rc;
        writeBuf += rc;
    }
    return result;
#else
    rc = _client->write(buf + (TERRAMQTT_MAX_HEADER_SIZE - hlen), length + hlen);
    lastOutActivity = millis();
    return (rc == hlen + length);
#endif
}

boolean TerraLib::subscribe(const char *topic)
{
    return subscribe(topic, 0);
}

boolean TerraLib::subscribe(const char *topic, uint8_t qos)
{
    size_t topicLength = strnlen(topic, this->bufferSize);
    if (topic == 0)
    {
        return false;
    }
    if (qos > 1)
    {
        return false;
    }
    if (this->bufferSize < 9 + topicLength)
    {
        return false;
    }
    if (connected())
    {
        uint16_t length = TERRAMQTT_MAX_HEADER_SIZE;
        nextMsgId++;
        if (nextMsgId == 0)
        {
            nextMsgId = 1;
        }
        this->buffer[length++] = (nextMsgId >> 8);
        this->buffer[length++] = (nextMsgId & 0xFF);
        length = writeString((char *)topic, this->buffer, length);
        this->buffer[length++] = qos;
        return write(TERRAMQTTSUBSCRIBE | TERRAMQTTQOS1, this->buffer, length - TERRAMQTT_MAX_HEADER_SIZE);
    }
    return false;
}

boolean TerraLib::unsubscribe(const char *topic)
{
    size_t topicLength = strnlen(topic, this->bufferSize);
    if (topic == 0)
    {
        return false;
    }
    if (this->bufferSize < 9 + topicLength)
    {
        return false;
    }
    if (connected())
    {
        uint16_t length = TERRAMQTT_MAX_HEADER_SIZE;
        nextMsgId++;
        if (nextMsgId == 0)
        {
            nextMsgId = 1;
        }
        this->buffer[length++] = (nextMsgId >> 8);
        this->buffer[length++] = (nextMsgId & 0xFF);
        length = writeString(topic, this->buffer, length);
        return write(TERRAMQTTUNSUBSCRIBE | TERRAMQTTQOS1, this->buffer, length - TERRAMQTT_MAX_HEADER_SIZE);
    }
    return false;
}

void TerraLib::disconnect()
{
    this->buffer[0] = TERRAMQTTDISCONNECT;
    this->buffer[1] = 0;
    _client->write(this->buffer, 2);
    _state = TERRAMQTT_DISCONNECTED;
    _client->flush();
    _client->stop();
    lastInActivity = lastOutActivity = millis();
}

uint16_t TerraLib::writeString(const char *string, uint8_t *buf, uint16_t pos)
{
    const char *idp = string;
    uint16_t i = 0;
    pos += 2;
    while (*idp)
    {
        buf[pos++] = *idp++;
        i++;
    }
    buf[pos - i - 2] = (i >> 8);
    buf[pos - i - 1] = (i & 0xFF);
    return pos;
}

boolean TerraLib::connected()
{
    boolean rc;
    if (_client == NULL)
    {
        rc = false;
    }
    else
    {
        rc = (int)_client->connected();
        if (!rc)
        {
            if (this->_state == TERRAMQTT_CONNECTED)
            {
                this->_state = TERRAMQTT_CONNECTION_LOST;
                _client->flush();
                _client->stop();
            }
        }
        else
        {
            return this->_state == TERRAMQTT_CONNECTED;
        }
    }
    return rc;
}

TerraLib &TerraLib::setServer(uint8_t *ip, uint16_t port)
{
    IPAddress addr(ip[0], ip[1], ip[2], ip[3]);
    return setServer(addr, port);
}

TerraLib &TerraLib::setServer(IPAddress ip, uint16_t port)
{
    this->ip = ip;
    this->port = port;
    this->domain = NULL;
    return *this;
}

TerraLib &TerraLib::setServer(const char *domain, uint16_t port)
{
    this->domain = domain;
    this->port = port;
    return *this;
}

TerraLib &TerraLib::setCallback(TERRAMQTT_CALLBACK_SIGNATURE)
{
    this->callback = callback;
    return *this;
}

TerraLib &TerraLib::setClient(Client &client)
{
    this->_client = &client;
    return *this;
}

TerraLib &TerraLib::setStream(Stream &stream)
{
    this->stream = &stream;
    return *this;
}

int TerraLib::state()
{
    return this->_state;
}

boolean TerraLib::setBufferSize(uint16_t size)
{
    if (size == 0)
    {
        return false;
    }
    if (this->bufferSize == 0)
    {
        this->buffer = (uint8_t *)malloc(size);
    }
    else
    {
        uint8_t *newBuffer = (uint8_t *)realloc(this->buffer, size);
        if (newBuffer != NULL)
        {
            this->buffer = newBuffer;
        }
        else
        {
            return false;
        }
    }
    this->bufferSize = size;
    return (this->buffer != NULL);
}

uint16_t TerraLib::getBufferSize()
{
    return this->bufferSize;
}

TerraLib &TerraLib::setKeepAlive(uint16_t keepAlive)
{
    this->keepAlive = keepAlive;
    return *this;
}

TerraLib &TerraLib::setSocketTimeout(uint16_t timeout)
{
    this->socketTimeout = timeout;
    return *this;
}
