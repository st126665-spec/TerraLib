#include <WiFi.h>
#include "TerraLib.h"
#include "DHT.h"

// Replace with your ssid/password and broker address
const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSWORD";
const char *mqtt_server = "broker.hivemq.com";
const uint16_t mqtt_port = 1883;

#define DHTPIN 4      // GPIO where DHT is connected
#define DHTTYPE DHT22 // DHT 11/22
#define LED_PIN 2

DHT dht(DHTPIN, DHTTYPE);
WiFiClient wifiClient;
TerraLib terra(wifiClient);

const char *tempTopic = "terra/data/temperature";
const char *humTopic = "terra/data/humidity";
const char *ledTopic = "terra/control/led";

void onMqttMessage(char *topic, uint8_t *payload, unsigned int length)
{
    String topicStr = String(topic);
    String payloadStr;
    for (unsigned int i = 0; i < length; i++)
    {
        payloadStr += (char)payload[i];
    }

    Serial.print("[TerraLib] Received ");
    Serial.print(topicStr);
    Serial.print(" -> ");
    Serial.println(payloadStr);

    if (topicStr == ledTopic)
    {
        if (payloadStr == "ON")
        {
            digitalWrite(LED_PIN, HIGH);
        }
        else if (payloadStr == "OFF")
        {
            digitalWrite(LED_PIN, LOW);
        }
    }
}

void connectWifi()
{
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" connected!");
}

void connectMqtt()
{
    while (!terra.connected())
    {
        Serial.print("Connecting TerraLib to MQTT...");
        if (terra.connect("TerraClient-ESP32"))
        {
            Serial.println(" connected");
            terra.read(ledTopic);
        }
        else
        {
            Serial.print(" failed, state=");
            Serial.println(terra.state());
            delay(2000);
        }
    }
}

void setup()
{
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    dht.begin();

    connectWifi();

    terra.setServer(mqtt_server, mqtt_port);
    terra.setCallback(onMqttMessage);

    connectMqtt();
}

unsigned long lastPublish = 0;

void loop()
{
    if (!terra.connected())
    {
        connectMqtt();
    }

    terra.loop();

    unsigned long now = millis();
    if (now - lastPublish > 10000)
    {
        float t = dht.readTemperature();
        float h = dht.readHumidity();

        if (!isnan(t) && !isnan(h))
        {
            char buf[64];
            snprintf(buf, sizeof(buf), "%.2f", t);
            terra.write(tempTopic, buf);
            snprintf(buf, sizeof(buf), "%.2f", h);
            terra.write(humTopic, buf);
            Serial.printf("Published temperature=%.2f humidity=%.2f\n", t, h);
        }
        else
        {
            Serial.println("DHT read failed");
        }
        lastPublish = now;
    }

    delay(10);
}
