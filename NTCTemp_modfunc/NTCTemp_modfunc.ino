
#define THSourceVoltage 5.0
#define THRES       7500
#define RT0         10000  // 常溫 25度時的 NTC 電阻值
#define RT1         35563  // 0度時的 NTC 電阻值
#define RT2         596    // 105度時的 NTC 電阻值
#define T0          298.15 // 常溫 25度時的 Kelvin 值
#define T1          273.15 // 0度時的 Kelvin 值
#define T2          378.15 // 105度時的 Kelvin 值

const int analogPin = A0;
int value;
float VoltageOut;
float ROut; 
float beta;
float Rx;
float KelvinValue;
                                   
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  beta = (log(RT1/RT2))/((1/T1)-(1/T2));
  Rx = RT0 * exp(-beta/T0);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(analogPin);

  Serial.print("NTC Temp: ");
  
  VoltageOut = (THSourceVoltage * value)/1023;
  ROut = THRES * VoltageOut/ (THSourceVoltage - VoltageOut); //目前 NTC 電阻值
  KelvinValue=(beta/log(ROut/Rx)); 
  
  Serial.println(KelvinValue - 273.15); //Kelvin 轉 溫度C
  Serial.println("");  
  delay(1000);
}
