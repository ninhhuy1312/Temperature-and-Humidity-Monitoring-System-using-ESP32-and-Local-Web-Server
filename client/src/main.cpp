#include <Arduino.h>
#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <HTTPClient.h>

const char* ssid = "P1404";
const char* password = "12345679";
const char* url = "http://192.168.1.100:3000";

#define DHTPIN 4  
#define DHTTYPE    DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid,password);
  dht.begin();
  while(WiFi.status() != WL_CONNECTED){
    Serial.print("...");
    delay(100);
  }
  Serial.println("Connected");
}

void loop() {
  //đọc nhiệt độ, độ ẩm
  float temp = 0;
  float hum = 0;
  if(dht.readTemperature() && dht.readHumidity()){
    temp = dht.readTemperature();
    hum = dht.readHumidity();
  }
  Serial.print("Nhiet do: ");
  Serial.println(temp);
  Serial.print("Do am: ");
  Serial.println(hum);
  
  //gửi lên server bằng call api post

  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    String jsonData = "{\"temp\":\""+String(temp)+"\", \"hum\":\""+String(hum)+"\"}";
    int res = http.POST(jsonData);
    if(res > 0){
      Serial.println("Gui thanh cong");
      Serial.print(http.getString());
    }
    else{
      Serial.println("Gui that bai");
      Serial.println(http.getString());
    }
    http.end();
 }
 delay(5000);
}

