#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h> 

// Conjunto de funciones destinadas a la implementación de los diferentes algoritmos
// Función para obtener los arreglos de tiempos de arribo y burst una vez que han sido leídos y guardados en un solo arreglo
int obtenerArregloTiemposArrivoYBurst(int *tiemposArrivo, int *tiemposBurst, int *lecturaArchivo, int sizeLecturaArchivo)
{
    int temporalArrivo = 0;
    int temporalBurst = 0;
    for (int i = 0; i < sizeLecturaArchivo; i++)
    {
        if (i % 2 == 0)
        {
            tiemposArrivo[temporalArrivo] = lecturaArchivo[i];
            temporalArrivo++;
        }
        else
        {
            tiemposBurst[temporalBurst] = lecturaArchivo[i];
            temporalBurst++;
        }
    }
    return 0;
}

//Función encargada de encontrar el arreglo de tiempos de espera de los procesos usando el algoritmo FCFS para posteriormente obtener los promedios requeridos, se imprime la salida esperada
int obtenerArregloTiempoEsperaFCFS(int *tiemposArrivo, int *tiemposBurst, int totalProcesos, int *tiemposEspera,int tipoEjecutable)
{
    int bufferCopiatiemposBurst[totalProcesos];
    for(int i =0;i < totalProcesos;i++){
        bufferCopiatiemposBurst[i]=tiemposBurst[i];
    }
    int tiempo=0;
    int procesosTerminados=0;
    int bandera=0;
    int procesoEjecucion=0;
    int finalizacionProceso=0;
    for(tiempo=0;procesosTerminados!=totalProcesos;tiempo++){        
        for (int j = 0; j < totalProcesos & bandera == 0;j++)
        {   
            if(tiemposArrivo[j]<=tiempo && bufferCopiatiemposBurst[j]>0){
            procesoEjecucion=j;
            bandera=1;
            }
        }
        if (bandera==0)
        {
            if(tipoEjecutable==1){
                printf("Tiempo iddle t=%d \n",tiempo);
            }
            
        }
        else if(bandera==1){
            bufferCopiatiemposBurst[procesoEjecucion]=0;
            tiempo=tiempo+tiemposBurst[procesoEjecucion]-1;
            if(bufferCopiatiemposBurst[procesoEjecucion]==0){
                finalizacionProceso=tiempo+1;
                bandera=0;
                tiemposEspera[procesoEjecucion]=finalizacionProceso-tiemposArrivo[procesoEjecucion]-tiemposBurst[procesoEjecucion];
                if(tipoEjecutable==1){
                    printf("%d: runs %d-%d -> end = %d, (arr=%d), turn=%d, (burst=%d), wait=%d\n", procesoEjecucion+1, tiemposArrivo[procesoEjecucion] + tiemposEspera[procesoEjecucion], finalizacionProceso,
                    finalizacionProceso, tiemposArrivo[procesoEjecucion], tiemposBurst[procesoEjecucion] + tiemposEspera[procesoEjecucion], tiemposBurst[procesoEjecucion], 
                    tiemposEspera[procesoEjecucion]);
                }
                procesosTerminados++;
            }
        }
    }
    return 0;
}

//Función para obtener el arreglo de tiempos de retorno para cualquiera de los algoritmos
int obtenerArregloTiempoRetorno(int *tiemposEspera, int *tiemposBurst, int totalProcesos, int *tiemposRetorno)
{
    for (int i = 0; i < totalProcesos; i++)
    {
        tiemposRetorno[i] = tiemposEspera[i] + tiemposBurst[i];
    }
    return 0;
}

//Función para calcular el promedio de los tiempos de espera y retorno
float calcularPromedioEsperaRetorno(int *tiemposEsperaORetorno, int totalProcesos)
{
    int temporal = 0;
    for (int i = 0; i < totalProcesos; i++)
    {
        temporal = temporal + tiemposEsperaORetorno[i];
    }
    float respuesta = (float)temporal / totalProcesos;
    return respuesta;
}

//Función para encontrar el arreglo de tiempos de retorno normalizado usando tiempos de espera y ráfaga por proceso
int obtenerArregloTiempoRetornoNormalizado(int *tiemposEspera, int *tiemposBurst, int totalProcesos, float *tiemposRetornoNormalizado){
    int buffer[totalProcesos];
    for (int i = 0; i < totalProcesos; i++)
    {
        buffer[i] = tiemposEspera[i] + tiemposBurst[i];
    }
    for (int j = 0; j < totalProcesos; j++)
    {
        tiemposRetornoNormalizado[j] = (float)buffer[j] / tiemposBurst[j];
    }
    return 0;
}

//Función para calcular el promedio de retorno normalizado en base al arreglo previamente creado
float calcularPromedioRetornoNormalizado(float *tiemposRetornoNormalizado, int totalProcesos)
{
    float temporal = 0;
    for (int k = 0; k < totalProcesos; k++)
    {
        temporal = temporal + tiemposRetornoNormalizado[k];
    }
    float respuesta = temporal / totalProcesos;
    return respuesta;
}

//Función para encontrar los tiempos de espera usando el algortimo sjf y posteriormente guardarlos en un arreglo para calcular los tiempos solicitados, se imprime la ejecución esperada
int obtenerArregloTiempoEsperaSJF(int *tiemposArrivo, int *tiemposBurst, int totalProcesos, int *tiemposEspera,int tipoEjecutable){
    int bufferCopiatiemposBurst[totalProcesos];
    for(int i =0;i < totalProcesos;i++){
        bufferCopiatiemposBurst[i]=tiemposBurst[i];
    }
    int finalizacionProceso=0;
    int procesosTerminados=0;
    int tiempo;
    int minimoRafaga=2147483647;
    int procesoMasCorto=0;
    int bandera=0;
    int precesoAnterior=0;
    int tiempoEjecucion=0;
    int bufferProcesoEjecucion[totalProcesos];
    memset(bufferProcesoEjecucion, 0, totalProcesos * sizeof(int));
    for(tiempo=0;procesosTerminados!=totalProcesos;tiempo++){
        for(int j=0;j<totalProcesos;j++){
            if(tiemposArrivo[j]<=tiempo & bufferCopiatiemposBurst[j]<minimoRafaga & bufferCopiatiemposBurst[j]>0){
                minimoRafaga=bufferCopiatiemposBurst[j];
                procesoMasCorto=j;
                bandera=1;
            }
        }
        if(bandera==0){
            if(tipoEjecutable==1){
                printf("Tiempo iddle t=%d \n",tiempo);
            }
            
        }

        if(bandera==1){
        bufferCopiatiemposBurst[procesoMasCorto]--;
        minimoRafaga = bufferCopiatiemposBurst[procesoMasCorto]; 
        if (minimoRafaga == 0){
            minimoRafaga = 2147483647; 
            }
        if(precesoAnterior!=procesoMasCorto & bufferCopiatiemposBurst[precesoAnterior]!=0 ){
            if(tipoEjecutable==1){
                tiempoEjecucion=tiemposBurst[precesoAnterior]-bufferCopiatiemposBurst[precesoAnterior];
                printf("%d: runs %d-%d\n",precesoAnterior + 1,tiempo-tiempoEjecucion,tiempo);
                bufferProcesoEjecucion[precesoAnterior]=tiempoEjecucion+bufferProcesoEjecucion[precesoAnterior];
            }
        }
        if (bufferCopiatiemposBurst[procesoMasCorto] == 0) { 
            procesosTerminados++; 
            finalizacionProceso = tiempo + 1;
            bandera=0;
            tiemposEspera[procesoMasCorto] = finalizacionProceso - tiemposArrivo[procesoMasCorto] - tiemposBurst[procesoMasCorto]; 
            if(tipoEjecutable==1){
                printf("%d: runs %d-%d -> end = %d, (arr=%d), turn=%d, (burst=%d), wait=%d\n", procesoMasCorto + 1, tiemposArrivo[procesoMasCorto] + tiemposEspera[procesoMasCorto]+bufferProcesoEjecucion[procesoMasCorto], 
                finalizacionProceso, finalizacionProceso, tiemposArrivo[procesoMasCorto], tiemposBurst[procesoMasCorto]+ tiemposEspera[procesoMasCorto], 
                tiemposBurst[procesoMasCorto], tiemposEspera[procesoMasCorto]);
            }
            if (tiemposEspera[procesoMasCorto] < 0) {
                tiemposEspera[procesoMasCorto] = 0;
                }     
            }    
        }
        precesoAnterior=procesoMasCorto;
    }
    return 0;
}

//Función para obtener los tiempos de espera usando round robin con diferentes quantums para posteriormente calcular los tiempos solicitados y muestra las salidas de ejecución esperadas
int obtenerArregloTiempoEsperaRR(int *tiemposArrivo, int *tiemposBurst, int totalProcesos, int *tiemposEspera,int quantum,int tipoEjecutable){
    int bufferCopiatiemposBurst[totalProcesos];
    int i,tiempoEspera,terminado;
    terminado=0;
    int tiempo=0;
    int finalizacionProceso;
    int procesosTerminados=0;
    int tiempoiddle=0;
    tiempoEspera=0;
    int procesoEjecucion=0;
    for(int i =0;i < totalProcesos;i++){
        bufferCopiatiemposBurst[i]=tiemposBurst[i];
    }
    for(int tiempo=0;procesosTerminados!=totalProcesos;tiempo++){
        int procesoAnterior=0;
        for( int j = 0; j<totalProcesos && tiempoiddle==0;j++)
        {
            if(tiemposArrivo[j] <= tiempo){
                if(bufferCopiatiemposBurst[j] <= quantum && bufferCopiatiemposBurst[j] > 0)
                {   
                    //trabajar tipo cola
                    printf("tiempo1 %d\n",tiempo);
                    tiempo=tiempo+bufferCopiatiemposBurst[j]-1;
                    bufferCopiatiemposBurst[j] = 0;
                    procesoEjecucion=j;
                    terminado = 1;
                    tiempoiddle =1;
                    printf("tiempo2 %d\n",tiempo);
                }
                else if(bufferCopiatiemposBurst[j] > 0 )
                {
                    printf("tiempo3 %d\n",tiempo);
                    bufferCopiatiemposBurst[j] = bufferCopiatiemposBurst[j] - quantum;
                    tiempo=tiempo+quantum;
                    if(tipoEjecutable==1){
                        printf("%d: runs %d-%d\n",j + 1,tiempo-quantum,tiempo);
                    }
                    printf("tiempo4 %d\n",tiempo);
                }
            }
        }
        if(tiempoiddle==0){
            printf("Tiempo iddle t=%d \n",tiempo);
        }
        if(tiempoiddle==1){
            if(bufferCopiatiemposBurst[procesoEjecucion] == 0 && terminado == 1)
            { 
            procesosTerminados++;
            finalizacionProceso=tiempo+1;
            printf("F %d\n",finalizacionProceso);
            tiempoEspera =  finalizacionProceso - tiemposArrivo[procesoEjecucion] - tiemposBurst[procesoEjecucion];
            tiemposEspera[procesoEjecucion] = tiempoEspera;
            if(tipoEjecutable==1){
                printf("%d: runs %d-%d -> end = %d, (arr=%d), turn=%d, (burst=%d), wait=%d\n", procesoEjecucion + 1, tiemposArrivo[procesoEjecucion] + tiemposEspera[procesoEjecucion], 
                finalizacionProceso, finalizacionProceso, tiemposArrivo[procesoEjecucion], tiemposBurst[procesoEjecucion]+ tiemposEspera[procesoEjecucion], 
                tiemposBurst[procesoEjecucion], tiemposEspera[procesoEjecucion]);
            }
            terminado =0;
            tiempoiddle =0;
            }
        }              
        
    }
    return 0;
}

//Permite leer los archivos de entrada línea por línea
int leerLinea(char *nombreArchivo, int *lecturaArchivo)
{
    int totalLineas = 0;
    FILE *fp;
    char *linea = NULL;
    size_t longitud = 0;
    int temporal = 0;
    int valorLiedo;
    char *temporalLinea;
    fp = fopen(nombreArchivo, "r");
    if (fp == NULL)
    {
        printf("Error al abrir el archivo \n");
        return 0;
    }
    while ((getline(&linea, &longitud, fp)) != -1)
    {
        temporalLinea = malloc(strlen(linea) + 1); 
        strcpy(temporalLinea, linea);
        if(strchr(temporalLinea,' ')!=NULL){
            int indiceEliminar = strlen(linea) - 1;
            memmove(&linea[indiceEliminar], &linea[indiceEliminar + 1], strlen(linea) - indiceEliminar);
            char *token;
            token = strtok(linea, " ");
            while (token != NULL)
            {
                sscanf(token, "%d", &valorLiedo);
                lecturaArchivo[temporal] = valorLiedo;
                temporal++;
                token = strtok(NULL, " ");
            }
            totalLineas++;
        }
        else{
            printf("Finalizacion de lectura archivo, la siguiente línea se encuentra vacía\n");
        }
    }
    fclose(fp);
    return totalLineas;
}

