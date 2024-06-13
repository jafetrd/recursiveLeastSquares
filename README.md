# recursiveLeastSquares
A vanilla implementation of recursive least squares to estimate the parameters of a IIR filter or ARX model 

Esta libreria implementa minimos cuadrados recursivos para identificar los parametros de un filtro IRR de la forma:

$$ y_n = - \sum_{k=1}^{\min(n,N)} a_k y_{n-k} + \sum_{k=0}^{\min(n,M)} b_k u_{n-k} $$ 

### Ejecuta en linea 
<https://onlinegdb.com/YrTfwFJxB>

# Documentación
Para hacer uso hay que agregarla al proyecto con:
 ``` #include "estimationFilters.h" ```

 Se construye el estimador con 3 parametros
 ```estimationFilters(N,M,lambda,gain,theta_hat);```
 
- N : numero de parametros en el denominador a estimar
- M : numero de parametros en el numerador a estimar
- lambda : Factor de olvido entre 0 y 1
- gain : ganancia inicial de la matriz de covarianza diagonal
- theta_hat : el arreglo que guarda los parametros estimados 

## Métodos
```C 
void _estimationRLS(double u, double y, double* theta_hat);
```
Asigna al array **theta_hat** los coeficientes identificados para cada medicion de entrada **u** y salida **y**

# Ejemplo minimo de uso

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



# Recomendaciones 


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

