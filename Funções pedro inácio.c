\* parte 5 \*

void comando_cd(No** pasta_corrente, char* nome_destino) {
    // Caso 1: Acessar a pasta do nível hierárquico superior (cd ..)
    if (strcmp(nome_destino, "..") == 0) {
        if ((*pasta_corrente)->pai != NULL) {
            *pasta_corrente = (*pasta_corrente)->pai;
        }
        return;
    }

    // Caso 2: Entrar em uma subpasta (cd <pasta>)
    No* temp = (*pasta_corrente)->filho;
    
    while (temp != NULL) {
        // Verifica se o nome bate e se realmente é uma pasta
        if (strcmp(temp->nome, nome_destino) == 0 && temp->is_pasta == 1) {
            *pasta_corrente = temp;
            return;
        }
        temp = temp->irmao;
    }
    
    // Se não encontrou ou digitou errado
    printf("comando invalido\n"); 
}


\* parte 6\*

// Função auxiliar recursiva para apagar todo o conteúdo de uma pasta
void liberar_arvore(No* no) {
    if (no == NULL) return;
    liberar_arvore(no->filho); // Libera os filhos (conteúdo da pasta)
    liberar_arvore(no->irmao); // Libera os irmãos
    free(no);
}

void comando_rm(No* pasta_corrente, char* nome_alvo) {
    No* atual = pasta_corrente->filho;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->nome, nome_alvo) == 0) {
            // Remove o nó da lista encadeada de irmãos
            if (anterior == NULL) {
                // O nó a ser removido é o primeiro filho
                pasta_corrente->filho = atual->irmao;
            } else {
                // O nó está no meio ou fim da lista de irmãos
                anterior->irmao = atual->irmao;
            }
            
            atual->irmao = NULL; // Isola o nó (e sua subárvore) do resto da árvore
            
            // Apaga o conteúdo interno (se for pasta) e depois o próprio nó
            liberar_arvore(atual->filho); 
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->irmao;
    }
    
    // Se não encontrou o arquivo/pasta com esse nome
    printf("comando invalido\n"); 
}

\*parte 7\*

// Dentro da sua função main() ou no seu loop de interpretação de comandos:

if (strcmp(comando, "ex") == 0) {
    printf("sistema encerrado\n");
    
    // Utilizado como critério de parada para o laço
    break; // Ou return 0; dependendo de como sua main está estruturada
}