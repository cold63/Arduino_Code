
#define THSourceVoltage 5.0
#define THRES       7500

const int analogPin = A0;
int value;

unsigned int temptable[] = {8019,7679,7356,7048,6754,6475,6209,5956,5714,5484,
                                    5264,5055,4855,4664,4482,4308,4143,3984,3833,3688,
                                    3549,3417,3291,3170,3054,2943,2837,2735,2637,2544,
                                    2455,2369,2286,2207,2132,2059,1989,1922,1858,1796,
                                    1736,1679,1624,1571,1521,1472,1425,1379,1336,1294,
                                    1253,1214,1176,1140,1105,1072,1039,1008,977,948,
                                    920,893,867,841,817,793,770,748,727,706,
                                    686,667,649,631,613,596};

unsigned char temp;
                                    
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(analogPin);
  temp = calTemp((THSourceVoltage * value)/1023);
  Serial.print("NTC temp: ");
  Serial.println(temp);
  Serial.println("");  
  delay(1000);
}


float calVoltage(unsigned int value)
{
  return THSourceVoltage * value/(value + THRES);
}

unsigned char calTemp(float value)
{
  unsigned char x,res;
  float xc;
  for(x = 0; x < sizeof(temptable)/sizeof(unsigned int); x++)
  {
    xc = calVoltage(temptable[x]);
    if(xc <= value)
    {
      res = 1;
      break;
    }
  }

  if(res)
    return (30 + x);

  return 0;  
}
