<<<<<<< HEAD
#ifndef PARAMETRO_HPP
#define PARAMETRO_HPP

#include <string>
#include <vector>

class Parametro {
private:
    int _id
    std::string _Desc;

    double _ValorAtual;
    std::vector<double> _Hist;

    double _Max;
    double _Min;

    bool _Estado;
public:
    Parametro(double ValorAtual, std::string Desc, ind id);
    Parametro(double ValorAtual, double Max, double Min, std::string Desc, int id);

    bool ValorValido(double Valor) const;

    void SetValorAtual(double Valor);
    void SetMax(double Valor);
    void SetMin(double Valor);
    void SetDesc (std::string Desc);
    bool DiagnosticarParametro();

    double GetValorAtual() const;
    double GetMax() const;
    double GetMin() const;
    std::string GetDesc() const;
    bool GetEstado() const;
    const std::vector<double>& GetHist() const;
    int GetId ();


    void ResetarLimites();
    void ResetarHistorico();
};

=======
#ifndef PARAMETRO_HPP
#define PARAMETRO_HPP

#include <string>
#include <vector>

class Parametro {
private:
    int _id
    std::string _Desc;

    double _ValorAtual;
    std::vector<double> _Hist;

    double _Max;
    double _Min;

    bool _Estado;
public:
    Parametro(double ValorAtual, std::string Desc, ind id);
    Parametro(double ValorAtual, double Max, double Min, std::string Desc, int id);

    bool ValorValido(double Valor) const;

    void SetValorAtual(double Valor);
    void SetMax(double Valor);
    void SetMin(double Valor);
    void SetDesc (std::string Desc);
    bool DiagnosticarParametro();

    double GetValorAtual() const;
    double GetMax() const;
    double GetMin() const;
    std::string GetDesc() const;
    bool GetEstado() const;
    const std::vector<double>& GetHist() const;
    int GetId ();


    void ResetarLimites();
    void ResetarHistorico();
};

>>>>>>> e0f0725 (Atualização de Cartões CRC e inclusão de contratos completos)
#endif