#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[50];
    char sexo;
    int idade;
}Familiar;

typedef struct no{
    Familiar familiar;
    struct no *pai, *mae;
}No;

Familiar lerFAmiliar(){
    Familiar f;
    printf("Digite o nome da pessoa: ");
    fgets(f.nome, 49, stdin);
    printf("Qual o sexo da pessoa? ");
    scanf("%c", &f.sexo);
    printf("Digite a idade: ");
    scanf("%d", &f.idade);
    return f;
}

void imprimirFamiliar(Familiar f){
    printf("Nome: %s\tSexo: %c\tIdade: %d\n", f.nome, f.sexo, f.idade);
}

void inserirFamiliar(No **raiz, Familiar f){
    No *aux = *raiz;
    char parente = 'M';
    while(aux){
        scanf("%c", &parente);
        if(parente == aux->familiar.sexo)
            raiz = &aux->pai;
        else
            raiz = &aux->mae;
        aux = *raiz;
    }
    aux = malloc(sizeof(No));
    aux->familiar = f;
    aux->pai = NULL;
    aux->mae = NULL;
    *raiz = aux;
}

No* buscarFamiliar(No *raiz, char nome[]){
    while(raiz){
        if(strcmp(nome,raiz->familiar.nome)==0) {
            return raiz;
        }
        buscarFamiliar(raiz->mae,nome);
        buscarFamiliar(raiz->pai,nome);
    }
    return NULL;
}

int altura(No *raiz){
    if(raiz == NULL){
        return -1;
    }
    else{
        int esq = altura(raiz->pai);
        int dir = altura(raiz->mae);
        if(esq > dir)
            return esq + 1;
        else
            return dir + 1;
    }
}

int quantidadeNos(No *raiz){
    if(raiz==NULL) {
        return 0;
    } else {
        return 1 + quantidadeNos(raiz->pai) + quantidadeNos(raiz->mae);
    }
}

int quantidadeFolhas(No *raiz){
    if(raiz==NULL) {
        return 0;
    } else if(raiz->pai==NULL && raiz->mae==NULL) {
        return 1;
    }
    else
        return quantidadeFolhas(raiz->pai)+quantidadeFolhas(raiz->mae);
}

No* removerFamiliar(No *raiz, char nome[]) {
    if(raiz==NULL){
        printf("Valor não encontrado!\n");
        return NULL;
    } else {
        if(strcmp(raiz->familiar.nome,nome)==0) {
            free(raiz);
            printf("Elemento folha removido: %s !\n", nome);
            return NULL;
        }
    }
}

void imprimirFamiliarRecursivo(No *raiz){ // 50 25 30 100
    if(raiz){
        imprimirFamiliar(raiz->familiar);
        imprimirFamiliarRecursivo(raiz->pai);
        imprimirFamiliarRecursivo(raiz->mae);
    }
}

void menu(No *busca, No *raiz) {
    int opcao, valor;
    char nome[50];

    do{
        printf("\n0 - Sair\n1 - Inserir\n2 - Imprimir\n3 - Buscar\n4 - Altura\n5 - Tamanho\n6 - Folhas\n7 - Remover\n");
        scanf("%d", &opcao);
        scanf("%c");

        switch(opcao){
            case 1:
                inserirFamiliar(&raiz,lerFAmiliar());
                break;
            case 2:
                imprimirFamiliarRecursivo(raiz);
                printf("\n");
                break;
            case 3:
                printf("\nDigite o nome a ser procurado: ");
                fgets(nome,49,stdin);
                busca = buscarFamiliar(raiz,nome);
                if(busca){
                    printf("\n\tValor encontrado:\n");
                    imprimirFamiliar(busca->familiar);
                }
                else {
                    printf("\nValor nao encontrado!\n");
                }
                break;
            case 4:
                printf("\nAltura da arvore: %d\n", altura(raiz));
                break;
            case 5:
                printf("\nQuantidade de nos: %d\n", quantidadeNos(raiz));
                break;
            case 6:
                printf("\nQuantidade folhas: %d\n", quantidadeFolhas(raiz));
                break;
            case 7:
                printf("\nDigite o nome a ser removido: ");
                fgets(nome,49,stdin);
                raiz = removerFamiliar(raiz,nome);
                break;
            default:
                if(opcao != 0) {
                    printf("Opção inválida");
                }
        }
    }while(opcao!=0);
}

int main(){

    No *busca, *raiz = NULL;

    menu(busca,raiz);

    return 0;
}
