#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define TAM_MAX_PRECESSOS_CADASTRADOS 1000
/* No inicio criei uma (STRUCT) estrutura  para cadastro onde tem as variveis
necessarias para o cadastro */
struct cadastro{
    int num_cadastro;
    char foro[100];
    char advogado[100];
    char nomeCliente[100];


};
/* A fun��o recoveryData serve para abrir o arquivo pra leitura, no caso do arquivo n�o existir
ele continua a percorer as linhas e entra na  fun��o main, donde  um arquivo com o mesmo nome vai ser criado,
essa essa fun��o tambem serve para ler os arquivos na inicializa��o para eventuais consultas*/
int recoveryData( struct cadastro *processos){
    FILE *dados;
    char linha[100];
    int i=0;
    dados=fopen("dados.txt","r");
    if(dados==NULL){   //Aqui esse poteiro de arquivo verifica se o arquivo � nulo
        printf("\n");
        return (0);
    }
    do {
      /* Aqui o fgets ler os arquivos no texto para consulta*/
      fgets(processos[i].foro,100,dados);
      fgets(processos[i].advogado,100,dados);
      fgets(processos[i].nomeCliente,100,dados);
      i++; // Incrementa mais 1 na variavel i
    }
    while(feof(dados)==0); // Aqui � pra ler ate o final do arquivo
    fclose(dados);  //Fecha o arquivo txt
    return i; // A fun��o recoveryData retorna i
}

/*Aqui criei uma fun��o do tipo struct cadastro que tem como paramentros o id, um ponteiro char *nomeCliente,
um ponteiro  char *advogado e tambem recebe um ponteiro *processos do tipo struct cadastro*/

struct cadastro buscar(int id,char *nomeCliente, char *advogado, struct cadastro *processos){
    FILE *dados;
    struct cadastro vazio; //
    return id < TAM_MAX_PRECESSOS_CADASTRADOS ? processos[id]:vazio;
    //Aqui no return, se id for menor que a constante TAM_MAX_PRECESSOS_CADASTRADOS processos[id]:vazio


}
/* Essa fun��o ela busca o cliente em uma determinada posi��o do vetor de struct cadastro, para posteriomente ser chamanda
para exibir o conteudo no terminal, e ela recebe um ponteiro char *nomeCliente e tambem recebe um
ponteiro *processos do tipo struct cadastro*/
struct cadastro buscarCliente (char *nomeCliente, struct cadastro *processos){
    int i;
    struct cadastro processoBuscado;

    for(i=0;i<TAM_MAX_PRECESSOS_CADASTRADOS;i++){
        /*aqui nessa condicional if ele verifica se o nome que o usuario digitou � o mesmo que tem no arquivo txt*/
        if(strcmp(processos[i].nomeCliente,nomeCliente)==0){
            processoBuscado=processos[i]; /*caso seja verdade processoBuscado=processos[i] e quando essa fun��o for chamada
            ela vai mostrar os dados na tela a partir do nome do cliente*/
            break;
        }

    }
    return processoBuscado; // aqui ela retorna a variavel  processoBuscado do tipo struct cadastro
}

/* Essa fun��o ela busca o nome advodado em uma determinada posi��o do vetor de struct cadastro, para posteriomente ser chamanda
para exibir o conteudo no terminal, e ela recebe um ponteiro char *advogado e tambem recebe um
ponteiro *processos do tipo struct cadastro*/

struct cadastro buscarAdvogado (char *advogado, struct cadastro *processos){
    int i;
    struct cadastro processoBuscado;
    for(i=0;i<TAM_MAX_PRECESSOS_CADASTRADOS;i++){
        /*aqui nessa condicional if ele verifica se o nome que o usuario digitou � o mesmo que tem no arquivo txt*/
        if(strcmp(processos[i].advogado,advogado)==0){
            processoBuscado=processos[i];
            /*caso seja verdade processos[i].advogado,advogado e quando essa fun��o for chamada
            ela vai mostrar os dados na tela a partir do nome do advogado*/

        }

    }
    return processoBuscado; // aqui ela retorna a variavel  processoBuscado do tipo struct cadastro
}

/*Essa fun��o do tipo vazia ela exiba na tela os dados cadastrados, e ela recebe como parametro a variavel proesso do tipo
struct cadastro*/

void exibirProcessos(struct cadastro processo){

    printf(" Numero de processo = %d\n",processo.num_cadastro); //Aqui ela imprime o numero do processo
    printf(" Foro = %s",processo.foro); //Aqui ela imprime o nome do foro
    printf(" Advogado = %s",processo.advogado); //Aqui ela imprime o nome do advogado
    printf(" Cliente = %s",processo.nomeCliente); //Aqui ela imprime o nome do cliente
}

void telaMenu(); // Aqui � o prototipo da fun��o que imprime o menu do sistema
void telaBucandoDados();// Aqui � o prototipo da fun��o  que que imprime o menu para mostrar os dados

/*Aqui � a fun��o principal */
int main(){
    setlocale(LC_ALL,"portuguese");
    int menu,i;
    char cliente[50],advogado[50];
    int puxarDados;
    int id=0,num_processo;
    struct cadastro processoCadastrado[TAM_MAX_PRECESSOS_CADASTRADOS];
    FILE *dados;
    id=recoveryData(processoCadastrado);
    //Aqui tem a tela de menu do sistema
    while(menu!=4){
        telaMenu();
        scanf("%d",&menu);
        system("cls");
        //caso o usuario digite um ele entra nessa condicional if
        if(menu==1){
            dados=fopen("dados.txt","a"); // Aqui ele abre o arquivo dados.txt para escrita, caso o arquivo n�o exista ele e criado
            processoCadastrado[id].num_cadastro=id;
            fprintf(dados,"N�mero do processo: %d\n",processoCadastrado[id].num_cadastro);// Aqui ele escreve o numero do processo no aquivo txt
            fflush(stdin);
            printf("Informe o Foro onde o processo foi registrado\n"); // Aqui o usuario vai digitar o nome do foro
            fgets(processoCadastrado[id].foro,100,stdin);
            fprintf(dados,"Nome do foro: %s",processoCadastrado[id].foro);// Aqui ele escreve no arquivo o nome do foro
            fflush(stdin);
            printf("Nome do advogado responsavel pelo processo\n"); //Aqui o usuario vai digitar o nome do advogado
            fgets(processoCadastrado[id].advogado,100,stdin);
            fprintf(dados,"Nome do advogado: %s",processoCadastrado[id].advogado);// Aqui ele escreve no arquivo o nome do advogado
            fflush(stdin);
            printf("Informe o nome do cliente\n"); //Aqui o usuario vai digitar o nome do cliente
            fgets(processoCadastrado[id].nomeCliente,100,stdin);
            fprintf(dados,"Nome do cliente %s",processoCadastrado[id].nomeCliente); // Aqui ele escreve no arquivo o nome do cliente
            fclose(dados); //Aqui ele fecha o arquivo
            fflush(stdin);
            id++; //Aqui o id vai ser incrementado em 1
        }
        // Caso o usuario digite 2 ele vai entrar nessa condicional if
        else if(menu==2){
            telaBucandoDados(); // Chmando a fun��o para apresentar o menu
            scanf("%d",&puxarDados);
            //Quando o usuario digitar 2 o programa vai exibir um menu com 3 op��es, essas tr�s op��es s�o:
            //Caso o usuario digite 1 ele entra nessa condicional if
            if(puxarDados==1){
                printf("informe o numero de processo\n");
                scanf("%d",&num_processo);
                system("cls");
                struct cadastro processoBuscado = buscar(num_processo,"","",processoCadastrado);// aqui processoBuscado recebe a fun��o buscar
                exibirProcessos(processoBuscado); // Chamando a fun��o para exibir os dados com base no id informado

            }
            //Caso o usuario digite 2 ela entra nessa condicional if
            else if(puxarDados==2){
                fflush(stdin);
                printf("Informe o nome do cliente\n");
                fgets(cliente,50,stdin);
                system("cls");
                struct cadastro processoBuscado = buscarCliente(cliente,processoCadastrado); // aqui processoBuscado recebe a fun��o buscarCliente
                exibirProcessos(processoBuscado); // Chamando a fun��o para exibir os dados com base no nome do cliente informado
            }
            // Caso o usuario digite 3 ela entra nessa condicional if
            else if(puxarDados==3){
                fflush(stdin);
                printf("Informe o nome do advogado\n");
                fgets(advogado,50,stdin);
                system("cls");
                struct cadastro processoBuscado = buscarAdvogado(advogado,processoCadastrado); // aqui processoBuscado recebe a fun��o buscarAdvogado
                exibirProcessos(processoBuscado);  // Chamando a fun��o para exibir os dados com base no nome do advogado informado
            }
        }
        // Caso o usuario digite 3 ela entra nessa condicional if
        else if(menu==3){
            dados=fopen("dados.txt","a");// Aqui ele abre o arquivo para escrita no final da linha
            if(dados==NULL){ // Aqio se o arquivo n�o existir o programa ser� encerrado
                printf("Ainda n�oo foi cadastrado nenhum processo\n");
                system("pause");
                exit (1);
            }
            printf("Edi��o de processos:\n");
            printf("Informe o numero de processo\n");// Aqui o usuario vai informar o numero no processo que dejesa editar os dados
            scanf("%d",&puxarDados);
            fflush(stdin);
            system("cls");
            printf("\n esse os dados dos cliente para editar\n\n");
            struct cadastro processoBuscado = buscar(num_processo,cliente,advogado,processoCadastrado);
            exibirProcessos(processoBuscado); // Chamada da fun��o para exibir na tela os dados do processo que vai ser editado
            fprintf(dados,"N�mero do processo: %d\n",puxarDados); //Aqui escreve no arquivo o numero do processo
            printf("\nInforme o Foro onde o processo foi registrado\n");
            fgets(processoCadastrado[puxarDados].foro,100,stdin);
            fprintf(dados,"Nome do foro: %s",processoCadastrado[puxarDados].foro); //Aqui escreve no arquivo o nome do foro
            fflush(stdin);
            printf("Nome do advogado respons�vel pelo processo\n");
            fgets(processoCadastrado[puxarDados].advogado,100,stdin);
            fprintf(dados,"Nome do  advogado: %s",processoCadastrado[puxarDados].advogado); //Aqui escreve no arquivo o nome do advogado
            fflush(stdin);
            printf("Informe o nome do cliente\n");
            fgets(processoCadastrado[puxarDados].nomeCliente,100,stdin);
            fprintf(dados,"Nome do cliente: %s",processoCadastrado[puxarDados].nomeCliente);//Aqui escreve no arquivo o nome do cliente
            fclose(dados);// Fecha o arquivo
        }
        // Aqui se o usuario digitar 4 o programa � encerrado
        if(menu==4){
            printf("\nPrograma encerrado\n");
            system("pause");
        }
        // Aqui se o usuario digitar um valor diferente de 1,2,3 ou 4 vai aparecer a mensagem "Op��o invalida"
        if(menu!=1 && menu !=2 && menu !=3 && menu !=4){
            system("cls");
            printf("\nOp��o invalida\n");
        }
    }
}
//Essa fun��o ela retorna o menu principal do sistema
void telaMenu(){
    printf("\nSistema de Gerenciamento de Processos\n");
    printf("\n\n\n1) Cadastro de processos:\n2) Consulta especifica:\n3) Edi��oo de processos:\n4) Sair do programa:\n");
}
//Essa fun��o ela retorna o menu da op��o buscar dados
void telaBucandoDados() {
    printf("Buscar dados de processos, informe uma op�oo \n");
    printf("1) numero de processo \n2) Nome do cliente\n3) Advogado responsavel\n");
}

