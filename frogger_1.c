#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>

FILE *arq;
FILE *arq2;
FILE *arq3;

typedef struct tipo_dados
{
    char objeto;
    int tamanho;
    int espacamento;
    float velocidade;
    int linha_inicial;
    int coluna_inicial;

}TIPO_DADOS;

//////////////////////////////////////////////////////////////Fun��es do sistema///////////////////////////////////////////////////////////
void retira_cursor ()
{
    HANDLE myconsole = GetStdHandle (STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CURSOR;
    CURSOR.dwSize = 1;
    CURSOR.bVisible = FALSE;
    SetConsoleCursorInfo (myconsole, &CURSOR); // declara��es para esconder o cursor do console (o "underline")
}

void esperar(float segundos)
{
clock_t cicloFinal;

cicloFinal= clock() + segundos * CLOCKS_PER_SEC; /* Calcula o ciclo final de acordo com os segundos passados. */
while (clock() < cicloFinal); /* Para quando o ciclo final e atingido. */
}

void clearscreen() // essa fun��o est� sendo utilizada no lugar do system("cls") para otimizar a jogabilidade (a tela pisca menos)
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle (STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

int abre_arquivo(int save)
{
   switch(save)
   {
    case 0:
    arq2 = fopen("captura_da_tela.txt","w");//se save for igual a 0 abre o arquivo texto em modo escrita
        if(!arq2)
        {
            printf("Erro de abertura\n");//retorna -1 caso haja erro de abertura
            return -1;
        }
        break;
    case 1:
    arq=fopen("fases.bin","rb");//se o save for igual a 1 abre o arquivo binario em modo leitura
        if(!arq)
        {
            printf("Erro de abertura!\n");
            return -1;
        }
        break;
    case 2:
    arq3=fopen("save.txt","r");//se save for igual a 2 abre o arquivo texto em modo leitura
        if(!arq3)
        {
            printf("Erro de abertura!\n");
            return -1;
        }
        break;
    case 3:
    arq3=fopen("save.txt","wr");//se save for igual a 3 abre o arquivo texto em modo escrita
        if(!arq3)
        {
            printf("Erro de abertura!\n");
            return -1;
        }
        break;
   }
}
//////////////////////////////////////////////////////////////Fun��es do jogo//////////////////////////////////////////////////////////////
void game_over()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &ConsoleInfo); // DEFINI��ES PARA USAR AS CORES
    int originalAttrs = ConsoleInfo.wAttributes;

    char bloco = 177;

    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("    %c%c%c%c%c %c%c%c%c%c %c   %c %c%c%c%c%c   %c%c%c%c%c %c   %c %c%c%c%c%c %c%c%c%c%c\n", bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco);
    printf("    %c     %c   %c %c%c %c%c %c       %c   %c %c   %c %c     %c   %c\n"); // aqui n�o precisa mais de ", bloco"
    printf("    %c  %c%c %c%c%c%c%c %c %c %c %c%c%c%c    %c   %c  %c %c  %c%c%c%c  %c%c%c%c%c\n");
    printf("    %c   %c %c   %c %c   %c %c       %c   %c  %c %c  %c     %c  %c\n");
    printf("    %c%c%c%c%c %c   %c %c   %c %c%c%c%c%c   %c%c%c%c%c   %c   %c%c%c%c%c %c   %c\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    system("pause");



}

void passa_fase()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &ConsoleInfo); // DEFINI��ES PARA USAR AS CORES
    int originalAttrs = ConsoleInfo.wAttributes;

    char bloco = 177;



    system("cls");

    SetConsoleTextAttribute(hConsole, 10);
    printf("\n\n\n\n\n\n\n");
    printf("         %c%c%c%c %c%c%c%c %c%c%c%c  %c   %c  %c  %c   %c %c%c%c%c\n", bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco);
    printf("         %c  %c %c  %c %c  %c   %c %c   %c  %c%c %c%c %c  %c\n");
    printf("         %c%c%c%c %c%c%c%c %c  %c    %c    %c  %c %c %c %c%c%c%c\n");
    printf("         %c    %c %c  %c  %c   %c %c   %c  %c   %c %c  %c\n");
    printf("         %c    %c  %c %c%c%c%c  %c   %c  %c  %c   %c %c  %c\n\n\n");
    printf("             %c%c%c%c%c %c%c%c%c%c   %c%c%c%c%c%c   %c%c%c%c%c\n");
    printf("             %c     %c   %c   %c%c       %c\n");
    printf("             %c%c%c   %c%c%c%c%c     %c%c     %c%c%c%c\n");
    printf("             %c     %c   %c       %c%c   %c\n");
    printf("             %c     %c   %c   %c%c%c%c%c%c   %c%c%c%c%c\n\n\n\n\n\n\n\n");
}

void salva_matriz(char mapasav[26][56])
{
    int i,j;

    for(i=0;i<26;i++)
    {
        for(j=0;j<56;j++)
        {
        fprintf(arq2,"%c",mapasav[i][j]);//salva a matriz mapa

        }
            fprintf(arq2,"\n");//quebra linha para alinhar o save
    }
    fclose(arq2);
}

void instruct ()
{
    puts("Instrucoes:");
    puts("O movimento do jogo eh feito pelas teclas direcionais.");
    printf("O botao Q permite salvar seu progresso no jogo ou sair\n");
    printf("dele.\n");
    puts("Aproveite  o jogo!");
}

void menu ()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &ConsoleInfo);

    int originalAttrs = ConsoleInfo.wAttributes;
    int i, k=0;
    char bloco=177;// NAO FOI POSSIVEL UTILIZAR O CARACTER DO BLOCO DIRETAMENTE NO PRINTF, ENT�O FOI NECESSARIO USAR UMA VARIAVEL CHAR



    printf("\n\n");
    clearscreen();


    SetConsoleTextAttribute(hConsole, 10);

    printf(" \n\n\n");
    printf("     _______________________________________________\n");
    printf("   ||   %c%c%c%c%c %c%c%c%c%c %c%c%c%c%c %c%c%c%c%c %c%c%c%c%c %c%c%c%c%c %c%c%c%c%c   ||\n", bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco);
    printf("  |||   %c     %c   %c %c   %c %c     %c     %c     %c   %c   |||\n"); // a partir daqui, n�o precisa mais de ", bloco"
    printf(" ||||   %c%c%c%c  %c%c%c%c%c %c   %c %c  %c%c %c  %c%c %c%c%c   %c%c%c%c%c   ||||");
    printf("  ||||   %c     %c  %c  %c   %c %c   %c %c   %c %c     %c  %c    ||||");
    printf("   |||   %c     %c   %c %c%c%c%c%c %c%c%c%c%c %c%c%c%c%c %c%c%c%c%c %c   %c   |||");
    printf("     ||_______________________________________________||");
    SetConsoleTextAttribute(hConsole, 15);
    printf("                                 by nPride & MadLaipe   ");
    SetConsoleTextAttribute(hConsole, 11);
    printf("\n\n\n\n\n");
    printf("         1 - Jogar \n ");
    printf("\n");
    printf("         2 - Carregar jogo salvo\n");
    printf("\n");
    printf("         3 - Instrucoes\n");
    printf("\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("         4 - Sair \n\n\n");
    SetConsoleTextAttribute(hConsole, 15);
}
void vitoria_img()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &ConsoleInfo); // DEFINI��ES PARA USAR AS CORES
    int originalAttrs = ConsoleInfo.wAttributes;

    char bloco = 177;

    system("cls");

    SetConsoleTextAttribute(hConsole, 10);
    printf("\n\n\n\n\n\n\n\n\n");
    printf("         %c   %c  %c  %c%c%c%c%c %c%c%c%c %c%c%c%c%c %c %c%c%c%c%c %c%c\n", bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco, bloco);
    printf("         %c   %c  %c    %c   %c  %c %c   %c %c %c   %c %c%c\n");
    printf("          %c %c   %c    %c   %c  %c %c%c%c%c%c %c %c%c%c%c%c %c%c\n");
    printf("          %c %c   %c    %c   %c  %c %c  %c  %c %c   %c\n");
    printf("           %c    %c    %c   %c%c%c%c %c   %c %c %c   %c %c%c\n");
    printf("\n\n\n\n\n\n\n\n");
    system("pause");

}

void limpa_matriz(char mapa[26][56])//limpa a matriz do jogo
{
    int i;

    for (i=0; i<2; i++) //Inicializa��o do mapa
    {
        strcpy(mapa[i], "      |**|      |**|      |**|      |**|      |**|           ");//linhas 1,2
    }
    for (i=2; i<12; i++)
    {
        strcpy(mapa[i], "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     ");//linhas 3,4,5,6,7,8,9,10,11,12
    }
    for (i=12;i<26;i++)
    {
        strcpy(mapa[i], "                                                             ");//linhas 13,14,15,16,17,18,19,20,21,22,23,24,25,26
    }
}

void preenche_matriz (char mapa[26][56], int x, int y, int tam, char type, int cont,float vel)//insere todos os caracteres moveis da matriz
{

    int i,j;
    char turtleU[2][2] = {"/\\","\\/"};//contem os dados da tartaruga quando esta encima da agua
    char turtleW[2][2] = {"\\/","/\\"};//contem os dados da tartaruga quando esta para submergir
    char turtleD[2][2] = {"~~","~~"};//contem os dados da tartaruga abaixo da agua
    char wood[2][2] = {"##","##"};//contem os dados do tronco
    char sapo[2][2] = {"@@","00"};//contem os dados do sapo
    char carrod[2][8]={{"_|=\\__"},{"/o___o_\\"}};//contem os dados do carro da direita
    char carroe[2][8]={{"__/=|_"},{"/_o___o|"}};//contem os dados do carro da esquerda

    x=2*x;//x � multiplicado por 2 pois n�o � um mapa de unidades
    y=2*y;//y � multiplicado por 2 pois n�o � um mapa de unidades


    switch(type)
    {
        case 'R':

         do
        {
            for(i=0;i<2;i++)
            {
            for(j=0;j<2;j++)
            {
                if(cont>=0 && cont<=40)
                {
                   mapa[y+i][x+j]=turtleU[i][j];//troca caracter por caracter da matriz onde x e y s�o as posi�oes iniciais
                }
                if(cont>=41 && cont<=50)
                {
                    mapa[y+i][x+j]=turtleW[i][j];//troca caracter por caracter da matriz onde x e y s�o as posi�oes iniciais
                }
                if(cont>=51 && cont<=70)
                {
                    mapa[y+i][x+j]=turtleD[i][j];//troca caracter por caracter da matriz onde x e y s�o as posi�oes iniciais
                }
                if(cont>=71 && cont<=85)
                {
                    mapa[y+i][x+j]=turtleW[i][j];//troca caracter por caracter da matriz onde x e y s�o as posi�oes iniciais
                }

            }
            }
            x=x+2;//faz a matriz andar dois para o lado, assim no reescreve encima da primeira
            tam--;//diminue uma intera��o
        }while(tam!=0);//termina quando bloco =0
        break;

        case 'T':
            do
            {

            for(i=0;i<2;i++)
            {
            for(j=0;j<2;j++)
            {
                mapa[y+i][x+j]=wood[i][j];//troca caracter por caracter da matriz onde x e y s�o as posi�oes iniciais
            }

            }
            x=x+2;//faz a matriz andar dois para o lado, assim no reescreve encima da primeira
            tam--;//diminue uma intera��o
        }while(tam!=0);//termina quando bloco =0
        break;

        case 'C':
            if(vel>0)
            {
                for(i=0;i<2;i++)
                {
                for(j=0;j<8;j++)
                {
                    mapa[y+i][x+j]=carrod[i][j];//troca caracter por caracter da matriz onde x e y s�o as posi�oes iniciais
                }
                x--;//core��o do carro n�o ficar alinhado
                }
            }
            else
            {
                for(i=0;i<2;i++)
                {
                for(j=0;j<8;j++)
                {
                    mapa[y+i][x+j]=carroe[i][j];//troca caracter por caracter da matriz onde x e y s�o as posi�oes iniciais
                }
                x--;//core��o do carro n�o ficar alinhado
                }
            }
        break;

        case 'S':
            for(i=0;i<2;i++)
            {
            for(j=0;j<2;j++)
            {
                mapa[y+i][x+j]=sapo[i][j];//troca caracter por caracter da matriz onde x e y s�o as posi�oes iniciais
            }

            }
        break;

    }
}
int morte(char mapa[26][56], int x,int y)
{
    char turtleU[2][2] = {"/\\","\\/"};//contem os dados da tartaruga quando esta encima da agua
    char turtleW[2][2] = {"\\/","/\\"};//contem os dados da tartaruga quando esta para submergir
    char turtleD[2][2] = {"~~","~~"};//contem os dados da tartaruga abaixo da agua
    char wood[2][2] = {"##","##"};//contem os dados do tronco
    char sapo[2][2] = {"@@","00"};//contem os dados do sapo
    char carrod[2][8]={{"_|=\\__"},{"/o___o_\\"}};//contem os dados do carro da direita
    char carroe[2][8]={{"__/=|_"},{"/_o___o|"}};//contem os dados do carro da esquerda
    int i,j;

        x=2*x;//x � multiplicado por 2 pois n�o � um mapa de unidades
        y=2*y;//y � multiplicado por 2 pois n�o � um mapa de unidades

    if(y<24 && y>10)
    {//morre se tocar em qualquer um desses caracteres , varia de 12~5 para pegar apenas os carros
        if(mapa[y][x]=='~' || mapa[y][x]=='_' || mapa[y][x]=='|' || mapa[y][x]=='\\' || mapa[y][x]=='=' || mapa[y][x+2]=='_' || mapa[y][x-1]=='_' )
            {
                return 1;
            }
    }

    if(mapa[y][x]=='~')//more se tocar na agua
    {
        return 1;
    }
    if(y<2)
    {
        if(mapa[y][x]==' ')//more se tocar nos espa�os vazio peto da toca
    {
        return 1;
    }
    }
    else

        return 0;
}

int vitoria(char mapa[26][56], int x,int y)
{
        x=2*x;//x � multiplicado por 2 pois n�o � um mapa de unidades
        y=2*y;//y � multiplicado por 2 pois n�o � um mapa de unidades


    if(mapa[y][x]=='*' || mapa[y][x+1]=='*' )//se o sapo ocupar a posi��o onde esta o *, passa de fase
    {
        return 1;
    }

}


int troca_vel (char mapa[26][56], int x,int y)
{
    //5 para o tartaruga 2x8
    //4 para o tronco 2x4
    //3 para o tartaruga 2x4
    //2 para o tronco 2x8
    //1 para o tartaruga 2x6

        x=2*x;
        y=2*y;

    int i;

            if(y==4 || y==8)
            {
                 //se x ou x+1 estiver sobre um desses caracteres tera sua velocidade alterada para a do objeto
                if(mapa[y][x]=='#' || mapa[y][x-1]=='#' || mapa[y][x+1]=='#')
                {

                    return y;
                }
            }

            if(y==2 || y==6 || y==10)
            {
                //se x ou x+1 estiver sobre um desses caracteres tera sua velocidade alterada para a do objeto
                if(mapa[y][x]=='/' || mapa[y][x]=='\\' || mapa[y][x+1]=='\\' || mapa[y][x+1]=='\\')
                {

                    return y;
                }
            }

}

int main ()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &ConsoleInfo);
    int originalAttrs = ConsoleInfo.wAttributes; // declara��es para o uso de cores


    char mapa[26][56];//matrix do mapa
    int i,j=0;//contadores
    int y[11],tam[11],esp[11],posx[11];//posicao inicial Y, o tamanho do elemento e seu espa�amento
    float x[27],ve[11];//x � definido como float para que assim a velocidade possa variar
    int k=0;//impede a saida do loop
    int op=0,op1=80;//variavel necessaria para inverter as tartarugas
    char inf[255];//linha a qual recebe as informa��es do texto
    char cod,cod1;//recebem a resposta do getch
    char obj[11];//recebe as informa��es do arquivo que determinam o objeto
    int sav;//determina o tipo de save que abrira ao jogo
    int vida=3,dif=0;//variavel responsavel pela vida e dificuldade
    float pont=100;//pontua��o
    TIPO_DADOS dados;//variavel da struct


    system("TITLE Frogger v4.0b ~ by nPride e MadLaipe");//titulo
    system("mode con:cols=57 lines=31");//altera o tamanho da janela
    retira_cursor();//retira o underscore da tela

        do//loop do menu, s� sai se o usuario escolher um arquivo a ser carregado
        {


            menu();//imprime o menu
            fflush(stdin);
            cod1=getch();//recebe a resposta de entrada
            switch(cod1)
            {
                case '1': abre_arquivo(1);//abre o fases.bin
                          sav=1;
                          break;
                case '2': abre_arquivo(2);//abre o save.txt
                          sav=2;
                          break;
                case '3': instruct();//Instru��es
                          system("pause");//s� sai das instru��es caso um tecla for presionada
                          break;
                case '4':
                          return 0;//finaliza o programa
                          break;
            }

        }while(cod1=='3');//repete caso o usuario olhe as intru�oes

                if(sav==1)//se save for igual a 1 ele retira as informa��es do fases.bin
                {
                    for(j=0;j<11;j++)//percorre o arquivo fases.bin\\antes estava usando do/while(feof(arq)) ele fazia uma intera��o a mais, bugando os valores
                    {
                    fread(&dados,sizeof(TIPO_DADOS),1,arq);
                    obj[j]=dados.objeto;//armaze os dados em um vetor de objetos
                    tam[j]=dados.tamanho;//armazena os dados em um vetor de tamanhos
                    esp[j]=dados.espacamento;//armazena os dados em um vetor de espa�amentos
                    y[j]=dados.linha_inicial;//armazena os dados em um vetor de posi��o y
                    posx[j]=dados.coluna_inicial;//armazena os dados em um vetor de posi��o x
                    ve[j]=dados.velocidade;//armazena os dados em um vetor de velocidades
                    }
                }

                if(sav==2)//se save for igual a 1 ele retira as informa��es do fsave.txt
                {
                    for(j=0;j<11;j++)//percorre o arquivo save.txt\\antes estava usando do/while(feof(arq)) ele fazia uma intera��o a mais, bugando os valores
                    {

                    obj[j]=getc(arq3);//armaze os dados em um vetor de objetos
                    fgets(inf,255,arq3);//le a linha do arquivo texto
                    tam[j]=atoi(strtok(inf," "));//armazena os dados em um vetor de tamanhos
                    esp[j]=atoi(strtok(NULL," "));//armazena os dados em um vetor de espa�amentos
                    posx[j]=atoi(strtok(NULL," "));//armazena os dados em um vetor de posi��o y
                    y[j]=atoi(strtok(NULL," "));//armazena os dados em um vetor de posi��o x
                    ve[j]=atof(strtok(NULL," "));//armazena os dados em um vetor de velocidades
                    vida=atoi(strtok(NULL," "));//numero de vidas no momento do save
                    dif=atoi(strtok(NULL," "));//dificuldade no momento do save
                    pont=atof(strtok(NULL," "));//pontua��o no momento do save
                    }

                }


                    //declara��o da variavel posi��o
                        x[0]=posx[0];//carro
                        x[1]=posx[0]+esp[0]+tam[0];//carro 2.1
                        x[2]=posx[1];//carro
                        x[3]=posx[1]+esp[1]+tam[1];//carro 2.2
                        x[4]=posx[2];//carro
                        x[5]=posx[2]+esp[2]+tam[2];//carro 2.3
                        x[6]=posx[3];//carro
                        x[7]=posx[3]+esp[3]+tam[3];//carro 2.4
                        x[8]=posx[4];//carro
                        x[9]=posx[4]+esp[4]+tam[4];//carro 2.5
                        x[10]=posx[5];//tronco
                        x[11]=posx[5]+tam[5]+esp[5];//tronco 2.1
                        x[12]=posx[5]+2*tam[5]+2*esp[5]; //tronco 3.1
                        x[13]=posx[6];//tronco
                        x[14]=posx[6]+esp[6]+tam[6]; //tronco 2.2
                        x[15]=posx[6]+2*esp[6]+2*tam[6]; //tronco 3.2
                        x[16]=posx[7];//tartaruga
                        x[17]=posx[7]+esp[7]+tam[7]; //tartaruga 1.2
                        x[18]=posx[7]+2*esp[7]+2*tam[7]; //tartaruga 1.3
                        x[19]=posx[8];//tartaruga
                        x[20]=posx[8]+esp[8]+tam[8]; //tartaruga 2.2
                        x[21]=posx[8]+2*esp[8]+2*tam[8]; //tartaruga 2.3
                        x[22]=posx[8]+3*esp[8]+3*tam[8]; //tartaruga 2.4
                        x[23]=posx[9]; //tartaruga
                        x[24]=posx[9]+esp[9]+tam[9]; //tartaruga 3.2
                        x[25]=posx[9]+2*esp[9]+2*tam[9]; //tartaruga 3.3
                        x[26]=posx[10];

     do
     {

                             SetConsoleTextAttribute(hConsole, 15); // cor das informa��es acima do jogo (branco)
                                printf("Num. de Vidas: %d \n", vida);
                                printf("       Pontos: %d \n", (int)pont);
                                printf("  Dificuldade: %d \n\n", dif+1);

            limpa_matriz(mapa);//fun��o que reseta a matriz, impedindo os obejtos de deixarem rastros pela matriz
    /////////////////////////////////////////////////////////////CARROS ESQUERDA////////////////////////////////////////////////////////////////
            if(x[2]>=1)//se x for maior que 1 imprime o carro//isso ajuda a diminuir o erro do carro sumir inteiro quando toca a parede e reaparecer inteiro na pos inicial
            {
                preenche_matriz(mapa,x[2],y[1],2*tam[1],obj[1],1,ve[1]);
            }
            if(x[3]>=1)//se x for maior que 1 imprime o carro
            {
                preenche_matriz(mapa,x[3],y[1],2*tam[1],obj[1],1,ve[1]);
            }
            if(x[6]>=1)//se x for maior que 1 imprime o carro
            {
                preenche_matriz(mapa,x[6],y[3],2*tam[3],obj[3],1,ve[3]);
            }
            if(x[7]>=1)//se x for maior que 1 imprime o carro
            {
                preenche_matriz(mapa,x[7],y[3],2*tam[3],obj[3],1,ve[3]);
            }

            x[2]=x[2]+ve[1]-(dif/10);//incrementa a posi��o alterando a sua posi��o na matriz,e altera a dificuldade
            x[3]=x[3]+ve[1]-(dif/10);
            x[6]=x[6]+ve[3]-(dif/10);
            x[7]=x[7]+ve[3]-(dif/10);

            if(x[2]==-esp[1])//condicional que reseta a posi��o do carro //o menos esp retarda a impress�o da do objeto, para assim ele ter o espa�amento suficiente
                {
                    x[2]=25;//reseta o valor para a posi��o inicial da lina
                }
            if(x[3]==-esp[1])//condicional que reseta a posi��o do carro //o menos esp retarda a impress�o da do objeto, para assim ele ter o espa�amento suficiente
                {
                    x[3]=25;
                }
            if(floor(x[6])==-esp[3])//condicional que reseta a posi��o do carro //o menos esp retarda a impress�o da do objeto, para assim ele ter o espa�amento suficiente
                {
                    x[6]=25;
                }
            if(floor(x[7])==-esp[3])//condicional que reseta a posi��o do carro //o menos esp retarda a impress�o da do objeto, para assim ele ter o espa�amento suficiente
                {
                    x[7]=25;
                }
/////////////////////////////////////////////////////////////CARROS DIREITA////////////////////////////////////////////////////////////////
            //se x for menor que 25 imprime o carro//isso ajuda a diminuir o erro do carro sumir inteiro quando toca a parede e reaparecer inteiro na pos inicial
            if(x[0]<=25)
            {
                preenche_matriz(mapa,x[0],y[0],2*tam[0],obj[0],1,ve[0]);
            }
            if(x[1]<=25)
            {
                preenche_matriz(mapa,x[1],y[0],2*tam[0],obj[0],1,ve[0]);
            }
            if(x[4]<=25)
            {
                preenche_matriz(mapa,x[4],y[2],2*tam[2],obj[2],1,ve[2]);
            }
            if(x[5]<=25)
            {
                preenche_matriz(mapa,x[5],y[2],2*tam[2],obj[2],1,ve[2]);
            }
            if(x[8]<=25)
            {
                preenche_matriz(mapa,x[8],y[4],2*tam[4],obj[4],1,ve[4]);
            }
            if(x[9]<=25)
            {
                preenche_matriz(mapa,x[9],y[4],2*tam[4],obj[4],1,ve[4]);
            }

            x[0]=x[0]+ve[0]+(dif/10);//incrementa a posi��o alterando a sua posi��o na matriz,e altera a dificuldade
            x[1]=x[1]+ve[0]+(dif/10);
            x[4]=x[4]+ve[2]+(dif/10);
            x[5]=x[5]+ve[2]+(dif/10);
            x[8]=x[8]+ve[4]+(dif/10);
            x[9]=x[9]+ve[4]+(dif/10);

            if(floor(x[0])==25+esp[0])//condicional que reseta a posi��o do carro//o 25+esp retarda a impress�o da do objeto, para assim ele ter o espa�amento suficiente
                {
                    x[0]=1;
                }

            if(floor(x[1])==25+esp[0])//condicional que reseta a posi��o do carro//o 25+esp retarda a impress�o da do objeto, para assim ele ter o espa�amento suficiente
                {
                    x[1]=1;
                }

            if(floor(x[4])==25+esp[2])//condicional que reseta a posi��o do carro//o 25+esp retarda a impress�o da do objeto, para assim ele ter o espa�amento suficiente
                {
                    x[4]=1;
                }

            if(floor(x[5])==25+esp[2])//condicional que reseta a posi��o do carro//o 25+esp retarda a impress�o da do objeto, para assim ele ter o espa�amento suficiente
                {
                    x[5]=1;
                }

            if(floor(x[8])==25+esp[4])//condicional que reseta a posi��o do carro//o 25+esp retarda a impress�o da do objeto, para assim ele ter o espa�amento suficiente
                {
                    x[8]=1;
                }

            if(floor(x[9])==25+esp[4])//condicional que reseta a posi��o do carro//o 25+esp retarda a impress�o da do objeto, para assim ele ter o espa�amento suficiente
                {
                    x[9]=1;
                }
/////////////////////////////////////////////////////////////////TRONCO////////////////////////////////////////////////////////////////////
            //s� imprime a tronco caso x seja menor que 27
            if(x[10]<=27)
            {
                preenche_matriz(mapa,x[10],y[5],tam[5],obj[5],1,ve[5]);
            }
            if(x[11]<=27)
            {
                preenche_matriz(mapa,x[11],y[5],tam[5],obj[5],1,ve[5]);
            }
            if(x[12]<=27)
            {
                preenche_matriz(mapa,x[12],y[5],tam[5],obj[5],1,ve[5]);
            }
            //s� imprime a tronco caso x seja maior que zero
            if(x[13]>=0)
            {
                preenche_matriz(mapa,x[13],y[6],tam[6],obj[6],1,ve[6]);
            }
            if(x[14]>=0)
            {
                preenche_matriz(mapa,x[14],y[6],tam[6],obj[6],1,ve[6]);
            }
            if(x[15]>=0)
            {
                preenche_matriz(mapa,x[15],y[6],tam[6],obj[6],1,ve[6]);
            }

            x[10]=x[10]+ve[5]+(dif/10);//incrementa a posi��o alterando a sua posi��o na matriz,e altera a dificuldade
            x[11]=x[11]+ve[5]+(dif/10);
            x[12]=x[12]+ve[5]+(dif/10);
            x[13]=x[13]+ve[6]-(dif/10);
            x[14]=x[14]+ve[6]-(dif/10);
            x[15]=x[15]+ve[6]-(dif/10);

            if(floor(x[10])==28+tam[5])//condicional que reseta a posi��o do tronco//o 20+esp retarda a impress�o da do objeto, para assim ele ter o espa�amento suficiente
                {
                    x[10]=0;
                }

            if(floor(x[11])==28+tam[5])//condicional que reseta a posi��o do tronco
                {
                    x[11]=0;
                }

            if(floor(x[12])==28+tam[5])//condicional que reseta a posi��o do tronco
                {
                    x[12]=0;
                }

            if(x[13]<=-esp[6])//condicional que reseta a posi��o do tronco//o 2-esp retarda a impress�o da do objeto, para assim ele ter o espa�amento suficiente
                {
                    x[13]=28-tam[6];
                }

            if(x[14]<=-esp[6])//condicional que reseta a posi��o do tronco
                {
                    x[14]=28-tam[6];
                }

            if(x[15]<=-esp[6])//condicional que reseta a posi��o do tronco
                {
                    x[15]=28-tam[6];
                }
    ////////////////////////////////////////////////////////////////TARTARUGAS/////////////////////////////////////////////////////////////////
            op=op+1;//respons�vel pela troca das tartarugas
            if(op==85)
            {
                op=0;//reseta a variavel respons�vel pela troca de posi��o das tartarugas das pontas
            }
             op1=op1-1;//respons�vel pela troca das tartarugas
            if(op1==0)
            {
                op1=85;//reseta a variavel respons�vel pela troca de posi��o das tartarugas do meio
            }

            //imprime a tartaruga caso x for menor que 25
            if(x[16]<=25)
            {
                preenche_matriz(mapa,x[16],y[7],tam[7],obj[7],op,ve[7]);
            }
            if(x[17]<=25)
            {
                preenche_matriz(mapa,x[17],y[7],tam[7],obj[7],op,ve[7]);
            }
            if(x[18]<=25)
            {
                preenche_matriz(mapa,x[18],y[7],tam[7],obj[7],op,ve[7]);
            }
            //imprime a tartaruga caso x for maior que 0
            if(x[19]>=0)
            {
                preenche_matriz(mapa,x[19],y[8],tam[8],obj[8],op1,ve[8]);
            }
            if(x[20]>=0)
            {
                preenche_matriz(mapa,x[20],y[8],tam[8],obj[8],op1,ve[8]);
            }
            if(x[21]>=0)
            {
                preenche_matriz(mapa,x[21],y[8],tam[8],obj[8],op1,ve[8]);
            }
            if(x[22]>=0)
            {
                preenche_matriz(mapa,x[22],y[8],tam[8],obj[8],op1,ve[8]);
            }
            //imprime a tartaruga caso x for menor que 25
            if(x[23]<=25)
            {
                preenche_matriz(mapa,x[23],y[9],tam[9],obj[9],op,ve[9]);
            }
            if(x[24]<=25)
            {
                preenche_matriz(mapa,x[24],y[9],tam[9],obj[9],op,ve[9]);
            }
            if(x[25]<=25)
            {
                preenche_matriz(mapa,x[25],y[9],tam[9],obj[9],op,ve[9]);
            }

            x[16]=x[16]+ve[7]+(dif/10);
            x[17]=x[17]+ve[7]+(dif/10);
            x[18]=x[18]+ve[7]+(dif/10);
            x[19]=x[19]+ve[8]+(dif/10);
            x[20]=x[20]+ve[8]+(dif/10);
            x[21]=x[21]+ve[8]+(dif/10);
            x[22]=x[22]+ve[8]+(dif/10);
            x[23]=x[23]+ve[9]+(dif/10);
            x[24]=x[24]+ve[9]+(dif/10);
            x[25]=x[25]+ve[9]+(dif/10);

            if(floor(x[16])==25+esp[7])//condicional que reseta a posi��o do tartarugas
                {
                    x[16]=0;
                }

            if(floor(x[17])==25+esp[7])//condicional que reseta a posi��o do tartarugas
                {
                    x[17]=0;
                }

            if(floor(x[18])==25+esp[7])//condicional que reseta a posi��o do tartarugas
                {
                    x[18]=0;
                }

            if(floor(x[19])==2-esp[8])//condicional que reseta a posi��o do tartarugas
                {
                    x[19]=25;
                }

            if(floor(x[20])==2-esp[8])//condicional que reseta a posi��o do tartarugas
                {
                    x[20]=25;
                }

            if(floor(x[21])==2-esp[8])//condicional que reseta a posi��o do tartarugas
                {
                    x[21]=25;
                }

            if(floor(x[22])==2-esp[8])//condicional que reseta a posi��o do tartarugas
                {
                    x[22]=25;
                }

            if(floor(x[23])==25+esp[9])//condicional que reseta a posi��o do tartarugas
                {
                    x[23]=0;
                }

            if(floor(x[24])==25+esp[9])//condicional que reseta a posi��o do tartarugas
                {
                    x[24]=0;
                }

            if(floor(x[25])==25+esp[9])//condicional que reseta a posi��o do tartarugas
                {
                    x[25]=0;
                }
///////////////////////////////////////////////////////////////////SAPO////////////////////////////////////////////////////////////////////
                    do
                    {
                        if (_kbhit())//s� entra nesse if caso recebe alguma resposta do teclado
                        {
                            cod = getch();
                            fflush(stdin);
                            if (cod==72)//72 equivale a seta para cima
                                y[10]=y[10]-1;

                            if (cod==80)//80 equivale a tecla para baixo
                                y[10]=y[10]+1;

                            if (cod==75)//75 equivale a tecla para esquerda
                                x[26]=x[26]-1;

                            if (cod==77)//77 equivale a tecla para a direita
                                x[26]=x[26]+1;


                             if (cod=='q')
                            {
                                    abre_arquivo(3);//abre o arquivo save.txt
                                    salva_matriz(mapa);//chama a matriz que tira um printf do mapa
                                    for(i=0;i<11;i++)//armazena os dados no vetor
                                    {
                                        fprintf(arq3,"%c %d %d %d %d %4.1f %d %d %f\n",obj[i],tam[i],esp[i],posx[i],y[i],ve[i],vida,dif,pont);
                                    }
                                    fclose(arq3);//fecha os arquivos
                                    printf("O jogo foi salvo com sucesso!\n");
                                    esperar(0.5);
                                    fclose(arq);
                                    k=1;
                            }
                        }
                        fflush(stdin);
                    }while(y[10]==13);

                if(morte(mapa,x[26],y[10])==1)
                {
                    vida--;//perde uma vida e retorna ao x e y originais
                    x[26]=14;
                    y[10]=12;
                }
                if(troca_vel(mapa,x[26],y[10])==4)
                {
                    x[26]=x[26]+ve[5];//se o sapo tiver a mesma posi��o do caracter especial ele ganha a velocidade do objeto
                }

                if(troca_vel(mapa,x[26],y[10])==8)
                {
                    x[26]=x[26]+ve[6];
                }
                if(troca_vel(mapa,x[26],y[10])==10)
                {
                    x[26]=x[26]+ve[9];
                }
                if(troca_vel(mapa,x[26],y[10])==6)
                {
                    x[26]=x[26]+ve[8];
                }
                if(troca_vel(mapa,x[26],y[10])==2)
                {
                    x[26]=x[26]+ve[7];
                }
                      if(vitoria(mapa,x[26],y[10])==1)
                {
                    dif++;//aumenta a dificuldade
                    pont=pont+100;//aumenta a pontua��o
                    passa_fase();//impreme a tela de passa_fase
                    esperar(5);
                    x[26]=14;//retorna ao x e y iniciais
                    y[10]=12;
                    if(dif==5)//se a dificuldade for igual a 5 o jogo se encerra
                    {
                        vitoria_img();
                        k=1;//saida do loop
                    }
                }

                preenche_matriz(mapa,x[26],y[10],tam[10],obj[10],op1,ve[10]);

              for(i=0;i<26;i++)
            {
                for(j=0;j<56;j++)
                {
                    switch(mapa[i][j])
                    {
                    case '~':
                        SetConsoleTextAttribute(hConsole, 9); // cor da �gua
                    break;
                    case '@':
                    case '0':
                        SetConsoleTextAttribute(hConsole, 10); // cor do sapo
                    break;
                    case '/':
                    case '\\':
                        SetConsoleTextAttribute(hConsole, 2); // cor da tartaruga
                    break;
                    case '#':
                        SetConsoleTextAttribute(hConsole, 6); // cor do tronco
                    break;
                    case '|':
                    case '*':
                        SetConsoleTextAttribute(hConsole, 14);
                    }

                    if(i>13 && mapa[i][j] != '@' && mapa[i][j] != '0')
                        SetConsoleTextAttribute(hConsole, 12);     // cor dos carros

                    printf("%c", mapa[i][j]);
                }
                printf("\n");
            }

            clearscreen();//fun��o que limpa a tela

            if(vida==0 || floor(pont)==0)//se as vidas acabam o jogo termina//se os pontos zeram o jogo termina
            {
                game_over();//printa a tela de final de jogo
            }


    pont=pont-.25;

     }while(vida!=0 && pont!=0 && k!=1);


    return 0;
}

