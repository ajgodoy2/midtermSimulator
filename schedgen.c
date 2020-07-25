#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h> 

int main(int argc, char* argv[]){
    int fd;
    double ta, tb;

    //Se presenta un conjunto de validaciones a los argumentos ingresados por el usuario para guiarlo y manejar errores generales de uso
    if(argc ==1){
        printf("Ingrese argumentos para obtener resultados, a continuacion se muestra el uso correcto donde los parentesis denotan informacion adicional no incluirlos:\n"
        "schedgen valorEntero(mayor que 0) NúmeroDecimal(entre 0 y 1) NúmeroDecimal(entre 0 y 1) nombreArchivo(Con extension .dat) \n");
        return 0;
    }

    else if (argc==2)
    {
        if(atoi(argv[1])<=0){
            printf("Faltan tres argumentos \nPrimer argumento incorrecto debe ser entero mayor que 0, a continuacion se muestra el uso correcto donde los parentesis denotan " 
            "informacion adicional no incluirlos:\nschedgen valorEntero(mayor que 0) NúmeroPuntoFlotante(entre 0 y 1 separado por .) NúmeroPuntoFlotante(entre 0 y 1 separado por .) nombreArchivo(Con extension .dat)\n");
            return 0;
        }
        else{
            printf("Primer argumento correcto, pero faltan 3 argumentos extra, a contiuacion se muestra el uso correcto donde los parentesis denotan informacion "
            "adicional no incluirlos:\nschedgen valorEntero(mayor que 0) NúmeroPuntoFlotante(entre 0 y 1 separado por .) NúmeroPuntoFlotante(entre 0 y 1 separado por .) nombreArchivo(Con extension .dat)\n "
            );
            return 0;
        }
    }    
    else if(argc==3){
        if(atoi(argv[1])<=0){
            printf("Faltan dos argumentos \nPrimer argumento incorrecto debe ser entero mayor que 0, a continuacion se muestra el uso correcto donde los parentesis denotan " 
            "informacion adicional no incluirlos:\nschedgen valorEntero(mayor que 0) NúmeroPuntoFlotante(entre 0 y 1 separado por .) NúmeroPuntoFlotante(entre 0 y 1 separado por .) nombreArchivo(Con extension .dat)\n");
            return 0;
        }

        else if(atof(argv[2])<0 | atof(argv[2])>1){
            printf("Faltan dos argumentos \nSegundo argumento incorrecto debe ser entero entre 0 y 1, a continuacion se muestra el uso correcto donde los parentesis denotan " 
            "informacion adicional no incluirlos:\nschedgen valorEntero(mayor que 0) NúmeroPuntoFlotante(entre 0 y 1 separado por .) NúmeroPuntoFlotante(entre 0 y 1 separado por .) nombreArchivo(Con extension .dat)\n");
            return 0;
        }
        else{
            printf("Primer y segundo argumento correctos, pero faltan 2 argumentos extra, a continuacion se muestra el uso correcto donde los parentesis denotan informacion " 
            "adicional no incluirlos:\nschedgen valorEntero(mayor que 0) NúmeroPuntoFlotante(entre 0 y 1 separado por .) NúmeroPuntoFlotante(entre 0 y 1 separado por .) nombreArchivo(Con extension .dat)\n");
             return 0;
        }
    }
    else if (argc==4)
    {
        if(atoi(argv[1])<=0){
            printf("Faltan un argumento \nPrimer argumento incorrecto debe ser entero mayor que 0, a continuacion se muestra el uso correcto donde los parentesis denotan " 
            "informacion adicional no incluirlos:\nschedgen valorEntero(mayor que 0) NúmeroPuntoFlotante(entre 0 y 1 separado por .) NúmeroPuntoFlotante(entre 0 y 1 separado por .) nombreArchivo(Con extension .dat)\n");
            return 0;
        }
        else if ( atof(argv[2])<0 | atof(argv[2])>1)
        {
            printf("Faltan un argumento \nSegundo argumento incorrecto debe ser entero entre 0 y 1, a continuacion se muestra el uso correcto donde los parentesis denotan informacion " 
            "adicional no incluirlos: \nschedgen valorEntero(mayor que 0) NúmeroPuntoFlotante(entre 0 y 1 separado por .) NúmeroPuntoFlotante(entre 0 y 1 separado por .) nombreArchivo(Con extension .dat)\n");
            return 0;
        }
        else if ( atof(argv[3])<0 | atof(argv[3])>1)
        {
            printf("Faltan un argumento \nTercer argumento incorrecto debe ser entero entre 0 y 1, a continuacion se muestra el uso correcto donde los parentesis denotan informacion " 
            "adicional no incluirlos: \nschedgen valorEntero(mayor que 0) NúmeroPuntoFlotante(entre 0 y 1 separado por .) NúmeroPuntoFlotante(entre 0 y 1 separado por .) nombreArchivo(Con extension .dat)\n");
            return 0;
        }
        else{
            printf("Primeros 3 argumentos correctos, pero falta 1 argumentos extra, a continuacion se muestra el uso correcto donde los parentesis denotan informacion " 
            "adicional no incluirlos: \nschedgen valorEntero(mayor que 0) NúmeroPuntoFlotante(entre 0 y 1 separado por .) NúmeroPuntoFlotante(entre 0 y 1 separado por .) nombreArchivo(Con extension .dat)\n");
            return 0;
        }
    }
    else if (argc==5)
    {
        if(atoi(argv[1])<=0){
            printf("Numero de argumentos ingresados correcto \nPrimer argumento incorrecto debe ser entero mayor que 0, a continuacion se muestra el uso correcto donde los parentesis denotan " 
            "informacion adicional no incluirlos:\nschedgen valorEntero(mayor que 0) NúmeroPuntoFlotante(entre 0 y 1 separado por .) NúmeroPuntoFlotante(entre 0 y 1 separado por .) nombreArchivo(Con extension .dat)\n");
            return 0;
        }
        else if ( atof(argv[2])<0 | atof(argv[2])>1)
        {
            printf("Numero de argumentos ingresados correcto \nSegundo argumento incorrecto debe ser entero entre 0 y 1, a continuacion se muestra el uso correcto donde los parentesis denotan informacion " 
            "adicional no incluirlos: \nschedgen valorEntero(mayor que 0) NúmeroPuntoFlotante(entre 0 y 1 separado por .) NúmeroPuntoFlotante(entre 0 y 1 separado por .) nombreArchivo(Con extension .dat)\n");
            return 0;
        }
        else if ( atof(argv[3])<0 | atof(argv[3])>1)
        {
            printf("Numero de argumentos ingresados correcto \nTercer argumento incorrecto debe ser entero entre 0 y 1, a continuacion se muestra el uso correcto donde los parentesis denotan informacion " 
            "adicional no incluirlos: \nschedgen valorEntero(mayor que 0) NúmeroPuntoFlotante(entre 0 y 1 separado por .) NúmeroPuntoFlotante(entre 0 y 1 separado por .) nombreArchivo(Con extension .dat)\n");
            return 0;
        }
        else if( strchr(argv[4],'.') == NULL ){
            printf("Numero de argumentos ingresados correcto \nEn el cuarto argumento ingrese un nombre de archivo con una extension valida, a continuacion se muestra el uso correcto donde los parentesis denotan informacion "
            "adicional no incluirlos: \nschedgen valorEntero(mayor que 0) NúmeroPuntoFlotante(entre 0 y 1 separado por .) NúmeroPuntoFlotante(entre 0 y 1 separado por .) nombreArchivo(Con extension .dat)\n");
            return 0;
        }
        else if(strcmp(strchr(argv[4],'.') , ".dat") != 0){
            printf("Numero de argumentos ingresados correcto \nCuarto argumento debe ser un archivo con extesion .dat a continuacion se muestra el uso correcto donde los parentésis denotan informacion " 
            "adicional no incluirlos: \nschedgen valorEntero(mayor que 0) NúmeroPuntoFlotante(entre 0 y 1 separado por .) NúmeroPuntoFlotante(entre 0 y 1 separado por .) nombreArchivo(Con extension .dat)\n");
            return 0;
        }
        else{
            //Porción de código encargada de realizar la escritura del archivo en el formato esperado
            int argumento1= atoi(argv[1]);
            float argumento2= atof(argv[2]);
            float argumento3= atof(argv[3]);
            fd=open(argv[4],O_CREAT|O_RDWR|O_APPEND|O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
            if(fd < 0) {
	        printf("Error al crear el archivo puede que ya exista un archivo con ese nombre o archivo no existe en el directorio especificado, ingrese un archivo valido\n");
            return 0;
	        }
            int i,j,k;
            int temporal_llegada=-1;
            for(i=0;i<argumento1;i++){
                int temporal=0;
                int temporal_burst=0;
                ta=rand()/(double)RAND_MAX;
                while (ta>=argumento2)
                {
                    ta=rand()/(double)RAND_MAX;
                    temporal++;
                }
                if(temporal==0){
                    temporal_llegada++;
                }
                else
                {
                    temporal_llegada=temporal + temporal_llegada +1;
                }
                
                tb=rand()/(double)RAND_MAX;
                while (tb>=argumento3)
                {
                    tb=rand()/(double)RAND_MAX;
                    temporal_burst++;
                }
                if(temporal_burst==0){
                    temporal_burst++;
                }
                printf("Linea %d ta %d tb %d \n",i+1,temporal_llegada,temporal_burst);
                char temp1[5]={0};
                char temp2[5]={0};
                char escribir[10]={0};
                sprintf(temp1, "%d", temporal_llegada); 
                sprintf(temp2, "%d", temporal_burst);
                strcat(escribir,temp1);
                strcat(escribir," ");
                strcat(escribir,temp2);
                strcat(escribir,"\n");
                write(fd,escribir,strlen(escribir));
            } 
            close(fd);                      
        }

    }
    else if(argc >5){
        printf("Numero argumentos supera los esperados deben ser 4 en total, a continuacion se muestra el uso correcto donde los parentesis denotan informacion adicional no incluirlos:\n"
        "schedgen valorEntero(mayor que 0) valorEntero(entre 0 y 1) valorEntero(entre 0 y 1) nombreArchivo(Con extension .dat) \n");
        return 0;
    }
    return 0;
}