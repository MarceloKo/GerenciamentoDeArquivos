#include<stdio.h>

typedef struct nodo{
char nome[15];
char tipo;
struct nodo *pai;
struct nodo *filho;
struct nodo *prox;
} Nodo;


Nodo *criarNodo(char nome[], char tipo){
Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
strcpy(novoNodo->nome,nome);
novoNodo->tipo = tipo;
novoNodo->pai = NULL;
novoNodo->filho = NULL;
novoNodo->prox = NULL;
return novoNodo;
}

Nodo *inserirNodo(Nodo *ligacao, char nome[], char tipo);
Nodo *trocaLigacao(Nodo *ligacao);
Nodo *apagar(Nodo *ligacao, char nome[]);
Nodo *entraNodo(Nodo *ligacao, char nome[]);
Nodo *entraPasta(Nodo *ligacao);
void MostrarLista(Nodo *ligacao);
void mostraLS(Nodo *ligacao);

int main(){
   int rep=0;
char op[6];
char nome[15], tipo;
Nodo *ligacao = criarNodo(" ", 'p');
do{
MostrarLista(ligacao);
printf(">");
scanf("%s",&op);
if(strcmp(op, "ma") == 0){

scanf("%s", &nome);
ligacao = inserirNodo(ligacao, nome, 'a');
}
else if(strcmp("mp", op) == 0){
scanf("%s", &nome);
ligacao = inserirNodo(ligacao, nome, 'p');
}
else if(strcmp("ls", op) == 0){
mostraLS(ligacao);
}
else if(strcmp("rm", op) == 0){
scanf("%s", &nome);
  ligacao = apagar(ligacao, nome);
}
else if(strcmp("cd", op) == 0){
scanf("%s", &nome);
if(strcmp("..", nome) == 0)
ligacao = entraPasta(ligacao);
else
ligacao = entraNodo(ligacao, nome);
}
else if(strcmp("ex", op) == 0){
printf("Saindo...\n");
rep=1;
}
else{
scanf("%s", &nome);
printf("Comando invalido!\n");
}
}while(rep==0);
return 0;
}


//Inserir oque deseja
Nodo *inserirNodo(Nodo *ligacao, char nome[], char tipo){
Nodo *novoNodo = criarNodo(nome, tipo);
novoNodo->pai= ligacao;
Nodo *lista = ligacao->filho;
if(lista == NULL){
lista = novoNodo;
novoNodo->prox = NULL;
}else if(strcmp(novoNodo->nome,lista->nome) <1){
novoNodo->prox = lista;
lista = novoNodo;
}else{
if(lista->prox == NULL){
lista->prox = novoNodo;
novoNodo->prox = NULL;
}else{
Nodo *aux = lista;
while(aux->prox != NULL && strcmp(novoNodo->nome,aux->prox->nome) > 0)
aux = aux->prox;
if(aux->prox == NULL){
novoNodo->prox = NULL;
aux->prox = novoNodo;
}else{
novoNodo->prox = aux->prox;
aux->prox = novoNodo;
}
}
}
ligacao->filho = lista;
printf("\n");
return ligacao;
}


//Liga o nodo anterior ao prox
Nodo *trocaLigacao(Nodo *ligacao){
Nodo *aux = ligacao;
if(aux->filho != NULL)
trocaLigacao(aux->filho);
if(aux->prox != NULL)
trocaLigacao(aux->prox);
free(aux);
printf("\n");
return ligacao;
}

//Apagar pasta ou arquirvo
Nodo *apagar(Nodo *ligacao, char nome[]){
Nodo *lista = ligacao;
if(lista->filho == NULL)
printf("Comando invalido!\n");
else{
Nodo *aux = lista->filho;
if(strcmp(aux->nome,nome)==0){
lista->filho = lista->filho->prox;
free(aux);
}else if(aux->prox == NULL){
printf("Comando invalido!\n");
}else{
while(strcmp(aux->prox->nome,nome)!=0 && aux->prox->prox != NULL)
aux = aux->prox;
if(strcmp(aux->prox->nome,nome)==0 && aux->prox->filho == NULL){
Nodo *temp = aux->prox;
aux->prox = temp->prox;
free(temp);
}else if(strcmp(aux->prox->nome,nome)==0 && aux->prox->filho != NULL){
Nodo *temp = aux->prox;
aux->prox = temp->prox;
trocaLigacao(temp->filho);
free(temp);
}else{
printf("Comando invalido!\n");
}
}
}
printf("\n");
return ligacao;
}


//MOSTRA ARQUIVOS E PASTAS CRIADAS
void mostraLS(Nodo *ligacao){
Nodo *lista = ligacao->filho;
while(lista != NULL){

if(lista->tipo == 'p')
printf("%s/\n", lista->nome);
else

printf("%s\n", lista->nome);
lista = lista->prox;
}
printf("\n");
}
//FIM

//ENTRAR NA PASTA
Nodo *entraNodo(Nodo *ligacao, char nome[]){
Nodo *lista = ligacao->filho;
if (lista == NULL)
printf("Comando invalido!\n");
else{
while(strcmp(lista->nome,nome)!=0 && lista->prox != NULL){
lista=lista->prox;
}
  if(lista->tipo!='p' || lista->prox == NULL){
if(strcmp(lista->nome,nome)==0 && lista->tipo == 'p' )
ligacao=lista;
  else
printf("Comando invalido!\n");
  }else
ligacao=lista;
}
printf("\n");
return ligacao;
}
//FIM

//SAIR DA PASTA
Nodo *entraPasta(Nodo *ligacao){
Nodo *lista = ligacao->pai;
// Volta 1 pasta
if (lista != NULL){
ligacao=lista;
printf("\n");}
        //Se vazio
else{
printf("Comando invalido!\n\n");

}
return ligacao;
}
//FIM


void MostrarLista(Nodo *ligacao){
Nodo *lista = ligacao;
if(lista->pai != NULL)
MostrarLista(lista->pai);

printf("%s/", lista->nome);
}
