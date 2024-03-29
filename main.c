#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TERMO,
    PARENTESE,
    SINAL
}TipoBloco;

typedef struct {
    int coef;
    int exp;
}Termo;

typedef struct bloco{
    TipoBloco tipo;
    union {
        Termo termo;
        char parentese;
        char sinal;
    };


  struct bloco *ant, *prox;
}Bloco;
 //Função de inserir Bloco (Insere Tanto termos quanto parentese)
void inserir (Bloco **head, int coef, int exp, char par){
  Bloco *temp,*ex;
  temp = (Bloco *) malloc(sizeof(Bloco));

  if(par == '(' || par == ')'){
    temp->tipo = PARENTESE;
    temp->parentese = par;
    temp->ant = temp->prox = NULL;
    if((*head)==NULL){
     (*head) = temp;
     return;
    }
    else{
      ex = (*head);
      while(ex->prox != NULL)
       ex = ex->prox;
      temp->ant = ex;
      ex->prox = temp;
      return;
    }
  }
  else if(par == '-' || par == '+'){
    temp->tipo = SINAL;
    temp->sinal = par;
    temp->ant = temp->prox = NULL;
    if((*head)==NULL){
     (*head) = temp;
     return;
    }
    else{
      ex = (*head);
      while(ex->prox != NULL)
       ex = ex->prox;
      temp->ant = ex;
      ex->prox = temp;
      return;
    }
  }
  else{
    temp->tipo = TERMO;
    temp->termo.coef = coef;
    temp->termo.exp = exp;
    temp->ant = temp->prox = NULL;
    if((*head)==NULL){
      (*head) = temp;
      return;
    }
    else{
      ex = (*head);
      while(ex->prox != NULL)
       ex = ex->prox;
      if(ex->tipo == PARENTESE){
        temp->ant = ex;
        ex->prox = temp;
        return;
      }
      else{
       while(ex->prox !=NULL && ex->prox->termo.exp < temp->termo.exp ){
        ex = ex->prox;
       }

       if(ex->prox == NULL){
         ex->prox = temp;
         temp->ant = ex;
         return;
       }
       else{
         temp->ant = ex;
         temp->prox = ex->prox;
         ex->prox->ant = temp;
         ex->prox = temp;
         return;
       }
      }
    }
  }
}
// A função de Impressão é basicamente aquela que voce ensinou na aula só que ela bota uns '+' caso o coeficiente for positivo.
void imprime(Bloco *head)
{
  if(head==NULL)return;
  switch (head->tipo){
  case PARENTESE:
   printf("%c", head->parentese);
   break;
  case SINAL:
   printf("%c", head->sinal);
   break;
  case TERMO:
   if(head->termo.exp == 0)
   printf("+%d ",head->termo.coef);
   else if (head->termo.coef > 0)
   printf("+%dX^%d ",head->termo.coef, head->termo.exp);
   else
   printf("%dX^%d ",head->termo.coef, head->termo.exp);
   break;
  }
  if(head->prox==NULL)return;
  imprime(head->prox);
}
// Essa função eu adicionei para usar em outras, não é uma função que o usuário poderá usar diretamente.
int tam(Bloco **p){
  int x=1;
  Bloco *temp = *p;
  if(*p==NULL)return x=0;
  while ( temp -> prox != NULL){
    temp = temp -> prox;
    x++;
  }
  return x;
}
// Função que remove os termos em uma determinada posição:
int Remove (Bloco **c, int x){
  Bloco *temp, *ex;
  int i,ta;
  if(x<0){
  printf("Posição Inválida\n\n");
  return 0;
  }
  ta = tam(c);
  if ( x >= ta ) return 0;
  temp =(*c);
  if(x==0){
    if((*c)->prox == NULL){
      (*c) = NULL;
      temp->prox = temp->ant = NULL;
      free(temp);
      return 1;
    }
    else{
    (*c) = (*c)->prox;
    (*c)->ant = NULL;
    temp->ant = temp->prox = NULL;
    free(temp);
    return 1;
    }
  }
  
  else
   for (i=0; i<(x-1); i++)
     temp=temp->prox;
   ex=temp->prox;
   if((temp->prox->prox)!= NULL){
    temp->prox=temp->prox->prox;
    temp->prox->ant=temp;
    ex->prox = ex->ant = NULL;
    free(ex);
    return 1;
}
   else
   temp->prox=NULL;
   ex->prox = ex->ant = NULL;
   free(ex);
   return 1;
  }

void acha_parentese(Bloco **head){
  
}
// Função que remove os parenteses, que ainda não funciona
int tira_parentese(Bloco **head){
  Bloco *temp, *perc;

}
//Função que reduz os termos de mesmo expoente
void reduz(Bloco **head){
  if(*head == NULL)return;
  Bloco *temp, *ex;
  temp = (*head);
  ex = temp->prox;
  while (temp ->prox != NULL){
    if(temp->tipo == PARENTESE){
      temp = temp->prox;
      ex = temp->prox;
    }
    if(ex->tipo == TERMO){
      if(temp->termo.exp == ex->termo.exp){
      temp->termo.coef = temp->termo.coef + ex->termo.coef;
      ex = ex->ant;
      Remove(&ex, 1);
      }
      else{
        if(ex->prox != NULL && ex->prox->tipo == TERMO)
        ex = ex->prox;
        else{
          if(temp->prox == NULL || temp->prox->tipo == PARENTESE) break;
          temp = temp->prox;
        }
      }
    }
    else
    break;
    if(temp->prox != NULL){
     temp = temp->prox;
     ex = temp->prox;
    }
  }
}
int Verifica(Bloco **head){
  Bloco *temp, *ex;
  int x = 0,y;
  temp = *head;
  while(temp != NULL){
    if(temp->tipo == PARENTESE && temp->parentese == '(')
    x++;
    if(temp->tipo == PARENTESE && temp->parentese == ')')
    x--;
    temp = temp->prox;
  }
   return x;
}
void Resolve_par(Bloco **head){
  Bloco *temp, *ex, *aux;
  if(*head == NULL) return;
  temp = *head;
  while(temp->tipo != PARENTESE)
   temp = temp->prox;
  ex = temp->prox;
  if(ex->tipo == TERMO)
   while(ex->prox->tipo == TERMO)
    ex = ex->prox;
 
  if(temp->ant != NULL && temp->ant->tipo == SINAL &&temp->ant->sinal == '-'){
    if(temp->prox->prox->tipo != PARENTESE){
      ex = temp;
     while(ex->prox->tipo != PARENTESE){
      ex->prox->termo.coef = (ex->prox->termo.coef)*(-1);
      ex = ex->prox;
     }
    }
    else
     temp->prox->termo.coef = (temp->prox->termo.coef)*(-1);
     if(temp->ant->ant == NULL){
      aux = (*head);
      (*head) = (*head)->prox;
      (*head)->ant = NULL;
      aux->ant = aux->prox = NULL;
      free(aux);
      return;
     }
     else{
       (*head) = (*head)->prox;
      aux = temp->ant;
      aux->ant->prox = aux->prox;
      aux->ant = aux->prox = NULL;
      free(aux);
      return;
     }
  }
}
void parentese(Bloco **head){
  Bloco *temp;
 temp = *head;
 while(temp->prox != NULL){
  temp = temp->prox;
  if(temp->tipo == SINAL && temp->prox->prox->parentese != ')')
   Resolve_par(&temp);
 }
}
// Função que exclui os polinomio todo, fiz com recursao
void Remove_tudo(Bloco **head,int tamanho)
{
 if(tamanho < 0) return;
    Remove(head,tamanho);
    Remove_tudo(head,tamanho-1);
}

int main() {
  char str;
  int ver;
  Bloco *head,*sss;
  int coef,exp,x=0, posi, i;
  head = NULL;
  //ESPAÇO PARA FUNÇAO DE DIGITAR OS BAGULHO
  while (x!=5){
   printf("Escolha Uma opção:\n");
   printf("1 - Inserir Termo.\n2 - Inserir Parentese\n");
   printf("3 - Inserir Sinal do Parentese\n4 - Sair\n");
   scanf("%d", &x);
   switch(x){
    case 1:
     printf("Digite o Coeficiente e o Expoente:\n");
     scanf("%d",&coef);
     scanf("%d",&exp);
     inserir(&head,coef,exp,'0');
     break;
    case 2:
     printf("Digite o Parentese:\n");
     scanf(" %c", &str);
     inserir(&head,0,0,str);
     break;
    case 3:
     printf("Digite o Operando:\n");
     scanf(" %c", &str);
     inserir (&head,0,0,str);
     break;
    case 4:
     x = 5;
     break;
   }
   system("clear");
  } 
 printf("\n");
 imprime(head);
 if(Verifica(&head) != 0){
 printf("Os parenteses estão incorretos");
 return 0;
 }
 printf("\n");
 sss = head;
 while(x != 6){
  printf("\n==============\n");
  printf("   MENU\n");
  printf("\n==============\n");
  printf("O que deseja fazer?\n");
  printf("1 - Remover posição\n");
  printf("2 - Excluir o polinomio\n");
  printf("3 - Imprimir o polinomio na tela\n");
  printf("4 - Reduzir os termos\n");
  printf("5 - Tirar o sinal dos Parenteses\n");
  printf("6 - Sair do Menu e fechar o programa\n");
  scanf(" %d",&x);
  switch(x){
    case 1:
     printf("Digite  a posição:\n");
     scanf(" %d",&posi);
     Remove(&head, posi);
     break;
    case 2:
     Remove_tudo(&head,tam(&head));
     if(head == NULL)
      printf("Lista Vazia\n");
     break;
    case 3:
     imprime(head);
     break;
    case 4:
     reduz(&head);
     break;
    case 5:
     Resolve_par(&head);
     imprime(head);
     printf("Ainda há parenteses com sinal?\n1 - Sim\n2 - Não");
     scanf("%d",&ver);
     if(ver == 2) break;
     printf("Digite a posição do sinal\n");
     scanf("%d", &ver);
     for( i=0; i < ver; i++)
      sss = sss->prox;
     Resolve_par(&sss);
     imprime(head);
     break;
    case 6:
    x = 6; 
     
  }
  system("clear");
 }
return 0;
}
