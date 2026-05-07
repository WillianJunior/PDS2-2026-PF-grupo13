<<<<<<< HEAD
#ifndef ALARME_HPP
#define ALARME_HPP

#include <string>
#include <vector>
#include "Parametro.hpp"

class Alarme {
private:
    std::string _Desc;

    bool _Estado;

    int _Id;
    const Parametro* _Parametro;
public:
    Alarme(std::string Desc, int Id, Parametro& p);

    bool AtualizarAlarme ();

    bool GetEstado() const;

    void SetEstado (bool Estado);
    void SetDesc (std::string);

};

=======
#ifndef ALARME_HPP
#define ALARME_HPP

#include <string>
#include <vector>
#include "Parametro.hpp"

class Alarme {
private:
    std::string _Desc;

    bool _Estado;

    int _Id;
    const Parametro* _Parametro;
public:
    Alarme(std::string Desc, int Id, Parametro& p);

    bool AtualizarAlarme ();

    bool GetEstado() const;

    void SetEstado (bool Estado);
    void SetDesc (std::string);

};

>>>>>>> e0f0725 (Atualização de Cartões CRC e inclusão de contratos completos)
#endif