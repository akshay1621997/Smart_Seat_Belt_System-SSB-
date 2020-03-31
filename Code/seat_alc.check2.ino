
int trigPin1 = 11;
int echoPin1 = 10;
int trigPin2 = 9;
int echoPin2 = 8;
int mq3relay = 7;
int crankrelay = 6 ;
int beltreed = 5;
long duration1,duration2;
float distanceCm1,distanceCm2;// 1 --> Front Sensor ; 2 --> BackSensor
float alcval;
int beltval;//beltval = 1 for no magnet .. 0 for magnet .. ie .. 1 for seat belt off. 0 for seat belt on.
int beltcheck;// to check if belt is worn for first time or nth time and removed correspondingly ----> 1 if already worn and removed later . so that the if loop runs continuosly


void setup() {
  // put your setup code here, to run once:
  pinMode(10,INPUT);
  pinMode(11,OUTPUT);
  pinMode(8,INPUT);
  pinMode(9,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(5,INPUT);
  
  Serial.begin(9600);
  alcval = -1;
  beltval=-1;
  beltcheck=-1;

}

void loop() 
{

        digitalWrite(trigPin1, LOW);
        delayMicroseconds(1000);
        digitalWrite(trigPin1, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin1, LOW);
        duration1 = pulseIn(echoPin1, HIGH);
        distanceCm1= duration1*0.034/2;
        
        
        digitalWrite(trigPin2, LOW);
        delayMicroseconds(1000);
        digitalWrite(trigPin2, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin2, LOW);
        duration2 = pulseIn(echoPin2, HIGH);
        distanceCm2= duration2*0.034/2;
        
        
        delay(2000);
        
        Serial.println(distanceCm1);
        Serial.println(distanceCm2);
        
        if(distanceCm1 <=12&&distanceCm2>=32)
            {
              digitalWrite(mq3relay,HIGH);
              delay(3000);
              alcval=analogRead(A0);
              Serial.println(alcval);
              
              if(alcval>300)
                  {
                    digitalWrite(crankrelay,LOW);
                    Serial.println("Alcohol Detected , Please don't drive");
                  }
             
              else
                  {
                      //digitalWrite(crankrelay,HIGH);
                      //Serial.println("You may drive"); BUT U HAVENT CHECKED SEATBELT . SO CALL SEATBELT FUNCTION
                      beltval=digitalRead(beltreed);
                        
                         if(beltval==0)
                              {
                                Serial.println("You may drive");
                                digitalWrite(crankrelay,HIGH);           // Seat belt ON
                                beltcheck=1;
                              }
                          
                          else
                            {
                              if(beltcheck==1)
                                 {
                                   Serial.println("Not safe to remove seabelt while driving.");  //removes seatbelt midway
                                 }
                                 
                               else
                                  {
                                    Serial.println("Please wear yor Seat belt"); // Hasnt put on Seatbelt after alc check
                                  } 
                            }
                     }
            }
            
         
        else
            { 
              digitalWrite(mq3relay,LOW);
              if(alcval!=-1)
                  {
                    if(alcval>300)
                    {
                        digitalWrite(crankrelay,LOW);
                        Serial.println("Alcohol Detected ,PLease don't drive");
                    }
                    else
                    {
                      beltval=digitalRead(beltreed);
                       if(beltval==0)
                              {
                                Serial.println("You may drive");
                                digitalWrite(crankrelay,HIGH);           // Seat belt ON
                                beltcheck=1;
                              }
                          
                          else
                            {
                              if(beltcheck==1)
                                 {
                                   Serial.println("Not safe to remove seabelt while driving.");  //removes seatbelt midway
                                 }
                                 
                               else
                                  {
                                    Serial.println("Please wear yor Seat belt"); // Hasnt put on Seatbelt after alc check
                                  } 
                            }    
                    }
                  }
                  
              else
                    {
                        digitalWrite(crankrelay,LOW);
                        Serial.println("Please bend forward and blow into the sensor");
                    }
            }
            Serial.println(alcval);


}
