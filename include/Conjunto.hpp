<<<<<<< HEAD
#ifndef CONJUNTO_HPP
#define CONJUNTO_HPP

#include <string>
#include <vector>
#include "Equipamento.hpp"

class Conjunto {
private:
    int _id;
    std::string _desc;
    std::string _nome;

    std::vector<Equipamento> _Equipamentos;
public:
    Conjunto(int id, std::string desc);

    void AdicionarEquipamento (int id, std::string desc);
    void RemoverEquipamento (int id);

    void SetDesc (std::string desc);
    void SetNome (std::string nome);

    void ExibirEquipamentos () const;
    void ExibirAlarmes () const;
    void ExibirTudo () const;

    int QuantidadeEquipamentos() const;
    int QuantidadeAlarmes() const;

    std::vector<int> DiagnosticarConjunto() const;
    void AtualizarAlarmes ();

    const std::vector<Equipamento>& GetEquipamentos() const;

    int GetId () const;
    std::string GetDesc () const;
    std::string GetNome () const;
};

=======
#ifndef CONJUNTO_HPP
#define CONJUNTO_HPP

#include <string>
#include <vector>
#include "Equipamento.hpp"

class Conjunto {
private:
    int _id;
    std::string _desc;
    std::string _nome;

    std::vector<Equipamento> _Equipamentos;
public:
    Conjunto(int id, std::string desc);

    void AdicionarEquipamento (int id, std::string desc);
    void RemoverEquipamento (int id);

    void SetDesc (std::string desc);
    void SetNome (std::string nome);

    void ExibirEquipamentos () const;
    void ExibirAlarmes () const;
    void ExibirTudo () const;

    int QuantidadeEquipamentos() const;
    int QuantidadeAlarmes() const;

    std::vector<int> DiagnosticarConjunto() const;
    void AtualizarAlarmes ();

    const std::vector<Equipamento>& GetEquipamentos() const;

    int GetId () const;
    std::string GetDesc () const;
    std::string GetNome () const;
};

>>>>>>> e0f0725 (Atualização de Cartões CRC e inclusão de contratos completos)
#endif