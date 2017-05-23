int val = 200;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);        // シリアル通信の初期化

}

void loop() {
  // put your main code here, to run repeatedly:

  val = 700 - val;
  
  sendDataToBLE(val, 1);

  delay(500);
}

void sendDataToBLE(int data, int data2) {
  byte buffer[1];

//  buffer[1] = data;
  buffer[0] = data >> 2;

  Serial.write(buffer, 1);

//  byte buffer[4];
//  buffer[3] = data;
//  buffer[2] = data >> 8;
//  buffer[1] = data >> 16;
//  buffer[0] = data >> 24;
  
//  Serial.write(buffer, 4);
//  Serial.print(data);
}

