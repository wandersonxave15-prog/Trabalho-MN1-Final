#include "SistemaJatos.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>

SistemaJatos::SistemaJatos(double eps) : epsilon(eps) {}

void SistemaJatos::adicionarJato(double a) {
    int id = jatos.size() + 1;
    jatos.push_back(Jato(id, a));
}

void SistemaJatos::limparJatos() {
    jatos.clear();
}

void SistemaJatos::setEpsilon(double eps) {
    epsilon = eps;
}

std::pair<double, double> SistemaJatos::encontrarIsolamento(FuncaoJato* funcao) {
    double a = funcao->getParametroA();
    double raiz_teorica = exp(a);
    
    double a0 = std::max(0.1, raiz_teorica - 1.0);
    double b0 = raiz_teorica + 1.0;
    
    while (funcao->calcular(a0) * funcao->calcular(b0) > 0 && a0 > 0.01) {
        a0 = a0 / 2.0;
        b0 = b0 * 1.5;
    }
    
    return std::make_pair(a0, b0);
}

void SistemaJatos::processarJatos() {
    for (auto& jato : jatos) {
        FuncaoJato funcao(jato.getParametroA());
        
        std::pair<double, double> isol = encontrarIsolamento(&funcao);
        jato.setIsolamento(isol);
        
        Bisseccao bisseccao(&funcao, epsilon);
        PosicaoFalsa posicaoFalsa(&funcao, epsilon);
        NewtonRaphson newtonRaphson(&funcao, epsilon);
        
        Resultado res_bis = bisseccao.calcular(isol.first, isol.second);
        Resultado res_pf = posicaoFalsa.calcular(isol.first, isol.second);
        Resultado res_nr = newtonRaphson.calcular(isol.first, isol.second);
        
        jato.setResultadoBisseccao(res_bis);
        jato.setResultadoPosicaoFalsa(res_pf);
        jato.setResultadoNewtonRaphson(res_nr);
    }
}

void SistemaJatos::executarTestePadrao() {
    std::cout << "\n=== TESTE PADRAO (Questão d) ===" << std::endl;
    std::cout << "a = 1, isolamento = (2, 3), epsilon = 1E-5" << std::endl;
    

    double epsilon_teste = 0.00001;
    
    FuncaoJato funcao(1.0);
    Bisseccao bisseccao(&funcao, epsilon_teste);
    PosicaoFalsa posicaoFalsa(&funcao, epsilon_teste);
    NewtonRaphson newtonRaphson(&funcao, epsilon_teste);
    
    Resultado res_bis = bisseccao.calcular(2.0, 3.0);
    Resultado res_pf = posicaoFalsa.calcular(2.0, 3.0);
    Resultado res_nr = newtonRaphson.calcular(2.5);
    
    std::cout << "\nResultados do teste padrao:" << std::endl;
    std::cout << "Bissecção:    d = " << std::fixed << std::setprecision(10) << res_bis.getRaiz() 
         << ", erro = " << std::scientific << res_bis.getErro() 
         << ", iteracoes = " << res_bis.getIteracoes() << std::endl;
    std::cout << "Posição Falsa: d = " << std::fixed << std::setprecision(10) << res_pf.getRaiz() 
         << ", erro = " << std::scientific << res_pf.getErro() 
         << ", iteracoes = " << res_pf.getIteracoes() << std::endl;
    std::cout << "Newton-Raphson: d = " << std::fixed << std::setprecision(10) << res_nr.getRaiz() 
         << ", erro = " << std::scientific << res_nr.getErro() 
         << ", iteracoes = " << res_nr.getIteracoes() << std::endl;
}

void SistemaJatos::exibirQuadroResposta() {
    std::cout << "\n\n=== QUADRO RESPOSTA ===" << std::endl;
    std::cout << std::setw(8) << "Jato" << std::setw(12) << "a" 
         << std::setw(20) << "d (Bissecção)" << std::setw(15) << "Erro (Bis)" 
         << std::setw(20) << "d (Pos. Falsa)" << std::setw(15) << "Erro (PF)"
         << std::setw(20) << "d (N-R)" << std::setw(15) << "Erro (N-R)" << std::endl;
    std::cout << std::string(135, '-') << std::endl;
    
    for (const auto& jato : jatos) {
        std::cout << std::setw(8) << jato.getId() 
             << std::setw(12) << std::fixed << std::setprecision(4) << jato.getParametroA();
        
        Resultado res_bis = jato.getResultadoBisseccao();
        if (res_bis.getConvergiu()) {
            std::cout << std::setw(20) << std::setprecision(10) << res_bis.getRaiz()
                 << std::setw(15) << std::scientific << std::setprecision(4) << res_bis.getErro();
        } else {
            std::cout << std::setw(20) << "N/A" << std::setw(15) << "N/A";
        }
        
        Resultado res_pf = jato.getResultadoPosicaoFalsa();
        if (res_pf.getConvergiu()) {
            std::cout << std::setw(20) << std::fixed << std::setprecision(10) << res_pf.getRaiz()
                 << std::setw(15) << std::scientific << std::setprecision(4) << res_pf.getErro();
        } else {
            std::cout << std::setw(20) << "N/A" << std::setw(15) << "N/A";
        }
        
        Resultado res_nr = jato.getResultadoNewtonRaphson();
        if (res_nr.getConvergiu()) {
            std::cout << std::setw(20) << std::fixed << std::setprecision(10) << res_nr.getRaiz()
                 << std::setw(15) << std::scientific << std::setprecision(4) << res_nr.getErro();
        } else {
            std::cout << std::setw(20) << "N/A" << std::setw(15) << "N/A";
        }
        
        std::cout << std::endl;
    }
}

void SistemaJatos::exibirQuadroComparativo() {
    std::cout << "\n\n=== QUADRO COMPARATIVO ===" << std::endl;
    std::cout << std::setw(8) << "Jato" << std::setw(12) << "a" 
         << std::setw(20) << "Isolamento" 
         << std::setw(15) << "Iter. (Bis)" << std::setw(15) << "Iter. (PF)" << std::setw(15) << "Iter. (N-R)"
         << std::setw(20) << "Raiz (Bis)" << std::setw(20) << "Raiz (PF)" << std::setw(20) << "Raiz (N-R)" << std::endl;
    std::cout << std::string(145, '-') << std::endl;
    
    for (const auto& jato : jatos) {
        std::pair<double, double> isol = jato.getIsolamento();
        
        std::cout << std::setw(8) << jato.getId() 
             << std::setw(12) << std::fixed << std::setprecision(4) << jato.getParametroA();
        std::cout << std::setw(10) << "(" << std::setprecision(4) << isol.first << ", " 
             << std::setprecision(4) << isol.second << ")";
        
        Resultado res_bis = jato.getResultadoBisseccao();
        Resultado res_pf = jato.getResultadoPosicaoFalsa();
        Resultado res_nr = jato.getResultadoNewtonRaphson();
        
        std::cout << std::setw(15) << res_bis.getIteracoes()
             << std::setw(15) << res_pf.getIteracoes()
             << std::setw(15) << res_nr.getIteracoes();
        
        std::cout << std::setw(20) << std::setprecision(10) << res_bis.getRaiz()
             << std::setw(20) << std::setprecision(10) << res_pf.getRaiz()
             << std::setw(20) << std::setprecision(10) << res_nr.getRaiz();
        
        std::cout << std::endl;
    }
}

void SistemaJatos::exibirAnaliseVariacaoA() {
    std::cout << "\n\n=== ANALISE DO EFEITO DA VARIACAO DE 'a' ===" << std::endl;
    std::cout << "\nPara cada metodo, observa-se:" << std::endl;
    
    std::cout << "\n1. BISSECCAO:" << std::endl;
    std::cout << "   - Numero de iteracoes: ";
    bool primeira = true;
    for (const auto& jato : jatos) {
        if (!primeira) std::cout << ", ";
        std::cout << "Jato " << jato.getId() << " = " << jato.getResultadoBisseccao().getIteracoes();
        primeira = false;
    }
    
    std::cout << "\n   - Raizes encontradas: ";
    primeira = true;
    for (const auto& jato : jatos) {
        if (!primeira) std::cout << ", ";
        std::cout << "Jato " << jato.getId() << " = " << std::fixed << std::setprecision(10) 
             << jato.getResultadoBisseccao().getRaiz();
        primeira = false;
    }
    
    std::cout << "\n\n2. POSICAO FALSA:" << std::endl;
    std::cout << "   - Numero de iteracoes: ";
    primeira = true;
    for (const auto& jato : jatos) {
        if (!primeira) std::cout << ", ";
        std::cout << "Jato " << jato.getId() << " = " << jato.getResultadoPosicaoFalsa().getIteracoes();
        primeira = false;
    }
    
    std::cout << "\n   - Raizes encontradas: ";
    primeira = true;
    for (const auto& jato : jatos) {
        if (!primeira) std::cout << ", ";
        std::cout << "Jato " << jato.getId() << " = " << std::fixed << std::setprecision(10) 
             << jato.getResultadoPosicaoFalsa().getRaiz();
        primeira = false;
    }
    
    std::cout << "\n\n3. NEWTON-RAPHSON:" << std::endl;
    std::cout << "   - Numero de iteracoes: ";
    primeira = true;
    for (const auto& jato : jatos) {
        if (!primeira) std::cout << ", ";
        std::cout << "Jato " << jato.getId() << " = " << jato.getResultadoNewtonRaphson().getIteracoes();
        primeira = false;
    }
    
    std::cout << "\n   - Raizes encontradas: ";
    primeira = true;
    for (const auto& jato : jatos) {
        if (!primeira) std::cout << ", ";
        std::cout << "Jato " << jato.getId() << " = " << std::fixed << std::setprecision(10) 
             << jato.getResultadoNewtonRaphson().getRaiz();
        primeira = false;
    }
}

void SistemaJatos::exibirVerificacaoSeguranca() {
    std::cout << "\n\n=== VERIFICACAO DE SEGURANCA ===" << std::endl;
    std::cout << "ATENCAO: Se d > 2 cm, o jato explodira!" << std::endl;
    
    for (const auto& jato : jatos) {
        std::cout << "\nJato " << jato.getId() << " (a = " << std::fixed << std::setprecision(4) 
             << jato.getParametroA() << "):" << std::endl;
        
        Resultado res_bis = jato.getResultadoBisseccao();
        Resultado res_pf = jato.getResultadoPosicaoFalsa();
        Resultado res_nr = jato.getResultadoNewtonRaphson();
        
        std::cout << "  Bissecção:    d = " << std::setprecision(10) << res_bis.getRaiz();
        if (res_bis.getRaiz() > 2.0) {
            std::cout << " [PERIGO - EXPLOSAO!]";
        } else {
            std::cout << " [SEGURO]";
        }
        std::cout << std::endl;
        
        std::cout << "  Posição Falsa: d = " << res_pf.getRaiz();
        if (res_pf.getRaiz() > 2.0) {
            std::cout << " [PERIGO - EXPLOSAO!]";
        } else {
            std::cout << " [SEGURO]";
        }
        std::cout << std::endl;
        
        std::cout << "  Newton-Raphson: d = " << res_nr.getRaiz();
        if (res_nr.getRaiz() > 2.0) {
            std::cout << " [PERIGO - EXPLOSAO!]";
        } else {
            std::cout << " [SEGURO]";
        }
        std::cout << std::endl;
    }
}

std::vector<Jato> SistemaJatos::getJatos() const {
    return jatos;
}

