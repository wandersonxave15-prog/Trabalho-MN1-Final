#ifndef NEWTONRAPHSON_H
#define NEWTONRAPHSON_H

#include "Resultado.h"
#include "FuncaoJato.h"

class NewtonRaphson {
private:
    FuncaoJato* funcao;
    double epsilon;
    static const int MAX_ITERACOES = 1000;

public:
    NewtonRaphson(FuncaoJato* f, double eps);
    Resultado calcular(double a0, double b0);
    Resultado calcular(double x0);
};

#endif // NEWTONRAPHSON_H
