#ifndef EQUIPAMENTO_HPP
#define EQUIPAMENTO_HPP

#include <string>
#include <vector>
#include <map>
#include "Parametro.hpp"
#include "Alarme.hpp"

/**
 * @brief Representa um equipamento físico dentro de um Conjunto.
 *
 * Gerencia uma coleção de parâmetros monitorados e os alarmes derivados
 * deles. Oferece diagnóstico consolidado do estado do equipamento.
 */
class Equipamento {
private:
    int _id;
    std::string _desc;
    std::string _nome;

    std::map<int, Parametro> _Parametros;
    std::vector<Alarme> _Alarmes;
public:
    /**
     * @brief Constrói um equipamento.
     * @param id   Identificador único.
     * @param desc Descrição do equipamento.
     */
    Equipamento(int id, std::string desc, std::string nome);

    /**
     * @brief Adiciona um parâmetro sem limites definidos.
     * @param ValorAtual Leitura inicial.
     * @param Desc       Descrição do parâmetro.
     * @param id         Identificador único do parâmetro.
     * @note Implementa US-018 (Configurar parâmetros de equipamentos).
     */
    void AdicionarParametro(double ValorAtual, std::string Desc, int id);

    /**
     * @brief Adiciona um parâmetro com limites Min/Max definidos.
     * @param ValorAtual Leitura inicial.
     * @param Max        Limite superior aceitável.
     * @param Min        Limite inferior aceitável.
     * @param Desc       Descrição do parâmetro.
     * @note Implementa US-018 (Configurar parâmetros de equipamentos).
     */
    void AdicionarParametro(double ValorAtual, double Max, double Min, std::string Desc, int id);

    /**
     * @brief Remove o parâmetro com o ID fornecido.
     * @param id Identificador do parâmetro a remover.
     */
    void RemoverParametro(int id);

    /**
     * @brief Diagnostica todos os parâmetros do equipamento.
     * @return Vetor com IDs dos parâmetros em estado de falha.
     * @note Implementa US-011 (Diagnóstico de Equipamento).
     */
    std::vector<int> DiagnosticarEquipamento() const;

    /**
     * @brief Atualiza o estado de todos os alarmes do equipamento.
     * @note Implementa US-014 (Criar Alarme).
     */
    void AtualizarAlarmes();

    /**
     * @brief Exibe no console os parâmetros e seus valores atuais.
     * @note Implementa US-009 (Acessar Equipamento).
     */
    void ExibirParametros() const;

    /**
     * @brief Exibe no console os alarmes ativos do equipamento.
     * @note Implementa US-009 (Acessar Equipamento).
     */
    void ExibirAlarmes() const;

    /** @return Número de parâmetros cadastrados. */
    int QuantidadeParametros() const;

    /** @return Número de alarmes ativos. */
    int QuantidadeAlarmes() const;

    /** @return Identificador único do equipamento. */
    int GetId() const;

    /** @return Referência constante ao vetor de parâmetros. */
    const std::vector<Parametro>& GetParametros() const;

    /** @return Referência constante ao vetor de alarmes. */
    const std::vector<Alarme>& GetAlarmes() const;

    /** @brief Atualiza a descrição do equipamento. @param desc Nova descrição. */
    void SetDesc(std::string desc);
};

#endif
