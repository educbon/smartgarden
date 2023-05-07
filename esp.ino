/*
 * LoRa E32-TTL-100
 * Start device or reset to send a message
 * https://www.mischianti.org
 *
 * E32-TTL-100----- Wemos D1 mini
 * M0         ----- GND
 * M1         ----- GND
 * TX         ----- PIN D2 (PullUP)
 * RX         ----- PIN D3 (PullUP)
 * AUX        ----- Not connected
 * VCC        ----- 3.3v/5v
 * GND        ----- GND
 *
 */
#include "Arduino.h"
#include "LoRa_E32.h"
#include <stdlib.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
LoRa_E32 e32ttl100(D3, D4); // e32 TX e32 RX
 
void setup() {
  lcd.begin();
  Serial.begin(9600);
  delay(100);
 
  Serial.println("Hi, I'm going to send message!");
 
  // Startup all pins and UART
  e32ttl100.begin();
 
  // Send message
  ResponseStatus rs = e32ttl100.sendMessage("Hello, world?");
  // Check If there is some problem of successfully send
  Serial.println(rs.getResponseDescription());
}
 
void loop() {
    lcd.backlight();
           lcd.setCursor(0,0);
           lcd.print("d.a:");
           lcd.setCursor(7,0);
           lcd.print("d.a.d:");
           lcd.setCursor(0,1);
           lcd.print("t0:");
           lcd.setCursor(6,1);
           lcd.print("d:");
           lcd.setCursor(11,1);
           lcd.print("b:");
    // If something available
  if (e32ttl100.available()>1) {
      // read the String message
    ResponseContainer rc = e32ttl100.receiveMessage();
    // Is something goes wrong print error
    if (rc.status.code!=1){
        rc.status.getResponseDescription();
    }else{
        // Print the data received
        ///////////////////////////////// code ơ day
        {
          String chuoi = rc.data;
          long songuyen = chuoi.toInt();
          if ( 99999911 >= songuyen && songuyen >= 0 ) {
          int doam =0,doamdat =0,nhietdo=0,den=0,bom=0;
          doam = songuyen/1000000;
          Serial.println(doam);
          doamdat = (songuyen - doam*1000000)/ 10000;
          Serial.println(doamdat);
            nhietdo= (songuyen - doam*1000000 - doamdat*10000)/100;
             Serial.println(nhietdo);
            den = (songuyen - doam*1000000 - doamdat*10000 - nhietdo*100)/10;
            Serial.println(den);
            bom = (songuyen - doam*1000000 - doamdat*10000 - nhietdo*100 - den*10);
           Serial.println(bom);
           lcd.setCursor(4,0);
           lcd.print(doam);
           lcd.setCursor(13,0);
           lcd.print(doamdat);
           lcd.setCursor(3,1);
           lcd.print(nhietdo);
           lcd.setCursor(8,1);
           if (den==1) lcd.print("B");
           else lcd.print("T");
           lcd.setCursor(13,1);
           if (bom==1) lcd.print("B");
           else lcd.print("T");
          }
           delay(100);
           
  delay(100);
    // Clear the screen
        }           
        ///////////////////////////////// code o day
    }
  }

}
