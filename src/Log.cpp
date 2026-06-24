#include "Log.hpp"

#include <fstream>

Log::Log(const std::string& arquivo) {
    this->_arquivo = arquivo;
}

bool Log::Registrar(const std::string& mensagem) const {
    if (mensagem.empty() || mensagem.size() > 500) {
        return false;
    }

    std::ofstream ofs(this->_arquivo, std::ios::app);
    if (!ofs.is_open()) {
        return false;
    }

    ofs << mensagem << '\n';
    return ofs.good();
}

std::string Log::GetArquivoLog() const {
    return this->_arquivo;
}

bool Log::SetArquivoLog(const std::string& arquivo) {
    if (arquivo.empty()) {
        return false;
    }
    this->_arquivo = arquivo;
    return true;
}
