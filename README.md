# Sistema de Tolerância de Falha em Fábricas

Sistema de monitoramento industrial orientado a objetos desenvolvido em C++. Permite o acompanhamento em tempo real de parâmetros de equipamentos organizados em linhas de produção, detectando automaticamente condições de falha e disparando alarmes.

## Funcionalidades

- Gerenciamento hierárquico de **Linhas de Produção → Conjuntos → Equipamentos → Parâmetros**
- Monitoramento de parâmetros com limites configuráveis (Min/Max)
- Disparo automático de **alarmes** quando parâmetros violam seus limites
- **Diagnóstico** propagado por toda a hierarquia, identificando os pontos de falha
- Controle de acesso por usuários com três níveis de cargo
- Persistência de dados com save/load de estado
- Registro de eventos via **Log** em arquivo

## Hierarquia do Sistema

```
Sistema
 \-- LinhaDeProducao
       \-- Conjunto
             \-- Equipamento
                   +-- Parametro
                   \-- Alarme
```

## Cargos de Usuário

| Cargo | Permissões |
|---|---|
| `ADMIN` | Gerencia usuários e toda a estrutura do sistema |
| `ENGENHEIRO` | Configura linhas, conjuntos e equipamentos |
| `TECNICO` | Visualiza dados e alarmes |

## Estrutura de Diretórios

```
.
+-- include/        # Contratos das classes (.hpp)
+-- src/            # Implementacoes (.cpp)
+-- design/         # User Stories e Cartoes CRC
+-- tests/          # Testes automatizados
+-- build/          # Artefatos de compilacao
+-- docs/           # Documentacao gerada pelo Doxygen
\-- README.md
```

## Compilação

```bash
make
```

## Documentação

A documentação das classes pode ser gerada com o Doxygen a partir da raiz do projeto:

```bash
doxygen Doxyfile
```

A saída HTML estará disponível em `docs/html/index.html`.
Uma versão, atualiza, em PDF pode ser encontrada na raiz do projeto como `doxygen_doc.pdf`.

## Equipe
| Nº Matrícula | Nome |
|--------------|------| 
| 2024010002 | Felipe Hildegardes Jorge |
| 2022028400dox | Wennedes de Oliveira Nogueira Junior |
| 2020057144 | Gustavo Coelho Santos |