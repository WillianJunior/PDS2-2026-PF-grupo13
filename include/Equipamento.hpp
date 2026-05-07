#ifndef EQUIPAMENTO_HPP
#define EQUIPAMENTO_HPP

#include <string>
#include <vector>
#include "Parametro.hpp"
#include "Alarme.hpp"

class Equipamento {
private:
    int _id;

    std::string _desc;

    std::vector<Parametro> _Parametros;
    std::vector<Alarme> _Alarmes;
public:
    Equipamento(int id, std::string desc);

    void AdicionarParametro (double ValorAtual, std::string Desc, int id);
    void AdicionarParametroComLimites (double ValorAtual, double Max, double Min, std::string Desc);

    void RemoverParametro (int id);

    std::vector<int> DiagnosticarEquipamento() const;
    void AtualizarAlarmes ();

    void ExibirParametros () const;
    void ExibirAlarmes () const;

    int QuantidadeParametros() const;
    int QuantidadeAlarmes() const;

    int GetId() const;
    const std::vector<Parametro>& GetParametros() const;
    const std::vector<Alarme>& GetAlarmes() const;

    void SetDesc (std::string);
};

#endif