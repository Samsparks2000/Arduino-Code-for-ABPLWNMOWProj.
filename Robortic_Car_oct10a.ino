// ---------------------------------------------------------------- //
// Arduino Ultrasonic Sensor HC-SR04
// Re-written by Samuel Ayodele Okunomo
// Using Arduino IDE
// Using HC-SR04 Module
// Tested on August 2021
// ---------------------------------------------------------------- //

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
//#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define trigPin 4 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int Direction,mb;
int speedCar = 170;//100; 
int speedCarCurve = 100;   

#define ENA_m1          9
#define ENA_m2          10
#define LongRange       160//160
#define MidRange        60//120
#define ShortRange      40
#define OffRange        15
#define OffRangeLow     5
#define  RightFwd_Wheel_On    analogWrite(ENA_m1, speedCar);//PORTB |=(1<<1);       // put off power    
#define  LeftFwd_Wheel_On     analogWrite(ENA_m2, speedCar);//PORTB |=(1<<2);       // put off power
#define  RightBck_Wheel_On    PORTB |=(1<<3);       // put off power    
#define  LeftBck_Wheel_On     PORTB |=(1<<4);       // put off power
#define  Right_Wheel_Off      PORTB &=~((1<<1)|(1<<3));// put off power
#define  Left_Wheel_Off       PORTB &=~((1<<2)|(1<<4));// put off power


void Control(){  
if (distance>OffRange){
  if (distance>LongRange){
    RightFwd_Wheel_On                              // move forward
    LeftFwd_Wheel_On                               // move forward
  }
  //else if (distance>MidRange){
  //    RightFwd_Wheel_On                              // move forward
  //    LeftFwd_Wheel_On                               // move forward
  //  }
  else if ((distance<ShortRange)&&(distance>OffRange)){
    Right_Wheel_Off
    Left_Wheel_Off
   _delay_ms(100);
   RightFwd_Wheel_On                                    // make left turn
   LeftBck_Wheel_On
    while((distance<ShortRange)&&(distance>OffRange)){
       Ultasonic_Samples();
       Serial.print("Short Distance: ");
       Serial.print(distance);
       Serial.println(" cm");
       //S_Out();        
      }
    _delay_ms(1000);                                  // to turn completly 90'
    Left_Wheel_Off
    _delay_ms(100);
    LeftFwd_Wheel_On                                  // move forward
    }
  }
else {
      Right_Wheel_Off
      Left_Wheel_Off
   }
}

void Control2(){  
//if ((distance>OffRangeLow)&&(distance<OffRange)){
  if ((distance>OffRangeLow)&&(distance<OffRange)){
    Right_Wheel_Off
    Left_Wheel_Off
  }
  
  else if ((distance>ShortRange)&&(distance<MidRange)){
    Right_Wheel_Off
    Left_Wheel_Off
   _delay_ms(1000);
   RightFwd_Wheel_On                                    // make left turn
   LeftBck_Wheel_On
    while((distance>ShortRange)&&(distance<MidRange)){
       Ultasonic_Samples();
       Serial.print("Short Distance: ");
       Serial.print(distance);
       Serial.println(" cm");
       //S_Out();       
       Right_Wheel_Off
       Left_Wheel_Off
       _delay_ms(400);
       RightFwd_Wheel_On                                    // make left turn
       LeftBck_Wheel_On
       _delay_ms(100); 
      }
    Right_Wheel_Off
      Left_Wheel_Off
    _delay_ms(500);                                   // to turn completly 90'
    }
  //}
else {
      RightFwd_Wheel_On                              // move forward
      LeftFwd_Wheel_On                               // move forward
   }
}

void Control3(){  
//  analogWrite(ENA_m1, speedCar);
//if ((distance>OffRangeLow)&&(distance<OffRange)){
  if ((distance>OffRangeLow)&&(distance<OffRange)){
    Right_Wheel_Off
    Left_Wheel_Off    
  }
  
  else if ((distance>ShortRange)&&(distance<MidRange)){
    Right_Wheel_Off
    Left_Wheel_Off
    mb = 0;
   _delay_ms(1000);
    //RightFwd_Wheel_On                                    // make left turn
    //LeftBck_Wheel_On
    if(Direction){Direction = 0;} else {Direction = 1;}
    //while((distance>ShortRange)&&(distance<MidRange)){
    while(mb++<255*15/speedCarCurve){
       //Ultasonic_Samples();
       //Serial.print("Short Distance: ");
       //Serial.print(distance);
       //Serial.println(" cm");
       Right_Wheel_Off
       Left_Wheel_Off
       _delay_ms(20);
        if(mb==255*7/speedCarCurve){                                          // move forward a bit 
        LeftFwd_Wheel_On 
        RightFwd_Wheel_On
        _delay_ms(400);
        Right_Wheel_Off
        Left_Wheel_Off
        _delay_ms(20);
        }
        if(Direction){
        RightBck_Wheel_On                                    // make right turn
        LeftFwd_Wheel_On
        }
       else{
        RightFwd_Wheel_On                                    // make left turn
        LeftBck_Wheel_On
        }
       _delay_ms(100);
       //S_Out();        
      }
      Right_Wheel_Off
      Left_Wheel_Off
    _delay_ms(500);                                   // to turn completly 90'
    LeftFwd_Wheel_On                                  // move forward
    RightFwd_Wheel_On                                 // move forward
    }
  //}
else {
      RightFwd_Wheel_On                              // move forward
      LeftFwd_Wheel_On                               // move forward
   }
}


void setup() {
  DDRB |=((1<<1)|(1<<2));
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  Right_Wheel_Off
  Left_Wheel_Off
}

unsigned int Ultasonic_Samples(){
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  return distance;
}

void S_Out(){
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void loop() {/*
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  */
  Ultasonic_Samples();
  S_Out();
  //Control();
  Control3();
}
