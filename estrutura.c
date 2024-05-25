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

int procurar(struct ficha vetor[], int num_fichas){ //Procura elementos na ficha

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
	fgets(nome_arquivo, sizeof(nome_arquivo), stdin); //adquire o nome do arquivo, que � limitado de acordo com o seu pr�prio tamanho.

	nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0'; //Remove caracteres extras indesejados(como o ENTER).

	fp = fopen(nome_arquivo, "r"); //L� o arquivo.
	
	if(!fp){ //Verificador para caso ocorra algum erro, que seja avisado para o usu�rio.
		printf("Erro na abertura do arquivo");
		exit(-1);

	} 
	
	if(op == 1) { //Texto
		char buffer[101];
		fgets (buffer, 100, fp); //Primeira Linha

		*num_fichas = atoi(buffer); //Os valores apontados em num_fichas assumir�o os valores inteiros do buffer

		for(int i=0; i<*num_fichas;i++){
			fflush(stdin);
			fgets(vetor[i].nome, 40, fp);
			fgets(vetor[i].telefone, 20, fp);
		}
		fclose(fp);

	} else if(op == 2) { //Planilha
		int i = 0;

		while(!feof(fp)){ //Verificador para saber quando chegou ao final do arquivo
			fscanf(fp, "%39[^,],", vetor[i].nome); //L� dados nome do fp, retirando toda a v�rgula que haver no arquivo
			fscanf(fp, "%20[^\n]\n", vetor[i].telefone); //L� dados telefone de fp, retirando todo espa�amento \n que houver
			i++; //Passa para a pr�xima posi��o.
		}
		*num_fichas = i; //Aponta que o valor assumido de num_fichas deve ser igual ao valor de i.
		fclose(fp); //Fecha o arquivo

	} else { //bin�rio
		fopen(nome_arquivo, "rb"); //reabre o arquivo para escrita em bin�rio;

		fread(num_fichas, sizeof(int), 1, fp); //s�o lidos os valores apontados em num_fichas, o seu tamanho de bits(em int),
											   //a quantidade de elementos e da onde os dados ser�o lidos apontados por fp.

		fread(vetor, sizeof(struct ficha), *num_fichas, fp); //depois, s�o lidos os valores apontados em vet, o tamanho de bits da estrutura, a quantidade de estruturas 
		                                                   //(que est� sendo apontada pelo num_fichas) e da onde esses dados ser�o lidos (fp);
		fclose(fp);
	}
}

void escrever_arquivo(struct ficha vetor[], int num_fichas, int op){
	FILE *fp;
	char nome_arquivo[40];

	printf("Informe o nome do arquivo: ");
	fgets(nome_arquivo, sizeof(nome_arquivo), stdin); //adquire o nome do arquivo, que � limitado de acordo com o seu pr�prio tamanho.

	nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0'; //Remove caracteres extras indesejados(como o ENTER).

	fp = fopen(nome_arquivo, "w"); //Escreve/cria o arquivo.
	
	if(!fp){ //Verificador para caso ocorra algum erro, que seja avisado para o usu�rio.
		printf("Erro na abertura do arquivo");
		exit(-1);

	} 

	if(op == 1){ //Texto
		fprintf (fp, "%d\n", num_fichas); 

		for(int i=0; i<num_fichas;i++){
			fprintf(fp, "%s\n", vetor[i].nome);
			fprintf(fp, "%s\n", vetor[i].telefone);
		}
		fclose(fp);

	} else if(op == 2){ //Planilha
		for(int i=0;i<num_fichas;i++){
			fprintf(fp, "%s, %s\n", vetor[i].nome, vetor[i].telefone);
		}
		fclose(fp);

	} else { //Bin�rio
		freopen(nome_arquivo, "wb", fp); //reabre o arquivo para escrita em bin�rio;

		fwrite(&num_fichas, sizeof(int), 1, fp);
		fwrite(vetor, sizeof(struct ficha), num_fichas, fp);
		fclose(fp);
	}

}

int main()
{
	struct ficha agenda[10];
	int fichas_existentes = 0, proxima = 0, operacao;
	char opcao[10]="0"; 
    setlocale(LC_ALL, "Portuguese_Brazil");
	while(opcao[0] != '8')
	{
		system("cls"); //Limpa a tela no �nicio de cada loop

		printf("\nEntre com a op��o desejada:\n");
		printf("\n1) Inserir ficha:");
		printf("\n2) Procurar por nome:");
		printf("\n3) Listar toda a base:");
		printf("\n4) Excluir por nome:");
		printf("\n5) Atualizar informa��es:");
		printf("\n6) Exportar informa��es:");
		printf("\n7) Importar informa��es:");
		printf("\n8) Sair\n\n");
		fgets(opcao, 2, stdin);
        fflush(stdin);

		switch (opcao[0]) 
		{
			case '1': //Inserir
				printf("\nEntre com um nome:");
				fgets(agenda[proxima].nome, 40, stdin);
				printf("\nEntre com um telefone:");
				fgets(agenda[proxima].telefone, 20, stdin);

				printf("Opera��o realizada com sucesso!");
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

				printf("\nAperte ENTER para continuar");
				getchar();
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

				printf("\nInforme o m�todo de salvamento:\n");
				printf("\n1) Arquivo texto");
				printf("\n2) Planilha");
				printf("\n3) Arquivo bin�rio");
				printf("\n4) Sair\n\n");
				scanf("%i", &operacao);
				fflush(stdin);
				if(operacao == 4){
					break;
				}
				
				escrever_arquivo(agenda, fichas_existentes, operacao);

			break;

			case '7': //Ler
				system("cls");

				printf("\nInforme o tipo de leitura:\n");
				printf("\n1) Arquivo texto");
				printf("\n2) Planilha");
				printf("\n3) Arquivo bin�rio");
				printf("\n4) Sair\n\n");
				scanf("%i", &operacao);
				fflush(stdin);
				if(operacao == 4){
					break;
				}

				ler_arquivo(agenda, &fichas_existentes, operacao);

			break;

			case '8': //Sair
				printf("Saindo...");
				sleep(2.00);
			break;

			default: //ERRO
				printf("Op��o inv�lida!");
				sleep(1.00);
			break;
		}
	}
	return 0;
}