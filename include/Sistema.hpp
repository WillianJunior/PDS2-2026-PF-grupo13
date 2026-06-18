#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <vector>
#include <map>
#include <string>

#include "LinhaDeProducao.hpp"
#include "Usuario.hpp"
#include "Cargo.hpp"

/**
 * @brief Ponto de entrada central do sistema de monitoramento.
 *
 * Gerencia o conjunto de linhas de produção, os usuários cadastrados,
 * o controle de sessão (login/logout) e a persistência dos dados.
 */
class Sistema {
private:
    int _ProximoId;
    std::map<int,LinhaDeProducao> _Linhas;
    std::vector<Usuario> _Usuarios;
    std::vector<int> _IdsAtivos;

    Usuario* _UsuarioLogado;

    /** @brief Registra um ID como utilizado. @param Id ID a reservar. */
    void AdicionarId(int Id);

    /** @brief Libera um ID previamente reservado. @param Id ID a liberar. */
    void RemoverId(int Id);
public:
    /** @brief Inicializa o sistema sem linhas, usuários ou sessão ativa. */
    Sistema();

    /**
     * @brief Cadastra uma nova linha de produção.
     * @param id    Identificador único da linha.
     * @param desc  Descrição da linha.
     * @param local Localização física.
     * @param nome  Nome da linha.
     * @note Implementa US-001 (Criar Linhas de Produção).
     */
    void AdicionarLinha(int id, std::string desc, std::string local, std::string nome);
    void AdicionarLinha(std::string desc, std::string local, std::string nome);

    /**
     * @brief Remove a linha de produção com o ID fornecido.
     * @param id Identificador da linha a remover.
     * @note Implementa US-002 (Remover Linhas de Produção).
     */
    void RemoverLinha(int id);

    /** @return Referência constante ao vetor de linhas cadastradas. */
    const std::vector<LinhaDeProducao>& GetLinhas() const;

    /**
     * @brief Exibe no console todas as linhas de produção cadastradas.
     * @note Implementa US-003 (Acessar Linhas de Produção).
     */
    void ExibirLinhas();

    /**
     * @brief Cadastra um novo usuário no sistema.
     * @param login Login de acesso.
     * @param senha Senha do usuário.
     * @param cargo Cargo/nível de acesso.
     * @note Implementa US-015 (Criar usuários).
     */
    void AdicionarUsuario(std::string login, std::string senha, Cargo cargo);

    /**
     * @brief Remove o usuário identificado pelo login.
     * @param login Login do usuário a remover.
     * @note Implementa US-016 (Remover usuários).
     */
    void RemoverUsuario(std::string login);

    /**
     * @brief Retorna o próximo ID disponível para cadastro.
     * @return Menor ID inteiro ainda não utilizado.
     */
    int ProximoIdDisponivel() const;

    /**
     * @brief Verifica se um ID está disponível para uso.
     * @param Id ID a verificar.
     * @return true se o ID não estiver em uso.
     */
    bool IdAtivo(int Id) const;

    /**
     * @brief Autentica um usuário e inicia a sessão.
     * @param login Login do usuário.
     * @param senha Senha do usuário.
     * @return true se as credenciais forem válidas.
     * @note Implementa US-017 (Login de usuário).
     */
    bool Login(std::string login, std::string senha);

    /**
     * @brief Encerra a sessão do usuário atual.
     * @return true se havia uma sessão ativa e foi encerrada com sucesso.
     * @note Implementa US-022 (Logoff de usuário).
     */
    bool Logout();

    /** @return Ponteiro para o usuário atualmente logado, ou nullptr se não houver sessão. */
    Usuario* GetUsuarioLogado() const;

    /**
     * @brief Persiste o estado atual do sistema em arquivo.
     * @return true se o salvamento foi bem-sucedido.
     * @note Implementa US-020 (Persistir dados).
     */
    bool SalvarAlteracoes();

    /**
     * @brief Carrega o último estado salvo do sistema.
     * @return true se o carregamento foi bem-sucedido.
     * @note Implementa US-021 (Carregar dados).
     */
    bool CarregarUltimoSave();

    /**
     * @brief Carrega o estado do sistema a partir de um arquivo específico.
     * @param arquivo Caminho do arquivo de save.
     * @return true se o carregamento foi bem-sucedido.
     * @note Implementa US-021 (Carregar dados).
     */
    bool CarregarSave(std::string arquivo);
};

#endif
