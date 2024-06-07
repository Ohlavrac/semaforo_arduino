//Semaforo 1 quadra 1
#define red1 13
#define yellow1 12
#define green1 11

//Semaforo 2 quadra 1
#define red2 10
#define yellow2 9
#define green2 8

//Semaforo 3 quadra 1
#define red3 5
#define yellow3 6
#define green3 7

//Semafoto 4 quadra 1
#define red4 2
#define yellow4 3
#define green4 4

#define buzzer1 A1 //SEMAPHORO 1 & 4
#define buzzer2 A2 //SEMAPHORO 2 & 3

void setup()
{
  short leds[12] = {
    red1,
    red2,
    red3,
    red4,
    yellow1,
    yellow2,
    yellow3,
    yellow4,
    green1,
    green2,
    green3,
    green4
  };
  
  //define os buzzers como saida
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  
  //garante que os buzzers começam sem som
  noTone(buzzer1);
  noTone(buzzer2);
  
  for(int index = 0; index < 12; index++)
  	pinMode(leds[index], OUTPUT);
}

void loop()
{
  semaphoro1C1();
  clear();
  semaphoro2C1();
  clear();
}

//CONTROLA OS SINAIS DA VIA 1 VERTICAL
int semaphoro1C1() {
  for (int index = 11; index <= 13; index++){
    digitalWrite(index, HIGH);
    if (digitalRead(green1) == HIGH) {
      digitalWrite(red2, HIGH);
      digitalWrite(red3, HIGH);
      digitalWrite(green4, HIGH);
      sinalSound(buzzer1, 10, 200, 500); //7 segs verde
    } else if (digitalRead(yellow1) == HIGH){
      digitalWrite(red3, HIGH);
      digitalWrite(red2, HIGH);
      digitalWrite(green4, LOW);
      digitalWrite(yellow4, HIGH);
      sinalSound(buzzer1, 7, 200, 200); //3 segs amarelo
    } else {
      digitalWrite(yellow4, LOW);
      digitalWrite(red4, HIGH);
      noTone(buzzer1);
      noTone(buzzer2);
      return 0;
    }
    digitalWrite(index, LOW);
  }
}

//CONTROLA OS SINAIS DA VIA 2 HORIZONTAL
int semaphoro2C1() {
  for (int index = 8; index <= 10; index++){
    digitalWrite(index, HIGH);
    if (digitalRead(green2) == HIGH) {
      digitalWrite(red1, HIGH);
      digitalWrite(red4, HIGH);
      digitalWrite(green3, HIGH);
      sinalSound(buzzer2, 10, 200, 500); //7 segs verde
    } else if (digitalRead(yellow2) == HIGH){
      digitalWrite(red4, HIGH);
      digitalWrite(red1, HIGH);
      digitalWrite(green3, LOW);
      digitalWrite(yellow3, HIGH);
      sinalSound(buzzer2, 7, 200, 200); //3 segs amarelo
    } else {
      digitalWrite(yellow3, LOW);
      digitalWrite(red3, HIGH);
      noTone(buzzer1);
      noTone(buzzer2);
      return 0;
    }
    digitalWrite(index, LOW);
  }
}

//GARANTE QUE SEMPRE VAI LIMPAR OS SEMAFOROS
void clear() {
  for (int index = 2; index <= 13; index++) {
    digitalWrite(index, LOW);
  }
}

//RESPONSAVEL PELO SINAL SONORO 
void sinalSound(int buzzer, int times, int delay1, int delay2) {
  for (int count = 0; count <= times; count++){
    tone(buzzer, 2000);
  	delay(delay1);
  	noTone(buzzer);
  	delay(delay2);
  }
}