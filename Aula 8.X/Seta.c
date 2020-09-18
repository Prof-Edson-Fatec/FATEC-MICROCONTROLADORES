/*******************************************************************************
 FileName:     Pisca_Led - FATEC SANTO ANDRÉ
 Dependencies: Veja a seção de includes
 Processor:    PIC18F4550
 Compiler:     MPLAB X v3.65 + XC8 1.40
 Company:      FATEC Santo Andre
 Author:       Prof. Edson Kitani
 Date:         17/09/2020
 Software License Agreement: Somente para fins didáticos
 *******************************************************************************
 File Description: Este simula uma seta de veículo
 Change History:
 1.0   17/09/2020  Versão inicial
 
*******************************************************************************/

// Includes do Compilador

#include<p18f4550.h>
#include<stdio.h>
#include<stdlib.h>

// Includes do Projeto

#include"Config.h"

//Protótipos das Funções

void delay_ms(unsigned int tempodeatraso);

// Define os apelidos das variáveis do PIC

#define setaEsquerda1     PORTBbits.RB7
#define setaEsquerda2     PORTBbits.RB6
#define setaEsquerda3     PORTBbits.RB5
#define setaEsquerda4     PORTBbits.RB4

#define setaDireita1      PORTBbits.RB0
#define setaDireita2      PORTBbits.RB1
#define setaDireita3      PORTBbits.RB2
#define setaDireita4      PORTBbits.RB3

#define botaoEsquerdo     PORTEbits.RE0
#define botaoDireito      PORTEbits.RE1

/******************************************************************************               
* Funcao:   void main(void)
* Entrada:  Nenhuma (void)
* Saida:    Nenhuma (void)
* Descricao: 
/******************************************************************************/

void main()
{
    ADCON1 = 0x0F;  // Define somente as entradas digitais
    
    TRISB = 0x00000000;   // Define todos os pinos da porta como saída
    TRISE = 0x11111111;   // Define todos os pinos da porta E como entrada
    
    
    while(1)
    {
        if(botaoEsquerdo == 0)
        {
         setaEsquerda1 = 0;
         setaEsquerda2 = 0;
         setaEsquerda3 = 0;
         setaEsquerda4 = 0;
         delay_ms(500);
         setaEsquerda1 = 1;
         setaEsquerda2 = 1;
         setaEsquerda3 = 1;
         setaEsquerda4 = 1;
         delay_ms(500);
         
        }
        
        if(botaoDireito == 0)
        {
         setaDireita1 = 0;
         setaDireita2 = 0;
         setaDireita3 = 0;
         setaDireita4 = 0;
         delay_ms(500);
         setaDireita1 = 1;
         setaDireita2 = 1;
         setaDireita3 = 1;
         setaDireita4 = 1;
         delay_ms(500);
         
        }
        
        
        
    }
    
    
    
    
    
    
    
    
    
    
    
}






/******************************************************************************               
* Funcao:   delay_ms(unsigned int delaytime)
* Entrada:  unsigned int delaytime - recebe valores de 0 a 65536
* Saida:    Nenhuma (void)
* Descricao: Gera um atraso de tempo conforme o valor recebido de delaytime
             O tempo interno é baseado no delay 1 ms. Assim, a cada loop temos o
 *           decremento da variável delaytime, até que ele atinja zero. Exemplo:
 *           se o delyatime = 500 a função terminará e retornará para o programa
 *           principal após 500 ms.
/******************************************************************************/

void delay_ms(unsigned int tempodeatraso)
{
    while(--tempodeatraso)
    {
        __delay_ms(1); //Gera um atraso de 1 ms
    }
}
