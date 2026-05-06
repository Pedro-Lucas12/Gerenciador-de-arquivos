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

//Função para criar tanto pasta(1) quanto arquivo(0) - Mateus
No* criar_no(char *nome_item, int tipo_pasta, No *pasta_atual){
    No *novo = (No*)malloc(sizeof(No));

    strcpy(novo->nome, nome_item);

    novo->eh_pasta = tipo_pasta;

    novo->esq = NULL;
    novo->dir = NULL;

    novo->pai = pasta_atual;

    return novo;
}

//Funcao para armazenar arquivos e pastas em ordem lexixografica - Mateus
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
No* comando_cd(No *corrente, char *destino); 
void comando_rm(No *corrente, char *alvo); 

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
        // Exibe o caminho (ex: -> ou -temp-teste2->) antes de ler
        mostrar_caminho(corrente); 
        
        fflush(stdin);
        gets(str); 
        
        // Limpando as strings antes de copiar para evitar lixo de memória
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
            printf("comando invalido\n");
        }
        
        // Precisa ter essa quebra de linha.
        printf("\n"); 

    } while(strcmp(cmd, "ex") != 0);

    return 0;
}



void mostrar_caminho(No *corrente) {
    // Se a pasta corrente for a raiz (a única que não tem pai), 
    // a regra é mostrar apenas "->"
    if (corrente->pai == NULL) {
        printf("->");
        return;
    }

    // Vetor de strings temporário para guardar os nomes das pastas.
    // Usei 1000 posições de segurança, já que não há limite de profundidade
    char *caminho[1000]; 
    int profundidade = 0;
    No *aux = corrente;

    // Laço que sobe a árvore de pai em pai. 
    // Ele para quando o pai for NULL (ou seja, quando o aux for a "raiz")
    while (aux->pai != NULL) {
        caminho[profundidade] = aux->nome;
        profundidade++;
        aux = aux->pai;
    }

    // Agora imprimimos o vetor de trás pra frente (do mais raso até o mais profundo)
    // Colocando o '-' antes de cada nome conforme o exemplo do pdf
    for (int i = profundidade - 1; i >= 0; i--) {
        printf("-%s", caminho[i]);
    }
    
    // E no final, a setinha indicando o local para digitar o comando
    printf("->");
}

void comando_ls(No *corrente) {
    // Para ver o conteúdo, precisamos "entrar" na pasta acessando o ponteiro esq (filho)
    No *aux = corrente->esq; 

    // Enquanto houver itens neste nível...
    while (aux != NULL) {
        
        // Verifica se é uma pasta para adicionar o traço "-" no final do nome
        if (aux->eh_pasta == 1) {
            printf("%s-\n", aux->nome);
        } else {
            // Se for arquivo, imprime apenas o nome
            printf("%s\n", aux->nome);
        }
        
        // Caminha para o próximo arquivo/pasta ao lado (irmão)
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
   
    return corrente; // Retorno temporário para não dar erro
}

void comando_rm(No *corrente, char *alvo) {
    
}
