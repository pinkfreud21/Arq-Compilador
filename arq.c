#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct Label
{
    char conteudo[7];
    int linha;
} Label;

Label defineLabel(Label a, char *opcode1, int linha)
{
    char aux[7]; // salvar o conteudo da label
    for (int i = 0; i < 6; i++)
    {
        aux[i] = opcode1[i + 2];
    }
    strcpy(a.conteudo, aux);
    a.linha = linha;
    return a;
}

void printarRegistradores(int registradores[])
{
    printf("Registradores utilizados:\n");
    if (registradores[0] != 0)
    {
        printf("Registrador AX: %d\n", registradores[0]);
    }
    if (registradores[1] != 0)
    {
        printf("Registrador CX: %d\n", registradores[1]);
    }
    if (registradores[2] != 0)
    {
        printf("Registrador DX: %d\n", registradores[2]);
    }
    if (registradores[3] != 0)
    {
        printf("Registrador BX: %d\n", registradores[3]);
    }
    if (registradores[4] != 0)
    {
        printf("Registrador SP: %d\n", registradores[4]);
    }
    if (registradores[5] != 0)
    {
        printf("Registrador BP: %d\n", registradores[5]);
    }
    if (registradores[6] != 0)
    {
        printf("Registrador SI: %d\n", registradores[6]);
    }
    if (registradores[7] != 0)
    {
        printf("Registrador DI: %d\n", registradores[7]);
    }
}

int posicaoReg(char *reg)
{
    int valorRegistrador = -1;

    if (strcmp(reg, "000") == 0)
    {
        // AX
        valorRegistrador = 0;
    }
    else if (strcmp(reg, "001") == 0)
    {
        valorRegistrador = 1;
        // CX
    }
    else if (strcmp(reg, "010") == 0)
    {
        valorRegistrador = 2;
        // DX
    }
    else if (strcmp(reg, "011") == 0)
    {
        valorRegistrador = 3;
        // BX
    }
    else if (strcmp(reg, "100") == 0)
    {
        valorRegistrador = 4;
        // SP
    }
    else if (strcmp(reg, "101") == 0)
    {
        valorRegistrador = 5;
        // BP
    }
    else if (strcmp(reg, "110") == 0)
    {
        valorRegistrador = 6;
        // SI
    }
    else if (strcmp(reg, "111") == 0)
    {
        valorRegistrador = 7;
        // DI
    }

    return valorRegistrador;
}

int verificaReg1(char *opcode1) // retorna a posicao do vetor reg1
{
    char vetor[4];
    vetor[0] = opcode1[2];
    vetor[1] = opcode1[3];
    vetor[2] = opcode1[4];
    vetor[3] = '\0';

    return posicaoReg(vetor);
}

int verificaReg2(char *opcode1) // retorna a posicao do vetor reg2
{
    char vetor[4];
    vetor[0] = opcode1[5];
    vetor[1] = opcode1[6];
    vetor[2] = opcode1[7];
    vetor[3] = '\0';

    return posicaoReg(vetor);
}

void zerarVetor(int vetor[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        vetor[i] = 0;
    }
}

double minhaPow(double base, int expoente)
{
    double resultado = 1.0;

    if (expoente >= 0)
    {
        for (int i = 0; i < expoente; i++)
        {
            resultado *= base;
        }
    }
    else
    {
        for (int i = 0; i < -expoente; i++)
        {
            resultado /= base;
        }
    }

    return resultado;
}

void multR(int *registradores, char *opcode1)
{
    int reg1 = verificaReg1(opcode1);
    int reg2 = verificaReg2(opcode1);

    registradores[reg1] = registradores[reg1] * registradores[reg2];
}

void subR(int *registradores, char *opcode1)
{
    int reg1 = verificaReg1(opcode1);
    int reg2 = verificaReg2(opcode1);

    registradores[reg1] = registradores[reg1] - registradores[reg2];
}

void addR(int *registradores, char *opcode1)
{
    int reg1 = verificaReg1(opcode1);
    int reg2 = verificaReg2(opcode1);

    registradores[reg1] = registradores[reg1] + registradores[reg2];
}

void divR(int *registradores, char *opcode1)
{
    int reg1 = verificaReg1(opcode1);
    int reg2 = verificaReg2(opcode1);

    registradores[reg1] = registradores[reg1] / registradores[reg2];
}

void moveR(int *registradores, char *opcode1)
{
    int reg1 = verificaReg1(opcode1);
    int reg2 = verificaReg2(opcode1);

    registradores[reg1] = registradores[reg2];
}

int converteBinarioPDecimal(char opcode1[])
{
    int decimal = 0;
    char vetor[3];
    // RM obtido com as 3 linhas abaixo
    vetor[0] = opcode1[5];
    vetor[1] = opcode1[6];
    vetor[2] = opcode1[7];

    for (int i = 0; i < 3; i++)
    {
        decimal += (vetor[i] - '0') * minhaPow(2, 2 - i);
    }

    return decimal;
}

int atualizaOpcodeReg(char opcode1[], int *registradoresUtilizados)
{
    char reg[4];
    int valorRegistrador = 0;
    for (int i = 0; i < 8; i++) // leitura do opcode
    {
        if (i < 5)
        {
            reg[i - 2] = opcode1[i];
        }
    }

    valorRegistrador = posicaoReg(reg);

    registradoresUtilizados[valorRegistrador] = 1;

    return valorRegistrador;
}

void moveI(int *registradores, char *opcode1)
{
    // funcao retorna a posicao do registrador que vou modificar
    int valorRegistrador = verificaReg1(opcode1);

    registradores[valorRegistrador] = converteBinarioPDecimal(opcode1);
}

void addI(int *registradores, char *opcode1)
{
    // funcao retorna a posicao do registrador que vou modificar
    int valorRegistrador = verificaReg1(opcode1);

    registradores[valorRegistrador] = registradores[valorRegistrador] + converteBinarioPDecimal(opcode1);
}

void subI(int *registradores, char *opcode1)
{
    // funcao retorna a posicao do registrador que vou modificar
    int valorRegistrador = verificaReg1(opcode1);

    registradores[valorRegistrador] = registradores[valorRegistrador] - converteBinarioPDecimal(opcode1);
}

void funcaoAnd(int *registradores, char *opcode1)
{
    int reg1 = verificaReg1(opcode1);
    int reg2 = verificaReg2(opcode1);

    registradores[reg1] = registradores[reg1] & registradores[reg2];
}

void funcaoOr(int *registradores, char *opcode1)
{
    int reg1 = verificaReg1(opcode1);
    int reg2 = verificaReg2(opcode1);

    registradores[reg1] = registradores[reg1] | registradores[reg2];
}

void funcaoXor(int *registradores, char *opcode1)
{
    int reg1 = verificaReg1(opcode1);
    int reg2 = verificaReg2(opcode1);

    registradores[reg1] = registradores[reg1] ^ registradores[reg2];
}

void funcaoShl(int *registradores, char *opcode1)
{
    int reg1 = verificaReg1(opcode1);

    registradores[reg1] = registradores[reg1] << converteBinarioPDecimal(opcode1);
}

void funcaoShr(int *registradores, char *opcode1)
{
    int reg1 = verificaReg1(opcode1);

    registradores[reg1] = registradores[reg1] >> converteBinarioPDecimal(opcode1);
}

void funcaoCompila(char *opcode, int *registradores, char opcode1[])
{
    opcode[8] = '\0';
    if (strcmp(opcode, "10001000") == 0)
    {
        // funcao mover reg / reg memo
        moveR(registradores, opcode1);
    }
    else if (strcmp(opcode, "11000110") == 0)
    {
        // funcao mover reg/ i
        moveI(registradores, opcode1);
    }
    else if (strcmp(opcode, "00000000") == 0)
    {
        // funcao add reg / reg
        addR(registradores, opcode1);
    }
    else if (strcmp(opcode, "10000000") == 0)
    {
        // funcao addi reg / i
        addI(registradores, opcode1);
    }
    else if (strcmp(opcode, "00101000") == 0)
    {
        // funcao sub reg / reg
        subR(registradores, opcode1);
    }
    else if (strcmp(opcode, "10000010") == 0)
    {
        // funcao sub reg / i
        subI(registradores, opcode1);
    }
    else if (strcmp(opcode, "11110110") == 0)
    {
        // funcao mul reg /reg
        multR(registradores, opcode1);
    }
    else if (strcmp(opcode, "11110110") == 0)
    {
        // funcao div reg / reg
        divR(registradores, opcode1);
    }
    else if (strcmp(opcode, "00100000") == 0)
    {
        // funca and reg / reg
        funcaoAnd(registradores, opcode1);
    }
    else if (strcmp(opcode, "00001000") == 0)
    {
        // funcao or reg /reg  101 001 001
        funcaoOr(registradores, opcode1);
    }
    else if (strcmp(opcode, "00110000") == 0)
    {
        // funcao xor reg / reg
        funcaoXor(registradores, opcode1);
    }
    else if (strcmp(opcode, "11010000") == 0)
    {
        // funcao sll shl
        funcaoShl(registradores, opcode1);
    }
    else if (strcmp(opcode, "11010010") == 0)
    {
        // funcao srl shr
        funcaoShr(registradores, opcode1);
    }
}

int verificaSyscall(char *opcode)
{
    int valor = 0; // definido como falso por padrao
    if (strcmp(opcode, "11001101") == 0)
    {
        valor = 1;
    }

    return valor;
}

int verificaLabel(char *opcode) // 1 - verdadeiro // 0 - falso
{
    int valor = 0; // definido como falso por padrao
    if (strcmp(opcode, "11100011") == 0)
    {
        valor = 1;
    }

    return valor;
}

int verificaJump(char *opcode) // 1 - verdadeiro // 0 - falso
{
    int valor = 0; // definido como falso por padrao
    if (strcmp(opcode, "11101001") == 0)
    {
        valor = 1;
    }

    return valor;
}

int verificaJe(char *opcode) // 1 - verdadeiro // 0 - falso
{
    int valor = 0; // definido como falso por padrao
    if (strcmp(opcode, "01110100") == 0)
    {
        valor = 1;
    }

    return valor;
}

int verificaJne(char *opcode) // 1 - verdadeiro // 0 - falso
{
    int valor = 0; // definido como falso por padrao
    if (strcmp(opcode, "01110101") == 0)
    {
        valor = 1;
    }

    return valor;
}

int verificaCmp(char *opcode) // 1 - verdadeiro // 0 - falso
{
    int valor = 0; // definido como falso por padrao
    if (strcmp(opcode, "00111000") == 0)
    {
        valor = 1;
    }

    return valor;
}

void iniciaLabel(Label *lista, int qtd) //seta valores para 0
{
    for (int i = 0; i < qtd; i++)
    {
        memset(lista[i].conteudo, 0, sizeof(lista[i].conteudo));
        lista[i].linha = 0;
    }
}

int pularNoArquivo(FILE *arq, Label *listaLabel, int qtdLabel, char *opcode1, int linhaAtual)
{
    char aux[7];       // salvar o conteudo da label
    int Encontrou = 0; // 0 - nao achou / 1 - encontrou
    int valorAchado = 0;
    int find = 0; // auxiliar segundo encontrou // caso nao ache na lista de label
    int valor = 0;
    for (int i = 0; i < 6; i++) // salvando na label
    {
        aux[i] = opcode1[i + 2];
    }

    for (int j = 0; j < qtdLabel; j++)
    {
        if (strcmp(listaLabel[j].conteudo, aux) == 0)
        {
            Encontrou = 1;
            valorAchado = j;
        }
    }

    if (Encontrou)
    {
        valor = listaLabel[valorAchado].linha * 16;
        fseek(arq, valor, SEEK_SET);
    }
    else
    {
        char linha[9]; // pega as primeiras 8 // posicao 9 é o \0
        int index = 2;

        while (fgets(linha, sizeof(linha), arq) != NULL) // procurando a label
        {
            if (index % 2 == 0)
            {
                if (verificaLabel(linha)) // encontrou uma label, tem que verificar se é a mesma para pular
                {
                    find = 1;
                }
            }
            index++;
            if (find) // se for a mesma que é para pular, sai do programa e pula
            {
                if (strcmp(linha, aux) == 0) // verifica se é a mesma
                {
                    break;
                }
                else
                { // se nao for a mesma, define que nao encontrou a variavel para pular
                    find = 0;
                }
            }
            
        }

        if (find) // pulando caso encontrou
        {
            linhaAtual = linhaAtual + (index - 1); // valor atualizado da linha que terei que pular
            valor = linhaAtual * 16;
            fseek(arq, valor, SEEK_SET);
        }
    }
    return (valor / 16);
}

int main()
{
    FILE *arq = fopen("input1.txt", "r");
    char c;
    Label listaLabel[10];
    iniciaLabel(listaLabel, 10);
    int qtdLabel = 0;
    int registradores[8];           // 0-AX; 1-CX; 2-DX; 3-BX; 4-SP; 5-BP; 6-SI; 7-DI
    int registradoresUtilizados[8]; // 1 - verdadeiro / 0 - falso
    char opcode[8];
    char opcode1[8];
    int aux = 0;    // auxiliar indicando as variaveis acima / 0 - opcode / 1 - opcode1
    int linhas = 0; // quantidade de linhas(16bits) cada
    int flag = 0;   // valor da flag, onde se compara o je/jne

    int index = 0;

    if (arq == NULL)
    {
        printf("Erro ao ler o arquivo");
        exit(1);
    }

    zerarVetor(registradores, 8);
    zerarVetor(registradoresUtilizados, 8);

    while (1)
    {
        c = fgetc(arq);
        if (c == EOF)
        {
            break;
        }
        if (!aux)
        {
            opcode[index] = c;
        }
        else
        {
            opcode1[index] = c;
        }

        if (index == 7)
        {
            aux++;
            index = 0;
            if (aux == 2)
            {
                aux = 0;
                linhas++;

                if (verificaSyscall(opcode))
                {
                    // finaliza o programa
                    break;
                }
                else if (verificaCmp(opcode))
                {
                    // caso cmp, verifica 2 reg e salva na flag
                    if (registradores[verificaReg1(opcode1)] == registradores[verificaReg2(opcode1)])
                    {
                        flag = 1;
                    }
                    else
                    {
                        flag = 0;
                    }
                }
                else if (verificaLabel(opcode))
                {
                    // caso for label savar as informacoes da label
                    listaLabel[qtdLabel] = defineLabel(listaLabel[qtdLabel], opcode1, linhas);
                    qtdLabel++;
                }
                // verificar casos jump 11101001, jne 01110101, je 01110100
                else if (verificaJump(opcode))
                {
                    linhas = pularNoArquivo(arq, listaLabel, qtdLabel, opcode1, linhas);
                }
                else if (verificaJne(opcode))
                {
                    if (!flag)
                    {
                        linhas = pularNoArquivo(arq, listaLabel, qtdLabel, opcode1, linhas);
                    }
                }
                else if (verificaJe(opcode))
                {
                    if (flag)
                    {
                        linhas = pularNoArquivo(arq, listaLabel, qtdLabel, opcode1, linhas);
                    }
                }
                else
                {
                    funcaoCompila(opcode, registradores, opcode1);
                }
            }
        }
        else
        {
            index++;
        }
    }
    printarRegistradores(registradores);
}