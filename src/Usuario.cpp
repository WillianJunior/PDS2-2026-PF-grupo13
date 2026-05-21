#include "Usuario.hpp"

Usuario::Usuario(std::string login, std::string senha, Cargo cargo) {}

bool Usuario::ValidarSenha(std::string senha) const { return false; }

std::string Usuario::GetLogin() const { return ""; }

Cargo Usuario::GetCargo(std::string login) { return Cargo::ADMIN; }
