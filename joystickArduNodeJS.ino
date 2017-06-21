#define X A0
#define Y A1
#define F 7
#define E 6
#define D 5
#define C 4
#define B 3
#define A 2
#define MIN 0
#define MAX 1024
#define MID 512
#define L (MID-MID/2)
#define H (MID+MID/2)


unsigned short xv = 1;
unsigned short yv = 1;
bool * buttons[6];
bool sendData = false;

void setup() {
  Serial.begin(9600);
  Serial.print("PROYECT_JOY!");
  unsigned long timeM = 0;
  String rec;
  do {
    if(timeM+1000<millis()) {
      timeM = millis();
      Serial.print("PROYECT_JOY!");
    }
    if(Serial.available()>0) {
      rec+=Serial.readString();
      //Serial.println(rec);
    }
  } while(rec.lastIndexOf("OK")==-1);
  for(int i=0;i<6;i++) {
    buttons[i] = 0;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(analogRead(X)<L&&xv!=0) {
    xv = 0;
    sendData = true;
  } else if(analogRead(X)>H&&xv!=2) {
    xv = 2;
    sendData = true;
  } else if(analogRead(X)>L&&analogRead(X)<H&&xv!=1) {
    xv = 1;
    sendData = true;
  }
  if(analogRead(Y)<L&&yv!=0) {
    yv = 0;
    sendData = true;
  } else if(analogRead(Y)>H&&yv!=2) {
    yv = 2;
    sendData = true;
  } else if(analogRead(Y)>L&&analogRead(Y)<H&&yv!=1) {
    yv = 1;
    sendData = true;
  }
  for(int i=2;i<=7;i++) {
    if(digitalRead(i)!=buttons[i-2]) {
      sendData = true;
      buttons[i-2] = digitalRead(i);
    }
  }
  if(sendData) {
    Serial.print("["+String(xv)+";"+String(yv)+"]");
    Serial.print("[");
    for(int i=2;i<=7;i++)
      Serial.print(buttons[i-2]?0:1);
    Serial.print("]!");
    //Serial.flush();
    sendData = false;
  }
}
