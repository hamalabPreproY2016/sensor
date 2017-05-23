
/*  Pulse Sensor Amped 1.4    by Joel Murphy and Yury Gitman   http://www.pulsesensor.com

----------------------  Notes ----------------------  ---------------------- 
This code:
1) Blinks an LED to User's Live Heartbeat   PIN 13
2) Fades an LED to User's Live HeartBeat
3) Determines BPM
4) Prints All of the Above to Serial

Read Me:
https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/README.md   
 ----------------------       ----------------------  ----------------------
*/

//  Variables
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin

int RTCPin = 3;
int CTSPin = 4;

int mortorPin = 8;

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded! 
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat". 
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = false;   // Set to 'false' by Default.  Re-set to 'true' to see Arduino Serial Monitor ASCII Visual Pulse 

boolean isFirstRead = true;

void setup(){
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  pinMode(fadePin,OUTPUT);          // pin that will fade to your heartbeat!

  pinMode(mortorPin, OUTPUT);
  
  digitalWrite(mortorPin, LOW);

  Serial.begin(9600);             // we agree to talk fast!
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 
   // IF YOU ARE POWERING The Pulse Sensor AT VOLTAGE LESS THAN THE BOARD VOLTAGE, 
   // UN-COMMENT THE NEXT LINE AND APPLY THAT VOLTAGE TO THE A-REF PIN
//   analogReference(EXTERNAL);   

  setupErectromyograph();
}


//  Where the Magic Happens
void loop(){
//  serialOutput() ;       
  vibration();

  sendDataToProcessing('S', Signal);     // send Processing the raw Pulse Sensor data
  if (QS == true){     // A Heartbeat Was Found
                       // BPM and IBI have been Determined
                       // Quantified Self "QS" true when arduino finds a heartbeat
        fadeRate = 255;         // Makes the LED Fade Effect Happen
                                // Set 'fadeRate' Variable to 255 to fade LED with pulse
        sendDataToProcessing('B',BPM);   // send heart rate with a 'B' prefix
        sendDataToProcessing('Q',IBI);   // send time between beats with a 'Q' prefix
        sendDataToBLE(IBI);

        //serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.     
        QS = false;                      // reset the Quantified Self flag for next time    
  }
  readErectromyograph();
  ledFadeToBeat();                      // Makes the LED Fade Effect Happen 
  delay(200);                             //  take a break

//  Serial.print("RTS:");
//  Serial.println(analogRead(RTCPin));
//  
//  Serial.print("CTS:");
//  Serial.println(analogRead(CTSPin));
}

void sendDataToProcessing(char symbol, int data ){
//    Serial.print(symbol);                // symbol prefix tells Processing what type of data is coming
//    Serial.print(",");
//    Serial.println(data);                // the data to send culminating in a carriage return
}

void ledFadeToBeat(){
    fadeRate -= 15;                         //  set LED fade value
    fadeRate = constrain(fadeRate,0,255);   //  keep LED fade value from going into negative numbers!
    analogWrite(fadePin,fadeRate);          //  fade LED
  }

void vibration() {
  if (Serial.available() > 0) {
//    if(isFirstRead) {
//    if(true) {
//      Serial.println(Serial.available());  
//      while(Serial.available()) {
//        Serial.read();
//      }
//      isFirstRead = false;
//      return;
//    }
    int i = Serial.read();
//    Serial.println(i);
    if (i == 1) {
      digitalWrite(mortorPin, HIGH);
    } else if(i == 2) {
      digitalWrite(mortorPin, LOW);
    }
//    Serial.println(i);
//    if(str == "ON") {
//      digitalWrite(mortorPin, HIGH);
//    } else if(str == "OFF"){
//      digitalWrite(mortorPin, LOW);
//    }
  }
}

void sendDataToBLE(int data) {
  byte buffer = data >> 2 & 0xFF;
  
  Serial.write(buffer);
//  Serial.print(data);
}


//void sendDataToBLE(int data) {
//  byte buffer[2];
//  buffer[1] = data;
//  buffer[0] = data >> 8;
//  
//  Serial.write(buffer, 2);
////  Serial.print(data);
//}

