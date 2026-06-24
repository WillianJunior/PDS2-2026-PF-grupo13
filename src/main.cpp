#include "Sistema.hpp"
#include <iostream>

int main(int argc, char const *argv[]) {
    std::cout << "Sistema de monitoramento de fábricas" << std::endl;

    std::string comando = "";
    bool continuar = true;
    while (continuar) {
        std::cout << "O que deseja fazer:" << std::endl;
        std::cout << "1 - Adicionar elemento" << std::endl;
        std::cout << "2 - Remover elemento" << std::endl;
        std::cout << "3 - Visualizar elementos" << std::endl;
        std::cout << "4 - Executar diagnóstico" << std::endl;
        std::cout << "5 - Salvar Alterações" << std::endl;
        std::cout << "6 - Carregar Alterações" << std::endl;
        std::cout << "0 - Finalizar" << std::endl;

        std::cin >> comando;

        if (comando == "0"){
            continuar = false;
        } else if (comando == "1") {
            /* code */
        } else if (comando == "2") {
            /* code */
        } else if (comando == "3") {
            /* code */
        } else if (comando == "4") {
            /* code */
        } else if (comando == "5") {
            /* code */
        } else if (comando == "6") {
            /* code */
        }
        
    }
    
    std::cout << "Fim" << std::endl;
    
    return 0;
}