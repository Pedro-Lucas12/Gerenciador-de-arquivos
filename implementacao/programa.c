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
    
}

void comando_ls(No *corrente) {
   
}

void comando_ma(No *corrente, char *nome_arquivo) {
   
}

void comando_mp(No *corrente, char *nome_pasta) {
   
}

No* comando_cd(No *corrente, char *destino) {
   
    return corrente; // Retorno temporário para não dar erro
}

void comando_rm(No *corrente, char *alvo) {
    
}