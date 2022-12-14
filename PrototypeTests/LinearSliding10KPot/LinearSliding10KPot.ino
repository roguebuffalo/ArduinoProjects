// AUTHOR: Me
// PURPOSE: Testing pinout and readings of sliding linear 10K pot
// TESTED ON/WORKS WITH: Leonardo

int val1 = 0;
int val2 = 0;
int val3 = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(A3, INPUT_PULLUP);
  Serial.println("Sliding pot test");
}

void loop() {
  // put your main code here, to run repeatedly:
  val1 = analogRead(A3);
  val2 = (val1 * 5.0) / 1024.0;
  val3 = 5000.0 * (val1 / 2024.0);

  Serial.print("Raw val: ");
  Serial.print(val1);
  Serial.print("\tVoltage: ");
  Serial.print(val2);
  Serial.print("\tResistance: ");
  Serial.print(val3);
  Serial.println();
  delay(500);
}
