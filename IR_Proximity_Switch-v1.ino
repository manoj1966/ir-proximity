
// IT is working 23-11-2017

#include <IRremote.h>
#include <TimerOne.h>

#define IR_PIN 3
#define SENSOR_PIN 7
#define LEDOUT_PIN 8
#define LEDOUT_PWM_PIN 9

IRsend irsend;

int counter = 0;
int proximityVal = 0;
unsigned long timerTime = 40;
bool ledState = false;

long time = 20*60;         // for 20 min

void setup()
{
pinMode(IR_PIN, OUTPUT);
pinMode(SENSOR_PIN, INPUT);
pinMode(LEDOUT_PIN, OUTPUT);
digitalWrite(LEDOUT_PIN, LOW);
irsend.enableIROut(38);
//irsend.enableIROut(34.5);
TIMER_ENABLE_PWM; // Enable pin 3 PWM output

time = time *25000;
Serial.begin(115200);

Timer1.initialize(timerTime);
Timer1.attachInterrupt(switch_led_off); 
Timer1.pwm(LEDOUT_PWM_PIN, 0);
}


void loop(){
  proximityVal = digitalRead(SENSOR_PIN);
  if (proximityVal == 0){
    Serial.println("switchLED"); 
    switch_led();
  }    
}

void switch_led() {         // To create Toggle function
  //digitalWrite(LEDOUT_PIN, digitalRead(LEDOUT_PIN) ^ 1);
  for(int i=0; i<1024; i++){
    if(!ledState){ // If condition ledState == false
      Timer1.setPwmDuty(9, i); 
    } else {
      Timer1.setPwmDuty(9, 1023 - i);
    }
    delay(1);
  }
  Serial.println("PWM loop complete");
  ledState = !ledState;
}

void switch_led_off(){     //  Timer function for 1 sec update
  counter++;
  
  if (counter == time * 25000){
    digitalWrite(LEDOUT_PIN, LOW);
    counter = 0; 
  }
}











