/*
    gazoanalizator
*/
#include <SPI.h>
#include <SD.h>
#include <SHT1x.h>

const int chipSD = 53;
const int ledPin = 13;
#define dataPin  A7
#define clockPin A6
SHT1x sht1x(dataPin, clockPin);
void setup()
{
  Serial.begin(9600);            // Задаем скорость передачи данных
  while (!Serial) {
    ;
  }
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSD)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
  Serial.println("Warming-UP");
  delay(6000);
  Serial.println("Measurement");
  pinMode(ledPin, OUTPUT);
  String dataString = "MQ6;MQ7;MQ9;MQ135;T;H\n";
  WriteToFile(dataString);
}

// the loop function runs over and over again forever
void loop()
{
  String dataString = "";
  for (int i = 2; i <= 5; i++) {
    delay(1000);
    int value = analogRead(i);
    dataString += String(value) + ";";
  }
  dataString += String(sht1x.readTemperatureC()) + ";";
  dataString += String(sht1x.readHumidity()) + ";";

  WriteToFile(dataString);
}

void WriteToFile(String dataString) {
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}
