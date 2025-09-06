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

#define JOYCON_Y A12
#define JOYCON_X A15
#define SHOULDER_L A0
#define SHOULDER_R A3

#define BUTTON_1 51
#define BUTTON_2 52
#define BUTTON_3 A6
#define BUTTON_4 A9
#define BUTTON_5 A11
#define BUTTON_6 A14

#define JOYCON_Y_MAX 917
#define JOYCON_Y_MID 504
#define JOYCON_Y_MIN 110
#define JOYCON_X_MAX 904
#define JOYCON_X_MID 497
#define JOYCON_X_MIN 116
#define JOYCON_DEADZONE 50

#define SHOULDER_L_MAX 1019
#define SHOULDER_L_MIN 3
#define SHOULDER_R_MAX 1019
#define SHOULDER_R_MIN 3
#define SHOULDER_DEADZONE 20

#define MAX_SPEED 255

int joyconY;
int joyconX;
int shoulderL;
int shoulderR;
int button1;
int button2;
int button3;
int button4;
int button5;
int button6;

void setup() {

  pinMode(JOYCON_Y, INPUT);
  pinMode(JOYCON_X, INPUT);
  pinMode(SHOULDER_L, INPUT);
  pinMode(SHOULDER_R, INPUT);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);
  pinMode(BUTTON_5, INPUT_PULLUP);
  pinMode(BUTTON_6, INPUT_PULLUP);

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

  Serial.begin(9600);

}

void readController() {
  joyconY = analogRead(JOYCON_Y);
  joyconX = analogRead(JOYCON_X);
  shoulderL = analogRead(SHOULDER_L);
  shoulderR = analogRead(SHOULDER_R);
  button1 = digitalRead(BUTTON_1);
  button2 = digitalRead(BUTTON_2);
  button3 = digitalRead(BUTTON_3);
  button4 = digitalRead(BUTTON_4);
  button5 = digitalRead(BUTTON_5);
  button6 = digitalRead(BUTTON_6);

  Serial.print(joyconY);
  Serial.print("\t");
  Serial.print(joyconX);
  Serial.print("\t");

  Serial.print(shoulderL);
  Serial.print("\t");
  Serial.print(shoulderR);
  Serial.print("\t");

  Serial.print(button1);
  Serial.print("\t");
  Serial.print(button2);
  Serial.print("\t");
  Serial.print(button3);
  Serial.print("\t");
  Serial.print(button4);
  Serial.print("\t");
  Serial.print(button5);
  Serial.print("\t");
  Serial.println(button6);
}

void move() {

  if (joyconY > JOYCON_Y_MID + JOYCON_DEADZONE ) {
    up(map(joyconY, JOYCON_Y_MID + JOYCON_DEADZONE, JOYCON_Y_MAX, 0, MAX_SPEED));
    return;
  }
  if (joyconY < JOYCON_Y_MID - JOYCON_DEADZONE) {
    down(map(joyconY, JOYCON_Y_MID - JOYCON_DEADZONE, JOYCON_Y_MIN, 0, MAX_SPEED));
    return;
  }
  if (joyconX > JOYCON_X_MID + JOYCON_DEADZONE) {
    left(map(joyconX, JOYCON_X_MID + JOYCON_DEADZONE, JOYCON_X_MAX, 0, MAX_SPEED));
    return;
  }
  if (joyconX < JOYCON_X_MID - JOYCON_DEADZONE) {
    right(map(joyconX, JOYCON_X_MID - JOYCON_DEADZONE, JOYCON_X_MIN, 0, MAX_SPEED));
    return;
  }
  if (shoulderL < SHOULDER_L_MAX - SHOULDER_DEADZONE || shoulderR < SHOULDER_R_MAX - SHOULDER_DEADZONE) {
    if (shoulderL > shoulderR)
    {
      t_left(map(shoulderR - shoulderL, SHOULDER_R_MAX - SHOULDER_L_MIN, 0, 0, MAX_SPEED));
    }else{
      t_right(map(shoulderL - shoulderR, SHOULDER_L_MAX - SHOULDER_R_MIN, 0, 0, MAX_SPEED));
    }
    return;
  }
  t_stop();
  return;

}

void loop() {
  readController();
  move();
}

void up(uint8_t speed) {
  digitalWrite(PORT1_B1, HIGH);
  digitalWrite(PORT1_B2, LOW);
  analogWrite(PORT1_PWB, speed);

  digitalWrite(PORT2_B1, HIGH);
  digitalWrite(PORT2_B2, LOW);
  analogWrite(PORT2_PWB, speed);

  digitalWrite(PORT3_B1, HIGH);
  digitalWrite(PORT3_B2, LOW);
  analogWrite(PORT3_PWB, speed);

  digitalWrite(PORT4_B1, HIGH);
  digitalWrite(PORT4_B2, LOW);
  analogWrite(PORT4_PWB, speed);
}

void down(uint8_t speed) {
  digitalWrite(PORT1_B1, LOW);
  digitalWrite(PORT1_B2, HIGH);
  analogWrite(PORT1_PWB, speed);

  digitalWrite(PORT2_B1, LOW);
  digitalWrite(PORT2_B2, HIGH);
  analogWrite(PORT2_PWB, speed);

  digitalWrite(PORT3_B1, LOW);
  digitalWrite(PORT3_B2, HIGH);
  analogWrite(PORT3_PWB, speed);

  digitalWrite(PORT4_B1, LOW);
  digitalWrite(PORT4_B2, HIGH);
  analogWrite(PORT4_PWB, speed);
}

void left(uint8_t speed) {
  digitalWrite(PORT1_B1, HIGH);
  digitalWrite(PORT1_B2, LOW);
  analogWrite(PORT1_PWB, speed);

  digitalWrite(PORT2_B1, LOW);
  digitalWrite(PORT2_B2, HIGH);
  analogWrite(PORT2_PWB, speed);

  digitalWrite(PORT3_B1, LOW);
  digitalWrite(PORT3_B2, HIGH);
  analogWrite(PORT3_PWB, speed);

  digitalWrite(PORT4_B1, HIGH);
  digitalWrite(PORT4_B2, LOW);
  analogWrite(PORT4_PWB, speed);
}

void right(uint8_t speed) {
  digitalWrite(PORT1_B1, LOW);
  digitalWrite(PORT1_B2, HIGH);
  analogWrite(PORT1_PWB, speed);

  digitalWrite(PORT2_B1, HIGH);
  digitalWrite(PORT2_B2, LOW);
  analogWrite(PORT2_PWB, speed);

  digitalWrite(PORT3_B1, HIGH);
  digitalWrite(PORT3_B2, LOW);
  analogWrite(PORT3_PWB, speed);

  digitalWrite(PORT4_B1, LOW);
  digitalWrite(PORT4_B2, HIGH);
  analogWrite(PORT4_PWB, speed);
}

void t_left(uint8_t speed) {
  digitalWrite(PORT1_B1, HIGH);
  digitalWrite(PORT1_B2, LOW);
  analogWrite(PORT1_PWB, speed);

  digitalWrite(PORT2_B1, LOW);
  digitalWrite(PORT2_B2, HIGH);
  analogWrite(PORT2_PWB, speed);

  digitalWrite(PORT3_B1, HIGH);
  digitalWrite(PORT3_B2, LOW);
  analogWrite(PORT3_PWB, speed);

  digitalWrite(PORT4_B1, LOW);
  digitalWrite(PORT4_B2, HIGH);
  analogWrite(PORT4_PWB, speed);
  
}
void t_right(uint8_t speed) {
  digitalWrite(PORT1_B1, LOW);
  digitalWrite(PORT1_B2, HIGH);
  analogWrite(PORT1_PWB, speed);

  digitalWrite(PORT2_B1, HIGH);
  digitalWrite(PORT2_B2, LOW);
  analogWrite(PORT2_PWB, speed);

  digitalWrite(PORT3_B1, LOW);
  digitalWrite(PORT3_B2, HIGH);
  analogWrite(PORT3_PWB, speed);

  digitalWrite(PORT4_B1, HIGH);
  digitalWrite(PORT4_B2, LOW);
  analogWrite(PORT4_PWB, speed);
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
