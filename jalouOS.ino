#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <ESP8266HTTPClient.h>

#include <Stepper.h>

#include <RCSwitch.h>

#include <OneWire.h>
#include <DallasTemperature.h>


/* WEBSERVER */
const char* ssid     = "";
const char* password = "";

/* Raspberry Pi */
#define RPI_IP ""

ESP8266WebServer server(80);

/* STEPPER */
const int stepsPerRevolution = 200;
Stepper rollo(stepsPerRevolution, 5, 4, 0, 2);


/* 433MHZ SENDER */
RCSwitch tx = RCSwitch();

/* TEMPERATURE SENSOR */
const int oneWireBus = 12;

OneWire oneWire(oneWireBus);
DallasTemperature temp(&oneWire);


void doRotations(int rotations) { //rotations: + = up, - = down
  int state = -1;

  Serial.print("doRotations: ");

  Serial.println("activating power...");
  for (int i = 0; i < 5; i++) {
    tx.send(1377617, 24);
    delay(10);
  }


  Serial.println(rotations);

  for (int i = 0; i < abs(rotations); i++) {
    if (rotations < 0) {
      state = 0;
      rollo.step(-stepsPerRevolution);
    } else {
      rollo.step(stepsPerRevolution);
      state = 1;
    }

    Serial.print("Step: ");
    Serial.println(i);
    delay(1);
  }

  Serial.println("deactivating power...");
  for (int i = 0; i < 5; i++) {
    tx.send(1377620, 24);
    delay(10);
  }

  Serial.println("Done");
  digitalWrite(LED_BUILTIN, HIGH);
}

/*
    WEBSERVER ENDPOINTS motor & temp
*/

void handleMotorControl() {
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
  } else {
    Serial.println("received POST request");
    server.send(200, "text/plain", "POST body was:\n" + server.arg("plain"));

    doRotations(server.arg("plain").toInt());
  }
}

void handleTemperature() {
  if (server.method() != HTTP_GET) {
    server.send(405, "text/plain", "Method Not Allowed");
  } else {

    temp.requestTemperatures();

    float temperature = temp.getTempCByIndex(0);

    Serial.println("received GET request");
    Serial.println(temperature);
    server.send(200, "text/plain", String(temperature));
  }
}

/*
   UPDATE CURRENT IP ADRESS TO HOME_AI ON rPi
*/
void updateIp() {
  WiFiClient client;
  HTTPClient http;

  Serial.print("[HTTP] update_ip begin...\n");

  String url_0 = "http://" RPI_IP "/home_ai/api/rollo/update_ip/";
  String url = url_0 + WiFi.localIP().toString();

  Serial.println(url);

  http.begin(client, url);
  Serial.print("[HTTP] GET...\n");

  int httpCode = http.GET();

  if (httpCode > 0) {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    if (httpCode == HTTP_CODE_OK) {
      const String& payload = http.getString();
      Serial.println("received payload:\n<<");
      Serial.println(payload);
      Serial.println(">>");
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}




void setup(void) {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  /* STEPPER */
  rollo.setSpeed(60);

  /* 433MHZ SENDER */
  tx.enableTransmit(13); //D7

  /* TEMP SENSOR */
  temp.begin();

  WiFi.begin(ssid, password);

  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleMotorControl);
  server.on("/temperature", handleTemperature);

  server.begin();
  Serial.println("HTTP server started");

  /* Send curren IP adress to Raspberry Pi*/
  updateIp();
}

void loop(void) {
  server.handleClient();
}
