/* Criar Lista*/
TipoListaSimples * criaLista();

/* Verificar caracter e trocar o tipo da variável */
unsigned char verificaCaracter(char c); //Troca um char para um hexadecimal
unsigned char verificaCaracterInt(short int c); //Troca um short int para um hexadecimal

/* Inserção em Lista */

//Insere um char de qualquer tamanho em uma lista, onde cada algarismo corresponde uma posição
TipoListaSimples * insereFatorLista(char * string); 

void insereProduto(short int res, short int control, short int mask, TipoListaSimples ** elemento);
//Insere um uma lista um valor de tamanho máximo de 9

void insereValorProduto(short int res, short int control, short int mask, TipoListaSimples *lista, TipoListaSimples ** elemento);
//Insere posição vazia no início da lista
TipoListaSimples * insereInicioLista(TipoListaSimples *cabeca); 

//Insere posição no final da lista
TipoListaSimples * insereNoFim(TipoListaSimples * cabeca);

/* Exibir Listas */
void exibeListaInvertida(TipoListaSimples *cabeca, short int mask);
void escreverListaInvertida(TipoListaSimples *elemento, FILE *fp, short int mask);
/* Operações */

//Faz operação de multiplicação
TipoListaSimples * multiplicao(char * fator1, char * fator2);

//Desaloca uma lista
void destroiLista(TipoListaSimples **cabeca); 
