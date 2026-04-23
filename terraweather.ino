#include <WiFi.h>
#include <TerraLib.h>
#include <ModbusMaster.h>
#include <MQTTWebSocketClient.h>

#define RX_PIN 16
#define TX_PIN 17

const char *ssid = "iot-ict-lab24g";
const char *password = "iot#labclass";
const char *mqtt_server = "203.154.11.225";
const char *mqtt_path = "/mqtt"; // Change to "/" or your broker's WebSocket path if needed
const char *mqtt_user = "d_proj_ba7b2820_dev_93e13079";
const char *mqtt_pass = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJkZXZpY2VfaWQiOiJkZXZfOTNlMTMwNzkiLCJwcm9qZWN0X2lkIjoicHJval9iYTdiMjgyMCIsImV4cCI6MTgwODI5MDQwMSwiaWF0IjoxNzc2NzU0NDAxfQ.pPc7hBsns_uyyqz_HOQqz_HOQqgGU7ep9w8lgG3RuFBoMEF6Q"; // ใช้ตัวเต็มของคุณ

MQTTWebSocketClient wsClient(1024, 50000);
TerraLib mqtt(wsClient);
ModbusMaster node;

char msg_json[300];
unsigned long lastMsg = 0;

void reconnect()
{
    while (!mqtt.connected())
    {
        Serial.print("Attempting WSS Connection to ");
        Serial.println(mqtt_server);

        // Check if we are even connected to WiFi first
        if (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("WiFi disconnected, reconnecting...");
            WiFi.begin(ssid, password);
            delay(2000);
            continue;
        }

        Serial.print("WiFi OK, attempting MQTT connect with user: ");
        Serial.println(mqtt_user);

        if (mqtt.connect("dev_93e13079", mqtt_user, mqtt_pass))
        {
            Serial.println("MQTT connected successfully!");
        }
        else
        {
            // If it fails, WAIT longer.
            // 10 seconds gives the SSL memory time to clear.
            Serial.println("MQTT connection failed. Possible causes:");
            Serial.println("  1. SSL/TLS certificate verification failed");
            Serial.println("  2. MQTT authentication rejected");
            Serial.println("  3. Broker unreachable");
            Serial.println("Waiting 10s before retry...");
            delay(10000);
        }
    }
}

void setup()
{
    Serial.begin(115200);
    Serial2.begin(4800, SERIAL_8N1, RX_PIN, TX_PIN);
    node.begin(5, Serial2);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected");

    delay(1000);

    // --- MANDATORY SETTINGS FOR PORT 443 ---
    wsClient.setUseSSL(true);
    wsClient.setPath(mqtt_path);
    wsClient.setInsecure(); // Disable SSL certificate verification

    mqtt.setServer(mqtt_server, 443);
    mqtt.setBufferSize(1024);

    Serial.println("MQTT Configured for WSS. Starting...");
}

void loop()
{
    if (!mqtt.connected())
        reconnect();
    mqtt.loop();

    unsigned long now = millis();
    if (now - lastMsg > 5000)
    {
        lastMsg = now;
        uint8_t result = node.readHoldingRegisters(500, 8);

        if (result == node.ku8MBSuccess)
        {
            float hum = node.getResponseBuffer(0) / 10.0;
            float temp = (int16_t)node.getResponseBuffer(1) / 10.0;
            float noise = node.getResponseBuffer(2) / 10.0;
            uint16_t pm25 = node.getResponseBuffer(3);
            uint16_t pm10 = node.getResponseBuffer(4);
            float press = node.getResponseBuffer(5) / 10.0;
            uint32_t lux = ((uint32_t)node.getResponseBuffer(6) << 16) | node.getResponseBuffer(7);

            // ปรับ JSON ให้ตรงกับ SQL: payload.data.xxx
            String data_json = "{ \"data\": { ";
            data_json += "\"temp\": " + String(temp) + ", ";
            data_json += "\"hum\": " + String(hum) + ", ";
            data_json += "\"noise\": " + String(noise) + ", ";
            data_json += "\"pm25\": " + String(pm25) + ", ";
            data_json += "\"pm10\": " + String(pm10) + ", ";
            data_json += "\"press\": " + String(press) + ", ";
            data_json += "\"lux\": " + String(lux);
            data_json += " } }";

            data_json.toCharArray(msg_json, data_json.length() + 1);
            // ส่งไปที่ Topic ที่ตรงกับ Rule: devices/+/data
            mqtt.write("devices/weather_01/data", msg_json);
            Serial.println("Sent: " + data_json);
        }
    }
}