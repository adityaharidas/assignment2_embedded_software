#include <math.h>
 int error_code = 0;
int win[4] = {0,0,0,0}; 
const unsigned long eventTime = 8;  // frame deadline is set to 8ms
const int LED_green = 16;   // pin where the led is connected in the microcontroller
const int P_Button1 = 22;  // push button pin
const int pulsepin = 2;    // pin for frequency counter
int P_Buttonstate1 = 0;
float frequency;
int average_analogue_in = 0;
int analog_input = 0;
const int analog_pin = 34;
int sensorValue = 0; 
float voltage = 0;
int rate[7] = {5,1,24,24,10,3,3}; // each task is executed according as per the given rate within 8ms.
int i = 2;             // variable which decides which task to be executed
int flag = 0;         // variable to call the deadline
void setup() 
{
 pinMode(LED_green, OUTPUT);
 pinMode(P_Button1, INPUT);
 pinMode(analog_pin, INPUT);
 pinMode(19,OUTPUT);
 Serial.begin(19200);
}
int task9_flag = 0; //the value of flag decide when should the value of the task 9 should be executed. 
void loop() 
{
unsigned long currentTime = millis(); 

   task1();
   if(i==2 && rate[i-2]>0)
    {
   task2();
    }
    else if(i==3 && rate[i-2]>0)   
    {
   task3();
    }
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
     int rate[7] = {5,1,24,24,10,3,3};   // restores the rate of the task 
   }
   flag++;
   i++;
   task9_flag++;
   if(task9_flag == 625)                     // each loop executes after every 5 seconds
    {
      task9();
      task9_flag=1;
    }
    while(millis()-currentTime <= eventTime) // wait signal is provided for each frame so that each task gets executed after 8 milliseconds
     {
      delay(1); 
     }
}
 void task1()                     // acts as watchdog timer
 {
   digitalWrite(LED_green, HIGH);
   delayMicroseconds(50);
   digitalWrite(LED_green, LOW);
 }
 void task2()                     // state of the pushbutton 
 {
  P_Buttonstate1 = digitalRead(P_Button1);
  if(P_Buttonstate1==1)
 {
   digitalWrite(LED_green, HIGH);
 }
else
 {
   digitalWrite(LED_green, LOW);
 }

 }  
 void task3()
 {                                 //generates square wave signal according to the frequency that is generated in the frequency generator
int pulseHigh, pulseLow, pulseTotal;
pulseHigh, pulseLow, pulseTotal= 0,0,0;    
pulseHigh = pulseIn(pulsepin,HIGH,6000);

pulseLow = pulseIn(pulsepin,LOW,6000);

pulseTotal = pulseHigh + pulseLow; // Time period of the pulse in microseconds

 
if(pulseTotal==0){
      frequency=0;
      }
      
    else{
    
    frequency = 1000000 / pulseTotal; // Frequency in Hertz (Hz)
    }

  }
 void task4()                             // updates the value of the potentiometer 
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
 void task5()                       //the last four values of the potentiometer is averaged for filtering in this function
 {
  long sum = 0;
  average_analogue_in = 0;
  for(int i=0; i<4; i++)
  {
  sum += win[i];
  average_analogue_in= sum/4;
  }
 }
 void task6()                      // function executes volatile nop which is an assembly instruction that does nothing
 {
   int j = 0;
   while(j<=1000)
      { 
        asm volatile("nop\n\t"::);
        j++;
      }
 }
 void task7()                      // the value of the error code is getting updayed in this code
 {error_code =0;                   
  if(average_analogue_in > 4095/2)
   { 
    error_code = 1;
   }  
 }
 void task8()                      //visualization of error code using LED
 {
   if(error_code==1)
    {
      digitalWrite(19,HIGH);
    }
  else
    {
      digitalWrite(19,LOW);
    }
 }
 void task9() //task 9                        //function logs data values to serial monitor using CSV format 

 {Serial.print("error_code ");
  Serial.print(error_code);
  Serial.print(",");
  Serial.print("P_Buttonstate1 ");
  Serial.print(P_Buttonstate1);
  Serial.print(",");
  Serial.print("frequency ");
  Serial.print(frequency);
  Serial.print(",");
  Serial.print("average_analogue_in ");
  Serial.println(average_analogue_in);
 }
