int LED = 13;
int isObstaclePin1 = 8; 
int isObstaclePin2 = 9; 
int isObstacle1 = HIGH;
int isObstacle2 = HIGH;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(isObstaclePin1, INPUT);
  pinMode(isObstaclePin2, INPUT);
  Serial.begin(9600);
}

void loop() {
  isObstacle1 = digitalRead(isObstaclePin1);
  isObstacle2 = digitalRead(isObstaclePin2);
  if (isObstacle1 == LOW && isObstacle2 == LOW) {
    Serial.println("GIRAR: NO GIRAR");
    digitalWrite(LED, HIGH);
  } else if(isObstacle1 == LOW){
    Serial.println("GIRAR: IZQUIERDA");
    digitalWrite(LED, HIGH);
  }
  else if(isObstacle2 == LOW){
    Serial.println("GIRAR: DERECHA");
    digitalWrite(LED, HIGH);
  }else {
    Serial.println("GIRAR: NO GIRAR");
    digitalWrite(LED, LOW);
  }

}
