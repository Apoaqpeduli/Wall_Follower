#include <AutoPID.h>

#define OUTPUT_MIN 0
#define OUTPUT_MAX 255
#define KP .12
#define KI .0003
#define KD 0

const int trigPin_FR = 8;
const int echoPin_FR = 9;
long Duration_FR;
int Distance_FR;

//pin motor
int mot_fr = 7;
int mot_fl = 5;
int mot_br = 6;
int mot_bl = 4;
int ENA = 10; //Kiri
int ENB = 11; //Kanan
int nENA = 150, nENB = 150;

double dis_FR, dis_FL, setPoint, outputVal_R,outputVal_L;

AutoPID myPID_kanan(&dis_FR, &setPoint, &outputVal_R, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);
AutoPID myPID_kiri(&dis_FL, &setPoint, &outputVal_L, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);

void setup() {
  Serial.begin(9600);

  //MOTOR
  pinMode(mot_fr, OUTPUT);
  pinMode(mot_fl, OUTPUT);
  pinMode(mot_br, OUTPUT);
  pinMode(mot_bl, OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

  //HCSR
  pinMode(trigPin_FR, OUTPUT);
  pinMode(echoPin_FR, INPUT);
  delay(1000);
  
  myPID_kanan.setTimeStep(100);
}

void loop() {
  setPoint = 5; //5cm
  readHCSR_FR();
  myPID_kanan.run();
  gerakMotor();
}

void readHCSR_FR(){
  digitalWrite(trigPin_FR, LOW);
  delayMicroseconds(2);
 
  digitalWrite(trigPin_FR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_FR, LOW);
 
  Duration_FR = pulseIn(echoPin_FR, HIGH);
  Distance_FR = Duration_FR*(0.034/2);
  dis_FR=Distance_FR;
 
  Serial.print("Distance Front Right: "); Serial.println(Distance_FR);
}

void gerakMotor(){
  digitalWrite(mot_br, HIGH);
  digitalWrite(mot_bl, LOW);
  digitalWrite(mot_fr, HIGH);
  digitalWrite(mot_fl, LOW);
  analogWrite(ENA, 255); //kiri
  analogWrite(ENB, outputVal_R ); //kanan
}
