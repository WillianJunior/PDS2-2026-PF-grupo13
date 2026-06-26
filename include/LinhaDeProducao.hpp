#ifndef LINHADEPRODUCAO_HPP
#define LINHADEPRODUCAO_HPP

#include <map>
#include <vector>
#include <string>

#include "Conjunto.hpp"

/**
 * @brief Representa uma linha de produção industrial.
 *
 * Agrega conjuntos de equipamentos e oferece operações de diagnóstico
 * e visualização para toda a linha.
 */
class LinhaDeProducao {
private:
    int _id;
    std::string _nome;
    std::string _local;
    std::string _desc;
    int _ProximoIdConjunto = 1;

    std::map<int, Conjunto> _Conjuntos;
public:
    /**
     * @brief Constrói uma linha de produção.
     * @param id    Identificador único.
     * @param desc  Descrição da linha.
     * @param local Localização física.
     * @param nome  Nome da linha.
     */
    LinhaDeProducao(int id, std::string desc, std::string local, std::string nome);

    /**
     * @brief Adiciona um conjunto à linha.
     * @param id   Identificador único do conjunto.
     * @param desc Descrição do conjunto.
     * @note Implementa US-004 (Criar Conjuntos).
     */
    void AdicionarConjunto(int id, std::string nome, std::string desc);

    /**
     * @brief Adiciona um conjunto com ID gerado automaticamente (incremental).
     * @return ID atribuído ao conjunto criado.
     */
    int AdicionarConjunto(std::string nome, std::string desc);

    /** @return Próximo ID disponível para conjunto (monotônico). */
    int ProximoIdConjunto() const;

    /**
     * @brief Remove o conjunto com o ID fornecido.
     * @param id Identificador do conjunto a remover.
     */
    void RemoverConjunto(int id);

    /**
     * @brief Exibe no console os conjuntos da linha.
     */
    void ExibirConjuntos() const;

    /** @brief Exibe no console os alarmes ativos de toda a linha. */
    void ExibirAlarmes() const;

    /**
     * @brief Exibe conjuntos, equipamentos e alarmes de forma consolidada.
     */
    void ExibirTudo() const;

    /** @return Número de conjuntos cadastrados na linha. */
    int QuantidadeConjuntos() const;

    /** @return Número total de alarmes ativos na linha. */
    int QuantidadeAlarmes() const;

    /**
     * @brief Diagnostica todos os conjuntos da linha.
     * @return Vetor com IDs dos parâmetros em estado de falha.
     * @note Implementa US-013 (Diagnóstico de Linha de Produção).
     */
    std::vector<int> DiagnosticarLinha() const;

    /**
     * @brief Propaga a atualização de alarmes para todos os conjuntos.
     */
    void AtualizarAlarmes();

    /** @brief Atualiza a descrição da linha. @param desc Nova descrição. */
    void SetDesc(std::string desc);

    /** @brief Atualiza a localização da linha. @param local Nova localização. */
    void SetLocal(std::string local);

    /** @brief Atualiza o nome da linha. @param nome Novo nome. */
    void SetNome(std::string nome);

    /** @return Referência constante ao mapa de conjuntos. */
    const std::map<int, Conjunto>& GetConjuntos() const;

    /**
     * @brief Acesso mutável a um conjunto pelo ID.
     * @param id Identificador do conjunto.
     * @return Referência ao conjunto.
     * @throws IdInexistente se não houver conjunto com o ID.
     */
    Conjunto& AcessarConjunto(int id);

    /** @return Identificador único da linha. */
    int GetId() const;

    /** @return Descrição da linha. */
    std::string GetDesc() const;

    /** @return Localização física da linha. */
    std::string GetLocal() const;

    /** @return Nome da linha. */
    std::string GetNome() const;
};

#endif
