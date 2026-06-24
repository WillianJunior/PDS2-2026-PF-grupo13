#ifndef ATUADOR_HPP
#define ATUADOR_HPP

#include "Equipamento.hpp"

class Atuador : public Equipamento {
public:
    Atuador(int id, std::string desc, double retorno);
    ~Atuador() override = default;

    std::string Tipo() const override;
};

#endif