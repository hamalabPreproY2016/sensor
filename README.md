# sensor

### heartrate
心拍センサ動かすコード。センサは5V、GND、アナログ0番ピンに刺す  
arduinoはフォルダ内のソースまとめて書き込むので、適当なファイルをIDEで開いて書き込めば動きます。

### mortor
振動モータ用。モータはデジタル8番ピンとGNDに刺す  
1を書き込むと動いて2を書き込むと止まる。

### myo
筋電位センサ用。センサは5V、GND、アナログ0番ピンへ。
一秒おきにセンサの値を書き出す。

### test
テスト用。0.5秒おきに200と700を交互に書き込む。

## 注意
heartrate、mortor、testで書き込まれた値は1バイトに抑えるために2ビット右シフトしてます。  
表示の値を2ビット左シフトした値（×４した値）が正しい値です。
