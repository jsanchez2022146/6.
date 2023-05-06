#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
#include <OneWire.h>
int bomba = 2;
RTC_DS3231 reloj;
#define pinbuzzer 8
#define ONE_WIRE_BUS 3
LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);



void setup() { 
  Serial.begin(9600);
pinMode(bomba,OUTPUT);
lcd.init();
 lcd.backlight();
 lcd.clear();
if (! reloj.begin()) {
Serial.println("Modulo RTC no encontrado !");
while (1);
}
reloj.adjust(DateTime(__DATE__, __TIME__));
}



void loop() {
DateTime fecha = reloj.now();

Serial.print(" ");
Serial.print(fecha.hour());
Serial.print(":");
Serial.print(fecha.minute());
Serial.print(":");
Serial.println(fecha.second());
Serial.print(fecha.day());
Serial.print("/");
Serial.print(fecha.month());
Serial.print("/");
Serial.print(fecha.year());

delay(1000);

if(fecha.minute() == 37){
lcd.clear();
lcd.setCursor(0, 0);
 lcd.print("tirando el agua");
tone(pinbuzzer, 1000);
delay(1000);
noTone(pinbuzzer);
delay(1000);
digitalWrite(bomba,LOW);}

if(fecha.minute() < 37 ||fecha.minute() > 37){//se pone el rango para ver a que hora no regara
lcd.clear();
lcd.setCursor(0, 0); // X, Y
lcd.print("aun no es tiempo");
delay(500);
lcd.clear();
sensors.requestTemperatures();
lcd.print(sensors.getTempCByIndex(0),1);
 digitalWrite(bomba,HIGH);
}
}