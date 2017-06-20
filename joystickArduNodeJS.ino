#define X A0
#define Y A1

unsigned short xv = 1;
unsigned short yv = 1;
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
  //Serial.write("OK!");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(analogRead(X)<400&&xv!=0) {
    xv = 0;
    sendData = true;
  } else if(analogRead(X)>700&&xv!=2) {
    xv = 2;
    sendData = true;
  } else if(analogRead(X)>400&&analogRead(X)<700&&xv!=1) {
    xv = 1;
    sendData = true;
  }
  if(analogRead(Y)<400&&yv!=0) {
    yv = 0;
    sendData = true;
  } else if(analogRead(Y)>700&&yv!=2) {
    yv = 2;
    sendData = true;
  } else if(analogRead(Y)>400&&analogRead(Y)<700&&yv!=1) {
    yv = 1;
    sendData = true;
  }
  if(sendData) {
    Serial.print("["+String(xv)+";"+String(yv)+"]!");
    //Serial.flush();
    sendData = false;
  }
}
