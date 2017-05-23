int mortorPin = 8;

void setup() {
  // put your setup code here, to run once:
  pinMode(mortorPin, OUTPUT);
  digitalWrite(mortorPin, LOW);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  vibration();
}

void vibration() {
  if (Serial.available() > 0) {

    int i = Serial.read();
    
    if (i == 1) {
      digitalWrite(mortorPin, HIGH);
    } else if(i == 2) {
      digitalWrite(mortorPin, LOW);
    }
  }
}
