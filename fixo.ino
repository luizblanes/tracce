
#include <RCSwitch.h>
#include <EEPROM.h>

int LED_RECV=12;
int LED_DATA=11;
int LED_SEND=10;

long unsigned int ticks;
long unsigned int last_milli;
unsigned int ls;

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  pinMode(LED_RECV,OUTPUT);
  pinMode(LED_DATA,OUTPUT);
  pinMode(LED_SEND,OUTPUT);
  digitalWrite(LED_RECV,LOW);
  digitalWrite(LED_DATA,LOW);
  digitalWrite(LED_SEND,LOW);
  ticks = 0;
  last_milli = millis();
  ls = LOW;
}

void loop() {


  if ( millis() >= ( last_milli + 250 ) ) {
    last_milli = millis();
    ticks = ticks + 1;
    ls = ! ls ;
    digitalWrite(LED_RECV,ls);
  }
  
  if (mySwitch.available()) {
    
    unsigned long value = mySwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {


      digitalWrite(LED_DATA,HIGH);
      delay(100);        
      digitalWrite(LED_DATA,LOW);

      digitalWrite(LED_SEND,HIGH);
      Serial.print("ID : ");
      Serial.println( mySwitch.getReceivedValue() );

      // send other stuffs
      
      delay(250);        
      digitalWrite(LED_SEND,LOW);
      
      
    }

    mySwitch.resetAvailable();
  }
}
