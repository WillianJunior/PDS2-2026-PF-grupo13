#include "Motor.hpp"
#include "Sistema.hpp"

Motor::Motor(int id, std::string desc, double velocidade, double torque) : Equipamento(int id, std::string desc) {
    Parametro vel_nom(velocidade, "velocidade nominal do motor", id+1);
    Parametro tor_nom(torque, "torque nominal do motor", id+2);

    this->_Parametros.push_back(vel_nom);
    this->_Parametros.push_back(torque_nom);
}