/*******************************************************************************
 FileName:     Pisca_Led - FATEC SANTO ANDRÉ
 Dependencies: Veja a seção de includes
 Processor:    PIC18F4550
 Compiler:     MPLAB X v3.65 + XC8 1.40
 Company:      FATEC Santo Andre
 Author:       Prof. Edson Kitani
 Date:         03/09/2020
 Software License Agreement: Somente para fins didáticos
 *******************************************************************************
 File Description: Este programa gera um pisca pisca numa saída determinada.
 Change History:
 1.0   03/09/2020  Versão inicial
 
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

#define RB7     PORTBbits.RB7



/******************************************************************************               
* Funcao:   void main(void)
* Entrada:  Nenhuma (void)
* Saida:    Nenhuma (void)
* Descricao: 
/******************************************************************************/

void main()
{
    
    ADCON1 = 0x0F;  // Define somente as entradas digitais
    TRISB  = 0x00;  // Define todos os pinos B como saídas
    LATB = 0xFF;
    
    while(1)
    {
        
      RB7 = 1;
      delay_ms(100);
      RB7 = 0;
      delay_ms(100);      
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

