#ifndef ALARME_HPP
#define ALARME_HPP

#include <string>
#include <vector>
#include "Parametro.hpp"

/**
 * @brief Alarme associado a um Parametro de um equipamento.
 *
 * Monitora um único parâmetro e mantém um estado booleano que indica
 * se o valor atual viola os limites configurados naquele parâmetro.
 */
class Alarme {
private:
    std::string _Desc;
    bool _Estado;
    int _Id;
    const Parametro* _Parametro;
public:
    /**
     * @brief Constrói um alarme vinculado a um parâmetro.
     * @param Desc Descrição do alarme.
     * @param Id   Identificador único do alarme.
     * @param p    Parâmetro monitorado por este alarme.
     * @note Implementa US-014 (Criar Alarme).
     */
    Alarme(std::string Desc, int Id, Parametro& p);

    /**
     * @brief Consulta o parâmetro associado e atualiza o estado do alarme.
     * @return true se o alarme estiver ativo (parâmetro em falha).
     */
    bool AtualizarAlarme();

    /** @return true se o alarme estiver ativo. */
    bool GetEstado() const;

    /** @brief Força o estado do alarme manualmente. @param Estado Novo estado. */
    void SetEstado(bool Estado);

    /** @brief Atualiza a descrição do alarme. @param desc Nova descrição. */
    void SetDesc(std::string desc);
};

#endif
