#ifndef CONJUNTO_HPP
#define CONJUNTO_HPP

#include <string>
#include <vector>
#include <map>
#include "Equipamento.hpp"

/**
 * @brief Agrupamento lógico de equipamentos dentro de uma LinhaDeProducao.
 *
 * Um conjunto reúne equipamentos correlacionados e propaga operações de
 * diagnóstico e atualização de alarmes para todos eles.
 */
class Conjunto {
private:
    int _id;
    std::string _desc;
    std::string _nome;

    std::map<int, Equipamento> _Equipamentos;
public:
    /**
     * @brief Constrói um conjunto.
     * @param id   Identificador único.
     * @param desc Descrição do conjunto.
     */
    Conjunto(int id, std::string nome ,std::string desc);

    /**
     * @brief Adiciona um equipamento ao conjunto.
     * @param id   Identificador único do equipamento.
     * @param desc Descrição do equipamento.
     * @note Implementa US-007 (Criar Equipamentos).
     */
    void AdicionarEquipamento(int id, std::string desc);

    /**
     * @brief Remove o equipamento com o ID fornecido.
     * @param id Identificador do equipamento a remover.
     * @note Implementa US-008 (Remover Equipamento).
     */
    void RemoverEquipamento(int id);

    /** @brief Atualiza a descrição do conjunto. @param desc Nova descrição. */
    void SetDesc(std::string desc);

    /** @brief Atualiza o nome do conjunto. @param nome Novo nome. */
    void SetNome(std::string nome);

    /**
     * @brief Exibe no console os equipamentos do conjunto.
     * @note Implementa US-006 (Acessar Conjunto).
     */
    void ExibirEquipamentos() const;

    /** @brief Exibe no console os alarmes ativos de todos os equipamentos. */
    void ExibirAlarmes() const;

    /**
     * @brief Exibe equipamentos e alarmes de forma consolidada.
     * @note Implementa US-006 (Acessar Conjunto).
     */
    void ExibirTudo() const;

    /** @return Número de equipamentos cadastrados no conjunto. */
    int QuantidadeEquipamentos() const;

    /** @return Número total de alarmes ativos no conjunto. */
    int QuantidadeAlarmes() const;

    /**
     * @brief Diagnostica todos os equipamentos do conjunto.
     * @return Vetor com IDs dos parâmetros em estado de falha.
     * @note Implementa US-012 (Diagnóstico de Conjunto).
     */
    std::vector<int> DiagnosticarConjunto() const;

    /**
     * @brief Propaga a atualização de alarmes para todos os equipamentos.
     * @note Implementa US-014 (Criar Alarme).
     */
    void AtualizarAlarmes();

    /** @return Referência constante ao mapa de equipamentos. */
    const std::map<int, Equipamento>& GetEquipamentos() const;

    /** @return Identificador único do conjunto. */
    int GetId() const;

    /** @return Descrição do conjunto. */
    std::string GetDesc() const;

    /** @return Nome do conjunto. */
    std::string GetNome() const;
};

#endif
