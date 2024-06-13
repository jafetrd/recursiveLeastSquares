#ifndef ESTIMATION_FILTERS_H
#define ESTIMATION_FILTERS_H

struct _configRLS {
    int _M;
    int _N;
    int _MN;
    int _MNt;
    double _y_hat; 
    double _lambda; 
    double _inv_lambda;
    double* _psi; 
    double* _P;
};

class estimationFilters {
 public:
    estimationFilters(int M, int N, double lambda, double Gain, double* theta_hat);
    void _estimationRLS(double u, double y, double* theta_hat);
    
 private:
    _configRLS _RLS;
};

#endif
