
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  mySwitch.enableTransmit(10);  // Using Pin #10
  mySwitch.setRepeatTransmit(5);
}

void loop() {
  mySwitch.send(145025765,28);
//  mySwitch.send(123,8);
  delay(1000);  
}


