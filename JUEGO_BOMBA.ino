// ===============================================
// CONFIGURACIÓN DEL JUEGO DE LA BOMBA
// ===============================================

// LEDs en orden
int leds[] = {7, 8, 9, 10, 11, 12};
int totalLeds = 6;

// Botones
int botonSeleccion = 2;   // Recorre LEDs
int botonConfirmar = 3;   // Confirma elección
int botonReset = 4;       // Reinicio manual

// Variables del juego
int posicionActual = 0;   // LED seleccionado
int posicionBomba = 0;    // LED donde está la bomba
int intentos = 3;         // 3 oportunidades

// Evitar rebotes
void esperarSoltar(int pin) {
  while (digitalRead(pin) == LOW);
  delay(150);
}

void setup() {
  for (int i = 0; i < totalLeds; i++) {
    pinMode(leds[i], OUTPUT);
  }

  pinMode(botonSeleccion, INPUT_PULLUP);
  pinMode(botonConfirmar, INPUT_PULLUP);
  pinMode(botonReset, INPUT_PULLUP);

  randomSeed(analogRead(0));

  iniciarJuego();
}

void loop() {

  // ------------- REINICIO MANUAL -------------
  if (digitalRead(botonReset) == LOW) {
    esperarSoltar(botonReset);
    iniciarJuego();
    return;
  }

  // ------------- SELECCIONAR LED -------------
  if (digitalRead(botonSeleccion) == LOW) {
    esperarSoltar(botonSeleccion);
    moverSeleccion();
  }

  // ------------- CONFIRMAR ELECCIÓN -------------
  if (digitalRead(botonConfirmar) == LOW) {
    esperarSoltar(botonConfirmar);
    procesarIntento();
  }
}

// ===============================================
//               FUNCIONES PRINCIPALES
// ===============================================

void iniciarJuego() {
  apagarTodos();
  intentos = 3;
  posicionActual = 0;
  posicionBomba = random(0, totalLeds);  // Bomba aleatoria

  // Mostrar LED seleccionado
  mostrarSeleccion();
}

void moverSeleccion() {
  apagarTodos();

  posicionActual++;
  if (posicionActual >= totalLeds) {
    posicionActual = 0; // volver a LED1
  }

  mostrarSeleccion();
}

void procesarIntento() {
  if (posicionActual == posicionBomba) {
    // GANÓ
    winAnimacion();
    fadeTodos();
    iniciarJuego();
    return;
  }

  // Falló
  intentos--;

  //  Parpadea 3 veces donde estaba la bomba
  mostrarBombaError();

  if (intentos > 0) {
    // Parpadeo de todos los LEDs → indica que la bomba se mueve
    encenderTodos();
    delay(250);
    apagarTodos();
    delay(250);

    // Genera nueva posición de la bomba diferente a la selección actual
    do {
      posicionBomba = random(0, totalLeds);
    } while (posicionBomba == posicionActual);

    // Continúa jugando
    mostrarSeleccion();
  } else {
    // Intentos agotados → fade y reinicio
    fadeTodos();
    iniciarJuego();
  }
}

// ===============================================
//              FUNCIONES DE ANIMACIÓN
// ===============================================

void mostrarSeleccion() {
  apagarTodos();
  digitalWrite(leds[posicionActual], HIGH);
}

void mostrarBombaError() {
  // Parpadea 3 veces el LED donde estaba la bomba
  for (int i = 0; i < 3; i++) {
    digitalWrite(leds[posicionBomba], HIGH);
    delay(300);
    digitalWrite(leds[posicionBomba], LOW);
    delay(300);
  }
}

void winAnimacion() {
  // Parpadean TODOS 3 veces
  for (int i = 0; i < 3; i++) {
    encenderTodos();
    delay(250);
    apagarTodos();
    delay(250);
  }
}

void fadeTodos() {
  // Fade de brillo → apagado
  for (int b = 0; b <= 255; b++) {
    for (int i = 0; i < totalLeds; i++) {
      analogWrite(leds[i], b);
    }
    delay(8);
  }

  for (int b = 255; b >= 0; b--) {
    for (int i = 0; i < totalLeds; i++) {
      analogWrite(leds[i], b);
    }
    delay(8);
  }

  apagarTodos();
}

// ===============================================
//                 FUNCIONES ÚTILES
// ===============================================

void encenderTodos() {
  for (int i = 0; i < totalLeds; i++) {
    digitalWrite(leds[i], HIGH);
  }
}

void apagarTodos() {
  for (int i = 0; i < totalLeds; i++) {
    digitalWrite(leds[i], LOW);
  }
}
