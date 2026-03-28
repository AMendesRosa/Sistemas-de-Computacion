# Estudio sobre el Tiempo de Ejecución en la ESP32 con variaciones en la Frecuencia del CPU



## 1- Introducción al Rendimiento
De acuerdo a la bibliografia presentada en esta asignatura, se define al rendimiento de un sistema como la capacidad que tiene dicho sistema para realizar un trabajo en un determinado tiempo. Es inversamente proporcional al tiempo, es decir, cuanto mayor sea el tiempo que necesite, menor será el rendimiento. Se tiene entonces que en base a esta definición, es de esperarse que al aumentar la frecuencia de trabajo de nuestro `CPU`, se pueden entonces ejecutar una mayor cantidad de instrucciones por unidad de tiempo, es decir y en términos más simplistas: los programas se ejecutarán más rápidos.

En esta sección del Trabajo Práctico 1, se busco estudiar de forma empírica esta relación, utilizando como base la placa `ESP32` la cual tiene la ventaja de que esta permite ajustar su frecuencia de trabajo de su CPU. Para ello, se ejecutó un código el cual compara la velocidad de ejecución de un código a medida que se modifica la frecuencia de trabajo del `CPU`.



## 2- Análisis Empírico
### 2.1 - Realización de la Prueba
Dado que no se tuvo poseción de una ESP32 en forma física, se optó por usar un simulador online llamado [Wokwi](https://wokwi.com/projects/new/esp32-s3), el cual permite introducir un código en `C/C++` y lo compiló en una instancia virtual de este microcontrolador, la cual a fines prácticos de nuestro análisis de rendimiento será suficiente.

Para realizar tal medición y análisis, se diseñó un código en `C` el cual realizó una serie de sumas tanto para números enteros como flotantes y midió el tiempo de ejecución mediante el comando `millis()`, para tales tareas a medida que se varió la frecuencia de la `CPU` de la placa. Para esto, se implementó mediante el código que se encuentra en este directorio y se llama `ESP32 Test.c`.

En este código se llama en la función `ejecutarPrueba()` la cual toma como parámetro la frecuencia de la `CPU` a la cual se debe realizar el test. Internamente esta función llama a otras dos funciones llamadas `testEnteros()` y `testFloats()` las cuales ejecutan un ciclo `for()` con sumas de `500000` iteraciones.



### 2.2- Análisis de los Resultados
Una vez explicado el funcionamiento de este código, se procedió a la ejecución del mismo donde se obtuvieron los siguientes valores: 

| Frecuencia (MHz) | Tiempo enteros (ms) | Tiempo float (ms) |
| ---------------- | ------------------- | ----------------- |
| 2                | 2828                | 31891             |
| 4                | 1435                | 16034             |
| 8                | 1076                | 11996             |

![Resultados del test](https://github.com/ErnestMonja/Sistemas-de-Computacion/blob/main/TP1%20-%20Rendimiento/ESP32%20Test/ESP32%20-%20Test%20Results.png)
---

> Nótese que las frecuencias de trabajo del CPU utilizadas, son comparativamente bajas a las que suele trabajar la CPU normalmente, esto se debió a que [Wokwi](https://wokwi.com/projects/new/esp32-s3) internamente no permite modificar o elevar tales frecuencias por encima de cierto límite. Si las frecuencias se aumentan (por ejemplo en 1 orden de magnitud), tales cambios no se reflejan en la simulación y los tiempos son iguales.

Como era de esperarse, vemos que al aumentar la frecuencia de la `CPU`, se tiene que los tiempos de ejecución tanto para los bucles en enteros como para los flotantes, disminuyen en una relación aproximadamente lineal. Tal linealidad no es exacta, como se puede ver del salto de `4` a `8 [MHz]` debido al uso de un simulador online el cual tiene sus claras desventajas en cuanto a tiempos de latencia internas y/o la falta de precisión en el comando `millis()` de un simulador.

Sin embargo estos resultados son válidos a los fines prácticos de este Benchmark, ya que se observa las relaciones mencionadas en la introducción. En base a estos resultados, podemos deducir los valores de Speedup obtenidos y consecuentemente realizar un análisis sobre los mismos. Para medir el Speedup, necesitamos tomar algunas relaciones de tiempos de respuestas:

$$
f_{2->4 MHz}^{int} = \frac{2828}{1435} \approx 1.97
$$






## 3- Conclusión
Se concluye entonces 
