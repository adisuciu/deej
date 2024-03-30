const int NUM_SLIDERS = 5;
const int NUM_BUTTONS = 1;
const int analogInputs[NUM_SLIDERS] = {A5, A4, A3, A2, A1};
const int digitalInputs[NUM_BUTTONS] = {2};

int analogSliderValues[NUM_SLIDERS];
int digitalButtonsValues[NUM_BUTTONS];

void setup() { 
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
  }
  
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(digitalInputs[i], INPUT);
  }

  pinMode(3, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  updateSliderValues();
  sendSliderValues(); // Actually send data (all the time)
  // printSliderValues(); // For debug
  delay(50);
  digitalWrite(3, digitalButtonsValues[0]);
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
     analogSliderValues[i] = analogRead(analogInputs[i]);
  }

  for (int i = 0; i < NUM_BUTTONS; i++) {
     digitalButtonsValues[i] = !digitalRead(digitalInputs[i]);
  }

}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  if(NUM_BUTTONS > 0) {
    builtString += String("|");
  }

  for (int i = 0; i < NUM_BUTTONS; i++) {
      builtString += String((int)digitalButtonsValues[i]);

    if (i < NUM_BUTTONS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}
