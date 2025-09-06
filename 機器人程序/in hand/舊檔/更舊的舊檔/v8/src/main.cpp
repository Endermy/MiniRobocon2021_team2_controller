#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMegaPi.h>
#include <math.h>

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

#define SERVO_PIN 26

#define JOYCON_Y A12
#define JOYCON_X A15
#define SHOULDER_L A6
#define SHOULDER_R A9

#define BUTTON_1 A15
#define BUTTON_2 A14
#define BUTTON_3 A11
#define BUTTON_4 A10
#define BUTTON_5 A7
#define BUTTON_6 A6

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
float x_input;
float y_input;
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
int y_max = 1;
int x_max = 1;
int save_area = 20;
float y_circle;
float x_circle;
float circle_feeter;
float radius;
float x_output;
float y_output;
float x_0;
float y_0;
int x_hl_judgment;
int x_de_hl_judgment;
int y_hl_judgment;
int y_de_hl_judgment;

Servo myservo;
int input, r;

void setup()
{
  myservo.attach(SERVO_PIN);

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

void readController()
{
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

  Serial.print("joyconY");
  Serial.print("\t");
  Serial.print(joyconY);
  Serial.print("\t");
  Serial.print("joyconX");
  Serial.print("\t");
  Serial.print(joyconX);
  Serial.print("\t");

  Serial.print(x_input);
  Serial.print("\t");
  Serial.print(y_input);
  Serial.print("\t");

  // Serial.print(shoulderL);
  // Serial.print("\t");
  // Serial.print(shoulderR);
  // Serial.print("\t");

  Serial.print(radius);
  Serial.print("\t");
  Serial.print(circle_feeter);
  Serial.print("\t");

  Serial.print(y_output);
  Serial.print("\t");
  Serial.print(x_output);
  Serial.print("\n");
  // Serial.print(button1);
  // Serial.print("\t");
  // Serial.print(button2);
  // Serial.print("\t");
  // Serial.print(button3);
  // Serial.print("\t");
  // Serial.print(button4);
  // Serial.print("\t");
  // Serial.print(button5);
  // Serial.print("\t");
  // Serial.println(button6);
}

uint8_t tryButtons()
{

  uint8_t buttonPressed = 0;

  if (button1 == LOW)
  {
    myservo.write(0);
    buttonPressed = 1;
  }
  if (button2 == LOW)
  {
    myservo.write(27);
    buttonPressed = 1;
  }
  if (button3 == LOW)
  {

    buttonPressed = 1;
  }
  if (button4 == LOW)
  {
    buttonPressed = 1;
  }
  if (button5 == LOW)
  {
    //do something
    buttonPressed = 1;
  }
  if (button6 == LOW)
  {
    //do something
    buttonPressed = 1;
  }
  return buttonPressed;
}

void let_xy_be_negative_one_to_positive_one()
{
  if (joyconX > 540)
  {
    x_input = double(joyconX - 540) * (1 - 0) / (930 - 540) + 0;
    //(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
  else if (joyconX < 508)
  {
    x_input = double(joyconX - 130) * (0 + 1) / (508 - 130) - 1;
    //(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
  else
  {
    x_input = 0;
  }

  if (joyconY > 530)
  {
    y_input = double(joyconY - 530) * (1 - 0) / (930 - 530) + 0;
    //(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
  else if (joyconY < 480)
  {
    y_input = (double(joyconY-130) / (480-130) - 1);
    // (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
  else
  {
    y_input = 0;
  }
}
void Positive_and_negative_judgment()
{
  if (x_output > 0)
  {
    x_hl_judgment = 1;
    x_de_hl_judgment = 0;
  }
  else if (x_output < 0)
  {
    x_hl_judgment = 0;
    x_de_hl_judgment = 1;
  }
  if (y_output > 0)
  {
    y_hl_judgment = 1;
    y_de_hl_judgment = 0;
  }
  else if (y_output < 0)
  {
    y_hl_judgment = 0;
    y_de_hl_judgment = 1;
  }
}

void triangle_to_circle()
{
  let_xy_be_negative_one_to_positive_one();
  x_circle = x_input / x_max;
  y_circle = y_input / y_max;
  circle_feeter = atan2(x_circle, y_circle);
  radius = max(abs(x_circle), abs(y_circle));
}

void circle_to_triangle()
{
  triangle_to_circle();
  x_0 = radius * sin(circle_feeter -PI/4);
  y_0 = radius * cos(circle_feeter -PI/4);
  x_output = x_0 / max(abs(x_0), abs(y_0)) * radius * 255;
  y_output = y_0 / max(abs(x_0), abs(y_0)) * radius * 255;
}

void move()
{
  circle_to_triangle();
  Positive_and_negative_judgment();
  digitalWrite(PORT1_B1, x_hl_judgment);
  digitalWrite(PORT1_B2, x_de_hl_judgment);
  analogWrite(PORT1_PWB, abs(x_output));

  digitalWrite(PORT2_B1, x_hl_judgment);
  digitalWrite(PORT2_B2, x_de_hl_judgment);
  analogWrite(PORT2_PWB, abs(x_output));

  digitalWrite(PORT3_B1, y_de_hl_judgment);
  digitalWrite(PORT3_B2, y_hl_judgment);
  analogWrite(PORT3_PWB, abs(y_output));

  digitalWrite(PORT4_B1, y_de_hl_judgment);
  digitalWrite(PORT4_B2, y_hl_judgment);
  analogWrite(PORT4_PWB, abs(y_output));
}

void loop()
{
  move();
  readController();
}
