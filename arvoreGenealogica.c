#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[50];
    char sexo;
    int idade;
}Familiar;

typedef struct irmao {
    char nome[50];
    int idade;
    struct irmao *fila, *prox;
} Irmao;

typedef struct no{
    Familiar familiar;
    struct no *pai, *mae;
}No;

Familiar lerFamiliar(){
    Familiar f;
    printf("Digite o nome da pessoa: ");
    fgets(f.nome, 49, stdin);
    printf("Qual o sexo da pessoa? ");
    scanf("%c", &f.sexo);
    printf("Digite a idade: ");
    scanf("%d", &f.idade);
    return f;
}

void inserirIrmao() {
    buscarIrmao();

    Irmao *i = (Irmao*)malloc(sizeof(Irmao));
    printf("Qual o nome do irmão? ");
    fgets(i.nome, 49, stdin);
    printf("Qual o sexo da pessoa? ");
    scanf("%d", &i.idade);
    return i;

    if(fila==NULL) {
        fila = p;
    } else {
        Pessoa *filaAux = fila;
        while(filaAux->prox!=NULL) {
            filaAux = filaAux->prox;
        }
        filaAux->prox = p;
    }
}

Irmao* buscarIrmao(No *raiz, nome[]) {
    if(raiz==NULL){
        return NULL;
    }
    if(strcmp(nome,raiz->familiar.nome)==0) {
        return raiz;
    }else{
        raiz = raiz->pai;
        buscarPai(raiz, nome);
        raiz = raiz->mae;
        buscarMae(raiz,nome);
    }
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

void inserirPai(No *filho, Familiar f){
    No *aux = filho;
    No *pai = malloc(sizeof(No));
    pai->familiar = f;
    pai->pai = NULL;
    pai->mae = NULL;
    aux->pai = pai;
}

void inserirMae(No *filho, Familiar f){
    No *aux = filho;
    No *mae = malloc(sizeof(No));
    mae->familiar = f;
    mae->pai = NULL;
    mae->mae = NULL;
    aux->mae = mae;
}

No* buscarPai(No *raiz, char nome[]){
    if(raiz==NULL){
        return NULL;
    }
    if(strcmp(nome,raiz->familiar.nome)==0) {
        return raiz;
    }else{
        raiz = raiz->pai;
        buscarPai(raiz, nome);
    }
}

No* buscarMae(No *raiz, char nome[]){
    if(raiz==NULL){
        return NULL;
    }
    if(strcmp(nome,raiz->familiar.nome)==0) {
        return raiz;
    }else{
        raiz = raiz->mae;
        buscarPai(raiz, nome);
    }
}

int geracoes(No *raiz){
    if(raiz == NULL){
        return -1;
    }
    else{
        int esq = geracoes(raiz->pai);
        int dir = geracoes(raiz->mae);
        if(esq>dir)
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
        if(strcmp(raiz->familiar.nome,nome)==0) {
            printf("Elemento folha removido: %s !\n", nome);
            return NULL;
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
    char sexo;
    char nome[50];

    do{
        printf("\n0 - Sair\n1 - Iniciar Arvore\n2 - Imprimir\n3 - Buscar\n4 - Quantidade de gerações\n5 - Tamanho\n6 - Folhas\n7 - Remover\n8 - Inserir Pai\n9 - Inserir Mae\n");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 1:
                inserirFamiliar(&raiz,lerFamiliar());
                break;
            case 2:
                imprimirFamiliarRecursivo(raiz);
                printf("\n");
                break;
            case 3:
                printf("\nDigite o sexo da Pessoa: ");
                scanf("%c", &sexo);
                getchar();
                printf("\nDigite o nome a ser procurado: ");
                fgets(nome,49,stdin);
                if(sexo=='M' || sexo=='m'){
                    busca = buscarPai(raiz,nome);
                }else if(sexo=='F' || sexo=='f'){
                    busca = buscarMae(raiz,nome);
                }else{
                    busca=NULL;
                }
                if(busca){
                    imprimirFamiliar(busca->familiar);
                }
                else {
                    printf("\nValor nao encontrado!\n");
                }
                break;
            case 4:
                printf("\Quantidade de gerações da família: %d\n", geracoes(raiz));
                break;
            case 5:
                printf("\nQuantidade de nos: %d\n", quantidadeNos(raiz));
                break;
            case 6:
                printf("\nQuantidade folhas: %d\n", quantidadeFolhas(raiz));
                break;
            case 7:
                printf("\nDigite o sexo da Pessoa: ");
                scanf("%c", &sexo);
                getchar();
                printf("\nDigite o nome da Pessoa: ");
                fgets(nome,49,stdin);
                if(sexo=='M'){
                    busca = buscarPai(raiz,nome);
                } else if(sexo=='F') {
                    busca = buscarMae(raiz, nome);
                } else {
                    busca=NULL;
                }
                if(busca){
                    removerFamiliar(raiz,nome);
                }
                break;
            case 8:
                printf("\nDigite o sexo do filho: ");
                scanf("%c", &sexo);
                getchar();
                printf("\nDigite o nome do filho: ");
                fgets(nome,49,stdin);
                if(sexo=='M'){
                    busca = buscarPai(raiz,nome);
                }else if(sexo=='F'){
                    busca = buscarMae(raiz, nome);
                }else{
                    busca=NULL;
                }
                if(busca){
                    printf("\n\tValor encontrado:\n");
                    inserirPai(busca, lerFAmiliar());
                }
                else {
                    printf("\nValor nao encontrado!\n");
                }
                break;
            case 9:
                printf("\nDigite o sexo do filho: ");
                scanf("%c", &sexo);
                getchar();
                printf("\nDigite o nome do filho: ");
                fgets(nome,49,stdin);
                if(sexo=='M'){
                    busca = buscarPai(raiz,nome);
                }else if(sexo=='F'){
                    busca = buscarMae(raiz, nome);
                }else{
                    busca=NULL;
                }
                if(busca){
                    printf("\n\tValor encontrado:\n");
                    inserirMae(busca, lerFAmiliar());
                }
                else {
                    printf("\nValor nao encontrado!\n");
                }
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
