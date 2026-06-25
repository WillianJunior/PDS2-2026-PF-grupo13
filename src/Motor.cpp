#include "Motor.hpp"

Motor::Motor(int id, std::string desc, double velocidade, double torque)
    : Equipamento(id, desc, "Motor") {
    this->AdicionarParametro(velocidade, "Velocidade nominal do motor");
    this->AdicionarParametro(torque, "Torque nominal do motor");
}

std::string Motor::Tipo() const { return "Motor"; }
