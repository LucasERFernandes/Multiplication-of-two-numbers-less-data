#include "dados.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bib-projeto.h"


/* Máscaras */
char most = '\xf0';
char less = '\x0f';

/* Procura dentro de um unsigned char por valor que possa converter para short int */
short int retornaValorPosicao(TipoListaSimples ** elemento, short int * mask)
{
  //Esta função pega o valor do most ou do less, e caso seja necessário, modifica as variáveis de controle fora do escopo da função
    short int num;
    if(*mask == 0)
    {
      *mask = 1;
      if(((*elemento)->chave & less) != '\x0f') //sem o parenteses em volta do (cabeca->chave & less) nao funciona por algum motivo
        num = ((*elemento)->chave) & less;
      else
        return retornaValorPosicao(elemento,mask); //Caso Less esteja vazio, pega o valor dentro de most
    }
    else
    {
      num = ((*elemento)->chave >> 4) & less;
      *elemento = (*elemento)->prox; 
      *mask = 0;
    }
  return num;
}

/* Inserção em Lista */ 

TipoListaSimples * insereNoFim(TipoListaSimples * cabeca) //Insere um novo elemento no final de uma lista
{
  if(cabeca->prox == NULL)
    {
      TipoListaSimples * posicao = (TipoListaSimples *)malloc(sizeof(TipoListaSimples));
      if(posicao != NULL)
      {
        posicao->chave = '\x00';
        posicao->prox = NULL;
        cabeca->prox = posicao;
        return posicao;
      }
      else
        exit(0);
    }
  else
    insereNoFim(cabeca->prox);
}

void insereProduto(short int res, short int control, short int mask, TipoListaSimples ** elemento)
{
  //insere um número em uma posição e preserva o resto do conteúdo
  short int temp;

  if(mask == 0)
  {
    (*elemento)->chave >>= 4;
    (*elemento)->chave <<= 4;
    (*elemento)->chave += res % 10;

    if(control == -1)
    {
      (*elemento)->chave <<= 4;
      (*elemento)->chave += '\xf';
    }
  }
  else
  {
    temp =  (*elemento)->chave & less;
    (*elemento)->chave = res % 10;
    (*elemento)->chave <<= 4;
    (*elemento)->chave += temp;
  }
}

void insereValorProduto(short int res, short int control, short int mask, TipoListaSimples *lista, TipoListaSimples ** elemento)
{
  if(*elemento == NULL)
    *elemento = insereNoFim(lista);

  short int temp;

  if(mask == 0)
    res += ((*elemento)->chave & less);
  else
    res += ((*elemento)->chave >> 4);

  if(res > 9)
  {    
    insereProduto((res%10),control,mask,elemento);
    if(mask == 0)
    {
      mask = 1;
      insereValorProduto(res/10, control, mask, lista, elemento);
    }
    else
    {
      mask = 0;
      insereValorProduto(res/10, control, mask, lista, &((*elemento)->prox));
    }
  }
  else
  {
    if((mask == 0) && (control == 1)) //Se a multiplicação chegar ao final e for o último número a ser posto na lista, dá um recuo.
      insereProduto(res,-1,mask,elemento);
    else
      insereProduto(res,control,mask,elemento);
  }

}

TipoListaSimples * multiplicao(char * fator1, char * fator2)
{
  short int mask = 0;
  TipoListaSimples * listaFator1 = insereFatorLista(fator1);
  TipoListaSimples * listaFator2 = insereFatorLista(fator2);
  
  /*
  exibeListaInvertida(listaFator1->prox,0);
  printf("\n"); mask = 0;
  exibeListaInvertida(listaFator2->prox,0);
  printf("\n"); mask = 0;
  */
  
  TipoListaSimples * elementoFator1; // Percorre o primeiro fator
 
  TipoListaSimples * listaProduto = criaLista();
  TipoListaSimples * cabecaProduto = listaProduto; //Controla o espaçamento
  TipoListaSimples * elementoProduto; //Controla a casa atual para fazer a multiplicação

  short int num1, num2, res, maskF1 = 0, maskF2 = 0, maskP = 0, maskN = 0; 
  /* mask controla o most=1 e o less= 0 do char, caso seja -1, indica que o less está vazio*/

  listaFator2 = listaFator2->prox; //Percorre o segundo fator, multiplicando o primeiro

  while(listaFator2 != NULL)
  {
  /* mask controla o most=1 e o less=0 do char*/
  num2 = retornaValorPosicao(&listaFator2, &maskF2);

  elementoFator1 = listaFator1->prox;
  elementoProduto = cabecaProduto->prox;
  maskP = maskN;
    while(elementoFator1 != NULL)
    {
      //Funcao retornaValorPosicao fornece o número atual para a multiplicação
      num1 = retornaValorPosicao(&elementoFator1, &maskF1);
      res = num1*num2;

      if((listaFator2 == NULL) && (elementoFator1 == NULL))
        insereValorProduto(res, 1, maskP, listaProduto, &elementoProduto);
      else
        insereValorProduto(res, 0, maskP, listaProduto, &elementoProduto);  
      
      if(maskP == 1)
      {
        elementoProduto = elementoProduto->prox;
        maskP = 0;
      }
      else
        maskP = 1; 
      //maskP controla as posições dentro enquanto percorre uma lista
    }     
    if(maskN == 1)
    {
      cabecaProduto = cabecaProduto->prox;
      maskN = 0;
    }
    else
      maskN = 1; 
    //maskN controla as posições de começo para a multiplicação
  }
  destroiLista(&listaFator1);
  destroiLista(&listaFator2);

  return listaProduto;
}


/* Cria Lista */
TipoListaSimples * criaLista()
{
  TipoListaSimples * cabeca = (TipoListaSimples *)malloc(sizeof(TipoListaSimples));
  if(cabeca != NULL)
    {
      cabeca->chave= '\xff';
      cabeca->prox=NULL;
      //printf("Criou Lista Simples \n");
    }
    else
      exit(0);
  return cabeca;
}

/* Inserção em Lista */

TipoListaSimples * insereInicioLista(TipoListaSimples *cabeca)
{
  TipoListaSimples *posicao = (TipoListaSimples *)malloc(sizeof(TipoListaSimples));
  if(posicao != NULL)
  {
    posicao->chave = '\xff';
    posicao->prox = cabeca->prox;
    cabeca->prox = posicao;
  }
  else
    exit(0);

  return posicao;
}

TipoListaSimples * insereFatorLista(char * string)
{
  TipoListaSimples * cabeca = criaLista();
  TipoListaSimples * pos = insereInicioLista(cabeca);
  //Aviso: Para operações, é estabelecido o uso de short int.

  while(*string != '\0')
  {
    if(pos->chave == 255) //Isso indica que a posição está vazia
    {
      pos->chave = verificaCaracter(*string);
      if(*(string+1) == '\0')
      {
        /*
        Condição para ajustar a variável no caso de string tiver um número ímpar de variáveis.
        */
          pos->chave <<= 4;
          pos->chave += '\xf';
          //printf("Conteudo: %x - Less: %x\n",pos->chave >> 4, pos->chave & less);
      }
    }
    else
    {
      pos->chave<<=4;
      pos->chave += verificaCaracter(*string);
      //printf("Conteudo: %x\n",pos->chave);
      if(*(string+1) != '\0')
        /*
          Aqui cria uma nova posição da lista se necessário for, ou seja, se houver mais caracteres.
        */
        pos = insereInicioLista(cabeca);
    }
    string++;
  }
  return cabeca;
}

/* Verificar Caracter */

unsigned char verificaCaracter(char c)
{
  /*
    Para evitar problemas na conversão é mais válido trabalhar com hexadecimal.
  */
  if(c == '0')
    return '\x0';
  else if(c == '1')
    return '\x1';
  else if(c == '2')
    return '\x2';
  else if(c == '3')
    return '\x3';
  else if(c == '4')
    return '\x4';
  else if(c == '5')
    return '\x5';
  else if(c == '6')
    return '\x6';
  else if(c == '7')
    return '\x7';
  else if(c == '8')
    return '\x8';
  else if(c == '9')
    return '\x9';
}

/* Exibir Lista */

void exibeListaInvertida(TipoListaSimples *cabeca, short int mask)//Cabeca == Ponteiro para o primeiro elemento
{
  if(cabeca != NULL)
    {
      /* mask controla o most=1 e o less=0 do char*/
      if(mask == 0)
      {
        mask= 1;
        exibeListaInvertida(cabeca,mask);
        if((cabeca->chave & less) != '\x0f') //sem o parenteses em volta do (cabeca->chave & less) nao funciona por algum motivo
          printf("%x", cabeca->chave & less);
      }
      else
      {
        mask = 0;
        exibeListaInvertida(cabeca->prox,mask);
        printf("%x", cabeca->chave >> 4);
      }
    }
}

void escreverListaInvertida(TipoListaSimples *elemento, FILE *fp, short int mask) //Recebe o endereço do primeiro elemento e exibe ao contrário
{
  if(elemento != NULL)
    {
      if(mask == 0)
      {
        mask= 1;
        escreverListaInvertida(elemento,fp, mask);
        if((elemento->chave & less) != '\x0f')
          fprintf(fp, "%x", elemento->chave & less);
      }
      else
      {
        mask = 0;
        escreverListaInvertida(elemento->prox, fp, mask);
        fprintf(fp, "%x", elemento->chave >> 4);
      }
    }
}

/* Desalocar Lista */
void destroiLista(TipoListaSimples **cabeca) //Desaloca uma lista
{
  if(*cabeca != NULL)
    {
      destroiLista(&((*cabeca)->prox));
      free(*cabeca);
    }
  *cabeca = NULL;
}