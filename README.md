# midtermSimulator
## Antecedentes
EL conjunto de programas desarrollados en este proyecto pertenecen a la materia de sistemas operativos y fue implementado por el estudiante Axel Jeremy Godoy Saavedra de la 
carrera de Ingeniería en Computación de ESPOL, el proyecto se centra en mostrar en detalle como trabajan diferentes algoritmos de planificación de procesos como el First Come First Served, Short Job First y Round Robin. En los programas se trata de 
simular como trabajaría el planificador de un sistema operativo al trabajar con diferentes algoritmos en aplicaciones concretas. Además los programas muestran de forma interactiva como 
se procesa cada uno de los algoritmos implementados e incluso al final se muestran gráficas con tiempos promedios de métricas de interes al trabajar con planificadores como tiempo de espera, 
tiempo de respuesta y tiempo de respuesta normalizado para ver como es su comportamiento con respecto a diferentes tiempos de ráfaga.

## Uso
Para utilizar los diferentes programas el primer paso es compilarlos y crear los ejecutables para lo cual se tiene un Makefile el cual es el encargado de crear todos los componentes relevantes 
del proyecto, para referenciar a dicho archivo se debe establecer el comando make en una línea de comandos de Linux, a continuación se muestra comos se vería en la línea de comandos:
```bash
make
```
Luego de crear los ejecutables también es posible eliminarlos para luego volverlos a compilar con el siguiente comando:
```bash
make clean 
```
En las próximas secciones se detallará como trabaja y sus especificaciones con detalles específicos cada uno de los ejecutables creados, es importante recalcar que si al usar alguno de los programas se comete un error en los comandos cada uno posee mensajes para
guiar al usuario de cuales son los parámetros requeridos para el programa a usar, además todos los programas se encuentran escritos en el lenguaje C a excepción del último que se encuentra en Python
por último estos programas solo admiten archivos de texto con estensión .dat el resto simplemente no son aceptados y se envía un error:

## Schedsim
Este programa se puede denominar como una revisión detallada de la ejecución de cada uno de los algoritmos implementados puesto que imprime por consola a partir de un archivo en un formato específico, como se
ejecutarian los procesos en base a sus tiempos de llegada y ráfaga, además que permite encontrar el promedio de los tiempos de retorno, espera y retorno normalizado, a continuación se detalla los uso y parámetros esperados:
```bash
./schedsim archivo.dat (fcfs | sjf)
./schedsim archivo.dat rr (numeroEntero>0)
```
En el primer uso el tercer argumento debe ser ya sea fcfs o sjf, haciendo referencia a los algoritmos implementados, mientras que en el segundo uso el cuarto argumento debe ser un entero mayor que 0, si se ingresa algún parámetro de 
forma inválida se mostrará el error respectivo y como usar el programa correctamente, a continuación se muestran 2 usos correctos del ejecutable:
```bash
./schedsim archivo.dat sjf 
./schedsim archivo.dat rr 5
```

## Schedgen 
El segundo programa puede ser denominado como un generador de procesos puesto que en base a probabilidades genera un número concreto de procesos con sus respectivos tiempos de arribo y ráfaga, posteriormente estos son guardados en 
un archivo con extensión .dat, que si el usuario desea puede usar para generar los archuvos de entrada del resto de ejecutables, a continuación se muestra la especificación del programa:
```bash
./schedgen (númeroEntero>0) (NúmeroPuntoFlotante) (NúmeroPuntoFlotante) (archivo.dat)
```
En este caso se espera que el segundo argumento sea un número entero mayor que 0, el tercer y cuarto argumento deben ser un número de punto flotante entre 0 y 1 donde el separador obligatoriamente deber ser un . para evitar problemas
en la ejecución, mientras que el último parámetro debe ser el nombre un archivo vacío con extensión .dat y que no exista en el directorio de trabajo puesto que si ya existe simplemente no se creará el archivo y deberá ejecutarse
nuevamente el programa con un archivo con nombre diferente, a continuación se presenta un uso correcto del programa:
```bash
./schedgen 15 0.5 0.2 schedtimes.dat
```

## Schedstats
Al igual que el schedsim este ejecuta los algoritmos pero sin mostrar nada por pantalla, simplemente genera 3 archivos diferentes donde se tienen los promedios de tiempos de espera, retonro y retorno normalizado por cada algoritmo 
dependiendo de los tiempos de ráfaga de los procesos de entrada contenidos en el archivo que se usa como entrada al programa, a continuación se presenta la especificación de programa y se detalla sus parámetros correctamente:
```bash
./schedstats archivo.dat
```
El archivo pasado como argumento debe poseer extensión .dat, a continuación se presenta el uso correcto del programa:
```bash
./schedstats schedtimes.dat
```
## Schedgraph
Este último programa como se específico previamente fue implementado en Python usando las librerias Pandas y Matplotlib, entonces para ser ejecutado el usuario debe poseer ambas librerías previamente instalas, al final se adjuntan enlaces 
a sus detalles generales y como se deberían instalar, entonces para correr este programa se requerirá una versión de python 3.6 o superior con las librerías previamente mencionadas, este utiliza los archivos
del ejecutable anterior para crear gráficos interactivos que demuestran como se comportan cada uno de los algoritmos en base a tiempos de espera, retorno y retorno normalizado por sus tiempos de ráfaga, en los
gráficos cada uno de los algoritmos es representado como una línea y poseen identificadores, a continuación se detalla su uso:
```bash
python3 schedgraph.py
```
## Conclusión
El proyecto efectuado explora de forma general diferentes comportamientos de un planificador en un sistema operativo, se espera fue implementado para ser ejecutado en la distribución de Ubuntu pertenciente 
a Linux, se alcanzan los resultados esperados por los objetivos del proyecto y se lo implementó de forma eficiente y para que sea una herramienta útil para los usuarios intersados, por último en el proyecto se
incluye un archivo .docx que presenta diferentes salidas de cada uno de los programas puede ser revisado en caso de ser conveniente y como se vería este README en un repositorio real en Github.


## Librerias 
https://pypi.org/project/pandas/
https://pypi.org/project/matplotlib/
