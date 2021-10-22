#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(9,10); 
LiquidCrystal_I2C lcd(0x27,16,2);
int MQ2gas;
int MQ135gas;
String message;
int buzzer = 12;
void setup() {
  lcd.begin();
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(buzzer,OUTPUT);
}

void loop() {
  MQ2gas = analogRead(A1);
  MQ135gas = analogRead(A2);
  Serial.print("MQ-2 amount: ");
  Serial.println(MQ2gas);
  Serial.print("MQ-135 amount: ");
  Serial.println(MQ135gas);
  lcd.print("MQ2=");
  lcd.print(MQ2gas);
  lcd.print("MQ135=");
  lcd.print(MQ135gas);
  if(MQ2gas>450 or MQ135gas>250)
  {
    SendMessage();
    digitalWrite(buzzer,HIGH);
    MQ2gas = 0;
    MQ135gas = 0;
  }
  else
  {
    digitalWrite(buzzer,LOW);
  }
  delay(500);
  lcd.clear();
}

void SendMessage(){
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CMGS=\"+8801772744545\"\r");
  delay(1000);
  mySerial.print("Hazardous Gas amounts in the air are at dangerous level. Immediate actions needs to be taken.");
  delay(100);
  mySerial.println(char(26));
  delay(5000);
}
