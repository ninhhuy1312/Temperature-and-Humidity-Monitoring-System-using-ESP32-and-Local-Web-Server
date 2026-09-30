#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "P1404";
const char* password = "12345679";

WebServer server(80);

// Chân LED tích hợp trên bo ESP32 WROOM (thường là GPIO 2)
#define LED_PIN 2

// Hàm hiển thị giao diện trang chủ
void viewer() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>ESP32 Control</title></head><body style='text-align:center; font-family:sans-serif;'>";
  html += "<h2>DIEU KHIEN LED ESP32</h2>";
  html += "<p><a href='/on' style='display:inline-block; padding:15px 30px; font-size:24px; color:white; background:green; text-decoration:none; border-radius:8px;'>ON LED</a></p>";
  html += "<p><a href='/off' style='display:inline-block; padding:15px 30px; font-size:24px; color:white; background:red; text-decoration:none; border-radius:8px;'>OFF LED</a></p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void TurnOnLed() {
  digitalWrite(LED_PIN, HIGH);
  server.sendHeader("Location", "/"); // Bật xong tự quay về trang chủ
  server.send(303);
}

void TurnOffLed() {
  digitalWrite(LED_PIN, LOW);
  server.sendHeader("Location", "/"); // Tắt xong tự quay về trang chủ
  server.send(303);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("\nDang ket noi WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("Dia chi IP: ");
  Serial.println(WiFi.localIP());

  // Đăng ký các đường dẫn
  server.on("/", viewer);
  server.on("/on", TurnOnLed);
  server.on("/off", TurnOffLed);

  server.begin();
  Serial.println("HTTP Server da khoi chay!");
}

void loop() {
  server.handleClient();
}