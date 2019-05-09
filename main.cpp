#include <iostream>
#include <string.h>
#include "pessoa.h"
#include "arqpessoa.h"
#include "arqarvore.h"

using namespace std;


int main(){

    int op = 1;

    system("clear");

    while(op != 0){
        printf("Sistema de cadastro de alunos - Versão Alpha 2.0\n");
        printf("================================================\n");
  /*X*/ printf("| %2d  | %-40s \n", 1, "Carregar Arquivo de inicialização");
  /*X*/ printf("| %2d  | %-40s \n", 2, "Inserir Aluno");
  /*X*/ printf("| %2d  | %-40s \n", 3, "Alterar Aluno");
  /*X*/ printf("| %2d  | %-40s \n", 4, "Buscar Dados de Aluno");
  /*O*/ printf("| %2d  | %-40s \n", 5, "Remover Aluno"); //Só remove folha
  /*X*/ printf("| %2d  | %-40s \n", 6, "Imprimir Cadastro");
  /*X*/ printf("| %2d  | %-40s \n", 7, "Imprimir Arvore B");
  /*X*/ printf("| %2d  | %-40s \n", 0, "Sair");

        scanf("%d", &op);
        getchar();

        switch(op){

        case 1:
        {
            FILE *arq = fopen("arquivoAlunos.txt","r");

            ArqPessoa *arqP = new ArqPessoa();

            if(!arqP){
                printf("Falha na abertura do arquivo Pessoa.bin\n");
            }

            ArqArvore *arqA = new ArqArvore();

            if(!arqA){
                printf("Falha na abertura do arquivo Arvore.bin\n");
            }

            arqA->Inicializar();
            arqP->Inicializar();

            char string[300];
            Pessoa *P;

            int counter = 0;

            fgets(string, 300, arq);
            while(!feof(arq)){
                P = new Pessoa(string);

                arqP->InserePessoa(P);

                arqA->insereArv(P->GetMatricula(),P->GetMyPos());

                counter++;
                delete P;
                fgets(string, 300, arq);
            }

            fclose(arq);

            delete arqA;
            delete arqP;

            printf("%d Alunos inseridos com sucesso\n", counter);
            getchar();
        }
        break;

        case 2:
        {
            char *strAux, charAux;
            int intAux;
            strAux = (char *) calloc(100,sizeof(char));
            Pessoa *p = new Pessoa();

            printf("Matricula:");
            scanf("%d", &intAux);
            p->SetMatricula(intAux);
            getchar();

            strcpy(strAux,"");
            do{
                printf("Novo nome*:");
                fgets(strAux,100,stdin);
            }while(strlen(strAux) <= 1);
            p->SetNome(strAux);

            do{
                printf("Novo sexo* (M/F):");
                charAux = getchar();
                getchar();
            }while( charAux != 'm' && charAux != 'M' && charAux != 'f' && charAux != 'F');
            p->SetSexo(charAux);
            getchar();

            do{
                printf("Novo CPF* (xxxxxxxxxx-xx):");
                fgets(strAux,100,stdin);
            }while(!isValid(strAux));
            p->SetCPF(strAux);

            char *strAux2 = (char *) calloc(100,sizeof(char));
            do{
                printf("Novo RG*:");
                fgets(strAux2,100,stdin);
            }while(strAux2[0] == '\n' || strAux2[0] == '\0');
            p->SetRG(strAux2);

            do{
                printf("Novo Telefone (xx-xxxx-xxxx):");
                fgets(strAux,100,stdin);
            }while(!isValid(strAux));

            if(strlen(strAux) == 0)
                strcpy(strAux,"0-0-0");
            p->SetTelefone(strAux);

            do{
                printf("Novo Celular (xx-xxxx-xxxx):");
                fgets(strAux,100,stdin);
            }while(!isValid(strAux));

            if(strlen(strAux) == 0)
                strcpy(strAux,"0-0-0");
            p->SetCelular(strAux);

            printf("Novo E-mail:");
            fgets(strAux,100,stdin);
            p->SetEmail(strAux);

            do{
                printf("Novo Endereço*:");
                fgets(strAux,100,stdin);
            }while(strAux[0] == '\0' || strAux[0] == '\n');
            p->SetEndereco(strAux);

            printf("Nova data de nascimento* (DD/MM/AAAA):");
            fgets(strAux,100,stdin);
            p->SetNascimento(strAux);


            ArqArvore arqA;
            ArqPessoa arqP;

            arqP.InserePessoa(p);
            arqA.insereArv(p->GetMatricula(),p->GetMyPos());

            getchar();
        }
        break;

        case 3:
        {

            int i, aux;
            printf("Matricula do aluno:");
            scanf("%d", &i);

            ArqArvore arqA;
            aux = arqA.buscaPessoa(i);

            if(aux == -1)
                printf("Este aluno não está cadastrado\n");
            else{
                ArqPessoa arqP;
                putwchar_unlocked('\n');
                arqP.EditarPessoa(aux);
            }

        }
        break;

        case 4:
        {

            int i, aux;
            printf("Matricula do aluno:");
            scanf("%d", &i);

            ArqArvore arqA;
            aux = arqA.buscaPessoa(i);

            if(aux == -1)
                printf("Este aluno não está cadastrado\n");
            else{
                ArqPessoa arqP;
                putwchar_unlocked('\n');
                arqP.ImprimePessoa(aux);
            }

            getchar();
            getchar();
        }
        break;

        case 5:
        {
            printf("Opção estara disponível na versão beta\n");

            getchar();
        }
        break;

        case 6:
        {
            ArqArvore a;

            a.ImprimeCadastro();

            getchar();
        }
        break;

        case 7:
        {
            ArqArvore a;

            a.Imprime();

            getchar();
        }
        break;

        case 0:
        {
            printf("Agradecemos pela preferência!\n");
            getchar();
        }
        break;

        }


        system("clear");
    }

    return 0;
}
