# TAREA 4 SISTEMAS OPERATIVOS

Juan Cucurella / 202173608-5 / par. 200
Vicente Illanes / 202173651-4 / par. 200

---

## Archivos

- University.py: implementacion de threads y sincronización a través de Locks para simular el comportamiento de la universidad según lo pedido en enunciados

## Instrucciones

- Descargar/instalar la libreria datetime:

    pip install datetime

- Ejecutar el código en el directorio raíz de la presente entrega a través del comando:

    make

- En caso de requerir otra ejecución, ejecutar el mismo comando anterior, limpiará el directorio raíz y reiniciará los archivos creados en la ejecución

en caso de fallas del archivo makefile:

- Ejecutar el código en la carpeta del proyecto usando el comando:
    python3 University.py

- En caso de requerir una segunda ejecucion, borrar los archivos de texto generados usando:
    
    rm *.txt

    Repetir el proceso para la ejecución normal.

## NOTAS:

- Existen un par de anomalías en los tiempos durante las consultas, por cierta razón desconocida algunas consultas toman menos tiempo a pesar de la orden de sleep, como hipótesis, es posible que se deba a la itineración, errores en el procesamiento de output con multithreads, interrupciones a la thread en proceso, etc.

- Es posible que el tiempo de ejecución sea alto dada la cantidad de threads utilizados y los cambios de contexto necesarios para cada interrupcion de las threads.
