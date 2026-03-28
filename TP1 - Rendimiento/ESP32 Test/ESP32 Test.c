#include <Arduino.h>

// ----------------------
// Funciones de test
// ----------------------

void testEnteros() {
  volatile long suma = 0;
  volatile long i;

  for (i = 0; i < 500000; i++) {  // iteraciones reducidas
    suma += i;
  }
}

void testFloats() {
  volatile float suma = 0;
  volatile long i;

  for (i = 0; i < 500000; i++) {  // iteraciones reducidas
    suma += (float)i * 0.1;
  }
}

// ----------------------
// Función de prueba
// ----------------------

void ejecutarPrueba(int freq) {
  setCpuFrequencyMhz(freq);
  delay(1000); // estabilización

  Serial.println("--------------------------------");

  Serial.print("Frecuencia seteada: ");
  Serial.print(freq);
  Serial.println(" MHz");

  Serial.print("Frecuencia real CPU: ");
  Serial.print(getCpuFrequencyMhz());
  Serial.println(" MHz");

  volatile unsigned long t0, t1;

  // -------- ENTEROS --------
  t0 = millis();
  testEnteros();
  t1 = millis();

  Serial.print("Tiempo enteros: ");
  Serial.print(t1 - t0);
  Serial.println(" ms");

  // -------- FLOATS --------
  t0 = millis();
  testFloats();
  t1 = millis();

  Serial.print("Tiempo floats: ");
  Serial.print(t1 - t0);
  Serial.println(" ms");
}

// ----------------------
// Setup principal
// ----------------------

void setup() {
  Serial.begin(115200);
  delay(2000);

  // Frecuencias bajas (según recomendación Wokwi)
  ejecutarPrueba(2);
  ejecutarPrueba(4);
  ejecutarPrueba(8);
}

void loop() {
  // No se usa
}