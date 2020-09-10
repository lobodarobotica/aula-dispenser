#include <Servo.h>

Servo myservo1;

#define sig 12
#define pinServo 10

bool flag = false;

const int k = 20;

void setup()
{
  Serial.begin(9600);
  myservo1.attach(pinServo);

}

void loop()
{
  long cm = ultrassom();

  if (cm <= 20) {

    if (flag == false) {

      myservo1.write(90);
      delay(1000);
      myservo1.write(0);
      delay(1000);
      myservo1.write(90);
      delay(1000);
      myservo1.write(0);
      delay(1000);

      flag = true;
    }

  }

  else {
    flag = false;
    myservo1.write(0);
  }


}
long ultrassom() {
  long tempo, cm;
  pinMode(sig, OUTPUT);

  digitalWrite(sig, LOW);
  delayMicroseconds(2);
  digitalWrite(sig, HIGH);
  delayMicroseconds(5);
  digitalWrite(sig, LOW);

  pinMode(sig, INPUT);
  tempo = pulseIn(sig, HIGH);
  cm = converter(tempo);

  Serial.print("Distancia: ");
  Serial.print(cm);
  Serial.print(" cm");
  Serial.println();
  return cm;
}

long converter(long microseconds)
{
  //A velocidade do som é 340 m/s ou 29 microssegundos por
  //centimetro. O sinal vai e volta, então para calcularmos
  //a distância deve-se dividir o valor da distância por 2.
  return microseconds / (29 * 2);
}

