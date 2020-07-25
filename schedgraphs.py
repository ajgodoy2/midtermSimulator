import pandas as pd
import matplotlib.pyplot as plt

dataframeTiemposEspera=pd.read_csv("schedwaits.dat", sep=" ",header=None)
dataframeTiemposEspera=dataframeTiemposEspera.drop(4, 1)
dataframeTiemposEspera=dataframeTiemposEspera.T
print("DataFrame Tiempos Espera\n")
print(dataframeTiemposEspera)
dataframeTiemposRetorno=pd.read_csv("schedturns.dat", sep=" ", header=None)
dataframeTiemposRetorno=dataframeTiemposRetorno.drop(4, 1)
dataframeTiemposRetorno=dataframeTiemposRetorno.T
print("DataFrame Tiempos Retorno\n")
print(dataframeTiemposRetorno)
dataframeTiemposRetornoNormalizado=pd.read_csv("schednturns.dat", sep=" ", header=None)
dataframeTiemposRetornoNormalizado=dataframeTiemposRetornoNormalizado.drop(4, 1)
print("DataFrame Tiempos Retorno Normalizado\n")
dataframeTiemposRetornoNormalizado=dataframeTiemposRetornoNormalizado.T
print(dataframeTiemposRetornoNormalizado)
axEspera = plt.gca()
axEspera.set_title('Tiempos de Espera')
axEspera.set_ylabel('Promedio Tiempos de espera')
dataframeTiemposEspera.plot(kind='line',x=0,y=1,ax=axEspera,label="FCFS")
dataframeTiemposEspera.plot(kind='line',x=0,y=2, color='red', ax=axEspera,label="SJF")
dataframeTiemposEspera.plot(kind='line',x=0,y=3, color='green',ax=axEspera,label="RR1")
dataframeTiemposEspera.plot(kind='line',x=0,y=4, color='yellow', ax=axEspera,label="RR4")
axEspera.set_xlabel('Tiempos de ráfaga')
plt.show()
axRetorno = plt.gca()
axRetorno.set_title('Tiempos de Retorno')
axRetorno.set_ylabel('Promedio Tiempos de retorno')
dataframeTiemposRetorno.plot(kind='line', x=0, y=1, ax=axRetorno, label="FCFS")
dataframeTiemposRetorno.plot(kind='line', x=0, y=2, color='red', ax=axRetorno, label="SJF")
dataframeTiemposRetorno.plot(kind='line', x=0, y=3, color='green', ax=axRetorno, label="RR1")
dataframeTiemposRetorno.plot(kind='line', x=0, y=4, color='yellow', ax=axRetorno, label="RR4")
axRetorno.set_xlabel('Tiempos de ráfaga')
plt.show()
axRetornoNormalizado = plt.gca()
axRetornoNormalizado.set_title('Tiempos de Retorno Normalizado')
axRetornoNormalizado.set_ylabel('Promedio Tiempos de retorno normalizado')
dataframeTiemposRetornoNormalizado.plot(kind='line', x=0, y=1, ax=axRetornoNormalizado, label="FCFS")
dataframeTiemposRetornoNormalizado.plot(kind='line', x=0, y=2, color='red', ax=axRetornoNormalizado, label="SJF")
dataframeTiemposRetornoNormalizado.plot(kind='line', x=0, y=3, color='green', ax=axRetornoNormalizado, label="RR1")
dataframeTiemposRetornoNormalizado.plot(kind='line', x=0, y=4, color='yellow', ax=axRetornoNormalizado, label="RR4")
axRetornoNormalizado.set_xlabel('Tiempos de ráfaga')
plt.show()



