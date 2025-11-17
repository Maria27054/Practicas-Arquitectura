# Practicas-Arquitectura
Contenido relacionado con las practicas realizadas en clase 

PRIMERA ACTIVIDAD "sos" -> Cargue a la computadora el código necesario para que la computadora pueda ejecutar con un dispositivo de salida la señal para escuchar o ver en código morse SOS.


SEGUNDA ACTIVIDAD "secuencias" -> Cargue a la placa de prototipado, el código necesario para que pueda computar automaticamente las siguientes secuencias.

-Encender y apagar el ed simulando el codigo morse para SOS

-Encender y apagar el LED en intervalos de medio segundo, 7 veces

-Encender y apagar el LED emitiendo un pulso gradual donde pasa de estar apagado, a totalmente encendido y luego apagado gradualmente


TERCERA ACTIVIDAD "secuencias selectivas" -> Modifique el codigo de la computadora para poder seleccionar mediante un dispositivo de entrada, la secuencia que desencadena esa señal.

-Encender y apagar el ed simulando el codigo morse para SOS

-Encender y apagar el LED en intervalos de medio segundo, 7 veces

-Encender y apagar el LED emitiendo un pulso gradual donde pasa de estar apagado, a totalmente encendido y luego apagado gradualmente


CUARTA ACTIVIDAD "IRQ Enmascarado" -> Modifique el código de la computadora para poder interrumpir la secuencia que está ejecutando en el momento en que se emita la solicitud de interrupción mediante un dispositivo de entrada.

-Encender y apagar el ed simulando el codigo morse para SOS

-Encender y apagar el LED en intervalos de medio segundo, 7 veces

-Encender y apagar el LED emitiendo un pulso gradual donde pasa de estar apagado, a totalmente encendido y luego apagado gradualmente


QUINTA ACTIVIDAD " IRQ + Memoria" -> Modifique el código de la computadora para poder interrumpir la secuencia que está ejecutando en el momento en que se emita la solicitud de interrupción mediante un dispositivo de entrada. Además debe almacenar en la memoria la información sobre la secuencia y el proceso que estaba ejecutándose antes de generar la interrupción.

-Encender y apagar el ed simulando el codigo morse para SOS

-Encender y apagar el LED en intervalos de medio segundo, 7 veces

-Encender y apagar el LED emitiendo un pulso gradual donde pasa de estar apagado, a totalmente encendido y luego apagado gradualmente

SEXTA ACTIVIDAD "Juego de la Bomba" -> El jugador debe seleccionar un LED y “desactivar la bomba” antes de agotar sus 3 intentos. La posición de la bomba es aleatoria y cambia después de cada intento fallido (excepto el último). La actividad incluye animaciones visuales que indican fallos, aciertos y reinicios.

Funcionalidad

LEDs: D7–D12

Botón 1 (D2): Recorrer la selección de LED de manera cíclica

Botón 2 (D3): Confirmar elección

Botón 3 (D4): Reinicio manual del juego

Lógica del juego

Se ilumina un solo LED indicando la selección actual.

Al confirmar:

Si coincide con la bomba → win animación + fade y reinicio.

Si falla:

Intentos 1 y 2: parpadea la bomba antigua 3 veces, luego todos los LEDs parpadean 1 vez indicando que la bomba se movió, y se genera nueva posición.

Intento 3: directamente fade lento y reinicio.

Reinicio manual disponible en cualquier momento con el botón 3.

Animaciones

Win: todos los LEDs parpadean 3 veces.

Fallo: LED de la bomba parpadea 3 veces.

Nueva partida: Fade, todos los LEDs aumentan y disminuyen brillo suavemente.
