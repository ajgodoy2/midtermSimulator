//Conjunto de funciones usadas por schedsim y schedstats para ejecutar los diferentes algoritmos
int obtenerArregloTiemposArrivoYBurst(int *tiemposArrivo, int *tiemposBurst, int *lecturaArchivo, int sizeLecturaArchivo);
int obtenerArregloTiempoEsperaFCFS(int *tiemposArrivo, int *tiemposBurst, int totalProcesos, int *tiemposEspera,int tipoEjecutable);
int obtenerArregloTiempoRetorno(int *tiemposEspera, int *tiemposBurst, int totalProcesos, int *tiemposRetorno);
int obtenerArregloTiempoEsperaSJF(int *tiemposArrivo, int *tiemposBurst, int totalProcesos, int *tiemposEspera,int tipoEjecutable);
float calcularPromedioEsperaRetorno(int *tiemposEsperaORetorno, int totalProcesos);
float calcularPromedioRetornoNormalizado(float *tiemposRetornoNormalizado, int totalProcesos);
int obtenerArregloTiempoEsperaRR(int *tiemposArrivo, int *tiemposBurst, int totalProcesos, int *tiemposEspera,int quantum,int tipoEjecutable);
int leerLinea(char *nombreArchivo, int *lecturaArchivo);
int obtenerArregloTiempoRetornoNormalizado(int *tiemposEspera, int *tiemposBurst, int totalProcesos, float *tiemposRetornoNormalizado);