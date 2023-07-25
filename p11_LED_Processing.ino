#include <LiquidCrystal.h>
#include <string.h>

/* dtypes def */
typedef enum _state{
  INIT,
  RECEIVED,
  CLEARED,
  WAITING
} state;

typedef struct _messages{
  const char* INIT = "INITIALIZED";
  const char* CLEARED = "CLR sent";
  char* toDisplay;
} messages;

/* var init */
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
long x = 0;
state portState;
messages displayMsg;
char incomingByte[2]; 

/* setup */
void setup() {
  displayMsg.toDisplay = displayMsg.INIT;
  portState = INIT;

  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  while(!Serial){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
  digitalWrite(LED_BUILTIN, LOW);
  lcd.begin(16, 2);
  lcd.print(displayMsg.toDisplay);
  lcd.setCursor(0, 1);
}

/* runtime */
void loop() {
  
  if(Serial.available() > 0){    
    portState = RECEIVED;
    incomingByte[0] = Serial.read();
    if(incomingByte[0] == '!'){
      portState = CLEARED;
      displayMsg.toDisplay = displayMsg.CLEARED;
    }else{
      incomingByte[1] = "\0";
      displayMsg.toDisplay = incomingByte;
    }
  }else{
    delay(50);
  }

  // lcd.clear();
  // lcd.setCursor(0, 0);
  
  if(portState == CLEARED){
    lcd.clear();
    lcd.setCursor(0, 0);
    portState = RECEIVED;
  }
  if(portState == RECEIVED)
    lcd.print(displayMsg.toDisplay);
  if(portState == RECEIVED)
    portState = WAITING; // to add ... for waiting
}

