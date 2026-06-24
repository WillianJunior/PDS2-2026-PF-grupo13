#include "Usuario.hpp"
#include "Excecoes.hpp"

Usuario::Usuario(std::string login, std::string senha, Cargo cargo) {
    if (login.empty()) {
        throw EntradaInvalida("Usuario: login vazio");
    }
    if (senha.empty()) {
        throw EntradaInvalida("Usuario: senha vazia");
    }
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
    (void)login;
    return this->_cargo;
}

Cargo Usuario::GetCargo() const {
    return this->_cargo;
}

std::string Usuario::GetSenha() const {
    return this->_senha;
}
