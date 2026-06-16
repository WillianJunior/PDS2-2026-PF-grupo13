#include "Valvula.hpp"
#include "Sistema.hpp"

Valvula::Valvula(int id, std::string desc, double vazao) : Equipamento(int id, std::string desc){
    Parametro vaz(vazao, "vazão nominal da valvula", id+1);

    this->_Parametros.push_back(vaz);
}