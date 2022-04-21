// Importaciónde de Librerias
#include <Average.h>


/*
   Modulo L298N (Puente H) --> Control motores DC
   cosntantes de las conexiones de cada uno de los pines L298N/Arduino

*/
#define ENA  3
#define IN1  2
#define IN2  4

#define ENB  5
#define IN4  6
#define IN3  7

/*
   Sensor Ultrasonido analogico SH-05

*/
#define TRIGGER 8
#define ECHO  9

float DURACION;
float distancia;


/*
   Modelo de control
   definimos el valor deseado, así como las las contantes para cada unos de los motores.
   variables para calculos

*/
float valorDeseado = 20;
#define kl 4
#define kr 7
float mDistancia;
float error;
Average<float> distancias(5);

/*
   LED azul indicador de proceso retroceder

*/
#define LED_RETROCESO 13

void setup() {
  // pines motores
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // pines ultrasonido
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIGGER, LOW);

  // pin LED
  pinMode(LED_RETROCESO, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  mDistancia = calcularModa();
  //int MDistancia = distancias.mean();
  //Serial.println("-------------");
  //Serial.println((String) "Moda: " + mDistancia);
  //Serial.println((String) "Media: " + MDistancia);
  error = calcularError(mDistancia);
  //Serial.println((String) "error: "+error);
  //girarLlantaDerechaHaciaAdelante(calcularVelocidadM2(error));
  //Serial.println("-------------------");
  //Serial.println((String) "Distancia: " + medirDistancia());
  if (error > 0) {
    retroceder(calcularVelocidadM2(error), calcularVelocidadM2(error));
    digitalWrite(LED_RETROCESO, HIGH);
  } else if (error < 0) {
    avanzar(calcularVelocidadM1(error), calcularVelocidadM1(error));
    digitalWrite(LED_RETROCESO, LOW);
  } else {
    pararMotorA();
    pararMotorB();
    digitalWrite(LED_RETROCESO, LOW);
  }
  //delay(1000);
}

/*
   Métodos matemáticos para el control

*/
int calcularModa() {
  llenarDistancias();
  //delay(1000);
  return distancias.mode();

}

float calcularError(int rmDistancia) {
  return valorDeseado - rmDistancia;
}

int calcularVelocidadM1(float error) {
  if (abs(error) * kl > 255) {
    return 255;
  } else {
    return (int) abs(error) * kl;
  }

}

int calcularVelocidadM2(float error) {
  if (abs(error) * kr > 255) {
    return 255;
  } else {
    return (int) abs(error) * kr;
  }
}

void llenarDistancias() {
  for (int index = 0; index < 5; index++) {
    int d = medirDistancia();
    distancias.push(d);
    //Serial.println((String) "Distancia: " + d);
    //Serial.println(distance[index]);
  }
}

int medirDistancia() {
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  DURACION = pulseIn(ECHO, HIGH);
  return DURACION / 59;
}

/*
   Métodos para el control de los motoreductores DC

*/
void pararMotorA() {
  analogWrite(ENA, 0);
}

void pararMotorB() {
  analogWrite(ENB, 0);
}

void avanzar(int velocidadA, int velocidadB) {
  girarLlantaIzquierdaHaciaAdelante(velocidadA);
  girarLlantaDerechaHaciaAdelante(velocidadB);
  Serial.println("Avanza");
}

void retroceder(int velocidadA, int velocidadB) {
  girarLlantaIzquierdaHaciaAtras(velocidadA);
  girarLlantaDerechaHaciaAtras(velocidadB);
  Serial.println("Retrocede");
}

void Izquierda(int velocidadA, int velocidadB) {
  girarLlantaIzquierdaHaciaAdelante(velocidadA);
  girarLlantaDerechaHaciaAtras(velocidadB);
}

void Derecha(int velocidadA, int velocidadB) {
  girarLlantaIzquierdaHaciaAtras(velocidadA);
  girarLlantaDerechaHaciaAdelante(velocidadB);
}

void girarLlantaIzquierdaHaciaAtras(int velocidad) {
  analogWrite(ENA, velocidad);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void girarLlantaDerechaHaciaAtras(int velocidad) {
  analogWrite(ENB, velocidad);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void girarLlantaIzquierdaHaciaAdelante(int velocidad) {
  analogWrite(ENA, velocidad);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void girarLlantaDerechaHaciaAdelante(int velocidad) {
  analogWrite(ENB, velocidad);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
