#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#define PORT1_PWB 12
#define PORT1_B1 34
#define PORT1_B2 35
#define PORT2_PWB 8
#define PORT2_B1 37
#define PORT2_B2 36
#define PORT3_PWB 9
#define PORT3_B1 43
#define PORT3_B2 42
#define PORT4_PWB 5
#define PORT4_B1 39
#define PORT4_B2 29
#define input_A12 A12
#define input_A13 A13
#define input_A14 A14
#define input_A15 A15

#include <MeMegaPi.h>
void setup() {
  // put your setup code here, to run once:
  pinMode(input_A12, INPUT);
  pinMode(input_A13, INPUT);
  pinMode(input_A14, INPUT);
  pinMode(input_A15, INPUT);

  pinMode(PORT1_PWB, OUTPUT);
  pinMode(PORT1_B1, OUTPUT);
  pinMode(PORT1_B2, OUTPUT);

  pinMode(PORT2_PWB, OUTPUT);
  pinMode(PORT2_B1, OUTPUT);
  pinMode(PORT2_B2, OUTPUT);

  pinMode(PORT3_PWB, OUTPUT);
  pinMode(PORT3_B1, OUTPUT);
  pinMode(PORT3_B2, OUTPUT);

  pinMode(PORT4_PWB, OUTPUT);
  pinMode(PORT4_B1, OUTPUT);
  pinMode(PORT4_B2, OUTPUT);

}
void loop() {
  int input_A12_quickshot = analogRead(input_A12);
  int input_A15_quickshot = analogRead(input_A15);
  if (input_A12_quickshot > input_A15_quickshot) {
    if (input_A12_quickshot > 503) {
      up();
    }
    else if (input_A12_quickshot < 500) {
    
    }
  }
  else if (input_A15_quickshot > input_A12_quickshot) {
    if (input_A15_quickshot > 503) {
      left();
    }
    else if (input_A15_quickshot < 500) {
      
    }
  }
  }
}
void up() {
  int input_A12_map = map( analogRead(input_A12), 502, 920, 0, 255);
  digitalWrite(PORT1_B1, HIGH);
  digitalWrite(PORT1_B2, LOW);
  analogWrite(PORT1_PWB, input_A12_map );

  digitalWrite(PORT4_B1, HIGH);
  digitalWrite(PORT4_B2, LOW);
  analogWrite(PORT4_PWB, input_A12_map);

  digitalWrite(PORT2_B1, LOW);
  digitalWrite(PORT2_B2, HIGH);
  analogWrite(PORT2_PWB, input_A12_map);

  digitalWrite(PORT3_B1, HIGH);
  digitalWrite(PORT3_B2, LOW);
  analogWrite(PORT3_PWB, input_A12_map);
}
void down() {
  int input_A12_map = map( analogRead(input_A12), 110, 502, 255, 0);
  digitalWrite(PORT1_B1, LOW);
  digitalWrite(PORT1_B2, HIGH);
  analogWrite(PORT1_PWB, input_A12_map );

  digitalWrite(PORT4_B1, LOW);
  digitalWrite(PORT4_B2, HIGH);
  analogWrite(PORT4_PWB, input_A12_map);

  digitalWrite(PORT2_B1, HIGH);
  digitalWrite(PORT2_B2, LOW);
  analogWrite(PORT2_PWB, input_A12_map);

  digitalWrite(PORT3_B1, LOW);
  digitalWrite(PORT3_B2, HIGH);
  analogWrite(PORT3_PWB, input_A12_map);
}
void left() {
  int input_A15_map = map( analogRead(input_A15), 110, 502, 255, 0);
  digitalWrite(PORT1_B1, HIGH);
  digitalWrite(PORT1_B2, LOW);
  analogWrite(PORT1_PWB, input_A15_map );

  digitalWrite(PORT2_B1, HIGH);
  digitalWrite(PORT2_B2, LOW);
  analogWrite(PORT2_PWB, input_A15_map);

  digitalWrite(PORT3_B1, LOW);
  digitalWrite(PORT3_B2, HIGH);
  analogWrite(PORT3_PWB, input_A15_map);

  digitalWrite(PORT4_B1, HIGH);
  digitalWrite(PORT4_B2, LOW);
  analogWrite(PORT4_PWB, input_A15_map);
}
void right() {
  int input_A15_map = map( analogRead(input_A15), 502, 920, 0, 255);
  digitalWrite(PORT1_B1, LOW);
  digitalWrite(PORT1_B2, HIGH);
  analogWrite(PORT1_PWB, input_A15_map );

  digitalWrite(PORT2_B1, LOW);
  digitalWrite(PORT2_B2, HIGH);
  analogWrite(PORT2_PWB, input_A15_map);

  digitalWrite(PORT3_B1, HIGH);
  digitalWrite(PORT3_B2, LOW);
  analogWrite(PORT3_PWB, input_A15_map);

  digitalWrite(PORT4_B1, LOW);
  digitalWrite(PORT4_B2, HIGH);
  analogWrite(PORT4_PWB, input_A15_map);
}
