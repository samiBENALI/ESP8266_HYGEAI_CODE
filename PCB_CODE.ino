
#include<Wire.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""
#define WIFI_SSID ""
// FirebaseDemo_ESP8266 is a sample that demo the different functions
#define WIFI_PASSWORD ""
int BUZZER = 2; 
int holdPin = 0;  // defines GPIO 0 as the hold pin (will hold CH_PD high untill we power down)
int trans=13; //treansistor pin that powers the GY-510

//2. Define FirebaseESP8266 data object for data sending and receiving
FirebaseData firebaseData;
const long utcOffsetInSeconds = 3600;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);


const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265;
int maxVal=402;

double x=0;
double y=0;
double z=0;

double xprev=0; 

int mouthx=0;
int mouthy=0;
int mouthz=0;

int nosex=0;
int nosey=0;
int nosez=0;

int eyex=0;
int eyey=0;
int eyez=0;
int eyex1=0;
int eyey1=0;
int eyez1=0;

int flag=0;
int counter=0;





void setup() {
  // put your setup code here, to run once:


pinMode(holdPin, OUTPUT);
digitalWrite(holdPin, HIGH);
pinMode(trans,OUTPUT);
digitalWrite(trans,HIGH);
pinMode(BUZZER,OUTPUT);


delay(200);
   

Wire.begin();
Wire.beginTransmission(MPU_addr);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);



Serial.begin(115200);

  
  

}

void loop() {
  // put your main code here, to run repeatedly:
Wire.beginTransmission(MPU_addr);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU_addr,14,true);
AcX=Wire.read()<<8|Wire.read();
AcY=Wire.read()<<8|Wire.read();
AcZ=Wire.read()<<8|Wire.read();
int xAng = map(AcX,minVal,maxVal,-90,90);
int yAng = map(AcY,minVal,maxVal,-90,90);
int zAng = map(AcZ,minVal,maxVal,-90,90);

xprev=x;
x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);








 if (!(mouthx&&mouthy&&mouthz))   //first we check if we have the refrence values if not we connect to get them 
            {
              WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();


  //3. Set your Firebase info

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //4. Enable auto reconnect the WiFi when connection lost
  Firebase.reconnectWiFi(true);

  if (Firebase.get(firebaseData, "/config"))
{
   
  Serial.print("Connection established \n");

  if (firebaseData.intData())
      {

  //config=1 so we can read the data 
  
              Serial.print("Reading refrence values from db \n");
              
                while (!Firebase.get(firebaseData, "/mouthx"))
                    {
                      
                       Serial.print("Error in getInt mouthx \n, ");
                Serial.println(firebaseData.errorReason());
  
                    }
               mouthx=firebaseData.intData();
                      Serial.print("Success in getInt mouthx \n, ");

              while (!Firebase.get(firebaseData, "/mouthy"))
                  {
                 
                   Serial.print("Error in getInt mouthy \n, ");
                Serial.println(firebaseData.errorReason());
                  }
              mouthy=firebaseData.intData();
                  Serial.print("Success in getInt mouthyy \n, ");

              while (!Firebase.get(firebaseData, "/mouthz"))
                 {
                
                  Serial.print("Error in getInt mouthz \n, ");
                Serial.println(firebaseData.errorReason());

                 }
                mouthz=firebaseData.intData();
                  Serial.print("Success in getInt mouthz \n, ");
                  
              Serial.print("Reading refrence values from db \n");
              
                while (!Firebase.get(firebaseData, "/nosex"))
                    {
                      
                       Serial.print("Error in getInt nosex \n, ");
                Serial.println(firebaseData.errorReason());
  
                    }
               nosex=firebaseData.intData();
                      Serial.print("Success in getInt nosex \n, ");

              while (!Firebase.get(firebaseData, "/nosey"))
                  {
                 
                   Serial.print("Error in getInt nosey \n, ");
                Serial.println(firebaseData.errorReason());
                  }
              nosey=firebaseData.intData();
                  Serial.print("Success in getInt nosey \n, ");

              while (!Firebase.get(firebaseData, "/nosez"))
                 {
                
                  Serial.print("Error in getInt nosez \n, ");
                Serial.println(firebaseData.errorReason());

                 }
                nosez=firebaseData.intData();
                  Serial.print("Success in getInt nosez \n, ");

                  


                   Serial.print("Reading refrence values from db \n");
              
                while (!Firebase.get(firebaseData, "/eyex"))
                    {
                      
                       Serial.print("Error in getInt eyex \n, ");
                Serial.println(firebaseData.errorReason());
  
                    }
               eyex=firebaseData.intData();
                      Serial.print("Success in getInt eyex \n, ");

              while (!Firebase.get(firebaseData, "/eyey"))
                  {
                 
                   Serial.print("Error in getInt eyey \n, ");
                Serial.println(firebaseData.errorReason());
                  }
              eyey=firebaseData.intData();
                  Serial.print("Success in getInt eyey \n, ");

              while (!Firebase.get(firebaseData, "/eyez"))
                 {
                
                  Serial.print("Error in getInt eyez \n, ");
                Serial.println(firebaseData.errorReason());

                 }
                eyez=firebaseData.intData();
                  Serial.print("Success in getInt eyez \n, ");

                  
                   Serial.print("Reading refrence values from db \n");
              
                while (!Firebase.get(firebaseData, "/eyex1"))
                    {
                      
                       Serial.print("Error in getInt eyex1 \n, ");
                Serial.println(firebaseData.errorReason());
  
                    }
               eyex1=firebaseData.intData();
                      Serial.print("Success in getInt eyex1 \n, ");

              while (!Firebase.get(firebaseData, "/eyey1"))
                  {
                 
                   Serial.print("Error in getInt eyey \n, ");
                Serial.println(firebaseData.errorReason());
                  }
              eyey1=firebaseData.intData();
                  Serial.print("Success in getInt eyey1 \n, ");

              while (!Firebase.get(firebaseData, "/eyez1"))
                 {
                
                  Serial.print("Error in getInt eyez1 \n, ");
                Serial.println(firebaseData.errorReason());

                 }
                eyez1=firebaseData.intData();
                  Serial.print("Success in getInt eyez1 \n, ");
                  
// we disconnect here
                  WiFi.disconnect();
                   Serial.println("done my work and disconnected");
                

      }
      else {
  //config=0 so we upload the values






      while(!Firebase.get(firebaseData, "/flag"))
      {
        //Failed?, get the error reason from firebaseData

    Serial.print("Error  getting config value \n, ");
    Serial.println(firebaseData.errorReason());
    delay(200);
        }
      


          flag=firebaseData.intData();
          Serial.print("Success in getInt mouthx \n, ");


         if(flag==1){
         

          while(!(Firebase.setInt(firebaseData, "/mouthx", x)))
            {
            
             //Failed?, get the error reason from firebaseData

          Serial.print("Error in setInt mouthx, ");
          Serial.println(firebaseData.errorReason());
          delay(200);

            }    
              //Success
            Serial.println("Set int data success mouthx"); 
          
          while(!Firebase.setInt(firebaseData, "/mouthy", y))
             {
              
              //Failed?, get the error reason from firebaseData

          Serial.print("Error in setInt mouthy, ");
          Serial.println(firebaseData.errorReason());
          delay(200);

             }
             //Success
              Serial.println("Set int data success mouthy");
          
          while(!Firebase.setInt(firebaseData, "/mouthz", z))
          {
          
          //Failed?, get the error reason from firebaseData

            Serial.print("Error in setInt mouthz ");
            Serial.println(firebaseData.errorReason());
            delay(200);

          }
          //Success
          Serial.println("Set int data success mouthz");
          
         }



         if(flag==2){
         

          while(!(Firebase.setInt(firebaseData, "/eyex", x)))
            {
            
             //Failed?, get the error reason from firebaseData

          Serial.print("Error in setInt eyex, ");
          Serial.println(firebaseData.errorReason());
          delay(200);

            }    
              //Success
            Serial.println("Set int data success eyex"); 
          
          while(!Firebase.setInt(firebaseData, "/eyey", y))
             {
              
              //Failed?, get the error reason from firebaseData

          Serial.print("Error in setInt eyey, ");
          Serial.println(firebaseData.errorReason());
          delay(200);

             }
             //Success
              Serial.println("Set int data success eyey");
          
          while(!Firebase.setInt(firebaseData, "/eyez", z))
          {
          
          //Failed?, get the error reason from firebaseData

            Serial.print("Error in setInt eyez ");
            Serial.println(firebaseData.errorReason());
            delay(200);

          }
          //Success
          Serial.println("Set int data success eyez");
          
         }

         if(flag==3){
         

          while(!(Firebase.setInt(firebaseData, "/nosex", x)))
            {
            
             //Failed?, get the error reason from firebaseData

          Serial.print("Error in setInt nosex, ");
          Serial.println(firebaseData.errorReason());
          delay(200);

            }    
              //Success
            Serial.println("Set int data success nosex"); 
          
          while(!Firebase.setInt(firebaseData, "/nosey", y))
             {
              
              //Failed?, get the error reason from firebaseData

          Serial.print("Error in setInt nosey, ");
          Serial.println(firebaseData.errorReason());
          delay(200);

             }
             //Success
              Serial.println("Set int data success nosey");
          
          while(!Firebase.setInt(firebaseData, "/nosez", z))
          {
          
          //Failed?, get the error reason from firebaseData

            Serial.print("Error in setInt nosez ");
            Serial.println(firebaseData.errorReason());
            delay(200);

          }
          //Success
          Serial.println("Set int data success nosez");
          
         }






         if(flag==4){
         

          while(!(Firebase.setInt(firebaseData, "/eyex1", x)))
            {
            
             //Failed?, get the error reason from firebaseData

          Serial.print("Error in setInt eyex1, ");
          Serial.println(firebaseData.errorReason());
          delay(200);

            }    
              //Success
            Serial.println("Set int data success eyex1"); 
          
          while(!Firebase.setInt(firebaseData, "/eyey1", y))
             {
              
              //Failed?, get the error reason from firebaseData

          Serial.print("Error in setInt eyey1, ");
          Serial.println(firebaseData.errorReason());
          delay(200);

             }
             //Success
              Serial.println("Set int data success eyey1");
          
          while(!Firebase.setInt(firebaseData, "/eyez1", z))
          {
          
          //Failed?, get the error reason from firebaseData

            Serial.print("Error in setInt eyez1 ");
            Serial.println(firebaseData.errorReason());
            delay(200);

          }
          //Success
          Serial.println("Set int data success eyez1");
          
         }
         if(flag==5){ Serial.println("config completed");
         
         delay(200);
// we disconnect here
              WiFi.disconnect();

         
         }



      }




      
}
else {
  Serial.print("Error in getInt config \n, ");
  Serial.println(firebaseData.errorReason());
  
}

              
            }
            
             //we connect again here to report the event 
                    else if( (((mouthx-10<x)&&(x<mouthx+10))&&((mouthz-10<z)&&(z<mouthz+10))&&((mouthy-10<y)&&(y<mouthy+10)))or(((nosex-10<x)&&(x<nosex+10))&&((nosez-10<z)&&(z<nosez+10)&&((nosey-10<y)&&(y<nosey+10)))or(((eyex-10<x)&&(x<eyex+10))&&((eyez-10<z)&&(z<eyez+10))&&((eyey-10<y)&&(y<eyey+10)))or(((eyex1-10<x)&&(x<eyex1+10))&&((eyez1-10<z)&&(z<eyez1+10))&&((eyey1-10<y)&&(y<eyey1+10)))))


{
     
          

             digitalWrite(BUZZER, HIGH);
            delay(250);
            digitalWrite(BUZZER, LOW);
            delay(250);
            digitalWrite(BUZZER, HIGH);
            delay(250);
            digitalWrite(BUZZER, LOW);
            delay(250);
            digitalWrite(BUZZER, HIGH);
            delay(250);
            digitalWrite(BUZZER, LOW);
             delay(250);
            digitalWrite(BUZZER, HIGH);
            delay(250);
            digitalWrite(BUZZER, LOW);
             delay(250);
            digitalWrite(BUZZER, HIGH);
            delay(250);
            digitalWrite(BUZZER, LOW);

 WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();


  //3. Set your Firebase info

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //4. Enable auto reconnect the WiFi when connection lost
  Firebase.reconnectWiFi(true);



           
            timeClient.begin();
            delay(500);
            Serial.println(timeClient.getFormattedTime());
            Serial.print(daysOfTheWeek[timeClient.getDay()]);
            while(!Firebase.setString(firebaseData,"/time", daysOfTheWeek[timeClient.getDay()]+timeClient.getFormattedTime()))
             {
              
              //Failed?, get the error reason from firebaseData

          Serial.println("Error in setInt time, ");
          Serial.println(firebaseData.errorReason());
          delay(200);

             }
             //Success
              Serial.println("Set int data success time");


              //we disconnect here
              WiFi.disconnect();
            

            

            
          }
        








if ( xprev==x) { counter++; }

if ( counter > 4000000000)   // freq is 80Mhz so if counter exeeds approximetaly 5 minutes without any change it will enter sleep mode  
{
 digitalWrite(holdPin, LOW); 
}

}




