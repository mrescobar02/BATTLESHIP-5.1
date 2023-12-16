#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <locale.h>
#include <ctype.h>
#include <windows.h>
#include <wchar.h>
#include <io.h>
#include <fcntl.h>

/*
barco1x: FILA DEL BARCO 1 (A,B,C,D...)
barco2x: FILA DEL BARCO 2 (A,B,C,D...)
barco1y: COLUMNA DEL BARCO 1 (1,2,3,4...)
barco2y: COLUMNA DEL BARCO 2 (1,2,3,4...)

orientbar1/orientbar2: ORIENTACION DE LOS BARCOS 1 Y 2

p1barco1: punto 1 del barco 1
p1barco2: punto 1 del barco 2
p2barco1: punto 2 del barco 1
p2barco2: punto 2 del barco 2
*/

int titulo()
{
#define ANSI_YELLOW "\x1b[33m"
    const wchar_t titulo[] = {L"\n\n\
\t\t██████╗░░█████╗░████████╗████████╗██╗░░░░░███████╗░██████╗██╗░░██╗██╗██████╗░\n\
\t\t██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║░░░░░██╔════╝██╔════╝██║░░██║██║██╔══██╗\n\
\t\t██████╦╝███████║░░░██║░░░░░░██║░░░██║░░░░░█████╗░░╚█████╗░███████║██║██████╔╝\n\
\t\t██╔══██╗██╔══██║░░░██║░░░░░░██║░░░██║░░░░░██╔══╝░░░╚═══██╗██╔══██║██║██╔═══╝░\n\
\t\t██████╦╝██║░░██║░░░██║░░░░░░██║░░░███████╗███████╗██████╔╝██║░░██║██║██║░░░░░\n\
\t\t╚═════╝░╚═╝░░╚═╝░░░╚═╝░░░░░░╚═╝░░░╚══════╝╚══════╝╚═════╝░╚═╝░░╚═╝╚═╝╚═╝░░░░░"};

    _setmode(fileno(stdout), _O_U16TEXT);
    wprintf(ANSI_YELLOW L"%s", titulo);
    _setmode(_fileno(stdout), O_TEXT);
    return 0;
}

struct barcos
{
    int barco1y, barco2y, p1barco1, p2barco1, p1barco2, p2barco2;
    char orientbar1, orientbar2, barco1x, barco2x; //barco1x,barco1y,barco2x,barco2y(coordenadas)         orientbar1,orientbar2(orientaciones)       p1barco1,p2barco1,p1barco2,p2barco2 (puntos)
};

struct buques
{
    int buque1y, buque2y, p1buque1, p2buque1, p3buque1, p1buque2, p2buque2, p3buque2; //buque1x,buque1y,buque2x,buque2y(coordenadas)          orientbuq1,orientbuq2(orientaciones)       p1buque1,p2buque1,p3buque1,p1buque2,p2buque2,p3buque2 (puntos)
    char orientbuq1, orientbuq2, buque1x, buque2x;
};

struct Portaviones
{
    int porta1y, p1porta1, p2porta1, p3porta1, p4porta1; //porta1x,porta1y           orientport1         p1porta1,p2porta1,p3porta1,p4porta1(puntos)
    char orientporta1, porta1x;
};

struct contadores
{
    int contabarcos;
    int contabuques;
    int contaportas;
};

void tableroJugador1(char *jugador1, int tablero1[8][8], struct barcos *b, struct buques *c, struct Portaviones *d, struct contadores *e)
{
    int i, j, verificador;
    char nave, letras, impbar1, impbar2, impbuq1, impbuq2, impport1;
    int contabarcos = 2, contabuques = 2, contaportas = 1;
    int fallo = 31;
    int asterisco = 42;
    int carita = 1;

    system("cls");
    //////////////////////////////////////////////////////////////TABLERO
    printf("                TABLERO DE POSICIONAMIENTO\n\n");
    printf("\t\t  1  2  3  4  5  6  7  8");
    letras = 65;

    for (i = 0; i < 8; i++)
    {
        printf("\n\t\t");
        printf("%c", letras);
        letras = letras + 1;
        for (j = 0; j < 8; j++)
        {

            printf("|-|");
        }
        if (i == 3)
        {
            printf("         J1. [%s]", strupr(jugador1)); //QUIERO IMPRIMIR EL NOMBRE DEL JUGADOR 1/
        }
    }
    printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);

    ///////////////////////////////////////////////////////////////////////////////////
    do
    {
        printf("\n\nQue tipo de nave desea colocar?\n 1. BARCO(x%d)\n 2. BUQUE(x%d) \n 3. PORTAVIONES(x%d)\n", contabarcos, contabuques, contaportas);
        nave = getch();
        switch (nave)
        {
        case '1': //BARCO

            if (contabarcos > 0)
            {
                system("cls");

                //////////////////////////////////////////////////////////////TABLERO
                printf("                TABLERO DE POSICIONAMIENTO\n\n");
                printf("\t\t  1  2  3  4  5  6  7  8");
                letras = 65;

                for (i = 0; i < 8; i++)
                {
                    printf("\n\t\t");
                    printf("%c", letras);
                    letras = letras + 1;
                    for (j = 0; j < 8; j++)
                    {
                        if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'H' && j < 7)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i][j + 1] = 1;
                            b->p1barco1 = b->barco1x;
                            b->p2barco1 = b->barco1y + 1;
                        }
                        else if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'V' && i < 7)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i + 1][j] = 1;
                            b->p1barco1 = b->barco1x + 1;
                            b->p2barco1 = b->barco1y;
                        }
                        else if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'H' && j < 7)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i][j + 1] = 1;
                            b->p1barco2 = b->barco2x;
                            b->p2barco2 = b->barco2y + 1;
                        }
                        else if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'V' && i < 7)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i + 1][j] = 1;
                            b->p1barco2 = b->barco2x + 1;
                            b->p2barco2 = b->barco2y;
                        }
                        if (tablero1[i][j] == 1)
                        {
                            printf("|%c|", asterisco);
                        }
                        else
                            printf("|-|");
                    }
                    if (i == 3)
                    {
                        printf("         J1. [%s]", strupr(jugador1)); //QUIERO IMPRIMIR EL NOMBRE DEL JUGADOR 1/
                    }
                }
                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);

                ///////////////////////////////////////////////////////////////////////////////////

                verificador = 0;
                printf("\n\nPOSCICIONAMIENTO DE BARCOS\n");
                printf("\t\t\tLos barcos ocupan [2] espacios \n\t\t\t[ocuparán tanto un espacio hacia abaio o hacia la derecha según su coordenada]\n");

                //BARCO 1
                printf("\nIntroduzca la primera coordenada del barco 1: ");
                scanf(" %c%d", &b->barco1x, &b->barco1y);
                b->barco1x = toupper(b->barco1x); //FUNCION PARA IGNORAR MINUSCULAS

                ///////////////////////////////////////VERIFICADORES
                if (b->barco1x == 'A' || b->barco1x == 'B' || b->barco1x == 'C' || b->barco1x == 'D' || b->barco1x == 'E' || b->barco1x == 'F' || b->barco1x == 'G' || b->barco1x == 'H')
                {
                    if (b->barco1y > 0 && b->barco1y <= 8)
                    {
                        if (b->barco1x == 'A')
                        {
                            b->barco1x = 0;
                            impbar1 = 65;
                        }
                        else if (b->barco1x == 'B')
                        {
                            b->barco1x = 1;
                            impbar1 = 66;
                        }
                        else if (b->barco1x == 'C')
                        {
                            b->barco1x = 2;
                            impbar1 = 67;
                        }
                        else if (b->barco1x == 'D')
                        {
                            b->barco1x = 3;
                            impbar1 = 68;
                        }
                        else if (b->barco1x == 'E')
                        {
                            b->barco1x = 4;
                            impbar1 = 69;
                        }
                        else if (b->barco1x == 'F')
                        {
                            b->barco1x = 5;
                            impbar1 = 70;
                        }
                        else if (b->barco1x == 'G')
                        {
                            b->barco1x = 6;
                            impbar1 = 71;
                        }
                        else if (b->barco1x == 'H')
                        {
                            b->barco1x = 7;
                            impbar1 = 72;
                        }
                        for (i = 0; i < 8; i++)
                        {
                            for (j = 0; j < 8; j++)
                            {
                                if (/*cen*/ tablero1[b->barco1x][b->barco1y - 1] == 1 || (/*der*/ tablero1[b->barco1x][b->barco1y] == 1 && /*abajo*/ tablero1[b->barco1x + 1][b->barco1y - 1] == 1) || ((b->barco1x >= 7) && (b->barco1y - 1 >= 7)))
                                {
                                    verificador = 0;
                                }
                                else
                                    verificador = 1;
                            }
                        }
                    }
                    else
                        verificador = 0;
                }
                else
                {
                    verificador = 0;
                }

                while (verificador == 0)
                {
                    printf("Vaya! parece que esta coordenada no es válida, inténtalo denuevo: ");
                    scanf(" %c%d", &b->barco1x, &b->barco1y);
                    b->barco1x = toupper(b->barco1x);

                    if (b->barco1x == 'A' || b->barco1x == 'B' || b->barco1x == 'C' || b->barco1x == 'D' || b->barco1x == 'E' || b->barco1x == 'F' || b->barco1x == 'G' || b->barco1x == 'H')
                    {
                        if (b->barco1y > 0 && b->barco1y <= 8)
                        {
                            if (b->barco1x == 'A')
                            {
                                b->barco1x = 0;
                                impbar1 = 65;
                            }
                            else if (b->barco1x == 'B')
                            {
                                b->barco1x = 1;
                                impbar1 = 66;
                            }
                            else if (b->barco1x == 'C')
                            {
                                b->barco1x = 2;
                                impbar2 = 67;
                            }
                            else if (b->barco1x == 'D')
                            {
                                b->barco1x = 3;
                                impbar1 = 68;
                            }
                            else if (b->barco1x == 'E')
                            {
                                b->barco1x = 4;
                                impbar1 = 69;
                            }
                            else if (b->barco1x == 'F')
                            {
                                b->barco1x = 5;
                                impbar1 = 70;
                            }
                            else if (b->barco1x == 'G')
                            {
                                b->barco1x = 6;
                                impbar1 = 71;
                            }
                            else if (b->barco1x == 'H')
                            {
                                b->barco1x = 7;
                                impbar1 = 72;
                            }

                            for (i = 0; i < 8; i++)
                            {
                                for (j = 0; j < 8; j++)
                                {
                                    if (/*cen*/ tablero1[b->barco1x][b->barco1y - 1] == 1 || (/*der*/ tablero1[b->barco1x][b->barco1y] == 1 && /*abajo*/ tablero1[b->barco1x + 1][b->barco1y - 1] == 1) || ((b->barco1x >= 7) && (b->barco1y - 1 >= 7)))
                                    {
                                        verificador = 0;
                                    }
                                    else
                                        verificador = 1;
                                }
                            }
                        }
                        else
                            verificador = 0;
                    }
                    else
                    {
                        verificador = 0;
                    }
                }

                b->barco1y -= 1;
                printf("[H]Horizontal\n[V]Vertical\n");
                b->orientbar1 = getch();
                b->orientbar1 = toupper(b->orientbar1); //funcion para ignorar minusculas

                if (b->orientbar1 == 'H')
                {
                    if (b->barco1y + 2 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else if (b->orientbar1 == 'V')
                {
                    if (b->barco1x + 2 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else
                {
                    verificador = 0;
                }

                while (verificador == 0)
                {
                    printf("¡Opción Inválida! [Es posble que tu nave esté tocando un punto no válido u ocupado en el tablero]\n");
                    printf("[H]Horizontal\n[V]Vertical\n");
                    b->orientbar1 = getch();
                    b->orientbar1 = toupper(b->orientbar1);
                    if (b->orientbar1 == 'H')
                    {
                        if (b->barco1y + 2 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else if (b->orientbar1 == 'V')
                    {
                        if (b->barco1x + 2 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else
                    {
                        verificador = 0;
                    }
                }
                /////////////////////////////////////////////////////////////////////////////////////////
                //BARCO 2
                system("cls");
                //////////////////////////////////////////////////////////////TABLERO
                printf("                TABLERO DE POSICIONAMIENTO\n\n");
                printf("\t\t  1  2  3  4  5  6  7  8");
                letras = 65;

                for (i = 0; i < 8; i++)
                {
                    printf("\n\t\t");
                    printf("%c", letras);
                    letras = letras + 1;
                    for (j = 0; j < 8; j++)
                    {
                        if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'H' && j < 7)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i][j + 1] = 1;
                            b->p1barco1 = b->barco1x;
                            b->p2barco1 = b->barco1y + 1;
                        }
                        else if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'V' && i < 7)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i + 1][j] = 1;
                            b->p1barco1 = b->barco1x + 1;
                            b->p2barco1 = b->barco1y;
                        }
                        if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'H' && j < 7)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i][j + 1] = 1;
                            b->p1barco2 = b->barco2x;
                            b->p2barco2 = b->barco2y + 1;
                        }
                        else if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'V' && i < 7)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i + 1][j] = 1;
                            b->p1barco2 = b->barco2x + 1;
                            b->p2barco2 = b->barco2y;
                        }
                        if (tablero1[i][j] == 1)
                        {
                            printf("|%c|", asterisco);
                        }
                        else
                            printf("|-|");
                    }
                    if (i == 3)
                    {
                        printf("         J1. [%s]", strupr(jugador1)); //QUIERO IMPRIMIR EL NOMBRE DEL JUGADOR 1/
                    }
                }
                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                ///////////////////////////////////////////////////////////////////////////////////

                printf("\n\nIntroduzca la primera coordenada del barco 2: ");
                scanf(" %c%d", &b->barco2x, &b->barco2y);
                b->barco2x = toupper(b->barco2x);

                ///////////////////////////////////////VERIFICADORES
                if (b->barco2x == 'A' || b->barco2x == 'B' || b->barco2x == 'C' || b->barco2x == 'D' || b->barco2x == 'E' || b->barco2x == 'F' || b->barco2x == 'G' || b->barco2x == 'H')
                {
                    if (b->barco2y > 0 && b->barco2y <= 8)
                    {
                        if (b->barco2x == 'A')
                        {
                            b->barco2x = 0;
                            impbar2 = 65;
                        }
                        else if (b->barco2x == 'B')
                        {
                            b->barco2x = 1;
                            impbar2 = 66;
                        }
                        else if (b->barco2x == 'C')
                        {
                            b->barco2x = 2;
                            impbar2 = 67;
                        }
                        else if (b->barco2x == 'D')
                        {
                            b->barco2x = 3;
                            impbar2 = 68;
                        }
                        else if (b->barco2x == 'E')
                        {
                            b->barco2x = 4;
                            impbar2 = 69;
                        }
                        else if (b->barco2x == 'F')
                        {
                            b->barco2x = 5;
                            impbar2 = 70;
                        }
                        else if (b->barco2x == 'G')
                        {
                            b->barco2x = 6;
                            impbar2 = 71;
                        }
                        else if (b->barco2x == 'H')
                        {
                            b->barco2x = 7;
                            impbar2 = 72;
                        }

                        if (/*cen*/ tablero1[b->barco2x][b->barco2y - 1] == 1 || (/*der*/ tablero1[b->barco2x][b->barco2y] == 1 && /*abajo*/ tablero1[b->barco2x + 1][b->barco2y - 1] == 1) || ((b->barco2x >= 7) && (b->barco2y - 1 >= 7)))
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else
                        verificador = 0;
                }
                else
                {
                    verificador = 0;
                }
                while (verificador == 0)
                {
                    printf("Vaya! parece que esta coordenada no es válida, inténtalo denuevo: ");
                    scanf(" %c%d", &b->barco2x, &b->barco2y);
                    b->barco2x = toupper(b->barco2x);
                    if (b->barco2x == 'A' || b->barco2x == 'B' || b->barco2x == 'C' || b->barco2x == 'D' || b->barco2x == 'E' || b->barco2x == 'F' || b->barco2x == 'G' || b->barco2x == 'H')
                    {
                        if (b->barco2y > 0 && b->barco2y <= 8)
                        {
                            if (b->barco2x == 'A')
                            {
                                b->barco2x = 0;
                                impbar2 = 65;
                            }
                            else if (b->barco2x == 'B')
                            {
                                b->barco2x = 1;
                                impbar2 = 66;
                            }
                            else if (b->barco2x == 'C')
                            {
                                b->barco2x = 2;
                                impbar2 = 67;
                            }
                            else if (b->barco2x == 'D')
                            {
                                b->barco2x = 3;
                                impbar2 = 68;
                            }
                            else if (b->barco2x == 'E')
                            {
                                b->barco2x = 4;
                                impbar2 = 69;
                            }
                            else if (b->barco2x == 'F')
                            {
                                b->barco2x = 5;
                                impbar2 = 70;
                            }
                            else if (b->barco2x == 'G')
                            {
                                b->barco2x = 6;
                                impbar2 = 71;
                            }
                            else if (b->barco2x == 'H')
                            {
                                b->barco2x = 7;
                                impbar2 = 72;
                            }
                            if (/*cen*/ tablero1[b->barco2x][b->barco2y - 1] == 1 || (/*der*/ tablero1[b->barco2x][b->barco2y] == 1 && /*abajo*/ tablero1[b->barco2x + 1][b->barco2y - 1] == 1) || ((b->barco2x >= 7) && (b->barco2y - 1 >= 7)))
                            {
                                verificador = 0;
                            }
                            else
                                verificador = 1;
                        }
                        else
                            verificador = 0;
                    }
                    else
                    {
                        verificador = 0;
                    }
                }

                b->barco2y -= 1;
                printf("[H]Horizontal\n[V]Vertical\n");
                b->orientbar2 = getch();
                b->orientbar2 = toupper(b->orientbar2); //funcion para ignorar minusculas

                if (b->orientbar2 == 'H')
                {
                    if (b->barco2y + 2 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else if (b->orientbar2 == 'V')
                {
                    if (b->barco2x + 2 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else
                {
                    verificador = 0;
                }

                while (verificador == 0)
                {
                    printf("¡Opción Inválida! [Es posble que tu nave esté tocando un punto no válido u ocupado en el tablero]\n");
                    printf("[H]Horizontal\n[V]Vertical\n");
                    b->orientbar2 = getch();
                    b->orientbar2 = toupper(b->orientbar2);
                    if (b->orientbar2 == 'H')
                    {
                        if (b->barco2y + 2 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else if (b->orientbar2 == 'V')
                    {
                        if (b->barco2x + 2 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else
                        verificador = 0;
                }
                ///////////////////////////////////////////////////////////////////////////////////////////

                system("cls");
                //////////////////////////////////////////////////////////////TABLERO
                printf("                TABLERO DE POSICIONAMIENTO\n\n");
                printf("\t\t  1  2  3  4  5  6  7  8");
                letras = 65;

                for (i = 0; i < 8; i++)
                {
                    printf("\n\t\t");
                    printf("%c", letras);
                    letras = letras + 1;
                    for (j = 0; j < 8; j++)
                    {
                        if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'H' && j < 7)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i][j + 1] = 1;
                            b->p1barco1 = b->barco1x;
                            b->p2barco1 = b->barco1y + 1;
                        }
                        else if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'V' && i < 7)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i + 1][j] = 1;
                            b->p1barco1 = b->barco1x + 1;
                            b->p2barco1 = b->barco1y;
                        }
                        else if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'H' && j < 7)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i][j + 1] = 1;
                            b->p1barco2 = b->barco2x;
                            b->p2barco2 = b->barco2y + 1;
                        }
                        else if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'V' && i < 7)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i + 1][j] = 1;
                            b->p1barco2 = b->barco2x + 1;
                            b->p2barco2 = b->barco2y;
                        }
                        if (tablero1[i][j] == 1)
                        {
                            printf("|%c|", asterisco);
                        }
                        else
                            printf("|-|");
                    }
                    if (i == 3)
                    {
                        printf("         J1. [%s]", strupr(jugador1));
                    }
                }
                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);

                ///////////////////////////////////////////////////////////////////////////////////

                if (b->orientbar1 == 'H')
                {
                    printf("\nPrimer barco poscicionado en Horizontal en las coordenadas [%c,%d] y [%c,%d]\n", impbar1, b->barco1y + 1, impbar1, b->p2barco1 + 1);
                }
                else if (b->orientbar1 == 'V')
                {
                    printf("\nPrimer barco poscicionado en Vertical en las coordenadas [%c,%d] y [%c,%d]\n", impbar1, b->barco1y + 1, impbar1 + 1, b->p2barco1 + 1);
                }
                if (b->orientbar2 == 'H')
                {
                    printf("\nSegundo barco Poscicionado en Horizontal en las coordenadas [%c,%d] y [%c,%d]\n", impbar2, b->barco2y + 1, impbar2, b->p2barco2 + 1);
                }
                else if (b->orientbar2 == 'V')
                {
                    printf("\nSegundo barco poscicionado en Vertical en las coordenadas [%c,%d] y [%c,%d\]\n", impbar2, b->barco2y + 1, impbar2 + 1, b->p2barco2 + 1);
                }
                contabarcos -= 2;
                printf("\nGuardando datos...");
                Sleep(4000);
            }
            else
            {
                printf("\nAgotaste tu cantidad de barcos!");
                Sleep(1000);
            }
            system("cls");
            //////////////////////////////////////////////////////////////TABLERO
            printf("                TABLERO DE POSICIONAMIENTO\n\n");
            printf("\t\t  1  2  3  4  5  6  7  8");
            letras = 65;

            for (i = 0; i < 8; i++)
            {
                printf("\n\t\t");
                printf("%c", letras);
                letras = letras + 1;
                for (j = 0; j < 8; j++)
                {
                    if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'H' && j < 7)
                    {
                        tablero1[i][j] = 1;
                        tablero1[i][j + 1] = 1;
                        b->p1barco1 = b->barco1x;
                        b->p2barco1 = b->barco1y + 1;
                    }
                    else if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'V' && i < 7)
                    {
                        tablero1[i][j] = 1;
                        tablero1[i + 1][j] = 1;
                        b->p1barco1 = b->barco1x + 1;
                        b->p2barco1 = b->barco1y;
                    }
                    else if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'H' && j < 7)
                    {
                        tablero1[i][j] = 1;
                        tablero1[i][j + 1] = 1;
                        b->p1barco2 = b->barco2x;
                        b->p2barco2 = b->barco2y + 1;
                    }
                    else if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'V' && i < 7)
                    {
                        tablero1[i][j] = 1;
                        tablero1[i + 1][j] = 1;
                        b->p1barco2 = b->barco2x + 1;
                        b->p2barco2 = b->barco2y;
                    }
                    if (tablero1[i][j] == 1)
                    {
                        printf("|%c|", asterisco);
                    }
                    else
                        printf("|-|");
                }
                if (i == 3)
                {
                    printf("         J1. [%s]", strupr(jugador1));
                }
            }
            printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);

            ///////////////////////////////////////////////////////////////////////////////////
            break;
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case '2':

            if (contabuques > 0)
            {
                system("cls");
                //////////////////////////////////////////////////////////////TABLERO
                printf("                TABLERO DE POSICIONAMIENTO\n\n");
                printf("\t\t  1  2  3  4  5  6  7  8");
                letras = 65;

                for (i = 0; i < 8; i++)
                {
                    printf("\n\t\t");
                    printf("%c", letras);
                    letras = letras + 1;
                    for (j = 0; j < 8; j++)
                    {
                        if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'H' && j < 7)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i][j + 1] = 1;
                            b->p1barco1 = b->barco1x;
                            b->p2barco1 = b->barco1y + 1;
                        }
                        else if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'V' && i < 7)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i + 1][j] = 1;
                            b->p1barco1 = b->barco1x + 1;
                            b->p2barco1 = b->barco1y;
                        }
                        if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'H' && j < 7)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i][j + 1] = 1;
                            b->p1barco2 = b->barco2x;
                            b->p2barco2 = b->barco2y + 1;
                        }
                        else if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'V' && i < 7)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i + 1][j] = 1;
                            b->p1barco2 = b->barco2x + 1;
                            b->p2barco2 = b->barco2y;
                        }
                        if (tablero1[i][j] == 1)
                        {
                            printf("|%c|", asterisco);
                        }
                        else
                            printf("|-|");
                    }
                    if (i == 3)
                    {
                        printf("         J1. [%s]", strupr(jugador1)); //QUIERO IMPRIMIR EL NOMBRE DEL JUGADOR 1/
                    }
                }
                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);

                //////////////////////////////////////////////////////////////////////////////////
                //BUQUE 1
                printf("\n\nPOSCICIONAMIENTO DE BUQUES\n");
                printf("\t\t\tLos buques ocupan [3] espacios\n\t\t\t[ocuparán tanto dos espacios hacia abaio o hacia la derecha según su coordenada]\n");
                printf("\nIntroduzca la primera coordenada del buque 1: ");
                scanf(" %c%d", &c->buque1x, &c->buque1y);
                c->buque1x = toupper(c->buque1x);

                ///////////////////////////////////////VERIFICADORES
                if (c->buque1x == 'A' || c->buque1x == 'B' || c->buque1x == 'C' || c->buque1x == 'D' || c->buque1x == 'E' || c->buque1x == 'F' || c->buque1x == 'G' || c->buque1x == 'H')
                {
                    if (c->buque1y > 0 && c->buque1y <= 8)
                    {
                        if (c->buque1x == 'A')
                        {
                            c->buque1x = 0;
                            impbuq1 = 65;
                        }
                        else if (c->buque1x == 'B')
                        {
                            c->buque1x = 1;
                            impbuq1 = 66;
                        }
                        else if (c->buque1x == 'C')
                        {
                            c->buque1x = 2;
                            impbuq1 = 67;
                        }
                        else if (c->buque1x == 'D')
                        {
                            c->buque1x = 3;
                            impbuq1 = 68;
                        }
                        else if (c->buque1x == 'E')
                        {
                            c->buque1x = 4;
                            impbuq1 = 69;
                        }
                        else if (c->buque1x == 'F')
                        {
                            c->buque1x = 5;
                            impbuq1 = 70;
                        }
                        else if (c->buque1x == 'G')
                        {
                            c->buque1x = 6;
                            impbuq1 = 71;
                        }
                        else if (c->buque1x == 'H')
                        {
                            c->buque1x = 7;
                            impbuq1 = 72;
                        }

                        for (i = 0; i < 8; i++)
                        {
                            for (j = 0; j < 8; j++)
                            {
                                if (/*cen*/ tablero1[c->buque1x][c->buque1y - 1] == 1 || (/*der1*/ tablero1[c->buque1x][c->buque1y] == 1 && /*der2*/ tablero1[c->buque1x][c->buque1y + 1] == 1 && /*abajo1*/ tablero1[c->buque1x + 1][c->buque1y - 1] == 1 && /*abajo2*/ tablero1[c->buque1x + 2][c->buque1y - 1] == 1) || ((c->buque1x >= 6) && (c->buque1y - 1 >= 6)))
                                {
                                    verificador = 0;
                                }
                                else
                                    verificador = 1;
                            }
                        }
                    }
                    else
                        verificador = 0;
                }
                else
                {
                    verificador = 0;
                }
                while (verificador == 0)
                {
                    printf("Vaya! parece que esta coordenada no es válida, inténtalo denuevo: ");
                    scanf(" %c%d", &c->buque1x, &c->buque1y);
                    c->buque1x = toupper(c->buque1x);
                    if (c->buque1x == 'A' || c->buque1x == 'B' || c->buque1x == 'C' || c->buque1x == 'D' || c->buque1x == 'E' || c->buque1x == 'F' || c->buque1x == 'G' || c->buque1x == 'H')
                    {
                        if (c->buque1y > 0 && c->buque1y <= 8)
                        {
                            if (c->buque1x == 'A')
                            {
                                c->buque1x = 0;
                                impbuq1 = 65;
                            }
                            else if (c->buque1x == 'B')
                            {
                                c->buque1x = 1;
                                impbuq1 = 66;
                            }
                            else if (c->buque1x == 'C')
                            {
                                c->buque1x = 2;
                                impbuq1 = 67;
                            }
                            else if (c->buque1x == 'D')
                            {
                                c->buque1x = 3;
                                impbuq1 = 68;
                            }
                            else if (c->buque1x == 'E')
                            {
                                c->buque1x = 4;
                                impbuq1 = 69;
                            }
                            else if (c->buque1x == 'F')
                            {
                                c->buque1x = 5;
                                impbuq1 = 70;
                            }
                            else if (c->buque1x == 'G')
                            {
                                c->buque1x = 6;
                                impbuq1 = 71;
                            }
                            else if (c->buque1x == 'H')
                            {
                                c->buque1x = 7;
                                impbuq1 = 72;
                            }

                            for (i = 0; i < 8; i++)
                            {
                                for (j = 0; j < 8; j++)
                                {
                                    if (/*cen*/ tablero1[c->buque1x][c->buque1y - 1] == 1 || (/*der1*/ tablero1[c->buque1x][c->buque1y] == 1 && /*der2*/ tablero1[c->buque1x][c->buque1y + 1] == 1 && /*abajo1*/ tablero1[c->buque1x + 1][c->buque1y - 1] == 1 && /*abajo2*/ tablero1[c->buque1x + 2][c->buque1y - 1] == 1) || ((c->buque1x >= 6) && (c->buque1y - 1 >= 6)))
                                    {
                                        verificador = 0;
                                    }
                                    else
                                        verificador = 1;
                                }
                            }
                        }
                        else
                            verificador = 0;
                    }
                    else
                    {
                        verificador = 0;
                    }
                }

                c->buque1y -= 1;
                printf("[H]Horizontal\n[V]Vertical\n");
                c->orientbuq1 = getch();
                c->orientbuq1 = toupper(c->orientbuq1); //funcion para ignorar minusculas

                if (c->orientbuq1 == 'H')
                {
                    if (/*der1*/ tablero1[c->buque1x][c->buque1y + 1] == 1 || /*der2*/ tablero1[c->buque1x][c->buque1y + 2] == 1 || c->buque1y + 3 > 8 || c->buque1y + 3 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else if (c->orientbuq1 == 'V')
                {
                    if (/*abajo1*/ tablero1[c->buque1x + 1][c->buque1y - 1] == 1 || /*abajo2*/ tablero1[c->buque1x + 2][c->buque1y - 1] == 1 || c->buque1x + 3 > 8 || c->buque1x + 3 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else
                {
                    verificador = 0;
                }

                while (verificador == 0)
                {
                    printf("¡Opción Inválida! [Es posble que tu nave esté tocando un punto no válido u ocupado en el tablero]");
                    printf("\n[H]Horizontal\n[V]Vertical\n");
                    c->orientbuq1 = getch();
                    c->orientbuq1 = toupper(c->orientbuq1);
                    if (c->orientbuq1 == 'H')
                    {
                        if (/*der1*/ tablero1[c->buque1x][c->buque1y + 1] == 1 || /*der2*/ tablero1[c->buque1x][c->buque1y + 2] == 1 || c->buque1y + 3 > 8 || c->buque1y + 3 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else if (c->orientbuq1 == 'V')
                    {
                        if (/*abajo1*/ tablero1[c->buque1x + 1][c->buque1y - 1] == 1 || /*abajo2*/ tablero1[c->buque1x + 2][c->buque1y - 1] == 1 || c->buque1x + 3 > 8 || c->buque1x + 3 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else
                    {
                        verificador = 0;
                    }
                }
                ////////////////////////////////////////////////////////////////////////////////////////

                //BUQUE 2
                system("cls");
                //////////////////////////////////////////////////////////////TABLERO
                printf("                TABLERO DE POSICIONAMIENTO\n\n");
                printf("\t\t  1  2  3  4  5  6  7  8");
                letras = 65;

                for (i = 0; i < 8; i++)
                {
                    printf("\n\t\t");
                    printf("%c", letras);
                    letras = letras + 1;
                    for (j = 0; j < 8; j++)
                    {
                        if (c->buque1y == j && c->buque1x == i && c->orientbuq1 == 'H' && j <= 6)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i][j + 1] = 1;
                            tablero1[i][j + 2] = 1;
                            c->p1buque1 = c->buque1y;
                            c->p2buque1 = c->buque1y + 1;
                            c->p3buque1 = c->buque1y + 2;
                        }
                        else if (c->buque1y == j && c->buque1x == i && c->orientbuq1 == 'V' && i <= 6)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i + 1][j] = 1;
                            tablero1[i + 2][j] = 1;
                            c->p1buque1 = c->buque1y;
                            c->p2buque1 = c->buque1y;
                            c->p3buque1 = c->buque1y;
                        }
                        if (c->buque2y == j && c->buque2x == i && c->orientbuq2 == 'H' && j <= 6)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i][j + 1] = 1;
                            tablero1[i][j + 2] = 1;
                            c->p1buque2 = c->buque2y;
                            c->p2buque2 = c->buque2y + 1;
                            c->p3buque2 = c->buque2y + 2;
                        }
                        else if (c->buque2y == j && c->buque2x == i && c->orientbuq2 == 'V' && i <= 6)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i + 1][j] = 1;
                            tablero1[i + 2][j] = 1;
                            c->p1buque2 = c->buque2y;
                            c->p2buque2 = c->buque2y;
                            c->p3buque2 = c->buque2y;
                        }
                        if (tablero1[i][j] == 1)
                        {
                            printf("|%c|", asterisco);
                        }
                        else
                            printf("|-|");
                    }
                    if (i == 3)
                    {
                        printf("         J1. [%s]", strupr(jugador1)); //QUIERO IMPRIMIR EL NOMBRE DEL JUGADOR 1/
                    }
                }
                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);

                ///////////////////////////////////////////////////////////////////////////////////

                printf("\nIntroduzca la primera coordenada del buque 2: ");
                scanf(" %c%d", &c->buque2x, &c->buque2y);
                c->buque2x = toupper(c->buque2x);

                ///////////////////////////////////////VERIFICADORES
                if (c->buque2x == 'A' || c->buque2x == 'B' || c->buque2x == 'C' || c->buque2x == 'D' || c->buque2x == 'E' || c->buque2x == 'F' || c->buque2x == 'G' || c->buque2x == 'H')
                {
                    if (c->buque2y > 0 && c->buque2y <= 8)
                    {
                        if (c->buque2x == 'A')
                        {
                            c->buque2x = 0;
                            impbuq2 = 65;
                        }
                        else if (c->buque2x == 'B')
                        {
                            c->buque2x = 1;
                            impbuq2 = 66;
                        }
                        else if (c->buque2x == 'C')
                        {
                            c->buque2x = 2;
                            impbuq2 = 67;
                        }
                        else if (c->buque2x == 'D')
                        {
                            c->buque2x = 3;
                            impbuq2 = 68;
                        }
                        else if (c->buque2x == 'E')
                        {
                            c->buque2x = 4;
                            impbuq2 = 69;
                        }
                        else if (c->buque2x == 'F')
                        {
                            c->buque2x = 5;
                            impbuq2 = 70;
                        }
                        else if (c->buque2x == 'G')
                        {
                            c->buque2x = 6;
                            impbuq2 = 71;
                        }
                        else if (c->buque2x == 'H')
                        {
                            c->buque2x = 7;
                            impbuq2 = 72;
                        }

                        for (i = 0; i < 8; i++)
                        {
                            for (j = 0; j < 8; j++)
                            {
                                if (/*cen*/ tablero1[c->buque2x][c->buque2y - 1] == 1 || (/*der1*/ tablero1[c->buque2x][c->buque2y] == 1 && /*der2*/ tablero1[c->buque2x][c->buque2y + 1] == 1 && /*abajo1*/ tablero1[c->buque2x + 1][c->buque2y - 1] == 1 && /*abajo2*/ tablero1[c->buque2x + 2][c->buque2y - 1] == 1) || ((c->buque2x >= 6) && (c->buque2y - 1 >= 6)))
                                {
                                    verificador = 0;
                                }
                                else
                                    verificador = 1;
                            }
                        }
                    }
                    else
                        verificador = 0;
                }
                else
                {
                    verificador = 0;
                }
                while (verificador == 0)
                {
                    printf("Vaya! parece que la coordenada [%c%d] no es válida, inténtalo denuevo: ", c->buque2x, c->buque2y);
                    scanf(" %c%d", &c->buque2x, &c->buque2y);
                    c->buque2x = toupper(c->buque2x);
                    if (c->buque2x == 'A' || c->buque2x == 'B' || c->buque2x == 'C' || c->buque2x == 'D' || c->buque2x == 'E' || c->buque2x == 'F' || c->buque2x == 'G' || c->buque2x == 'H')
                    {
                        if (c->buque2y > 0 && c->buque2y <= 8)
                        {
                            if (c->buque2x == 'A')
                            {
                                c->buque2x = 0;
                                impbuq2 = 65;
                            }
                            else if (c->buque2x == 'B')
                            {
                                c->buque2x = 1;
                                impbuq2 = 66;
                            }
                            else if (c->buque2x == 'C')
                            {
                                c->buque2x = 2;
                                impbuq2 = 67;
                            }
                            else if (c->buque2x == 'D')
                            {
                                c->buque2x = 3;
                                impbuq2 = 68;
                            }
                            else if (c->buque2x == 'E')
                            {
                                c->buque2x = 4;
                                impbuq2 = 69;
                            }
                            else if (c->buque2x == 'F')
                            {
                                c->buque2x = 5;
                                impbuq2 = 70;
                            }
                            else if (c->buque2x == 'G')
                            {
                                c->buque2x = 6;
                                impbuq2 = 71;
                            }
                            else if (c->buque2x == 'H')
                            {
                                c->buque2x = 7;
                                impbuq2 = 72;
                            }

                            for (i = 0; i < 8; i++)
                            {
                                for (j = 0; j < 8; j++)
                                {
                                    if (/*cen*/ tablero1[c->buque2x][c->buque2y - 1] == 1 || (/*der1*/ tablero1[c->buque2x][c->buque2y] == 1 && /*der2*/ tablero1[c->buque2x][c->buque2y + 1] == 1 && /*abajo1*/ tablero1[c->buque2x + 1][c->buque2y - 1] == 1 && /*abajo2*/ tablero1[c->buque2x + 2][c->buque2y - 1] == 1) || ((c->buque2x >= 6) && (c->buque2y - 1 >= 6)))
                                    {
                                        verificador = 0;
                                    }
                                    else
                                        verificador = 1;
                                }
                            }
                        }
                        else
                        {
                            verificador = 0;
                        }
                    }
                    else
                        verificador = 0;
                }

                c->buque2y -= 1;
                printf("[H]Horizontal\n[V]Vertical\n");
                c->orientbuq2 = getch();
                c->orientbuq2 = toupper(c->orientbuq2); //funcion para ignorar minusculas

                if (c->orientbuq2 == 'H')
                {
                    if (/*der1*/ tablero1[c->buque2x][c->buque2y + 1] == 1 || /*der2*/ tablero1[c->buque2x][c->buque2y + 2] == 1 || c->buque2y + 3 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else if (c->orientbuq2 == 'V')
                {
                    if (/*abajo1*/ tablero1[c->buque2x + 1][c->buque2y - 1] == 1 || /*abajo2*/ tablero1[c->buque2x + 2][c->buque2y - 1] == 1 || c->buque2x + 3 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else
                {
                    verificador = 0;
                }
                while (verificador == 0)
                {
                    printf("¡Opción Inválida! [Es posble que tu nave esté tocando un punto no válido u ocupado en el tablero]");
                    printf("\n[H]Horizontal\n[V]Vertical\n");
                    c->orientbuq2 = getch();
                    c->orientbuq2 = toupper(c->orientbuq2);
                    if (c->orientbuq2 == 'H')
                    {
                        if (/*der1*/ tablero1[c->buque2x][c->buque2y + 1] == 1 || /*der2*/ tablero1[c->buque2x][c->buque2y + 2] == 1 || c->buque2y + 3 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else if (c->orientbuq2 == 'V')
                    {
                        if (/*abajo1*/ tablero1[c->buque2x + 1][c->buque2y - 1] == 1 || /*abajo2*/ tablero1[c->buque2x + 2][c->buque2y - 1] == 1 || c->buque2x + 3 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else
                    {
                        verificador = 0;
                    }
                }
                ////////////////////////////////////////////////////////////////////////////////////////

                system("cls");
                //////////////////////////////////////////////////////////////TABLERO
                printf("                TABLERO DE POSICIONAMIENTO\n\n");
                printf("\t\t  1  2  3  4  5  6  7  8");
                letras = 65;

                for (i = 0; i < 8; i++)
                {
                    printf("\n\t\t");
                    printf("%c", letras);
                    letras = letras + 1;
                    for (j = 0; j < 8; j++)
                    {
                        if (c->buque1y == j && c->buque1x == i && c->orientbuq1 == 'H' && j <= 6)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i][j + 1] = 1;
                            tablero1[i][j + 2] = 1;
                            c->p1buque1 = c->buque1y;
                            c->p2buque1 = c->buque1y + 1;
                            c->p3buque1 = c->buque1y + 2;
                        }
                        else if (c->buque1y == j && c->buque1x == i && c->orientbuq1 == 'V' && i <= 6)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i + 1][j] = 1;
                            tablero1[i + 2][j] = 1;
                            c->p1buque1 = c->buque1y;
                            c->p2buque1 = c->buque1y;
                            c->p3buque1 = c->buque1y;
                        }
                        if (c->buque2y == j && c->buque2x == i && c->orientbuq2 == 'H' && j <= 6)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i][j + 1] = 1;
                            tablero1[i][j + 2] = 1;
                            c->p1buque2 = c->buque2y;
                            c->p2buque2 = c->buque2y + 1;
                            c->p3buque2 = c->buque2y + 2;
                        }
                        else if (c->buque2y == j && c->buque2x == i && c->orientbuq2 == 'V' && i <= 6)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i + 1][j] = 1;
                            tablero1[i + 2][j] = 1;
                            c->p1buque2 = c->buque2y;
                            c->p2buque2 = c->buque2y;
                            c->p3buque2 = c->buque2y;
                        }
                        if (tablero1[i][j] == 1)
                        {
                            printf("|%c|", asterisco);
                        }
                        else
                            printf("|-|");
                    }
                    if (i == 3)
                    {
                        printf("         J1. [%s]", strupr(jugador1));
                    }
                }
                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);

                ///////////////////////////////////////////////////////////////////////////////////

                if (c->orientbuq1 == 'H')
                {
                    printf("\nPrimer Buque poscicionado en horizontal, en las coordenadas [%c,%d], [%c,%d] y [%c,%d]\n ", impbuq1, c->p1buque1 + 1, impbuq1, c->p2buque1 + 1, impbuq1, c->p3buque1 + 1);
                }
                else if (c->orientbuq2 == 'V')
                {
                    printf("\nPrimer Buque Poscicionado en vertical, en las coordenadas [%c,%d], [%c,%d] y [%c,%d]\n", impbuq1, c->p1buque1, impbuq1 + 1, c->p2buque1, impbuq1 + 2, c->p3buque1);
                }
                if (c->orientbuq2 == 'H')
                {
                    printf("\nSegundo Buque Poscicionado en horizontal, en las coordenadas [%c,%d], [%c,%d] y [%c,%d]\n", impbuq2, c->p1buque2 + 1, impbuq2, c->p2buque2 + 1, impbuq2, c->p3buque2 + 1);
                }
                else if (c->orientbuq2 == 'V')
                {
                    printf("\nSegundo Buque Poscicionado en vertical en, las coordenadas [%c,%d], [%c,%d] y [%c,%d]\n", impbuq2, c->p1buque2, impbuq2 + 1, c->p2buque2, impbuq2 + 2, c->p3buque2);
                }
                contabuques = contabuques - 2;
                printf("\nGuardando datos...");
                Sleep(4000);
            }
            else
            {
                printf("\nAgotaste tu cantidad de buques!");
                Sleep(1000);
            }

            system("cls");
            //////////////////////////////////////////////////////////////TABLERO
            printf("                TABLERO DE POSICIONAMIENTO\n\n");
            printf("\t\t  1  2  3  4  5  6  7  8");
            letras = 65;

            for (i = 0; i < 8; i++)
            {
                printf("\n\t\t");
                printf("%c", letras);
                letras = letras + 1;
                for (j = 0; j < 8; j++)
                {
                    if (c->buque1y == j && c->buque1x == i && c->orientbuq1 == 'H' && j <= 6)
                    {
                        tablero1[i][j] = 1;
                        tablero1[i][j + 1] = 1;
                        tablero1[i][j + 2] = 1;
                        c->p1buque1 = c->buque1y;
                        c->p2buque1 = c->buque1y + 1;
                        c->p3buque1 = c->buque1y + 2;
                    }
                    else if (c->buque1y == j && c->buque1x == i && c->orientbuq1 == 'V' && i <= 6)
                    {
                        tablero1[i][j] = 1;
                        tablero1[i + 1][j] = 1;
                        tablero1[i + 2][j] = 1;
                        c->p1buque1 = c->buque1y;
                        c->p2buque1 = c->buque1y;
                        c->p3buque1 = c->buque1y;
                    }
                    if (c->buque2y == j && c->buque2x == i && c->orientbuq2 == 'H' && j <= 6)
                    {
                        tablero1[i][j] = 1;
                        tablero1[i][j + 1] = 1;
                        tablero1[i][j + 2] = 1;
                        c->p1buque2 = c->buque2y;
                        c->p2buque2 = c->buque2y + 1;
                        c->p3buque2 = c->buque2y + 2;
                    }
                    else if (c->buque2y == j && c->buque2x == i && c->orientbuq2 == 'V' && i <= 6)
                    {
                        tablero1[i][j] = 1;
                        tablero1[i + 1][j] = 1;
                        tablero1[i + 2][j] = 1;
                        c->p1buque2 = c->buque2y;
                        c->p2buque2 = c->buque2y;
                        c->p3buque2 = c->buque2y;
                    }
                    if (tablero1[i][j] == 1)
                    {
                        printf("|%c|", asterisco);
                    }
                    else
                        printf("|-|");
                }
                if (i == 3)
                {
                    printf("         J1. [%s]", strupr(jugador1));
                }
            }
            printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);

            ///////////////////////////////////////////////////////////////////////////////////
            break;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case '3':

            if (contaportas > 0)
            {
                system("cls");

                //////////////////////////////////////////////////////////////TABLERO
                printf("                TABLERO DE POSICIONAMIENTO\n\n");
                printf("\t\t  1  2  3  4  5  6  7  8");
                letras = 65;

                for (i = 0; i < 8; i++)
                {
                    printf("\n\t\t");
                    printf("%c", letras);
                    letras = letras + 1;
                    for (j = 0; j < 8; j++)
                    {
                        if (tablero1[i][j] == 1)
                        {
                            printf("|%c|", asterisco);
                        }
                        else
                            printf("|-|");
                    }
                    if (i == 3)
                    {
                        printf("         J1. [%s]", strupr(jugador1)); //QUIERO IMPRIMIR EL NOMBRE DEL JUGADOR 1/
                    }
                }
                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);

                ///////////////////////////////////////////////////////////////////////////////////

                printf("\n\nPOSCICIONAMIENTO DE PORTAVIONES\n");
                printf("\t\t\tLos portaviones ocupan [4] espacios\n\t\t\t[ocuparán tanto cuatro espacios hacia abaio o hacia la derecha según su coordenada]\n");
                printf("\nIntroduzca la primera coordenada del portaviones 1: ");
                scanf(" %c%d", &d->porta1x, &d->porta1y);

                d->porta1x = toupper(d->porta1x);
                ///////////////////////////////////////VERIFICADORES

                if (d->porta1x == 'A' || d->porta1x == 'B' || d->porta1x == 'C' || d->porta1x == 'D' || d->porta1x == 'E' || d->porta1x == 'F' || d->porta1x == 'G' || d->porta1x == 'H')
                {
                    if (d->porta1y > 0 && d->porta1y <= 8)
                    {
                        if (d->porta1x == 'A')
                        {
                            d->porta1x = 0;
                            impport1 = 65;
                        }
                        else if (d->porta1x == 'B')
                        {
                            d->porta1x = 1;
                            impport1 = 66;
                        }
                        else if (d->porta1x == 'C')
                        {
                            d->porta1x = 2;
                            impport1 = 67;
                        }
                        else if (d->porta1x == 'D')
                        {
                            d->porta1x = 3;
                            impport1 = 68;
                        }
                        else if (d->porta1x == 'E')
                        {
                            d->porta1x = 4;
                            impport1 = 69;
                        }
                        else if (d->porta1x == 'F')
                        {
                            d->porta1x = 5;
                            impport1 = 70;
                        }
                        else if (d->porta1x == 'G')
                        {
                            d->porta1x = 6;
                            impport1 = 71;
                        }
                        else if (d->porta1x == 'H')
                        {
                            d->porta1x = 7;
                            impport1 = 72;
                        }
                        for (i = 0; i < 8; i++)
                        {
                            for (j = 0; j < 8; j++)
                            {
                                if ((/*cen*/ tablero1[d->porta1x][d->porta1y - 1] == 1 || (/*der1*/ tablero1[d->porta1x][d->porta1y] == 1 && /*der2*/ tablero1[d->porta1x][d->porta1y + 1] == 1 && /*der3*/ tablero1[d->porta1x][d->porta1y + 2] == 1 && /*abajo1*/ tablero1[d->porta1x + 1][d->porta1y - 1] == 1 && /*abajo2*/ tablero1[d->porta1x + 2][d->porta1y - 1] == 1) && /*abajo3*/ tablero1[d->porta1x + 3][d->porta1y - 1] == 1) || ((d->porta1x >= 5) && (d->porta1y - 1 >= 5)))
                                {
                                    verificador = 0;
                                }
                                else
                                    verificador = 1;
                            }
                        }
                    }
                    else
                        verificador = 0;
                }
                else
                {
                    verificador = 0;
                }
                while (verificador == 0)
                {
                    printf("Vaya! parece que esta coordenada no es válida, inténtalo denuevo: ");
                    scanf(" %c%d", &d->porta1x, &d->porta1y);
                    d->porta1x = toupper(d->porta1x);
                    if (d->porta1x == 'A' || d->porta1x == 'B' || d->porta1x == 'C' || d->porta1x == 'D' || d->porta1x == 'E' || d->porta1x == 'F' || d->porta1x == 'G' || d->porta1x == 'H')
                    {
                        if (d->porta1y > 0 && d->porta1y <= 5)
                        {
                            if (d->porta1x == 'A')
                            {
                                d->porta1x = 0;
                                impport1 = 65;
                            }
                            else if (d->porta1x == 'B')
                            {
                                d->porta1x = 1;
                                impport1 = 66;
                            }
                            else if (d->porta1x == 'C')
                            {
                                d->porta1x = 2;
                                impport1 = 67;
                            }
                            else if (d->porta1x == 'D')
                            {
                                d->porta1x = 3;
                                impport1 = 68;
                            }
                            else if (d->porta1x == 'E')
                            {
                                d->porta1x = 4;
                                impport1 = 69;
                            }
                            else if (d->porta1x == 'F')
                            {
                                d->porta1x = 5;
                                impport1 = 70;
                            }
                            else if (d->porta1x == 'G')
                            {
                                d->porta1x = 6;
                                impport1 = 71;
                            }
                            else if (d->porta1x == 'H')
                            {
                                d->porta1x = 7;
                                impport1 = 72;
                            }
                            for (i = 0; i < 8; i++)
                            {
                                for (j = 0; j < 8; j++)
                                {
                                    if ((/*cen*/ tablero1[d->porta1x][d->porta1y - 1] == 1 || (/*der1*/ tablero1[d->porta1x][d->porta1y] == 1 && /*der2*/ tablero1[d->porta1x][d->porta1y + 1] == 1 && /*der3*/ tablero1[d->porta1x][d->porta1y + 2] == 1 && /*abajo1*/ tablero1[d->porta1x + 1][d->porta1y - 1] == 1 && /*abajo2*/ tablero1[d->porta1x + 2][d->porta1y - 1] == 1) && /*abajo3*/ tablero1[d->porta1x + 3][d->porta1y - 1] == 1) || ((d->porta1x >= 5) && (d->porta1y - 1 >= 5)))
                                    {
                                        verificador = 0;
                                    }
                                    else
                                        verificador = 1;
                                }
                            }
                        }
                        else
                            verificador = 0;
                    }
                    else
                    {
                        verificador = 0;
                    }
                }

                printf("[H]Horizontal\n[V]Vertical\n");
                d->orientporta1 = getch();
                d->orientporta1 = toupper(d->orientporta1); //funcion para ignorar minusculas

                if (d->orientporta1 == 'H')
                {
                    if (/*der1*/ tablero1[d->porta1x][d->porta1y + 1] == 1 && /*der2*/ tablero1[d->porta1x][d->porta1y + 2] == 1 && /*der3*/ tablero1[d->porta1x][d->porta1y + 3] == 1 || d->porta1y + 4 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else if (d->orientporta1 == 'V')
                {
                    if (/*abajo1*/ tablero1[d->porta1x + 1][d->porta1y] == 1 && /*abajo2*/ tablero1[d->porta1x + 2][d->porta1y - 1] == 1 && /*abajo3*/ tablero1[d->porta1x + 3][d->porta1y - 1] == 1 || d->porta1x + 4 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else
                {
                    verificador = 0;
                }

                while (verificador == 0)
                {
                    printf("\n¡Opción Inválida! [Es posble que tu nave esté tocando un punto no válido u ocupado en el tablero");
                    printf("\n[H]Horizontal\n[V]Vertical\n");
                    d->orientporta1 = getch();
                    d->orientporta1 = toupper(d->orientporta1);

                    if (d->orientporta1 == 'H')
                    {
                        if (tablero1[d->porta1x][d->porta1y + 1] == 1 || tablero1[d->porta1x][d->porta1y + 2] == 1 || d->porta1y + 2 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else if (d->orientporta1 == 'V')
                    {
                        if (tablero1[d->porta1x + 1][d->porta1y] == 1 || tablero1[d->porta1x + 2][d->porta1y] == 1 || d->porta1x + 2 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else
                    {
                        verificador = 0;
                    }
                }

                d->porta1y -= 1;
                ////////////////////////////////////////////////////////////////////////////////////////

                system("cls");
                //////////////////////////////////////////////////////////////TABLERO
                printf("                TABLERO DE POSICIONAMIENTO\n\n");
                printf("\t\t  1  2  3  4  5  6  7  8");
                letras = 65;
                for (i = 0; i < 8; i++)
                {
                    printf("\n\t\t");
                    printf("%c", letras);
                    letras = letras + 1;
                    for (j = 0; j < 8; j++)
                    {
                        if (d->porta1y == j && d->porta1x == i && d->orientporta1 == 'H' && j <= 5)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i][j + 1] = 1;
                            tablero1[i][j + 2] = 1;
                            tablero1[i][j + 3] = 1;
                            d->p1porta1 = d->porta1y;
                            d->p2porta1 = d->porta1y + 1;
                            d->p3porta1 = d->porta1y + 2;
                            d->p4porta1 = d->porta1y + 3;
                        }
                        else if (d->porta1y == j && d->porta1x == i && d->orientporta1 == 'V' && i <= 5)
                        {
                            tablero1[i][j] = 1;
                            tablero1[i + 1][j] = 1;
                            tablero1[i + 2][j] = 1;
                            tablero1[i + 3][j] = 1;
                            d->p1porta1 = d->porta1y;
                            d->p2porta1 = d->porta1y;
                            d->p3porta1 = d->porta1y;
                            d->p4porta1 = d->porta1y;
                        }
                        if (tablero1[i][j] == 1)
                        {
                            printf("|%c|", asterisco);
                        }
                        else
                            printf("|-|");
                    }
                    if (i == 3)
                    {
                        printf("         J1. [%s]", strupr(jugador1)); //QUIERO IMPRIMIR EL NOMBRE DEL JUGADOR 1/
                    }
                }
                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                ///////////////////////////////////////////////////////////////////////////////////

                if (d->orientporta1 == 'H')
                {
                    printf("\nPortaviones poscicionado en horizontal, en las coordenadas [%c,%d], [%c,%d], [%c,%d] y [%c,%d]\n ", impport1, d->p1porta1 + 1, impport1, d->p2porta1 + 1, impport1, d->p3porta1 + 1, impport1, d->p4porta1 + 1);
                }
                else if (d->orientporta1 == 'V')
                {
                    printf("\n Portaviones poscicionado en vertical, en las coordenadas [%c,%d], [%c,%d], [%c,%d] y [%c,%d]\n", impport1, d->p1porta1 + 1, impport1 + 1, d->p2porta1 + 1, impport1 + 2, d->p3porta1 + 1, impport1 + 3, d->p4porta1 + 1);
                }
                contaportas = contaportas - 1;
                printf("\nGuardando datos...");
                Sleep(4000);
            }
            else
            {
                printf("\n\nAgotaste tu cantidad de Portaviones!");
                Sleep(2000);
            }
            system("cls");
            //////////////////////////////////////////////////////////////TABLERO
            printf("                TABLERO DE POSICIONAMIENTO\n\n");
            printf("\t\t  1  2  3  4  5  6  7  8");
            letras = 65;
            for (i = 0; i < 8; i++)
            {
                printf("\n\t\t");
                printf("%c", letras);
                letras = letras + 1;
                for (j = 0; j < 8; j++)
                {

                    if (d->porta1y == j && d->porta1x == i && d->orientporta1 == 'H' && j <= 5)
                    {
                        tablero1[i][j] = 1;
                        tablero1[i][j + 1] = 1;
                        tablero1[i][j + 2] = 1;
                        tablero1[i][j + 3] = 1;
                        d->p1porta1 = d->porta1y;
                        d->p2porta1 = d->porta1y + 1;
                        d->p3porta1 = d->porta1y + 2;
                        d->p4porta1 = d->porta1y + 3;
                    }
                    else if (d->porta1y == j && d->porta1x == i && d->orientporta1 == 'V' && i <= 5)
                    {
                        tablero1[i][j] = 1;
                        tablero1[i + 1][j] = 1;
                        tablero1[i + 2][j] = 1;
                        tablero1[i + 3][j] = 1;
                        d->p1porta1 = d->porta1y;
                        d->p2porta1 = d->porta1y;
                        d->p3porta1 = d->porta1y;
                        d->p4porta1 = d->porta1y;
                    }
                    if (tablero1[i][j] == 1)
                    {
                        printf("|%c|", asterisco);
                    }
                    else
                        printf("|-|");
                }
                if (i == 3)
                {
                    printf("         J1. [%s]", strupr(jugador1)); //QUIERO IMPRIMIR EL NOMBRE DEL JUGADOR 1/
                }
            }
            printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
            ///////////////////////////////////////////////////////////////////////////////////
            break;
        }
    } while (contabarcos > 0 || contabuques > 0 || contaportas > 0); //CUANDO EL JUGADOR YA POSICIONÓ TODOS SUS BARCOS
}

struct barcos2
{
    int barco1y, barco2y, p1barco1, p2barco1, p1barco2, p2barco2;
    char orientbar1, orientbar2, barco1x, barco2x; //barco1x,barco1y,barco2x,barco2y(coordenadas)         orientbar1,orientbar2(orientaciones)       p1barco1,p2barco1,p1barco2,p2barco2 (puntos)
};

struct buques2
{
    int buque1y, buque2y, p1buque1, p2buque1, p3buque1, p1buque2, p2buque2, p3buque2; //buque1x,buque1y,buque2x,buque2y(coordenadas)          orientbuq1,orientbuq2(orientaciones)       p1buque1,p2buque1,p3buque1,p1buque2,p2buque2,p3buque2 (puntos)
    char orientbuq1, orientbuq2, buque1x, buque2x;
};

struct Portaviones2
{
    int porta1y, p1porta1, p2porta1, p3porta1, p4porta1; //porta1x,porta1y           orientport1         p1porta1,p2porta1,p3porta1,p4porta1(puntos)
    char orientporta1, porta1x;
};

struct contadores2
{
    int contabarcos;
    int contabuques;
    int contaportas;
};

void tableroJugador2(char *jugador2, int tablero2[8][8], struct barcos2 *b, struct buques2 *c, struct Portaviones2 *d, struct contadores2 *e)
{
    int i, j, verificador;
    char nave, letras, impbar1, impbar2, impbuq1, impbuq2, impport1;
    int contabarcos = 2, contabuques = 2, contaportas = 1;
    int fallo = 31;
    int asterisco = 42;
    int carita = 1;

    system("cls");
    //////////////////////////////////////////////////////////////TABLERO
    printf("                TABLERO DE POSICIONAMIENTO\n\n");
    printf("\t\t  1  2  3  4  5  6  7  8");
    letras = 65;

    for (i = 0; i < 8; i++)
    {

        printf("\n\t\t");
        printf("%c", letras);
        letras = letras + 1;
        for (j = 0; j < 8; j++)
        {
            tablero2[i][j] = 0;
            printf("|-|");
        }
        if (i == 3)
        {
            printf("         J2. [%s]", strupr(jugador2));
        }
    }
    printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);

    ///////////////////////////////////////////////////////////////////////////////////
    do
    {

        printf("\n\nQue tipo de nave desea colocar?\n 1. BARCO(x%d)\n 2. BUQUE(x%d) \n 3. PORTAVIONES(x%d)\n", contabarcos, contabuques, contaportas);
        nave = getch();

        switch (nave)
        {
        case '1': //BARCO

            if (contabarcos > 0)
            {
                system("cls");

                //////////////////////////////////////////////////////////////TABLERO
                printf("                TABLERO DE POSICIONAMIENTO\n\n");
                printf("\t\t  1  2  3  4  5  6  7  8");
                letras = 65;

                for (i = 0; i < 8; i++)
                {

                    printf("\n\t\t");
                    printf("%c", letras);
                    letras = letras + 1;
                    for (j = 0; j < 8; j++)
                    {
                        if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'H' && j < 7)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i][j + 1] = 1;
                            b->p1barco1 = b->barco1x;
                            b->p2barco1 = b->barco1y + 1;
                        }
                        else if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'V' && i < 7)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i + 1][j] = 1;
                            b->p1barco1 = b->barco1x + 1;
                            b->p2barco1 = b->barco1y;
                        }
                        else if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'H' && j < 7)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i][j + 1] = 1;
                            b->p1barco2 = b->barco2x;
                            b->p2barco2 = b->barco2y + 1;
                        }
                        else if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'V' && i < 7)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i + 1][j] = 1;
                            b->p1barco2 = b->barco2x + 1;
                            b->p2barco2 = b->barco2y;
                        }
                        if (tablero2[i][j] == 1)
                        {
                            printf("|%c|", asterisco);
                        }
                        else
                            printf("|-|");
                    }
                    if (i == 3)
                    {
                        printf("         J2. [%s]", strupr(jugador2));
                    }
                }
                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);

                ///////////////////////////////////////////////////////////////////////////////////

                verificador = 0;
                printf("\n\nPOSCICIONAMIENTO DE BARCOS\n");
                printf("\t\t\tLos barcos ocupan [2] espacios \n\t\t\t[ocuparán tanto un espacio hacia abaio o hacia la derecha según su coordenada]\n");

                //BARCO 1
                printf("\nIntroduzca la primera coordenada del barco 1: ");
                scanf(" %c%d", &b->barco1x, &b->barco1y);
                b->barco1x = toupper(b->barco1x); //FUNCION PARA IGNORAR MINUSCULAS

                ///////////////////////////////////////VERIFICADORES
                if (b->barco1x == 'A' || b->barco1x == 'B' || b->barco1x == 'C' || b->barco1x == 'D' || b->barco1x == 'E' || b->barco1x == 'F' || b->barco1x == 'G' || b->barco1x == 'H')
                {
                    if (b->barco1y > 0 && b->barco1y <= 8)
                    {
                        if (b->barco1x == 'A')
                        {
                            b->barco1x = 0;
                            impbar1 = 65;
                        }
                        else if (b->barco1x == 'B')
                        {
                            b->barco1x = 1;
                            impbar1 = 66;
                        }
                        else if (b->barco1x == 'C')
                        {
                            b->barco1x = 2;
                            impbar1 = 67;
                        }
                        else if (b->barco1x == 'D')
                        {
                            b->barco1x = 3;
                            impbar1 = 68;
                        }
                        else if (b->barco1x == 'E')
                        {
                            b->barco1x = 4;
                            impbar1 = 69;
                        }
                        else if (b->barco1x == 'F')
                        {
                            b->barco1x = 5;
                            impbar1 = 70;
                        }
                        else if (b->barco1x == 'G')
                        {
                            b->barco1x = 6;
                            impbar1 = 71;
                        }
                        else if (b->barco1x == 'H')
                        {
                            b->barco1x = 7;
                            impbar1 = 72;
                        }
                        for (i = 0; i < 8; i++)
                        {
                            for (j = 0; j < 8; j++)
                            {
                                if (/*cen*/ tablero2[b->barco1x][b->barco1y - 1] == 1 || (/*der*/ tablero2[b->barco1x][b->barco1y] == 1 && /*abajo*/ tablero2[b->barco1x + 1][b->barco1y - 1] == 1) || ((b->barco1x >= 7) && (b->barco1y - 1 >= 7)))
                                {
                                    verificador = 0;
                                }
                                else
                                    verificador = 1;
                            }
                        }
                    }
                    else
                        verificador = 0;
                }
                else
                {
                    verificador = 0;
                }

                while (verificador == 0)
                {
                    printf("Vaya! parece que esta coordenada no es válida, inténtalo denuevo: ");
                    scanf(" %c%d", &b->barco1x, &b->barco1y);
                    b->barco1x = toupper(b->barco1x);

                    if (b->barco1x == 'A' || b->barco1x == 'B' || b->barco1x == 'C' || b->barco1x == 'D' || b->barco1x == 'E' || b->barco1x == 'F' || b->barco1x == 'G' || b->barco1x == 'H')
                    {
                        if (b->barco1y > 0 && b->barco1y <= 8)
                        {
                            if (b->barco1x == 'A')
                            {
                                b->barco1x = 0;
                                impbar1 = 65;
                            }
                            else if (b->barco1x == 'B')
                            {
                                b->barco1x = 1;
                                impbar1 = 66;
                            }
                            else if (b->barco1x == 'C')
                            {
                                b->barco1x = 2;
                                impbar2 = 67;
                            }
                            else if (b->barco1x == 'D')
                            {
                                b->barco1x = 3;
                                impbar1 = 68;
                            }
                            else if (b->barco1x == 'E')
                            {
                                b->barco1x = 4;
                                impbar1 = 69;
                            }
                            else if (b->barco1x == 'F')
                            {
                                b->barco1x = 5;
                                impbar1 = 70;
                            }
                            else if (b->barco1x == 'G')
                            {
                                b->barco1x = 6;
                                impbar1 = 71;
                            }
                            else if (b->barco1x == 'H')
                            {
                                b->barco1x = 7;
                                impbar1 = 72;
                            }

                            for (i = 0; i < 8; i++)
                            {
                                for (j = 0; j < 8; j++)
                                {
                                    if (/*cen*/ tablero2[b->barco1x][b->barco1y - 1] == 1 || (/*der*/ tablero2[b->barco1x][b->barco1y] == 1 && /*abajo*/ tablero2[b->barco1x + 1][b->barco1y - 1] == 1) || ((b->barco1x >= 7) && (b->barco1y - 1 >= 7)))
                                    {
                                        verificador = 0;
                                    }
                                    else
                                        verificador = 1;
                                }
                            }
                        }
                        else
                            verificador = 0;
                    }
                    else
                    {
                        verificador = 0;
                    }
                }

                b->barco1y -= 1;
                printf("[H]Horizontal\n[V]Vertical\n");
                b->orientbar1 = getch();
                b->orientbar1 = toupper(b->orientbar1); //funcion para ignorar minusculas

                if (b->orientbar1 == 'H')
                {
                    if (b->barco1y + 2 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else if (b->orientbar1 == 'V')
                {
                    if (b->barco1x + 2 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else
                {
                    verificador = 0;
                }

                while (verificador == 0)
                {
                    printf("¡Opción Inválida! [Es posble que tu nave esté tocando un punto no válido u ocupado en el tablero]\n");
                    printf("[H]Horizontal\n[V]Vertical\n");
                    b->orientbar1 = getch();
                    b->orientbar1 = toupper(b->orientbar1);
                    if (b->orientbar1 == 'H')
                    {
                        if (b->barco1y + 2 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else if (b->orientbar1 == 'V')
                    {
                        if (b->barco1x + 2 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else
                    {
                        verificador = 0;
                    }
                }
                /////////////////////////////////////////////////////////////////////////////////////////
                //BARCO 2
                system("cls");
                //////////////////////////////////////////////////////////////TABLERO
                printf("                TABLERO DE POSICIONAMIENTO\n\n");
                printf("\t\t  1  2  3  4  5  6  7  8");
                letras = 65;

                for (i = 0; i < 8; i++)
                {
                    printf("\n\t\t");
                    printf("%c", letras);
                    letras = letras + 1;
                    for (j = 0; j < 8; j++)
                    {
                        if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'H' && j < 7)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i][j + 1] = 1;
                            b->p1barco1 = b->barco1x;
                            b->p2barco1 = b->barco1y + 1;
                        }
                        else if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'V' && i < 7)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i + 1][j] = 1;
                            b->p1barco1 = b->barco1x + 1;
                            b->p2barco1 = b->barco1y;
                        }
                        if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'H' && j < 7)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i][j + 1] = 1;
                            b->p1barco2 = b->barco2x;
                            b->p2barco2 = b->barco2y + 1;
                        }
                        else if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'V' && i < 7)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i + 1][j] = 1;
                            b->p1barco2 = b->barco2x + 1;
                            b->p2barco2 = b->barco2y;
                        }
                        if (tablero2[i][j] == 1)
                        {
                            printf("|%c|", asterisco);
                        }
                        else
                            printf("|-|");
                    }
                    if (i == 3)
                    {
                        printf("         J2. [%s]", strupr(jugador2));
                    }
                }
                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                ///////////////////////////////////////////////////////////////////////////////////

                printf("\n\nIntroduzca la primera coordenada del barco 2: ");
                scanf(" %c%d", &b->barco2x, &b->barco2y);
                b->barco2x = toupper(b->barco2x);

                ///////////////////////////////////////VERIFICADORES
                if (b->barco2x == 'A' || b->barco2x == 'B' || b->barco2x == 'C' || b->barco2x == 'D' || b->barco2x == 'E' || b->barco2x == 'F' || b->barco2x == 'G' || b->barco2x == 'H')
                {
                    if (b->barco2y > 0 && b->barco2y <= 8)
                    {
                        if (b->barco2x == 'A')
                        {
                            b->barco2x = 0;
                            impbar2 = 65;
                        }
                        else if (b->barco2x == 'B')
                        {
                            b->barco2x = 1;
                            impbar2 = 66;
                        }
                        else if (b->barco2x == 'C')
                        {
                            b->barco2x = 2;
                            impbar2 = 67;
                        }
                        else if (b->barco2x == 'D')
                        {
                            b->barco2x = 3;
                            impbar2 = 68;
                        }
                        else if (b->barco2x == 'E')
                        {
                            b->barco2x = 4;
                            impbar2 = 69;
                        }
                        else if (b->barco2x == 'F')
                        {
                            b->barco2x = 5;
                            impbar2 = 70;
                        }
                        else if (b->barco2x == 'G')
                        {
                            b->barco2x = 6;
                            impbar2 = 71;
                        }
                        else if (b->barco2x == 'H')
                        {
                            b->barco2x = 7;
                            impbar2 = 72;
                        }
                        if (/*cen*/ tablero2[b->barco2x][b->barco2y - 1] == 1 || (/*der*/ tablero2[b->barco2x][b->barco2y] == 1 && /*abajo*/ tablero2[b->barco2x + 1][b->barco2y - 1] == 1) || ((b->barco2x >= 7) && (b->barco2y - 1 >= 7)))
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else
                        verificador = 0;
                }
                else
                {
                    verificador = 0;
                }
                while (verificador == 0)
                {
                    printf("Vaya! parece que esta coordenada no es válida, inténtalo denuevo: ");
                    scanf(" %c%d", &b->barco2x, &b->barco2y);
                    b->barco2x = toupper(b->barco2x);
                    if (b->barco2x == 'A' || b->barco2x == 'B' || b->barco2x == 'C' || b->barco2x == 'D' || b->barco2x == 'E' || b->barco2x == 'F' || b->barco2x == 'G' || b->barco2x == 'H')
                    {
                        if (b->barco2y > 0 && b->barco2y <= 8)
                        {
                            if (b->barco2x == 'A')
                            {
                                b->barco2x = 0;
                                impbar2 = 65;
                            }
                            else if (b->barco2x == 'B')
                            {
                                b->barco2x = 1;
                                impbar2 = 66;
                            }
                            else if (b->barco2x == 'C')
                            {
                                b->barco2x = 2;
                                impbar2 = 67;
                            }
                            else if (b->barco2x == 'D')
                            {
                                b->barco2x = 3;
                                impbar2 = 68;
                            }
                            else if (b->barco2x == 'E')
                            {
                                b->barco2x = 4;
                                impbar2 = 69;
                            }
                            else if (b->barco2x == 'F')
                            {
                                b->barco2x = 5;
                                impbar2 = 70;
                            }
                            else if (b->barco2x == 'G')
                            {
                                b->barco2x = 6;
                                impbar2 = 71;
                            }
                            else if (b->barco2x == 'H')
                            {
                                b->barco2x = 7;
                                impbar2 = 72;
                            }
                            if (/*cen*/ tablero2[b->barco2x][b->barco2y - 1] == 1 || (/*der*/ tablero2[b->barco2x][b->barco2y] == 1 && /*abajo*/ tablero2[b->barco2x + 1][b->barco2y - 1] == 1) || ((b->barco2x >= 7) && (b->barco2y - 1 >= 7)))
                            {
                                verificador = 0;
                            }
                            else
                                verificador = 1;
                        }
                        else
                            verificador = 0;
                    }
                    else
                    {
                        verificador = 0;
                    }
                }

                b->barco2y -= 1;
                printf("[H]Horizontal\n[V]Vertical\n");
                b->orientbar2 = getch();
                b->orientbar2 = toupper(b->orientbar2); //funcion para ignorar minusculas

                if (b->orientbar2 == 'H')
                {
                    if (b->barco2y + 2 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else if (b->orientbar2 == 'V')
                {
                    if (b->barco2x + 2 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else
                {
                    verificador = 0;
                }

                while (verificador == 0)
                {
                    printf("¡Opción Inválida! [Es posble que tu nave esté tocando un punto no válido u ocupado en el tablero]\n");
                    printf("[H]Horizontal\n[V]Vertical\n");
                    b->orientbar2 = getch();
                    b->orientbar2 = toupper(b->orientbar2);
                    if (b->orientbar2 == 'H')
                    {
                        if (b->barco2y + 2 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else if (b->orientbar2 == 'V')
                    {
                        if (b->barco2x + 2 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else
                        verificador = 0;
                }
                ///////////////////////////////////////////////////////////////////////////////////////////

                system("cls");

                //////////////////////////////////////////////////////////////TABLERO
                printf("                TABLERO DE POSICIONAMIENTO\n\n");
                printf("\t\t  1  2  3  4  5  6  7  8");
                letras = 65;
                for (i = 0; i < 8; i++)
                {
                    printf("\n\t\t");
                    printf("%c", letras);
                    letras = letras + 1;
                    for (j = 0; j < 8; j++)
                    {
                        if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'H' && j < 7)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i][j + 1] = 1;
                            b->p1barco1 = b->barco1x;
                            b->p2barco1 = b->barco1y + 1;
                        }
                        else if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'V' && i < 7)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i + 1][j] = 1;
                            b->p1barco1 = b->barco1x + 1;
                            b->p2barco1 = b->barco1y;
                        }
                        else if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'H' && j < 7)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i][j + 1] = 1;
                            b->p1barco2 = b->barco2x;
                            b->p2barco2 = b->barco2y + 1;
                        }
                        else if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'V' && i < 7)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i + 1][j] = 1;
                            b->p1barco2 = b->barco2x + 1;
                            b->p2barco2 = b->barco2y;
                        }
                        if (tablero2[i][j] == 1)
                        {
                            printf("|%c|", asterisco);
                        }
                        else
                            printf("|-|");
                    }
                    if (i == 3)
                    {
                        printf("         J2. [%s]", strupr(jugador2));
                    }
                }
                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);

                ///////////////////////////////////////////////////////////////////////////////////

                if (b->orientbar1 == 'H')
                {
                    printf("\nPrimer barco poscicionado en Horizontal en las coordenadas [%c,%d] y [%c,%d]\n", impbar1, b->barco1y + 1, impbar1, b->p2barco1 + 1);
                }
                else if (b->orientbar1 == 'V')
                {
                    printf("\nPrimer barco poscicionado en Vertical en las coordenadas [%c,%d] y [%c,%d]\n", impbar1, b->barco1y + 1, impbar1 + 1, b->p2barco1 + 1);
                }
                if (b->orientbar2 == 'H')
                {
                    printf("\nSegundo barco Poscicionado en Horizontal en las coordenadas [%c,%d] y [%c,%d]\n", impbar2, b->barco2y + 1, impbar2, b->p2barco2 + 1);
                }
                else if (b->orientbar2 == 'V')
                {
                    printf("\nSegundo barco poscicionado en Vertical en las coordenadas [%c,%d] y [%c,%d\]\n", impbar2, b->barco2y + 1, impbar2 + 1, b->p2barco2 + 1);
                }
                contabarcos -= 2;
                printf("\nGuardando datos...");
                Sleep(4000);
            }
            else
            {
                printf("\nAgotaste tu cantidad de barcos!");
                Sleep(1000);
            }
            system("cls");
            //////////////////////////////////////////////////////////////TABLERO
            printf("                TABLERO DE POSICIONAMIENTO\n\n");
            printf("\t\t  1  2  3  4  5  6  7  8");
            letras = 65;

            for (i = 0; i < 8; i++)
            {

                printf("\n\t\t");
                printf("%c", letras);
                letras = letras + 1;
                for (j = 0; j < 8; j++)
                {
                    if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'H' && j < 7)
                    {
                        tablero2[i][j] = 1;
                        tablero2[i][j + 1] = 1;
                        b->p1barco1 = b->barco1x;
                        b->p2barco1 = b->barco1y + 1;
                    }
                    else if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'V' && i < 7)
                    {
                        tablero2[i][j] = 1;
                        tablero2[i + 1][j] = 1;
                        b->p1barco1 = b->barco1x + 1;
                        b->p2barco1 = b->barco1y;
                    }
                    else if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'H' && j < 7)
                    {
                        tablero2[i][j] = 1;
                        tablero2[i][j + 1] = 1;
                        b->p1barco2 = b->barco2x;
                        b->p2barco2 = b->barco2y + 1;
                    }
                    else if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'V' && i < 7)
                    {
                        tablero2[i][j] = 1;
                        tablero2[i + 1][j] = 1;
                        b->p1barco2 = b->barco2x + 1;
                        b->p2barco2 = b->barco2y;
                    }
                    if (tablero2[i][j] == 1)
                    {
                        printf("|%c|", asterisco);
                    }
                    else
                        printf("|-|");
                }
                if (i == 3)
                {
                    printf("         J2. [%s]", strupr(jugador2));
                }
            }
            printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);

            ///////////////////////////////////////////////////////////////////////////////////
            break;

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case '2':

            if (contabuques > 0)
            {
                system("cls");
                //////////////////////////////////////////////////////////////TABLERO
                printf("                TABLERO DE POSICIONAMIENTO\n\n");
                printf("\t\t  1  2  3  4  5  6  7  8");
                letras = 65;

                for (i = 0; i < 8; i++)
                {
                    printf("\n\t\t");
                    printf("%c", letras);
                    letras = letras + 1;
                    for (j = 0; j < 8; j++)
                    {
                        if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'H' && j < 7)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i][j + 1] = 1;
                            b->p1barco1 = b->barco1x;
                            b->p2barco1 = b->barco1y + 1;
                        }
                        else if (b->barco1y == j && b->barco1x == i && b->orientbar1 == 'V' && i < 7)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i + 1][j] = 1;
                            b->p1barco1 = b->barco1x + 1;
                            b->p2barco1 = b->barco1y;
                        }
                        if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'H' && j < 7)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i][j + 1] = 1;
                            b->p1barco2 = b->barco2x;
                            b->p2barco2 = b->barco2y + 1;
                        }
                        else if (b->barco2y == j && b->barco2x == i && b->orientbar2 == 'V' && i < 7)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i + 1][j] = 1;
                            b->p1barco2 = b->barco2x + 1;
                            b->p2barco2 = b->barco2y;
                        }
                        if (tablero2[i][j] == 1)
                        {
                            printf("|%c|", asterisco);
                        }
                        else
                            printf("|-|");
                    }
                    if (i == 3)
                    {
                        printf("         J2. [%s]", strupr(jugador2));
                    }
                }
                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);

                //////////////////////////////////////////////////////////////////////////////////
                //BUQUE 1
                printf("\n\nPOSCICIONAMIENTO DE BUQUES\n");
                printf("\t\t\tLos buques ocupan [3] espacios\n\t\t\t[ocuparán tanto dos espacios hacia abaio o hacia la derecha según su coordenada]\n");
                printf("\nIntroduzca la primera coordenada del buque 1: ");
                scanf(" %c%d", &c->buque1x, &c->buque1y);
                c->buque1x = toupper(c->buque1x);

                ///////////////////////////////////////VERIFICADORES

                if (c->buque1x == 'A' || c->buque1x == 'B' || c->buque1x == 'C' || c->buque1x == 'D' || c->buque1x == 'E' || c->buque1x == 'F' || c->buque1x == 'G' || c->buque1x == 'H')
                {
                    if (c->buque1y > 0 && c->buque1y <= 8)
                    {
                        if (c->buque1x == 'A')
                        {
                            c->buque1x = 0;
                            impbuq1 = 65;
                        }
                        else if (c->buque1x == 'B')
                        {
                            c->buque1x = 1;
                            impbuq1 = 66;
                        }
                        else if (c->buque1x == 'C')
                        {
                            c->buque1x = 2;
                            impbuq1 = 67;
                        }
                        else if (c->buque1x == 'D')
                        {
                            c->buque1x = 3;
                            impbuq1 = 68;
                        }
                        else if (c->buque1x == 'E')
                        {
                            c->buque1x = 4;
                            impbuq1 = 69;
                        }
                        else if (c->buque1x == 'F')
                        {
                            c->buque1x = 5;
                            impbuq1 = 70;
                        }
                        else if (c->buque1x == 'G')
                        {
                            c->buque1x = 6;
                            impbuq1 = 71;
                        }
                        else if (c->buque1x == 'H')
                        {
                            c->buque1x = 7;
                            impbuq1 = 72;
                        }

                        for (i = 0; i < 8; i++)
                        {
                            for (j = 0; j < 8; j++)
                            {
                                if (/*cen*/ tablero2[c->buque1x][c->buque1y - 1] == 1 || (/*der1*/ tablero2[c->buque1x][c->buque1y] == 1 && /*der2*/ tablero2[c->buque1x][c->buque1y + 1] == 1 && /*abajo1*/ tablero2[c->buque1x + 1][c->buque1y - 1] == 1 && /*abajo2*/ tablero2[c->buque1x + 2][c->buque1y - 1] == 1) || ((c->buque1x >= 6) && (c->buque1y - 1 >= 6)))
                                {
                                    verificador = 0;
                                }
                                else
                                    verificador = 1;
                            }
                        }
                    }
                    else
                        verificador = 0;
                }
                else
                {
                    verificador = 0;
                }
                while (verificador == 0)
                {
                    printf("Vaya! parece que esta coordenada no es válida, inténtalo denuevo: ");
                    scanf(" %c%d", &c->buque1x, &c->buque1y);
                    c->buque1x = toupper(c->buque1x);
                    if (c->buque1x == 'A' || c->buque1x == 'B' || c->buque1x == 'C' || c->buque1x == 'D' || c->buque1x == 'E' || c->buque1x == 'F' || c->buque1x == 'G' || c->buque1x == 'H')
                    {
                        if (c->buque1y > 0 && c->buque1y <= 8)
                        {
                            if (c->buque1x == 'A')
                            {
                                c->buque1x = 0;
                                impbuq1 = 65;
                            }
                            else if (c->buque1x == 'B')
                            {
                                c->buque1x = 1;
                                impbuq1 = 66;
                            }
                            else if (c->buque1x == 'C')
                            {
                                c->buque1x = 2;
                                impbuq1 = 67;
                            }
                            else if (c->buque1x == 'D')
                            {
                                c->buque1x = 3;
                                impbuq1 = 68;
                            }
                            else if (c->buque1x == 'E')
                            {
                                c->buque1x = 4;
                                impbuq1 = 69;
                            }
                            else if (c->buque1x == 'F')
                            {
                                c->buque1x = 5;
                                impbuq1 = 70;
                            }
                            else if (c->buque1x == 'G')
                            {
                                c->buque1x = 6;
                                impbuq1 = 71;
                            }
                            else if (c->buque1x == 'H')
                            {
                                c->buque1x = 7;
                                impbuq1 = 72;
                            }

                            for (i = 0; i < 8; i++)
                            {
                                for (j = 0; j < 8; j++)
                                {
                                    if (/*cen*/ tablero2[c->buque1x][c->buque1y - 1] == 1 || (/*der1*/ tablero2[c->buque1x][c->buque1y] == 1 && /*der2*/ tablero2[c->buque1x][c->buque1y + 1] == 1 && /*abajo1*/ tablero2[c->buque1x + 1][c->buque1y - 1] == 1 && /*abajo2*/ tablero2[c->buque1x + 2][c->buque1y - 1] == 1) || ((c->buque1x >= 6) && (c->buque1y - 1 >= 6)))
                                    {
                                        verificador = 0;
                                    }
                                    else
                                        verificador = 1;
                                }
                            }
                        }
                        else
                            verificador = 0;
                    }
                    else
                    {
                        verificador = 0;
                    }
                }

                c->buque1y -= 1;
                printf("[H]Horizontal\n[V]Vertical\n");
                c->orientbuq1 = getch();
                c->orientbuq1 = toupper(c->orientbuq1); //funcion para ignorar minusculas

                if (c->orientbuq1 == 'H')
                {
                    if (/*der1*/ tablero2[c->buque1x][c->buque1y + 1] == 1 || /*der2*/ tablero2[c->buque1x][c->buque1y + 2] == 1 || c->buque1y + 3 > 8 || c->buque1y + 3 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else if (c->orientbuq1 == 'V')
                {
                    if (/*abajo1*/ tablero2[c->buque1x + 1][c->buque1y - 1] == 1 || /*abajo2*/ tablero2[c->buque1x + 2][c->buque1y - 1] == 1 || c->buque1x + 3 > 8 || c->buque1x + 3 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else
                {
                    verificador = 0;
                }

                while (verificador == 0)
                {
                    printf("¡Opción Inválida! [Es posble que tu nave esté tocando un punto no válido u ocupado en el tablero]");
                    printf("\n[H]Horizontal\n[V]Vertical\n");
                    c->orientbuq1 = getch();
                    c->orientbuq1 = toupper(c->orientbuq1);
                    if (c->orientbuq1 == 'H')
                    {
                        if (/*der1*/ tablero2[c->buque1x][c->buque1y + 1] == 1 || /*der2*/ tablero2[c->buque1x][c->buque1y + 2] == 1 || c->buque1y + 3 > 8 || c->buque1y + 3 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else if (c->orientbuq1 == 'V')
                    {
                        if (/*abajo1*/ tablero2[c->buque1x + 1][c->buque1y - 1] == 1 || /*abajo2*/ tablero2[c->buque1x + 2][c->buque1y - 1] == 1 || c->buque1x + 3 > 8 || c->buque1x + 3 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else
                    {
                        verificador = 0;
                    }
                }
                ////////////////////////////////////////////////////////////////////////////////////////

                //BUQUE 2
                system("cls");
                //////////////////////////////////////////////////////////////TABLERO
                printf("                TABLERO DE POSICIONAMIENTO\n\n");
                printf("\t\t  1  2  3  4  5  6  7  8");
                letras = 65;

                for (i = 0; i < 8; i++)
                {
                    printf("\n\t\t");
                    printf("%c", letras);
                    letras = letras + 1;
                    for (j = 0; j < 8; j++)
                    {
                        if (c->buque1y == j && c->buque1x == i && c->orientbuq1 == 'H' && j <= 6)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i][j + 1] = 1;
                            tablero2[i][j + 2] = 1;
                            c->p1buque1 = c->buque1y;
                            c->p2buque1 = c->buque1y + 1;
                            c->p3buque1 = c->buque1y + 2;
                        }
                        else if (c->buque1y == j && c->buque1x == i && c->orientbuq1 == 'V' && i <= 6)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i + 1][j] = 1;
                            tablero2[i + 2][j] = 1;
                            c->p1buque1 = c->buque1y;
                            c->p2buque1 = c->buque1y;
                            c->p3buque1 = c->buque1y;
                        }
                        if (c->buque2y == j && c->buque2x == i && c->orientbuq2 == 'H' && j <= 6)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i][j + 1] = 1;
                            tablero2[i][j + 2] = 1;
                            c->p1buque2 = c->buque2y;
                            c->p2buque2 = c->buque2y + 1;
                            c->p3buque2 = c->buque2y + 2;
                        }
                        else if (c->buque2y == j && c->buque2x == i && c->orientbuq2 == 'V' && i <= 6)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i + 1][j] = 1;
                            tablero2[i + 2][j] = 1;
                            c->p1buque2 = c->buque2y;
                            c->p2buque2 = c->buque2y;
                            c->p3buque2 = c->buque2y;
                        }
                        if (tablero2[i][j] == 1)
                        {
                            printf("|%c|", asterisco);
                        }
                        else
                            printf("|-|");
                    }
                    if (i == 3)
                    {
                        printf("         J2. [%s]", strupr(jugador2));
                    }
                }
                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);

                ///////////////////////////////////////////////////////////////////////////////////

                printf("\nIntroduzca la primera coordenada del buque 2: ");
                scanf(" %c%d", &c->buque2x, &c->buque2y);
                c->buque2x = toupper(c->buque2x);

                ///////////////////////////////////////VERIFICADORES

                if (c->buque2x == 'A' || c->buque2x == 'B' || c->buque2x == 'C' || c->buque2x == 'D' || c->buque2x == 'E' || c->buque2x == 'F' || c->buque2x == 'G' || c->buque2x == 'H')
                {
                    if (c->buque2y > 0 && c->buque2y <= 8)
                    {
                        if (c->buque2x == 'A')
                        {
                            c->buque2x = 0;
                            impbuq2 = 65;
                        }
                        else if (c->buque2x == 'B')
                        {
                            c->buque2x = 1;
                            impbuq2 = 66;
                        }
                        else if (c->buque2x == 'C')
                        {
                            c->buque2x = 2;
                            impbuq2 = 67;
                        }
                        else if (c->buque2x == 'D')
                        {
                            c->buque2x = 3;
                            impbuq2 = 68;
                        }
                        else if (c->buque2x == 'E')
                        {
                            c->buque2x = 4;
                            impbuq2 = 69;
                        }
                        else if (c->buque2x == 'F')
                        {
                            c->buque2x = 5;
                            impbuq2 = 70;
                        }
                        else if (c->buque2x == 'G')
                        {
                            c->buque2x = 6;
                            impbuq2 = 71;
                        }
                        else if (c->buque2x == 'H')
                        {
                            c->buque2x = 7;
                            impbuq2 = 72;
                        }

                        for (i = 0; i < 8; i++)
                        {
                            for (j = 0; j < 8; j++)
                            {
                                if (tablero2[c->buque2y][c->buque2x + 1] == 1)
                                {
                                    verificador = 0;
                                }
                                else
                                    verificador = 1;
                            }
                        }
                    }
                    else
                        verificador = 0;
                }

                else
                {
                    verificador = 0;
                }
                while (verificador == 0)
                {
                    printf("Vaya! parece que esta coordenada no es válida, inténtalo denuevo:  ");
                    scanf(" %c%d", &c->buque2x, &c->buque2y);
                    c->buque2x = toupper(c->buque2x);
                    if (c->buque2x == 'A' || c->buque2x == 'B' || c->buque2x == 'C' || c->buque2x == 'D' || c->buque2x == 'E' || c->buque2x == 'F' || c->buque2x == 'G' || c->buque2x == 'H')
                    {
                        if (c->buque2y > 0 && c->buque2y <= 8)
                        {
                            if (c->buque2x == 'A')
                            {
                                c->buque2x = 0;
                                impbuq2 = 65;
                            }
                            else if (c->buque2x == 'B')
                            {
                                c->buque2x = 1;
                                impbuq2 = 66;
                            }
                            else if (c->buque2x == 'C')
                            {
                                c->buque2x = 2;
                                impbuq2 = 67;
                            }
                            else if (c->buque2x == 'D')
                            {
                                c->buque2x = 3;
                                impbuq2 = 68;
                            }
                            else if (c->buque2x == 'E')
                            {
                                c->buque2x = 4;
                                impbuq2 = 69;
                            }
                            else if (c->buque2x == 'F')
                            {
                                c->buque2x = 5;
                                impbuq2 = 70;
                            }
                            else if (c->buque2x == 'G')
                            {
                                c->buque2x = 6;
                                impbuq2 = 71;
                            }
                            else if (c->buque2x == 'H')
                            {
                                c->buque2x = 7;
                                impbuq2 = 72;
                            }

                            for (i = 0; i < 8; i++)
                            {
                                for (j = 0; j < 8; j++)
                                {
                                    if (/*cen*/ tablero2[c->buque2x][c->buque2y - 1] == 1 || (/*der1*/ tablero2[c->buque2x][c->buque2y] == 1 && /*der2*/ tablero2[c->buque2x][c->buque2y + 1] == 1 && /*abajo1*/ tablero2[c->buque2x + 1][c->buque2y - 1] == 1 && /*abajo2*/ tablero2[c->buque2x + 2][c->buque2y - 1] == 1) || ((c->buque2x >= 6) && (c->buque2y - 1 >= 6)))
                                    {
                                        verificador = 0;
                                    }
                                    else
                                        verificador = 1;
                                }
                            }
                        }
                        else
                        {
                            verificador = 0;
                        }
                    }
                    else
                        verificador = 0;
                }

                c->buque2y -= 1;
                printf("[H]Horizontal\n[V]Vertical\n");
                c->orientbuq2 = getch();
                c->orientbuq2 = toupper(c->orientbuq2); //funcion para ignorar minusculas

                if (c->orientbuq2 == 'H')
                {
                    if (/*der1*/ tablero2[c->buque2x][c->buque2y + 1] == 1 || /*der2*/ tablero2[c->buque2x][c->buque2y + 2] == 1 || c->buque2y + 3 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else if (c->orientbuq2 == 'V')
                {
                    if (/*abajo1*/ tablero2[c->buque2x + 1][c->buque2y - 1] == 1 || /*abajo2*/ tablero2[c->buque2x + 2][c->buque2y - 1] == 1 || c->buque2x + 3 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else
                {
                    verificador = 0;
                }

                while (verificador == 0)
                {
                    printf("¡Opción Inválida! [Es posble que tu nave esté tocando un punto no válido u ocupado en el tablero]");
                    printf("\n[H]Horizontal\n[V]Vertical\n");
                    c->orientbuq2 = getch();
                    c->orientbuq2 = toupper(c->orientbuq2);
                    if (c->orientbuq2 == 'H')
                    {
                        if (/*der1*/ tablero2[c->buque2x][c->buque2y + 1] == 1 || /*der2*/ tablero2[c->buque2x][c->buque2y + 2] == 1 || c->buque2y + 3 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else if (c->orientbuq2 == 'V')
                    {
                        if (/*abajo1*/ tablero2[c->buque2x + 1][c->buque2y - 1] == 1 || /*abajo2*/ tablero2[c->buque2x + 2][c->buque2y - 1] == 1 || c->buque2x + 3 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else
                    {
                        verificador = 0;
                    }
                }
                ////////////////////////////////////////////////////////////////////////////////////////

                system("cls");
                //////////////////////////////////////////////////////////////TABLERO
                printf("                TABLERO DE POSICIONAMIENTO\n\n");
                printf("\t\t  1  2  3  4  5  6  7  8");
                letras = 65;
                for (i = 0; i < 8; i++)
                {
                    printf("\n\t\t");
                    printf("%c", letras);
                    letras = letras + 1;
                    for (j = 0; j < 8; j++)
                    {
                        if (c->buque1y == j && c->buque1x == i && c->orientbuq1 == 'H' && j <= 6)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i][j + 1] = 1;
                            tablero2[i][j + 2] = 1;
                            c->p1buque1 = c->buque1y;
                            c->p2buque1 = c->buque1y + 1;
                            c->p3buque1 = c->buque1y + 2;
                        }
                        else if (c->buque1y == j && c->buque1x == i && c->orientbuq1 == 'V' && i <= 6)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i + 1][j] = 1;
                            tablero2[i + 2][j] = 1;
                            c->p1buque1 = c->buque1y;
                            c->p2buque1 = c->buque1y;
                            c->p3buque1 = c->buque1y;
                        }
                        if (c->buque2y == j && c->buque2x == i && c->orientbuq2 == 'H' && j <= 6)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i][j + 1] = 1;
                            tablero2[i][j + 2] = 1;
                            c->p1buque2 = c->buque2y;
                            c->p2buque2 = c->buque2y + 1;
                            c->p3buque2 = c->buque2y + 2;
                        }
                        else if (c->buque2y == j && c->buque2x == i && c->orientbuq2 == 'V' && i <= 6)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i + 1][j] = 1;
                            tablero2[i + 2][j] = 1;
                            c->p1buque2 = c->buque2y;
                            c->p2buque2 = c->buque2y;
                            c->p3buque2 = c->buque2y;
                        }
                        if (tablero2[i][j] == 1)
                        {
                            printf("|%c|", asterisco);
                        }
                        else
                            printf("|-|");
                    }
                    if (i == 3)
                    {
                        printf("         J2. [%s]", strupr(jugador2));
                    }
                }
                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);

                ///////////////////////////////////////////////////////////////////////////////////

                if (c->orientbuq1 == 'H')
                {
                    printf("\nPrimer Buque poscicionado en horizontal, en las coordenadas [%c,%d], [%c,%d] y [%c,%d]\n ", impbuq1, c->p1buque1 + 1, impbuq1, c->p2buque1 + 1, impbuq1, c->p3buque1 + 1);
                }
                else if (c->orientbuq2 == 'V')
                {
                    printf("\nPrimer Buque Poscicionado en vertical, en las coordenadas [%c,%d], [%c,%d] y [%c,%d]\n", impbuq1, c->p1buque1, impbuq1 + 1, c->p2buque1, impbuq1 + 2, c->p3buque1);
                }
                if (c->orientbuq2 == 'H')
                {
                    printf("\nSegundo Buque Poscicionado en horizontal, en las coordenadas [%c,%d], [%c,%d] y [%c,%d]\n", impbuq2, c->p1buque2 + 1, impbuq2, c->p2buque2 + 1, impbuq2, c->p3buque2 + 1);
                }
                else if (c->orientbuq2 == 'V')
                {
                    printf("\nSegundo Buque Poscicionado en vertical en, las coordenadas [%c,%d], [%c,%d] y [%c,%d]\n", impbuq2, c->p1buque2, impbuq2 + 1, c->p2buque2, impbuq2 + 2, c->p3buque2);
                }
                contabuques = contabuques - 2;
                printf("\nGuardando datos...");
                Sleep(4000);
            }
            else
            {
                printf("\nAgotaste tu cantidad de buques!");
                Sleep(1000);
            }

            system("cls");
            //////////////////////////////////////////////////////////////TABLERO
            printf("                TABLERO DE POSICIONAMIENTO\n\n");
            printf("\t\t  1  2  3  4  5  6  7  8");
            letras = 65;

            for (i = 0; i < 8; i++)
            {

                printf("\n\t\t");
                printf("%c", letras);
                letras = letras + 1;
                for (j = 0; j < 8; j++)
                {
                    if (c->buque1y == j && c->buque1x == i && c->orientbuq1 == 'H' && j <= 6)
                    {
                        tablero2[i][j] = 1;
                        tablero2[i][j + 1] = 1;
                        tablero2[i][j + 2] = 1;
                        c->p1buque1 = c->buque1y;
                        c->p2buque1 = c->buque1y + 1;
                        c->p3buque1 = c->buque1y + 2;
                    }
                    else if (c->buque1y == j && c->buque1x == i && c->orientbuq1 == 'V' && i <= 6)
                    {
                        tablero2[i][j] = 1;
                        tablero2[i + 1][j] = 1;
                        tablero2[i + 2][j] = 1;
                        c->p1buque1 = c->buque1y;
                        c->p2buque1 = c->buque1y;
                        c->p3buque1 = c->buque1y;
                    }
                    if (c->buque2y == j && c->buque2x == i && c->orientbuq2 == 'H' && j <= 6)
                    {
                        tablero2[i][j] = 1;
                        tablero2[i][j + 1] = 1;
                        tablero2[i][j + 2] = 1;
                        c->p1buque2 = c->buque2y;
                        c->p2buque2 = c->buque2y + 1;
                        c->p3buque2 = c->buque2y + 2;
                    }
                    else if (c->buque2y == j && c->buque2x == i && c->orientbuq2 == 'V' && i <= 6)
                    {
                        tablero2[i][j] = 1;
                        tablero2[i + 1][j] = 1;
                        tablero2[i + 2][j] = 1;
                        c->p1buque2 = c->buque2y;
                        c->p2buque2 = c->buque2y;
                        c->p3buque2 = c->buque2y;
                    }
                    if (tablero2[i][j] == 1)
                    {
                        printf("|%c|", asterisco);
                    }
                    else
                        printf("|-|");
                }
                if (i == 3)
                {
                    printf("         J2. [%s]", strupr(jugador2));
                }
            }
            printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);

            ///////////////////////////////////////////////////////////////////////////////////

            break;

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case '3':

            if (contaportas > 0)
            {
                system("cls");

                //////////////////////////////////////////////////////////////TABLERO
                printf("                TABLERO DE POSICIONAMIENTO\n\n");
                printf("\t\t  1  2  3  4  5  6  7  8");
                letras = 65;

                for (i = 0; i < 8; i++)
                {
                    printf("\n\t\t");
                    printf("%c", letras);
                    letras = letras + 1;
                    for (j = 0; j < 8; j++)
                    {
                        if (tablero2[i][j] == 1)
                        {
                            printf("|%c|", asterisco);
                        }
                        else
                            printf("|-|");
                    }
                    if (i == 3)
                    {
                        printf("         J2. [%s]", strupr(jugador2)); //QUIERO IMPRIMIR EL NOMBRE DEL JUGADOR 1/
                    }
                }
                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);

                ///////////////////////////////////////////////////////////////////////////////////

                printf("\n\nPOSCICIONAMIENTO DE PORTAVIONES\n");
                printf("\t\t\tLos portaviones ocupan [4] espacios\n\t\t\t[ocuparán tanto cuatro espacios hacia abaio o hacia la derecha según su coordenada]\n");
                printf("\nIntroduzca la primera coordenada del portaviones 1: ");
                scanf(" %c%d", &d->porta1x, &d->porta1y);

                d->porta1x = toupper(d->porta1x);
                ///////////////////////////////////////VERIFICADORES

                if (d->porta1x == 'A' || d->porta1x == 'B' || d->porta1x == 'C' || d->porta1x == 'D' || d->porta1x == 'E' || d->porta1x == 'F' || d->porta1x == 'G' || d->porta1x == 'H')
                {
                    if (d->porta1y > 0 && d->porta1y <= 8)
                    {
                        if (d->porta1x == 'A')
                        {
                            d->porta1x = 0;
                            impport1 = 65;
                        }
                        else if (d->porta1x == 'B')
                        {
                            d->porta1x = 1;
                            impport1 = 66;
                        }
                        else if (d->porta1x == 'C')
                        {
                            d->porta1x = 2;
                            impport1 = 67;
                        }
                        else if (d->porta1x == 'D')
                        {
                            d->porta1x = 3;
                            impport1 = 68;
                        }
                        else if (d->porta1x == 'E')
                        {
                            d->porta1x = 4;
                            impport1 = 69;
                        }
                        else if (d->porta1x == 'F')
                        {
                            d->porta1x = 5;
                            impport1 = 70;
                        }
                        else if (d->porta1x == 'G')
                        {
                            d->porta1x = 6;
                            impport1 = 71;
                        }
                        else if (d->porta1x == 'H')
                        {
                            d->porta1x = 7;
                            impport1 = 72;
                        }
                        for (i = 0; i < 8; i++)
                        {
                            for (j = 0; j < 8; j++)
                            {
                                if ((/*cen*/ tablero2[d->porta1x][d->porta1y - 1] == 1 || (/*der1*/ tablero2[d->porta1x][d->porta1y] == 1 && /*der2*/ tablero2[d->porta1x][d->porta1y + 1] == 1 && /*der3*/ tablero2[d->porta1x][d->porta1y + 2] == 1 && /*abajo1*/ tablero2[d->porta1x + 1][d->porta1y - 1] == 1 && /*abajo2*/ tablero2[d->porta1x + 2][d->porta1y - 1] == 1) && /*abajo3*/ tablero2[d->porta1x + 3][d->porta1y - 1] == 1) || ((d->porta1x >= 5) && (d->porta1y - 1 >= 5)))
                                {
                                    verificador = 0;
                                }
                                else
                                    verificador = 1;
                            }
                        }
                    }
                    else
                        verificador = 0;
                }
                else
                {
                    verificador = 0;
                }
                while (verificador == 0)
                {
                    printf("Vaya! parece que esta coordenada no es válida, inténtalo denuevo: ");
                    scanf(" %c%d", &d->porta1x, &d->porta1y);
                    d->porta1x = toupper(d->porta1x);
                    if (d->porta1x == 'A' || d->porta1x == 'B' || d->porta1x == 'C' || d->porta1x == 'D' || d->porta1x == 'E' || d->porta1x == 'F' || d->porta1x == 'G' || d->porta1x == 'H')
                    {
                        if (d->porta1y > 0 && d->porta1y <= 5)
                        {
                            if (d->porta1x == 'A')
                            {
                                d->porta1x = 0;
                                impport1 = 65;
                            }
                            else if (d->porta1x == 'B')
                            {
                                d->porta1x = 1;
                                impport1 = 66;
                            }
                            else if (d->porta1x == 'C')
                            {
                                d->porta1x = 2;
                                impport1 = 67;
                            }
                            else if (d->porta1x == 'D')
                            {
                                d->porta1x = 3;
                                impport1 = 68;
                            }
                            else if (d->porta1x == 'E')
                            {
                                d->porta1x = 4;
                                impport1 = 69;
                            }
                            else if (d->porta1x == 'F')
                            {
                                d->porta1x = 5;
                                impport1 = 70;
                            }
                            else if (d->porta1x == 'G')
                            {
                                d->porta1x = 6;
                                impport1 = 71;
                            }
                            else if (d->porta1x == 'H')
                            {
                                d->porta1x = 7;
                                impport1 = 72;
                            }
                            for (i = 0; i < 8; i++)
                            {
                                for (j = 0; j < 8; j++)
                                {
                                    if ((/*cen*/ tablero2[d->porta1x][d->porta1y - 1] == 1 || (/*der1*/ tablero2[d->porta1x][d->porta1y] == 1 && /*der2*/ tablero2[d->porta1x][d->porta1y + 1] == 1 && /*der3*/ tablero2[d->porta1x][d->porta1y + 2] == 1 && /*abajo1*/ tablero2[d->porta1x + 1][d->porta1y - 1] == 1 && /*abajo2*/ tablero2[d->porta1x + 2][d->porta1y - 1] == 1) && /*abajo3*/ tablero2[d->porta1x + 3][d->porta1y - 1] == 1) || ((d->porta1x >= 5) && (d->porta1y - 1 >= 5)))
                                    {
                                        verificador = 0;
                                    }
                                    else
                                        verificador = 1;
                                }
                            }
                        }
                        else
                            verificador = 0;
                    }
                    else
                    {
                        verificador = 0;
                    }
                }
                printf("[H]Horizontal\n[V]Vertical\n");
                d->orientporta1 = getch();
                d->orientporta1 = toupper(d->orientporta1); //funcion para ignorar minusculas

                if (d->orientporta1 == 'H')
                {
                    if (/*der1*/ tablero2[d->porta1x][d->porta1y + 1] == 1 && /*der2*/ tablero2[d->porta1x][d->porta1y + 2] == 1 && /*der3*/ tablero2[d->porta1x][d->porta1y + 3] == 1 || d->porta1y + 4 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else if (d->orientporta1 == 'V')
                {
                    if (/*abajo1*/ tablero2[d->porta1x + 1][d->porta1y] == 1 && /*abajo2*/ tablero2[d->porta1x + 2][d->porta1y - 1] == 1 && /*abajo3*/ tablero2[d->porta1x + 3][d->porta1y - 1] == 1 || d->porta1x + 4 > 8)
                    {
                        verificador = 0;
                    }
                    else
                        verificador = 1;
                }
                else
                {
                    verificador = 0;
                }
                while (verificador == 0)
                {
                    printf("\n¡Opción Inválida!");
                    printf("\n[H]Horizontal\n[V]Vertical\n");
                    d->orientporta1 = getch();
                    d->orientporta1 = toupper(d->orientporta1);

                    if (d->orientporta1 == 'H')
                    {
                        if (/*der1*/ tablero2[d->porta1x][d->porta1y + 1] == 1 && /*der2*/ tablero2[d->porta1x][d->porta1y + 2] == 1 && /*der3*/ tablero2[d->porta1x][d->porta1y + 3] == 1 || d->porta1y + 4 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else if (d->orientporta1 == 'V')
                    {
                        if (/*abajo1*/ tablero2[d->porta1x + 1][d->porta1y] == 1 && /*abajo2*/ tablero2[d->porta1x + 2][d->porta1y - 1] == 1 && /*abajo3*/ tablero2[d->porta1x + 3][d->porta1y - 1] == 1 || d->porta1x + 4 > 8)
                        {
                            verificador = 0;
                        }
                        else
                            verificador = 1;
                    }
                    else
                    {
                        verificador = 0;
                    }
                }
                d->porta1y -= 1;
                ////////////////////////////////////////////////////////////////////////////////////////

                system("cls");
                //////////////////////////////////////////////////////////////TABLERO
                printf("                TABLERO DE POSICIONAMIENTO\n\n");
                printf("\t\t  1  2  3  4  5  6  7  8");
                letras = 65;
                for (i = 0; i < 8; i++)
                {
                    printf("\n\t\t");
                    printf("%c", letras);
                    letras = letras + 1;
                    for (j = 0; j < 8; j++)
                    {
                        if (d->porta1y == j && d->porta1x == i && d->orientporta1 == 'H' && j <= 5)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i][j + 1] = 1;
                            tablero2[i][j + 2] = 1;
                            tablero2[i][j + 3] = 1;
                            d->p1porta1 = d->porta1y;
                            d->p2porta1 = d->porta1y + 1;
                            d->p3porta1 = d->porta1y + 2;
                            d->p4porta1 = d->porta1y + 3;
                        }
                        else if (d->porta1y == j && d->porta1x == i && d->orientporta1 == 'V' && i <= 5)
                        {
                            tablero2[i][j] = 1;
                            tablero2[i + 1][j] = 1;
                            tablero2[i + 2][j] = 1;
                            tablero2[i + 3][j] = 1;
                            d->p1porta1 = d->porta1y;
                            d->p2porta1 = d->porta1y;
                            d->p3porta1 = d->porta1y;
                            d->p4porta1 = d->porta1y;
                        }
                        if (tablero2[i][j] == 1)
                        {
                            printf("|%c|", asterisco);
                        }
                        else
                            printf("|-|");
                    }
                    if (i == 3)
                    {
                        printf("         J2. [%s]", strupr(jugador2));
                    }
                }
                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                ///////////////////////////////////////////////////////////////////////////////////
                if (d->orientporta1 == 'H')
                {
                    printf("\nPortaviones poscicionado en horizontal, en las coordenadas [%c,%d], [%c,%d], [%c,%d] y [%c,%d]\n ", impport1, d->p1porta1 + 1, impport1, d->p2porta1 + 1, impport1, d->p3porta1 + 1, impport1, d->p4porta1 + 1);
                }
                else if (d->orientporta1 == 'V')
                {
                    printf("\n Portaviones poscicionado en vertical, en las coordenadas [%c,%d], [%c,%d], [%c,%d] y [%c,%d]\n", impport1, d->p1porta1 + 1, impport1 + 1, d->p2porta1 + 1, impport1 + 2, d->p3porta1 + 1, impport1 + 3, d->p4porta1 + 1);
                }
                contaportas = contaportas - 1;
                printf("\nGuardando datos...");
                Sleep(4000);
            }
            else
            {
                printf("\n\nAgotaste tu cantidad de Portaviones!");
                Sleep(2000);
            }
            system("cls");
            //////////////////////////////////////////////////////////////TABLERO
            printf("                TABLERO DE POSICIONAMIENTO\n\n");
            printf("\t\t  1  2  3  4  5  6  7  8");
            letras = 65;
            for (i = 0; i < 8; i++)
            {
                printf("\n\t\t");
                printf("%c", letras);
                letras = letras + 1;
                for (j = 0; j < 8; j++)
                {

                    if (d->porta1y == j && d->porta1x == i && d->orientporta1 == 'H' && j <= 5)
                    {
                        tablero2[i][j] = 1;
                        tablero2[i][j + 1] = 1;
                        tablero2[i][j + 2] = 1;
                        tablero2[i][j + 3] = 1;
                        d->p1porta1 = d->porta1y;
                        d->p2porta1 = d->porta1y + 1;
                        d->p3porta1 = d->porta1y + 2;
                        d->p4porta1 = d->porta1y + 3;
                    }
                    else if (d->porta1y == j && d->porta1x == i && d->orientporta1 == 'V' && i <= 5)
                    {
                        tablero2[i][j] = 1;
                        tablero2[i + 1][j] = 1;
                        tablero2[i + 2][j] = 1;
                        tablero2[i + 3][j] = 1;
                        d->p1porta1 = d->porta1y;
                        d->p2porta1 = d->porta1y;
                        d->p3porta1 = d->porta1y;
                        d->p4porta1 = d->porta1y;
                    }
                    if (tablero2[i][j] == 1)
                    {
                        printf("|%c|", asterisco);
                    }
                    else
                        printf("|-|");
                }
                if (i == 3)
                {
                    printf("         J2. [%s]", strupr(jugador2)); //QUIERO IMPRIMIR EL NOMBRE DEL JUGADOR 1/
                }
            }
            printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
            ///////////////////////////////////////////////////////////////////////////////////
            break;
        }
    } while (contabarcos > 0 || contabuques > 0 || contaportas > 0); //CUANDO EL JUGADOR YA POSICIONÓ TODOS SUS BARCOS
}

struct atacar
{
    int atqy;
    char atqx;
};

struct atacar2
{
    int atqy;
    char atqx;
};

int main()
{
    int regresar, op, i, j, verificador, navesj1 = 14, navesj2 = 14;
    char letras, jugador1[20], jugador2[20], opcion, opt, opt2;
    struct barcos b1;
    struct buques c2;
    struct Portaviones d3;
    struct barcos2 b2;
    struct buques2 c3;
    struct contadores e4;
    struct contadores2 e5;
    struct Portaviones2 d4;
    struct atacar a;
    struct atacar2 a2;

    //TABLA DE SIMBOLOS
    int fallo = 31;
    int asterisco = 42;
    int carita = 1;
    int tabler1[8][8], tabler2[8][8];
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_CYAN "\x1b[96m"
#define ANSI_RED "\x1b[31m"
#define ANSI_RESET "\x1b[0m"

    setlocale(LC_ALL, "spanish"); //Impresión de caracteres especiales del idioma español

    printf("\n\n\n\n[SE RECOMIENDA JUGAR EN PANTALLA COMPLETA]");
    Sleep(3000);
    printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tCARGANDO...");
    Sleep(4000);
    system("cls");
    do
    {
        titulo();
        printf("\n");
        printf(ANSI_RESET "\n  --    .-  -.\\                                                        \n");
        printf(ANSI_RESET "     ) (    )\\                              \t\t" ANSI_RED "1." ANSI_CYAN " Jugar"
                          "\n");
        printf(ANSI_RESET "     (   ) (\\                                                          \n");
        printf(ANSI_RESET "     /     )\\                                                          \n");
        printf(ANSI_RESET "    (_    _)                     0_,-.__     \t\t" ANSI_RED "2." ANSI_CYAN " Instrucciones                        \n");
        printf(ANSI_RESET "      (_  )_                     |_.-._/                              \n");
        printf(ANSI_RESET "       (    )                    |_--..\\                              \n");
        printf(ANSI_RESET "        (__)                     |__--_/     \t\t" ANSI_RED "3." ANSI_CYAN " Salir                       \n");
        printf(ANSI_RESET "     |''   ``\\                   |                                     \n");
        printf("     |        \\                  |      /b.\\                           \n");
        printf("     |         \\ ,,,---===?A`\\  |  ,==y'                              \n");
        printf("   ___,,,,,---==\\         |M] \\ | ;|\ |>                              \n");
        printf("           _   _  \\   ____,|H,,---=="
               ""
               "bno,                           \n");
        printf("    o  O  (_) (_)  \\ /          _     AWAW/                           \n");
        printf("                    /         _(+)_  dMM/                             \n");
        printf("      \@_,,,,,,---=='   \\      \\| /  MW/                              \n");
        printf("--'''''                         ===  d/                                \n");
        printf("                                     /                                 \n");
        printf("                                    ,'__________________________       \n");
        printf("   \\     \\     \\      \\                ,/~~~~~~~~~~~~~~~~~~~~~~~~~~~       \n");
        printf("                         _____    ,'  ~~~   .-"
               "-.~~~~~~  .-"
               "-.       \n");
        printf("      .-"
               "-.           / ==---   /`-._ ..-'      -.__..-'              \n");
        printf("            `-.__..-' =====\\\\\\ V/  .---\\.                           \n");
        printf(" ___,                 ~~~~~~~~~~~~, _',--/_.\\  .-"
               "-.                  \n");
        printf("                            .-"
               "-.___` --  \\|         -.__..-          \n");
        opcion = getch();

        switch (opcion)
        {
        case '1':
            op = 1;
            system("cls");
            printf("\nIntroduzca el nombre del [Jugador 1]: ");
            scanf("%s", &jugador1);
            system("color 0B");
            tableroJugador1(jugador1, tabler1, &b1, &c2, &d3, &e4);
            system("cls");
            printf("Completado con éxito");
            Sleep(2000);
            system("cls");
            system("color 07");
            printf("\nIntroduzca el nombre del [Jugador 2]: ");
            scanf("%s", &jugador2);
            system("color 0C");
            tableroJugador2(jugador2, tabler2, &b2, &c3, &d4, &e5);
            system("cls");
            printf("Completado con éxito");
            Sleep(2000);
            system("cls");
            system("color 07");
            printf("\nES MOMENTO DE ATACAR!");
            Sleep(1000);
            do
            {
                system("cls");
                system("color 0B");
                printf("TURNO DE [%s]", strupr(jugador1));
                Sleep(3000);
                system("cls");
                printf("\t\t      MONITOR ENEMIGO\n");
                printf("\t\t  1  2  3  4  5  6  7  8");
                letras = 65;
                for (i = 0; i < 8; i++)
                {
                    printf("\n\t\t");
                    printf("%c", letras);
                    letras = letras + 1;
                    for (j = 0; j < 8; j++)
                    {
                        if (tabler2[i][j] == 'X')
                        {
                            printf("|%c|", carita);
                        }
                        else if (tabler2[i][j] == 'F')
                        {
                            printf("|%c|", fallo);
                        }
                        else
                        {
                            printf("|-|");
                        }
                    }
                    if (i == 3)
                    {
                        printf("         ENEMIGO");
                    }
                }
                printf("\n\n\t  --------------------------------------\n\n");
                printf("\t\t  1  2  3  4  5  6  7  8");
                letras = 65;
                for (i = 0; i < 8; i++)
                {
                    printf("\n\t\t");
                    printf("%c", letras);
                    letras = letras + 1;
                    for (j = 0; j < 8; j++)
                    {
                        if (tabler1[i][j] == 1)
                        {
                            printf("|%c|", asterisco);
                        }
                        else if (tabler1[i][j] == 'X')
                        {
                            printf("|%c|", carita);
                        }
                        else if (tabler1[i][j] == 'F')
                        {
                            printf("|%c|", fallo);
                        }
                        else
                        {
                            printf("|-|");
                        }
                    }
                    if (i == 3)
                    {
                        printf("         J1. [%s]", strupr(jugador1));
                    }
                }
                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                ///////////////////////////////////////////////////////////////////////////////////

                printf("\n\nIntroduzca la coordenada a atacar: "); /////ATACAR TURNO JUGADOR 1
                scanf(" %c%d", &a.atqx, &a.atqy);
                a.atqx = toupper(a.atqx);
                if (a.atqx == 'A')
                {
                    a.atqx = 0;
                }
                else if (a.atqx == 'B')
                {
                    a.atqx = 1;
                }
                else if (a.atqx == 'C')
                {
                    a.atqx = 2;
                }
                else if (a.atqx == 'D')
                {
                    a.atqx = 3;
                }
                else if (a.atqx == 'E')
                {
                    a.atqx = 4;
                }
                else if (a.atqx == 'F')
                {
                    a.atqx = 5;
                }
                else if (a.atqx == 'G')
                {
                    a.atqx = 6;
                }
                else if (a.atqx == 'H')
                {
                    a.atqx = 7;
                }
                a.atqy = a.atqy - 1;

                if (tabler2[a.atqx][a.atqy] == 1) //si acierta
                {
                    tabler2[a.atqx][a.atqy] = 'X';
                    navesj2 -= 1;
                    system("cls");
                    printf("\t\t      MONITOR ENEMIGO\n");
                    printf("\t\t  1  2  3  4  5  6  7  8");
                    letras = 65;
                    for (i = 0; i < 8; i++)
                    {
                        printf("\n\t\t");
                        printf("%c", letras);
                        letras = letras + 1;
                        for (j = 0; j < 8; j++)
                        {
                            if (tabler2[i][j] == 'X')
                            {
                                printf("|%c|", carita);
                            }
                            else if (tabler2[i][j] == 'F')
                            {
                                printf("|%c|", fallo);
                            }
                            else
                            {
                                printf("|-|");
                            }
                        }
                        if (i == 3)
                        {
                            printf("         ENEMIGO");
                        }
                    }
                    printf("\n\n\t  --------------------------------------\n\n");
                    printf("\t\t  1  2  3  4  5  6  7  8");
                    letras = 65;
                    for (i = 0; i < 8; i++)
                    {
                        printf("\n\t\t");
                        printf("%c", letras);
                        letras = letras + 1;
                        for (j = 0; j < 8; j++)
                        {
                            if (tabler1[i][j] == 1)
                            {
                                printf("|%c|", asterisco);
                            }
                            else if (tabler1[i][j] == 'X')
                            {
                                printf("|%c|", carita);
                            }
                            else if (tabler1[i][j] == 'F')
                            {
                                printf("|%c|", fallo);
                            }
                            else
                            {
                                printf("|-|");
                            }
                        }
                        if (i == 3)
                        {
                            printf("         J1. [%s]", strupr(jugador1)); //NOMBRE DEL JUGADOR 1
                        }
                    }
                    printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                    ///////////////////////////////////////////////////////////////////////////////////
                    printf("\nLE DISTE A UNA NAVE!\n");
                    Sleep(2000);
                }
                else if (tabler2[a.atqx][a.atqy] == 0) //SI FALLA
                {
                    tabler2[a.atqx][a.atqy] = 'F';
                    system("cls");
                    printf("\t\t      MONITOR ENEMIGO\n");
                    printf("\t\t  1  2  3  4  5  6  7  8");
                    letras = 65;
                    for (i = 0; i < 8; i++)
                    {
                        printf("\n\t\t");
                        printf("%c", letras);
                        letras = letras + 1;
                        for (j = 0; j < 8; j++)
                        {
                            if (tabler2[i][j] == 'X')
                            {
                                printf("|%c|", carita);
                            }
                            else if (tabler2[i][j] == 'F')
                            {
                                printf("|%c|", fallo);
                            }
                            else
                            {
                                printf("|-|");
                            }
                        }
                        if (i == 3)
                        {
                            printf("         ENEMIGO");
                        }
                    }
                    printf("\n\n\t  --------------------------------------\n\n");
                    printf("\t\t  1  2  3  4  5  6  7  8");
                    letras = 65;
                    for (i = 0; i < 8; i++)
                    {
                        printf("\n\t\t");
                        printf("%c", letras);
                        letras = letras + 1;
                        for (j = 0; j < 8; j++)
                        {
                            if (tabler1[i][j] == 1)
                            {
                                printf("|%c|", asterisco);
                            }
                            else if (tabler1[i][j] == 'X')
                            {
                                printf("|%c|", carita);
                            }
                            else if (tabler1[i][j] == 'F')
                            {
                                printf("|%c|", fallo);
                            }
                            else
                            {
                                printf("|-|");
                            }
                        }
                        if (i == 3)
                        {
                            printf("         J1. [%s]", strupr(jugador1)); //NOMBRE DEL JUGADOR 1
                        }
                    }
                    printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                    ///////////////////////////////////////////////////////////////////////////////////
                    printf("\nTIRO FALLIDO!\n");
                    Sleep(2000);
                }
                else if (tabler2[a.atqx][a.atqy] == 'F') ////SI LA POSICIÓN YA ESTÁ TOMADA
                {
                    do
                    {
                        printf("Vaya!, parece que ya atacaste esta coordenada, introduce otra: ");
                        scanf(" %c%d", &a.atqx, &a.atqy);
                        a.atqx = toupper(a.atqx);
                        if (a.atqx == 'A')
                        {
                            a.atqx = 0;
                        }
                        else if (a.atqx == 'B')
                        {
                            a.atqx = 1;
                        }
                        else if (a.atqx == 'C')
                        {
                            a.atqx = 2;
                        }
                        else if (a.atqx == 'D')
                        {
                            a.atqx = 3;
                        }
                        else if (a.atqx == 'E')
                        {
                            a.atqx = 4;
                        }
                        else if (a.atqx == 'F')
                        {
                            a.atqx = 5;
                        }
                        else if (a.atqx == 'G')
                        {
                            a.atqx = 6;
                        }
                        else if (a.atqx == 'H')
                        {
                            a.atqx = 7;
                        }
                        a.atqy = a.atqy - 1;
                        if (tabler2[a.atqx][a.atqy] == 1) //despues si acierta
                        {
                            tabler2[a.atqx][a.atqy] = 'X';
                            verificador = 1;
                            navesj2 -= 1;
                            system("cls");
                            printf("\t\t      MONITOR ENEMIGO\n");
                            printf("\t\t  1  2  3  4  5  6  7  8");
                            letras = 65;
                            for (i = 0; i < 8; i++)
                            {
                                printf("\n\t\t");
                                printf("%c", letras);
                                letras = letras + 1;
                                for (j = 0; j < 8; j++)
                                {
                                    if (tabler2[i][j] == 'X')
                                    {
                                        printf("|%c|", carita);
                                    }
                                    else if (tabler2[i][j] == 'F')
                                    {
                                        printf("|%c|", fallo);
                                    }
                                    else
                                    {
                                        printf("|-|");
                                    }
                                }
                                if (i == 3)
                                {
                                    printf("         ENEMIGO");
                                }
                            }
                            printf("\n\n\t  --------------------------------------\n\n");
                            printf("\t\t  1  2  3  4  5  6  7  8");
                            letras = 65;
                            for (i = 0; i < 8; i++)
                            {
                                printf("\n\t\t");
                                printf("%c", letras);
                                letras = letras + 1;
                                for (j = 0; j < 8; j++)
                                {
                                    if (tabler1[i][j] == 1)
                                    {
                                        printf("|%c|", asterisco);
                                    }
                                    else if (tabler1[i][j] == 'X')
                                    {
                                        printf("|%c|", carita);
                                    }
                                    else if (tabler1[i][j] == 'F')
                                    {
                                        printf("|%c|", fallo);
                                    }
                                    else
                                    {
                                        printf("|-|");
                                    }
                                }
                                if (i == 3)
                                {
                                    printf("         J1. [%s]", strupr(jugador1)); //NOMBRE DEL JUGADOR 1
                                }
                            }
                            printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                            ///////////////////////////////////////////////////////////////////////////////////
                            printf("\nLE DISTE A UNA NAVE!\n");
                            Sleep(2000);
                        }
                        else if (tabler2[a.atqx][a.atqy] == 0) //despues si falla
                        {
                            tabler2[a.atqx][a.atqy] = 'F';
                            verificador = 1;
                            system("cls");
                            printf("\t\t      MONITOR ENEMIGO\n");
                            printf("\t\t  1  2  3  4  5  6  7  8");
                            letras = 65;
                            for (i = 0; i < 8; i++)
                            {
                                printf("\n\t\t");
                                printf("%c", letras);
                                letras = letras + 1;
                                for (j = 0; j < 8; j++)
                                {
                                    if (tabler2[i][j] == 'X')
                                    {
                                        printf("|%c|", carita);
                                    }
                                    else if (tabler2[i][j] == 'F')
                                    {
                                        printf("|%c|", fallo);
                                    }
                                    else
                                    {
                                        printf("|-|");
                                    }
                                }
                                if (i == 3)
                                {
                                    printf("         ENEMIGO");
                                }
                            }
                            printf("\n\n\t  --------------------------------------\n\n");
                            printf("\t\t  1  2  3  4  5  6  7  8");
                            letras = 65;
                            for (i = 0; i < 8; i++)
                            {
                                printf("\n\t\t");
                                printf("%c", letras);
                                letras = letras + 1;
                                for (j = 0; j < 8; j++)
                                {
                                    if (tabler1[i][j] == 1)
                                    {
                                        printf("|%c|", asterisco);
                                    }
                                    else if (tabler1[i][j] == 'X')
                                    {
                                        printf("|%c|", carita);
                                    }
                                    else if (tabler1[i][j] == 'F')
                                    {
                                        printf("|%c|", fallo);
                                    }
                                    else
                                    {
                                        printf("|-|");
                                    }
                                }
                                if (i == 3)
                                {
                                    printf("         J1. [%s]", strupr(jugador1)); //NOMBRE DEL JUGADOR 1
                                }
                            }
                            printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                            ///////////////////////////////////////////////////////////////////////////////////
                            printf("\nTIRO FALLIDO!\n");
                            Sleep(2000);
                        }
                        else if (tabler2[a.atqx][a.atqy] == 'F')
                        {
                            verificador = 0;
                        }
                        else if (tabler2[a.atqx][a.atqy] == 'X')
                        {
                            verificador = 0;
                        }
                    } while (verificador == 0);
                }
                else if (tabler2[a.atqx][a.atqy] == 'X') //si ya acertó antes
                {
                    do
                    {
                        printf("Vaya!, parece que ya atacaste esta coordenada, introduce otra: ");
                        scanf(" %c%d", &a.atqx, &a.atqy);
                        a.atqx = toupper(a.atqx);
                        if (a.atqx == 'A')
                        {
                            a.atqx = 0;
                        }
                        else if (a.atqx == 'B')
                        {
                            a.atqx = 1;
                        }
                        else if (a.atqx == 'C')
                        {
                            a.atqx = 2;
                        }
                        else if (a.atqx == 'D')
                        {
                            a.atqx = 3;
                        }
                        else if (a.atqx == 'E')
                        {
                            a.atqx = 4;
                        }
                        else if (a.atqx == 'F')
                        {
                            a.atqx = 5;
                        }
                        else if (a.atqx == 'G')
                        {
                            a.atqx = 6;
                        }
                        else if (a.atqx == 'H')
                        {
                            a.atqx = 7;
                        }
                        a.atqy = a.atqy - 1;
                        if (tabler2[a.atqx][a.atqy] == 1)
                        {
                            tabler2[a.atqx][a.atqy] = 'X';
                            verificador = 1;
                            navesj2 -= 1;
                            system("cls");
                            printf("\t\t      MONITOR ENEMIGO\n");
                            printf("\t\t  1  2  3  4  5  6  7  8");
                            letras = 65;
                            for (i = 0; i < 8; i++)
                            {
                                printf("\n\t\t");
                                printf("%c", letras);
                                letras = letras + 1;
                                for (j = 0; j < 8; j++)
                                {
                                    if (tabler2[i][j] == 'X')
                                    {
                                        printf("|%c|", carita);
                                    }
                                    else if (tabler2[i][j] == 'F')
                                    {
                                        printf("|%c|", fallo);
                                    }
                                    else
                                    {
                                        printf("|-|");
                                    }
                                }
                                if (i == 3)
                                {
                                    printf("         ENEMIGO");
                                }
                            }
                            printf("\n\n\t  --------------------------------------\n\n");
                            printf("\t\t  1  2  3  4  5  6  7  8");
                            letras = 65;
                            for (i = 0; i < 8; i++)
                            {
                                printf("\n\t\t");
                                printf("%c", letras);
                                letras = letras + 1;
                                for (j = 0; j < 8; j++)
                                {
                                    if (tabler1[i][j] == 1)
                                    {
                                        printf("|%c|", asterisco);
                                    }
                                    else if (tabler1[i][j] == 'X')
                                    {
                                        printf("|%c|", carita);
                                    }
                                    else if (tabler1[i][j] == 'F')
                                    {
                                        printf("|%c|", fallo);
                                    }
                                    else
                                    {
                                        printf("|-|");
                                    }
                                }
                                if (i == 3)
                                {
                                    printf("         J1. [%s]", strupr(jugador1)); //NOMBRE DEL JUGADOR 1
                                }
                            }
                            printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                            ///////////////////////////////////////////////////////////////////////////////////
                            printf("\nLE DISTE A UNA NAVE!\n");
                            Sleep(2000);
                        }
                        else if (tabler2[a.atqx][a.atqy] == 0) //si despues falla
                        {
                            tabler2[a.atqx][a.atqy] = 'F';
                            verificador = 1;
                            system("cls");
                            printf("\t\t      MONITOR ENEMIGO\n");
                            printf("\t\t  1  2  3  4  5  6  7  8");
                            letras = 65;
                            for (i = 0; i < 8; i++)
                            {
                                printf("\n\t\t");
                                printf("%c", letras);
                                letras = letras + 1;
                                for (j = 0; j < 8; j++)
                                {
                                    if (tabler2[i][j] == 'X')
                                    {
                                        printf("|%c|", carita);
                                    }
                                    else if (tabler2[i][j] == 'F')
                                    {
                                        printf("|%c|", fallo);
                                    }
                                    else
                                    {
                                        printf("|-|");
                                    }
                                }
                                if (i == 3)
                                {
                                    printf("         ENEMIGO");
                                }
                            }
                            printf("\n\n\t  --------------------------------------\n\n");
                            printf("\t\t  1  2  3  4  5  6  7  8");
                            letras = 65;
                            for (i = 0; i < 8; i++)
                            {
                                printf("\n\t\t");
                                printf("%c", letras);
                                letras = letras + 1;
                                for (j = 0; j < 8; j++)
                                {
                                    if (tabler1[i][j] == 1)
                                    {
                                        printf("|%c|", asterisco);
                                    }
                                    else if (tabler1[i][j] == 'X')
                                    {
                                        printf("|%c|", carita);
                                    }
                                    else if (tabler1[i][j] == 'F')
                                    {
                                        printf("|%c|", fallo);
                                    }
                                    else
                                    {
                                        printf("|-|");
                                    }
                                }
                                if (i == 3)
                                {
                                    printf("         J1. [%s]", strupr(jugador1)); //NOMBRE DEL JUGADOR 1
                                }
                            }
                            printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                            ///////////////////////////////////////////////////////////////////////////////////
                            printf("\nTIRO FALLIDO!\n");
                            Sleep(2000);
                        }
                        else if (tabler2[a.atqx][a.atqy] == 'F')
                        {
                            verificador = 0;
                        }
                        else if (tabler2[a.atqx][a.atqy] == 'X')
                        {
                            verificador = 0;
                        }
                    } while (verificador == 0);
                }
                else
                {
                    tabler2[a.atqx][a.atqy] = 'F';
                    system("cls");
                    printf("\t\t      MONITOR ENEMIGO\n");
                    printf("\t\t  1  2  3  4  5  6  7  8");
                    letras = 65;
                    for (i = 0; i < 8; i++)
                    {
                        printf("\n\t\t");
                        printf("%c", letras);
                        letras = letras + 1;
                        for (j = 0; j < 8; j++)
                        {
                            if (tabler2[i][j] == 'X')
                            {
                                printf("|%c|", carita);
                            }
                            else if (tabler2[i][j] == 'F')
                            {
                                printf("|%c|", fallo);
                            }
                            else
                            {
                                printf("|-|");
                            }
                        }
                        if (i == 3)
                        {
                            printf("         ENEMIGO");
                        }
                    }
                    printf("\n\n\t  --------------------------------------\n\n");
                    printf("\t\t  1  2  3  4  5  6  7  8");
                    letras = 65;
                    for (i = 0; i < 8; i++)
                    {
                        printf("\n\t\t");
                        printf("%c", letras);
                        letras = letras + 1;
                        for (j = 0; j < 8; j++)
                        {
                            if (tabler1[i][j] == 1)
                            {
                                printf("|%c|", asterisco);
                            }
                            else if (tabler1[i][j] == 'X')
                            {
                                printf("|%c|", carita);
                            }
                            else if (tabler1[i][j] == 'F')
                            {
                                printf("|%c|", fallo);
                            }
                            else
                            {
                                printf("|-|");
                            }
                        }
                        if (i == 3)
                        {
                            printf("         J1. [%s]", strupr(jugador1)); //NOMBRE DEL JUGADOR 1
                        }
                    }
                    printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                    ///////////////////////////////////////////////////////////////////////////////////
                    printf("\nTIRO FALLIDO!\n");
                    Sleep(2000);
                }

                if (navesj2 > 0) /////////////////////////////////////JUGADOR 2
                {
                    system("cls");
                    system("color 0C");
                    printf("TURNO DE [%s]", strupr(jugador2));
                    Sleep(3000);
                    system("cls");
                    printf("\t\t      MONITOR ENEMIGO\n");
                    printf("\t\t  1  2  3  4  5  6  7  8");
                    letras = 65;
                    for (i = 0; i < 8; i++)
                    {
                        printf("\n\t\t");
                        printf("%c", letras);
                        letras = letras + 1;
                        for (j = 0; j < 8; j++)
                        {
                            if (tabler1[i][j] == 'X')
                            {
                                printf("|%c|", carita);
                            }
                            else if (tabler1[i][j] == 'F')
                            {
                                printf("|%c|", fallo);
                            }
                            else
                            {
                                printf("|-|");
                            }
                        }
                        if (i == 3)
                        {
                            printf("         ENEMIGO");
                        }
                    }
                    printf("\n\n\t  --------------------------------------\n\n");
                    printf("\t\t  1  2  3  4  5  6  7  8");
                    letras = 65;
                    for (i = 0; i < 8; i++)
                    {
                        printf("\n\t\t");
                        printf("%c", letras);
                        letras = letras + 1;
                        for (j = 0; j < 8; j++)
                        {
                            if (tabler2[i][j] == 1)
                            {
                                printf("|%c|", asterisco);
                            }
                            else if (tabler2[i][j] == 'X')
                            {
                                printf("|%c|", carita);
                            }
                            else if (tabler2[i][j] == 'F')
                            {
                                printf("|%c|", fallo);
                            }
                            else
                            {
                                printf("|-|");
                            }
                        }
                        if (i == 3)
                        {
                            printf("         J2. [%s]", strupr(jugador2));
                        }
                    }
                    printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                    ///////////////////////////////////////////////////////////////////////////////////

                    printf("\n\nIntroduzca la coordenada a atacar: "); /////ATACAR TURNO JUGADOR 2
                    scanf(" %c%d", &a2.atqx, &a2.atqy);
                    a2.atqx = toupper(a2.atqx);
                    if (a2.atqx == 'A')
                    {
                        a2.atqx = 0;
                    }
                    else if (a2.atqx == 'B')
                    {
                        a2.atqx = 1;
                    }
                    else if (a2.atqx == 'C')
                    {
                        a2.atqx = 2;
                    }
                    else if (a2.atqx == 'D')
                    {
                        a2.atqx = 3;
                    }
                    else if (a2.atqx == 'E')
                    {
                        a2.atqx = 4;
                    }
                    else if (a2.atqx == 'F')
                    {
                        a2.atqx = 5;
                    }
                    else if (a2.atqx == 'G')
                    {
                        a2.atqx = 6;
                    }
                    else if (a2.atqx == 'H')
                    {
                        a2.atqx = 7;
                    }
                    a2.atqy = a2.atqy - 1;

                    if (tabler1[a2.atqx][a2.atqy] == 1) //si acierta
                    {
                        tabler1[a2.atqx][a2.atqy] = 'X';
                        navesj1 -= 1;
                        system("cls");
                        printf("\t\t      MONITOR ENEMIGO\n");
                        printf("\t\t  1  2  3  4  5  6  7  8");
                        letras = 65;
                        for (i = 0; i < 8; i++)
                        {
                            printf("\n\t\t");
                            printf("%c", letras);
                            letras = letras + 1;
                            for (j = 0; j < 8; j++)
                            {
                                if (tabler1[i][j] == 'X')
                                {
                                    printf("|%c|", carita);
                                }
                                else if (tabler1[i][j] == 'F')
                                {
                                    printf("|%c|", fallo);
                                }
                                else
                                {
                                    printf("|-|");
                                }
                            }
                            if (i == 3)
                            {
                                printf("         ENEMIGO");
                            }
                        }
                        printf("\n\n\t  --------------------------------------\n\n");
                        printf("\t\t  1  2  3  4  5  6  7  8");
                        letras = 65;
                        for (i = 0; i < 8; i++)
                        {
                            printf("\n\t\t");
                            printf("%c", letras);
                            letras = letras + 1;
                            for (j = 0; j < 8; j++)
                            {
                                if (tabler2[i][j] == 1)
                                {
                                    printf("|%c|", asterisco);
                                }
                                else if (tabler2[i][j] == 'X')
                                {
                                    printf("|%c|", carita);
                                }
                                else if (tabler2[i][j] == 'F')
                                {
                                    printf("|%c|", fallo);
                                }
                                else
                                {
                                    printf("|-|");
                                }
                            }
                            if (i == 3)
                            {
                                printf("         J2. [%s]", strupr(jugador2));
                            }
                        }
                        printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                        ///////////////////////////////////////////////////////////////////////////////////
                        printf("\nLE DISTE A UNA NAVE!\n");
                        Sleep(2000);
                    }
                    else if (tabler1[a2.atqx][a2.atqy] == 0) //SI FALLA
                    {
                        tabler1[a2.atqx][a2.atqy] = 'F';
                        system("cls");
                        printf("\t\t      MONITOR ENEMIGO\n");
                        printf("\t\t  1  2  3  4  5  6  7  8");
                        letras = 65;
                        for (i = 0; i < 8; i++)
                        {
                            printf("\n\t\t");
                            printf("%c", letras);
                            letras = letras + 1;
                            for (j = 0; j < 8; j++)
                            {
                                if (tabler1[i][j] == 'X')
                                {
                                    printf("|%c|", carita);
                                }
                                else if (tabler1[i][j] == 'F')
                                {
                                    printf("|%c|", fallo);
                                }
                                else
                                {
                                    printf("|-|");
                                }
                            }
                            if (i == 3)
                            {
                                printf("         ENEMIGO");
                            }
                        }
                        printf("\n\n\t  --------------------------------------\n\n");
                        printf("\t\t  1  2  3  4  5  6  7  8");
                        letras = 65;
                        for (i = 0; i < 8; i++)
                        {
                            printf("\n\t\t");
                            printf("%c", letras);
                            letras = letras + 1;
                            for (j = 0; j < 8; j++)
                            {
                                if (tabler2[i][j] == 1)
                                {
                                    printf("|%c|", asterisco);
                                }
                                else if (tabler2[i][j] == 'X')
                                {
                                    printf("|%c|", carita);
                                }
                                else if (tabler2[i][j] == 'F')
                                {
                                    printf("|%c|", fallo);
                                }
                                else
                                {
                                    printf("|-|");
                                }
                            }
                            if (i == 3)
                            {
                                printf("         J2. [%s]", strupr(jugador2));
                            }
                        }
                        printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                        ///////////////////////////////////////////////////////////////////////////////////
                        printf("\nTIRO FALLIDO!\n");
                        Sleep(2000);
                    }
                    else if (tabler1[a2.atqx][a2.atqy] == 'F') ////SI LA POSICIÓN YA ESTÁ TOMADA
                    {
                        do
                        {
                            printf("Vaya!, parece que ya atacaste esta coordenada, introduce otra: ");
                            scanf(" %c%d", &a2.atqx, &a2.atqy);
                            a2.atqx = toupper(a2.atqx);
                            if (a2.atqx == 'A')
                            {
                                a2.atqx = 0;
                            }
                            else if (a2.atqx == 'B')
                            {
                                a2.atqx = 1;
                            }
                            else if (a2.atqx == 'C')
                            {
                                a2.atqx = 2;
                            }
                            else if (a2.atqx == 'D')
                            {
                                a2.atqx = 3;
                            }
                            else if (a2.atqx == 'E')
                            {
                                a2.atqx = 4;
                            }
                            else if (a2.atqx == 'F')
                            {
                                a2.atqx = 5;
                            }
                            else if (a2.atqx == 'G')
                            {
                                a2.atqx = 6;
                            }
                            else if (a2.atqx == 'H')
                            {
                                a2.atqx = 7;
                            }
                            a2.atqy = a2.atqy - 1;
                            if (tabler1[a2.atqx][a2.atqy] == 1) //despues si acierta
                            {
                                tabler1[a2.atqx][a2.atqy] = 'X';
                                verificador = 1;
                                navesj1 -= 1;
                                system("cls");
                                printf("\t\t      MONITOR ENEMIGO\n");
                                printf("\t\t  1  2  3  4  5  6  7  8");
                                letras = 65;
                                for (i = 0; i < 8; i++)
                                {
                                    printf("\n\t\t");
                                    printf("%c", letras);
                                    letras = letras + 1;
                                    for (j = 0; j < 8; j++)
                                    {
                                        if (tabler1[i][j] == 'X')
                                        {
                                            printf("|%c|", carita);
                                        }
                                        else if (tabler1[i][j] == 'F')
                                        {
                                            printf("|%c|", fallo);
                                        }
                                        else
                                        {
                                            printf("|-|");
                                        }
                                    }
                                    if (i == 3)
                                    {
                                        printf("         ENEMIGO");
                                    }
                                }
                                printf("\n\n\t  --------------------------------------\n\n");
                                printf("\t\t  1  2  3  4  5  6  7  8");
                                letras = 65;
                                for (i = 0; i < 8; i++)
                                {
                                    printf("\n\t\t");
                                    printf("%c", letras);
                                    letras = letras + 1;
                                    for (j = 0; j < 8; j++)
                                    {
                                        if (tabler2[i][j] == 1)
                                        {
                                            printf("|%c|", asterisco);
                                        }
                                        else if (tabler2[i][j] == 'X')
                                        {
                                            printf("|%c|", carita);
                                        }
                                        else if (tabler2[i][j] == 'F')
                                        {
                                            printf("|%c|", fallo);
                                        }
                                        else
                                        {
                                            printf("|-|");
                                        }
                                    }
                                    if (i == 3)
                                    {
                                        printf("         J2. [%s]", strupr(jugador2)); //NOMBRE DEL JUGADOR 2
                                    }
                                }
                                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                                ///////////////////////////////////////////////////////////////////////////////////
                                printf("\nLE DISTE A UNA NAVE!\n");
                                Sleep(2000);
                            }
                            else if (tabler1[a2.atqx][a2.atqy] == 0) //despues si falla
                            {
                                tabler1[a2.atqx][a2.atqy] = 'F';
                                verificador = 1;
                                system("cls");
                                printf("\t\t      MONITOR ENEMIGO\n");
                                printf("\t\t  1  2  3  4  5  6  7  8");
                                letras = 65;
                                for (i = 0; i < 8; i++)
                                {
                                    printf("\n\t\t");
                                    printf("%c", letras);
                                    letras = letras + 1;
                                    for (j = 0; j < 8; j++)
                                    {
                                        if (tabler1[i][j] == 'X')
                                        {
                                            printf("|%c|", carita);
                                        }
                                        else if (tabler1[i][j] == 'F')
                                        {
                                            printf("|%c|", fallo);
                                        }
                                        else
                                        {
                                            printf("|-|");
                                        }
                                    }
                                    if (i == 3)
                                    {
                                        printf("         ENEMIGO");
                                    }
                                }
                                printf("\n\n\t  --------------------------------------\n\n");
                                printf("\t\t  1  2  3  4  5  6  7  8");
                                letras = 65;
                                for (i = 0; i < 8; i++)
                                {
                                    printf("\n\t\t");
                                    printf("%c", letras);
                                    letras = letras + 1;
                                    for (j = 0; j < 8; j++)
                                    {
                                        if (tabler2[i][j] == 1)
                                        {
                                            printf("|%c|", asterisco);
                                        }
                                        else if (tabler2[i][j] == 'X')
                                        {
                                            printf("|%c|", carita);
                                        }
                                        else if (tabler2[i][j] == 'F')
                                        {
                                            printf("|%c|", fallo);
                                        }
                                        else
                                        {
                                            printf("|-|");
                                        }
                                    }
                                    if (i == 3)
                                    {
                                        printf("         J2. [%s]", strupr(jugador2));
                                    }
                                }
                                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                                ///////////////////////////////////////////////////////////////////////////////////
                                printf("\nTIRO FALLIDO!\n");
                                Sleep(2000);
                            }
                            else if (tabler1[a2.atqx][a2.atqy] == 'F')
                            {
                                verificador = 0;
                            }
                            else if (tabler1[a2.atqx][a2.atqy] == 'X')
                            {
                                verificador = 0;
                            }
                        } while (verificador == 0);
                    }
                    else if (tabler1[a2.atqx][a2.atqy] == 'X') //si ya acertó antes
                    {
                        do
                        {
                            printf("Vaya!, parece que ya atacaste esta coordenada, introduce otra: ");
                            scanf(" %c%d", &a2.atqx, &a2.atqy);
                            a2.atqx = toupper(a2.atqx);
                            if (a2.atqx == 'A')
                            {
                                a2.atqx = 0;
                            }
                            else if (a2.atqx == 'B')
                            {
                                a2.atqx = 1;
                            }
                            else if (a2.atqx == 'C')
                            {
                                a2.atqx = 2;
                            }
                            else if (a2.atqx == 'D')
                            {
                                a2.atqx = 3;
                            }
                            else if (a2.atqx == 'E')
                            {
                                a2.atqx = 4;
                            }
                            else if (a2.atqx == 'F')
                            {
                                a2.atqx = 5;
                            }
                            else if (a2.atqx == 'G')
                            {
                                a2.atqx = 6;
                            }
                            else if (a2.atqx == 'H')
                            {
                                a2.atqx = 7;
                            }
                            a2.atqy = a2.atqy - 1;
                            if (tabler1[a2.atqx][a2.atqy] == 1)
                            {
                                tabler1[a2.atqx][a2.atqy] = 'X';
                                verificador = 1;
                                navesj1 -= 1;
                                system("cls");
                                printf("\t\t      MONITOR ENEMIGO\n");
                                printf("\t\t  1  2  3  4  5  6  7  8");
                                letras = 65;
                                for (i = 0; i < 8; i++)
                                {
                                    printf("\n\t\t");
                                    printf("%c", letras);
                                    letras = letras + 1;
                                    for (j = 0; j < 8; j++)
                                    {
                                        if (tabler1[i][j] == 'X')
                                        {
                                            printf("|%c|", carita);
                                        }
                                        else if (tabler1[i][j] == 'F')
                                        {
                                            printf("|%c|", fallo);
                                        }
                                        else
                                        {
                                            printf("|-|");
                                        }
                                    }
                                    if (i == 3)
                                    {
                                        printf("         ENEMIGO");
                                    }
                                }
                                printf("\n\n\t  --------------------------------------\n\n");
                                printf("\t\t  1  2  3  4  5  6  7  8");
                                letras = 65;
                                for (i = 0; i < 8; i++)
                                {
                                    printf("\n\t\t");
                                    printf("%c", letras);
                                    letras = letras + 1;
                                    for (j = 0; j < 8; j++)
                                    {
                                        if (tabler2[i][j] == 1)
                                        {
                                            printf("|%c|", asterisco);
                                        }
                                        else if (tabler2[i][j] == 'X')
                                        {
                                            printf("|%c|", carita);
                                        }
                                        else if (tabler2[i][j] == 'F')
                                        {
                                            printf("|%c|", fallo);
                                        }
                                        else
                                        {
                                            printf("|-|");
                                        }
                                    }
                                    if (i == 3)
                                    {
                                        printf("         J2. [%s]", strupr(jugador2));
                                    }
                                }
                                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                                ///////////////////////////////////////////////////////////////////////////////////
                                printf("\nLE DISTE A UNA NAVE!\n");
                                Sleep(2000);
                            }
                            else if (tabler1[a2.atqx][a2.atqy] == 0) //si despues falla
                            {
                                tabler1[a2.atqx][a2.atqy] = 'F';
                                verificador = 1;
                                system("cls");
                                printf("\t\t      MONITOR ENEMIGO\n");
                                printf("\t\t  1  2  3  4  5  6  7  8");
                                letras = 65;
                                for (i = 0; i < 8; i++)
                                {
                                    printf("\n\t\t");
                                    printf("%c", letras);
                                    letras = letras + 1;
                                    for (j = 0; j < 8; j++)
                                    {
                                        if (tabler1[i][j] == 'X')
                                        {
                                            printf("|%c|", carita);
                                        }
                                        else if (tabler1[i][j] == 'F')
                                        {
                                            printf("|%c|", fallo);
                                        }
                                        else
                                        {
                                            printf("|-|");
                                        }
                                    }
                                    if (i == 3)
                                    {
                                        printf("         ENEMIGO");
                                    }
                                }
                                printf("\n\n\t  --------------------------------------\n\n");
                                printf("\t\t  1  2  3  4  5  6  7  8");
                                letras = 65;
                                for (i = 0; i < 8; i++)
                                {
                                    printf("\n\t\t");
                                    printf("%c", letras);
                                    letras = letras + 1;
                                    for (j = 0; j < 8; j++)
                                    {
                                        if (tabler2[i][j] == 1)
                                        {
                                            printf("|%c|", asterisco);
                                        }
                                        else if (tabler2[i][j] == 'X')
                                        {
                                            printf("|%c|", carita);
                                        }
                                        else if (tabler2[i][j] == 'F')
                                        {
                                            printf("|%c|", fallo);
                                        }
                                        else
                                        {
                                            printf("|-|");
                                        }
                                    }
                                    if (i == 3)
                                    {
                                        printf("         J2. [%s]", strupr(jugador2));
                                    }
                                }
                                printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                                ///////////////////////////////////////////////////////////////////////////////////
                                printf("\nTIRO FALLIDO!\n");
                                Sleep(2000);
                            }
                            else if (tabler1[a2.atqx][a2.atqy] == 'F')
                            {
                                verificador = 0;
                            }
                            else if (tabler1[a2.atqx][a2.atqy] == 'X')
                            {
                                verificador = 0;
                            }
                        } while (verificador == 0);
                    }
                    else
                    {
                        tabler1[a2.atqx][a2.atqy] = 'F';
                        system("cls");
                        printf("\t\t      MONITOR ENEMIGO\n");
                        printf("\t\t  1  2  3  4  5  6  7  8");
                        letras = 65;
                        for (i = 0; i < 8; i++)
                        {
                            printf("\n\t\t");
                            printf("%c", letras);
                            letras = letras + 1;
                            for (j = 0; j < 8; j++)
                            {
                                if (tabler1[i][j] == 'X')
                                {
                                    printf("|%c|", carita);
                                }
                                else if (tabler1[i][j] == 'F')
                                {
                                    printf("|%c|", fallo);
                                }
                                else
                                {
                                    printf("|-|");
                                }
                            }
                            if (i == 3)
                            {
                                printf("         ENEMIGO");
                            }
                        }
                        printf("\n\n\t  --------------------------------------\n\n");
                        printf("\t\t  1  2  3  4  5  6  7  8");
                        letras = 65;
                        for (i = 0; i < 8; i++)
                        {
                            printf("\n\t\t");
                            printf("%c", letras);
                            letras = letras + 1;
                            for (j = 0; j < 8; j++)
                            {
                                if (tabler2[i][j] == 1)
                                {
                                    printf("|%c|", asterisco);
                                }
                                else if (tabler2[i][j] == 'X')
                                {
                                    printf("|%c|", carita);
                                }
                                else if (tabler2[i][j] == 'F')
                                {
                                    printf("|%c|", fallo);
                                }
                                else
                                {
                                    printf("|-|");
                                }
                            }
                            if (i == 3)
                            {
                                printf("         J2. [%s]", strupr(jugador2));
                            }
                        }
                        printf("\n\n          ***************************************\n          %c=NAVES %c=TIRO ACERTADO %c=TIRO FALLIDO\n          ***************************************", asterisco, carita, fallo);
                        ///////////////////////////////////////////////////////////////////////////////////
                        printf("\nTIRO FALLIDO!\n");
                        Sleep(2000);
                    }
                }
            } while (navesj1 > 0 && navesj2 > 0);
            system("cls");
            system("color 06");
            printf("PARECE QUE TENEMOS UN GANADOR!");
            Sleep(2000);
            if (navesj2 < navesj1)
            {
                system("color 0B");
                printf("\nFelicidades %s, ganaste!", strupr(jugador1));
            }
            else if (navesj1 < navesj2)
            {
                system("color 0C");
                printf("\nFelicidades %s, ganaste!", strupr(jugador2));
            }
            Sleep(5000);
            system("cls");
            printf("Desea volver a jugar?\n1. Si\n2. No");
            opt2 = getch();
            switch (opt2)
            {
            case '2':
                system("cls");
                Sleep(1000);
                printf("ESPERAMOS QUE VUELVAS PRONTO!");
                Sleep(2000);
                system("cls");
                exit(1);
                break;

            case '1':
                system("cls");
                break;
            }
            break;

        case '2':
            op = 2;
            system("cls");
            system("color 06");
            printf("\n-----Para este juego los tableros de cada jugador tendran una dimensión de 8 x 8,------\n");
            printf("\n--------se le permitirá a cada jugador ubicar su flota de naves, esta flota-----------\n");
            printf("\n-----está compuesta por 2 barcos de tamaño 2, 2 barcos de tamaño 3 y 1 barco de--------\n");
            printf("\n-----tamaño 4; los barcos pueden colocarse de manera horizontal o vertical, no es------\n");
            printf("\n-----posible colocar las naves de forma diagonal. Se juega por turnos alternados--------\n");
            printf("\n-----entre el jugador 1 y el jugador 2. El juego finaliza cuando uno de los jugadores---\n");
            printf("\n------------------haya hundido toda la flota de barcos de su oponente.------------------\n");
            printf("\n---------------------PULSE CUALQUIER TECLA PARA REGRESAR AL MENU-------------------------\n\n");
            system("pause");
            system("cls");
            system("color 07");
            break;

        case '3':
            system("cls");
            system("color 06");
            printf("Seguro que desea salir del juego?\n1. Si\n2. No");
            opt = getch();
            switch (opt)
            {
            case '1':
                system("cls");
                Sleep(1000);
                printf("ESPERAMOS QUE VUELVAS PRONTO!");
                Sleep(2000);
                system("cls");
                exit(1);
                break;

            case '2':
                system("cls");
                system("color 07");
                break;
            }
            break;

        default:
            printf("\nIntroduzca una opcion valida\n");
            opcion = getch();
            system("cls");
            break;
        }
    } while (opcion != '1' || opt == '2' || opt2 == '1');
    return 0;
}
