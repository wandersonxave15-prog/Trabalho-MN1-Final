#include "Jato.h"
#include <cmath>

Jato::Jato(int identificador, double a) 
    : id(identificador), parametro_a(a) {}

int Jato::getId() const {
    return id;
}

double Jato::getParametroA() const {
    return parametro_a;
}

std::pair<double, double> Jato::getIsolamento() const {
    return isolamento;
}

Resultado Jato::getResultadoBisseccao() const {
    return resultado_bisseccao;
}

Resultado Jato::getResultadoPosicaoFalsa() const {
    return resultado_posicao_falsa;
}

Resultado Jato::getResultadoNewtonRaphson() const {
    return resultado_newton_raphson;
}

void Jato::setIsolamento(std::pair<double, double> isol) {
    isolamento = isol;
}

void Jato::setResultadoBisseccao(Resultado res) {
    resultado_bisseccao = res;
}

void Jato::setResultadoPosicaoFalsa(Resultado res) {
    resultado_posicao_falsa = res;
}

void Jato::setResultadoNewtonRaphson(Resultado res) {
    resultado_newton_raphson = res;
}

bool Jato::isSeguro() const {
    // Verifica se d > 2 cm (perigo de explosão)
    double d = resultado_bisseccao.getRaiz();
    return d <= 2.0 && !std::isnan(d);
}
