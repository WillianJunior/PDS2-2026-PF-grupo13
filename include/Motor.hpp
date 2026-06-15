#ifndef MOTOR_HPP
#define MOTOR_HPP

#include "Equipamento.hpp"

class Motor : public Equipamento {
    private:
        
    public:
        Motor(int id, std::string desc, double velocidade, double torque);
        ~Motor();
};

#endif