#include <Arduino.h>  //Arduino library
#include <HX711.h>    //Library for the HX711 amplifier
#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <WiFiClient.h>


// HX711 circuit wiring
const byte LOADCELL_DAT_PIN = D0;  //Names of the pins can be found on the HX711 board
const byte LOADCELL_CLK_PIN = D1;  //Names of the pins can be found on the HX711 board
const float CALIBRATION_VALUE = 105250;  //This goes into the set_scale() function
const int DATA_LOGGING_SPEED = 100;  //Speed at which the serial monitor prints the values measured (in Milicesonds)

HX711 scale;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void setup() {
  Serial.begin(115200);

  // Serial.println("HX711 testing:");
  // Serial.println("Initialization Started");
  scale.begin(LOADCELL_DAT_PIN, LOADCELL_CLK_PIN);
  scale.set_scale(CALIBRATION_VALUE);
  scale.tare();  // Tare the loadcell

  WiFi.softAP("near", "12345678");
  IPAddress ipa = WiFi.softAPIP();
  Serial.println(ipa);

  ws.onEvent([] (AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    switch (type) {
      case WS_EVT_CONNECT:
        Serial.printf("WS connected %s from ip: %s", client->id(), client->remoteIP().toString().c_str());
    }
  });
  server.addHandler(&ws);

  server.on("/", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", R"rawliteral(<!DOCTYPE html><html><head></head><body><h1>AAA</h1></body><script>var websocket=new WebSocket(`ws://${window.location.hostname}/ws`);</script></html>)rawliteral");
  });

  server.begin();
  // Serial.println("Before set up:");

  // Serial.print("read: \t\t");
  // Serial.println(scale.read());
  // Serial.print("read average: \t\t");
  // Serial.println(scale.read_average(20));

  // Serial.print("get value: \t\t");
  // Serial.println(scale.get_value(5));

  // Serial.print("get units: \t\t");
  // Serial.println(scale.get_units(5), 3);

  


}

void loop() {
  //Serial.println(scale.get_units(), 3);
  ws.cleanupClients();
  delay(0);
}

