#include <ESP8266WiFi.h>
int sensor = A0;
int motor = D1;

String apiKey = " ";     //  Enter your Write API key from ThingSpeak API anahtarınızı giriniz.
 
const char *ssid =  "wifi0008";     // wifi adı
const char *pass =  "4F85s72WvG";  //wifi şifresi
const char* server = "api.thingspeak.com";
 
WiFiClient client;
 
void setup() 
{
  pinMode(sensor, INPUT);
  pinMode(motor, OUTPUT);
  Serial.begin(115200);
  delay(10);
      
  Serial.println("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
      delay(500);
      Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
}
 
void loop() 
{
  Serial.println("*********");
      int nem = analogRead(sensor);
      Serial.print("Nem: ");
      Serial.print(nem);
      if (nem > 400) {
        Serial.println(" 400den yüksek");
        digitalWrite(motor,HIGH);
        delay(3000);
        digitalWrite(motor,LOW);
        delay(3000);
      } else {
        Serial.println("nem 400den düşük");
        delay(3000);


      }


      if (client.connect(server,80))   
      {  
      String postStr = apiKey;
      postStr +="&field1=";
      postStr += String(nem);
      postStr += "\r\n\r\n";                      
      
      client.print("POST /update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(postStr.length());
      client.print("\n\n");
      client.print(postStr);
                            
      
      Serial.println(" Send to Thingspeak.");
      }
      Serial.println("Waiting...");
  
  Serial.println("*******");
  delay(5000);
}

