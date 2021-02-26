// Joao Vitor Andrade de Araujo RA: 21377112
// Murillo Monteiro Pedroso RA:21393496
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct func
{
    int id;
    int idia;
    int imes;
    int iano;
    char nome[5][51]; //limite de 51 para evitar erros com o \0.
    char cpf[16]; 
    float fcpf[16]; 
    char dia[20];
    char mes[20];
    char ano[40];
} tFuncionario;

int main()
{
    struct tm *data_hora_atual;
    tFuncionario dados[5];

    //variaveis
    dados[0].id = -1;
    int tamanho_cpf = 0;
    int j = 0;
    int i = 0;
    int x = 0;
    int tamanho = 0;
    int cont = 0;
    int error = 0; // As variáveis com o nome "error" são para controle de um dado que não está conforme o sistema
    int error_dois = 0;
    int error_cpf = 0;
    int error_tres = 0;
    float acm = 0; // Os acumuladores são para fazer verificação de um CPF válido
    float acm_dois = 0;
    float cont_cpf = 10;
    int resposta;
    char resposta_dois;
    //fim-variaveis

    // Função para atualizar a data em tempo real
    time_t segundos;
    time(&segundos);
    data_hora_atual = localtime(&segundos);

    /*
        Upgrades realizados:
         - Menu de interação.
         - Validação de respostas.
         - Checagem de CPF.
         - Checagem de data em tempo real.
         - Inserção de datas e CPFs com barras e traços ou sem.
         - Limite de caracteres para inscrição de nome. 
    */

    //menu-start
    printf("\n\t\t\tBem vindo a Empresa Sirius Cybernetics Corp\n");
    do // Verifica a resposta do usuário para interação com o menu
    {
        do //valida a resposta e também inicializa o menu interativo com usuário
        {
            printf("\n\t O que voce deseja fazer?\n\t 0 - Inserir os dados dos funcionarios da empresa \n\t 1 - Exibir os funcionarios ja cadastrados \n\t 2 - Sair\n\n ");

            resposta = NULL;

            scanf("%i", &resposta);

            if (resposta < 0 || resposta > 2)
            {
                printf("opcao invalida");
            }
        } while (resposta < 0 || resposta > 2); //repete enquanto resposta for invalida

        switch (resposta) //define a opcao escolhida
        {
        case 0: //inserir novos dados

            printf("\t\tVoce escolheu: Inserir novos dados!\n");
            //Leitura dos dados

            do
            {
                if (cont > 4) //limita o número de funcionários.
                {
                    error++;
                    printf("\nLimite de funcionarios atingido!\n");
                }
                else
                {
                    error = 0;
                    cont++;
                    dados[x].id = x;

                    do
                    {   
                        /*Nesse setor há as limitações para algum dado inválido
                        Exemplo:
                        - Se o usuário colocar um nome maior do que 50 caracteres */
                        printf("\nDigite o nome do funcionario: ");
                        fflush(stdin);

                        scanf("%[^\n]s", dados[x].nome[x]);
                        setbuf(stdin, NULL);
                        error_dois = 0;

                        tamanho = strlen(dados[x].nome[x]);
                        if (tamanho > 50)
                        {
                            error_dois++;
                            printf("\n\n|-ERROR-| Limite de 50 caracteres atingido, por favor, reinsira os dados!");
                        }
                        else
                        {
                            for (i = 0; i < tamanho; i++)
                            {

                                if ((dados[x].nome[x][i] < 65 || dados[x].nome[x][i] > 90) && (dados[x].nome[x][i] < 97 || dados[x].nome[x][i] > 122) && dados[x].nome[x][i] != 32)
                                {

                                    error_dois++;
                                }
                            }
                            if (error_dois != 0)
                            {
                                printf("\n\n|-ERROR-| Use apenas Letras maiusculas, minusculas e espacos!");
                            }
                        }
                    } while (error_dois != 0);
                    do /* Nesse local o sistema vai fazer verificação de um CPF,. O sistema possibilita
                    o usuário escrever os dados com as pontuações ou não. O programa só continua seu progresso
                    após a checagem de um CPF válido. */
                    {
                        printf("\nDigite o CPF: ");
                        scanf("%s", &dados[x].cpf);
                        acm = 0;
                        acm_dois = 0;
                        error_cpf = 0;
                        cont_cpf = 10;
                        j = 0;
                        for (i = 0; i < 14; i++)
                        {
                            if (dados[x].cpf[i] >= 48 && dados[x].cpf[i] <= 57)
                            {
                                dados[x].fcpf[j] = (dados[x].cpf[i] - 48);
                                j++;
                            }
                        }

                        for (i = 0; i < 9; i++)
                        {
                            acm = acm + (dados[x].fcpf[i] * cont_cpf);
                            cont_cpf--;
                        }
                        cont_cpf = 11;
                        for (i = 0; i < 10; i++)
                        {
                            acm_dois = acm_dois + (dados[x].fcpf[i] * cont_cpf);
                            cont_cpf--;
                        }

                        acm = (acm * 10);
                        acm = fmod(acm, 11);
                        acm_dois = (acm_dois * 10);
                        acm_dois = fmod(acm_dois, 11);

                        if (dados[x].fcpf[9] != acm || dados[x].fcpf[10] != acm_dois)
                        {
                            printf("\nCPF invalido");
                            error_cpf++;
                        }
                    } while (error_cpf != 0);

                    do /* Nesse laço a verificação é feita a partir de uma data.
                    O critério usado foi pegar a pessoa mais velha do mundo e fazer as contas para o usuário
                    não colocar alguém mais velho e nem algúem mais novo do que uma pessoa de 18 anos. Fazendo
                    que o sistema cheque a data/hora local do cadastro. O sistema possibilita o usuário escrever
                    a data com barras ou colocando uma por vês. */
                    {
                        error_tres = 0;
                        printf("\nDigite o dia do nascimento: ");
                        fflush(stdin);
                        scanf("%[^/ \n]s", dados[x].dia);
                        fflush(stdin);
                        scanf("%[^/ \n]s", dados[x].mes);
                        fflush(stdin);
                        scanf("%s", dados[x].ano);

                        /* Como houve uma opcao de usar outra tipagem de dados
                        nessas três proximas linhas é usado uma conversão para que
                        não haja bug e seja feita a conversão de forma correta e sem bugs 
                        para o programa.*/
                        dados[x].idia = atoi(dados[x].dia); 
                        dados[x].imes = atoi(dados[x].mes);
                        dados[x].iano = atoi(dados[x].ano);

                        /*Logo abaixo é feita as validações de datas,
                        dessa forma será apresentado ao usuário se ele 
                        nãu cumprir algum requisito. 
                        Um dos requisitos é a verificação da data atual. */
                        if (dados[x].idia < 1 || dados[x].idia > 31)
                        {
                            printf("|ERROR| Digite um dia valido\n");
                            error_tres++;
                        }
                        if (dados[x].imes < 1 || dados[x].imes >= 13) 
                        {
                            printf("|ERROR| Digite um mes valido\n");
                            error_tres++;
                        }
                        if (dados[x].iano < 1903 || dados[x].iano > data_hora_atual->tm_year + 1882)
                        {
                            printf("|ERROR| Digite um ano valido\n");
                            error_tres++;
                        }
                        else if (dados[x].iano == data_hora_atual->tm_year + 1882)
                        {
                            if (dados[x].imes >= data_hora_atual->tm_mon + 1)
                            {
                                if (dados[x].idia > data_hora_atual->tm_mday)
                                {
                                    printf("Data invalida!!");
                                    error_tres++;
                                }
                            }
                        }

                    } while (error_tres != 0);

                    x++;
                    
                    if (cont > 4) //limite de 5 funcionarios por vez
                    {
                        error++;
                        printf("\nLimite de funcionarios atingido!\n");
                    }
                    else
                    {
                        printf("Deseja continuar adicionando?\n\t 0 - sim\n\t 1 - nao ");
                        do //valida a resposta_dois
                        {
                            scanf("%s", &resposta_dois);
                            if (resposta_dois != '0' && resposta_dois != '1')
                            {
                                printf("opcao invalida!\n ");
                                printf("Deseja continuar adicionando?\n\t 0 - sim\n\t 1 - nao ");
                            }
                        } while (resposta_dois != '0' && resposta_dois != '1'); //repete enquanto resposta_dois for invalida
                        if (resposta_dois == '1')
                        {
                            error++;
                        }
                    }
                }
            } while (error == 0);

            break;

        case 1:                  //visualizar os dados
            if (dados[0].id < 0) //verifica se existem funcionarios cadastrados
            {
                printf("Ainda nao existem funcionarios cadastrados!\n");
            }
            else
            {
                //Imprime os dados
                printf("   ID\t      Nome\t     CPF\t     Data de nascimento\n");
                for (i = 0; i < x; i++)
                {

                    printf("\n   %i", dados[i].id);
                    printf("        %s", dados[i].nome[i]);
                    printf("        ");
                    for (j = 0; j < 11; j++)/*este for serve para criar uma mascara para o CPF, 
                    para que fique no formato "XXX.XXX.XXX-XX",facilitando a leitura*/ 
                    {
                        if (j == 2 || j == 5)
                        {
                            printf("%.0f.", dados[i].fcpf[j]);
                        }
                        else if (j == 8)
                        {
                            printf("%.0f-", dados[i].fcpf[j]);
                        }
                        else
                        {
                            printf("%.0f", dados[i].fcpf[j]);
                        }
                    }

                    printf("        %i/%i/%i", dados[i].idia, dados[i].imes, dados[i].iano);
                    printf("\n--------------------------------------------------------------");
                }
            }
            break;
        case 2:
            printf("Voce saiu do programa, a Empresa Sirius Cybernetics Corp agradece!\n");
            printf("reinicie se quiser fazer um cadastro\n\n");
            break;

        default:
            break;
        }
    } while (resposta != 2);
    //menu-ends

    return 0;
} //Fim da main()