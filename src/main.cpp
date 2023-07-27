/**
 * @brief This script sets up a WiFi server and a DDBot object, which controls a two-wheeled robot with four motors.
 * It listens for incoming commands from a client, executes them on the DDBot object, and sends a response back to the client.
 *
 * The script first sets up the WiFi connection and waits for a client to connect to the server.
 * Once a client is connected, the script listens for incoming data from the client.
 * When data is received, it is parsed and executed on the DDBot object.
 * A response is then generated and sent back to the client.
 * This process continues until the client disconnects from the server.
 *
 * To use this script, upload it to an appropriate board (such as an ESP32 or ESP8266) and connect the four motor pins to the appropriate pins on the board.
 * Then, connect to the WiFi network created by the board and send commands to the server using a client such as a web browser or a custom application.
 * The server will execute the commands on the DDBot object and send a response back to the client.
 * The IP address of the board can be found in the Serial Monitor after connecting to the WiFi network.
 */

#include <Arduino.h>
#include <DDBot.h>
#include <WiFi.h>
#include <secrets.h>

const int PORT = 80;

WiFiServer server(PORT);
WiFiClient client;
DDBot bot(
    13,  // left forward
    12,  // left backward
    14,  // right forward
    27  // right backward
);

const uint8_t LED_PIN = 2;

char command;
String response, receivedData;

void setupWiFi() {
    WiFi.mode(WIFI_STA);

    WiFi.begin(SSID, PASSWORD);

    Serial.print("Connecting to WiFi ");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        
        digitalWrite(LED_PIN, HIGH);
        delay(100);
        digitalWrite(LED_PIN, LOW);
        delay(100);
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
    digitalWrite(LED_PIN, HIGH);

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
            digitalWrite(LED_PIN, LOW);
            
            break;

        default:
            bot.stop();
            digitalWrite(LED_PIN, LOW);

            return "ERROR";
    }

    return "OK";
}

void setup() {
    pinMode(LED_PIN, OUTPUT);
    
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