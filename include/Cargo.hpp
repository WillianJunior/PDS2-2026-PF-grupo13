#ifndef CARGO_HPP
#define CARGO_HPP

/**
 * @brief Níveis de acesso dos usuários do sistema.
 *
 * - ADMIN:      Gerencia usuários e a estrutura completa do sistema.
 * - ENGENHEIRO: Configura linhas, conjuntos e equipamentos.
 * - TECNICO:    Visualiza dados e alarmes.
 */
enum class Cargo {
    ADMIN,
    ENGENHEIRO,
    TECNICO
};

#endif
