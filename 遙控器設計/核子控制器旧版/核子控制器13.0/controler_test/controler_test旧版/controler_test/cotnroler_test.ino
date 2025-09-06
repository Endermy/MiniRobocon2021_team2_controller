void setup() {
  Serial.begin(38400);
   for(int digital_pin = 38 ; digital_pin < 50 ; digital_pin ++ ){
    pinMode(digital_pin,INPUT_PULLUP);
    }
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  }


void loop() {
  int snapshot [16];
   char shoting_pin = A0;
   for( int newlength=0 ; newlength < 4 ; newlength ++ ){ 
    snapshot[newlength]=analogRead(shoting_pin);
    shoting_pin++;
    }  
   shoting_pin = 38;
   for( int newlength=4 ; newlength < 16 ; newlength ++ ){ 
    snapshot[newlength]=digitalRead(shoting_pin);
    shoting_pin++;
    }  
  Serial.print(" 鍵程按鈕1： ");
  Serial.print(snapshot[0]);
  Serial.print(" 鍵程按鈕2： ");
  Serial.print(snapshot[1]);
  Serial.print(" 搖桿Y： ");
  Serial.print(snapshot[2]);
  Serial.print(" 搖桿X： ");
  Serial.print(snapshot[3]);
  Serial.print(" 開關1： ");
  Serial.print(snapshot[4]);
  Serial.print(" 開關2： ");
  Serial.print(snapshot[5]);
  Serial.print(" 開關3： ");
  Serial.print(snapshot[6]);
  Serial.print(" 開關4： ");
  Serial.print(snapshot[7]);
  Serial.print(" 按鈕1： ");
  Serial.print(snapshot[8]);
  Serial.print(" 按鈕2： ");
  Serial.print(snapshot[9]);
  Serial.print(" 按鈕3： ");
  Serial.print(snapshot[10]);
  Serial.print(" 按鈕4： ");
  Serial.print(snapshot[11]);
  Serial.print(" 按鈕5： ");
  Serial.print(snapshot[12]);
  Serial.print(" 按鈕6： ");
  Serial.print(snapshot[13]);
  Serial.print(" 按鈕7： ");
  Serial.print(snapshot[14]);
  Serial.print(" 按鈕8： ");
  Serial.println(snapshot[15]);
}
