/*
  Simple example for receiving
  
  https://github.com/sui77/rc-switch/
*/

#include <RCSwitch.h>
#include <EEPROM.h>

int LED_GREEN=12;
int LED_RED=11;
int LED_DOOR=10;

int door_state;
byte code_value;
unsigned long codes[4];
byte code_ok;

long unsigned int seconds;
long unsigned int last_milli;

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  pinMode(LED_GREEN,OUTPUT);
  pinMode(LED_RED,OUTPUT);
  pinMode(LED_DOOR,OUTPUT);
  digitalWrite(LED_DOOR,LOW);
  door_state = LOW;

  codes[0] = 145025765;
  codes[1] = 0;
  codes[2] = 0;
  codes[3] = 0;

  seconds = 0;
  last_milli = millis();
  
}

void loop() {


  if ( millis() >= ( last_milli + 1000 ) ) {
    last_milli = millis();
    seconds = seconds + 1;
    //Serial.println( seconds );
  }
  
  if (mySwitch.available()) {
    
    unsigned long value = mySwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {

      
      Serial.print("Received ");
      Serial.print( mySwitch.getReceivedValue() );
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
      
      code_ok = 0;
      for (int i=0; i <= 3; i++){
        if ( ( codes[i] == value ) && ( value != 0 ) ) {
          code_ok = 1;
          break;
        }
      }       

      if ( code_ok == 1 ) {
        digitalWrite(LED_GREEN,HIGH);
        delay(10);        
        digitalWrite(LED_GREEN,LOW);
        door_state = ! door_state ;
      }
      else {
        digitalWrite(LED_RED,HIGH);
        delay(10);        
        digitalWrite(LED_RED,LOW);
      }
   
      digitalWrite(LED_DOOR,door_state);
      
    }

    mySwitch.resetAvailable();
  }
}
