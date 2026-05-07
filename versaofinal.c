#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Definição da Estrutura 
typedef struct no {
    char nome[100];
    int eh_pasta;     // 1 se for pasta, 0 se for arquivo
    struct no *pai;   // Aponta para a pasta acima 
    struct no *esq;   // Aponta para o conteúdo de dentro 
    struct no *dir;   // Aponta para o item ao lado 
} No;

// Função para criar no, tanto pasta(1) quanto arquivo(0) - Mateus
No* criar_no(char *nome_item, int tipo_pasta, No *pasta_atual){
    No *novo = (No*)malloc(sizeof(No));

    strcpy(novo->nome, nome_item);

    novo->eh_pasta = tipo_pasta;

    novo->esq = NULL;
    novo->dir = NULL;

    novo->pai = pasta_atual;

    return novo;
}

// Funcao para armazenar arquivos e pastas em ordem lexixografica - Mateus
void insercao_ordenada(No *corrente, No *novo){
    if(corrente->esq == NULL){
        corrente->esq = novo;
        return;
    }

    if(strcmp(novo->nome, corrente->esq->nome) < 0){
        novo->dir = corrente->esq;
        corrente->esq = novo;
        return;
    }

    No *anterior = corrente->esq;
    No *atual_busca = anterior->dir;

    while(atual_busca != NULL && strcmp(novo->nome, atual_busca->nome) > 0){
        anterior = atual_busca;
        atual_busca = atual_busca->dir;
    }

    novo->dir = atual_busca;
    anterior->dir = novo;
}

// 2. Função copiaStr
void copiarStr(char dest[], char orig[], int ini, int fim){
    int i=0, tam=strlen(orig);
    while(i+ini<tam && i<fim-ini && orig[i+ini] != '\0' && orig[i+ini] != '\n'){
        dest[i] = orig[i+ini];
        i++;
    }
    dest[i] = '\0';
}

// 3. Funçoes para implementar
void mostrar_caminho(No *corrente); 
void comando_ls(No *corrente);
void comando_ma(No *corrente, char *nome_arquivo);
void comando_mp(No *corrente, char *nome_pasta);
No* comando_cd(No *corrente, char *destino); 
void comando_rm(No *corrente, char *alvo);
void liberar_arvore(No* no); // Protótipo da função auxiliar do RM

int main() {
    // Inicializando a "pasta raiz" do sistema
    No *raiz = (No*)malloc(sizeof(No));
    strcpy(raiz->nome, "raiz");
    raiz->eh_pasta = 1;
    raiz->pai = NULL;
    raiz->esq = NULL;
    raiz->dir = NULL;

    No *corrente = raiz; 
    
    // variaveis da string completa, do comando e do nome do arquivo/pasta.
    char str[100], cmd[3], par[100];

    do {
        mostrar_caminho(corrente); 
        
        if (fgets(str, sizeof(str), stdin) == NULL) break; 
        
        cmd[0] = '\0';
        par[0] = '\0';

        copiarStr(cmd, str, 0, 2);
        copiarStr(par, str, 3, 100); 

        if (strcmp(cmd, "ex") == 0) {
            printf("sistema encerrado\n");
            break; 
        }
        else if (strcmp(cmd, "ls") == 0) {
            comando_ls(corrente);
        }
        else if (strcmp(cmd, "ma") == 0) {
            comando_ma(corrente, par);
        }
        else if (strcmp(cmd, "mp") == 0) {
            comando_mp(corrente, par);
        }
        else if (strcmp(cmd, "cd") == 0) {
            corrente = comando_cd(corrente, par); 
        }
        else if (strcmp(cmd, "rm") == 0) {
            comando_rm(corrente, par);
        }
        else {
            printf("comando invalido");
        }
        
        printf("\n"); 

    } while(strcmp(cmd, "ex") != 0);

    return 0;
}


// --- IMPLEMENTAÇÕES DOS COMANDOS ---

void mostrar_caminho(No *corrente) {
    // Se a pasta corrente for a raiz precisa mostrar só ->
    if (corrente->pai == NULL) {
        printf("->");
        return;
    }

    // Vetor temporário pra guardar o nome das pastas
    char *caminho[1000]; // 1000 por segurança
    int profundidade = 0;
    No *aux = corrente;

    // Laço para subir a arvore. Para qnd chega no NULL
    while (aux->pai != NULL) {
        caminho[profundidade] = aux->nome;
        profundidade++;
        aux = aux->pai;
    }

    // Imprime o vetor ao contrario.
    for (int i = profundidade - 1; i >= 0; i--) {
        printf("-%s", caminho[i]);
    }
    
    // seta para indicar onde escrever o comando
    printf("->");
}

void comando_ls(No *corrente) {
    // Acesso do ponteiro esquerdo para entrar na pasta
    No *aux = corrente->esq; 
    int primeiro = 1; // Flag para controlar as quebras de linha internas

    // loop para ver se ainda tem algo no nivel
    while (aux != NULL) {
        
        // Pula uma linha apenas se não for o primeiro item impresso
        if (!primeiro) {
            printf("\n");
        }
        
        if (aux->eh_pasta == 1) {
            printf("%s-", aux->nome);
        } else {
            // Imprime so o nome se for um arquivo
            printf("%s", aux->nome);
        }
        
        primeiro = 0;
        aux = aux->dir; 
    }
}

void comando_ma(No *corrente, char *nome_arquivo) {
   No *novo = criar_no(nome_arquivo, 0, corrente);
   insercao_ordenada(corrente, novo);
}

void comando_mp(No *corrente, char *nome_pasta) {
   No *novo = criar_no(nome_pasta, 1, corrente);
   insercao_ordenada(corrente, novo);
}

No* comando_cd(No *corrente, char *destino) {
    // Caso 1: Acessar a pasta do nível hierárquico superior (cd ..)
    if (strcmp(destino, "..") == 0) {
        if (corrente->pai != NULL) {
            return corrente->pai;
        } else {
            // Se tentar dar cd .. na raiz, é comando inválido
            printf("comando invalido");
            return corrente;
        }
    }

    // Caso 2: Entrar em uma subpasta (cd <pasta>)
    No* temp = corrente->esq;
    
    while (temp != NULL) {
        // Verifica se o nome bate
        if (strcmp(temp->nome, destino) == 0) {
            // Se for pasta entra, se for arquivo é erro
            if (temp->eh_pasta == 1) {
                return temp;
            } else {
                printf("comando invalido");
                return corrente;
            }
        }
        temp = temp->dir;
    }
    
    // Se não encontrou 
    printf("comando invalido"); 
    return corrente;
}

void liberar_arvore(No* no) {
    if (no == NULL) return;
    liberar_arvore(no->esq); 
    liberar_arvore(no->dir); 
    free(no);
}

void comando_rm(No *corrente, char *alvo) {
    No* atual = corrente->esq;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->nome, alvo) == 0) {
            // Remove o nó da lista encadeada de irmãos
            if (anterior == NULL) {
                // O nó a ser removido é o primeiro filho
                corrente->esq = atual->dir;
            } else {
                // O nó está no meio ou fim da lista de irmãos
                anterior->dir = atual->dir;
            }
            
            atual->dir = NULL; // separa o nó do resto da árvore
            
            // Apaga o conteúdo interno e depois o próprio nó
            liberar_arvore(atual->esq); 
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->dir;
    }
    
    // Se não encontrou o arquivo/pasta com esse nome
    printf("comando invalido"); 
}