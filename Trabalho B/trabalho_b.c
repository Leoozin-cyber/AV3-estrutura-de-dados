#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Estrutura de dados definida conforme Tema B2
typedef struct {
    int protocolo;
    char local[50];
    char tipo[30];
    char horario[20];
} Chamada;

// Variaveis globais de controle da pilha
Chamada pilha[MAX];
int topo = -1;

/* PUSH: Insere elemento no topo */
void push() {
    if (topo == MAX - 1) {
        printf("\n[Erro] A pilha esta cheia (Stack Overflow).\n");
        return;
    }
    Chamada c;
    printf("\n--- Registrar Chamada ---\n");
    printf("Protocolo: ");
    scanf("%d", &c.protocolo);
    getchar(); // limpar buffer

    printf("Local: ");
    fgets(c.local, 50, stdin);
    c.local[strcspn(c.local, "\n")] = 0;

    printf("Tipo da ocorrencia: ");
    fgets(c.tipo, 30, stdin);
    c.tipo[strcspn(c.tipo, "\n")] = 0;

    printf("Horario (ex: 14:30): ");
    fgets(c.horario, 20, stdin);
    c.horario[strcspn(c.horario, "\n")] = 0;

    topo++;
    pilha[topo] = c;
    printf("\n[Sucesso] Chamada registrada no topo da pilha.\n");
}

/* POP: Remove elemento do topo */
void pop() {
    if (topo == -1) {
        printf("\n[Aviso] Nenhuma chamada pendente (Pilha Vazia).\n");
        return;
    }
    Chamada c = pilha[topo];
    topo--;
    printf("\n--- Chamada Atendida ---\n");
    printf("Protocolo: %d\n", c.protocolo);
    printf("Local: %s\n", c.local);
    printf("Tipo: %s\n", c.tipo);
    printf("Horario: %s\n", c.horario);
    printf("------------------------\n");
}

/* PEEK: Consulta o topo sem remover */
void peek() {
    if (topo == -1) {
        printf("\n[Aviso] Nenhuma chamada pendente.\n");
        return;
    }
    Chamada c = pilha[topo];
    printf("\n--- Proxima Chamada (Topo) ---\n");
    printf("Protocolo: %d\n", c.protocolo);
    printf("Local: %s\n", c.local);
    printf("Tipo: %s\n", c.tipo);
    printf("Horario: %s\n", c.horario);
    printf("------------------------------\n");
}

/* LISTAR: Mostra do topo para a base */
void listar() {
    if (topo == -1) {
        printf("\n[Aviso] Nenhuma chamada pendente.\n");
        return;
    }
    printf("\n--- Lista de Chamadas Pendentes (Topo -> Base) ---\n");
    for (int i = topo; i >= 0; i--) {
        printf("[%d] Protocolo: %d | Local: %s | Tipo: %s | Horario: %s\n",
                i, pilha[i].protocolo, pilha[i].local, pilha[i].tipo, pilha[i].horario);
    }
    printf("--------------------------------------------------\n");
}

/* SALVAR: Grava os dados no CSV (da base para o topo) - Ajustado para a pasta correta */
void salvarCSV() {
    FILE *f = fopen("Trabalho B/dados_b.csv", "w");
    if (f == NULL) {
        printf("\n[Erro] Nao foi possivel abrir o arquivo em Trabalho B/dados_b.csv.\n");
        return;
    }
    fprintf(f, "protocolo;local;tipo;horario\n");
    for (int i = 0; i <= topo; i++) {
        fprintf(f, "%d;%s;%s;%s\n",
                pilha[i].protocolo, pilha[i].local, pilha[i].tipo, pilha[i].horario);
    }
    fclose(f);
    printf("\n[Sucesso] Dados salvos em Trabalho B/dados_b.csv.\n");
}

/* CARREGAR: Reconstroi a pilha a partir do arquivo CSV - Ajustado para a pasta correta */
void carregarCSV() {
    FILE *f = fopen("Trabalho B/dados_b.csv", "r");
    if (f == NULL) {
        printf("\n[Erro] Arquivo Trabalho B/dados_b.csv nao encontrado.\n");
        return;
    }
    char linha[256];
    fgets(linha, sizeof(linha), f); // Ignorar cabecalho
    topo = -1; // Limpar pilha
    while (fgets(linha, sizeof(linha), f)) {
        if (topo == MAX - 1) break;
        linha[strcspn(linha, "\n")] = 0;
        Chamada c;
        char *token = strtok(linha, ";");
        if (token) c.protocolo = atoi(token);
        token = strtok(NULL, ";");
        if (token) strcpy(c.local, token);
        token = strtok(NULL, ";");
        if (token) strcpy(c.tipo, token);
        token = strtok(NULL, ";");
        if (token) strcpy(c.horario, token);
        topo++;
        pilha[topo] = c;
    }
    fclose(f);
    printf("\n[Sucesso] Dados carregados com sucesso de Trabalho B/dados_b.csv.\n");
}

/* MENU PRINCIPAL */
int main() {
    int opcao;
    do {
        printf("\n===================================\n");
        printf("    SISTEMA DE EMERGENCIA LIFO     \n");
        printf("===================================\n");
        printf("1. Registrar nova chamada (Push)\n");
        printf("2. Atender chamada (Pop)\n");
        printf("3. Consultar proxima chamada (Peek)\n");
        printf("4. Listar todas as chamadas\n");
        printf("5. Salvar dados (CSV)\n");
        printf("6. Carregar dados (CSV)\n");
        printf("0. Sair\n");
        printf("===================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch(opcao) {
            case 1: push(); break;
            case 2: pop(); break;
            case 3: peek(); break;
            case 4: listar(); break;
            case 5: salvarCSV(); break;
            case 6: carregarCSV(); break;
            case 0: printf("\nEncerrando sistema...\n"); break;
            default: printf("\n[Erro] Opcao invalida.\n");
        }
    } while(opcao != 0);
    return 0;
}