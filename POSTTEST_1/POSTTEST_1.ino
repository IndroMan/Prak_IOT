#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "UNIVERSITAS MULAWARMAN";
const char* password = "";

ESP8266WebServer server(80); // Port untuk web server

const int buzzer = D8;
const int BTN_BUZZ1 = D6;
const int BTN_BUZZ2 = D7;
const int BTN_BUZZ3 = D5;
const int ledPWM = D0;
const int BTN_LED1 = D1;
const int BTN_LED2 = D2;
const int BTN_LED3 = D4;

int nilaiLED;
int nilaiBuzzer =100;

void setup() {
  Serial.begin(115200);      
  pinMode(buzzer, OUTPUT); 
  pinMode(BTN_BUZZ1, INPUT_PULLUP);                                                                                                                                    
  pinMode(BTN_BUZZ2, INPUT_PULLUP);                                                                                                                                    
  pinMode(BTN_BUZZ3, INPUT_PULLUP);                                                                                                                                    
  pinMode(ledPWM, OUTPUT); 
  pinMode(BTN_LED1, INPUT_PULLUP);                                                                                                                                    
  pinMode(BTN_LED2, INPUT_PULLUP);                                                                                                                                    
  pinMode(BTN_LED3, INPUT_PULLUP);     

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi.");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot); // Halaman utama

  server.begin(); // Memulai web server                                                                                                                               
}

void loop() {
  server.handleClient(); // Menangani permintaan dari klien

  int nyalaBuzzer = analogRead(BTN_BUZZ1);
  int IncBuzzer = analogRead(BTN_BUZZ2);
  int DecBuzzer = analogRead(BTN_BUZZ3);
  if (nyalaBuzzer == LOW) {
    if (nilaiBuzzer == 0){
      nilaiBuzzer = 100;
      delay(500);
    }else{
      nilaiBuzzer = 0;
      delay(500);
    }
  }
  if(IncBuzzer == LOW){
    if (nilaiBuzzer >= 100 && nilaiBuzzer <=2495){
      nilaiBuzzer += 5;
    }
  }
  if(DecBuzzer == LOW){
    if (nilaiBuzzer >= 105 && nilaiBuzzer <=2500){
      nilaiBuzzer -= 5;
    }
  }


  int nyalaLampu = analogRead(BTN_LED1);
  int IncLampu = analogRead(BTN_LED2);
  int DecLampu = analogRead(BTN_LED3);
  if (nyalaLampu == LOW) {
    if (nilaiLED == 0){
      nilaiLED = 5;
      delay(500);
    }else{
      nilaiLED = 0;
      delay(500);
    }
  }
  if(IncLampu == LOW){
    if (nilaiLED >= 5 && nilaiLED <=250){
      nilaiLED += 5;
    }
  }
  if(DecLampu == LOW){
    if (nilaiLED >= 10 && nilaiLED <=255){
      nilaiLED -= 5;
    }
  }

  // nyala buzzer
  analogWrite(buzzer, nilaiBuzzer);
  //nyala lampu
  analogWrite(ledPWM, nilaiLED);

  Serial.println(nilaiBuzzer);
  Serial.println(nyalaBuzzer);
  Serial.println(IncBuzzer);
  Serial.println(DecBuzzer);
  Serial.println("\n\n");
  delay(15);
}

void handleRoot() {
  String isi = "<html><body><p>Value LED " + String(nilaiLampu) + "</p> <br> <p>Value Buzzer " + String(nilaiBuzzer) + "</p></body></html>";
  server.send(200, "text/html",isi); // Menampilkan halaman web
}