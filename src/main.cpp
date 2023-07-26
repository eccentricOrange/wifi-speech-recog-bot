#include <Arduino.h>
#include <DDBot.h>
#include <WiFi.h>
#include <secrets.h>

const int PORT = 80;

uint8_t DIRECTION_PINS[DDBot::NUMBER_OF_DIRECTION_PINS] = {
    2,  // Left forward
    3,  // Left backward
    4,  // Right forward
    5   // Right backward
};

WiFiServer server(PORT);
WiFiClient client;
DDBot bot(DIRECTION_PINS);

char command;
String response, receivedData;

void setupWiFi() {
    WiFi.mode(WIFI_STA);

    WiFi.begin(SSID, PASSWORD);

    Serial.print("Connecting to WiFi ");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(500);
    }

    Serial.println();

    Serial.print("Connected to WiFi. IP address: ");
    Serial.println(WiFi.localIP());

    server.begin();
}

void sendHTTPResponse(WiFiClient client, int statusCode, const String& contentType, const String& content) {
    client.println("HTTP/1.1 " + String(statusCode) + " OK");
    client.println("Content-Type: " + contentType);
    client.println("Connection: close");
    client.println();
    client.println(content);
}

String writeToBot(const char command) {
    switch (command) {
        case 'F':
            bot.forward();
            break;

        case 'B':
            bot.backward();
            break;

        case 'L':
            bot.left();
            break;

        case 'R':
            bot.right();
            break;

        case 'S':
            bot.stop();
            break;

        default:
            bot.stop();
            return "ERROR";
    }

    return "OK";
}

void setup() {
    Serial.begin(115200);
    setupWiFi();
    bot.setPinModes();
}

void loop() {
    client = server.available();

    if (client) {

        while (client.connected()) {

            if (client.available()) {
                receivedData = client.readString();
                command = receivedData[receivedData.length() - 1];
                
                Serial.printf("Received command: %c\n", command);
                response = writeToBot(command);

                sendHTTPResponse(client, 200, "text/plain", response);
            }
            break;
        }

        client.stop();
        Serial.println("Client disconnected");
    }
}