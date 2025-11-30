#include "Resultado.h"
#include <cmath>

Resultado::Resultado() : raiz(NAN), erro(NAN), iteracoes(0), convergiu(false) {}

Resultado::Resultado(double r, double e, int it, bool conv) 
    : raiz(r), erro(e), iteracoes(it), convergiu(conv) {}

double Resultado::getRaiz() const {
    return raiz;
}

double Resultado::getErro() const {
    return erro;
}

int Resultado::getIteracoes() const {
    return iteracoes;
}

bool Resultado::getConvergiu() const {
    return convergiu;
}

void Resultado::setRaiz(double r) {
    raiz = r;
}

void Resultado::setErro(double e) {
    erro = e;
}

void Resultado::setIteracoes(int it) {
    iteracoes = it;
}

void Resultado::setConvergiu(bool conv) {
    convergiu = conv;
}

