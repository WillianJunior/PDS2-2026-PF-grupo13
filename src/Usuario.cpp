#include "Usuario.hpp"

Usuario::Usuario(std::string login, std::string senha, Cargo cargo) {
    this->_login = login;
    this->_senha = senha;
    this->_cargo = cargo;
}

bool Usuario::ValidarSenha(std::string senha) const { 

    if (senha == this->_senha){
        return true;
    }
    return false;
}

std::string Usuario::GetLogin() const { 
    return this->_login; 
}

Cargo Usuario::GetCargo(std::string login) { 
    return this->_cargo; 
}
