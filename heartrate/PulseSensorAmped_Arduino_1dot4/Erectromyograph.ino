unsigned long nexttime;
int analogInput = 5;
int value = 0;

void setupErectromyograph() {
  // put your setup code here, to run once:
//  Serial.begin(9600);
  nexttime = millis() + 1000;

  pinMode(analogInput, INPUT);
}

int readErectromyograph() {
  // put your main code here, to run repeatedly:

  if(nexttime>=millis())
  {
    nexttime = nexttime +1000;

    value = analogRead(analogInput); 
    sendDataToProcessing('E',value);
  }
}
