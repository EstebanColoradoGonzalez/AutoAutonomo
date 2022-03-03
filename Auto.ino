// Modulo L298N (Puente H) --> Control motores DC
// Motor A
int ENA = 3;
int IN1 = 2;
int IN2 = 4;

// Motor B
int ENB = 5;
int IN4 = 6;
int IN3 = 7;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  delay(2000);
  avanzar();
  girarDerecha();
  delay(500);
  pararMotorB();
  delay(500);
  girarIzquierda();
  delay(500);
  pararMotorB();
  pararMotorA();
  delay(2000);
  retroceder();
  delay(1000);
  pararMotorA();
  delay(4000);
}

void pararMotorA() {
    analogWrite(ENA, 0);
}

void pararMotorB() {
    analogWrite(ENB, 0);
}

void retroceder() {
  analogWrite(ENA, 70);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void avanzar() {
  analogWrite(ENA, 80);
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
