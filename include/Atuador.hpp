#ifndef ATUADOR_HPP
#define ATUADOR_HPP

#include "Equipamento.hpp"

class Atuador : public Equipamento {
private:

public:
    Atuador(int id, std::string desc, double retorno);
    ~Atuador();
};

#endif