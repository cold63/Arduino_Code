/*!
 *@file getData.ino
 *@brief Read ambient temperature and relative humidity and print them to serial port.
 *@copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@licence     The MIT License (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@version  V1.0
 *@date  2021-6-24
 *@get from https://www.dfrobot.com
 *@https://github.com/DFRobot/DFRobot_DHT20
*/

#include <DFRobot_DHT20.h>
#include <U8g2lib.h>

/*!
 * @brief Construct the function
 * @param pWire IC bus pointer object and construction device, can both pass or not pass parameters, Wire in default.
 * @param address Chip IIC address, 0x38 in default.
 */
DFRobot_DHT20 dht20;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, /* reset=*/ U8X8_PIN_NONE);
uint8_t fontHigh,fontWidth;

double tempValue,humidityValue;

void setup(){

  Serial.begin(115200);
 
  //Initialize sensor
  while(dht20.begin()){
    Serial.println("Initialize sensor failed");
    delay(1000);
  }
  
  u8g2.begin();
  u8g2.setFont(u8g2_font_8x13_mf);
  u8g2.setFontPosTop();
  fontHigh = u8g2.getMaxCharHeight();
  fontWidth = u8g2.getMaxCharWidth();
  
  u8g2.clear();
  u8g2.setCursor(0,0);
  u8g2.print("temp:");
  u8g2.updateDisplay();
  delay(100);
  u8g2.setCursor(0,fontHigh);
  u8g2.print("Humidity:");
  u8g2.updateDisplay();
}

void loop(){
  //Get ambient temperature
  tempValue = dht20.getTemperature();
  Serial.print("temp:"); Serial.print(tempValue);Serial.print("C");
  delay(100);
  
  //clean temp display
  u8g2.setCursor(fontWidth * 5 + 1,0);
  u8g2.print("    ");
  u8g2.updateDisplay();

  //display temp value to oled
  delay(10);
  String tempStr = String(tempValue,2);
  u8g2.setCursor(fontWidth * 5 + 1,0);
  u8g2.print(tempStr + "C");
  u8g2.updateDisplay();
  delay(500);
 
  //Get relative humidity
  humidityValue = dht20.getHumidity()*100;
  Serial.print("  humidity:"); Serial.print(humidityValue);Serial.println(" %RH");
  delay(100);
  
  //clean temp display
  u8g2.setCursor(fontWidth * 9 + 1,fontHigh);
  u8g2.print("    ");
  u8g2.updateDisplay();
  
  //display temp value to oled
  delay(10);
  String humidityStr = String(humidityValue,2);
  u8g2.setCursor(fontWidth * 9 + 1,fontHigh);
  u8g2.print(humidityStr + "%");
  u8g2.updateDisplay();

  delay(1000);

}
