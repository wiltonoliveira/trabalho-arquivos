
#include <stdio.h>
#include <stdlib.h>
//#include <stdio_ext.h>

/* Aluno: Wilton Silva Oliveira Júnior
   Email: wilton.junior@ifba.edu.br
   Matrícula: 2016116055
   Semestre: 2nd
*/

#define TAM_PRINC 10

struct auxiliar {
	int *vet_aux;
	int tam_vetor;
	int topo;
};

typedef struct auxiliar aux;


int  menu (int operador);
void asteriscos ();

void novo_vetor (int **vet, int tam);
void novo_elemento (int *vet, int topo);
void lista_todos (int vet[], int tam);
void lista_ordenado (int vet[], int topo);
void insertionSort(int array[], int tamanho);
void excluir_elemento (aux estrutura, int elemento);
void aumentar_vetor (int *vet, int tam_antigo, int add);
void inicializa_principal (aux principal[]);


int main (void){
	FILE *tipo_de_arquivo;
	char leitura;
	int i;
	float x;
	
	tipo_de_arquivo	 = fopen ("tipo.txt", "rt");

	
	if (tipo_de_arquivo == NULL){
		printf ("FALHA NA CRIACAO DO ARQUIVO\n");
		return 0;
	}
	
	else {
		leitura = fscanf (tipo_de_arquivo, "%d%f", &i, &x);
		
		if (leitura == EOF)
			printf ("arquivo vazio\n");
		
		else 
			puts (leitura);
	}

	

}


int programa(void) {
	aux principal [TAM_PRINC];
	int op;
	int i, j, w = 0;
	int pos;
	int pos_excluir, num_excluir;
	int add;
	int *copia = NULL;
	int tam_copia = 0;

	
	
	inicializa_principal (principal);

	do {
	op = menu (op);

	switch (op) {
			case 1: {
				//Inserir elemento

				printf ("Informe a posicao da estrutura principal sera alocada: ");
				scanf ("%d", &pos);
				fflush(stdin);
				//__fpurge (stdin);

				if (principal[pos].tam_vetor == 0){
					printf("\nVetor auxiliar na posicao %d nao criado\nInforme o tamanho do vetor: ",pos);
					scanf ("%d", &principal[pos].tam_vetor);
					fflush(stdin);
					//__fpurge (stdin);

					novo_vetor (&principal[pos].vet_aux, principal[pos].tam_vetor);

					printf("\nendereco: %p\n" , principal[pos].vet_aux);

					novo_elemento (principal[pos].vet_aux, principal[pos].topo);

					printf("Valor inserido out function: %d\n", principal[pos].vet_aux[principal[pos].topo] );

					principal[pos].topo += 1;
				}

				else if (principal[pos].topo == principal[pos].tam_vetor){
						printf ("\n\nVETOR DA POSICAO %d CHEIO\n", pos);
				}

				else if (principal[pos].topo < principal[pos].tam_vetor){
					novo_elemento (principal[pos].vet_aux, principal[pos].topo);
					principal[pos].topo += 1;
				}
				system ("PAUSE");
				system ("cls");
				break;
			}

			case 2: {
				//Listar numeros de todas as estruturas

				for (i = 0; i < TAM_PRINC; i++){
					printf("VETOR AUXILIAR DA POSICAO %d:", i);
					printf ("(%d posicoes) - ",principal[i].tam_vetor);
					lista_todos (principal[i].vet_aux, principal[i].topo);
				}
				system ("PAUSE");
				system ("cls");
				break;
			}
			case 3: {
				//Listar os numeros ordenados para cada estrutura auxiliar
				for (i = 0; i < TAM_PRINC; i++){
					printf("VETOR AUXILIAR DA POSICAO %d:", i);
					lista_ordenado (principal[i].vet_aux, principal[i].topo);
					printf ("\n");
				}
				break;
			}
			case 4: {
				//Listar todos os numeros de forma ordenada
				copia = NULL;

				for (i = 0; i < TAM_PRINC ; i++)
					if (principal[i].topo > 0){
					copia = (int *) malloc (principal[i].topo * sizeof (int));
					break;
					}
					
				
				
				for (; i < TAM_PRINC ; i++){
					if (principal[i].topo > 0){
						tam_copia += principal[i].topo;
					}
				}
				
				copia = (int *) realloc (copia, (tam_copia) * sizeof (int));
				
				for (i = 0; i < TAM_PRINC; i++){
					if (principal[i].topo > 0){
						for (j = 0; j < principal[i].topo; j++){
							copia[w] = principal[i].vet_aux[j];
							w++;
						}
					}
				}
				
				insertionSort(copia, tam_copia);
				
				printf ("TODOS OS ELEMENTOS ORDENADOS:\n");
				for (i = 0; i < tam_copia; i++){
					printf (" %d ", copia[i]);
				}

				free (copia);
				printf("\n\n");
				break;

			}
			case 5: {
				//Excluir um elemento


				printf ("De qual posicao da estrutura principal voce deseja excluir: ");
				scanf ("%d", &pos_excluir);
				fflush(stdin);
				//__fpurge (stdin);

				if (principal[pos_excluir].topo == 0)
					printf("\nVETOR AUXILIAR VAZIO\n");

				else {
				printf ("Informe o numero a ser excluido: ");
				scanf ("%d", &num_excluir);
				fflush(stdin);
				//__fpurge (stdin);

				excluir_elemento (principal[pos_excluir], num_excluir);
				principal[pos_excluir].topo -= 1;
				}
				
				break;
			}
			case 6: {
				//Aumentar o tamanho de uma estrutura auxiliar

				printf ("\nDigite a posicao da estrutura principal que quer aumentar [0 - 9]: ");
				scanf ("%d", &pos);
				fflush(stdin);
				//__fpurge (stdin);

				if (principal[pos].tam_vetor == 0)
					printf ("\nVETOR DA POSICAO %d NAO FOI CRIADO\n", pos);
				
				else {
				printf ("Quantos elementos serao adicionados: ");
				scanf ("%d", &add);
				fflush(stdin);
				//__fpurge (stdin);

				aumentar_vetor (principal[pos].vet_aux, principal[pos].tam_vetor, add);
				principal[pos].tam_vetor += add;
				}

				break;
			}
		}
	} while (op != 7);

	return 0;

}

void novo_vetor (int **vet, int tam){

	*vet = (int *) malloc (tam * sizeof (int));
}

void novo_elemento (int *vet, int topo){

    printf("\nPonteiro: %p\n", vet);

	printf ("\n\nDigite o elemento a ser inserido: ");

	scanf ("%d", &vet[topo]);

    printf("Valor inserido in function: %d\n", vet[topo]);

	fflush(stdin);
	//__fpurge (stdin);

}

void lista_todos (int vet[], int topo){
	int i;

	for (i = 0; i < topo; i++){
		printf("%d ", vet[i]);
	}

	printf("\n");
}

void lista_ordenado (int *vet, int topo){
	int i;
	int *v = NULL;

	v = (int *) malloc (topo * sizeof (int));

	for (i = 0; i < topo; i++){
		v[i] = vet[i];
	}

	insertionSort (v, topo);

	for (i = 0; i < topo; i++)
		printf ("%d ",v[i]);

	free (v);
}

void insertionSort(int array[], int tamanho) {
      int i, j, tmp;
      for (i = 1; i < tamanho; i++) {
            j = i;
            while (j > 0 && array[j - 1] > array[j]) {
                  tmp = array[j];
                  array[j] = array[j - 1];
                  array[j - 1] = tmp;
                  j--;
            }
      }
}

void excluir_elemento (aux estrutura, int elemento){
	int i, j, w;

	for (i = 0, j = (i +1); i < estrutura.tam_vetor; i++){
		if (estrutura.vet_aux[i] == elemento){
			estrutura.vet_aux[i] = estrutura.vet_aux[j];

			for (w = j; w < estrutura.tam_vetor; w++){
				estrutura.vet_aux[w] = estrutura.vet_aux[w + 1];
			}
			break;
		}
	}
}

void aumentar_vetor (int *vet, int tam_antigo, int add){

	vet = (int *) realloc (vet,  (tam_antigo + add) * sizeof (int));
}

int  menu (int operador){
	asteriscos (); printf ("MENU"); asteriscos (); printf ("\n");
	printf ("1 - Inserir elemento\n");
	printf ("2 - Listar numeros de todas as estruturas\n");
	printf ("3 - Listar os numeros ordenados para cada estrutura auxiliar\n");
	printf ("4 - Listar todos os numeros de forma ordenada\n");
	printf ("5 - Excluir um elemento\n");
	printf ("6 - Aumentar o tamanho de uma estrutura auxiliar\n");
	printf ("7 - Sair\n");
	printf ("Digite a operacao desejada:");
	scanf ("%d", &operador);

	if (operador <= 0 || operador > 7){
		printf ("\nOPERACAO INVALIDA\n");
		menu (operador);
	}
	fflush(stdin);
	//__fpurge (stdin);
	system ("cls");
	return operador;
}

void asteriscos (){
	int i;

	for (i = 0; i < 6; i++)
		printf ("*");
}

void inicializa_principal (aux principal[]){
	int i;

	for (i = 0; i < TAM_PRINC; i++){
		principal[i].topo = 0;
		principal[i].tam_vetor = 0;
		principal[i].vet_aux = NULL;
	}
    
		
}
