#ifndef JATO_H
#define JATO_H

#include "Resultado.h"
#include <utility>

class Jato {
private:
    int id;
    double parametro_a;
    std::pair<double, double> isolamento;
    Resultado resultado_bisseccao;
    Resultado resultado_posicao_falsa;
    Resultado resultado_newton_raphson;

public:
    Jato(int identificador, double a);
    
    int getId() const;
    double getParametroA() const;
    std::pair<double, double> getIsolamento() const;
    
    Resultado getResultadoBisseccao() const;
    Resultado getResultadoPosicaoFalsa() const;
    Resultado getResultadoNewtonRaphson() const;
    
    void setIsolamento(std::pair<double, double> isol);
    void setResultadoBisseccao(Resultado res);
    void setResultadoPosicaoFalsa(Resultado res);
    void setResultadoNewtonRaphson(Resultado res);
    
    bool isSeguro() const;
};

#endif // JATO_H

