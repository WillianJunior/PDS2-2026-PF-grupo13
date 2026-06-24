#ifndef MOTOR_HPP
#define MOTOR_HPP

#include "Equipamento.hpp"

class Motor : public Equipamento {
    public:
        Motor(int id, std::string desc, double velocidade, double torque);
        ~Motor() override = default;

        std::string Tipo() const override;
};

#endif