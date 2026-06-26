#include "Motor.hpp"

Motor::Motor(int id, std::string desc, double velocidade, double torque)
    : Equipamento(id, desc, "Motor") {
    AdicionarParametro(velocidade, "Velocidade nominal (rpm)");
    AdicionarParametro(torque, "Torque (Nm)");
}

std::string Motor::Tipo() const {
    return "Motor";
}
