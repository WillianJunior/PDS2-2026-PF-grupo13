#ifndef DEPENDENCIA_HPP
#define DEPENDENCIA_HPP

#include "EstadoOperacional.hpp"

class Dependencia {
private:
    int _id;
    EstadoOperacional _condicao;
    EstadoOperacional _resultado;

public:
    Dependencia(int id, EstadoOperacional condicao, EstadoOperacional resultado);

    int Get_Id ();
    EstadoOperacional Get_Condicao ();
    EstadoOperacional Get_Resultado ();

};

#endif