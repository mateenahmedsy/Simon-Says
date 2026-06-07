// Simon Says Game - Updated Pin Config
const int ledPins[] = {2, 5, 12, 13};     // Shifted LEDs to open pins
const int buttonPins[] = {6, 7, 9, 10};   // Buttons stay the same
const int buzzerPos = 3;                  // Your buzzer positive pin
const int buzzerNeg = 4;                  // Your buzzer negative pin

// Audio frequencies for each game button (Hz)
const int tones[] = {262, 330, 392, 494}; 

#define MAX_SEQUENCE 100
int gameSequence[MAX_SEQUENCE];
int currentLevel = 0;

void setup() {
  // Initialize LEDs and Buttons
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT); 
  }
  
  // Set up both buzzer pins as outputs
  pinMode(buzzerPos, OUTPUT);
  pinMode(buzzerNeg, OUTPUT);
  
  // Force the negative pin to stay LOW to act as our Ground connection
  digitalWrite(buzzerNeg, LOW);
  
  // Seed the random generator using an unconnected analog pin
  randomSeed(analogRead(A0));
  
  startupSound();
  delay(1000);
}

void loop() {
  gameSequence[currentLevel] = random(0, 4);
  currentLevel++;

  showSequence();

  if (!getPlayerInput()) {
    gameOver();
    return;
  }

  delay(800);
}

// Function to flash an LED and play its corresponding tone
void lightUp(int index, int duration) {
  digitalWrite(ledPins[index], HIGH);
  tone(buzzerPos, tones[index], duration); // Sends audio signal to Pin 3
  delay(duration);
  digitalWrite(ledPins[index], LOW);
}

// Function to playback the current sequence
void showSequence() {
  for (int i = 0; i < currentLevel; i++) {
    delay(250); 
    lightUp(gameSequence[i], 400); 
  }
}

// Function to read and verify player inputs
bool getPlayerInput() {
  for (int i = 0; i < currentLevel; i++) {
    int activatedButton = -1;

    while (activatedButton == -1) {
      for (int b = 0; b < 4; b++) {
        if (digitalRead(buttonPins[b]) == HIGH) {
          activatedButton = b;
          lightUp(b, 200); 
          
          while (digitalRead(buttonPins[b]) == HIGH) {
            delay(10);
          }
        }
      }
    }

    if (activatedButton != gameSequence[i]) {
      return false; 
    }
  }
  return true; 
}

void startupSound() {
  for (int i = 0; i < 4; i++) {
    lightUp(i, 150);
  }
}

void gameOver() {
  tone(buzzerPos, 150, 500);
  
  for (int i = 0; i < 3; i++) {
    for (int l = 0; l < 4; l++) digitalWrite(ledPins[l], HIGH);
    delay(200);
    for (int l = 0; l < 4; l++) digitalWrite(ledPins[l], LOW);
    delay(200);
  }
  
  currentLevel = 0;
  delay(1000);
}