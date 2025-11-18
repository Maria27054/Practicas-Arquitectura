// pines LEDs
const int leds[] = {8,9,10,11,12};
const int numLeds = 5;

// botón de pausa
const int btnPause = 2;

// variables generales
bool paused = false;

// SOS
const int sosPattern[9] = {1,1,1,3,3,3,1,1,1}; // 1=punto, 3=raya
const unsigned long dotTime = 400;
int sosStep = 0;
bool sosLEDOn = false;
unsigned long sosTimer = 0;
bool sosActive = true;

// Blink 
int blinkCount = 0;
bool blinkState = false;
unsigned long blinkTimer = 0;
const unsigned long blinkInterval = 500;
bool blinkActive = false;

// Fade 
int fadeValue = 0;
bool fadeUp = true;
unsigned long fadeTimer = 0;
const unsigned long fadeStepTime = 40;
bool fadeActive = false;

void setup() {
  for(int i=0;i<numLeds;i++) pinMode(leds[i], OUTPUT);
  pinMode(btnPause, INPUT_PULLUP);

  // Apagar todos
  for(int i=0;i<numLeds;i++) analogWrite(leds[i],0);

  // Iniciar SOS
  sosActive = true;
  sosStep = 0;
  sosLEDOn = false;
  sosTimer = millis();
}

void loop() {
  unsigned long currentMillis = millis();

  // Leer botón de pausa
  if(digitalRead(btnPause)==LOW){
    paused = true;
  } else {
    paused = false;
  }

  // Secuencia SOS 
  if(sosActive && !paused){
    unsigned long duration = (sosPattern[sosStep]==1?dotTime:dotTime*3);
    if(currentMillis - sosTimer >= duration){
      sosTimer = currentMillis;
      sosLEDOn = !sosLEDOn;
      for(int i=0;i<numLeds;i++) digitalWrite(leds[i],sosLEDOn);

      if(!sosLEDOn){ // avanza al siguiente paso solo cuando apaga
        sosStep++;
        if(sosStep>=9){
          sosActive=false;
          for(int i=0;i<numLeds;i++) digitalWrite(leds[i],LOW);
          delay(500);
          blinkActive = true;
          blinkCount=0;
          blinkState=false;
          blinkTimer=currentMillis;
        }
      }
    }
  }

  // Secuencia Blink 7 veces 
  if(blinkActive && !paused){
    if(currentMillis - blinkTimer >= blinkInterval){
      blinkTimer=currentMillis;
      blinkState=!blinkState;
      for(int i=0;i<numLeds;i++) digitalWrite(leds[i],blinkState);
      if(!blinkState){ // contar solo cuando apaga
        blinkCount++;
        if(blinkCount>=7){
          blinkActive=false;
          for(int i=0;i<numLeds;i++) digitalWrite(leds[i],LOW);
          delay(500);
          fadeActive = true;
          fadeValue=0;
          fadeUp=true;
          fadeTimer=currentMillis;
        }
      }
    }
  }

  // Secuencia Fade 
  if(fadeActive && !paused){
    if(currentMillis - fadeTimer >= fadeStepTime){
      fadeTimer=currentMillis;
      if(fadeUp){
        fadeValue+=5;
        if(fadeValue>=255) fadeUp=false;
      } else {
        fadeValue-=5;
        if(fadeValue<=0){
          fadeValue=0;
          fadeActive=false;
          for(int i=0;i<numLeds;i++) analogWrite(leds[i],0);
          delay(1000); // pausa final antes de reiniciar
          // Reiniciar ciclo
          sosActive=true;
          sosStep=0;
          sosLEDOn=false;
          sosTimer=currentMillis;
        }
      }
      for(int i=0;i<numLeds;i++) analogWrite(leds[i],fadeValue);
    }
  }
}
