
#include <Wire.h>

#define Example1
#define EEPROM_ADDRESS  0x50

uint8_t Datax[8] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};
uint8_t DataOut[8] ={0};

uint8_t x;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("EEPROM TEST");
  Wire.begin();

#ifdef Example1
  WriteBytes(0,Datax,8);

  delay(10);

  ReadBytes(0,DataOut,8);

  for(x = 0; x < 8; x++)
  {
    Serial.println(DataOut[x],HEX);
  }

#else
 
  WriteByte(1,0x5A);
  delay(10);
  
  Serial.println(ReadByte(1),HEX);
  
#endif  

}

void loop() {
  // put your main code here, to run repeatedly:

}

void WriteByte(uint8_t data_addr, uint8_t data)
{
  
  Wire.beginTransmission(EEPROM_ADDRESS);
  Wire.write(data_addr);
  Wire.write(data);
  Wire.endTransmission();
}

uint8_t ReadByte(uint8_t data_addr)
{
  uint8_t data;
  Wire.beginTransmission(EEPROM_ADDRESS);
  Wire.write(data_addr);
  Wire.endTransmission();
  Wire.requestFrom(EEPROM_ADDRESS,1);

  if(Wire.available())
  {
    data = Wire.read();  
  }
  Wire.endTransmission();
  
  return data;
}

void ReadBytes(uint8_t data_addr,uint8_t *data, int len)
{
  uint8_t x;
  Wire.beginTransmission(EEPROM_ADDRESS);
  Wire.write(data_addr);
  Wire.endTransmission();
  Wire.requestFrom(EEPROM_ADDRESS,len);

  if(Wire.available())
  {
    for(x = 0; x < len;x++)
    {
      data[x] = Wire.read();    
    }
    
  }
  Wire.endTransmission();
  
}


void WriteBytes(uint8_t data_addr, uint8_t *data,uint8_t len)
{

  uint8_t x;
  Wire.beginTransmission(EEPROM_ADDRESS);
  Wire.write(data_addr);
  for(x = 0; x < len; x++)
  {
    Wire.write(data[x]);  
  }
  
  Wire.endTransmission();
}
