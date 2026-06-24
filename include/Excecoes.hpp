#ifndef EXCECOES_HPP
#define EXCECOES_HPP

#include <stdexcept>
#include <string>

/**
 * @brief Exceção base do sistema de monitoramento.
 *
 * Todas as exceções específicas do domínio herdam desta classe, permitindo
 * capturar qualquer erro do sistema com um único `catch (const ExcecaoSistema&)`.
 */
class ExcecaoSistema : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

/** @brief Entrada inválida (string vazia, argumento sem sentido). */
class EntradaInvalida : public ExcecaoSistema {
public:
    using ExcecaoSistema::ExcecaoSistema;
};

/** @brief Limites incoerentes (Max < Min). */
class LimitesInvalidos : public ExcecaoSistema {
public:
    using ExcecaoSistema::ExcecaoSistema;
};

/** @brief Identificador inválido (ex.: negativo). */
class IdInvalido : public ExcecaoSistema {
public:
    using ExcecaoSistema::ExcecaoSistema;
};

/** @brief Tentativa de inserir um identificador já existente. */
class IdDuplicado : public ExcecaoSistema {
public:
    using ExcecaoSistema::ExcecaoSistema;
};

/** @brief Acesso a um identificador inexistente. */
class IdInexistente : public ExcecaoSistema {
public:
    using ExcecaoSistema::ExcecaoSistema;
};

/** @brief Operação sem permissão para o cargo do usuário logado. */
class AcessoNegado : public ExcecaoSistema {
public:
    using ExcecaoSistema::ExcecaoSistema;
};

/** @brief Operação que exige sessão ativa sem usuário logado. */
class SessaoInvalida : public ExcecaoSistema {
public:
    using ExcecaoSistema::ExcecaoSistema;
};

#endif
