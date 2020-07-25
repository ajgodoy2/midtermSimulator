#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h> 
#include "libscheduler.h"

//Se agregan funciones para implementar los diferentes algoritmos 
int fcfs(int *tiemposArrivo, int *tiemposBurst, int totalProcesos);
int sjf(int *tiemposArrivo, int *tiemposBurst, int totalProcesos);
int rr(int *tiemposArrivo, int *tiemposBurst, int totalProcesos,int quantum);

//Se presenta una serie de validaciones para guiar al usuario y evitar ciertos inconvenientes al ingresar parámetros al ejecutar el programa
int main(int argc, char *argv[])
{
    int fd;
    if (argc == 1)
    {
        printf("Ingrese argumentos para obtener resultados, a continuacion se muestran los usos correctos donde los parentesis denotan informacion adicional no incluirlos:\n"
               "schedsim nombreArchivo(Con extension .dat) nombreAlgoritmo(fcfs o sjf) \nschedsim nombreArchivo(Con extension .dat) rr numeroEntero(mayor que 0) \n");
        return 0;
    }

    else if (argc == 2)
    {
        if (strchr(argv[1], '.') == NULL)
        {
            printf("Faltan argumentos \nPrimer argumento incorrecto ingrese un nombre de archivo con una extension valida en este caso .dat, a continuacion se muestra el uso correcto donde los parentesis denotan "
                   "informacion adicional no incluirlos: \nschedsim nombreArchivo(Con extension .dat) nombreAlgoritmo(fcfs o sjf) \nschedsim nombreArchivo(Con extension .dat) rr numeroEntero(mayor que 0) \n");
            return 0;
        }
        else if (strcmp(strchr(argv[1], '.'), ".dat") != 0)
        {
            printf("Faltan argumentos \nPrimer argumento incorrecto debe ser un archivo con extesion .dat a continuacion se muestra el uso correcto donde los parentesis denotan informacion"
                   "adicional no incluirlos: \nschedsim nombreArchivo(Con extension .dat) nombreAlgoritmo(fcfs o sjf) \nschedsim nombreArchivo(Con extension .dat) rr numeroEntero(mayor que 0) \n");
            return 0;
        }
        else
        {
            printf("Primer argumento correcto, pero faltan argumentos extras, a contiuacion se muestra el uso correcto donde los parentesis denotan informacion adicional"
                   "no incluirlos:\nschedsim nombreArchivo(Con extension .dat) nombreAlgoritmo(fcfs o sjf) \nschedsim nombreArchivo(Con extension .dat) rr numeroEntero(mayor que 0) \n ");
            return 0;
        }
    }
    else if (argc == 3)
    {
        if (strchr(argv[1], '.') == NULL)
        {
            printf("Número de argumentos correcto \nPrimer argumento incorrecto ingrese un nombre de archivo con una extension valida en este caso .dat, a continuacion se muestra el uso correcto donde los parentesis denotan "
                   "informacion adicional no incluirlos: \nschedsim nombreArchivo(Con extension .dat) nombreAlgoritmo(fcfs o sjf) \nschedsim nombreArchivo(Con extension .dat) rr numeroEntero(mayor que 0) \n");
            return 0;
        }
        else if (strcmp(strchr(argv[1], '.'), ".dat") != 0)
        {
            printf("Número de argumentos corrrecto \nPrimer argumento incorrecto debe ser un archivo con extesion .dat a continuacion se muestra el uso correcto donde los parentesis denotan informacion"
                   "adicional no incluirlos: \nschedsim nombreArchivo(Con extension .dat) nombreAlgoritmo(fcfs o sjf) \nschedsim nombreArchivo(Con extension .dat) rr numeroEntero(mayor que 0) \n");
            return 0;
        }
        else if ((strcmp(argv[2], "fcfs") != 0) & (strcmp(argv[2], "sjf") != 0))
        {
            printf("Número de argumentos corrrecto \nSegundo argumento incorrecto debe ser un nombre de algoritmo válido ya sea fcfs o sjf a continuacion se muestra el uso correcto donde los parentesis denotan informacion"
                   "adicional no incluirlos: \nschedsim nombreArchivo(Con extension .dat) nombreAlgoritmo(fcfs o sjf) \nschedsim nombreArchivo(Con extension .dat) rr numeroEntero(mayor que 0) \n");
            return 0;
        }
        else
        {
            //Se usa el algoritmo fcfs en caso que el usario lo desee y se le mostrarán las salidas solicitadas
            if (strcmp(argv[2], "fcfs") == 0)
            {
                int lecturaArchivo[200] = {0};
                printf("Ejecución de algoritmo FCFS \n");
                int totalProcesos = leerLinea(argv[1], lecturaArchivo);
                if(totalProcesos<2){
                    printf("No se puede contniuar con la ejecución ingrese archivo con al menos 2 procesos\n");
                    return 0;
                }
                int tiemposArrivo[totalProcesos];
                int tiemposBurst[totalProcesos];
                memset(tiemposArrivo, 0, totalProcesos * sizeof(int));
                memset(tiemposBurst, 0, totalProcesos * sizeof(int));
                obtenerArregloTiemposArrivoYBurst(tiemposArrivo, tiemposBurst, lecturaArchivo, totalProcesos * 2);
                fcfs(tiemposArrivo, tiemposBurst, totalProcesos);
                return 0;
            }
            //Se usa el algoritmo sjf en caso que el usario lo desee y se le mostrarán las salidas solicitadas
            if (strcmp(argv[2], "sjf") == 0)
            {
                int lecturaArchivo[200] = {0};
                printf("Ejecución de algoritmo SJF apropiativo \n");
                int totalProcesos = leerLinea(argv[1], lecturaArchivo);
                if(totalProcesos<2){
                    printf("No se puede contniuar con la ejecución ingrese archivo con al menos 2 procesos\n");
                    return 0;
                }
                int tiemposArrivo[totalProcesos];
                int tiemposBurst[totalProcesos];
                memset(tiemposArrivo, 0, totalProcesos * sizeof(int));
                memset(tiemposBurst, 0, totalProcesos * sizeof(int));
                obtenerArregloTiemposArrivoYBurst(tiemposArrivo, tiemposBurst, lecturaArchivo, totalProcesos * 2);
                sjf(tiemposArrivo, tiemposBurst, totalProcesos);
                return 0;
            }
            return 0;
        }
    }
    else if (argc == 4)
    {
        if (strchr(argv[1], '.') == NULL)
        {
            printf("Número de argumentos correcto \nPrimer argumento incorrecto ingrese un nombre de archivo con una extension valida en este caso .dat, a continuacion se muestra el uso correcto donde los parentesis denotan "
                   "informacion adicional no incluirlos: \nschedsim nombreArchivo(Con extension .dat) nombreAlgoritmo(fcfs o sjf) \nschedsim nombreArchivo(Con extension .dat) rr numeroEntero(mayor que 0) \n");
            return 0;
        }
        else if (strcmp(strchr(argv[1], '.'), ".dat") != 0)
        {
            printf("Número de argumentos corrrecto \nPrimer argumento incorrecto debe ser un archivo con extesion .dat a continuacion se muestra el uso correcto donde los parentesis denotan informacion"
                   "adicional no incluirlos: \nschedsim nombreArchivo(Con extension .dat) nombreAlgoritmo(fcfs o sjf) \nschedsim nombreArchivo(Con extension .dat) rr numeroEntero(mayor que 0) \n");
            return 0;
        }
        else if (strcmp(argv[2], "rr") != 0)
        {
            printf("Número de argumentos corrrecto \nSegundo argumento incorrecto debe ser un nombre de algoritmo válido en este caso rr haciendo referencia a round robin, a continuacion se muestra el uso correcto donde los parentesis denotan informacion"
                   "adicional no incluirlos: \nschedsim nombreArchivo(Con extension .dat) nombreAlgoritmo(fcfs o sjf) \nschedsim nombreArchivo(Con extension .dat) rr numeroEntero(mayor que 0) \n");
            return 0;
        }
        else if (argv[3] <= 0)
        {
            printf("Número de argumentos corrrecto \nTercer argumento incorrecto debe ser un numero entero mayor que 0, a continuacion se muestra el uso correcto donde los parentesis denotan informacion"
                   "adicional no incluirlos: \nschedsim nombreArchivo(Con extension .dat) nombreAlgoritmo(fcfs o sjf) \nschedsim nombreArchivo(Con extension .dat) rr numeroEntero(mayor que 0) \n");
            return 0;
        }
        //Se usa el algoritmo round robin en caso que el usario lo desee y se le mostrarán las salidas solicitadas
        else
        {
            int quantum=atoi(argv[3]);
            printf("Ejecución de Round Robin con quantum %d\n",quantum);
            int lecturaArchivo[200] = {0};
            int totalProcesos = leerLinea(argv[1], lecturaArchivo);
            if(totalProcesos<2){
                printf("No se puede contniuar con la ejecución ingrese archivo con al menos 2 procesos\n");
                return 0;
                }
            int tiemposArrivo[totalProcesos];
            int tiemposBurst[totalProcesos];
            memset(tiemposArrivo, 0, totalProcesos * sizeof(int));
            memset(tiemposBurst, 0, totalProcesos * sizeof(int));
            obtenerArregloTiemposArrivoYBurst(tiemposArrivo, tiemposBurst, lecturaArchivo, totalProcesos * 2);
            rr(tiemposArrivo, tiemposBurst, totalProcesos,quantum);
            return 0;
        }
    }
    else if (argc > 4)
    {
        printf("Numero argumentos supera los esperados deben ser 3 o máximo 4 y cumplir característias específicas, a continuacion se muestra el uso correcto donde los parentesis denotan informacion adicional no incluirlos:\n"
               "schedsim nombreArchivo(Con extension .dat) nombreAlgoritmo(fcfs o sjf) \nschedsim nombreArchivo(Con extension .dat) rr numeroEntero(mayor que 0) \n");
        return 0;
    }
    return 0;
}

//Se obtienen los diferentes arreglos de salida usando fcfs y se presenta los promedios esperados la ejecución se da en los archivos de la librería 
int fcfs(int *tiemposArrivo, int *tiemposBurst, int totalProcesos)
{
    int tiemposEspera[totalProcesos];
    int tiempoRetorno[totalProcesos];
    float tiemposRetornoNormalizado[totalProcesos];
    obtenerArregloTiempoEsperaFCFS(tiemposArrivo, tiemposBurst, totalProcesos, tiemposEspera,1);
    obtenerArregloTiempoRetorno(tiemposEspera, tiemposBurst, totalProcesos, tiempoRetorno);
    obtenerArregloTiempoRetornoNormalizado(tiemposEspera,tiemposBurst,totalProcesos,tiemposRetornoNormalizado);
    float promedioRetorno = calcularPromedioEsperaRetorno(tiempoRetorno, totalProcesos);
    float promedioEspera = calcularPromedioEsperaRetorno(tiemposEspera, totalProcesos);
    float promedioRetornoNormalizado = calcularPromedioRetornoNormalizado(tiemposRetornoNormalizado, totalProcesos);
    printf("Promedio de tiempo de retorno = %.2f\n", promedioRetorno);
    printf("Promedio de tiempo de retorno normalizado = %.2f\n", promedioRetornoNormalizado);
    printf("Promedio tiempo de espera = %.2f\n", promedioEspera);
    return 0;
}

//Se obtienen los diferentes arreglos de salida usando fcfs y se presenta los promedios esperados la ejecución se da en los archivos de la librería 
int sjf(int *tiemposArrivo, int *tiemposBurst, int totalProcesos)
{
    int tiemposEspera[totalProcesos];
    int tiempoRetorno[totalProcesos];
    float tiemposRetornoNormalizado[totalProcesos];
    obtenerArregloTiempoEsperaSJF(tiemposArrivo, tiemposBurst, totalProcesos, tiemposEspera,1);
    obtenerArregloTiempoRetorno(tiemposEspera, tiemposBurst, totalProcesos, tiempoRetorno);
    obtenerArregloTiempoRetornoNormalizado(tiemposEspera,tiemposBurst,totalProcesos,tiemposRetornoNormalizado);
    float promedioRetorno = calcularPromedioEsperaRetorno(tiempoRetorno, totalProcesos);
    float promedioEspera = calcularPromedioEsperaRetorno(tiemposEspera, totalProcesos);
    float promedioRetornoNormalizado = calcularPromedioRetornoNormalizado(tiemposRetornoNormalizado, totalProcesos);
    printf("Promedio de tiempo de retorno = %.2f\n", promedioRetorno);
    printf("Promedio de tiempo de retorno normalizado = %.2f\n", promedioRetornoNormalizado);
    printf("Promedio tiempo de espera = %.2f\n", promedioEspera);
    return 0;
}

//Se obtienen los diferentes arreglos de salida usando fcfs y se presenta los promedios esperados la ejecución se da en los archivos de la librería
int rr(int *tiemposArrivo, int *tiemposBurst, int totalProcesos, int quantum){
    int tiemposEspera[totalProcesos];
    int tiempoRetorno[totalProcesos];
    float tiemposRetornoNormalizado[totalProcesos];
    obtenerArregloTiempoEsperaRR(tiemposArrivo, tiemposBurst, totalProcesos, tiemposEspera,quantum,1);
    obtenerArregloTiempoRetorno(tiemposEspera, tiemposBurst, totalProcesos, tiempoRetorno);
    obtenerArregloTiempoRetornoNormalizado(tiemposEspera,tiemposBurst,totalProcesos,tiemposRetornoNormalizado);
    float promedioRetorno = calcularPromedioEsperaRetorno(tiempoRetorno, totalProcesos);
    float promedioEspera = calcularPromedioEsperaRetorno(tiemposEspera, totalProcesos);
    float promedioRetornoNormalizado = calcularPromedioRetornoNormalizado(tiemposRetornoNormalizado, totalProcesos);
    printf("Promedio de tiempo de retorno = %.2f\n", promedioRetorno);
    printf("Promedio de tiempo de retorno normalizado = %.2f\n", promedioRetornoNormalizado);
    printf("Promedio tiempo de espera = %.2f\n", promedioEspera);
    return 0;
}


