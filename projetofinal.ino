#include <Servo.h>
#define SERVO 6

Servo s; // Variável Servo
int pos; // Posição Servo

void setup() {
  pinMode(A1, INPUT);
  pinMode(7, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  s.attach(6);
  s.write(0);
  Serial.begin(9600);

}
int botao;
int vetor[50];
int i = 0;
int numBatidas = 0;

void validarBatida() {
  for (int a = 0; a < i; a++) {
    if (((vetor[a] - vetor[a + 1]) * (-1)) > 1000) {
      numBatidas++;
      digitalWrite(8, HIGH);

      delay(500);
      digitalWrite(8, LOW);

      delay(500);
    }
  }

  if (numBatidas == 5) {
    Serial.print("numBatidas: ");
    Serial.println(numBatidas);
    s.write(90);
    delay(1000);
    s.write(0);
    digitalWrite(8, HIGH);
    delay(500);
    digitalWrite(8, LOW);
    delay(500);
    digitalWrite(8, HIGH);
    delay(500);
    digitalWrite(8, LOW);
    numBatidas = 0;

  } else {
    Serial.print("numBatidas: ");
    Serial.println(numBatidas);
    digitalWrite(9, HIGH);
    delay(500);
    digitalWrite(9, LOW);
    delay(500);
    digitalWrite(9, HIGH);
    delay(500);
    digitalWrite(9, LOW);
    numBatidas = 0;
  }

}

void escutarBatida() {
  int batida;
  int tempo;
  batida = analogRead(A1);
  if (batida >= 600 && botao == 1) {
    tempo = millis();
    Serial.print("batida: ");
    Serial.println(batida);
    if (tempo < 0) {
      tempo = tempo * (-1);
    }
    vetor[i] = tempo;
    i = i + 1;
    Serial.print("tempo");
    Serial.println(tempo);
  }


}
int cont;

void loop() {
  botao = digitalRead(7);
  Serial.println(botao);
  delay(200);

  if (botao == 1) {
    escutarBatida();
  } else if (botao == 0 && i > 0) {
    validarBatida();

    i = 0;
  }

}
