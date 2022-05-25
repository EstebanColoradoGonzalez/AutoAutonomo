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
#define kl 20
#define kr 70
#define VelocidadGiro 100
float mDistancia;
float error;
Average<float> distancias(5);

/*
    LED azul indicador de proceso retroceder
*/
//#define LED_RETROCESO 13

/*
   Sensor Infrarojo
*/
#define ObstaculoDerecha 12
#define ObstaculoIzquierda 13
int ObstaculoDerechaLectura = HIGH;
int ObstaculoIzquierdaLectura = HIGH;

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
  //pinMode(LED_RETROCESO, OUTPUT);

  // IR pin
  pinMode(ObstaculoDerecha, INPUT);
  pinMode(ObstaculoIzquierda, INPUT);

  Serial.begin(9600);
}

void loop() {
  ObstaculoDerechaLectura = digitalRead(ObstaculoDerecha);
  ObstaculoIzquierdaLectura = digitalRead(ObstaculoIzquierda);

  if (ObstaculoDerechaLectura == HIGH && ObstaculoIzquierdaLectura == LOW) {
    Izquierda(VelocidadGiro);
    pararMotorB();
  } else if (ObstaculoDerechaLectura == LOW && ObstaculoIzquierdaLectura == HIGH) {
    Derecha(VelocidadGiro);
    pararMotorA();
  } else {
    mDistancia = medirDistancia();
    error = calcularError(mDistancia);
    if (error > 0) {
      retroceder(calcularVelocidadR(error));
      Serial.println("FF");
    } else if (error < 0) {
      avanzar(calcularVelocidadA(error));
      Serial.println("F");
    } else {
      pararMotorA();
      pararMotorB();
    }
  }
}



/*
   Métodos matemáticos para el control
*/
int calcularModa() {
  llenarDistancias();
  return distancias.mode();
}

float calcularError(int rmDistancia) {
  return valorDeseado - rmDistancia;
}

int calcularVelocidadR(int dato) {
  if (abs(dato) * kl > 255) {
    return 255;
  } else {
    return (int) abs(dato) * kl;
  }
}
int calcularVelocidadA(int dato) {
  if (abs(dato) * kr > 255) {
    return 255;
  } else {
    return (int) abs(dato) * kl;
  }
}

void llenarDistancias() {
  for (int index = 0; index < 5; index++) {
    int d = medirDistancia();
    distancias.push(d);
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

void avanzar(int velocidad) {
  girarLlantaIzquierdaHaciaAdelante(velocidad);
  girarLlantaDerechaHaciaAdelante(velocidad);
}

void retroceder(int velocidad) {
  girarLlantaIzquierdaHaciaAtras(velocidad);
  girarLlantaDerechaHaciaAtras(velocidad);
}

void Izquierda(int velocidad) {
  girarLlantaIzquierdaHaciaAtras(velocidad);
  //girarLlantaDerechaHaciaAtras(velocidad);
  Serial.println("D");
}

void Derecha(int velocidad) {
  //girarLlantaIzquierdaHaciaAtras(velocidad);
  girarLlantaDerechaHaciaAtras(velocidad);
  Serial.println("L");
}

// LLantas
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
