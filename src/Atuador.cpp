#include "Atuador.hpp"

Atuador::Atuador(int id, std::string desc, double retorno){
    Parametro ret (retorno, desc, id+1);

    this->_Parametros.push_back(ret);
}