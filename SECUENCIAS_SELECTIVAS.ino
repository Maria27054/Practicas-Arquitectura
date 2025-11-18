// Pines LEDs
const int ledSOS   = 8;
const int ledBlink = 9;
const int ledFade  = 10;

// Pines botones
const int btnSOS   = 2;
const int btnBlink = 3;
const int btnFade  = 4;

// Variables SOS
const int sosPattern[9] = {1,1,1,3,3,3,1,1,1}; // 1=punto, 3=raya
const unsigned long dotTime = 400; // tiempo lento
int sosStep = 0;
bool sosLEDOn = false;
bool sosActive = false;
unsigned long sosTimer = 0;

// Variables Blink 
int blinkCount = 0;
bool blinkState = false;
bool blinkActive = false;
unsigned long blinkTimer = 0;
const unsigned long blinkInterval = 500;

// Variables Fade
bool fadeUp = true;
bool fadeActive = false;
int fadeValue = 0;
unsigned long fadeTimer = 0;
const unsigned long fadeStepTime = 40;

void setup() {
  pinMode(ledSOS, OUTPUT);
  pinMode(ledBlink, OUTPUT);
  pinMode(ledFade, OUTPUT);

  pinMode(btnSOS, INPUT_PULLUP);
  pinMode(btnBlink, INPUT_PULLUP);
  pinMode(btnFade, INPUT_PULLUP);

  // Apagar todos los LEDs al inicio
  digitalWrite(ledSOS, LOW);
  digitalWrite(ledBlink, LOW);
  analogWrite(ledFade, 0);
}

void loop() {
  unsigned long currentMillis = millis();

  // Botón SOS 
  if (digitalRead(btnSOS) == LOW && !sosActive && !blinkActive && !fadeActive){
    sosActive = true;
    sosStep = 0;
    sosLEDOn = false;
    sosTimer = currentMillis;
  }

  // Botón Blink 
  if (digitalRead(btnBlink) == LOW && !blinkActive && !sosActive && !fadeActive){
    blinkActive = true;
    blinkCount = 0;
    blinkState = false;
    blinkTimer = currentMillis;
  }

  // Botón Fade
  if (digitalRead(btnFade) == LOW && !fadeActive && !sosActive && !blinkActive){
    fadeActive = true;
    fadeUp = true;
    fadeValue = 0;
    fadeTimer = currentMillis;
  }

  // Ejecutar SOS 
  if(sosActive){
    unsigned long duration = (sosPattern[sosStep]==1?dotTime:dotTime*3);
    if(currentMillis - sosTimer >= duration){
      sosTimer = currentMillis;
      sosLEDOn = !sosLEDOn;
      digitalWrite(ledSOS,sosLEDOn);

      if(!sosLEDOn){ // avanzar al siguiente paso solo cuando apaga
        sosStep++;
        if(sosStep>=9){
          sosActive=false;
          digitalWrite(ledSOS,LOW);
          delay(500); // pausa final
        }
      }
    }
  }

  // Ejecutar Blink 
  if(blinkActive){
    if(currentMillis - blinkTimer >= blinkInterval){
      blinkTimer = currentMillis;
      blinkState = !blinkState;
      digitalWrite(ledBlink, blinkState);

      if(!blinkState){ // contar solo cuando apaga
        blinkCount++;
        if(blinkCount>=7){
          blinkActive=false;
          digitalWrite(ledBlink,LOW);
          delay(500); // pausa final
        }
      }
    }
  }

  // Ejecutar Fade 
  if(fadeActive){
    if(currentMillis - fadeTimer >= fadeStepTime){
      fadeTimer = currentMillis;
      if(fadeUp){
        fadeValue+=5;
        if(fadeValue>=255) fadeUp=false;
      } else {
        fadeValue-=5;
        if(fadeValue<=0){
          fadeValue=0;
          fadeActive=false;
          analogWrite(ledFade,0);
          delay(1000); // pausa final
        }
      }
      analogWrite(ledFade,fadeValue);
    }
  }
}
