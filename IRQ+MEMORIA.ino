// LEDs
int leds[] = {8, 9, 10, 11, 12};

// Botones
int botonPause = 2;
int botonResume = 3;

// Control de secuencia
int estadoSecuencia = 0;    // 0 = SOS, 1 = Blink, 2 = Fade
int pasoInterno = 0;        // Guarda progreso interno
bool pausado = false;

// Tiempo entre secuencias (2 segundos)
int pausaEntreSecuencias = 2000;

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
  }

  pinMode(botonPause, INPUT_PULLUP);
  pinMode(botonResume, INPUT_PULLUP);
}

void loop() {

  // -------- PAUSA ----------
  if (digitalRead(botonPause) == LOW) {
    pausado = true;
    esperarSoltar(botonPause);
  }

  // -------- REANUDAR --------
  if (digitalRead(botonResume) == LOW) {
    pausado = false;
    esperarSoltar(botonResume);
  }

  if (pausado) return;  // detiene TODO

  // ----------- CONTROL GENERAL DE SECUENCIA -----------
  switch (estadoSecuencia) {

    case 0:  // SOS
      if (SOS()) { 
        esperarPausaSecuencia(); 
        estadoSecuencia = 1; 
        pasoInterno = 0; 
      }
      break;

    case 1:  // BLINK 7 VECES
      if (blink7()) { 
        esperarPausaSecuencia();
        estadoSecuencia = 2; 
        pasoInterno = 0; 
      }
      break;

    case 2:  // FADE
      if (fade()) { 
        esperarPausaSecuencia();
        estadoSecuencia = 0; 
        pasoInterno = 0; 
      }
      break;
  }
}

// ==========================================================
//                      FUNCIONES
// ==========================================================

// ------------------- SOS -------------------
bool SOS() {
  int dot = 300;
  int dash = 900;

  // Secuencia SOS total = 9 pasos
  int duraciones[] = {dot, dot, dot, dash, dash, dash, dot, dot, dot};

  if (pasoInterno >= 9) return true;

  encenderTodos();
  delayConPausa(duraciones[pasoInterno]);
  apagarTodos();
  delayConPausa(dot);

  pasoInterno++;
  return false;
}

// ------------------- BLINK 7 VECES -------------------
bool blink7() {
  if (pasoInterno >= 7) return true;

  encenderTodos();
  delayConPausa(500);
  apagarTodos();
  delayConPausa(500);

  pasoInterno++;
  return false;
}

// ------------------- FADE -------------------
bool fade() {

  if (pasoInterno < 256) { // Subida
    int b = pasoInterno;
    setBrillo(b);
    pasoInterno++;
    delayConPausa(20);
    return false;

  } else if (pasoInterno < 512) { // Bajada
    int b = 511 - pasoInterno;
    setBrillo(b);
    pasoInterno++;
    delayConPausa(20);
    return false;

  } else {
    setBrillo(0);
    return true;
  }
}

// ==========================================================
//                   FUNCIONES DE APOYO
// ==========================================================

// Encender todos
void encenderTodos() {
  for (int i = 0; i < 5; i++)
    digitalWrite(leds[i], HIGH);
}

void apagarTodos() {
  for (int i = 0; i < 5; i++)
    digitalWrite(leds[i], LOW);
}

void setBrillo(int v) {
  for (int i = 0; i < 5; i++)
    analogWrite(leds[i], v);
}

// Delay que se interrumpe con pausa
void delayConPausa(int ms) {
  for (int t = 0; t < ms; t += 10) {
    if (pausado) return;
    delay(10);
  }
}

// Pausa entre secuencias (2 segundos)
void esperarPausaSecuencia() {
  delayConPausa(pausaEntreSecuencias);
}

// Esperar que suelte
void esperarSoltar(int boton) {
  while (digitalRead(boton) == LOW);
  delay(150);
}
