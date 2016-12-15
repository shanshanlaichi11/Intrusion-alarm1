#define  sensorPin  6
#define buzzer_pin 4
#include <avr/sleep.h>

int pin2 = 2;
int state;
int pushButton =2;
void pin2Interrupt(void) {
    /* 中断唤醒 */
 
    /*当中断引脚为低电平时关闭中断*/
    Serial.println("wake up!!!");
    detachInterrupt(0);
}
 
/***************************************************
 *  Name:        enterSleep
 *  Returns:     Nothing.
 *  Parameters:  None.
 *  Description: Enters the arduino into sleep mode.
 ***************************************************/
void enterSleep(void) {

    attachInterrupt(0, pin2Interrupt, LOW);
    delay(100);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
}
 
/***************************************************
 *  Name:        setup
 *  Returns:     Nothing.
 *  Parameters:  None.
 *  Description: Setup for the Arduino.           
 ***************************************************/
void setup() {
    Serial.begin(9600);
    /* Setup the pin direction. */
    pinMode(pin2, INPUT);
    Serial.println("Initialisation complete.");
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  pinMode(buzzer_pin,OUTPUT);
   pinMode(pushButton, INPUT);
}
void loop()
{

  state = digitalRead(sensorPin);
  if (state == 1){
    Serial.println("Somebody is in this area!");
   
    for(int i=200;i<=800;i++)  //用循环的方式将频率从200HZ 增加到800HZ
  {
    tone(buzzer_pin,i);   //在四号端口输出频率
      int buttonState = digitalRead(pushButton);
      Serial.println(buttonState);
      if(buttonState == 0){
        Serial.println("Entering sleep");
        enterSleep();
      }
     
    delay(5);      //该频率维持5毫秒  
    
  }
}
else
    Serial.println("No one!");
  delay(1000);
}
