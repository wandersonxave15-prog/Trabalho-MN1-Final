#ifndef BISSECCAO_H
#define BISSECCAO_H

#include "Resultado.h"
#include "FuncaoJato.h"

class Bisseccao {
private:
    FuncaoJato* funcao;
    double epsilon;
    static const int MAX_ITERACOES = 1000;

public:
    Bisseccao(FuncaoJato* f, double eps);
    Resultado calcular(double a0, double b0);
};

#endif // BISSECCAO_H
