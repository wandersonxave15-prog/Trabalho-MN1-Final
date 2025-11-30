#ifndef SISTEMAJATOS_H
#define SISTEMAJATOS_H

#include "Jato.h"
#include "FuncaoJato.h"
#include "Bisseccao.h"
#include "PosicaoFalsa.h"
#include "NewtonRaphson.h"
#include <vector>
#include <utility>

class SistemaJatos {
private:
    std::vector<Jato> jatos;
    double epsilon;
    
    static std::pair<double, double> encontrarIsolamento(FuncaoJato* funcao);
    
public:
    SistemaJatos(double eps);
    
    void adicionarJato(double a);
    void limparJatos();
    void setEpsilon(double eps);
    void processarJatos();
    void executarTestePadrao();
    void exibirQuadroResposta();
    void exibirQuadroComparativo();
    void exibirAnaliseVariacaoA();
    void exibirVerificacaoSeguranca();
    
    std::vector<Jato> getJatos() const;
};

#endif // SISTEMAJATOS_H

