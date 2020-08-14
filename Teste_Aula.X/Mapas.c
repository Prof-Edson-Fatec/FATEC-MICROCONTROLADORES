/*******************************************************************************
 FileName:     Mapas - FATEC SANTO ANDR�
 Dependencies: Veja a se��o de includes
 Processor:    PIC18F4550
 Compiler:     MPLAB X v3.65 + XC8 1.40
 Company:      FATEC Santo Andre
 Author:       Prof. Edson Kitani
 Date:         03/07/2020
 Software License Agreement: Somente para fins did�ticos
 ********************************************************************
 File Description: Este programa mostra alguns exemplos de como buscar dados
 *                 em tabelas e Look up tables
 * 
 Change History:
 
 1.0   03/07/2020  Vers�o inicial

******************************************************************************/

// Includes do Compilador

#include <p18f4550.h>
#include <stdlib.h>

// Includes do Projeto

#include "Config.h"
#include "displayLCD.h"

#define Botao_B1    PORTEbits.RE0
#define Botao_B2    PORTEbits.RE1
#define Botao_B3    PORTEbits.RE2

// Vari�veis Globais

unsigned long int tickTime   = 0;     // Contador de tempo incremental
unsigned long int delay100    = 1000; // Comparador de delay de 100 ms
unsigned long int tickCount  = 0;
unsigned long int taxaRep = 10000;
unsigned int dwellTime = 0;

char run = 0;
char borda = 0;
char maux1 = 1;
char maux2 = 0;
char teste = 10;

int incremento = 0;
int decremento = 0;
int start      = 0;

unsigned long int taxa_bt1 = 0;
unsigned long int taxa_bt2 = 0;
unsigned long int rate = 1;
unsigned long int taxaBotao = 10000;

unsigned int RPM = 500;
unsigned long int R_aux = 0;
unsigned int TPS = 0;
unsigned int T_aux = 0;
unsigned int coluna = 0;
unsigned int linha  = 0;


// Esta fun��o � usada para gerar um delay program�vel, cuja base de tempo � de
// 1 ms. Assim, se voc� colocar delay_ms(500), ele esperar� um tempo de 500 ms 
// para seguir o programa.

 void delay_ms(int delaytime)       // Gera delay para o novo compilador
{
  while (--delaytime)
  {
       __delay_ms(1);
  }
}  

//==============================================================================
// Area das Interrup��es
 
void interrupt high_priority Interrupcoes(void) // Define somente as interrup��es de alta prioridade
{
    if(INTCONbits.TMR0IF == 1)
    {
        
        INTCONbits.TMR0IF = 0;      // Reset o flag para a pr�xima interrup��o
        tickTime++;             // Contador de tempo
        tickCount++;
        
        
    TMR0L = 107 + TMR0L;    // Valor do estouro + res�duo para 100us
       
    /* Com 220 a frequ�ncia � de 20,13563 kHz (24,83 us por interrup��o)
     * Com 183 a frequ�ncia � de 9,967474 kHz (50,16 us por interrup��o)
     * Com 107 a frequ�ncia � de 4,992028 kHz (100,2 us por interrup��o)
     */
    }
}
  
//==============================================================================
// �rea das Funcoes

void botao(char bt, unsigned int *valor, char inc_dec, char *mem_aux, unsigned int lmin, unsigned int lmax, long int *taxa)

/*-----------------------------------------------------------------------
  bt = vari�vel que traz o estado do botao. 0 = Pressionado 1 = Solto
  valor = vari�vel a ser incrementado ou decrementado
  inc_dec = vari�vel que define se incrementa ou decrementa 0 = inc 1 = dec
  mem_aux = vari�vel auxiliar para indicar se o bot�o foi solto
  lmin e lmax = limites de valor
--------------------------------------------------------------------------*/
{
    if(bt == 0 && *mem_aux == 0)
		{
			*mem_aux = 1;				  // Mem�ria auxiliar para indicar que o bot�o est� pressionado
			*taxa = tickCount + taxaBotao; // Delay para avaliar repeti��o autom�tica do bot�o
                          
            if(inc_dec == 0)
			{
				*valor = *valor+rate;  
                rate = 1;
                if(*valor > lmax)
				{
					*valor = lmax;
				}
			 
            }
			else
			{
				*valor = *valor -rate;
                rate = 1;
				if(*valor < lmin || *valor > lmax)
				{
					*valor = lmin;
				}
			}
		}
	if(bt == 1 && *mem_aux == 1)
	{	
		*mem_aux = 0;
		taxaBotao = taxaRep;            // Tempo para avaliar ciclo de repeti��o do bot�o
	}		
	if((bt == 0) && (tickCount > *taxa))
	{
		*mem_aux = 0;
		rate = 100;
        taxaBotao = 100;
	}
}

// Converte um n�mero de 8 bits para ponto fixo no display
// Coloca o ponto decimal na posicao definida da esquerda para direita
// Se colocar a vari�vel pontoDecimal maior do que 4 n�o aparece o ponto.
void byte_ascii(unsigned int A, char linha, char coluna, char pontoDecimal)
{

    char i = 2;
	char j = 0;
	char ASCII[3];
    ASCII[0] = 0x30;
	ASCII[1] = 0x30;
	ASCII[2] = 0x30;
    
    PosicaoCursorLCD(linha, coluna);
    
	while (A>=10)      // Separa cada d�gito
		{
			ASCII[i] = A%10 + 0x30;
			A = A/10;
            --i;
		}
    ASCII[i] = A + 0x30;

	while(j<3)
    {
         if(pontoDecimal == j)
            { 
                EscreveCaractereLCD(0x2C);
            }
        EscreveCaractereLCD(ASCII[j]);
		++j;
    }
    
}

// Converte um n�mero de 16 bits para ponto fixo no display
// Coloca o ponto decimal na posicao definida da esquerda para direita
// Se colocar a vari�vel pontoDecimal maior do que 4 n�o aparece o ponto.

void word_ascii(unsigned int A, char linha, char coluna, char pontoDecimal)
{
	char i = 4;
	char j = 0;
    
	unsigned int ASCII[5];
	ASCII[0] = 0x30;
	ASCII[1] = 0x30;
	ASCII[2] = 0x30;	
	ASCII[3] = 0x30;
	ASCII[4] = 0x30;
 
	while (A>=10)
	    {	
            ASCII[i] = A%10 + 0x30;
			A = A/10;
		    --i;
		}
	ASCII[i] = A + 0x30;
    PosicaoCursorLCD(linha, coluna);
	while(j<5)
		{
            if(pontoDecimal == j)
            { 
                EscreveCaractereLCD(0x2C);
            }
            EscreveCaractereLCD(ASCII[j]);
			++j;
		}
}


 
  void main(void) 
{
   
    ADCON1 = 0x0D;   //Define o grupo das portas digitais (veja pag. 19 aula 4)
    LATB   = 0xFF;   //Carrega FF na porta B
    LATD   = 0X00;   //Carrega 00 na porta D
    TRISB  = 0x03;    // Define PB como sa�das e entradas de interrup��o
    TRISE  = 0xFF;    //Define todas os pinos da porta E como entrada
  
// Telas do Display LCD

    const unsigned char Texto_0[] = "FATEC STO  ANDRE";
    const unsigned char Texto_1[] = "Mapas e Tabelas ";
    const unsigned char Texto_2[] = "R=        T=    ";
    const unsigned char Texto_3[] = "AVANCO =        ";
    
    unsigned int tabela[4][10] = {
        {280, 280, 280, 272, 290, 300, 300, 300, 300, 300}, 
        {280, 280, 280, 312, 332, 342, 342, 342, 282, 282},
        {280, 280, 330, 415, 415, 427, 437, 437, 322, 322},
        {287, 300, 322, 357, 370, 370, 437, 460, 322, 322}
    };
    
// Configura Timer 0 (Consulte o Manual do PIC 18F4550 na p�gina 125)
// Lembre-se que o clock � de 48 MHz quando se trabalha com USB
    
    T0CONbits.TMR0ON = 1; // Habilitar o Timer 0;
    T0CONbits.T08BIT = 1; // Habilitar no modo 8 bits
    T0CONbits.T0CS   = 0; // Usa o oscilador interno como clock
    T0CONbits.T0SE   = 0; // Irrelevante na sele��o interna
    T0CONbits.PSA    = 0; // Ativa o Prescaler para dividir o sinal do clock
    T0CONbits.T0PS   = 0b010; // Prescaler divisor por 8
      
// Carrega o valor inicial no registrador baixo do Timer 0

    TMR0L = 107;  // Valor do estouro
        
// Configura a Interrup��o do Timer 0
    
    INTCONbits.TMR0IE    = 1; // Habilita Timer 0 pelo flag de overflow    

// Habilita interrup��es
   
   INTCON2bits.TMR0IP = 1;    // Prioridade alta para Timer 0
   RCONbits.IPEN = 0;         // Habilita n�veis de prioridades
   INTCONbits.PEIE_GIEL = 0;  // Desabilita as interrup��es de baixo n�vel
   INTCONbits.GIE_GIEH  = 1;  // Habilita as interrup��es de alto n�vel

    
//Configura LCD e tela de sauda��o  

    ConfiguraLCD();
    delay_ms(2);
    PosicaoCursorLCD(1,1);
    EscreveFraseRamLCD(Texto_0);
    PosicaoCursorLCD(2,1);
    EscreveFraseRamLCD(Texto_1);
    DesligaCursor();
    delay_ms(3000); 

 // Tela de opera��o
          
        PosicaoCursorLCD(1,1);
        EscreveFraseRamLCD(Texto_2);
        PosicaoCursorLCD(2,1);
        EscreveFraseRamLCD(Texto_3);
        
 
    while(1)
    {
        if(Botao_B3 == 1)
        {
            botao(Botao_B1, &RPM, 0, &maux1, 500, 4000, &taxa_bt1); 		
            botao(Botao_B2, &RPM, 1, &maux2, 500, 4000, &taxa_bt2);
            word_ascii(RPM, 1,4, 5); 			// Coloca o RPM no display
        }
        else
        {
            botao(Botao_B1, &TPS, 0, &maux1, 000, 30, &taxa_bt1); 		
            botao(Botao_B2, &TPS, 1, &maux2, 000, 30, &taxa_bt2);
            byte_ascii(TPS, 1, 13, 4); 			// Coloca o TPS no display
        }    
 
// Interpola RPM e TPS para indexar o mapa
        
        R_aux = RPM/100;
        R_aux = ((418*R_aux - 4*R_aux*R_aux))/1000;
        coluna = R_aux;
        linha  = TPS/10;
        
        word_ascii(tabela[linha][coluna], 2, 10, 4);

    }
    
            
    
    
  }
  