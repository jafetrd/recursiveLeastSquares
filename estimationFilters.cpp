#include "estimationFilters.h"
#include <algorithm>

estimationFilters::estimationFilters(int M,int N,double lambda,double Gain,double* theta_hat){
    _cRLS._M = M;
    _cRLS._N = N;
    _cRLS._MN = M+N;
    _cRLS._MNt = _cRLS._MN * _cRLS._MN;
    _cRLS._h_hat = 0.0;
    _cRLS._lambda = lambda;
    _cRLS._inv_lambda = 1/lambda;
    _cRLS._y_hat = 0.0;
    
    // Inicializar theta_hat y psi y matriz de covarianza P
    std::fill(theta_hat, theta_hat + _cRLS._MN, 0.0);
    std::fill(_cRLS._psi, _cRLS._psi + _cRLS._MN, 0.0);
    std::fill(_cRLS._P, _cRLS._P + _cRLS._MNt, 0.0);
    for (int i = 0; i < _cRLS._MN; i++) {
        _cRLS._P[i * (_cRLS._MN + 1)] = Gain;
    }
}

void estimationFilters::_estimationRLS(double u, double y,double* theta_hat){
        // Actualizar el vector regresor psi
        for (int i = _cRLS._MN - 1; i > 0; i--) {
            _cRLS._psi[i] = _cRLS._psi[i - 1];
        }
        _cRLS._psi[_cRLS.N] = u;
        _cRLS._psi[0] = -_cRLS._y_hat;
        
        // estimar filtro ARX - IIR
        _cRLS._y_hat = 0.0;
        for (int k = 0; k <= _cRLS._MN; k++) {
            _cRLS._y_hat += theta_hat[k] * _cRLS.psi[k];
        }
        
        // Cálculo del residuo
        double error = y - _cRLS._y_hat;

        double W[_cRLS._MN];
        for (int i = 0; i <_cRLS._MN; i++) {
            double sum = 0.0;
            for (int j = 0; j <_cRLS._MN; j++) {
                sum += _cRLS._P[i * _cRLS._MN + j] * _cRLS._psi[j];
            }
            W[i] = sum;
        }

        double den = _cRLS._lambda;
        for (int i = 0; i <MN; i++) {
            den += _cRLS._psi[i] * W[i];
        } 
        
        // Actualizar el vector de ganancia
        double inv_den = 1.0 / den;
        double gain[_cRLS._MN];
        for (int i = 0; i < _cRLS._MN; i++) {
            gain[i] = W[i] * inv_den;
        }
        
        // Actualizar la estimación del vector de parámetros 
        for (int i = 0; i < _cRLS._MN; i++) {
            theta_hat[i] += gain[i] * error;
        }

        // Actualizar la matriz de covarianza
        for (int i = 0; i < _cRLS._MN; i++) {
            for (int j = 0; j < _cRLS._MN; j++) {
                _cRLS._P[i * _cRLS._MN + j] += - W[i] * W[j] * inv_den * _cRLS._inv_lambda;
            }
        }
}