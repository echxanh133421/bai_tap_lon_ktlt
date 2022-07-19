#include<Servo.h>

#define S0 9
#define S1 10
#define S2 11
#define S3 12
#define sensorOut 13

#define IN1  2
#define IN2  3
#define MAX_SPEED 255
#define MIN_SPEED 0

int c;
int cam_bien_0=6;
int cam_bien_1=7;
int cam_bien_2=8;

//tạo 2 biến myservo1-2
Servo myservo1;
Servo myservo2;

int red=0;
int green=0;
int blue=0;
int colors[3][6];

//int count_color[3]={0,0,0};

void setup()
{

  Serial.begin(9600);
  myservo1.attach(4);
  myservo2.attach(5);
  myservo1.write(0);
  myservo2.write(0);
  pinMode(S0,OUTPUT);
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(S3,OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(sensorOut,INPUT);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
}

int read_color()
{
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  red=pulseIn(sensorOut,LOW);
  delay(50);

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  green=pulseIn(sensorOut,LOW);
  delay(50);

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  blue=pulseIn(sensorOut,LOW);
  delay(50);
  for(int i=0;i<3;i++){
     if(red>=colors[i][0] && red<=colors[i][1] &&
        green>=colors[i][2] && green<=colors[i][3] &&
        blue>=colors[i][4]&& blue<=colors[i][5])
     {
            return i;
     }
  }
  return -1;
  //Serial.println("R="+(String)red+"g="+(String)green+"B="+(String)blue);
}

void initColor()
{
  //RED
  colors[0][0]=20; //Min R
  colors[0][1]=50;

  colors[0][2]=85; //Min G
  colors[0][3]=115;

  colors[0][4]=73; //Min B
  colors[0][5]=103;
  //----------------------
  //GREEN
  colors[1][0]=75; //Min R
  colors[1][1]=105;

  colors[1][2]=82; //Min G
  colors[1][3]=112;
  
  colors[1][4]=95; //Min B
  colors[1][5]=125;

  //BLUE
  colors[2][0]=84; //Min R
  colors[2][1]=114;

  colors[2][2]=86; //Min G
  colors[2][3]=116;

  colors[2][4]=52; //Min B
  colors[2][5]=82;
}
void dieu_khien_cam_bien_hong_ngoai(int cam_bien_thu_i)
{
  int cam_bien;
  Servo myservo;
  if(cam_bien_thu_i==1)
  {
    cam_bien = cam_bien_1;
    myservo = myservo1;
  }
  else if(cam_bien_thu_i==2)
  {
    cam_bien = cam_bien_2;
    myservo = myservo2;
  }
  int gia_tri = digitalRead(cam_bien);
  if(gia_tri==0)
  {
    if(cam_bien_thu_i==1)
    {
//      if(Serial.available()>0)
      Serial.print("red");
    }
    else if(cam_bien_thu_i==2)
    {
//      if(Serial.available()>0)
      Serial.print("blue");
    }
    myservo.write(50);
    delay(3000);
    myservo.write(-50);

    c=10; //Thay doi gia tri cua c de thoat vong lap
  }
}

void motor_Dung() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
void motor_Tien(int speed) { //speed: từ 0 - MAX_SPEED
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED
  digitalWrite(IN1, HIGH);
  analogWrite(IN2, 255 - speed);
}

void hamchinh(int gia_tri)
{
    if(gia_tri==0)
  {
    c=read_color();
    if(c>-1)
    {
//    if(c==0)
//    {

      while(c==0)
      {
      dieu_khien_cam_bien_hong_ngoai(1);
//      count_color[0]+=1;
      }
//    }
//    if(c==1)
//    {

      while(c==1)
      {
        int gia_tri = digitalRead(cam_bien_2);
        if(gia_tri==0)
        {
          c=10;
//          if(Serial.available()>0)
          Serial.print("green");
        }
      }
//    }
//    if(c==2)
//    {

      while(c==2)
      {
      dieu_khien_cam_bien_hong_ngoai(2);
//      count_color[1]+=1;

      }
//    }
    }
//  delay(100);
  }
}
String x;
void loop(){
  if(Serial.available()>0)
  {
    x=Serial.readString();
    int y=x.toInt();
    motor_Tien(y);

  }
//  motor_Tien(155);
  int gia_tri=digitalRead(cam_bien_0);
  initColor();
  hamchinh(gia_tri);

  }
