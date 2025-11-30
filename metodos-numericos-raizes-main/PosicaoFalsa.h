#ifndef POSICAOFALSA_H
#define POSICAOFALSA_H

#include "Resultado.h"
#include "FuncaoJato.h"

class PosicaoFalsa {
private:
    FuncaoJato* funcao;
    double epsilon;
    static const int MAX_ITERACOES = 1000;

public:
    PosicaoFalsa(FuncaoJato* f, double eps);
    Resultado calcular(double a0, double b0);
};

#endif // POSICAOFALSA_H
