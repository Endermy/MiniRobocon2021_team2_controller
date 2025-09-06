void setup() {
  Serial.begin(38400);
   for(char analog_pin = 'A0' ; analog_pin < 'A16' ; analog_pin ++ ){
    pinMode(analog_pin, read);
    }
  }

void loop() {
  int snapshot [16];
   char shoting_pin = A0;
   for( int newlength=0 ; newlength < 3 ; newlength ++ ){ 
    shoting_pin++;
    snapshot[newlength]=analogRead(shoting_pin);
    }  
   for( int newlength=4 ; newlength < 16 ; newlength ++ ){ 
    shoting_pin++;
    snapshot[newlength]=digitalRead(shoting_pin);
    }  
  Serial.print(" 鍵程按鈕1： ");
  Serial.println(snapshot[0]);
  Serial.print(" 鍵程按鈕2： ");
  Serial.println(snapshot[1]);
  Serial.print(" 搖桿Y： ");
  Serial.println(snapshot[2]);
  Serial.print(" 搖桿X： ");
  Serial.println(snapshot[3]);
  Serial.print(" 開關1： ");
  Serial.println(snapshot[4]);
  Serial.print(" 開關2： ");
  Serial.println(snapshot[5]);
  Serial.print(" 開關3： ");
  Serial.println(snapshot[6]);
  Serial.print(" 開關4： ");
  Serial.println(snapshot[7]);
  Serial.print(" 按鈕1： ");
  Serial.println(snapshot[8]);
  Serial.print(" 按鈕2： ");
  Serial.println(snapshot[9]);
  Serial.print(" 按鈕3： ");
  Serial.println(snapshot[10]);
  Serial.print(" 按鈕4： ");
  Serial.println(snapshot[11]);
  Serial.print(" 按鈕5： ");
  Serial.println(snapshot[12]);
  Serial.print(" 按鈕6： ");
  Serial.println(snapshot[13]);
  Serial.print(" 按鈕7： ");
  Serial.println(snapshot[14]);
  Serial.print(" 按鈕8： ");
  Serial.println(snapshot[15]);
}
