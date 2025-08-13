#include "button_func.h"

const int trig_pin = A2; //## 초음파를 보내는 센서
const int echo_pin = A3; //## 초음파를 받는 센서 
const int LED[3] = {11,10,9}; // RED,GREEN,BLUE
const int height = 9;

int count = 0;
int set_height = 0;

int seg[]={2,3,4,5,6,7,8,12}; //D2(a)


long get_distance(){

  digitalWrite(trig_pin,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin,HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig_pin,LOW);

  long duration = pulseIn(echo_pin,HIGH);  
  long distance = duration/58.0;

  return distance;

}


byte digits[10][8]={  
  { 1,1,1,1,1,1,0,0 }, // 0 2번 3번 4번 5번 6번 7번 on 
  { 0,1,1,0,0,0,0,0 }, // 1
  { 1,1,0,1,1,0,1,0 }, // 2
  { 1,1,1,1,0,0,1,0 }, // 3
  { 0,1,1,0,0,1,1,0 }, // 4
  { 1,0,1,1,0,1,1,0 }, // 5
  { 1,0,1,1,1,1,1,0 }, // 6
  { 1,1,1,0,0,0,0,0 }, // 7
  { 1,1,1,1,1,1,1,0 }, // 8
  { 1,1,1,0,0,1,1,0 }, // 9
};

void set_number(int distance){

  if (distance < 10){
    for (int j = 0; j < 8; j++){
      digitalWrite(seg[j], digits[distance][j]);   //cathode
  }
  }
  else{
    for (int j = 0; j < 8; j++){
      digitalWrite(seg[j], digits[9][j]);   //cathode
    }
    }

}

void get_color(long distance){

  if(distance < 3){

    analogWrite(LED[0],255);
    analogWrite(LED[1],0);
    analogWrite(LED[2],0);

  }
  else if(distance < 11){
    analogWrite(LED[0],255- int(distance*25));
    analogWrite(LED[1],int(distance*25));
    analogWrite(LED[2],0);
  }
  else{
    analogWrite(LED[0],255);
    analogWrite(LED[1],255);
    analogWrite(LED[2],255);
  }

}

void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(button,INPUT_PULLUP);
  pinMode(trig_pin,OUTPUT);
  pinMode(echo_pin,INPUT);
  Serial.begin(115200);
  for (int i = 0; i < 8; i++){
  pinMode(seg[i], OUTPUT);
  }

}

void loop() {
  
  long distance = get_distance();
  get_color(distance);
  // set_number(distance);
  // Serial.println(distance);
  delay(50);

  if(readButton()){
    count = !count;

    if (count){
      set_height = distance;
    }
    else{
      if (set_height-distance < 0){
        set_height = height;
      }
      set_number(set_height-distance);
    }
    Serial.print("Button =  ");
    Serial.println(count);
    Serial.print("Set height = ");
    Serial.println(set_height);
    Serial.print("distance = ");
    Serial.println(distance);

  }

}
