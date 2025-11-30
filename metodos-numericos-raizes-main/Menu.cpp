#include "Menu.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <termios.h>
#include <unistd.h>

Menu::Menu() {
    selecao = 0;
    rodando = true;
    sistema = nullptr;
    opcoes.push_back("1. Executar Teste Padrao");
    opcoes.push_back("2. Configurar Jatos");
    opcoes.push_back("3. Listar Jatos Configurados");
    opcoes.push_back("4. Exibir Quadro Resposta");
    opcoes.push_back("5. Exibir Quadro Comparativo");
    opcoes.push_back("6. Analise da Variacao de 'a'");
    opcoes.push_back("7. Verificacao de Seguranca");
    opcoes.push_back("8. Sair");
}

void Menu::setSistema(SistemaJatos* s) {
    sistema = s;
}

void Menu::limparTela() {
    std::cout << "\033[2J\033[H";
}

void Menu::mostrarMenu() {
    limparTela();
    std::cout << "=== SISTEMA DE CALCULO DE DESLOCAMENTO DE JATO SUPERSONICO ===" << std::endl;
    std::cout << std::endl;
    std::cout << "Use as setas para navegar, ENTER para selecionar, ESC para sair" << std::endl;
    std::cout << std::endl;
    
    for (int i = 0; i < (int)opcoes.size(); i++) {
        if (i == selecao) {
            std::cout << "> " << opcoes[i] << std::endl;
        } else {
            std::cout << "  " << opcoes[i] << std::endl;
        }
    }
    std::cout << std::endl;
}

int Menu::lerTecla() {
    struct termios antigo, novo;
    int tecla;
    
    tcgetattr(STDIN_FILENO, &antigo);
    novo = antigo;
    novo.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &novo);
    
    tecla = getchar();
    
    if (tecla == 27) {
        tecla = getchar();
        if (tecla == 91) {
            tecla = getchar();
            tcsetattr(STDIN_FILENO, TCSANOW, &antigo);
            if (tecla == 65) return 1;
            if (tecla == 66) return 2;
        } else {
            tcsetattr(STDIN_FILENO, TCSANOW, &antigo);
            return 6;
        }
    }
    
    tcsetattr(STDIN_FILENO, TCSANOW, &antigo);
    
    if (tecla == 10 || tecla == 13) {
        return 5;
    }
    
    return 0;
}

void Menu::processarTecla() {
    int tecla = lerTecla();
    
    if (tecla == 1) {
        selecao--;
        if (selecao < 0) selecao = opcoes.size() - 1;
    }
    if (tecla == 2) {
        selecao++;
        if (selecao >= (int)opcoes.size()) selecao = 0;
    }
    if (tecla == 5) {
        executarOpcao();
    }
    if (tecla == 6) {
        sair();
    }
}

void Menu::executarOpcao() {
    limparTela();
    
    if (selecao == 0) testePadrao();
    else if (selecao == 1) configurarJatos();
    else if (selecao == 2) listarJatos();
    else if (selecao == 3) quadroResposta();
    else if (selecao == 4) quadroComparativo();
    else if (selecao == 5) analiseVariacao();
    else if (selecao == 6) verificacaoSeguranca();
    else if (selecao == 7) {
        sair();
        return;
    }
    
    std::cout << std::endl;
    std::cout << "Pressione ENTER para voltar ao menu...";
    std::cin.ignore();
    std::cin.get();
}

void Menu::testePadrao() {
    if (sistema) {
        sistema->executarTestePadrao();
    }
}

void Menu::configurarJatos() {
    if (!sistema) return;
    
    std::cout << "=== CONFIGURACAO DE JATOS ===" << std::endl;
    
    int n;
    double epsilon;
    
    std::cout << "\nDigite o numero de jatos: ";
    std::cin >> n;
    
    if (n <= 0) {
        std::cout << "Numero invalido!" << std::endl;
        return;
    }
    
    std::cout << "Digite a precisao (epsilon): ";
    std::cin >> epsilon;
    
    if (epsilon <= 0) {
        std::cout << "Epsilon invalido!" << std::endl;
        return;
    }
    
    sistema->limparJatos();
    sistema->setEpsilon(epsilon);
    
    std::cout << "\nDigite os valores de 'a' para cada jato:" << std::endl;
    for (int i = 0; i < n; i++) {
        double a;
        std::cout << "Jato " << (i + 1) << ": ";
        std::cin >> a;
        sistema->adicionarJato(a);
    }
    
    std::cout << "\nProcessando jatos..." << std::endl;
    sistema->processarJatos();
    
    std::cout << "\n" << n << " jato(s) configurado(s)!" << std::endl;
}

void Menu::listarJatos() {
    if (!sistema) return;
    
    std::vector<Jato> jatos = sistema->getJatos();
    
    if (jatos.empty()) {
        std::cout << "Nenhum jato configurado." << std::endl;
        return;
    }
    
    std::cout << "=== JATOS CONFIGURADOS ===" << std::endl;
    std::cout << "\nTotal: " << jatos.size() << std::endl;
    std::cout << "\nJato\tParametro 'a'" << std::endl;
    std::cout << "------------------------" << std::endl;
    
    for (int i = 0; i < (int)jatos.size(); i++) {
        std::cout << jatos[i].getId() << "\t" << std::fixed << std::setprecision(6) 
                  << jatos[i].getParametroA() << std::endl;
    }
}

void Menu::quadroResposta() {
    if (!sistema) return;
    if (sistema->getJatos().empty()) {
        std::cout << "Configure os jatos primeiro." << std::endl;
        return;
    }
    sistema->exibirQuadroResposta();
}

void Menu::quadroComparativo() {
    if (!sistema) return;
    if (sistema->getJatos().empty()) {
        std::cout << "Configure os jatos primeiro." << std::endl;
        return;
    }
    sistema->exibirQuadroComparativo();
}

void Menu::analiseVariacao() {
    if (!sistema) return;
    if (sistema->getJatos().empty()) {
        std::cout << "Configure os jatos primeiro." << std::endl;
        return;
    }
    sistema->exibirAnaliseVariacaoA();
}

void Menu::verificacaoSeguranca() {
    if (!sistema) return;
    if (sistema->getJatos().empty()) {
        std::cout << "Configure os jatos primeiro." << std::endl;
        return;
    }
    sistema->exibirVerificacaoSeguranca();
}

void Menu::sair() {
    limparTela();
    std::cout << "Encerrando..." << std::endl;
    rodando = false;
}

void Menu::executar() {
    while (rodando) {
        mostrarMenu();
        processarTecla();
    }
}

