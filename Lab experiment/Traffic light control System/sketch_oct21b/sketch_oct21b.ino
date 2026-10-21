
enum TrafficState {
  STATE_NS_GREEN,
  STATE_NS_YELLOW,
  STATE_EW_GREEN,
  STATE_EW_YELLOW
};

const int NS_RED = 2;
const int NS_YELLOW = 3;
const int NS_GREEN = 4;

const int EW_RED = 5;
const int EW_YELLOW = 6;
const int EW_GREEN = 7;

TrafficState currentState = STATE_NS_GREEN;

void allOff() {
  digitalWrite(NS_RED, LOW);
  digitalWrite(NS_YELLOW, LOW);
  digitalWrite(NS_GREEN, LOW);

  digitalWrite(EW_RED, LOW);
  digitalWrite(EW_YELLOW, LOW);
  digitalWrite(EW_GREEN, LOW);
}

void enterState(TrafficState state) {
  allOff();

  switch (state) {
    case STATE_NS_GREEN:
      digitalWrite(NS_GREEN, HIGH);
      digitalWrite(EW_RED, HIGH);
      Serial.println("STATE S0: NS GREEN / EW RED");
      break;

    case STATE_NS_YELLOW:
      digitalWrite(NS_YELLOW, HIGH);
      digitalWrite(EW_RED, HIGH);
      Serial.println("STATE S1: NS YELLOW / EW RED");
      break;

    case STATE_EW_GREEN:
      digitalWrite(NS_RED, HIGH);
      digitalWrite(EW_GREEN, HIGH);
      Serial.println("STATE S2: NS RED / EW GREEN");
      break;

    case STATE_EW_YELLOW:
      digitalWrite(NS_RED, HIGH);
      digitalWrite(EW_YELLOW, HIGH);
      Serial.println("STATE S3: NS RED / EW YELLOW");
      break;
  }
}

void setup() {
  pinMode(NS_RED, OUTPUT);
  pinMode(NS_YELLOW, OUTPUT);
  pinMode(NS_GREEN, OUTPUT);

  pinMode(EW_RED, OUTPUT);
  pinMode(EW_YELLOW, OUTPUT);
  pinMode(EW_GREEN, OUTPUT);

  Serial.begin(9600);

  enterState(STATE_NS_GREEN);
}

void loop() {
  delay(10000);

  currentState = STATE_NS_YELLOW;
  enterState(currentState);
  delay(3000);

  currentState = STATE_EW_GREEN;
  enterState(currentState);
  delay(10000);

  currentState = STATE_EW_YELLOW;
  enterState(currentState);
  delay(3000);

  currentState = STATE_NS_GREEN;
  enterState(currentState);
}
