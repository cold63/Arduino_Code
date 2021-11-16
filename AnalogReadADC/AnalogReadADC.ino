

const int analogPin = A0;
int value;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(analogPin);
  Serial.print("Value:");
  Serial.println(value);

  Serial.print("Voltage:");
  Serial.print((5.0 * value)/1023);
  Serial.println(" V");
  Serial.println("");
  delay(1000);
}
