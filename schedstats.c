#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h> 
#include "libscheduler.h"

//Conjunto de funciones particulares para este ejecutable
int ordenarArreglo(int *arreglo, int tamano);
int fcfs(int *tiemposArrivo, int *tiemposBurst, int totalProcesos,int *tiemposEspera,int *tiempoRetorno,float *tiemposRetornoNormalizado);
int sjf(int *tiemposArrivo, int *tiemposBurst, int totalProcesos,int *tiemposEspera,int *tiempoRetorno,float *tiemposRetornoNormalizado);
int rr(int *tiemposArrivo, int *tiemposBurst, int totalProcesos, int quantum, int *tiemposEspera,int *tiempoRetorno,float *tiemposRetornoNormalizado);
int removerRepetidosArregloBurst(int totalProcesos,int *bufferSinRepetidos);
int ordenarBurstSinRepetidos(int totalProcesos,int *bufferSinRepetidos);
int escribirPrimeraLineaEnteros(int fd,int *burstOrdenadosSinRepetidos,int totalProcesos);
int encontrarFrecuencia(int*tiemposBurst,int totalProcesos,int valor);
int obtenerArregloIndicesFrecuenciaValor(int *tiemposBurst,int totalProcesos,int *indices,int valor);
float calculoPromedioPorBurst(int *indices, int *arregloTipoTiempo,int totalindices);
float calculoPromedioPorBurstNormalizado(int *indices, float *arregloTipoTiempo,int totalindices);

//Se presenta una serie de validaciones para guiar al usuario y evitar ciertos inconvenientes al ingresar parámetros al ejecutar el programa
int main(int argc, char* argv[]){
    if(argc==1){
        printf("Ingrese argumentos para obtener resultados, a continuacion se muestran los usos correctos donde los parentesis denotan informacion adicional no incluirlos:\n"
        "schedstats nombreArchivo(Con extension .dat)\n");
        return 0;
    }
    if(argc==2){
        if (strchr(argv[1], '.') == NULL)
        {
            printf("Numero de argumentos correcto \nPrimer argumento incorrecto ingrese un nombre de archivo con una extension valida en este caso .dat, a continuacion se muestra el uso correcto"
            "donde los parentesis denotan informacion adicional no incluirlos:\nschedstats nombreArchivo(Con extension .dat)\n");
        }
        else if (strcmp(strchr(argv[1], '.'), ".dat") != 0)
        {
            printf("Numero de argumentos correcto \nPrimer argumento incorrecto debe ser un archivo con extesion .dat a continuacion se muestra el uso correcto donde los parentesis" 
            "denotan informacion adicional no incluirlos:\nschedstats nombreArchivo(Con extension .dat)\n");
            return 0;
        }
        else{
            int fdRetorno;
            int fdEspera;
            int fdRetornoNormalizado;
            int lecturaArchivo[200] = {0};
            int totalProcesos = leerLinea(argv[1], lecturaArchivo);
            if(totalProcesos<2){
                printf("No se puede contniuar con la ejecución ingrese archivo con extension .dat con al menos 2 procesos\n");
                return 0;
                }
            int tiemposArrivo[totalProcesos];
            int tiemposBurst[totalProcesos];
            memset(tiemposArrivo, 0, totalProcesos * sizeof(int));
            memset(tiemposBurst, 0, totalProcesos * sizeof(int));
            obtenerArregloTiemposArrivoYBurst(tiemposArrivo, tiemposBurst, lecturaArchivo, totalProcesos * 2);
            int copiaTiemposBurst[totalProcesos];
            for(int i=0;i<totalProcesos;i++){
                copiaTiemposBurst[i]=tiemposBurst[i];
            }
            int bufferBurstSinRepetidos[200];
            for(int j=0;j<totalProcesos;j++){
                bufferBurstSinRepetidos[j]=tiemposBurst[j];
            }
            int totalRepetidos=removerRepetidosArregloBurst(totalProcesos,bufferBurstSinRepetidos);
            int tiemposBurstSinRepetidos[totalRepetidos];
            for(int k=0;k<totalRepetidos;k++){
                tiemposBurstSinRepetidos[k]=bufferBurstSinRepetidos[k];
            }
            //Se ordenan una copia de los burst para evitar problemas al usar los datos originales y se crean los archivos de salida que serán escritos posteriormente
            ordenarBurstSinRepetidos(totalRepetidos,tiemposBurstSinRepetidos);
            fdEspera=open("schedwaits.dat",O_CREAT|O_RDWR|O_APPEND,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            fdRetorno=open("schedturns.dat",O_CREAT|O_RDWR|O_APPEND,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            fdRetornoNormalizado=open("schednturns.dat",O_CREAT|O_RDWR|O_APPEND,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            escribirPrimeraLineaEnteros(fdEspera,tiemposBurstSinRepetidos,totalRepetidos);
            escribirPrimeraLineaEnteros(fdRetorno,tiemposBurstSinRepetidos,totalRepetidos);
            escribirPrimeraLineaEnteros(fdRetornoNormalizado,tiemposBurstSinRepetidos,totalRepetidos);
            //Se empleas matrices que representan los promedios por tiempos burst por columna y las filas depende de cada algoritmo
            float matrizTiemposEspera[5][totalRepetidos];
            float matrizTiemposRetorno[5][totalRepetidos];
            float matrizTiemposRetornoNormalizado[5][totalRepetidos];
            memset(matrizTiemposEspera,0,sizeof(matrizTiemposEspera));
            memset(matrizTiemposRetorno,0,sizeof(matrizTiemposRetorno));
            memset(matrizTiemposRetornoNormalizado,0,sizeof(matrizTiemposRetornoNormalizado));

            for(int i=0;i<totalRepetidos;i++){
                matrizTiemposEspera[0][i]=(float)tiemposBurstSinRepetidos[i];
            }
            for(int i=0;i<totalRepetidos;i++){
                matrizTiemposRetorno[0][i]=(float)tiemposBurstSinRepetidos[i];
            }
            for(int i=0;i<totalRepetidos;i++){
                matrizTiemposRetornoNormalizado[0][i]=(float)tiemposBurstSinRepetidos[i];
            }
            int tiemposEspera[totalProcesos];
            int tiempoRetorno[totalProcesos];
            float tiemposRetornoNormalizado[totalProcesos];
            {
                //Encuentra la fila de tiempos promedios de esperar, retorno y retorno normalizado usando el algoritmo FCFS
                fcfs(tiemposArrivo, tiemposBurst, totalProcesos,tiemposEspera,tiempoRetorno,tiemposRetornoNormalizado);
                printf("Ejecución de algoritmo FCFS \n");
                for(int i=0;i<totalRepetidos;i++){
                    int frecuencia=0;
                    frecuencia=encontrarFrecuencia(tiemposBurst,totalProcesos,tiemposBurstSinRepetidos[i]);
                    int indices[frecuencia];
                    memset(indices, 0, frecuencia * sizeof(int));
                    obtenerArregloIndicesFrecuenciaValor(tiemposBurst,totalProcesos,indices,tiemposBurstSinRepetidos[i]);
                    float promedioEspera=calculoPromedioPorBurst(indices,tiemposEspera,frecuencia);
                    float promedioRetorno=calculoPromedioPorBurst(indices,tiempoRetorno,frecuencia);
                    float promedioRetornoNormalizado=calculoPromedioPorBurstNormalizado(indices,tiemposRetornoNormalizado,frecuencia);
                    matrizTiemposEspera[1][i]=promedioEspera;
                    matrizTiemposRetorno[1][i]=promedioRetorno;
                    matrizTiemposRetornoNormalizado[1][i]=promedioRetornoNormalizado;
                }
                printf("Fin de ejecución algoritmo FCFS\n");
            }
                //Encuentra la fila de tiempos promedios de esperar, retorno y retorno normalizado usando el algoritmo SJF
                printf("Ejecución de algoritmo SJF apropiativo \n");
                sjf(tiemposArrivo, tiemposBurst, totalProcesos,tiemposEspera,tiempoRetorno,tiemposRetornoNormalizado);
                for(int i=0;i<totalRepetidos;i++){
                    int frecuencia=0;
                    frecuencia=encontrarFrecuencia(tiemposBurst,totalProcesos,tiemposBurstSinRepetidos[i]);
                    int indices[frecuencia];
                    memset(indices, 0, frecuencia * sizeof(int));
                    obtenerArregloIndicesFrecuenciaValor(tiemposBurst,totalProcesos,indices,tiemposBurstSinRepetidos[i]);
                    float promedioEspera=calculoPromedioPorBurst(indices,tiemposEspera,frecuencia);
                    float promedioRetorno=calculoPromedioPorBurst(indices,tiempoRetorno,frecuencia);
                    float promedioRetornoNormalizado=calculoPromedioPorBurstNormalizado(indices,tiemposRetornoNormalizado,frecuencia);
                    matrizTiemposEspera[2][i]=promedioEspera;
                    matrizTiemposRetorno[2][i]=promedioRetorno;
                    matrizTiemposRetornoNormalizado[2][i]=promedioRetornoNormalizado;
                }
                printf("Fin de ejecución algoritmo SJF\n");
            {
                //Encuentra la fila de tiempos promedios de esperar, retorno y retorno normalizado usando el algoritmo round robin con quantum 1
                printf("Ejecución de Round Robin con quantum 1\n");
                rr(tiemposArrivo, tiemposBurst, totalProcesos,1,tiemposEspera,tiempoRetorno,tiemposRetornoNormalizado);
                for(int i=0;i<totalRepetidos;i++){
                    int frecuencia=0;
                    frecuencia=encontrarFrecuencia(tiemposBurst,totalProcesos,tiemposBurstSinRepetidos[i]);
                    int indices[frecuencia];
                    memset(indices, 0, frecuencia * sizeof(int));
                    obtenerArregloIndicesFrecuenciaValor(tiemposBurst,totalProcesos,indices,tiemposBurstSinRepetidos[i]);
                    float promedioEspera=calculoPromedioPorBurst(indices,tiemposEspera,frecuencia);
                    float promedioRetorno=calculoPromedioPorBurst(indices,tiempoRetorno,frecuencia);
                    float promedioRetornoNormalizado=calculoPromedioPorBurstNormalizado(indices,tiemposRetornoNormalizado,frecuencia);
                    matrizTiemposEspera[3][i]=promedioEspera;
                    matrizTiemposRetorno[3][i]=promedioRetorno;
                    matrizTiemposRetornoNormalizado[3][i]=promedioRetornoNormalizado;
                }
            }
            {
                //Encuentra la fila de tiempos promedios de esperar, retorno y retorno normalizado usando el algoritmo round robin con quantum 4
                printf("Ejecución de Round Robin con quantum 4\n");
                rr(tiemposArrivo, tiemposBurst, totalProcesos,4,tiemposEspera,tiempoRetorno,tiemposRetornoNormalizado);
                for(int i=0;i<totalRepetidos;i++){
                    int frecuencia=0;
                    frecuencia=encontrarFrecuencia(tiemposBurst,totalProcesos,tiemposBurstSinRepetidos[i]);
                    int indices[frecuencia];
                    memset(indices, 0, frecuencia * sizeof(int));
                    obtenerArregloIndicesFrecuenciaValor(tiemposBurst,totalProcesos,indices,tiemposBurstSinRepetidos[i]);
                    float promedioEspera=calculoPromedioPorBurst(indices,tiemposEspera,frecuencia);
                    float promedioRetorno=calculoPromedioPorBurst(indices,tiempoRetorno,frecuencia);
                    float promedioRetornoNormalizado=calculoPromedioPorBurstNormalizado(indices,tiemposRetornoNormalizado,frecuencia);
                    matrizTiemposEspera[4][i]=promedioEspera;
                    matrizTiemposRetorno[4][i]=promedioRetorno;
                    matrizTiemposRetornoNormalizado[4][i]=promedioRetornoNormalizado;
                }
            }
            //Se encarga de pasar cada una de las matrices a los archivos correspondientes con los valores correctos
            for(int i=1;i<5;i++){
                char salto[10]={0};
                for (int j = 0; j < totalRepetidos; j++)
                {
                    char temporal[10]={0};
                    char escribir[10]={0};
                    sprintf(temporal, "%.2f", matrizTiemposEspera[i][j]); 
                    strcat(escribir,temporal);
                    strcat(escribir," "); 
                    write(fdEspera,escribir,strlen(escribir));
                }
                strcat(salto,"\n");
                write(fdEspera,salto,strlen(salto));  
            }
            for(int i=1;i<5;i++){
                char salto[10]={0};
                for (int j = 0; j < totalRepetidos; j++)
                {
                    char temporal[10]={0};
                    char escribir[10]={0};
                    sprintf(temporal, "%.2f", matrizTiemposRetorno[i][j]); 
                    strcat(escribir,temporal);
                    strcat(escribir," "); 
                    write(fdRetorno,escribir,strlen(escribir));
                }
                strcat(salto,"\n");
                write(fdRetorno,salto,strlen(salto));  
            }
            for(int i=1;i<5;i++){
                char salto[10]={0};
                for (int j = 0; j < totalRepetidos; j++)
                {
                    char temporal[10]={0};
                    char escribir[10]={0};
                    sprintf(temporal, "%.2f", matrizTiemposRetornoNormalizado[i][j]); 
                    strcat(escribir,temporal);
                    strcat(escribir," "); 
                    write(fdRetornoNormalizado,escribir,strlen(escribir));
                }
                strcat(salto,"\n");
                write(fdRetornoNormalizado,salto,strlen(salto));  
            } 
            close(fdEspera);
            close(fdRetorno);
            close(fdRetornoNormalizado);  
        }
    }
    if(argc>2){
        printf("Numero argumentos supera los esperados debe ser solo 1, a continuacion se muestra el uso correcto donde los parentesis denotan informacion adicional no incluirlos:\n"
        "schedstats nombreArchivo(Con extension .dat)\n");
        return 0;
    }
    return 0;
}

//Implementación de FCFS donde usa funciones de la librería para generar los arreglos con los tiempos requeridos
int fcfs(int *tiemposArrivo, int *tiemposBurst, int totalProcesos,int *tiemposEspera,int *tiempoRetorno,float *tiemposRetornoNormalizado)
{
    obtenerArregloTiempoEsperaFCFS(tiemposArrivo, tiemposBurst, totalProcesos, tiemposEspera,0);
    obtenerArregloTiempoRetorno(tiemposEspera, tiemposBurst, totalProcesos, tiempoRetorno);
    obtenerArregloTiempoRetornoNormalizado(tiemposEspera,tiemposBurst,totalProcesos,tiemposRetornoNormalizado);
    return 0;
}

//Implementación de SJF donde usa funciones de la librería para generar los arreglos con los tiempos requeridos
int sjf(int *tiemposArrivo, int *tiemposBurst, int totalProcesos, int *tiemposEspera,int *tiempoRetorno,float *tiemposRetornoNormalizado)
{
    obtenerArregloTiempoEsperaSJF(tiemposArrivo, tiemposBurst, totalProcesos, tiemposEspera,0);
    obtenerArregloTiempoRetorno(tiemposEspera, tiemposBurst, totalProcesos, tiempoRetorno);
    obtenerArregloTiempoRetornoNormalizado(tiemposEspera,tiemposBurst,totalProcesos,tiemposRetornoNormalizado);
    return 0;
}

//Implementación de RR donde usa funciones de la librería para generar los arreglos con los tiempos requeridos
int rr(int *tiemposArrivo, int *tiemposBurst, int totalProcesos, int quantum, int *tiemposEspera,int *tiempoRetorno,float *tiemposRetornoNormalizado){
    obtenerArregloTiempoEsperaRR(tiemposArrivo, tiemposBurst, totalProcesos, tiemposEspera,quantum,0);
    obtenerArregloTiempoRetorno(tiemposEspera, tiemposBurst, totalProcesos, tiempoRetorno);
    obtenerArregloTiempoRetornoNormalizado(tiemposEspera,tiemposBurst,totalProcesos,tiemposRetornoNormalizado);
    return 0;
}

//Función para eliminar repetidos en arreglo burst para trabajar con los tiempos burst de forma individual
int removerRepetidosArregloBurst(int totalProcesos,int *bufferSinRepetidos){
    int respuesta=totalProcesos;
    for(int j=0;j<respuesta;j++){
        for(int k=j+1; k<respuesta; k++){
            if(bufferSinRepetidos[j]==bufferSinRepetidos[k]){
                for(int l=k;l<respuesta;l++){
                    bufferSinRepetidos[l]=bufferSinRepetidos[l+1];
                }
            respuesta--;
            k--;
            }
        }
    }
    return respuesta;
}

//Función para ordenar los tiempos de ráfaga sin valores repetidos para posteriormente escribirlos en ese orden al archivo
int ordenarBurstSinRepetidos(int totalProcesos,int *bufferSinRepetidos){
    int temporal;
    for(int i=0;i<totalProcesos;i++){
        for(int j=i+1;j<totalProcesos;j++){
            if(bufferSinRepetidos[i]>bufferSinRepetidos[j]){
                temporal=bufferSinRepetidos[i];
                bufferSinRepetidos[i]=bufferSinRepetidos[j];
                bufferSinRepetidos[j]=temporal;
            }
        }
    }
    return 0;
}

//Función para escribir la primera línea con tiempos burst al archivo de salida
int escribirPrimeraLineaEnteros(int fd,int *burstOrdenadosSinRepetidos,int totalProcesos){
    char salto[10]={0};
    for(int i=0;i<totalProcesos;i++){
        char temporal[10]={0};
        char escribir[10]={0};
        sprintf(temporal, "%d", burstOrdenadosSinRepetidos[i]); 
        strcat(escribir,temporal);
        strcat(escribir," "); 
        write(fd,escribir,strlen(escribir));
        }       
    strcat(salto,"\n");
    write(fd,salto,strlen(salto));
}

//Función para encontrar la frecuencia de un valor especifico en un arreglo
int encontrarFrecuencia(int *tiemposBurst,int totalProcesos,int valor){
    int conteo=0;
    for(int i=0;i<totalProcesos;i++){
        if(tiemposBurst[i]==valor){
            conteo++;
        }
    }
    return conteo;
}

//Implementación para obtener los indices de los tiempos burst con igual valor para guardarlos en un arreglo y usarlos
int obtenerArregloIndicesFrecuenciaValor(int *tiemposBurst,int totalProcesos,int *indices,int valor){
    int temporal=0;
    for(int i=0;i<totalProcesos;i++){
        if(tiemposBurst[i]==valor){
            indices[temporal]=i;  
            temporal++;    
        }
    }
    return 0;
}

//Implementación para calcular el promedio de los tiempos de espera y retorno por cada uno de los burst con valores repetidos en base a sus indices
float calculoPromedioPorBurst(int *indices, int *arregloTipoTiempo,int totalindices){
    int temporal=0;
    for(int i=0;i<totalindices;i++){
        temporal=temporal+arregloTipoTiempo[indices[i]];
    }
    float respuesta= (float)temporal / totalindices;
    return respuesta;
}

//Implementación para calcular promedio de los tiempos de retorno normalizado por cada uno de los burst con valores repetidos en base a sus indices
float calculoPromedioPorBurstNormalizado(int *indices, float *arregloTipoTiempo, int totalindices){
    float temporal=0;
    for(int i=0;i<totalindices;i++){
        temporal=temporal+arregloTipoTiempo[indices[i]];
    }
    float respuesta= temporal / totalindices;
    return respuesta;
}
