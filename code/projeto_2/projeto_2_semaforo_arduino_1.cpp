#define red1 13
#define yellow1 12
#define green1 11

#define red2 10
#define yellow2 9
#define green2 8

#define red3 5
#define yellow3 6
#define green3 7

#define red4 2
#define yellow4 3
#define green4 4

#define buzzer1 A1
#define buzzer2 A2

#define button1 A5
#define button2 A0
#define button3 A3
#define button4 A4

int btn1State;
int btn2State;
int btn3State;
int btn4State;

unsigned long previousMillis = 0;
unsigned long interval = 0;

enum TrafficLightState {
  GREEN1,
  YELLOW1,
  RED1,
  GREEN2,
  YELLOW2,
  RED2
};

TrafficLightState currentState = GREEN1;

void setup() {
  short leds[12] = {
    red1, red2, red3, red4,
    yellow1, yellow2, yellow3, yellow4,
    green1, green2, green3, green4
  };

  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);

  noTone(buzzer1);
  noTone(buzzer2);

  for (int index = 0; index < 12; index++) {
    pinMode(leds[index], OUTPUT);
  }
}

void loop() {
  unsigned long currentMillis = millis();

  int reading1 = digitalRead(button1);
  int reading2 = digitalRead(button2);
  int reading3 = digitalRead(button3);
  int reading4 = digitalRead(button4);

  if (reading1 == HIGH) btn1State = HIGH;
  if (reading2 == HIGH) btn2State = HIGH;
  if (reading3 == HIGH) btn3State = HIGH;
  if (reading4 == HIGH) btn4State = HIGH;

  switch (currentState) {
    case GREEN1:
      digitalWrite(red1, LOW);
      digitalWrite(red4, LOW);
    
      digitalWrite(green1, HIGH);
      digitalWrite(red2, HIGH);
      digitalWrite(red3, HIGH);
      digitalWrite(green4, HIGH);

      if (btn1State == HIGH || btn4State == HIGH) {
        sinalSound(buzzer1, 10, 200, 500);
        //btn1State = LOW;
        //btn4State = LOW;
      } else {
        interval = 7000;
      }

      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        currentState = YELLOW1;
        digitalWrite(green1, LOW);
        digitalWrite(green4, LOW);
        digitalWrite(yellow1, HIGH);
        digitalWrite(yellow4, HIGH);
      }
      break;

    case YELLOW1:
      digitalWrite(red1, LOW);
      digitalWrite(red4, LOW);
    
      if (btn1State == HIGH || btn4State == HIGH) {
        sinalSound(buzzer1, 7, 200, 200);
        btn1State = LOW;
        btn4State = LOW;
      } else {
        interval = 3000;
      }

      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        currentState = RED1;
        digitalWrite(yellow1, LOW);
        digitalWrite(yellow4, LOW);
        digitalWrite(red1, HIGH);
        digitalWrite(red4, HIGH);
      }
    
      btn1State = LOW;
      btn4State = LOW;
      break;

    case RED1:
      previousMillis = currentMillis;
      currentState = GREEN2;
      digitalWrite(red1, LOW);
      digitalWrite(red4, LOW);
      noTone(buzzer1);
      noTone(buzzer2);
      break;

    case GREEN2:
      digitalWrite(green2, HIGH);
      digitalWrite(red1, HIGH);
      digitalWrite(red4, HIGH);
      digitalWrite(green3, HIGH);
      digitalWrite(red2, LOW);
      digitalWrite(red3, LOW);

      if (btn2State == HIGH || btn3State == HIGH) {
        sinalSound(buzzer2, 10, 200, 500);
        //btn2State = LOW;
        //btn3State = LOW;
      } else {
        interval = 7000;
      }

      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        currentState = YELLOW2;
        digitalWrite(green2, LOW);
        digitalWrite(green3, LOW);
        digitalWrite(yellow2, HIGH);
        digitalWrite(yellow3, HIGH);
      }
      break;

    case YELLOW2:
      if (btn2State == HIGH || btn3State == HIGH) {
        sinalSound(buzzer2, 7, 200, 200);
        btn2State = LOW;
        btn3State = LOW;
      } else {
        interval = 3000;
      }

      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        currentState = RED2;
        digitalWrite(yellow2, LOW);
        digitalWrite(yellow3, LOW);
        digitalWrite(red2, HIGH);
        digitalWrite(red3, HIGH);
      }
      break;

    case RED2:
      previousMillis = currentMillis;
      currentState = GREEN1;
      digitalWrite(red2, LOW);
      digitalWrite(red3, LOW);
      noTone(buzzer1);
      noTone(buzzer2);
      break;
  }
}

//RESPONSAVEL PELO SINAL SONORO 
void sinalSound(int buzzer, int times, int delay1, int delay2) {
  unsigned long soundMillis = millis();
  for (int count = 0; count < times; count++) {
    if (millis() - soundMillis < delay1) {
      tone(buzzer, 2000);
    } else if (millis() - soundMillis < (delay1 + delay2)) {
      noTone(buzzer);
    } else {
      soundMillis = millis();
    }
  }
}
