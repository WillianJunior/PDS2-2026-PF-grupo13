#include "Dependencia.hpp"

Dependencia::Dependencia(int id, EstadoOperacional condicao, EstadoOperacional resultado){
    this->_id = id;
    this->_condicao = entrada;
    this->_resultado = saida;
}

EstadoOperacional Dependencia::Get_Resultado () {
    return this->_resultado;
}

EstadoOperacional Dependencia::Get_Condicao () {
    return this->_condicao;
}

int Dependencia::Get_Id (){
    return this->_id;
}