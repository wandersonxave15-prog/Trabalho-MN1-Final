#include "FuncaoJato.h"
#include <cmath>

FuncaoJato::FuncaoJato(double parametro_a) : a(parametro_a) {}

double FuncaoJato::calcular(double d) const {
    if (d <= 0) return NAN; // ln(d) não está definido para d <= 0
    return a * d - d * log(d);
}

double FuncaoJato::calcularDerivada(double d) const {
    if (d <= 0) return NAN;
    return a - log(d) - 1;
}

double FuncaoJato::getParametroA() const {
    return a;
}

void FuncaoJato::setParametroA(double novo_a) {
    a = novo_a;
}

