/*
  Created by TEOS
  Domotic with Arduino https://goo.gl/btZpjs
  YouTube https://goo.gl/k7TUSZ
  Instagram https://goo.gl/zEIjia
  Facebook https://goo.gl/eivraR
  Twitter https://goo.gl/du5Wgn
  Github https://goo.gl/Xl5IiS
  WEB https://www.proyecto-teos.com
*/

#include <SoftwareSerial.h>
SoftwareSerial serialColorT(2, 3);

String inputStringT, sensorStringT;
bool inputStringCompleteT, sensorStringCompleteT;

void setup() {
  Serial.begin(9600);
  serialColorT.begin(9600);
  inputStringT.reserve(10);
  sensorStringT.reserve(30);
}

void serialEvent() {
  inputStringT = Serial.readStringUntil(13);
  inputStringCompleteT = true;
}


void loop() {
  if (inputStringCompleteT) {
    serialColorT.print(inputStringT);
    serialColorT.print('\r');
    inputStringT = "";
    inputStringCompleteT = false;
  }
  if (serialColorT.available() > 0) {
    char inCharT = (char)serialColorT.read();
    sensorStringT += inCharT;
    if (inCharT == '\r')
      sensorStringCompleteT = true;
  }
  if (sensorStringCompleteT == true) {
    if (isdigit(sensorStringT[0]) == false)
      Serial.print("");
    else
      Serial.println(printRGBDataT());
    sensorStringT = "";
    sensorStringCompleteT = false;
  }
}

String printRGBDataT() {
  char sensorStringArrayT[30];
  char *redT, *greenT, *blueT;
  String resultSerial;
  sensorStringT.toCharArray(sensorStringArrayT, 30);
  redT = strtok(sensorStringArrayT, ",");
  greenT = strtok(NULL, ",");
  blueT = strtok(NULL, ",");
  return resultSerial = ("Red: " + String(redT) + "  || Green: " + String(greenT) + " || Blue: " + String(blueT));
}
