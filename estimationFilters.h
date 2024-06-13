#ifndef ESTIMATION_FILTER_H
#define ESTIMATION_FILTER_H

struct _configRLS {
    int _M;
    int _N;
    int _MN;
    int _MNt;
    double _psi[_MN]; 
    double _P[_MNt]; 
    
    double _y_hat; 
    double _lambda; 
    double _inv_lambda;
}

class estimationFilter {
 public:
    estimationFilter(int M, int N, double lambda, double Gain, double* theta_hat);
    void _estimationRLS(double u, double y, double* theta_hat);
    
 private:
     _configRLS _cRLS;
};

#endif