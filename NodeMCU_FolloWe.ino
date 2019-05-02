#define BLYNK_PRINT Serial

//Include Libraries
#include <SoftwareSerial.h>

//Definitions
//Motor
#define MOTOR_A_EN D1
#define MOTOR_B_EN D4
//Motor Controll
#define MOTOR_A_IN_1 D2   // A1 HIGH,A2 LOW : Backwards
#define MOTOR_A_IN_2 D3   // A2 LOW,A2 HIGH : Forwards
#define MOTOR_B_IN_3 D5   // A3 HIGH,A4 LOW : Backwards
#define MOTOR_B_IN_4 D6   // A3 LOW,A4 HIGH : Forwards

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "--Your Blynk Token--";

char ssid[] = "--Your SSID--";
char pass[] = "--Your PWD--";

BLYNK_CONNECTED() {
  Blynk.syncAll();
}

int x_axis,y_axis;
//X - 1024 : Right , X - 0 : Left
//Y - 1024 : Forward , Y - 0 : Backward
// Center : 512,512

BLYNK_WRITE(V1){
  digitalWrite(D1,param.asInt());
  digitalWrite(D4,param.asInt());
}

BLYNK_WRITE(V2){
  //From Joystick in Blynk App
  x_axis = param[0].asInt();
  y_axis = param[1].asInt();
  
  //Check for axes from joystick
  if(y_axis > 512){
    //Forward
    digitalWrite(MOTOR_A_IN_1,LOW);
    digitalWrite(MOTOR_A_IN_2,HIGH);
    digitalWrite(MOTOR_B_IN_3,LOW);
    digitalWrite(MOTOR_B_IN_4,HIGH);

    if(x_axis > 768){
      //Turn Right
      analogWrite(MOTOR_A_EN,1023);
      analogWrite(MOTOR_B_EN,511);
    }
    else if(x_axis < 256){
      //Turn Left
      analogWrite(MOTOR_A_EN,511);
      analogWrite(MOTOR_B_EN,1023);
    }
    else{
      //Return Default
      analogWrite(MOTOR_A_EN,1023);
      analogWrite(MOTOR_B_EN,1023);
    }
  }
  
  else if(y_axis < 512){
    //Backward
    digitalWrite(MOTOR_A_IN_1,HIGH);
    digitalWrite(MOTOR_A_IN_2,LOW);
    digitalWrite(MOTOR_B_IN_3,HIGH);
    digitalWrite(MOTOR_B_IN_4,LOW);

    if(x_axis > 768){
      //Turn Right
      analogWrite(MOTOR_A_EN,1023);
      analogWrite(MOTOR_B_EN,511);
    }
    else if(x_axis < 256){
      //Turn Left
      analogWrite(MOTOR_A_EN,511);
      analogWrite(MOTOR_B_EN,1023);
    }
    else{
      //Return Default
      analogWrite(MOTOR_A_EN,1023);
      analogWrite(MOTOR_B_EN,1023);
    }
  }
  
  else{
    //Centered
    digitalWrite(MOTOR_A_IN_1,LOW);
    digitalWrite(MOTOR_A_IN_2,LOW);
    digitalWrite(MOTOR_B_IN_3,LOW);
    digitalWrite(MOTOR_B_IN_4,LOW);
  }
  
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  //Motor A
  pinMode(MOTOR_A_EN,OUTPUT);
  pinMode(MOTOR_A_IN_1,OUTPUT);
  pinMode(MOTOR_A_IN_2,OUTPUT);
  //Motor B
  pinMode(MOTOR_B_EN,OUTPUT);
  pinMode(MOTOR_B_IN_3,OUTPUT);
  pinMode(MOTOR_B_IN_4,OUTPUT);
}

void loop()
{
  Blynk.run();
}
