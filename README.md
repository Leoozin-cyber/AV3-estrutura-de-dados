## 👥 Integrantes do Grupo e Funções
* **Integrante A:** Leonardo Góes Santos Cavalcante — Desenvolvimento do **Trabalho A**
* **Integrante B:** Alex Augusto da Cruz Gomes Júnior — Desenvolvimento do **Trabalho B**
* **Integrante C:** Caio de Souza Vitorino — Desenvolvimento do **Trabalho C**

---


## 📁 Estrutura de Pastas do Projeto

O projeto está organizado em subpastas dedicadas para manter os códigos-fontes e os arquivos de dados separados de forma limpa:

```t
AV3 Estrutura de Dados/
│
├── .vscode/
│   └── tasks.json       # Configuração de automação de compilação do  VS Code
│
├── README.md            # Manual de instruções e execução (Este arquivo)
├── relatorio.md         # Relatório técnico e fundamentação teórica
│
├── Trabalho A/
│   ├── trabalho_a.c     # Playlist de Músicas (Lista Sequencial)
│   └── dados_a.csv      # Base de dados das músicas
│
├── Trabalho B/
│   ├── trabalho_b.c     # Chamadas de emergência (Pilha LIFO)
│   └── dados_b.csv      # Base de dados dos atendimentos
│
└── Trabalho C/
    ├── trabalho_c.c     # Atendimento Bancário (Fila Circular FIFO)
    └── dados_c.csv      # Base de dados das senhas

---

# 🛠️ Como compilar e executar os trabalhos   

🎵 Trabalho A: Playlist de Músicas (Lista)
Compilar: gcc "Trabalho A/trabalho_a.c" -o trabalho_a
Executar: .\trabalho_a

🚨 Trabalho B: Chamadas de emergência (Pilha)
Compilar: gcc "Trabalho B/trabalho_b.c" -o trabalho_b
Executar: .\trabalho_b

🏦 Trabalho C: Atendimento Bancário (Fila Circular)
Compilar: gcc "Trabalho C/trabalho_c.c" -o trabalho_c
Executar: .\trabalho_c

---

## 🔍 6. Observações Críticas sobre o Funcionamento

Para garantir a execução correta e a consistência dos dados, o grupo mapeou as seguintes características e comportamentos do sistema:

### ⚡ 1. Comportamento da Fila Circular (Trabalho C)
* **Gerenciamento de Índices:** Diferente de uma fila linear comum, onde a remoção exige "arrastar" todos os elementos para a esquerda ($O(n)$), a nossa Fila Circular apenas move os ponteiros lógicos `inicio` e `fim` usando o operador resto (`%`).
* **Zerar a Fila:** Quando a quantidade de elementos chega a 0, o sistema reseta os índices `inicio` e `fim` para `0`. Isso previne fragmentação e garante que novas inserções comecem sempre no primeiro índice da memória.

### 👥 2. Algoritmo de Prioridade Bancária (Normais vs. Preferenciais)
* **Prevenção de Starvation:** O sistema utiliza um `contadorNormais`. A regra atende até 2 pessoas da fila normal consecutivas antes de verificar a fila preferencial. 
* **Fluxo de Exceção:** Se a fila normal estiver cheia e a preferencial vazia (ou vice-versa), o sistema ignora temporariamente o contador e atende quem estiver disponível, impedindo que o sistema trave por falta de um tipo específico de senha.

### 💾 3. Particularidades da Persistência (CSV)
* **Tratamento de Strings:** A função de leitura utiliza o caractere ponto e vírgula (`;`) como delimitador. Durante o cadastro de textos (como horários ou nomes), o sistema possui uma trava que sanitiza a entrada, removendo qualquer `;` digitado pelo usuário. Isso evita a quebra indesejada de colunas ao recarregar o arquivo.
* **Ajuste Automático do Contador:** Ao carregar o arquivo CSV, o sistema varre todos os registros, identifica qual era o maior número de senha emitido anteriormente e define o `proximoNumero` como `maiorNumero + 1`. Isso impede a duplicação de IDs de senhas entre reinicializações do programa.

### ⚠️ 4. Limitações de Memória (Vetor Estático)
* **Capacidade Máxima:** Como as três estruturas foram implementadas utilizando alocação estática (vetores com tamanho fixo de 50 posições), o sistema emitirá um alerta de "Fila/Pilha Cheia" caso o limite seja atingido. Para expandir essa capacidade, bastaria alterar as constantes `#define TAM_FILA` no topo do código-fonte.