#include "fractionalOrderFilter.h"
#include "estimationFilters.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

// Funcion para abrir datos medidos y almacenados en un txt 
void _abrirDatos(const std::string& filename, double* arreglo, int L){
    // Open the file
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Unable to open file";
        delete[] arreglo; // Clean up memory if allocation was successful
        return; // Return error code
    }

    // Read the file content into a string
    std::string line;
    std::getline(infile, line);
    infile.close();

    // Use a stringstream to parse the data
    std::stringstream ss(line);

    // Read the values into the array
    for (int i = 0; i < L; ++i) {
        if (!(ss >> arreglo[i])) {
            std::cerr << "Error reading double at index " << i << std::endl;
            delete[] arreglo; // Clean up memory
            return; // Return error code
        }
    }
}

int main() {   
    int L = 500; // Cantidad de medicion a usar
    _abrirDatos("dataInput.txt", u, L); // Archivo con mediciones de entrada
    _abrirDatos("dataOutput.txt", y, L); // Archivo con mediciones de salida
    std::ofstream outFile("datos.txt"); // Crear y abrir un archivo de texto
    
    double u[L];
    double y[L];
        
    int M = 3; // Cantidad de coeficientes de numerador a estimar
    int N = 2; // Cantidad de coeficientes de denominador a estimar
    double lambda = 1.0; // Factor de olvido
    double gain = 100000; // Ganancia inicial de matriz de covarianza
  
    double theta_hat[M+N]; //Vector de parametros estimados
    
    estimationFilters RLS(N,M,lambda,gain,theta_hat); //Crear objeto
    
    for(int i = 0; i < L;i++){
        RLS._estimationRLS(u[i],y[i],theta_hat); 

      //Guardar cada estimacion para verla en Mathematica
        for (int i = 0; i < M+N-1; i++) {
            outFile << std::fixed << std::setprecision(15) << theta_hat[i] << ",";
        }
        outFile << std::fixed << std::setprecision(15) << theta_hat[M+N-1] << "\n";
    }
    
    outFile.close();
    return 0;
}
