#include <iostream>
#include "SistemaJatos.h"
#include "Menu.h"

int main() {
    SistemaJatos sistema(1e-10);
    Menu menu;
    menu.setSistema(&sistema);
    menu.executar();
    return 0;
}
