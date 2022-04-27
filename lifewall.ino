//	2018 Daniel Strebkov
//
//	https://gitlab.com/maddsua
//	https://github.com/maddsua

#include <OneWire.h>
OneWire ds(7);

int bright = (A4);
int water = (A5);
int light = 11;
int pump = 12;
int buzz = 13;

void setup() {

  Serial.begin(9600);

  pinMode(light, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(buzz, OUTPUT);

  delay(128);
  tone(buzz, 800);
  delay(300);
  noTone(buzz);

  Serial.println("---");
  Serial.println("Started");
  delay(1000);
}

void loop() {

  Serial.println("---");
  delay(1000);

  byte data[2];
  ds.reset();
  ds.write(0xCC);
  ds.write(0x44);
  delay(750);
  ds.reset();
  ds.write(0xCC);
  ds.write(0xBE);
  data[0] = ds.read();
  data[1] = ds.read();
  int temp = (data[1] << 8) + data[0];
  temp = temp >> 4;

  Serial.print("Temperature ");
  Serial.print(temp);
  Serial.println(" *C");

  int humidity = analogRead(water)/10;
  int light = analogRead(bright)/10;

  Serial.print("Lghting ");
  Serial.print(light);
  Serial.print(" % | ");

  if (light < 50) {
    Serial.println("Backlight is active");
    digitalWrite(light, HIGH);
  }
  else {
    Serial.println("Daylight");
    digitalWrite(light, LOW);
  }

  Serial.print("Humidity ");
  Serial.print(humidity);
  Serial.print(" % | ");

  if (humidity > 60) {
    Serial.println("Wet");
    digitalWrite(pump, LOW);
  }

  else {
    Serial.println("Pump actived");
    digitalWrite(pump, HIGH);
  }

}




