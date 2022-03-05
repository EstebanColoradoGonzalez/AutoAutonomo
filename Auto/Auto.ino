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

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  Serial.begin(9600);
}

void loop() {
  distancia = medirDistancia();
  while ( distancia > 10 && distancia < 40) {

    Serial.println((String) "Distancia: " + distancia);
    if (distancia == 20) {
      pararMotorA();
    }
    if(distancia < 20 && distancia > 18){
      retroceder(255);
    }
    if(distancia > 20 && distancia < 22){
      avanzar(100);
    }
    distancia = medirDistancia();
    pararMotorA();
  }
  pararMotorA();
}

float medirDistancia() {
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);

  DURACION = pulseIn(ECHO, HIGH);
  return DURACION / 58.2;
}

void pararMotorA() {
  analogWrite(ENA, 0);
}

void pararMotorB() {
  analogWrite(ENB, 0);
}

void retroceder(int velocidad) {
  analogWrite(ENA, velocidad);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void avanzar(int velocidad) {
  analogWrite(ENA, velocidad);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void girarDerecha() {
  analogWrite(ENB, 200);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void girarIzquierda() {
  analogWrite(ENB, 200);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
