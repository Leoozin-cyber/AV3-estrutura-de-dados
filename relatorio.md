# Projeto AV3 - Estrutura de Dados 🚀

Este repositório contém a consolidação dos três projetos práticos desenvolvidos para a AV3 da disciplina de Estrutura de Dados para o curso de Análise e Desenvolvimento de Sistemas (ADS). Cada trabalho simula um cenário real utilizando estruturas lineares com persistência de dados em arquivos CSV.

---

## 👥 Integrantes do Grupo e Funções
* **Integrante A:** Leonardo Góes Santos Cavalcante — Desenvolvimento do **Trabalho A**
* **Integrante B:** Alex Augusto da Cruz Gomes Júnior — Desenvolvimento do **Trabalho B**
* **Integrante C:** Caio de Souza Vitorino — Desenvolvimento do **Trabalho C**

---

📝 Descrição Breve dos Trabalhos

🎵 Trabalho A: Playlist de músicas (Lista Sequencial)
O primeiro módulo gerencia uma playlist de músicas utilizando uma estrutura de dados do tipo struct chamada Musica para agrupar as informações de cada faixa (como ID, título, artista e duração). Essas structs são armazenadas de forma linear e sequencial dentro de um vetor global. A inserção de novas músicas ocorre sempre no final do vetor por meio de um contador de controle, contando com validações que impedem o cadastro de IDs duplicados e barram novas entradas caso o limite máximo de memória seja atingido. Na exclusão, para evitar buracos na memória, o algoritmo realiza o deslocamento físico de todas as structs posteriores uma posição para trás, reorganizando os índices de forma sequencial para as operações de busca, listagem e edição.

🚨 Trabalho B: Chamadas de emergência (Pilha LIFO)
O segundo módulo simula um sistema de pronto-socorro baseado na estrutura de pilha estática sequencial, operando estritamente sob a regra LIFO (Last In, First Out). O fluxo modela uma fila de emergência onde o último caso crítico empilhado representa a urgência mais recente, precisando de mitigação imediata e tornando-se obrigatoriamente o primeiro a ser desempilhado e atendido pelo médico de plantão. O estado atual da pilha e o histórico de atendimentos pendentes são sincronizados e validados de forma contínua com persistência de dados em arquivo externo.

🏦 Trabalho C: Atendimento Bancário (Fila Circular FIFO)
O terceiro módulo controla o atendimento bancário através de uma fila circular estática que segue a regra do primeiro a chegar, primeiro a ser atendido. A implementação mapeia o fluxo movendo apenas os ponteiros lógicos de início e fim por meio de resto da divisão, otimizando o uso da memória ao evitar o reposicionamento pesado de estruturas a cada chamada de senha, além de contar com um algoritmo de prioridade alternada que chama até duas senhas normais para cada uma preferencial para mitigar o tempo de espera. Quando a fila se esvazia, os índices são reiniciados para garantir que os próximos registros comecem sempre no primeiro índice da memória física.

---

🛠️ Desafios e Soluções Práticas

Durante o desenvolvimento em C, o grupo enfrentou desafios clássicos de manipulação de fluxos de entrada e saída, resolvidos da seguinte forma:

1. **Sujeira no Buffer do Teclado (`stdin`):** Ao utilizar `scanf()` para ler números, o caractere de nova linha (`\n`) permanecia no buffer, fazendo com que o `fgets` seguinte fosse ignorado. **Solução:** Implementação da função utilitária `limparBuffer()` usando um laço com `getchar()`.
2. **Eliminação de Terminações de String:** O `fgets` captura o caractere `\n` ao final da digitação. **Solução:** Criação da função `removerNovaLinha()` que localiza o caractere terminal e o substitui por `\0` para evitar saltos de linha incorretos nas impressões de tela.

---

## 🏁 Conclusão
A execução deste projeto consolidou de forma prática os custos computacionais de cada estrutura estudada em ambiente acadêmico. Ficou evidente para o grupo que o uso de vetores estáticos de structs atende perfeitamente a problemas de escopo controlado (com limites definidos por constantes `#define`), e que a escolha lógica entre Listas, Pilhas e Filas dita diretamente a eficiência do software em cenários reais de logística e atendimento de dados.