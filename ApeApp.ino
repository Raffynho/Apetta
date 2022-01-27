#include <SoftwareSerial.h>

int enable = 8;
int in1 = 4;
int in2 = 5;
int in3 = 6;
int in4 = 7;

int distanza;
int triggerPort = 2;
int echoPort = 3;

#define   RX  0
#define   TX  1
SoftwareSerial mySerial(RX, TX);
char Ch;

void setup() {

  pinMode(enable, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(triggerPort, OUTPUT );
  pinMode(echoPort, INPUT );

  mySerial.begin(9600);
  Serial.begin(9600);
}

void Sensore() {
  unsigned long durata = 0;
  digitalWrite(triggerPort, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPort, LOW);
  durata = pulseIn(echoPort, HIGH);
  distanza = durata / 58;

  Serial.print(" distanza = ");
  Serial.println(distanza);
}

void Indietro() {
  digitalWrite(enable, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void Avanti() {
  digitalWrite(enable, HIGH);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void Stop() {
  digitalWrite(enable, LOW);
}

void Destra() {
  digitalWrite(enable, HIGH);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void Sinistra() {
  digitalWrite(enable, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}


void Automatico() {
  Avanti();
  Sensore();
  if (distanza < 50) {
    Destra();
    delay(1000);
  }
}

void loop() {
  if (mySerial.available()) {
    Ch = mySerial.read();
  }
  if (Ch == 'W') {
    Automatico();
  }
  else if (Ch == 'A') {
    Avanti();
  }
  else if (Ch == 'D') {
    Destra();
  }
  else if (Ch == 'S') {
    Sinistra();
  }
  else if (Ch == 'I') {
    Indietro();
  }
  else if (Ch == 'H') {
    Stop();
  }
}






