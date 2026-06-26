#ifndef PARAMETRO_HPP
#define PARAMETRO_HPP

#include <string>
#include <vector>

/**
 * @brief Representa um parâmetro monitorado de um equipamento.
 *
 * Armazena um valor numérico em tempo real, limites aceitáveis (Min/Max),
 * histórico de leituras e um estado de diagnóstico.
 */
class Parametro {
private:
    int _id;
    std::string _Desc;

    double _ValorAtual;
    std::vector<double> _Hist;

    double _Max;
    double _Min;

    bool _Estado;
public:
    /**
     * @brief Constrói um parâmetro sem limites definidos.
     * @param ValorAtual Leitura inicial do parâmetro.
     * @param Desc       Descrição do parâmetro.
     * @param id         Identificador único.
     */
    Parametro(double ValorAtual, std::string Desc, int id);

    /**
     * @brief Constrói um parâmetro com limites Min/Max definidos.
     * @param ValorAtual Leitura inicial do parâmetro.
     * @param Max        Limite superior aceitável.
     * @param Min        Limite inferior aceitável.
     * @param Desc       Descrição do parâmetro.
     * @param id         Identificador único.
     */
    Parametro(double ValorAtual, double Max, double Min, std::string Desc, int id);

    /**
     * @brief Verifica se um valor está dentro dos limites configurados.
     * @param Valor Valor a verificar.
     * @return true se o valor estiver dentro dos limites.
     */
    bool ValorValido(double Valor) const;

    /**
     * @brief Atualiza o valor atual e registra no histórico.
     * @param Valor Novo valor lido.
     */
    void SetValorAtual(double Valor);

    /**
     * @brief Define o limite superior.
     * @param Valor Novo limite máximo.
     */
    void SetMax(double Valor);

    /**
     * @brief Define o limite inferior.
     * @param Valor Novo limite mínimo.
     */
    void SetMin(double Valor);

    /** @brief Atualiza a descrição do parâmetro. @param Desc Nova descrição. */
    void SetDesc(std::string Desc);

    /**
     * @brief Verifica se o valor atual viola os limites e atualiza o estado.
     * @return true se o parâmetro estiver fora dos limites (em falha).
     * @note Implementa US-011 (Diagnóstico de Equipamento).
     */
    bool DiagnosticarParametro();

    /** @return Valor atual do parâmetro. */
    double GetValorAtual() const;

    /** @return Limite máximo configurado. */
    double GetMax() const;

    /** @return Limite mínimo configurado. */
    double GetMin() const;

    /** @return Descrição do parâmetro. */
    std::string GetDesc() const;

    /** @return true se o parâmetro estiver em estado de falha. */
    bool GetEstado() const;

    /**
     * @return Histórico de leituras anteriores.
     * @note Relacionado a US-010 (Leitura do Equipamento).
     */
    const std::vector<double>& GetHist() const;

    /** @return Identificador único do parâmetro. */
    int GetId();

    /** @brief Restaura os limites Min/Max para os valores padrão (sem restrição). */
    void ResetarLimites();

    /** @brief Limpa o histórico de leituras. */
    void ResetarHistorico();
};

#endif
