#ifndef LOG_HPP
#define LOG_HPP

#include <string>

/**
 * @brief Registra eventos e operações do sistema em arquivo de texto.
 */
class Log {
private:
    std::string _arquivo;
public:
    /**
     * @brief Constrói o logger apontando para o arquivo especificado.
     * @param arquivo Caminho do arquivo de log.
     */
    Log(const std::string& arquivo);

    /**
     * @brief Acrescenta uma mensagem ao arquivo de log.
     * @param mensagem Texto a registrar (limite de 500 caracteres).
     * @return true se o registro foi bem-sucedido.
     * @note Implementa US-019 (Registro de informações no log).
     */
    bool Registrar(const std::string& mensagem) const;

    /** @return Caminho do arquivo de log atual. */
    std::string GetArquivoLog() const;

    /**
     * @brief Redireciona o log para um novo arquivo.
     * @param arquivo Novo caminho de arquivo.
     * @return true se a alteração foi aceita.
     */
    bool SetArquivoLog(const std::string& arquivo);
};

#endif
