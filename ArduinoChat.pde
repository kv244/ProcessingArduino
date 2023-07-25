/* jp 25.07.2023
   Processing sketch communicating with Arduino board over serial.
   Currently no key count/scroll etc is done. ESC triggers a CLS.
   Port is hardcoded. The Arduino Serial Monitor (IDE) cannot run
   while the Processing sketch is running.
   */
import processing.serial.*;

Serial arduinoPort;
char keyRead;

void setup(){
  background(128);
  size(600, 400);
  println("Serial ports:");
  println((Object[])Serial.list());
  arduinoPort = new Serial(this, "COM3", 9600); 
  arduinoPort.bufferUntil(10); // buff end marker, has to match in Arduino sketch
}

void keyPressed(){
  if(key == ESC){
    keyRead = '!';
    key = 0;
  }
  else
    keyRead = (char)key;
    
  // println("Writing ", keyRead);
  arduinoPort.write(keyRead);
}

void draw(){
}

void serialEvent(Serial p){
  String arduinoCmd = p.readString();
  println("Serial event", arduinoCmd.substring(0, 5));
  if(arduinoCmd.substring(0, 5).equals("RECVD")) // have to handle the newline needed to signal buff end
    exit();
}
