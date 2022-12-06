enum cod_assento {
    A0, B0, C0,
    A1, B1, C1, 
    A2, B2, C2,
    A3, B3, C3,
    A4, B4, C4,
    A5, B5, C5,
    A6, B6, C6,
    A7, B7, C7,
    A8, B8, C8, 
    A9, B9, C9
 };

typedef enum cod_assento Assento;
typedef struct data Data;
typedef struct voo Voo;
typedef struct lista_voo ListaVoo;
typedef struct passageiro Passageiro;
typedef struct lista_passageiro ListaPassageiro;
typedef struct reserva Reserva;
typedef struct agenda Agenda;
typedef struct viagem Viagem;
typedef struct tabela_viagem TabelaViagem;

/*Implementação da lista de passageiro*/
typedef struct lista Lista;

/* TAD:  lista encadeada */
ListaPassageiro *lista_cria();
int lista_liberar(ListaPassageiro **lista);
int lista_inserir(ListaPassageiro *lista, Passageiro *passageiro);
ListaPassageiro *lista_busca(ListaPassageiro *lista, int ID);
ListaPassageiro *lista_retirar(ListaPassageiro *lista);
int lista_vazia(ListaPassageiro* lista);
Passageiro *lista_primeiro(ListaPassageiro* lista);

/*Funções para passageiros*/

int verificar_parametros(int passageiro_id, char *nome, char *endereco);
Passageiro *passageiro_novo(int id, char *nome,char *endereco);
void passageiro_liberar(Passageiro **passageiro);
void passageiro_acessa(Passageiro *passageiro,int *id, char *nome, char *endereco);
void passageiro_atribuir(Passageiro *passageiro, int id, char *nome, char *endereco);
int passageiro_igual(Passageiro *passageiro1, Passageiro *passageiro2);
int passageiro_tramanho();
