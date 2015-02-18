#include "dados.h"
#include <stdio.h>
#include <stdlib.h>
#include "bib-projeto.h"


int main()
{
  char * fator1, *fator2;
  FILE *fp, *fpr;
 
  fp = fopen("resultado", "a"); //Abre o arquivo para escrita.
  if (fp == NULL) {
    printf("Nao foi possivel abrir um resultado.txt para a escrita.\n");
    exit(0);
  }
  

  fpr = fopen("parametros", "r"); //Abre o arquivo para leitura.
  if (fpr == NULL)
  {
    printf("Nao foi possivel abrir um arquivo chamado parametros.txt para a leitura. \n");
    exit(0);
  }

  while(fscanf(fpr, "%ms %ms", &fator1, &fator2) != EOF) //Leitura de cada elemento por linha.
  {
    TipoListaSimples * listaProduto = multiplicao(fator1,fator2);
    escreverListaInvertida(listaProduto->prox, fp, 0);
    fprintf(fp, "\n");
    //exibeListaInvertida(listaProduto->prox,0);
    destroiLista(&listaProduto); //Desaloca Lista recebida
    free(fator1);
    free(fator2);
  }
  fclose(fpr);
  fclose(fp);
	return 0;
}