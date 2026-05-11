## Práctico #3a UEFI 


### Introducción 
El presente trabajo tiene como objetivo el desarrollo y ejecución de un aplicación UEFI (Unified Extensible Firmware Interface) de 64
bits para realizar análisis de seguridad básico en el firmware en una computadora real, en nuestro caso usamos una Dell Inspiron con
procesador Intel Core Ultra 9. En esta experiencia se realiza emulación mediante QEMU para las tareas de depuración controlada, en donde se busca detectar la presencia de un breakpoint estático (`0xCC`) en una región de memoria simulada, replicando 
patrones de análisis utilizados en Ghidra. Esto nos permite entender cómo interacúa el software de bajo nivel con el hardware antes de la carga del Sistema Opertavivo. 

### Marco Teórico 
Para empezar este trabajo es necesario saber lo siguiente: 

- UEFI: es la infraestructura de firmware estándar de la industria,es puramente una especificación de interfaz. Define las APIs, estructuras de datos y el entorno pre-sistema operativos mediante el cual interactúan el firmware, los componenetes de hardware y los cargadores del sistema operativo 4,6. 
- PI: es la arquitectura interna del firmware. Define como se construye la plataforma desde el momento del restablecimiento (reset) del hardware, estableciendo fases de control bien definidas hasta que se crea el entorno UEFI para el OS 5.

La UEFI reemplaza a la BIOS tradicional operando en modods modernos de 64 bits. A diferencia de las limitaciones históricas de 16 bits, UEFI ofrece una arquitectura modular dividida en fases: 

#### Fases de Arranque (PI - Plataform Initialization)
El flujo de incialización del hardware está dividido en fases específicas para gestionar progresivamente los recusas de la máquina 

1. SEC (Security): Es la fase pre-memoria. Establece un contexto mínimo de ejecución, como configurar la memoria caché del procesador para ser usada como RAM temproral antes de que la memoria principal esté disponible.
2. PEI(Pre-EFI Initialization): su objetivo es inicializar la cantidad mínima de hardware crítico y además, determina el "modo de arranque" y pasa la información descubierta a la fase que le sigue a través de estructuras independientes de posición llamadas Hand-Off Blocks
3. DXE(Driver Execution Environment) es el núcleo de la inicialización de la plataforma. El "DXE Dispatcher" carga y ejecuta drivers en un orden determinado. En esta fase se instalan la mayoría de las abstracciones de hardware, buses y los servicios centrales de UEFI
4. BDS(Boot Device Selection): básandose en variables almacenadas en NVRAM, el firmware decide la política de arranqe.
5. RT(Runtime): una vez que se ha establecido su infraestructura se invoca la función ExitBootServices(). Esto finaliza el entrono de pre-arranque, liberando la mayoría de la memoria, pero conservando los Runtime Services que proveen funciones básicas al OS

#### Estructuras de Datos y Objetos Centrales 
El código UEFI hace uso de construcciones orientadas a objetos: 

- UEFI System Table: estructura de datos más crítica y actuá como el "entry point" principal. Contiene punteros a dos grandes tablas de servicios: los Boot Services (manejan memoria, tareas y eventos) y los Runtime Services (disponibles antes y después de la carga de OS)
- Protocolos y Basa de Daros de Handles: UEFI abstrae el hardware y los servicios mediante Protocolos. Un protocolo es un bloque de punteros a funciones y estructuras de datos, identificado invariablemente por un identificasor único global (GUID). Estos se agrupan dentro de Handles. Los Handles representan entidades físicas o lógicas y son usados por los programas para descubrir si un protocolo específico está disponible en el sistema e interactuar con el hardware asociado
- Imágenes UEFI: es todo el código ejecutble de UEFI. Se empaqueta usando el formato estándar PE/COFF. Las imágenes contienen información de rubicación, lo que permite que la función LoadImage() asigne memoria dinámica y adapte el ejecutable en cualquier espacio de direcciones físicas antes de invocarlo.  

#### El Modelo de Drives de UEFI 
Este modelo moderno oblig a separar la carga del driver del momento en el cual este asume el control del Hardware. 
Meidante el protocolo Driver Binding Protocol, un driver se cargo pero solo "conecta" con su dispositivo (inicializándolo) si el sistema se lo requiere explícitamente durante la fase BDS. Esta carga perezosa (lazy activation) permite que el sistema solo encienda los dispositivos estrictamente necesarios para encontrar el boot target, logrando optimizar drásticamente la latencia del arranque (fast boot) y empujando el descubrimiento del resto del hardware a nivel de sistema operativo. 

#### Superficie de Ataque y Seguridad 
UEFI proporciona primitivas criptográficas mediante funcionalidades como el Secure Boot, que verifica firmas x509 embebidas en los archivos PE/COFF antes de permitir la ejecución de drivers externos o bootloaders, estableciendo una cadena de confianza

### Entorno de Desarrollo 
Para garantizar la compatibilidad con el etándar UEFI de 64 bits, se configuró un entorno de desarrollo robusto sobre el sistema operativo `Ubuntu 24.04 LTS` y la cadena de herramientas de `GNU-EFI`.

Las pruebas físicas se realizaron sobre una estación de trabajo portátil con capacidades de procesamiento de última generación, permitiendo validar el comportamiento del binario en arquitecturas x86_64 

- Modelo: Dell Inspiron 14 Plus 7440
- Procesador: Intel COre Ultra 9 185H
- Memoria: 32 GB RAM
- Almacenamiento: 1TB NVMe SSD

Se utilizó la cadena de herramientas de GNU para la generación de binarios PE32+ (Portable Executable), formato requerido por el firmware UEFI

- Compilador: `gcc`
- Librerías de Desarrollo: Se instaló el paquete `gnu-efi`, el cual proporciona `efi.h` y `efilib.h` para el manejo de protocolos de consola y
  los objetos de inicio necesarios para la interfaz con las tablas del sistema
- Scripts de Elace: se utilizó el archivo `elf_x86_64_efi.lds` para definir la disposición de las secciones de memoria de la aplicación dentro del firmware

#### Herramientas de Análisis y Emulación 
Antes del despliegue en hardware real, usamos herramientas para verificar la integridad del código: 

- Emulación: QEMU con soporte OVMF para simular un entorno UEFI puro sin riesgo de bloqueo del hardware del host
- Ingeniería inversa: Ghidra 12.0, utilizado para la descompilación y análisis estǽtitco del binario generado
- Inspección de Binarios: utilidades `file` y `readelf` para corroborar que el formato de salida fuera efectivamente una aplicación EFI y no un binario ELF de Linux  

<img width="1024" height="768" alt="image" src="https://github.com/user-attachments/assets/27004ffe-c428-4207-839c-34f065c6a362" />


### Implementación del Código 

El código utilizado para el archivo `aplicacion.c` es el siguiente: 

```
#include <efi.h>
#include <efilib.h>

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    InitializeLib(ImageHandle, SystemTable);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, 
        L"Iniciando analisis de seguridad...\r\n");

    // Simulación de breakpoint estático (INT3)
    unsigned char code[] = { 0xCC };

    if (code[0] == 0xCC) {
        SystemTable->ConOut->OutputString(SystemTable->ConOut, 
            L"Breakpoint estatico alcanzado.\r\n");
    }

    return EFI_SUCCESS;
}
```

Para asegurar que el binario pueda ser analizado mediante Ghidra, se utilizó una variable que define el breakpoint como un arreglo de datos 
`unsigned char code[]`. Esto permite verificar la lógica de detección sin forzar una interrupción de hardware que el firmware podría no manejar 



<img width="1427" height="790" alt="Pasted image (2)" src="https://github.com/user-attachments/assets/cd610bab-ab61-4b3a-830d-196fc9cf238b" />
Figura 1

En la imagen se ve la edición del archivo fuente `aplicacion.c` utilizando el editor Nano. Se observa la implementación final que incluye una pausa 
(`WaitForKey`) para permitir la lectura de los resultados antes del cierre de la aplicación. 

### Construcción y Análisis del Binario 
  En esta etapa se realizó la transformación del código fuente en un ejecutable compatible con el firmware y se auditó su estructura mediante ingeniería inversa 

#### Proceso de Compilación 
Paso 1: Generación del código objeto 

  `gcc -I/usr/include/efi -I/usr/include/efi/x86_64 -I/usr/include/efi/protocol \
    -fpic -ffreestanding -fno-stack-protector -fno-strict-aliasing \
    -fshort-wchar -mno-red-zone -maccumulate-outgoing-args \
    -Wall -c -o aplicacion.o aplicacion.c `

Paso 2: Linkeo (genera .so intermedio )
  `ld -shared -Bsymbolic -L/usr/lib -L/usr/lib/efi -T /usr/lib/elf_x86_64_efi.lds
/usr/lib/crt0-efi-x86_64.o aplicacion.o -o aplicacion.so -lefi -lgnuefi` 

Paso 3:  Convertir a ejecutable EFI (PE/COFF)
`objcopy -j .text -j .sdata -j .data -j .dynamic -j .dynsym -j .rel -j .rela -j .rel.* -j .rela.* -j .reloc
--target=efi-app-x86_64 aplicacion.so aplicacion.efi` 

<img width="512" height="220" alt="image" src="https://github.com/user-attachments/assets/cbb812a4-ffa2-4d46-a4c3-f8b546a1bcd1" />
Figura 2


#### Verificacion de Formato 
Antes del análisis estatico, se valido la integridad del archivo mediante el comando `file`, confirmando que se trata de un PE32+ executable (EFI application) x86_64. Tambien pudimos verificar la incompatibilidad con herramientas ELF estandar como `readelf`, confirmando la correcta conversion del formtato, como se observa en la siguiente imagen 

<img width="512" height="51" alt="image" src="https://github.com/user-attachments/assets/27ed794b-31fa-43ec-8ce4-3fb8ab19f809" />
Figura 3: Validación del formato de salida, confirmando que se trata de un ejecutable PE32 para EFI 

Comando `readelf` 
<img width="512" height="86" alt="image" src="https://github.com/user-attachments/assets/e6af0247-92d3-4cdb-b91e-5ee8ff7fc513" />
Figura 3: El error evidencia el cambio exitoso de Magic Bytes 


#### Análisis de Ingenieria Inversa 
Se realizó una auditoria del binario utilizando Ghidra para verificar que el opcode `0xCC` fuera claramente identificable 

- Importación y reconocimiento: al cargar el archivo, Ghidra identificó automáticamente el formato PE. Esto confirma que el firmware Dell podrá interpretar el punto de entrada de la aplicación.
 <img width="2880" height="1723" alt="image" src="https://github.com/user-attachments/assets/c5f85fc9-284a-4afd-9a79-af0f3a336932" />
Figura 4

- Análisis del Punto de entrada: utilizando el CodeBrowser y el Decompiler, se localizó la función `efi_main`. Se constató como la instrucción de impresión se traduce a llamadas de los protocolos de consola de UEFI(`ConOut`)


### Configuración del Firmware y Seguridad 
Para permitir la ejecución de nuestro código personalizado, fue necesario intervenir en la configuración de seguridad del firmware. Al tratarse de una aplicación no firmada por una Autoridad de Certificación reconocida, el protocolo de Secure Boot bloquearía el incio por defecto

Para permitir la ejecución del binario no firmado, tuvimos que acceder a la configuración del firmware presionando F2 durante el arranque. 
Dentro del menú Secure Boot, se deshabilitó la opción correspondiente. Esta modificación es necesaria porque nuestra aplicación no está firmada por una autoridad de Certificación reconocida. De dejarse activo, el firmware rechazaría la carga del binario con un error de violación de política de seguridad. Adicionalmente, se verificó que el modo de arranque estuviera configurado en UEFI y no en modo Legacy/CSM 


### Ejecución en Hardware Real y Resultados 
Una vez configurada la BIOS y preparado el pendrive con el sistemade archivos FAT32, se procedio al arranque mediante el mení de dispositivos 

#### Interacción con la UEFI Shell 
Al iniciar, el firmware cedió el control a la UEFI Interactive Shell v2.2. Como se observa en la captura, el sistema realizó el mapeo de dispositivos (Mapping table), identificando el pendrive como el sistema de archivos `FS0: `

#### Verificación del Análisis de Seguridad 
Al ejecutar la aplicación, el sistema imprimió con éxito los mensajes programados. A diferencia de las pruebas en emuladores, aqui se validó la ejecución directa sobre el procesador 

 Salida detectada:

- "Iniciando analisis de seguridad"
- "Breakpoint estatico alcanzado "

Manejo de flujo: Implementamos la espera de teclado final para evitar que el firmware regresara al menú de booteo instantáneamente, permitiendo sacar una captura 

<img width="1024" height="768" alt="image" src="https://github.com/user-attachments/assets/0f7af9f0-e90d-4736-9806-261d8bc81db3" />
Ejecución en el hardware real 

### 4a: Depuración con GDB 
Para poder validar la detección del breakpoint, establecimos un puente de comunicación entre el emulador y el desensamblador. Para esto, tuvimos que realizar los siguientes pasos: 
#### 1. Iniciar QEMU con el servidor GDB habilitado:
```
  bashqemu-system-x86_64 -m 512 \
  -bios /usr/share/ovmf/OVMF.fd \
  -net none \
  -drive file=fat:rw:$HOME/uefi_security_lab,format=raw \
  -s \        # abre el servidor GDB en localhost:1234
  -S           # pausa la CPU al inicio (espera que GDB conecte antes de ejecutar)

  -s es shorthand de -gdb tcp::1234
  -S hace que QEMU no arranque hasta que GDB le diga continue
```
<img width="1600" height="882" alt="image" src="https://github.com/user-attachments/assets/f05d61e4-42ab-4332-b887-b4a768fab5cf" />

#### 2. Conectar GDB: para este paso es necesario hacerlo en otra terminal
```
  gdb
  Dentro de GDB:
  gdb# Conectar al servidor de QEMU
  (gdb) target remote localhost:1234

```
Después de este paso, como el firmware arranca en modo 16-bit real, hay que decirle a GDB la arquitectura i8086. 
`set architecture i8086`

<img width="1600" height="340" alt="image" src="https://github.com/user-attachments/assets/ad618938-346d-4eb4-8183-d760951f7008" />

Como se puede observar en la imágen, no reconocia la arquitectura especificada en la consigna. Debido a esto, usamos la que nos saltaba en la terminal que es la i386:x86-64. 
<img width="1600" height="153" alt="image" src="https://github.com/user-attachments/assets/83db9133-0db3-44c5-adb9-dbdfe6ebb776" />

Dado que el binario generado es un ejecutable de 64 bits, forzar una arquitectura inferior habría provocado errores de desalieación en los opcodes y una lectura de los registros de la CPU.

#### 3. Encontrar la dirección base del .efi
UEFI carga las imágenes de direcciones dinámicas por lo que necesitamos saber dónde en memoria se cargó `aplicacion.efi`
   
<img width="2886" height="276" alt="Screenshot from 2026-05-10 12-12-01" src="https://github.com/user-attachments/assets/9956af9b-f091-4c20-8b32-d94643ce2ab7" />

#### 4. Cambio de la varible "volatile int waiting "  

Para cambiar el `volatile int waiting = 1 ` a `volatile int waiting = 0 `, conectamos el GDB en el `while (waiting) {}`
<img width="2886" height="276" alt="Screenshot from 2026-05-10 12-12-01" src="https://github.com/user-attachments/assets/723d5540-eb09-4bb4-9e6e-42eb49bc3128" />

#### 5. Carga de los símbolos en GDB 
<img width="2382" height="837" alt="image" src="https://github.com/user-attachments/assets/1fae8919-1ca9-4334-a549-9a31b13394f9" />

Para este paso ejecutamos el comando `info registers rip` como se observa en la imagen, el GDB nos devuelve que el rip esta en `0x1e044058` (dentro del bucle while)

<img width="747" height="81" alt="image" src="https://github.com/user-attachments/assets/60927405-fc64-46c6-ba11-c8c0f3b0f03b" />

Luego, ejecutamos el comando `objdump -h aplicacion.so | grep .text` , que nos dice el offset de `.text` en el `.so` es `0x3000` 
<img width="922" height="60" alt="image" src="https://github.com/user-attachments/assets/475d7d50-4472-42b0-8ac4-1e3e62b5f37b" />

Con estos dos datos, y sabiendo que el loop while está al inicio de `efi_main` que es la primera función en .text , entonces el rip está muy cerca del inicio de `.text` en memoria tenemos que: 

`dirección base de .text en memoria = RIP - (offset dentro de .text)`
Como el loop está al inicio de `efi_main ` y este está cerca del inicio de `.text`, asumimos que el offset interno es pequeño(~0x58) 
Entonces nos queda: 
`base de imagen = 0x1e044058 - 0x3000 - 0x58  = 0x1e041000` 
Redondeamos a 0x1e041000 porque las imágenes UEFI se cargan en páginas alineadas a 0x1000 
Por esto usamos  `add-symbol-file aplicacion.so 0x1e041000` 
<img width="2886" height="761" alt="Screenshot from 2026-05-10 12-12-40" src="https://github.com/user-attachments/assets/eed0999e-c36b-4310-bd9a-2f0761e7e6b3" />
<img width="891" height="378" alt="image" src="https://github.com/user-attachments/assets/86553105-9b97-48d6-82f7-a67f7b30d88e" />

#### 6. Como último paso: comandos de registros 
En este paso se usaron comando para ver registros, el 0xCC en memoria, el breakpoint 0xCC, ver estados de los registros 
<img width="2886" height="286" alt="Screenshot from 2026-05-10 12-13-14" src="https://github.com/user-attachments/assets/6553c5bc-ef4a-4c17-a28d-c7d940e46382" />

<img width="2886" height="761" alt="Screenshot from 2026-05-10 12-12-40" src="https://github.com/user-attachments/assets/067fb993-0bf3-41d4-a66e-50b827599c7c" />

### 4b: Análisis híbrido (conexión Ghidra a GDB )
Para hacer este análisis primero hay que establecer la conexión de Ghidra con GDB

Primero iniciamos QEMU con `s -S` para que quede pausado 
<img width="1136" height="631" alt="image" src="https://github.com/user-attachments/assets/15aeaa55-91c2-4ea4-b93d-1f0d643593a8" />

Hacemos la conexión con gdb remote: 
<img width="858" height="931" alt="Screenshot from 2026-05-10 17-25-37" src="https://github.com/user-attachments/assets/c4839bac-6d5b-4835-aa88-5c5d82b07345" />

Una vez conectado, por la terminal de Ghidra configuramos la arquitectura y usamos el continue para que la UEFI Shell no este pausada 
<img width="907" height="411" alt="image" src="https://github.com/user-attachments/assets/7e5fce88-58dd-4021-be78-215ffc980262" />

<img width="2560" height="987" alt="Screenshot from 2026-05-10 18-08-01" src="https://github.com/user-attachments/assets/604e1187-fbbd-4e29-aeec-a07498790714" />

<img width="1292" height="610" alt="Screenshot from 2026-05-10 18-15-05" src="https://github.com/user-attachments/assets/b8345696-7cb9-4030-9e04-df986b22d316" />

<img width="2545" height="1265" alt="Screenshot from 2026-05-10 18-18-41" src="https://github.com/user-attachments/assets/5f6362ae-d1e6-4109-83d2-ef81968a15be" />



### Conclusiones 
Este laboratorio permitió integrar concepetos de bajo nivel, seguridad de firmware y desarrollo de sistemas embebidos 

1. Portabilidad UEFI: Se demostró que el formato PE32+ es el estándar universal para la comunicaión con el firmware, permitiendo que un binario compilado en Ubuntu corra en una arquitectura de hardware mederna sin necesidad de un sistema operativo intermedio
2. La desactivación del Secure Boot es un paso mandatorio y esto hace que evidencie como el hardware protege la cadena de confianza
3. Eficiencia del Análisis Híbrido: mediante el uso de Ghidra y QEMU, pudimos validar que las marcarde depuración o vulnerabilidadea, como el breakpoint estático (0xCC), son detectables tanto en el análisis estático como dinámico. La sincronización en tiempo real del registro RAX/AL con el desensamblador confirmó que el análisis híbrido es la técnica más potente para la auditoria de firmware y la prevención de malware de arranque
4. Adaptabilidad Técnica y Diagnóstico: EL uso de mecanismos de sincronización manual, como el bucle `while (waiting)`, y el ajuste de la arquitectura a 64 bits, remarcó la importancia de la coherencia entre el firmware y las herramientas de depuración. La capacidad de modificar el flujo de ejecución demostró un dminio práctico sobre el estado del procesador en etapas tempranas del arranque. 



## Preguntas de Razonamiento

1. Al ejecutar el comando map y dh, vemos
protocolos e identificadores en lugar de puertos de hardware fijos. ¿Cuál es la
ventaja de seguridad y compatibilidad de este modelo frente al antiguo BIOS?

Como se observa en la imagen, al iniciar la Shell, el comando `map` se ejecuta automáticamente mostrando la tabla de mapeo. En lugar de direcciones físicas rígidas, observamos rutas lógicas. Esto garantiza que, si conectamos el pendrive en un puerto USB distinto, el sistema UEFI pueda localizar el protocolo de archivos (FS0:) dinámicamente, mejorando la compatibilidad frente al modelo de direccionamiento fijo de BIOS 


2. Observando las variables Boot#### y
BootOrder, ¿cómo determina el Boot Manager la secuencia de arranque?

En la imagen, se puede evidenciar que el sistema gestiona el arranque mediante variables globales. La variable `BootOrder` defina la prioridad, mientras que las variables ``Boot####` especifican la ubicación fisica y lógica de cada cargador de arranque. Esta estructura permite que, al desconectar el pendrive utilizado en este laboratorio, el Boot Manager salte automaticamente a la siguiente opción válida sin intervención del usuario 

3.  En el mapa de memoria (memmap), existen
regiones marcadas como RuntimeServicesCode. ¿Por qué estas áreas son un
objetivo principal para los desarrolladores de malware (Bootkits)?

Como se analizó mediante la inspección de variables que se muestran en la imagen, las regiones de tipo `RuntimeServices` son fundamentales para el funcionamiento continuo del sistema. Sin embargo, desde el punto de vista de la seguridad,  respresentan la superficie de ataque más crítica para los Bootkits. Debido a que este código permanece residente en memoria tras el inicio del SO y opera con altos privilegios, un atacante podría subvertir la seguridad del sistema de manera persistente e invisible para las herramieentas de protección convencionales.

4. ¿Por qué utilizamos
SystemTable->ConOut->OutputString en lugar de la función printf de C?

En este laboratorio se utilizó `OutputString`a través de la `SystemTable` en lugar del tradicional `pintf`. Esto se debe a que las aplicaciones UEFI se ejecutan antes de cualquier sistema operativo, careciendo de acceso a la biblioteca estándar de C. `OutputString` utiliza los protocolos nativos del firmware para interacturar con el búfer de videp, garantizando que le mensaje sea visible en el hardware fisico 

5.  En el pseudocódigo de Ghidra, la condición
0xCC suele aparecer como -52. ¿A qué se debe este fenómeno y por qué
importa en ciberseguridad?

El fenómeno ocurre porque Ghidra interpreta el byte `0xCC` como un entero con signo de 8 bits (signed char). En representación en complemento a dos, este significa `-52` en decimal. Esto no es un error del descompilador sino una decisión de tipado: si la variable `code[]` se declara como char en lugar de unsigned char, el compilador trata el valor como negativo. 
En ciberseguridad esto es importante por dos razones. Primero, las herramientas de detección de malware y las reglas YARA que buscan el patrón `0xCC` en positivo o en hexadecimal podrían no correlacionar correctamente si el analista trabaja sobre pseudocódigo de Ghidra son considerar la representación con signo, generando falsos negativos. Segundo, un desarrollador de malware podría aprovechar esta ambiguedad construyendo breakpoints de forma que sean dificiles de identificar mediante búsqueda literal de bytes en herramientas de análisis estático que operen sobre representaciones de alto nivel en lugar del binario crudo 

