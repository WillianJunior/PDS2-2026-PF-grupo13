<<<<<<< HEAD
#ifndef LINHADEPRODUCAO_HPP
#define LINHADEPRODUCAO_HPP

#include <vector>
#include <string>

#include "Conjunto.hpp"

class LinhaDeProducao {
private:
    int _id;
    std::string _nome;
    std::string _local;
    std::string _desc;

    std::vector<Conjunto> _Conjuntos;
public:
    LinhaDeProducao(int id, std::string desc, std::string local, std::string nome);

    void AdicionarConjunto (int id, std::string desc);
    void RemoverConjunto (int id);

    void ExibirConjuntos () const;
    void ExibirAlarmes () const;
    void ExibirTudo () const;

    int QuantidadeConjuntos() const;
    int QuantidadeAlarmes() const;

    std::vector<int> DiagnosticarLinha() const;
    void AtualizarAlarmes ();

    void SetDesc (std::string desc);
    void SetLocal (std::string local);
    void SetNome (std::string nome);

    const std::vector<Conjunto>& GetConjuntos() const;

    int GetId () const;
    std::string GetDesc () const;
    std::string GetLocal () const;
    std::string GetNome () const;
};

=======
#ifndef LINHADEPRODUCAO_HPP
#define LINHADEPRODUCAO_HPP

#include <vector>
#include <string>

#include "Conjunto.hpp"

class LinhaDeProducao {
private:
    int _id;
    std::string _nome;
    std::string _local;
    std::string _desc;

    std::vector<Conjunto> _Conjuntos;
public:
    LinhaDeProducao(int id, std::string desc, std::string local, std::string nome);

    void AdicionarConjunto (int id, std::string desc);
    void RemoverConjunto (int id);

    void ExibirConjuntos () const;
    void ExibirAlarmes () const;
    void ExibirTudo () const;

    int QuantidadeConjuntos() const;
    int QuantidadeAlarmes() const;

    std::vector<int> DiagnosticarLinha() const;
    void AtualizarAlarmes ();

    void SetDesc (std::string desc);
    void SetLocal (std::string local);
    void SetNome (std::string nome);

    const std::vector<Conjunto>& GetConjuntos() const;

    int GetId () const;
    std::string GetDesc () const;
    std::string GetLocal () const;
    std::string GetNome () const;
};

>>>>>>> e0f0725 (Atualização de Cartões CRC e inclusão de contratos completos)
#endif