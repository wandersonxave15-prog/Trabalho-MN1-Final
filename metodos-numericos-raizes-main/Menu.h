#ifndef MENU_H
#define MENU_H

#include "SistemaJatos.h"
#include <vector>
#include <string>

class Menu {
private:
    std::vector<std::string> opcoes;
    int selecao;
    bool rodando;
    SistemaJatos* sistema;
    
    void limparTela();
    void mostrarMenu();
    int lerTecla();
    void processarTecla();
    void executarOpcao();
    
    void testePadrao();
    void configurarJatos();
    void listarJatos();
    void quadroResposta();
    void quadroComparativo();
    void analiseVariacao();
    void verificacaoSeguranca();
    void sair();
    
public:
    Menu();
    void executar();
    void setSistema(SistemaJatos* s);
};

#endif // MENU_H

