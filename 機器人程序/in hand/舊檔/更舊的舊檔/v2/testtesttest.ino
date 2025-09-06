#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMegaPi.h>

#define PORT1_PWB 12
#define PORT1_B1 34
#define PORT1_B2 35
#define PORT2_PWB 8
#define PORT2_B1 36
#define PORT2_B2 37
#define PORT3_PWB 9
#define PORT3_B1 43
#define PORT3_B2 42
#define PORT4_PWB 5
#define PORT4_B1 39
#define PORT4_B2 29
#define input_joycon_y A12
#define input_joycon_x A13
#define input_A14 A14
#define input_A15 A15
#define input_A9 A9
#define input_A6 A6
#define input_52 52
int input_joycon_y_quickshot;
int input_joycon_x_quickshot;
int input_A9_quickshot;
int input_A6_quickshot;
int input_52_quickshot;
void setup() {
  pinMode(input_joycon_y, INPUT);
  pinMode(input_joycon_x, INPUT);
  pinMode(input_A14, INPUT);
  pinMode(input_A15, INPUT);
  pinMode(input_A9, INPUT);
  pinMode(input_A6, INPUT);
  pinMode(input_52, INPUT);

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

void move() {
  if (input_joycon_y_quickshot > 530 ) {
    up();
    return;
  }
  if (input_joycon_y_quickshot < 470) {
    down();
    return;
  }
  if (input_joycon_x_quickshot > 530) {
   t_left();
    return;
  }
  if (input_joycon_x_quickshot < 470) {
    t_right();
    return;
  }
  //  if (input_A9_quickshot == 1) {
  //    t_left();
  //    return;
  //  }
  //  if (input_52_quickshot == 1) {
  //    t_right();
  //    return;
  //  }
  t_stop();
  return;

}

void loop() {
 
   input_joycon_y_quickshot = analogRead(input_joycon_y);
   input_joycon_x_quickshot = analogRead(input_joycon_x);
   input_A9_quickshot = analogRead(input_A9);
   input_A6_quickshot = analogRead(input_A6);
   input_52_quickshot = analogRead(input_52);
    move();
}

void up() {
  int input_joycon_y_map = map(input_joycon_y_quickshot, 502, 1000, 0, 255);
  digitalWrite(PORT1_B1, HIGH);
  digitalWrite(PORT1_B2, LOW);
  analogWrite(PORT1_PWB, input_joycon_y_map );

  digitalWrite(PORT2_B1, HIGH);
  digitalWrite(PORT2_B2, LOW);
  analogWrite(PORT2_PWB, input_joycon_y_map);

  digitalWrite(PORT3_B1, HIGH);
  digitalWrite(PORT3_B2, LOW);
  analogWrite(PORT3_PWB, input_joycon_y_map);

  digitalWrite(PORT4_B1, HIGH);
  digitalWrite(PORT4_B2, LOW);
  analogWrite(PORT4_PWB, input_joycon_y_map);
}
void down() {
  int input_joycon_y_map = map(input_joycon_y_quickshot, 110, 502, 255, 0);
  digitalWrite(PORT1_B1, LOW);
  digitalWrite(PORT1_B2, HIGH);
  analogWrite(PORT1_PWB, input_joycon_y_map );

  digitalWrite(PORT2_B1, LOW);
  digitalWrite(PORT2_B2, HIGH);
  analogWrite(PORT2_PWB, input_joycon_y_map);

  digitalWrite(PORT3_B1, LOW);
  digitalWrite(PORT3_B2, HIGH);
  analogWrite(PORT3_PWB, input_joycon_y_map);

  digitalWrite(PORT4_B1, LOW);
  digitalWrite(PORT4_B2, HIGH);
  analogWrite(PORT4_PWB, input_joycon_y_map);}
void left() {
  int input_joycon_x_map = map(input_joycon_x_quickshot, 520, 1000, 0, 255);
  digitalWrite(PORT1_B1, HIGH);
  digitalWrite(PORT1_B2, LOW);
  analogWrite(PORT1_PWB, input_joycon_x_map );

  digitalWrite(PORT2_B1, LOW);
  digitalWrite(PORT2_B2, HIGH);
  analogWrite(PORT2_PWB, input_joycon_x_map);

  digitalWrite(PORT3_B1, LOW);
  digitalWrite(PORT3_B2, HIGH);
  analogWrite(PORT3_PWB,input_joycon_x_map);

  digitalWrite(PORT4_B1, HIGH);
  digitalWrite(PORT4_B2, LOW);
  analogWrite(PORT4_PWB,input_joycon_x_map);
}
void right() {
  int input_joycon_x_map = map(input_joycon_x_quickshot, 110, 502, 255, 0);
  digitalWrite(PORT1_B1, LOW);
  digitalWrite(PORT1_B2, HIGH);
  analogWrite(PORT1_PWB,input_joycon_x_map );

  digitalWrite(PORT2_B1, HIGH);
  digitalWrite(PORT2_B2, LOW);
  analogWrite(PORT2_PWB,input_joycon_x_map);

  digitalWrite(PORT3_B1, HIGH);
  digitalWrite(PORT3_B2, LOW);
  analogWrite(PORT3_PWB, input_joycon_x_map);

  digitalWrite(PORT4_B1, LOW);
  digitalWrite(PORT4_B2, HIGH);
  analogWrite(PORT4_PWB,input_joycon_x_map);
}
void t_left() {
  digitalWrite(PORT1_B1, HIGH);
  digitalWrite(PORT1_B2, LOW);
  analogWrite(PORT1_PWB, 100 );

  digitalWrite(PORT2_B1, LOW);
  digitalWrite(PORT2_B2, HIGH);
  analogWrite(PORT2_PWB, 100);

  digitalWrite(PORT3_B1, HIGH);
  digitalWrite(PORT3_B2, LOW);
  analogWrite(PORT3_PWB, 100);

  digitalWrite(PORT4_B1, LOW);
  digitalWrite(PORT4_B2, HIGH);
  analogWrite(PORT4_PWB, 100);
}
void t_right() {
  digitalWrite(PORT1_B1, LOW);
  digitalWrite(PORT1_B2, HIGH);
  analogWrite(PORT1_PWB, 100 );

  digitalWrite(PORT2_B1, HIGH);
  digitalWrite(PORT2_B2, LOW);
  analogWrite(PORT2_PWB, 100);

  digitalWrite(PORT3_B1, LOW);
  digitalWrite(PORT3_B2, HIGH);
  analogWrite(PORT3_PWB, 100);

  digitalWrite(PORT4_B1, HIGH);
  digitalWrite(PORT4_B2, LOW);
  analogWrite(PORT4_PWB, 100);
}
void t_stop() {
  digitalWrite(PORT1_B1, LOW);
  digitalWrite(PORT1_B2, LOW);
  analogWrite(PORT1_PWB, 0 );

  digitalWrite(PORT2_B1, LOW);
  digitalWrite(PORT2_B2, LOW);
  analogWrite(PORT2_PWB, 0);

  digitalWrite(PORT3_B1, LOW);
  digitalWrite(PORT3_B2, LOW);
  analogWrite(PORT3_PWB, 0);

  digitalWrite(PORT4_B1, LOW);
  digitalWrite(PORT4_B2, LOW);
  analogWrite(PORT4_PWB, 0);
}
