#include <WiFi.h>
#include <HCSR04.h>
#include "FirebaseESP32.h"

#define FIREBASE_HOST "https://smarthomeiot-a47a8.firebaseio.com/"
#define FIREBASE_AUTH "MFK7GYdTltcAxAd53vEJEiqhibsdsdsMlcHqV3XvWFaTR" //hanya contoh yang saya ketik
#define WIFI_SSID "gratis"
#define WIFI_PASSWORD "gratis123"

UltraSonicDistanceSensor distanceSensor(18,19);//initialisation class HCSR04 (trig pin , echo pin)

#define led1 22
#define led2 13
#define ldr 34

FirebaseData firebaseData;

String path = "/Node1";
            
int oldAdcLdr;
int newAdcLdr;

int oldDistance;
int newDistance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(ldr,INPUT);
  oldDistance = distanceSensor.measureDistanceCm();
  oldAdcLdr = analogRead(ldr);
  
  initWifi();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);

  //ambil nilai dari sensor ultarsonic dan kirim ke firebase
  newDistance = distanceSensor.measureDistanceCm();
  Serial.print("nilai jarak: ");
  Serial.println(newDistance);
  if(newDistance != oldDistance){
    Firebase.setInt(firebaseData, path + "/jarak", newDistance);
    oldDistance = newDistance; 
  }

  //ambil nilai dari sensor LDR dan kirim ke firebase
  newAdcLdr = analogRead(ldr);
  newAdcLdr = newAdcLdr * (5.0 / 1023.0);   // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
  Serial.print("nilai ldr: ");
  Serial.println(newAdcLdr);
  if(newAdcLdr != oldAdcLdr){
    Firebase.setInt(firebaseData, path + "/cahaya", newAdcLdr);
    oldAdcLdr = newAdcLdr;
  }
  if(newAdcLdr == 0){
    digitalWrite(led2,1);
  } else{
    digitalWrite(led2,0);
  }
  
  //Merubah nilai lampu
  Firebase.getInt(firebaseData, path + "/lampu");
  if(firebaseData.intData() == 0){
    digitalWrite(led1,0);
  }else{
    digitalWrite(led1,1);  
  }
      
}


void initWifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}
