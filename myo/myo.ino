int analogPin = 0; // ポテンショメータのワイプ(中央の端子)を接続する
                       // 両端はグランドと+5Vに接続
int val = 0;           // 読み取った値を格納する変数

void setup() {
  Serial.begin(9600);        // シリアル通信の初期化

  pinMode (analogPin,INPUT);
}

void loop() {
  val = analogRead(analogPin);    // アナログピンを読み取る

//  sendDataToBLE(val);

  sendDataToBLE(val);

  delay(1000);
}

void sendDataToBLE(int data) {
  byte buffer = data >> 2 & 0xFF;
  
  Serial.write(buffer);
//  Serial.print(data);
}

