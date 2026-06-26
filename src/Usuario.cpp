#include "Usuario.hpp"
#include "Excecoes.hpp"

Usuario::Usuario(std::string login, std::string senha, Cargo cargo) {
    if (login.empty()) {
        throw EntradaInvalida("login vazio");
    }
    if (senha.empty()) {
        throw EntradaInvalida("senha em branco");
    }
    this->_login = login;
    this->_senha = senha;
    this->_cargo = cargo;
}

bool Usuario::ValidarSenha(std::string senha) const {
    return senha == _senha;
}

std::string Usuario::GetLogin() const {
    return _login;
}

Cargo Usuario::GetCargo(std::string login) {
    (void)login;
    return _cargo;
}

Cargo Usuario::GetCargo() const { return _cargo; }

std::string Usuario::GetSenha() const { return _senha; }
