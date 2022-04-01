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

float DURACION;
float distancia;
//int velocidadA = 70;
//int velocidadB = 100;

//Mathematical model
float valorDeseado = 20;
//float k1 = 20 / 3;
//float k2 = 8;
float k1 = 20 / 6;
float k2 = 6;
float error;
//float distance[5];

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
  //llenarVector();
  //vaciarVector();
  //Serial.println((String) "Distancia: " + medirDistancia());
    error = calcularError();
    //Serial.println((String) "Error: " + error);
    //Serial.println((String) "velocidad: " + calcularVelocidadM1(error));
    //Serial.println((String) "velocidad2: " + calcularVelocidadM2(error));
    if (error > 0) {
      retroceder(calcularVelocidadM1(error), calcularVelocidadM2);
      //Serial.println("Retrocede");
    } else if (error < 0) {
      avanzar(calcularVelocidadM1(error), calcularVelocidadM2(error));
      //Serial.println("Avanza");
    } else {
      pararMotorA();
      pararMotorB();
    }
 //delay(2000);
}

float calcularError() {
  return valorDeseado - medirDistancia();
}

int calcularVelocidadM1(float error) {
  if(abs(error) * k1 > 255){
    return 255;
  }else{
    return (int) abs(error) * k1;
  }
  
}

int calcularVelocidadM2(float error) {
   if(abs(error) * k2 > 233){
    return 233;
  }else{
   return (int) abs(error) * k2;
  }
}

/*
  void llenarVector() {
  for (int index = 0; index < 5; index++) {
    distance[index] = medirDistancia();
    //distance[index] = 5;
    Serial.println(distance[index]);
  }
  }

  void vaciarVector(){
  for (int index = 0; index < 5; index++) {
    distance[index] = 0;
    Serial.println(distance[index]);
  }
  }
*/

float medirDistancia() {
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso durante 10us
  digitalWrite(TRIGGER, LOW);

  DURACION = pulseIn(ECHO, HIGH);
  if(DURACION / 59 < 0){
    medirDistancia();
  }
  return DURACION / 59;
}

void pararMotorA() {
  analogWrite(ENA, 0);
}

void pararMotorB() {
  analogWrite(ENB, 0);
}

void retroceder(int velocidadA, int velocidadB) {
  girarLlantaIzquierdaHaciaAdelante(velocidadA);
  girarLlantaDerechaHaciaAdelante(velocidadB);
}

void avanzar(int velocidadA, int velocidadB) {
  girarLlantaIzquierdaHaciaAtras(velocidadA);
  girarLlantaDerechaHaciaAtras(velocidadB);
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
