#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Servo.h>

#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

#define WIFI_SSID "Redmi A1+"
#define WIFI_PASSWORD "30082022"
#define PWMChannel 0
#define LED1_PIN 14
#define LED2_PIN 5
Servo servo; 

const int freq = 5000;
const int resolution = 8;

// Insert Firebase project API Key
#define API_KEY "AIzaSyDc-JZmdPXUMwd9-NZwOlSYAu019FS07Ck"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://esp8266-2-bbe56-default-rtdb.asia-southeast1.firebasedatabase.app/" 

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;
int number = 0;
String pwmValue = "";
bool ledStatus = false;
void setup() {
  servo.attach(2);
  servo.write(0);
  delay(200);
  pinMode(LED1_PIN,OUTPUT);
  pinMode(LED2_PIN,OUTPUT);
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;
  

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

}

void loop() {

 /// servo.write(90);
  //delay(1000);
  //servo.write(0);
  //delay(1000);
//  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
//    sendDataPrevMillis = millis();
    // Write an Int number on the database path test/int
//    if (Firebase.RTDB.setInt(&fbdo, "test/int", count)){
  //    Serial.println("PASSED");
    //  Serial.println("PATH: " + fbdo.dataPath());
      //Serial.println("TYPE: " + fbdo.dataType());
    //}
    //else {
      //Serial.println("FAILED");
      //Serial.println("REASON: " + fbdo.errorReason());
    //}
    //count++;
    
    // Write an Float number on the database path test/float
    //if (Firebase.RTDB.setFloat(&fbdo, "test/float", 0.01 + random(0,100))){
    //  Serial.println("PASSED");
    //  Serial.println("PATH: " + fbdo.dataPath());
    //  Serial.println("TYPE: " + fbdo.dataType());
    //}
    //else {
    //  Serial.println("FAILED");
    //  Serial.println("REASON: " + fbdo.errorReason());
   // }

   // if (Firebase.RTDB.setInt(&fbdo, "test/porte", number)){
    //  Serial.println("PASSED");
    //  Serial.println("PATH: " + fbdo.dataPath());
    //  Serial.println("TYPE: " + fbdo.dataType());
  //  }
  //  else {
  //    Serial.println("FAILED");
   //   Serial.println("REASON: " + fbdo.errorReason());
  //  }

 // }
  //----------READ DATA
  if(Firebase.RTDB.getInt(&fbdo,"/LED/led1")){
    if (fbdo.dataType() == "string"){
      pwmValue = fbdo.stringData();
      Serial.println(pwmValue);
      if (pwmValue == "1"){
        digitalWrite(LED1_PIN,HIGH);
       
      }else{
        digitalWrite(LED1_PIN,LOW);
      }
    }
  }  
  else {
    Serial.println("FAILED");
    Serial.println("REASON: " + fbdo.errorReason());
  }  


  if(Firebase.RTDB.getString(&fbdo,"/LED/led2")){
    if (fbdo.dataType() == "string"){
      pwmValue = fbdo.stringData();
       Serial.println(pwmValue);
      if (pwmValue == "1"){
        digitalWrite(LED2_PIN,HIGH);
       
      }else{
        digitalWrite(LED2_PIN,LOW);
      }
    }
  }  
  else {
    Serial.println("FAILED");
    Serial.println("REASON: " + fbdo.errorReason());
  }  
}