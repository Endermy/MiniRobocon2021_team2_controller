#include <JY901.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMegaPi.h>
#include <math.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define DELAYVAL 500
#define colour pixels.Color(0, 0, 0)
#define Colour2 pixels.Color(100, 36, 0)
#define Colour3 pixels.Color(75, 0, 0)
#define Colour4 pixels.Color(75, 0, 75)
#define PORT1_PWB 11
#define PORT1_B1 32
#define PORT1_B2 33
#define PORT2_PWB 4
#define PORT2_B1 35
#define PORT2_B2 34
#define PORT3_PWB 8
#define PORT3_B1 37
#define PORT3_B2 36
#define PORT4_PWB 10
#define PORT4_B1 30
#define PORT4_B2 31
#define SERVO_PIN A8

#define JOYCON_Y A2
#define JOYCON_X A3
#define shoulderL_PIN A0
#define shoulderR_PIN A1

#define BUTTON_1 49
#define BUTTON_2 48
#define BUTTON_3 47
#define BUTTON_4 46
#define BUTTON_5 45
#define BUTTON_6 44
#define BUTTON_7 43
#define BUTTON_8 42
#define SWITCH_1 38
#define SWITCH_2 39
#define SWITCH_3 40 //1 is up (lock) 0 is down (unlock)
#define SWITCH_4 41 //1 is up (leftside) 0 is down (rightside)

#define L_turning_MIN 0
#define L_turning_MAX 255
#define R_turning_MIN 0
#define R_turning_MAX 255
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
#define kp 3
#define ki 0
#define kd 9
//3，0，9
// 2.5，0.5，4
#define Motor_Left_Up A4
#define Motor_Left_Dw A5
#define Motor_Left_pwm 9
#define Motor_Right_Up A6
#define Motor_Right_Dw A7
#define Motor_Right_pwm 10

#define motorballR_pin1 A4
#define motorballR_pin2 A5
#define motorballR_pwm 9

#define motorballL_pin1 A6
#define motorballL_pin2 A7
#define motorballL_pwm 5 //FLball

unsigned long time, time2;
int incomingByte = 0;
int ledPin[25] = {1, 0, 0, 0, 1,
                  0, 1, 0, 1, 0,
                  0, 0, 1, 0, 0,
                  0, 1, 0, 1, 0,
                  1, 0, 0, 0, 1};
int ledPin2[25] = {0, 1, 1, 1, 0,
                   1, 0, 0, 0, 1,
                   1, 0, 1, 0, 1,
                   1, 0, 0, 0, 1,
                   0, 1, 1, 1, 0};
int ledPinclose[25] = {0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0};
int ledPinlockoff[25] = {0, 0, 1, 0, 0,
                         0, 0, 1, 0, 0,
                         1, 1, 1, 1, 1,
                         0, 0, 1, 0, 0,
                         0, 0, 1, 0, 0};
int kick_ball_on = 0;
double get_initial_yaw_waiting;
double a_base_speed;
double b_base_speed;
int L_turning;
int R_turning;
float x_input;
float y_input;
int joyconX;
int joyconY;
int shoulderL;
int shoulderR;
int button1;
int button2;
int button3;
int button4;
int button5;
int button6;
int button7;
int button8;
int switch_1;
int switch_2;
int switch_3;
int switch_4;
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
int x_hl_judgment_line[4]{1};
int y_hl_judgment_line[4]{1};
int run_time[4]{10000};
int round_1 = 0;
Servo myservo;
int input, r;
double yaw_recoup;
double yaw_error;
double yaw_error_history;
double yaw_integral;
double speed_recoup_a;
double speed_recoup_b;
double initial_yaw;
double recoup_speed;
int Gyro_on;
int only_y_on;

void LEDON()
{
  digitalWrite(6, 1);
}

void LEDOFF()
{
  digitalWrite(6, 0);
}

void Buzzer()
{
  digitalWrite(8, 1);
  delay(100);

  digitalWrite(8, 0);
  delay(100);
}

void get_initial_yaw()
{
  get_initial_yaw_waiting = millis() + 1000;
  while (millis() <= get_initial_yaw_waiting)
  {
    JY901.receiveSerialData();
    initial_yaw = JY901.getYaw();
  }
}

void fix_initial_yaw()
{
  initial_yaw = JY901.getYaw();
}

void setup()
{
  Serial.begin(9600);

  Serial2.begin(9600);
  JY901.attach(Serial2);

  myservo.attach(SERVO_PIN);

  pinMode(JOYCON_Y, INPUT);
  pinMode(JOYCON_X, INPUT);
  pinMode(shoulderL_PIN, INPUT);
  pinMode(shoulderR_PIN, INPUT);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);
  pinMode(BUTTON_5, INPUT_PULLUP);
  pinMode(BUTTON_6, INPUT_PULLUP);
  pinMode(BUTTON_7, INPUT_PULLUP);
  pinMode(BUTTON_8, INPUT_PULLUP);
  pinMode(SWITCH_1, INPUT_PULLUP);
  pinMode(SWITCH_2, INPUT_PULLUP);
  pinMode(SWITCH_3, INPUT_PULLUP);
  pinMode(SWITCH_4, INPUT_PULLUP);

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

  pinMode(Motor_Left_Up, OUTPUT);
  pinMode(Motor_Left_Dw, OUTPUT);
  pinMode(Motor_Left_pwm, OUTPUT);
  pinMode(Motor_Right_Up, OUTPUT);
  pinMode(Motor_Right_Dw, OUTPUT);
  pinMode(Motor_Right_pwm, OUTPUT);

  Serial.begin(9600);
  get_initial_yaw();
  myservo.write(170);
}

void readController()
{
  joyconY = analogRead(JOYCON_Y);
  joyconX = analogRead(JOYCON_X);
  shoulderL = analogRead(shoulderL_PIN);
  shoulderR = analogRead(shoulderR_PIN);
  button1 = digitalRead(BUTTON_1);
  button2 = digitalRead(BUTTON_2);
  button3 = digitalRead(BUTTON_3);
  button4 = digitalRead(BUTTON_4);
  button5 = digitalRead(BUTTON_5);
  button6 = digitalRead(BUTTON_6);
  button7 = digitalRead(BUTTON_7);
  button8 = digitalRead(BUTTON_8);
  switch_1 = digitalRead(SWITCH_1);
  switch_2 = digitalRead(SWITCH_2);
  switch_3 = digitalRead(SWITCH_3);
  switch_4 = digitalRead(SWITCH_4);
}

void tryButtons()
{

  // uint8_t buttonPressed = 0; //write sth.

  if (button1 == 0)
  {
    myservo.write(170);
    //buttonPressed = 1;
  }
  if (button2 == 0)
  {
    myservo.write(130);
    //buttonPressed = 1;
  }
  if (button3 == 0)
  {
    myservo.write(30);
    // buttonPressed = 1;
  }
  if (button4 == 0)
  {
    fix_initial_yaw();
    //buttonPressed = 1;
  }
  if (button5 == 0)
  {
    yaw_integral = 0;
    //buttonPressed = 1;
  }
  if (button6 == 0)
  {
  }
  if (button7 == 0)
  {
  }
  if (button8 == 0)
  {
    digitalWrite(Motor_Right_Up, 0);
    digitalWrite(Motor_Right_Dw, 1);
    analogWrite(Motor_Right_pwm, 180);
    //buttonPressed = 1;
  }
  if (switch_1 == 0)
  {
    Gyro_on = 0;
    yaw_integral = 0;
  }
  else
  {
    Gyro_on = 1;
  }
  if (switch_2 == 0)
  {
    /* code */
  }
  if (switch_3 == 0)
  {
    kick_ball_on = 1;
  }
  else
  {
    kick_ball_on = 0;
  }
  if (switch_4 == 0)
  {
    only_y_on = 1;
  }
  else
  {
    only_y_on = 0;
  }
  // return buttonPressed;
}

void get_error()
{

  if (initial_yaw - JY901.getYaw() > 180)
  {
    yaw_error = (initial_yaw - JY901.getYaw() - 360);
  }
  else if (initial_yaw - JY901.getYaw() < -180)
  {
    yaw_error = (initial_yaw - JY901.getYaw() + 360);
  }
  else
  {
    yaw_error = initial_yaw - JY901.getYaw();
  }

  yaw_integral += yaw_error;
  Serial.print("JY901.getYaw()");
  Serial.print(" ");
  Serial.print(JY901.getYaw());
  Serial.print(" ");
  Serial.print("initial_yaw");
  Serial.print(" ");
  Serial.print(initial_yaw);
  Serial.print(" ");
  Serial.print("yaw_integral");
  Serial.print(" ");
  Serial.print(yaw_integral);
  Serial.print(" ");
  Serial.print("yaw_error");
  Serial.print(" ");
  Serial.print(yaw_error);
  Serial.print(" ");
  Serial.print("yaw_recoup");
  Serial.print(" ");
  Serial.print(yaw_recoup);
  Serial.print(" ");
}

void pid()
{
  JY901.receiveSerialData();

  get_error();
  yaw_recoup = kp * yaw_error + ki * yaw_integral + kd * (yaw_error - yaw_error_history);
  // yaw_recoup = kp * yaw_error;
  // yaw_recoup = kp * yaw_error + ki * yaw_integral;
  yaw_error_history = yaw_error;
  recoup_speed = yaw_recoup;
}

void let_xy_be_negative_one_to_positive_one()
{
  if (joyconX > 550)
  {
    x_input = double(joyconX - 550) * (1 - 0) / (970 - 550) + 0;
    //(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
  else if (joyconX < 500)
  {
    x_input = double(joyconX - 90) * (0 + 1) / (500 - 90) - 1;
    //(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
  else
  {
    x_input = 0;
  }

  if (joyconY > 530)
  {
    y_input = double(joyconY - 530) * (1 - 0) / (970 - 530) + 0;
    //(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
  else if (joyconY < 470)
  {
    y_input = (double(joyconY - 100) / (470 - 100) - 1);
    // (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
  else
  {
    y_input = 0;
  }
}

void Positive_and_negative_judgment(int x_output, int y_output, int &x_hl_judgment, int &x_de_hl_judgment, int &y_hl_judgment, int &y_de_hl_judgment)
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
  x_0 = radius * sin(circle_feeter - PI / 4);
  y_0 = radius * cos(circle_feeter - PI / 4);
  Serial.print(circle_feeter);
  Serial.print("\t");
  x_output = x_0 / fmax(fabs(x_0), fabs(y_0)) * radius * 255;
  if (isnan(x_output))
    x_output = 0;
  // Serial.print("x_output");
  // Serial.print(x_output);
  // Serial.print("\t");

  y_output = y_0 / fmax(fabs(x_0), fabs(y_0)) * radius * 255;
  if (isnan(y_output))
    y_output = 0;
  // Serial.print("y_output");
  // Serial.print(y_output);
  // Serial.print("\t");
}

int get_turning_speed()
{
  // return  recoup_speed + map(shoulderL, 1024, 0, 0, 510) + map(shoulderR, 1024, 0, 0, -510);
  if (Gyro_on == 1)
  {
    return recoup_speed;
  }
  else if (Gyro_on == 0)
  {
    return map(shoulderR - shoulderL, 1024, -1024, 510, -510) / 4;
  }
}

void motor_speed_setting(int motor_number, int motor_speed)
{
  switch (motor_number)
  {
  case 1:
    if (motor_speed >= 0)
    {
      digitalWrite(PORT1_B1, 1);
      digitalWrite(PORT1_B2, 0);
      analogWrite(PORT1_PWB, abs(motor_speed));
    }
    else if (motor_speed < 0)
    {
      digitalWrite(PORT1_B1, 0);
      digitalWrite(PORT1_B2, 1);
      analogWrite(PORT1_PWB, abs(motor_speed));
    }
    break;
  case 2:
    if (motor_speed >= 0)
    {
      digitalWrite(PORT2_B1, 1);
      digitalWrite(PORT2_B2, 0);
      analogWrite(PORT2_PWB, abs(motor_speed));
    }
    else if (motor_speed < 0)
    {
      digitalWrite(PORT2_B1, 0);
      digitalWrite(PORT2_B2, 1);
      analogWrite(PORT2_PWB, abs(motor_speed));
    }
    break;
  case 3:
    if (motor_speed >= 0)
    {
      digitalWrite(PORT3_B1, 1);
      digitalWrite(PORT3_B2, 0);
      analogWrite(PORT3_PWB, abs(motor_speed));
    }
    else if (motor_speed < 0)
    {
      digitalWrite(PORT3_B1, 0);
      digitalWrite(PORT3_B2, 1);
      analogWrite(PORT3_PWB, abs(motor_speed));
    }
    break;
  case 4:
    if (motor_speed >= 0)
    {
      digitalWrite(PORT4_B1, 1);
      digitalWrite(PORT4_B2, 0);
      analogWrite(PORT4_PWB, abs(motor_speed));
    }
    else if (motor_speed < 0)
    {
      digitalWrite(PORT4_B1, 0);
      digitalWrite(PORT4_B2, 1);
      analogWrite(PORT4_PWB, abs(motor_speed));
    }
    break;

  default:
    break;
  }
}

float speed_planning(int c)
{
  int a;
  int b;

  switch (c)
  {
  case 1:
    if (x_output + get_turning_speed() > 255)
    {
      return 255;
      a = (x_output + get_turning_speed()) - (255);
    }
    else if (x_output + get_turning_speed() < -255)
    {
      return -255;
      a = (x_output + get_turning_speed()) - (-255);
    }
    else
    {
      return x_output + get_turning_speed() - a;
    }
    break;

  case 2:
    if (x_output - get_turning_speed() < -255)
    {
      return -255;
      a = (x_output - get_turning_speed()) - (-255);
    }
    else if (x_output - get_turning_speed() > 255)
    {
      return 255;
      a = (x_output - get_turning_speed()) - (255);
    }
    else
    {
      return x_output - get_turning_speed() - a;
    }
    break;

  case 3:
    if (y_output - get_turning_speed() < -255)
    {
      return -255;
      b = (y_output - get_turning_speed()) - (-255);
    }
    else if (y_output - get_turning_speed() > 255)
    {
      return 255;
      b = (y_output - get_turning_speed()) - (255);
    }
    else
    {
      return y_output - get_turning_speed() - b;
    }

    break;

  case 4:
    if (y_output + get_turning_speed() > 255)
    {
      return 255;
      b = (y_output + get_turning_speed()) - 255;
    }
    else if (y_output + get_turning_speed() < -255)
    {
      return -255;
      b = (y_output + get_turning_speed()) - (-255);
    }
    else
    {
      return y_output + get_turning_speed() - b;
    }

    break;

  default:
    break;
  }
}

void move()
{
  circle_to_triangle();
  if (radius > 1 && radius < 2)
  {
    int x, x_de, y, y_de;
    Positive_and_negative_judgment(x_output, y_output, x, x_de, y, y_de);

    motor_speed_setting(1, speed_planning(1) + 60);

    motor_speed_setting(2, speed_planning(2) + 60);

    motor_speed_setting(3, speed_planning(3) + 60);

    motor_speed_setting(4, speed_planning(4) + 60);
  }
  // if (radius > 1 && radius <2)
  // {
  //   int x, x_de, y, y_de;
  //   Positive_and_negative_judgment(x_output, y_output, x, x_de, y, y_de);

  //   motor_speed_setting(1, speed_planning(1)+60);

  //   motor_speed_setting(2, speed_planning(2)+60);

  //   motor_speed_setting(3, speed_planning(3)+60);

  //   motor_speed_setting(4, speed_planning(4)+60);
  // }
  // else if (radius < -1 && radius > -2)
  // {
  //   int x, x_de, y, y_de;
  //   Positive_and_negative_judgment(x_output, y_output, x, x_de, y, y_de);

  //   motor_speed_setting(1, speed_planning(1)+60);

  //   motor_speed_setting(2, speed_planning(2)+60);

  //   motor_speed_setting(3, speed_planning(3)+60);

  //   motor_speed_setting(4, speed_planning(4)+60);
  // }
}

void kick()
{
  if (digitalRead(BUTTON_7) == 0 && digitalRead(SWITCH_3) == 0)
  {
    switch (digitalRead(SWITCH_4))
    {
    case 0:
      LEDON();
      digitalWrite(motorballR_pin2, LOW);
      digitalWrite(motorballR_pin1, HIGH);
      analogWrite(motorballR_pwm, 90);
      delay(750);
      digitalWrite(motorballR_pin2, HIGH);
      digitalWrite(motorballR_pin1, LOW);
      analogWrite(motorballR_pwm, 255);
      delay(350);
      digitalWrite(motorballR_pin2, HIGH);
      digitalWrite(motorballR_pin1, HIGH);
      analogWrite(motorballR_pwm, 0);
      LEDOFF();
      break;
    case 1:
      LEDON();
      digitalWrite(motorballL_pin2, LOW);
      digitalWrite(motorballL_pin1, HIGH);
      analogWrite(motorballL_pwm, 90);
      delay(750);
      digitalWrite(motorballL_pin2, HIGH);
      digitalWrite(motorballL_pin1, LOW);
      analogWrite(motorballL_pwm, 255);
      delay(350);
      digitalWrite(motorballL_pin2, HIGH);
      digitalWrite(motorballL_pin1, HIGH);
      analogWrite(motorballL_pwm, 0);
      LEDOFF();
      break;
    }
  }
}

void loop()
{
  digitalWrite(motorballR_pin2, LOW);
  digitalWrite(motorballR_pin1, HIGH);
  analogWrite(motorballR_pwm, 20);
  digitalWrite(motorballL_pin2, LOW);
  digitalWrite(motorballL_pin1, HIGH);
  analogWrite(motorballL_pwm, 20);
  readController();
  tryButtons();
  JY901.receiveSerialData();
  pid();
  move();
  kick();
  Serial.print("Gyro_on");
  Serial.print(" ");
  Serial.print(Gyro_on);
  Serial.println(" ");
}
