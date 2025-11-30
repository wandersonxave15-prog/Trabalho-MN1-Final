#include "NewtonRaphson.h"
#include <cmath>

NewtonRaphson::NewtonRaphson(FuncaoJato* f, double eps) : funcao(f), epsilon(eps) {}

Resultado NewtonRaphson::calcular(double a0, double b0) {
    double x0 = (a0 + b0) / 2.0;
    return calcular(x0);
}

Resultado NewtonRaphson::calcular(double x0) {
    Resultado resultado;
    resultado.setConvergiu(false);
    resultado.setIteracoes(0);
    
    double x = x0;
    double x_ant;
    
    for (int i = 0; i < MAX_ITERACOES; i++) {
        double fx = funcao->calcular(x);
        double dfx = funcao->calcularDerivada(x);
        
        if (abs(dfx) < 1e-10) {
            resultado.setRaiz(NAN);
            resultado.setErro(NAN);
            return resultado;
        }
        
        x_ant = x;
        x = x - fx / dfx;
        resultado.setIteracoes(resultado.getIteracoes() + 1);
        
        double erro_atual = abs(x - x_ant);
        resultado.setErro(erro_atual);
        
        if (erro_atual < epsilon || abs(fx) < epsilon) {
            resultado.setRaiz(x);
            resultado.setConvergiu(true);
            return resultado;
        }
    }
    
    resultado.setRaiz(x);
    return resultado;
}
