#include <math.h>
int win[4] = {0,0,0,0}; 
const unsigned long eventTime = 8; 
const int LED_green = 15; //pin where the led is connected in the microcontroller
const int P_Button1 = 22; //push button 
const int pulsepin = 2;
int P_Buttonstate1 = 0;
int pulsetotal;
int frequency;
int pulsehigh;
int pulselow;
int average_analogue_in = 0;
int analog_input = 0;
const int analog_pin = 34;
int sensorValue = 0;
float voltage = 0;
int rate[7] = {5,1,24,24,10,3,3};
int i = 2;
int flag = 0;
void setup() 
{
 pinMode(LED_green, OUTPUT);
 pinMode(P_Button1, INPUT);
 pinMode(analog_pin, INPUT);
 Serial.begin(19200);
}
void loop() 
{
unsigned long currentTime = millis(); 
int task9_flag = 0;   
   task1();
   if(i==2 && rate[i-2]>0)
    {
   task2();
    }
  //  else if(i==3 && rate[i-2]>0)   
  //  {
  //  task3();
  //  }
    else if(i==4 && rate[i-2]>0)   
   {
   task4();
   }
    else if(i==5 && rate[i-2]>0)   
   {
   task5();
   }
    else if(i==6 && rate[i-2]>0)   
   {
   task6();
   }
    else if(i==7 && rate[i-2]>0)   
   {
   task7();
   }
    else if(i==8 && rate[i-2]>0)   
   {
   task8();
   }
   if(i==8)
   {
     i=1;
   }
   if(flag==125)
   {
     flag = 0;
     int i = 1;
     int rate[7] = {5,1,24,24,10,3,3};
   }
   flag++;
   i++;
   task9_flag++;
   if(task9_flag == 625)
    {
      task9();
      task9_flag=1;
    }
    while(millis()-currentTime <= eventTime)
     {
      delay(1); 
     }
}
 void task1() //task 1 Signal B
 {
   digitalWrite(LED_green, HIGH);
   delayMicroseconds(50);
   digitalWrite(LED_green, LOW);
 }
 void task2() //task 2
 {
  P_Buttonstate1 = digitalRead(P_Button1);
 }  
//  void task3() //task 3
//  {
//    pulsehigh = pulseIn(pulsepin, HIGH,5000);
//    pulselow = pulseIn(pulsepin, LOW,5000);
//    pulsetotal = pulsehigh + pulselow;
//  if (pulsetotal>0){
//     frequency = 1000000/pulsetotal; 
//    }
//  else{
//    frequency=0;
//  }
 //}
 void task4()
 {
  sensorValue = analogRead(analog_pin);
  digitalWrite(LED_green, HIGH);
  voltage = (sensorValue * 3.3/ 4095);
  digitalWrite(LED_green, LOW);
  
  analog_input = analogRead(analog_pin);
    for(int i=0; i<3; i++){
    win[i]=win[i+1];
 }
  win[3]= analog_input;
 }
 void task5()
 {
  long sum = 0;
  average_analogue_in = 0;
  for(int i=0; i<4; i++)
  {
  sum += win[i];
  average_analogue_in= sum/4;
  }
 }
 void task6()
 {
   int j = 0;
   while(j<=1000)
      { 
        asm volatile("nop\n\t"::);
        j++;
      }
 }
 void task7() //task 7
 {
  int error_code = 0;
  if(average_analogue_in > 4095/2)
   { 
    error_code = 1;
   }  
 }
 void task8()
 { int error_code = 0;
   if(error_code==1)
    {
      digitalWrite(15,HIGH);
    }
  else
    {
      digitalWrite(15,LOW);
    }
 }
 void task9() //task 9
 {
  Serial.print(P_Buttonstate1);
  Serial.print(",");
  Serial.print(frequency);
  Serial.print(",");
  Serial.println(average_analogue_in);
 }
