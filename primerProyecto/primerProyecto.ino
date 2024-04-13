//==================================
// ESP32 WebSocket Server: Toggle LED
// by: Ulas Dikme
//==================================
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

//-----------------------------------------------
const char* ssid = "1";
const char* password = "12345678";

//-----------------------------------------------
#define LED_PIN 2
#define LED2_PIN 18

//-----------------------------------------------
WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

//-----------------------------------------------
boolean LEDonoff = false;
boolean LEDonoff2 = false;

//-----------------------------------------------
#include "functions.h"

//====================================================================
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  //-----------------------------------------------
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  WiFi.mode(WIFI_STA);
  Serial.println();
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());

  //-----------------------------------------------
  server.on("/", webpage);

  //-----------------------------------------------
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

//====================================================================
void loop() {
  webSocket.loop();
  server.handleClient();

  // Escribir el estado de los LEDs según el valor de LEDonoff y LEDonoff2
  digitalWrite(LED_PIN, LEDonoff ? HIGH : LOW);
  digitalWrite(LED2_PIN, LEDonoff2 ? HIGH : LOW);

  // Asignar el valor de LEDstatus usando el operador ternario para LEDonoff
  String LEDstatus = LEDonoff ? "ON" : "OFF";
  String LEDstatus2 = LEDonoff2 ? "ON" : "OFF";

  String JSONtxt = "{\"LEDonoff\":\"" + LEDstatus + "\", \"LEDonoff2\":\"" + LEDstatus2 + "\"}";
  webSocket.broadcastTXT(JSONtxt);
}




