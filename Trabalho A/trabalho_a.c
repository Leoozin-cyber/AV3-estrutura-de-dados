#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MUSICAS 100 // Capacidade máxima do vetor (Tratamento de estrutura cheia)

// =======================================================
// ESTRUTURA DE DADOS
// =======================================================

typedef struct {
    int id;
    char titulo[50];
    char artistar[50]; // Mantido como 'artistar' ou 'artista' conforme o padrão anterior
    int duracao; // Em segundos
    char genero[30];
} Musica;

// Vetor de structs e variável de controle de quantidade
Musica playlist[MAX_MUSICAS];
int totalMusicas = 0;

// =======================================================
// FUNÇÕES UTILITÁRIAS
// =======================================================

// Limpa o buffer do teclado de forma segura no GCC/VS Code
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Remove o '\n' deixado pelo fgets na string
void removerNovaLinha(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Verifica se um ID já existe no vetor
int idExiste(int id) {
    for (int i = 0; i < totalMusicas; i++) {
        if (playlist[i].id == id) {
            return 1; // ID já cadastrado
        }
    }
    return 0; // ID livre
}

// Retorna o índice da música no vetor baseado no ID (ajuda na busca, edição e exclusão)
int obterIndicePorId(int id) {
    for (int i = 0; i < totalMusicas; i++) {
        if (playlist[i].id == id) {
            return i; // Retorna a posição no vetor
        }
    }
    return -1; // Não encontrado
}

// =======================================================
// REQUISITOS OBRIGATÓRIOS DO SISTEMA
// =======================================================

// Cadastro / Inserção
void inserir() {
    // Tratamento de estrutura cheia
    if (totalMusicas >= MAX_MUSICAS) {
        printf("\nErro: A playlist esta cheia! Limite maximo de %d musicas atingido.\n", MAX_MUSICAS);
        return;
    }

    Musica m;
    printf("\n--- CADASTRAR NOVA MUSICA ---\n");
    printf("ID: ");
    if (scanf("%d", &m.id) != 1) {
        printf("Entrada invalida!\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    // Validação de entrada: ID único
    if (idExiste(m.id)) {
        printf("Erro: Ja existe uma musica cadastrada com o ID %d!\n", m.id);
        return;
    }

    printf("Titulo: ");
    fgets(m.titulo, 50, stdin);
    removerNovaLinha(m.titulo);

    printf("Artista: ");
    fgets(m.artistar, 50, stdin);
    removerNovaLinha(m.artistar);

    printf("Duracao (em segundos): ");
    scanf("%d", &m.duracao);
    limparBuffer();

    printf("Genero: ");
    fgets(m.genero, 30, stdin);
    removerNovaLinha(m.genero);

    // Insere no vetor na posição atual do contador e depois incrementa o contador
    playlist[totalMusicas] = m;
    totalMusicas++;

    printf("Musica cadastrada com sucesso!\n");
}

// Busca ou Consulta
void buscar() {
    // Tratamento de estrutura vazia
    if (totalMusicas == 0) {
        printf("\nA playlist esta vazia! Nao ha o que buscar.\n");
        return;
    }

    int idBusca;
    printf("\nDigite o ID da musica para buscar: ");
    scanf("%d", &idBusca);
    limparBuffer();

    int indice = obterIndicePorId(idBusca);

    if (indice != -1) {
        printf("\n--- MUSICA ENCONTRADA ---\n");
        printf("ID: %d\nTitulo: %s\nArtista: %s\nDuracao: %ds\nGenero: %s\n",
               playlist[indice].id, playlist[indice].titulo, playlist[indice].artistar,
               playlist[indice].duracao, playlist[indice].genero);
    } else {
        printf("Musica com ID %d nao encontrada.\n", idBusca);
    }
}

// Edição de registros
void editar() {
    if (totalMusicas == 0) {
        printf("\nA playlist esta vazia! Nao ha o que editar.\n");
        return;
    }

    int idEdit;
    printf("\nDigite o ID da musica para editar: ");
    scanf("%d", &idEdit);
    limparBuffer();

    int indice = obterIndicePorId(idEdit);

    if (indice != -1) {
        printf("\nEditando musica: %s (ID %d)\n", playlist[indice].titulo, playlist[indice].id);
        
        printf("Novo Titulo: ");
        fgets(playlist[indice].titulo, 50, stdin);
        removerNovaLinha(playlist[indice].titulo);

        printf("Novo Artista: ");
        fgets(playlist[indice].artistar, 50, stdin);
        removerNovaLinha(playlist[indice].artistar);

        printf("Nova Duracao (segundos): ");
        scanf("%d", &playlist[indice].duracao);
        limparBuffer();

        printf("Novo Genero: ");
        fgets(playlist[indice].genero, 30, stdin);
        removerNovaLinha(playlist[indice].genero);

        printf("Musica alterada com sucesso!\n");
    } else {
        printf("Musica com ID %d nao encontrada.\n", idEdit);
    }
}

// Remoção de registros
void excluir() {
    if (totalMusicas == 0) {
        printf("\nA playlist esta vazia! Nao ha o que excluir.\n");
        return;
    }

    int idDel;
    printf("\nDigite o ID da musica para excluir: ");
    scanf("%d", &idDel);
    limparBuffer();

    int indice = obterIndicePorId(idDel);

    if (indice != -1) {
        // Para excluir em um vetor sem deixar buracos:
        // Movemos todas as músicas que estão à frente da excluída uma posição para trás
        for (int i = indice; i < totalMusicas - 1; i++) {
            playlist[i] = playlist[i + 1];
        }
        
        // Reduzimos o total de músicas cadastradas
        totalMusicas--;
        printf("Musica ID %d excluida com sucesso!\n", idDel);
    } else {
        printf("Musica com ID %d nao encontrada para exclusao.\n", idDel);
    }
}

// Listagem dos dados
void listar() {
    // Tratamento de estrutura vazia
    if (totalMusicas == 0) {
        printf("\nA playlist esta vazia!\n");
        return;
    }

    printf("\n--- PLAYLIST ACTUAL (Total: %d) ---\n", totalMusicas);
    for (int i = 0; i < totalMusicas; i++) {
        printf("[%d] %s - %s (%ds) | %s\n", 
               playlist[i].id, playlist[i].titulo, playlist[i].artistar, 
               playlist[i].duracao, playlist[i].genero);
    }
}

// =======================================================
// ARQUIVO CSV (PERSISTÊNCIA)
// =======================================================

void salvarCSV() {
    FILE* arquivo = fopen("Trabalho A/dados_a.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }

    // Cabeçalho estrutural
    fprintf(arquivo, "id;titulo;artista;duracao;genero\n");

    // Grava os elementos do vetor até o limite do contador
    for (int i = 0; i < totalMusicas; i++) {
        fprintf(arquivo, "%d;%s;%s;%d;%s\n", 
                playlist[i].id, playlist[i].titulo, playlist[i].artistar, 
                playlist[i].duracao, playlist[i].genero);
    }

    fclose(arquivo);
    printf("\nDados gravados em 'dados_a.csv' com sucesso!\n");
}

void carregarCSV() {
    FILE* arquivo = fopen("Trabalho A/dados_a.csv", "r");
    if (arquivo == NULL) {
        printf("Nenhum arquivo 'dados_a.csv' localizado. Iniciando com playlist vazia.\n");
        return;
    }

    char linha[256];
    // Ignorar a linha do cabeçalho
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        fclose(arquivo);
        return;
    }

    totalMusicas = 0; // Reseta o contador para preencher do início

    while (fgets(linha, sizeof(linha), arquivo) != NULL && totalMusicas < MAX_MUSICAS) {
        Musica m;
        
        char* token = strtok(linha, ";");
        if (token) m.id = atoi(token);

        token = strtok(NULL, ";");
        if (token) strcpy(m.titulo, token);

        token = strtok(NULL, ";");
        if (token) strcpy(m.artistar, token);

        token = strtok(NULL, ";");
        if (token) m.duracao = atoi(token);

        token = strtok(NULL, "\n");
        if (token) strcpy(m.genero, token);

        playlist[totalMusicas] = m;
        totalMusicas++;
    }

    fclose(arquivo);
    printf("Dados carregados de 'dados_a.csv' com sucesso! (%d musicas carregadas)\n", totalMusicas);
}

// =======================================================
// MENU INTERATIVO
// =======================================================

int main() {
    int opcao = 0;

    // Carrega dados persistidos ao iniciar o programa
    carregarCSV();

    do {
        printf("\n===================================\n");
        printf("    SISTEMA DE PLAYLIST (VETOR)    \n");
        printf("===================================\n");
        printf("1. Inserir Musica\n");
        printf("2. Buscar Musica por ID\n");
        printf("3. Editar Musica\n");
        printf("4. Excluir Musica\n");
        printf("5. Listar Todas as Musicas\n");
        printf("6. Salvar Dados (CSV)\n");
        printf("0. Sair e Salvar\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        limparBuffer();

        switch (opcao) {
            case 1: inserir(); break;
            case 2: buscar(); break;
            case 3: editar(); break;
            case 4: excluir(); break;
            case 5: listar(); break;
            case 6: salvarCSV(); break;
            case 0:
                salvarCSV();
                printf("Programa encerrado com seguranca.\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}