#ifndef CONJUNTO_HPP
#define CONJUNTO_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>
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
    int _ProximoIdEquipamento = 1;

    std::map<int, std::unique_ptr<Equipamento>> _Equipamentos;
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
     * @brief Adiciona um equipamento já construído (permite tipos derivados).
     * @param equip Equipamento (posse transferida ao conjunto via unique_ptr).
     * @note Suporta polimorfismo: Motor, Sensor, Valvula, Atuador.
     */
    void AdicionarEquipamento(std::unique_ptr<Equipamento> equip);

    /** @return Próximo ID disponível para equipamento (monotônico). */
    int ProximoIdEquipamento() const;

    /**
     * @brief Remove o equipamento com o ID fornecido.
     * @param id Identificador do equipamento a remover.
     */
    void RemoverEquipamento(int id);

    /** @brief Atualiza a descrição do conjunto. @param desc Nova descrição. */
    void SetDesc(std::string desc);

    /** @brief Atualiza o nome do conjunto. @param nome Novo nome. */
    void SetNome(std::string nome);

    /**
     * @brief Exibe no console os equipamentos do conjunto.
     */
    void ExibirEquipamentos() const;

    /** @brief Exibe no console os alarmes ativos de todos os equipamentos. */
    void ExibirAlarmes() const;

    /**
     * @brief Exibe equipamentos e alarmes de forma consolidada.
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
     */
    void AtualizarAlarmes();

    /** @return Referência constante ao mapa de equipamentos (posse via unique_ptr). */
    const std::map<int, std::unique_ptr<Equipamento>>& GetEquipamentos() const;

    /**
     * @brief Acesso mutável a um equipamento pelo ID.
     * @param id Identificador do equipamento.
     * @return Referência ao equipamento.
     * @throws IdInexistente se não houver equipamento com o ID.
     */
    Equipamento& AcessarEquipamento(int id);

    /** @return Identificador único do conjunto. */
    int GetId() const;

    /** @return Descrição do conjunto. */
    std::string GetDesc() const;

    /** @return Nome do conjunto. */
    std::string GetNome() const;
};

#endif
