#include <Servo.h>


#define SERVO_PIN 26


Servo myservo;
int input, r;

void setup() {
  myservo.attach(SERVO_PIN);
 
  Serial.begin(9600);
  Serial.println("begin");
}

void loop() {
  char inputChar;
  static byte inputBuffer;

  r = 43;
  if (Serial.available())
  {
    inputChar = Serial.read();

    if (inputChar == 10)
    {
      input = inputBuffer;

      /*
        if (input <= 180) {
        servolower.write(input);
        Serial.print("Angle = ");
        Serial.println(input);
        }
      */

      if (input == 1) {
        myservo.write(4);

      } else if (input == 2) {
        myservo.write(r);
        delay(94);
        for (int i = r; i <= 115 ; i++) {
          myservo.write(i);
          delay(7);
        }
      }


      inputBuffer = 0;
    }
    else if (inputChar >= '0' & inputChar <= '9')
    {
      inputBuffer = (inputBuffer * 10) + (inputChar - '0');
    }
  }
}
