/*
  SmartHHC - Electronic Drums HiHat Controller Firmware
  Copyright (C) 2018-2020 Lyudmil Tachev

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "define.h"

//Variable definitions start, should not normally need to change anything bellow here!!

byte opMode=OP_NORMAL;//OP_MODE_TEST;
#if HAVE_SERIAL_DEBUG
  byte sDebug=SER_DEBUG_EVENTS;
#endif

void setup() {
 
  pinMode(IR_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  digitalWrite(IR_PIN, HIGH);
  pinMode (MCP_CS, OUTPUT);
  delay(10);
#if HAVE_SERIAL
 #if HAVE_BT
  
    Serial.begin(9600); //115200);
    // wait for serial port to open on native usb devices
    while (!Serial) {
    delay(1);
    }
     /*
      Change name:
      AT+NAME:DesiredName
      Change speed to 115200:
      AT+UART=115200,0,0
      Change pin:
      AT+PSWD HC-05 / AT+PIN HC-06??:"0000"
     */
    delay(200);
    Serial.println("AT+NAME:SmartHHC-01");
    delay(50);
    Serial.println("AT+UART=38400,0,0");
    delay(50);
    Serial.println("AT+PIN:0000");delay(50);Serial.println("AT+PSWD:0000");delay(50);
    Serial.end();
    delay(100);
 #endif //HAVE_BT      
  Serial.begin(38400);
  while (!Serial) {
    delay(1);
   }
 #if HAVE_BT
  Serial.println("AT+NAME:SmartHHC-01"); delay(50);Serial.println("AT+PIN:0000");delay(50);Serial.println("AT+PSWD:0000");
 #endif //HAVE_BT        
  hcInit(); //command protocol module init
#endif//HAVE_SERIAL
  mcpInitial();
  btnInitial();
  MinMaxLoadEEPROM();
  RMALoadEEPROM(); 
  FixedLoadEEPROM();
  calcPWMcoef();
#if AV_M_ITERATIONS  //prepare the avm array
  prepareAV_M();
#endif
  LedInitialBlink;
#if STARTUP_DELAY 
      delay(STARTUP_DELAY);
#endif  
}

void loop() {
#if HAVE_SERIAL
  hcProcess(); //process commands from host
#endif  
  btnScan();
  btnHandle();
  doLed();
  switch (opMode) {
  case OP_NORMAL: 
     doMCP();
#if MAIN_LOOP_DELAY 
     delay(MAIN_LOOP_DELAY); //mind btn scan isn't working during this time!! 
#endif     
     break;
  case OP_LEARN: 
      Learn();
      break; 
  case OP_FIXED:
    //Dealt by Btn events. 
    break;
  case OP_TUNE_FIXED:
    //Dealt by Btn events. 
    break;
  default:
#if MAIN_LOOP_DELAY 
    delay(MAIN_LOOP_DELAY); //mind btn scan isn't working during this time!! 
#endif    
    break;    
 }
}
