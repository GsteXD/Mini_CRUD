 //C�digo Base para o Mini-Projeto Agenda de Amigos
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

struct ficha{ //cria uma vari�vel estrutura ficha
	char nome[40];
	char telefone[20];
};

int procurar(struct ficha vetor[], int num_fichas){

    int i;
    char procurado[40];
	printf("\nEntre com o nome procurado:");
	fgets(procurado,40,stdin);

    for(i=0;i<num_fichas;i++){
        if(strcasecmp(procurado,vetor[i].nome) == 0){
            return i; //Depois de achar o valor, n�o precisa mais procurar
        }
    }
    printf("\n\nElemento n�o encontrado!");
	sleep(1.00);

    return -1;
}

void ler_arquivo(struct ficha vetor[], int *num_fichas, int op){
	FILE *fp; //Cria uma vari�vel tipo FILE, que � um ponteiro.
	char nome_arquivo[40];

	printf("Informe o nome do arquivo: ");
	fgets(nome_arquivo, 40, stdin);

	fp = fopen(nome_arquivo, "r"); //Define a vari�vel fp como uma fun��o "fopen", onde deve ser especificado o nome do arquivo e seu tipo de par�metro
								 	//que neste caso, � leitura.

	if(!fp){
		printf("Erro na abertura do arquivo");
		exit(-1);
	} else if(op == 1) { //Texto
		char buffer[101];
		fgets (buffer, 100, fp); //Primeira Linha 

		*num_fichas = atoi(buffer); //Os valores apontados em num_fichas assumir�o os valores inteiros do buffer

		for(int i=0; i < *num_fichas;i++){
			fflush(stdin);
			fgets(vetor[i].nome, 40, fp);
			fgets(vetor[i].telefone, 20, fp);
		}
		fclose(fp);

	} else if(op == 2) { //Planilha
		int i = 0;

		while(!feof(fp)){ //Verificador para saber quando chegou ao final do arquivo
			fscanf(fp, "%40[^,],", vetor[i].nome); //L� dados de nome de fp, excluindo todo o conjunto de v�rgulas do arquivo.
			fscanf(fp, "%20[^\n]\n", vetor[i].telefone); //L� dados de telefone de fp, excluindo todos os espa�amentos \n de sua leitura.
			i++; //Passa para a pr�xima posi��o.
		}
		*num_fichas = i; //Aponta que o valor assumido de num_fichas deve ser igual ao valor de i.
		fclose(fp); //Fecha o arquivo

	} else { //bin�rio
		fread(num_fichas, sizeof(int), 1, fp); //s�o lidos os valores apontados em num_fichas, o seu tamanho de bits(em int),
											   //a quantidade de elementos e da onde os dados ser�o lidos apontados por fp.

		fread(vetor, sizeof(struct ficha), *num_fichas, fp); //depois, s�o lidos os valores apontados em vet, o tamanho de bits da estrutura, a quantidade de estruturas 
		                                                   //(que est� sendo apontada pelo num_fichas) e da onde esses dados ser�o lidos (fp);
		fclose(fp);
	}
}

void 

int main()
{
	struct ficha agenda[10];
	int fichas_existentes = 0, proxima = 0;
	char opcao[10]="0"; 
    setlocale(LC_ALL, "Portuguese_Brazil");
	while(opcao[0] != '6')
	{
		system("cls"); //Limpa a tela no �nicio de cada loop

		printf("\nEntre com a op��o desejada:\n");
		printf("\n1) Inserir ficha:");
		printf("\n2) Procurar por nome:");
		printf("\n3) Listar toda a base:");
		printf("\n4) Excluir por nome:");
		printf("\n5) Atualizar informa��es:");
		printf("\n6) Salvar informa��es:");
		printf("\n7) Sair\n\n");
		fgets(opcao, 2, stdin);
        fflush(stdin);

		switch (opcao[0]) 
		{
			case '1': //Inserir
				printf("\nEntre com um nome:");
				fgets(agenda[proxima].nome, 40, stdin);
				printf("\nEntre com um telefone:");
				fgets(agenda[proxima].telefone, 20, stdin);

				printf("Opera��a realizada com sucesso!");
				sleep(2.00);

				fichas_existentes++;
				proxima++;
			break;
		
			case '2': //Procurar
				int linha;
			
				linha = procurar(agenda, fichas_existentes);
				if(linha != -1){
					printf("\nTelefone:%s", agenda[linha].telefone);
				}
			break;

			case '3': //Listar Tudo
				printf("\n\n");
				int i;
				for(i=0; i<fichas_existentes; i++)
				{
					printf("O telefone de %s � %s\n",
					agenda[i].nome, agenda[i].telefone);
				}
				if(fichas_existentes == 0)
					printf("A base de dados est� vazia!\n");

				printf("\nAperte ENTER para continuar");
				getchar();
			break;
		
			case '4': //Excluir
				int ultimaLinha; //Cria apenas uma vari�vel apenas para a �ltima linha, n�o � necess�rio uma v�riavel para a linha atual pois ela foi declarada anteriormente.

				linha = procurar(agenda, fichas_existentes); //Chama a fun��o procurar

				if(linha != -1){ //Caso o valor retornado seja diferente de -1(valor de erro)
					ultimaLinha = fichas_existentes - 1; //define o valor da ultima linha a partir do n�mero total de fichas existentes menos 1 (pois o vetor inicia em 0).

					agenda[linha] = agenda[ultimaLinha]; //define a posi��o do valor achado como estando na �ltima posi��o do vetor.

					fichas_existentes--; //Exclui uma ficha do total
					proxima--; //Exclui a �ltima posi��o do vetor
				}
			break;

			case '5': //Atualizar
				int op; //cria uma vari�vel para opera��o

				linha = procurar(agenda, fichas_existentes); //chama a fun��o "procurar", que utiliza os par�metros da agenda e fichas_existentes.

				if(linha != -1){
					printf("Informe o campo a ser alterado: \n1-Nome\n2-Telefone\n\nResposta: ");
					scanf("%i", &op);
					fflush(stdin);
					if(op == 1){
						printf("Entre com o novo nome: ");
						fgets(agenda[linha].nome, 40, stdin);
					} else {
						printf("Entre com o novo telefone: ");
						fgets(agenda[linha].telefone, 20, stdin);
					}
				}

			break;

			case '6': //Salvar
				system("cls");

				int operacao;
				printf("\nInforme o m�todo de salvamento:\n");
				printf("\n1) Arquivo texto");
				printf("\n2) Planilha:");
				printf("\n3) Arquivo bin�rio:");
				printf("\n4) Sair\n\n");
				scanf("%i", &operacao);



			break;

			case '7':
				printf("Saindo...");
				sleep(2.00);
			break;

			default:
				printf("Op��o inv�lida!");
				sleep(1.00);
			break;
		}
	}
	return 0;
}