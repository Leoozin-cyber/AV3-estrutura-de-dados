#include <stdio.h>  
#include <stdlib.h> 
#include <string.h>  
#include <ctype.h> 

/* / / CONSTANTES GERAIS / / */ 
#define TAM_FILA_NORMAL 50       /* capacidade maxima da fila normal */  
#define TAM_FILA_PREFERENCIAL 50 /* capacidade maxima da fila preferencial*/  
#define TAM_HORARIO 10           /* tamanho maximo do horario (HH:MM) */ 

/* / / ESTRUTURA DA SENHA / / */ 
typedef struct { 
    int numero; /* numero (identificador) unico da senha*/  
    char tipo;  /* 'N' = normal | 'P' = preferencial */  
    char horarioChegada[TAM_HORARIO]; 
} Senha; 

/* / / FILA NORMAL SIMPLES (vetor de struct, FIFO linear) / / */ 
typedef struct { 
    Senha dados[TAM_FILA_NORMAL];  
    int inicio; 
    int fim; /* proxima posicao livre */  
    int quantidade;  
} FilaNormal; 

/* / / FILA PREFERENCIAL CIRCULAR SIMPLES (vetor de struct) / / */ 
typedef struct { 
    Senha dados[TAM_FILA_PREFERENCIAL];  
    int inicio;  
    int fim;  
    int quantidade; 
} FilaPreferencial; 

/* / / PROTOTIPOS / / */ 
void inicializarFilaNormal(FilaNormal *f); 
void inicializarFilaPreferencial(FilaPreferencial *f); 
int filaNormalVazia(FilaNormal *f); 
int filaNormalCheia(FilaNormal *f); 
int inserirFilaNormal(FilaNormal *f, Senha s);  
int removerFilaNormal(FilaNormal *f, Senha *s); 
int removerPorNumeroFilaNormal(FilaNormal *f, int numero);  
Senha* buscarPorNumeroFilaNormal(FilaNormal *f, int numero);                  
void listarFilaNormal(FilaNormal *f); 

int filaPreferencialVazia(FilaPreferencial *f);  
int filaPreferencialCheia(FilaPreferencial *f);  
int inserirFilaPreferencial(FilaPreferencial *f, Senha s);  
int removerFilaPreferencial(FilaPreferencial *f, Senha *s);  
int removerPorNumeroFilaPreferencial(FilaPreferencial *f, int numero);  
Senha* buscarPorNumeroFilaPreferencial(FilaPreferencial *f, int numero);  
void listarFilaPreferencial(FilaPreferencial *f); 

void cadastrarSenha(FilaNormal *fn, FilaPreferencial *fp, int *proximoNumero);  
void chamarProximaSenha(FilaNormal *fn, FilaPreferencial *fp, int *contadorNormais);  
void buscarSenha(FilaNormal *fn, FilaPreferencial *fp);  
void listarTodos(FilaNormal *fn, FilaPreferencial *fp);  
void cancelarSenha(FilaNormal *fn, FilaPreferencial *fp); 
void salvarCSV(FilaNormal *fn, FilaPreferencial *fp);
void carregarCSV(FilaNormal *fn, FilaPreferencial *fp, int *proximoNumero);

int lerInteiro(const char *mensagem);  
void lerTexto(const char *mensagem, char *destino, int tamanho);  
char lerTipo(const char *mensagem);  
void pausar(void); 
void exibirMenu(void); 

/* / / FUNCAO PRINCIPAL / / */ 
int main(void) {  
    FilaNormal fn; 
    FilaPreferencial fp;  
    int proximoNumero = 1;  
    int contadorNormais = 0; 
    int opcao;

    inicializarFilaNormal(&fn); 
    inicializarFilaPreferencial(&fp);  
    
    do {  
        exibirMenu();  
        opcao = lerInteiro("Escolha uma opcao: ");  
        switch (opcao) {  
            case 1:  
                cadastrarSenha(&fn, &fp, &proximoNumero);  
                break;  
            case 2:  
                chamarProximaSenha(&fn, &fp, &contadorNormais);  
                break;  
            case 3:  
                buscarSenha(&fn, &fp);  
                break;  
            case 4:  
                listarTodos(&fn, &fp);  
                break;  
            case 5:  
                cancelarSenha(&fn, &fp);  
                break;  
            case 6:
                salvarCSV(&fn, &fp);
                break;
            case 7:
                carregarCSV(&fn, &fp, &proximoNumero);
                break;
            case 0:  
                printf("\nEncerrando o sistema. Ate logo!\n");  
                break;  
            default:  
                printf("\nOpcao invalida! Tente novamente.\n");  
                pausar();  
                break;  
        }  
    } while (opcao != 0);  
    return 0;  
} 

/* / / IMPLEMENTACAO - INICIALIZACAO / / */ 
void inicializarFilaNormal(FilaNormal *f) { 
    f->inicio = 0; 
    f->fim = 0; 
    f->quantidade = 0; 
} 

void inicializarFilaPreferencial(FilaPreferencial *f) { 
    f->inicio = 0; 
    f->fim = 0; 
    f->quantidade = 0; 
} 

/* / / IMPLEMENTACAO - FILA NORMAL SIMPLES / / */ 
int filaNormalVazia(FilaNormal *f) { return (f->quantidade == 0); } 
int filaNormalCheia(FilaNormal *f) { return (f->quantidade == TAM_FILA_NORMAL); } 

int inserirFilaNormal(FilaNormal *f, Senha s) { 
    if (filaNormalCheia(f)) { return 0; } 
    if (f->quantidade == 0) {  
        f->inicio = 0;  
        f->fim = 0; 
    }  
    f->dados[f->fim] = s; 
    f->fim++; 
    f->quantidade++; 
    return 1;  
} 

int removerFilaNormal(FilaNormal *f, Senha *s) { 
    if (filaNormalVazia(f)) { return 0; } 
    *s = f->dados[f->inicio]; 
    f->inicio++; 
    f->quantidade--;  
    if (f->quantidade == 0) {  
        f->inicio = 0;  
        f->fim = 0; 
    }  
    return 1;  
} 

int removerPorNumeroFilaNormal(FilaNormal *f, int numero) { 
    int i, posicao = -1; 
    int indiceReal; 
    if (filaNormalVazia(f)) { return 0; }  
    for (i = 0; i < f->quantidade; i++) {  
        indiceReal = f->inicio + i;  
        if (f->dados[indiceReal].numero == numero) {  
            posicao = i;  
            break;  
        } 
    }  
    if (posicao == -1) { return 0; }  
    for (i = posicao; i < f->quantidade - 1; i++) {  
        f->dados[f->inicio + i] = f->dados[f->inicio + i + 1]; 
    }  
    f->quantidade--; 
    f->fim--;  
    if (f->quantidade == 0) {  
        f->inicio = 0;  
        f->fim = 0; 
    }  
    return 1;  
} 

Senha* buscarPorNumeroFilaNormal(FilaNormal *f, int numero) { 
    int i, indiceReal; 
    for (i = 0; i < f->quantidade; i++) {  
        indiceReal = f->inicio + i;  
        if (f->dados[indiceReal].numero == numero) {  
            return &f->dados[indiceReal];  
        } 
    } 
    return NULL;  
} 

void listarFilaNormal(FilaNormal *f) { 
    int i, indiceReal; 
    printf("\n--- FILA NORMAL (%d senha(s)) ---\n", f->quantidade);  
    if (filaNormalVazia(f)) {  
        printf("(fila normal vazia)\n");  
        return; 
    }  
    printf("%-8s %-6s %-10s\n", "SENHA", "TIPO", "CHEGADA"); 
    for (i = 0; i < f->quantidade; i++) {  
        indiceReal = f->inicio + i;  
        printf("N%03d     %-6c %-10s\n",  
               f->dados[indiceReal].numero,  
               f->dados[indiceReal].tipo,  
               f->dados[indiceReal].horarioChegada); 
    }  
} 

/* / / IMPLEMENTACAO - FILA PREFERENCIAL CIRCULAR SIMPLES / / */ 
int filaPreferencialVazia(FilaPreferencial *f) { return (f->quantidade == 0); } 
int filaPreferencialCheia(FilaPreferencial *f) { return (f->quantidade == TAM_FILA_PREFERENCIAL); } 

int inserirFilaPreferencial(FilaPreferencial *f, Senha s) { 
    if (filaPreferencialCheia(f)) { return 0; } 
    f->dados[f->fim] = s; 
    f->fim = (f->fim + 1) % TAM_FILA_PREFERENCIAL; 
    f->quantidade++; 
    return 1;  
} 

int removerFilaPreferencial(FilaPreferencial *f, Senha *s) { 
    if (filaPreferencialVazia(f)) { return 0; } 
    *s = f->dados[f->inicio]; 
    f->inicio = (f->inicio + 1) % TAM_FILA_PREFERENCIAL; 
    f->quantidade--; 
    return 1;  
} 

int removerPorNumeroFilaPreferencial(FilaPreferencial *f, int numero) { 
    int i, posicao = -1; 
    int indiceReal; 
    int origemA, destinoA; 
    if (filaPreferencialVazia(f)) { return 0; }  
    for (i = 0; i < f->quantidade; i++) {  
        indiceReal = (f->inicio + i) % TAM_FILA_PREFERENCIAL;  
        if (f->dados[indiceReal].numero == numero) {  
            posicao = i;  
            break;  
        } 
    }  
    if (posicao == -1) { return 0; }  
    for (i = posicao; i < f->quantidade - 1; i++) {  
        destinoA = (f->inicio + i) % TAM_FILA_PREFERENCIAL;  
        origemA  = (f->inicio + i + 1) % TAM_FILA_PREFERENCIAL;  
        f->dados[destinoA] = f->dados[origemA]; 
    }  
    f->quantidade--; 
    f->fim = (f->fim - 1 + TAM_FILA_PREFERENCIAL) % TAM_FILA_PREFERENCIAL;  
    return 1;  
} 

Senha* buscarPorNumeroFilaPreferencial(FilaPreferencial *f, int numero) { 
    int i, indiceReal; 
    for (i = 0; i < f->quantidade; i++) {  
        indiceReal = (f->inicio + i) % TAM_FILA_PREFERENCIAL;  
        if (f->dados[indiceReal].numero == numero) {  
            return &f->dados[indiceReal];  
        } 
    } 
    return NULL;  
} 

void listarFilaPreferencial(FilaPreferencial *f) { 
    int i, indiceReal; 
    printf("\n--- FILA PREFERENCIAL (%d senha(s)) ---\n", f->quantidade);  
    if (filaPreferencialVazia(f)) {  
        printf("(fila preferencial vazia)\n");  
        return; 
    }  
    printf("%-8s %-6s %-10s\n", "SENHA", "TIPO", "CHEGADA"); 
    for (i = 0; i < f->quantidade; i++) {  
        indiceReal = (f->inicio + i) % TAM_FILA_PREFERENCIAL;  
        printf("P%03d     %-6c %-10s\n",  
               f->dados[indiceReal].numero,  
               f->dados[indiceReal].tipo,  
               f->dados[indiceReal].horarioChegada); 
    }  
} 

/* / / OPERACOES GERAIS DO SISTEMA / / */ 
void cadastrarSenha(FilaNormal *fn, FilaPreferencial *fp, int *proximoNumero) { 
    Senha nova; 
    char tipo; 
    int sucesso; 
    printf("\n=== EMISSAO DE NOVA SENHA ===\n");  
    tipo = lerTipo("Tipo da senha (N = normal, P = preferencial): ");  
    lerTexto("Horario de chegada (ex: 14:30): ", nova.horarioChegada, TAM_HORARIO);  
    nova.tipo = tipo;  
    
    if (tipo == 'N' && filaNormalCheia(fn)) {  
        printf("\n[ERRO] A fila NORMAL esta cheia!\n");  
        pausar();  
        return; 
    } 
    if (tipo == 'P' && filaPreferencialCheia(fp)) {  
        printf("\n[ERRO] A fila PREFERENCIAL esta cheia!\n");  
        pausar();  
        return; 
    }  
    nova.numero = *proximoNumero; 
    (*proximoNumero)++;  
    
    if (tipo == 'N') {  
        sucesso = inserirFilaNormal(fn, nova); 
    } else {  
        sucesso = inserirFilaPreferencial(fp, nova); 
    }  
    if (sucesso) {  
        printf("\nSenha emitida com sucesso: %c%03d\n", tipo, nova.numero); 
    } else {  
        printf("\n[ERRO] Nao foi possivel emitir a senha.\n");  
        (*proximoNumero)--; 
    }  
    pausar();  
} 

void chamarProximaSenha(FilaNormal *fn, FilaPreferencial *fp, int *contadorNormais) { 
    Senha s; 
    int deveChamarPreferencial; 
    printf("\n=== CHAMAR PROXIMA SENHA ===\n");  
    if (filaNormalVazia(fn) && filaPreferencialVazia(fp)) {  
        printf("\n[INFO] Nao ha senhas pendentes em nenhuma das filas.\n");  
        pausar();  
        return; 
    }  
    deveChamarPreferencial = (*contadorNormais >= 2) && !filaPreferencialVazia(fp);  
    if (deveChamarPreferencial) {  
        removerFilaPreferencial(fp, &s);  
        *contadorNormais = 0;  
        printf("\n[PREFERENCIAL] Chamando senha P%03d (chegada: %s).\n", s.numero, s.horarioChegada); 
    } else if (!filaNormalVazia(fn)) {              
        removerFilaNormal(fn, &s);  
        (*contadorNormais)++;  
        printf("\n[NORMAL] Chamando senha N%03d (chegada: %s).\n", s.numero, s.horarioChegada); 
    } else if (!filaPreferencialVazia(fp)) {  
        removerFilaPreferencial(fp, &s);  
        *contadorNormais = 0;  
        printf("\n[PREFERENCIAL] Chamando senha P%03d (chegada: %s).\n", s.numero, s.horarioChegada);  
        printf("(fila normal estava vazia; atendimento seguiu pela preferencial)\n"); 
    }  
    pausar();  
} 

void buscarSenha(FilaNormal *fn, FilaPreferencial *fp) { 
    int numero; 
    Senha *encontrada; 
    printf("\n=== BUSCAR SENHA POR NUMERO ===\n"); 
    numero = lerInteiro("Informe o numero da senha: ");  
    encontrada = buscarPorNumeroFilaNormal(fn, numero); 
    if (encontrada != NULL) {  
        printf("\nSenha encontrada na FILA NORMAL:\n");  
        printf("Senha: N%03d | Tipo: %c | Chegada: %s\n", encontrada->numero, encontrada->tipo, encontrada->horarioChegada);  
        pausar();  
        return; 
    }  
    encontrada = buscarPorNumeroFilaPreferencial(fp, numero); 
    if (encontrada != NULL) {  
        printf("\nSenha encontrada na FILA PREFERENCIAL:\n");  
        printf("Senha: P%03d | Tipo: %c | Chegada: %s\n", encontrada->numero, encontrada->tipo, encontrada->horarioChegada);  
        pausar();  
        return; 
    }  
    printf("\n[INFO] Nenhuma senha encontrada com o numero %d.\n", numero); 
    pausar();  
} 

void listarTodos(FilaNormal *fn, FilaPreferencial *fp) { 
    int opcao; 
    printf("\n=== LISTAGEM DE SENHAS ===\n"); 
    printf("1 - Listar fila normal\n"); 
    printf("2 - Listar fila preferencial\n"); 
    printf("3 - Listar ambas as filas\n"); 
    opcao = lerInteiro("Escolha uma opcao: ");  
    switch (opcao) {  
        case 1:  
            listarFilaNormal(fn);  
            break;  
        case 2:  
            listarFilaPreferencial(fp);                  
            break;  
        case 3:  
            listarFilaPreferencial(fp);  
            listarFilaNormal(fn);  
            break;  
        default:  
            printf("\nOpcao invalida.\n");  
            break; 
    }  
    pausar();  
} 

void cancelarSenha(FilaNormal *fn, FilaPreferencial *fp) { 
    int numero; 
    int removidoNormal, removidoPreferencial; 
    printf("\n=== CANCELAR SENHA ===\n"); 
    numero = lerInteiro("Informe o numero da senha a cancelar: ");  
    removidoPreferencial = removerPorNumeroFilaPreferencial(fp, numero); 
    if (removidoPreferencial) {  
        printf("\nSenha P%03d removida da fila PREFERENCIAL com sucesso.\n", numero);  
        pausar();  
        return; 
    }  
    removidoNormal = removerPorNumeroFilaNormal(fn, numero); 
    if (removidoNormal) {  
        printf("\nSenha N%03d removida da fila NORMAL com sucesso.\n", numero);  
        pausar();  
        return; 
    }  
    printf("\n[INFO] Nenhuma senha encontrada com o numero %d. Nada foi removido.\n", numero); 
    pausar();  
} 

void salvarCSV(FilaNormal *fn, FilaPreferencial *fp) {
    FILE *f = fopen("Trabalho C/dados_c.csv", "w");
    if (f == NULL) {
        printf("\n[ERRO] Nao foi possivel abrir o arquivo Trabalho C/dados_c.csv para escrita.\n");
        pausar();
        return;
    }
    fprintf(f, "numero;tipo;horarioChegada\n");
    for (int i = 0; i < fn->quantidade; i++) {
        Senha s = fn->dados[(fn->inicio + i)];
        fprintf(f, "%d;%c;%s\n", s.numero, s.tipo, s.horarioChegada);
    }
    for (int i = 0; i < fp->quantidade; i++) {
        Senha s = fp->dados[(fp->inicio + i) % TAM_FILA_PREFERENCIAL];
        fprintf(f, "%d;%c;%s\n", s.numero, s.tipo, s.horarioChegada);
    }
    fclose(f);
    printf("\n[SUCESSO] Dados salvos em Trabalho C/dados_c.csv com sucesso!\n");
    pausar();
}

void carregarCSV(FilaNormal *fn, FilaPreferencial *fp, int *proximoNumero) {
    FILE *f = fopen("Trabalho C/dados_c.csv", "r");
    if (f == NULL) {
        printf("\n[ERRO] Arquivo Trabalho C/dados_c.csv nao encontrado.\n");
        pausar();
        return;
    }
    char linha[256];
    fgets(linha, sizeof(linha), f); 
    
    inicializarFilaNormal(fn);
    inicializarFilaPreferencial(fp);
    int maiorNumero = 0;

    while (fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = 0;
        Senha s;
        char *token = strtok(linha, ";");
        if (token) s.numero = atoi(token);
        token = strtok(NULL, ";");
        if (token) s.tipo = token[0];
        token = strtok(NULL, ";");
        if (token) strcpy(s.horarioChegada, token);

        if (s.numero > maiorNumero) maiorNumero = s.numero;

        if (s.tipo == 'N') inserirFilaNormal(fn, s);
        else inserirFilaPreferencial(fp, s);
    }
    fclose(f);
    *proximoNumero = maiorNumero + 1;
    printf("\n[SUCESSO] Dados carregados de Trabalho C/dados_c.csv com sucesso!\n");
    pausar();
}

/* / / FUNCOES UTILITARIAS DE ENTRADA / / */ 
int lerInteiro(const char *mensagem) { 
    char buffer[100]; 
    int valor, valido; 
    do {  
        printf("%s", mensagem);  
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) { return 0; }  
        valido = (sscanf(buffer, "%d", &valor) == 1);  
        if (!valido) { printf("Entrada invalida! Digite um numero inteiro.\n"); }  
    } while (!valido);  
    return valor;  
} 

void lerTexto(const char *mensagem, char *destino, int tamanho) { 
    char buffer[200]; 
    int valido; 
    do {  
        printf("%s", mensagem);  
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {  
            destino[0] = '\0';  
            return;  
        }  
        buffer[strcspn(buffer, "\r\n")] = '\0';  
        {  
            int i, j = 0;  
            char limpo[200];  
            for (i = 0; buffer[i] != '\0'; i++) {  
                if (buffer[i] != ';') { limpo[j++] = buffer[i]; }  
            }  
            limpo[j] = '\0';  
            strncpy(buffer, limpo, sizeof(buffer) - 1);  
            buffer[sizeof(buffer) - 1] = '\0';  
        }  
        valido = (strlen(buffer) > 0);  
        if (!valido) { printf("Entrada invalida! O campo nao pode ser vazio.\n"); }  
    } while (!valido);  
    strncpy(destino, buffer, tamanho - 1); 
    destino[tamanho - 1] = '\0';  
} 

char lerTipo(const char *mensagem) { 
    char buffer[20]; 
    char tipo; 
    int valido; 
    do {  
        printf("%s", mensagem);  
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) { return 'N'; }  
        tipo = (char)toupper((unsigned char)buffer[0]);  
        valido = (tipo == 'N' || tipo == 'P');  
        if (!valido) { printf("Tipo invalido! Digite N para normal ou P para preferencial.\n"); }  
    } while (!valido);  
    return tipo;  
} 

void pausar(void) {  
    printf("\nPressione ENTER para continuar...");  
    getchar(); 
} 

/* / / MENU / / */ 
void exibirMenu(void) {  
    printf("\nSISTEMA DE ATENDIMENTO BANCARIO\n");  
    printf(" 1 - Emitir nova senha\n");  
    printf(" 2 - Chamar proxima senha\n");  
    printf(" 3 - Buscar senha por numero\n");  
    printf(" 4 - Listar senhas\n");  
    printf(" 5 - Cancelar senha por numero\n");  
    printf(" 6 - Salvar senhas (CSV)\n");
    printf(" 7 - Carregar senhas (CSV)\n");
    printf(" 0 - Sair\n");  
}