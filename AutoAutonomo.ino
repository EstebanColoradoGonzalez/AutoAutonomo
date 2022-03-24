// Modulo L298N (Puente H) --> Control motores DC
// Motor A
int ENA = 3;
int IN1 = 2;
int IN2 = 4;

// Motor B
int ENB = 5;
int IN4 = 6;
int IN3 = 7;

//Ultrasonido
int TRIGGER = 8;
int ECHO = 9;

int DURACION;
int distancia;
int velocidadA = 70;
int velocidadB = 100;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIGGER, LOW);

  Serial.begin(9600);
}

void loop() {
  distancia = medirDistancia();
  Serial.println((String) "Distancia: " + distancia);
  if ( distancia > 5 && distancia < 100) {
    if (distancia <= 19) {
      retroceder(velocidadA, velocidadB);
      Serial.println("Retrocede");
    } else if (distancia >= 21) {
      avanzar(velocidadA, velocidadB);
      Serial.println("Avanza");
    } else {
      pararMotorA();
      pararMotorB();
    }
  }
}

float medirDistancia() {
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso durante 10us
  digitalWrite(TRIGGER, LOW);

  DURACION = pulseIn(ECHO, HIGH);
  return DURACION / 59;
}

void pararMotorA() {
  analogWrite(ENA, 0);
}

void pararMotorB() {
  analogWrite(ENB, 0);
}

void avanzar(int velocidadA, int velocidadB) {
  girarLlantaIzquierdaHaciaAdelante(velocidadA);
  girarLlantaDerechaHaciaAdelante(velocidadB);
}

void retroceder(int velocidadA, int velocidadB) {
  girarLlantaIzquierdaHaciaAtras(velocidadA);
  girarLlantaDerechaHaciaAtras(velocidadB);
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
