#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

#include "Cargo.hpp"

class Usuario {
private:
    std::string _login;
    std::string _senha;
    Cargo _cargo;
public:
    Usuario(std::string login, std::string senha, Cargo cargo);

    bool ValidarSenha(std::string senha) const;

    std::string GetLogin() const;
    Cargo GetCargo (std::string login);
};

#endif