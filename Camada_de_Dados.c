#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Logica_do_programa.h"
#include "Interface.h"


//DEFINE O ESTADO INICIAL
void casas_inicial(CASA tabi[8][8])
{
    int i, j;
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            if (i==3 && j==4)
            {
                tabi[i][j] = PRETA;
            }
            else
            {
                tabi[i][j] = VAZIO;
            }       
        }
    }  
}

//ESTADO INICIAL
ESTADO *inicializador_estado()
{
    ESTADO *estado = (ESTADO *) malloc(sizeof(ESTADO));
    casas_inicial( estado->tab);
   // estado.jogadas = NULL;
    estado->num_jogadas = 0;
    estado->jogador_atual = 1;

    return estado;
}

//Procura onde se encotra a peca preta
COORDENADA encontra_peca_preta(ESTADO estado)
{
    int i,j;
    COORDENADA coord;

    for (i=0; i<8 ; i++)
    {
        for (j=0; j<8; j++)
        {
            if (estado.tab[i][j])
            {
                coord.linha = i;
                coord.coluna = j;
            }
        }
    }
    return coord;
}

//FUNCAO QUE DEVLOVE O ESTADO DE UMA PECA CONSOANTE AS COORDENADAS DADAS
CASA estado_casa(ESTADO estado, COORDENADA coordenada)
{
    int x = coordenada.linha;
    int y = coordenada.coluna;
    CASA peca = estado.tab[x][y];
    return peca;
}

//FUNCAO QUE VERIFICA SE A JOGADA É POSSIVEL
int verifica_se_e_vizinho(COORDENADA coord_inicial, COORDENADA coord_final)
{
    int x, y, x_, y_, resul=0;

    x = coord_inicial.linha;
    y = coord_inicial.coluna; 
    x_ = coord_final.linha; 
    y_ = coord_final.coluna; 

    if ( (x==x_ && ( (y+1)==y_ || (y-1)==y_ )) || 
          y==y_ && ( (x+1)==x_ || (x-1)==x_ ) )
        resul=1;
    return resul;
}

//Funcao principal que verifica se é possivel executar a jogada
int verifica_jogada(ESTADO *estado,COORDENADA pos_inicial, COORDENADA pos_final)
{
    int resul = 0;
    int x = pos_final.linha;
    int y = pos_final.coluna;
    CASA peca = estado->tab[x][y];

    return ( peca == VAZIO && verifica_se_e_vizinho(pos_inicial, pos_final )  );
}

//FUNCAO QUE VERIFICA SE HA CASAS DISPONIVEIS AO REDOR DA PECA PRETA

//Verificar casa a direita
int verifica_casa_Direita(ESTADO *estado, COORDENADA coord)
{
    int x, y, resul=0;
    x = coord.linha;
    y = coord.coluna;  

    if (x!=7 && estado.tab[x-1][y] == VAZIA )
    {
        resul = 1;
    }
    return resul;
}

//Verificar casa a esquerda
int verifica_casa_Esquerda(ESTADO *estado, COORDENADA coord)
{
    int x, y, resul=0;
    x = coord.linha;
    y = coord.coluna;  

    if (x!=0 && estado.tab[x+1][y] == VAZIA )
    {
        resul = 1;
    }
    return resul;
}

//Verificar casa a acima
int verifica_casa_Acima(ESTADO *estado, COORDENADA coord)
{
    int x, y, resul=0;
    x = coord.linha;
    y = coord.coluna;  

    if (y!=0 && estado.tab[x][y+1] == VAZIA )
    {
        resul = 1;
    }
    return resul;
}

//Verificar casa a baixa
int verifica_casa_Baixo(ESTADO *estado, COORDENADA coord)
{
    int x, y, resul=0;
    x = coord.linha;
    y = coord.coluna;  

    if (y!=7 && estado.tab[x][y-1] == VAZIA )
    {
        resul = 1;
    }
    return resul;
}

//funcao principal
int verificar_casas_disponiveis(ESTADO *estado, COORDENADA coord)
{
    return ( verifica_casa_Direita(*estado, coord) &&  verifica_casa_Esquerda(*estado, coord) &&
             verifica_casa_Baixo(*estado, coord)   &&  verifica_casa_Acima(*estado, coord)   );
}

//Funcao que verifica se a peca prente se encontra na posicao 1 ou 2
int verifica_vencedor(ESTADO estado) 
{
    int r;
    COORDENADA coord = encontra_peca_preta(estado);
    if  ( ( (coord.linha = 7) && (coord.coluna = 0) ) || 
          ( (coord.linha = 0) && (coord.coluna = 7) )  )
        r = 1;
    else 
        r = 0;
    return r;
}

//Funcao principal que verifica se existe vencedor
int verifica_Vitoria(ESTADO *estado,COORDENADA coord)
{
    COORDENADA peca_preta = encontra_peca_preta(estado);
    return ( !verifica_vencedor(estado) && verificar_casas_disponiveis(estado, peca_preta) );
}