#include "TravelBooking.h"
#include <stdio.h>
#include <stdlib.h>

struct data {
    int dia;
    int mes;
    int ano;

    bool operator<(const data& outro) {
        if (ano < outro.ano){
            return 1;
        }
        if (ano == outro.ano){
            if (mes < outro.mes){
                return 1;
            }
            if (mes == outro.mes && dia <= outro.dia){
                return 1;
            }
        }
        return 0;
    }
    bool operator==(const data& outro) {
        if (ano == outro.ano && mes == outro.mes && dia == outro.dia){
            return 1;
        }
        return 0;
    }
};

struct voo {
    int codigo;
    char *origem;
    char *destino;
};

struct no_voo {
    Voo *voo;
    struct no_voo *proximo;
};

struct lista_voo {
    struct no_voo *primeiro;
};

struct reserva{
    int codigo;
    Data *data_viagem;
    Passageiro *passageiro;
    Voo *voo;
    Assento assento;
};

struct agenda {
    Reserva *reserva;
    Agenda *esq;
    Agenda *dir;
};

struct trecho {
    Reserva *reserva;
    struct trecho *proximo;
};

struct viagem {
    struct trecho *trechos;
};

struct tabela_viagem {
    int tamanho;
    Viagem *tabela_hash;
};


//"agenda" é como nó -> struct q contem reserva, esq e dir


//retorna 0 caso a data nova seja menor que a antiga (esquerda) e 1 caso a data nova seja maior ou igual a antiga (direita).
int checaData(Data anterior, Data nova){

    if (anterior.ano < nova.ano){
        return 1;
    }
    if (anterior.ano == nova.ano){
        if (anterior.mes < nova.mes){
            return 1;
        }
        if (anterior.mes == nova.mes && anterior.dia <= nova.dia){
            return 1;
        }
    }
    return 0;
}

Data hoje, *aux;
Data aux;


/* Cria ABB */
Agenda *IniciaABB(Reserva primeira){

    //Dados Invalidos: (Data da viagem < Data de hoje)
    if (checaData(hoje, primeira.data_viagem) == 0){
        return NULL;
    }

//Happy path: (completamente perdido na questao dos ponteiros)
    Agenda *raiz = (Agenda *)malloc(sizeof(Agenda));
    raiz->reserva = &primeira;
    raiz->esq = NULL;
    raiz->dir = NULL;
    return raiz;
}



/* Procura a agenda pela data. Retorna a agenda caso a busca obtenha sucesso ou NULL
 * em caso contrário. */


Agenda *BuscaAgenda(Agenda *raiz, Data busca) {

    if (raiz != NULL) {
        if (raiz->reserva->data_viagem == aux){
            return raiz;
        }

        int checagemData;
        Data inicial;
        inicial = *raiz->reserva->data_viagem;

        checagemData  = checaData(busca,inicial);


        if (checagemData == 0) {
            return BuscaAgenda(raiz->esq, busca);
        } else {
            return BuscaAgenda(raiz->dir, busca);
        }
    }

    return NULL;
}




/* Adiciona uma agenda à esquerda(caso for menor) ou à direita(caso for maior ou igual) do no raiz. Retorna a raiz da árvore
 * resultante ou NULL raiz e o nó sejam NULL */

Agenda *InsereAgenda(Agenda *raiz, Agenda *nova) {
    int *restricao, *restricao2;
    restricao = BuscaInd(raiz,nova->reserva->codigo);
    restricao2 = BuscaVoo(raiz,nova->reserva->voo->codigo);


    if (restricao == 1){
        return NULL;
    }

    if (restricao2 == 1){
        return NULL;
    }
    if (raiz == NULL) {
        return nova;
    }

    if (checaData(raiz->reserva->data_viagem, nova->reserva->data_viagem) == 1){
        raiz->dir = InsereAgenda(raiz->dir, nova);
    } else {
        raiz->esq = InsereAgenda(raiz->esq, nova);
    }
    return raiz;

}


/*Realiza uma busca linear pelo código de reserva*/

Agenda *BuscaCodigo(Agenda *raiz, int reserva){
    if (raiz == NULL){
        return NULL;
    }
    if (raiz->reserva->codigo == reserva){
        return raiz;
    }
    Agenda *esq = BuscaCodigo(raiz->esq,reserva);
    Agenda *dir = BuscaCodigo(raiz->dir,reserva);
    if(esq != NULL){
        return esq;
    }
    return dir;
}

/*Remove Agenda com um dado código de reserva*/
bool RemoverAgenda() {
    if (raiz == NULL) {
        return NULL;
    }
    if (raiz->reserva->codigo == reserva) {
        return raiz;
    }
    Agenda *esq = BuscaCodigo(raiz->esq, reserva);
    Agenda *dir = BuscaCodigo(raiz->dir, reserva);
    if (esq != NULL) {
        return esq;
    }
    return dir;
}


/*Busca por (i) identificador do passageiro e código do voo*/

Agenda *BuscaI(Agenda *raiz, Passageiro passageiro, int codigo){
    if (raiz == NULL){
        return NULL;
    }
    if (raiz->reserva->codigo == codigo && raiz->reserva->passageiro == passageiro){
        return raiz;
    }
    Agenda *esq = BuscaI(raiz->esq,passageiro, codigo);
    Agenda *dir = BuscaI(raiz->dir,passageiro, codigo);
    if(esq != NULL){
        return esq;
    }
    return dir;
}

/*Busca por (ii) identificador do passageiro e data da viagem.*/

Agenda *BuscaII(Agenda *raiz, Passageiro passageiro, Data data){
    if (raiz == NULL){
        return NULL;
    }
    if (raiz->reserva->data_viagem == data && raiz->reserva->passageiro == passageiro){
        return raiz;
    }
    Agenda *esq = BuscaII(raiz->esq,passageiro,data);
    Agenda *dir = BuscaII(raiz->dir,passageiro,data);
    if(esq != NULL){
        return esq;
    }
    return dir;
}

/*Busca por identificador do passageiro*/

int *BuscaInd(Agenda *raiz, int codigo){

    if (raiz->reserva->codigo = codigo){
        return 1;
    }

    if(raiz != NULL){
        BuscaInd(raiz->esq,codigo);
        BuscaInd(raiz->dir,codigo);
    }
}

/*Busca por identificador do voo*/

int *BuscaVoo(Agenda *raiz, int voo){

    if (raiz->reserva->voo->codigo = voo){
        return 1;
    }

    if(raiz != NULL){
        BuscaVoo(raiz->esq,voo);
        BuscaVoo(raiz->dir,voo);
    }
}


/*Edita a reserva*/

Agenda *Edita(Agenda *raiz, int codEditar){
    Agenda *edita;
    edita = BuscaCodigo(raiz,codEditar);
    removeCodigo(raiz,codEditar);

    Data *dataNova;
    int ano, mes, dia;


    printf("Digite a data no formato ano,mes,dia");
    //scanfs

    dataNova->ano = ano;
    dataNova->mes = mes;
    dataNova->dia = dia;

    edita->reserva->passageiro; //esperar tabela hash

    edita->reserva->voo; //esperar tabela hash


    edita->reserva->data_viagem = dataNova;
    edita->reserva->assento; //esperar tabela hash

    //codigo permanece o mesmo


    InsereAgenda(raiz, edita);
    /*I- Achar agenda; II- Criar Cópia; III- Remover Agenda original, IV- Inserir cópia modificada*/
    /*boooool*/
}
//=-=-=-=-=-=-=-=-=-=-=-=Lista encadeada de passageiros=-=-=-=-=-=

struct passageiro {
  int id;
  char *nome;
  char *endereco;
};

struct no_passageiro {
  Passageiro *passageiro;
  struct no_passageiro *proximo;
};

struct lista_passageiro {
  struct no_passageiro *primeiro;
};

typedef struct no_passageiro No_Passagueiro;

/* Aloca espaço em memória e retorna uma Lista */
ListaPassageiro *lista_cria(){
  ListaPassageiro *lista = (ListaPassageiro *)malloc(sizeof(ListaPassageiro));
  lista->primeiro = NULL;
  return lista;
}

/* Libera a memória da lista previamente criada e atribui NULL ao ponteiro lista.
 * Retorna 1 caso seja possível fazer a liberação e 0 caso a lista informada seja NULL. */
int lista_liberar(ListaPassageiro **lista){
  if(lista != NULL){
    if((*lista)->primeiro != NULL){
      No_Passagueiro *aux = (*lista)->primeiro;
      do{
        passageiro_libera(&aux->passageiro);
        aux = aux->proximo;
      }while(aux != NULL);
    }
    free(*lista);
    *lista = NULL;
    return 1;
  }
  return 0;
}

/* Insere um passageiro na lista.
 *  Retorna 1 se foi possível adicionar, 0 caso já exista um passageiro com o mesmo id (nesse caso, o passageiro não pode ser adicionado) e -1 caso a lista ou passageiro sejam NULL */
int lista_inserir(ListaPassageiro *lista, Passageiro *passageiro){
  if(lista == NULL || passageiro==NULL){
    return -1;
  }

  if(lista->primeiro != NULL){
    int id_passagueiro;
    char nome[50];
    char endereco[50];
    passagueiro_acessa(passageiro, &id_passagueiro,nome,endereco);
    Passageiro *passageiro_aux = passageiro_busca(lista,id_passagueiro);
    if(passageiro_aux != NULL){
      return 0;
    }
  }

  if(lista->primeiro == NULL){
    No_Passagueiro *novo = (No_Passagueiro *)malloc(sizeof(No_Passagueiro));
    novo->passageiro = passageiro;
    novo->proximo = NULL;
    lista->primeiro = novo;
  }else{
    No_Passagueiro *ultimo = lista->primeiro;
    while (ultimo->proximo != NULL){
      ultimo = ultimo->proximo;
    }

    No_Passagueiro *novo = (No_Passagueiro *)malloc(sizeof(No_Passagueiro));
    novo->passageiro = passageiro;
    novo->proximo = NULL;
    ultimo->proximo = novo;
  }
  return 1;
}

/* Busca passageiro pelo número de id. Retorna o passageiro se este estiver na
 * lista e NULL caso contrário, isto é, (i) lista vazia; (ii) não exista passageiro com a id fornecida;
 * ou (iii) a lista seja NULL */
ListaPassageiro *lista_busca(ListaPassageiro *lista, int ID){
  if(lista != NULL && lista->primeiro != NULL){

    int passageiro_id;
    char nome[50];
    char endereco[30];

    No_Passagueiro *aux = lista->primeiro;
    do{
      passagueiro_acessa(aux->passageiro, &passageiro_id, nome, endereco);
      if(ID == passageiro_id){
        return aux->passageiro;
      }
      aux = aux->proximo;
    }while(aux != NULL);
  }

  return NULL;
}

/* Remove um passagueiro na lista. Retorna o passagueiro ou NULL caso a lista esteja vazia*/
ListaPassageiro *lista_retirar(ListaPassageiro *lista){
  if(lista == NULL || lista->primeiro == NULL){
    return NULL;
  }
  Passageiro *passageiro = lista->primeiro->passageiro;
  lista->primeiro = lista->primeiro->proximo;
  return passageiro;
}

/* Verifica se a lista está vazia. Retorna 1 se a lista estiver vazia, 0 caso não
 * esteja vazia e -1 se a lista for NULL*/
int lista_vazia(ListaPassageiro* lista){
  if (lista==NULL){
    return -1;
  }
  if (lista->primeiro==NULL){
    return 1;
  }
  return 0;
}

/* Recupera o primeiro passageiro da fila. Retorna o passageiro ou NULL caso a lista esteja vazia ou seja NULL */
Passageiro *lista_primeiro(ListaPassageiro* lista){
  if(lista == NULL || lista->primeiro->passageiro ==NULL){
    return NULL;
  }
  return lista->primeiro->passageiro;
}


/*=-=-=-=-=-=-=-=-=-=-=-=-= funções para a lista de passageiros=-=-=-=-=-=-=-=-*/

int verificar_parametros(int passageiro_id, char *nome, char *endereco){
    if(passageiro_id < 0 || nome == NULL || endereco == NULL){
        return -1;
    }

    if(strlen(nome) > 50 || strlen(endereco) > 30){
        return -1;
    }

    return 1;
}

/* Aloca e retorna um aluno com os dados passados por parâmetro. Porém, para os
 * casos em que (i) pelo menos um dos parâmetros sejam nulos <-1, NULL, NULL>; e
 * (ii) o tamanho das strings nome e curso sejam maiores que os da especificação
 * (50 e 30, respectivamente), a função deve retornar NULL. */
Passageiro *passageiro_novo(int id, char *nome,char *endereco){
  if(verificar_parametros(id,nome,endereco)== -1){
    return NULL;
  }
  if(strcmp(nome,endereco) == 0){
    return NULL;
  }
  Passageiro *novo_passageiro = (Passageiro *)malloc(sizeof(Passageiro));
  novo_passageiro->id = id;
  strcpy(novo_passageiro->nome, nome);
  strcpy(novo_passageiro->endereco, endereco);

  return novo_passageiro;
}

/* Libera a memória de um aluno previamente criado e atribui NULL ao aluno. */
void passageiro_liberar(Passageiro **passageiro){
  if(passageiro != NULL){
    free(passageiro);
    *passageiro = NULL;
  }
}

/* Copia os valores de um aluno para as referências informadas. Em caso de aluno
 * NULL, atribuir valor padrão <-1, "NULL", "NULL"> aos parâmetros. */
void passageiro_acessa(Passageiro *passageiro,int *id, char *nome, char *endereco){
  if(passageiro == NULL){
    *id = -1;
    strcpy(nome, "NULL");
    strcpy(endereco, "NULL");
  }else{
    *id = passageiro->id;
    strcpy(nome, passageiro->nome);
    strcpy(endereco, passageiro->endereco);
  }
}

/* Atribui novos valores aos campos de um aluno. Porém, para os casos em que (i)
 * algum dos parâmetros sejam nulos <NULL, -1, NULL, NULL>; ou (ii) o tamanho
 * das strings nome e curso sejam maiores que os da especificação (50 e 30,
 * respectivamente), a função não deve fazer a atribuição. */
void passageiro_atribuir(Passageiro *passageiro, int id, char *nome, char *endereco){
  if(passageiro != NULL && verificar_parametros(id,nome,endereco) == 1){
    passageiro->id = id;
    strcpy(passageiro->nome, nome);
    strcpy(passageiro->endereco, endereco);
  }
}

/* Avalia se dois alunos são iguas. A função deve retornar 1 se os alunos
 * possuem os mesmos dados, 0 caso os dados dos alunos possuam alguma diferença
 * e -1 caso pelo menos um dos alunos seja NULL.
 */
int passageiro_igual(Passageiro *passageiro1, Passageiro *passageiro2){
  if(passageiro1 == NULL || passageiro2 == NULL){
    return -1;
  }

  if(passageiro1->id != passageiro2->id){
    return 0;
  }

  if(strcmp(passageiro1->nome,passageiro2->nome) != 0){
    return 0;
  }

  if(strcmp(passageiro1->endereco,passageiro2->endereco) != 0){
    return 0;
  }

  return 1;
}

/* Retorna o tamanho em bytes do TAD aluno. */
int passageiro_tramanho() {
  return sizeof(Passageiro); 
}


//int arvore;


/*

  isso provavelmente vai estar em outro arquivo

int main(){
    while (1){ //Base do programa

        if (arvore == NULL){ // Caso não exista arvore ainda(ainda n sei como arrumar essa ideia de arvore)
            Reserva raiz;
        };

        //Menu de operações:
        int op;
        printf("Digite o número relacionado a operação desejada: ");
        printf("Criar nova reserva: 1");
        
        scanf("%d",&op);

        if (op = 1){
            No *abb_insere_no(No *raiz, No *no);
        };
        


    }
}*/
