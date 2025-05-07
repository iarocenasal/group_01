#include <WiFi.h>
#include <HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// === CONFIGURA AQUÍ ===
const char* ssid = "Lamborghini Urus";
const char* password = "12345678";
String apiKey = "3N9J82UVSLO01PE7"; // Write API Key de ThingSpeak
const char* server = "http://api.thingspeak.com/update";

// Pines del sensor
#define MOISTURE_PIN 34
#define ONE_WIRE_BUS 15

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  sensors.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado");
}

void loop() {
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  int moisture = analogRead(MOISTURE_PIN);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = server + String("?api_key=") + apiKey +
                 "&field1=" + String(moisture) +
                 "&field2=" + String(temp);

    http.begin(url);
    int httpCode = http.GET();
    http.end();

    Serial.print("Enviado a ThingSpeak - Código: ");
    Serial.println(httpCode);
  }

  delay(15000); // Espera 15 segundos (requisito de ThingSpeak)
}
