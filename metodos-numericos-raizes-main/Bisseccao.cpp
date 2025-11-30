#include "Bisseccao.h"
#include <cmath>

Bisseccao::Bisseccao(FuncaoJato* f, double eps) : funcao(f), epsilon(eps) {}

Resultado Bisseccao::calcular(double a0, double b0) {
    Resultado resultado;
    resultado.setConvergiu(false);
    resultado.setIteracoes(0);
    
    double a_val = a0;
    double b_val = b0;
    double fa = funcao->calcular(a_val);
    double fb = funcao->calcular(b_val);

    if (fa == 0) {
        resultado.setRaiz(a_val);
        resultado.setConvergiu(true);
        return resultado;
    }
    if (fb == 0) {
        resultado.setRaiz(b_val);
        resultado.setConvergiu(true);
        return resultado;
    }
    
    if (fa * fb > 0) {
        resultado.setRaiz(NAN);
        resultado.setErro(NAN);
        return resultado;
    }
    
    double x;
    
    for (int i = 0; i < MAX_ITERACOES; i++) {
        x = (a_val + b_val) / 2.0;
        double fx = funcao->calcular(x);
        resultado.setIteracoes(resultado.getIteracoes() + 1);
        
        double erro_atual = std::abs(b_val - a_val) / 2.0;
        resultado.setErro(erro_atual);
        
        if (erro_atual < epsilon || std::abs(fx) < epsilon) {
            resultado.setRaiz(x);
            resultado.setConvergiu(true);
            return resultado;
        }
        
        if (fa * fx < 0) {
            b_val = x;
            fb = fx;
        } else {
            a_val = x;
            fa = fx;
        }
    }
    
    resultado.setRaiz(x);
    return resultado;
}
