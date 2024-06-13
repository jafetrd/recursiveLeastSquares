#include "estimationFilters.h"
#include <algorithm>

estimationFilters::estimationFilters(int N,int M,double lambda,double Gain,double* theta_hat){
    _RLS._M = M;
    _RLS._N = N;
    _RLS._MN = M+N;
    _RLS._MNt = _RLS._MN * _RLS._MN;
    _RLS._y_hat = 0.0;
    _RLS._lambda = lambda;
    _RLS._inv_lambda = 1/lambda;
    _RLS._y_hat = 0.0;
    
    _RLS._psi = new double[_RLS._MN];
    _RLS._P = new double[_RLS._MNt];
    
    // Inicializar theta_hat, psi y matriz de covarianza P
    std::fill(theta_hat, theta_hat + _RLS._MN, 0.0);
    std::fill(_RLS._psi, _RLS._psi + _RLS._MN, 0.0);
    std::fill(_RLS._P, _RLS._P + _RLS._MNt, 0.0);
    for (int i = 0; i < _RLS._MN; i++) {
        _RLS._P[i * (_RLS._MN + 1)] = Gain;
    }
}

void estimationFilters::_estimationRLS(double _u_real, double _y_real,double* theta_hat){
        // Actualizar el vector regresor psi
        for (int i = _RLS._MN - 1; i > 0; i--) {
            _RLS._psi[i] = _RLS._psi[i - 1];
        }
        _RLS._psi[_RLS._N] = _u_real;
        _RLS._psi[0] = -_RLS._y_hat;
        
        // estimar filtro ARX - IIR
        _RLS._y_hat = 0.0;
        for (int k = 0; k <= _RLS._MN; k++) {
            _RLS._y_hat += theta_hat[k] * _RLS._psi[k];
        }
        
        // Cálculo del residuo
        double error = _y_real - _RLS._y_hat;

        double W[_RLS._MN];
        for (int i = 0; i <_RLS._MN; i++) {
            double sum = 0.0;
            for (int j = 0; j <_RLS._MN; j++) {
                sum += _RLS._P[i * _RLS._MN + j] * _RLS._psi[j];
            }
            W[i] = sum;
        }

        double den = _RLS._lambda;
        for (int i = 0; i <_RLS._MN; i++) {
            den += _RLS._psi[i] * W[i];
        } 
        
        // Actualizar el vector de ganancia
        double inv_den = 1.0 / den;
        double gain[_RLS._MN];
        for (int i = 0; i < _RLS._MN; i++) {
            gain[i] = W[i] * inv_den;
        }
        
        // Actualizar la estimación del vector de parámetros 
        for (int i = 0; i < _RLS._MN; i++) {
            theta_hat[i] += gain[i] * error;
        }

        // Actualizar la matriz de covarianza
        for (int i = 0; i < _RLS._MN; i++) {
            for (int j = 0; j < _RLS._MN; j++) {
                _RLS._P[i * _RLS._MN + j] += - W[i] * W[j] * inv_den * _RLS._inv_lambda;
            }
        }
}
