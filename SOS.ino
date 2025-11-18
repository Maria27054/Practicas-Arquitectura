// Pines de los LEDs (puedes usar varios, todos harán lo mismo)
const int ledPins[] = {8, 9, 10, 11, 12};
const int numLEDs = 5;

// Configuración de tiempos para Morse
const unsigned long dotTime = 250;       // Duración de un punto (en ms)
const unsigned long dashTime = dotTime*3; // Duración de un guion
const unsigned long symbolSpace = dotTime; // Espacio entre puntos/guiones
const unsigned long letterSpace = dotTime*3; // Espacio entre letras

void setup() {
  // Configura todos los LEDs como salida
  for(int i=0; i<numLEDs; i++){
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void loop() {
  // SOS en Morse: ... --- ...

  // S: ...
  morseDot();
  morseDot();
  morseDot();
  delay(letterSpace); // espacio entre letras

  // O: ---
  morseDash();
  morseDash();
  morseDash();
  delay(letterSpace); // espacio entre letras

  // S: ...
  morseDot();
  morseDot();
  morseDot();
  delay(letterSpace*2); // espacio antes de repetir SOS
}

// Funciones para Morse 
void morseDot() {
  digitalWriteAll(HIGH);
  delay(dotTime);
  digitalWriteAll(LOW);
  delay(symbolSpace);
}

void morseDash() {
  digitalWriteAll(HIGH);
  delay(dashTime);
  digitalWriteAll(LOW);
  delay(symbolSpace);
}

// Función para encender/apagar todos los LEDs juntos
void digitalWriteAll(bool state){
  for(int i=0; i<numLEDs; i++){
    digitalWrite(ledPins[i], state ? HIGH : LOW);
  }
}
