# recursiveLeastSquares
Esta libreria implementa minimos cuadrados recursivos para identificar los parametros de un filtro IRR de la forma:

$$ y_n = - \sum_{k=1}^{\min(n,N)} a_k y_{n-k} + \sum_{k=0}^{\min(n,M)} b_k u_{n-k} $$ 

Ademas se incluye una libreta en Mathematica que genera los archivos **dataInput.txt** y **dataOutput.txt** que corresponden a las "mediciones" de la entrada y salida del sistema a identificar que son usadas en el archivo **main.cpp**, este a su vez genera el historial de la identificacion de parametros almacenado en **estimatedParams.txt** archivo usado en la libreta Mathematica para ser graficados y comparar el modelo "real" contra el modelo estimado. A continuación el modelo real $G$ y el estimado $\widehat{G}$, 

$$ G(z^{-1}) = \frac{1 - 3 z^{-1} + 0.2 z^{-2}}{1 - 0.9 z^{-1} + 0.1 z^{-2}} $$ 

$$ \widehat{G} (z^{-1} ) = \frac{1.0492 -2.18383 z^{-1} - 2.4286 z^{-2}}{1 - 0.0316771 z^{-1} - 0.572705 z^{-2}} $$

En la grafica se muestra como se sobreponen las señales generados por ambos filtros para la misma señal de entrada

![image](https://github.com/jafetrd/recursiveLeastSquares/assets/20916745/87925dfb-5e6e-4e4c-a8f0-b0777b4ef83c)


### Ejecuta en linea 
<https://onlinegdb.com/YrTfwFJxB>

# Documentación
Para hacer uso hay que agregarla al proyecto con:
 ``` #include "estimationFilters.h" ```

 Se construye el estimador con 4 parametros y el vector $\widehat{\theta}$ 
 
 ```estimationFilters(N,M,lambda,gain,theta_hat);```
 
- N : numero de parámetros en el denominador a estimar
- M : numero de parámetros en el numerador a estimar
- lambda : Factor de olvido entre 0 y 1
- gain : ganancia inicial de la matriz de covarianza diagonal
- theta_hat : el arreglo que guarda los parametros estimados 

## Métodos
```C 
void _estimationRLS(double u, double y, double* theta_hat);
```
Asigna al array **theta_hat** los parametros estimados para la medicion de entrada **u** y salida **y** actual

# Ejemplo mínimo de uso

```C
#include "fractionalOrderFilter.h"
int main() {
    int L = cantidad de mediciones;    
    double u[L] = {mediciones entrada};
    double y[L] = {mediciones salida};    
    int M = Cantidad de coeficientes de numerador a estimar
    int N = Cantidad de coeficientes de denominador a estimar
    int lambda = 1; //sin olvido
    int gain = 100000;
    double theta_hat[M+N]; //Vector de parametros estimados
    estimationFilters RLS(N,M,lambda,gain,theta_hat);
    for(int i = 0; i < L;i++){
        RLS._estimationRLS(u[i],y[i],theta_hat); //Estimacion para cada muestra
    }
    return 0;
}
```

# Posibles problemas
Al ser una implementación "Vanilla" la matriz de covarianza puede crecer exponencialmente al no estar acotada y el vector de Ganancia no está condicionado, por lo que no puede estimar donde existan cambios bruscos o donde la señal sea constante para un largo periodo de tiempo.  

# Recomendaciones 
Hacer uso de una señal en la entrada que cumpla la condición de excitación persistente (en la practica una señal con varios armónicos). 
Si se trata de un sistema lineal variante en el tiempo usar un valor menor a uno para que el pasado tenga menos importancia.
El valor de la ganancia puede ser pequeño (ej. 1, 10, 50) si se cuenta con una gran cantidad de datos, si son pocos hacer uso de valores mas grandes (1000,10000,1000000) para acelerar la convergencia. 

# Contribuciones
Las contribuciones son bienvenidas. Por favor, abre un issue o envía un pull request para contribuir al desarrollo de esta librería.

# Bibliografia


## Requisitos

- C++11 o superior

## Instalación

Para utilizar esta librería, simplemente clona el repositorio y compila el archivo `main.cpp`.

```bash
git clone [https://github.com/jafetrd/recursiveLeastSquares]
cd recursiveLeastSquares
g++ -std=c++11 main.cpp -o main

