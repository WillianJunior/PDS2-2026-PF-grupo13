#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

#include "Cargo.hpp"

/**
 * @brief Representa um usuário do sistema com credenciais e cargo.
 */
class Usuario {
private:
    std::string _login;
    std::string _senha;
    Cargo _cargo;
public:
    /**
     * @brief Constrói um usuário.
     * @param login Login de acesso.
     * @param senha Senha do usuário.
     * @param cargo Cargo/nível de acesso.
     */
    Usuario(std::string login, std::string senha, Cargo cargo);

    /**
     * @brief Verifica se a senha fornecida corresponde à senha do usuário.
     * @param senha Senha a validar.
     * @return true se a senha estiver correta.
     */
    bool ValidarSenha(std::string senha) const;

    /** @return Login do usuário. */
    std::string GetLogin() const;

    /**
     * @brief Retorna o cargo do usuário identificado pelo login.
     * @param login Login do usuário.
     * @return Cargo associado ao login.
     */
    Cargo GetCargo(std::string login);

    /** @return Cargo do usuário. */
    Cargo GetCargo() const;

    /** @return Senha do usuário (uso interno: persistência). */
    std::string GetSenha() const;
};

#endif
