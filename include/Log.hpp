#ifndef LOG_HPP
#define LOG_HPP

#include <string>

class Log {
private:
    std::string _arquivo;
public:
    Log (const std::string& arquivo);

    bool Registrar (const std::string& mensagem) const;

    std::string GetArquivoLog () const;
    bool SetArquivoLog (const std::string& arquivo);
};

#endif