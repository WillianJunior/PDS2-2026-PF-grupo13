#ifndef VALVULA_HPP
#define VALVULA_HPP

#include "Equipamento.hpp"

class Valvula : public Equipamento{
    private:
        
    public:
        Valvula(int id, std::string desc, double vazao);
        ~Valvula();
};

#endif 