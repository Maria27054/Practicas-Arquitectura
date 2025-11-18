// Pines de los LEDs
const int ledPins[] = {8, 9, 10, 11, 12};
const int numLEDs = 5;

// Variables de tiempo
unsigned long previousMillis = 0;

// Secuencia
enum State {SOS, BLINK, FADE, WAIT_FADE_END};
State currentState = SOS;
int subStep = 0;      // paso dentro de cada bloque
bool ledOn = false;
bool fadeUp = true;
int fadeValue = 0;

// Configuración de tiempos
const int sosPattern[9] = {1,1,1, 3,3,3, 1,1,1}; // 1=corto, 3=largo
const unsigned long shortFlash = 200; // ms
const unsigned long longFlash = 600;  // ms
const unsigned long blinkTime = 500;  // ms
const unsigned long fadeStepTime = 30; // ms por incremento de fade
const unsigned long waitAfterFade = 2000; // ms final Fade

unsigned long stepStart = 0;

void setup() {
  for(int i = 0; i < numLEDs; i++){
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void loop() {
  unsigned long currentMillis = millis();

  switch(currentState){
    case SOS:
      runSOS(currentMillis);
      break;
    case BLINK:
      runBlink(currentMillis);
      break;
    case FADE:
      runFade(currentMillis);
      break;
    case WAIT_FADE_END:
      if(currentMillis - stepStart >= waitAfterFade){
        currentState = SOS;
        subStep = 0;
        fadeUp = true;
        fadeValue = 0;
      }
      break;
  }
}

// Funciones

void runSOS(unsigned long now){
  unsigned long duration = sosPattern[subStep] == 1 ? shortFlash : longFlash;

  if(now - stepStart >= duration){
    stepStart = now;
    ledOn = !ledOn;
    digitalWriteAll(ledOn);

    if(!ledOn){ // solo contar subStep cuando se apaga
      subStep++;
      if(subStep >= 9){
        subStep = 0;
        currentState = BLINK;
        digitalWriteAll(false);
        stepStart = now;
      }
    }
  }
}

void runBlink(unsigned long now){
  if(now - stepStart >= blinkTime){
    stepStart = now;
    ledOn = !ledOn;
    digitalWriteAll(ledOn);

    if(!ledOn){
      subStep++;
      if(subStep >= 7){ // 7 veces
        subStep = 0;
        currentState = FADE;
        stepStart = now;
        fadeValue = 0;
        fadeUp = true;
      }
    }
  }
}

void runFade(unsigned long now){
  if(now - stepStart >= fadeStepTime){
    stepStart = now;

    if(fadeUp){
      fadeValue += 5;
      if(fadeValue >= 255) fadeUp = false;
    } else {
      fadeValue -= 2;
      if(fadeValue <= 0){
        fadeValue = 0;
        currentState = WAIT_FADE_END;
        stepStart = now;
      }
    }

    for(int i = 0; i < numLEDs; i++){
      analogWrite(ledPins[i], fadeValue);
    }
  }
}

// Función para encender/apagar todos los LEDs
void digitalWriteAll(bool state){
  for(int i = 0; i < numLEDs; i++){
    digitalWrite(ledPins[i], state ? HIGH : LOW);
  }
}
