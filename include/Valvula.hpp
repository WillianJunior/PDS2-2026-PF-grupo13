#ifndef VALVULA_HPP
#define VALVULA_HPP

#include "Equipamento.hpp"

class Valvula : public Equipamento{
    public:
        Valvula(int id, std::string desc, double vazao);
        ~Valvula() override = default;

        std::string Tipo() const override;
};

#endif 