/*******************************************************************************
 FileName:     Sequencial de Leds - FATEC SANTO ANDRÉ
 Dependencies: Veja a seção de includes
 Processor:    PIC18F4550
 Compiler:     MPLAB X v3.65 + XC8 1.40
 Company:      FATEC Santo Andre
 Author:       Prof. Edson Kitani
 Date:         17/07/2019
 Software License Agreement: Somente para fins didáticos
 ********************************************************************
 File Description: Este programa gera um sequencial com os 8 Leds da placa. 
                   O programa permite alterar a velocidade de troca dos Leds.
 Change History:
 1.0   17/07/2019  Versão inicial

******************************************************************************/

// Includes do Compilador

#include <p18f4550.h>
#include <stdlib.h>

// Includes do Projeto
#include "Config.h"
#include "displayLCD.h"

#define Enquanto    while   
#define Botao_B1    PORTEbits.RE0
#define Botao_B2    PORTEbits.RE1
#define Botao_B3    PORTEbits.RE2

// Variáveis Gloabais

char vetor_leds = 01;
char i = 1;
int tempo = 500;


// Esta função é usada para gerar um delay programável, cuja base de tempo é de
// 1 ms. Assim, se você colocar delay_ms(500), ele esperará um tempo de 500 ms 
// para seguir o programa.

 void delay_ms(int delaytime)       // Gera delay para o novo compilador
{
  while (--delaytime)
  {
       __delay_ms(1);
  }
}  

int saida(int sequencia)
 {
     LATB = ~(sequencia);
 }

void  incrementa()
{  
    if(Botao_B1 == 0)
    {
        tempo = tempo+100;
        delay_ms(100);
    }
}

void decrementa()
{
    if(Botao_B2 == 0)
    {
        tempo = tempo-100;
        if(tempo <= 0)
        {
            tempo = 100;
        }
                
    }
}

void main(void) 
{
    
    ADCON1 = 0x0D;
    LATB   = 0xFF;
    LATD   = 0X00;
    TRISB  = 0x00;

 // Telas do Display LCD

const unsigned char Texto_0[] = "FATEC STO  ANDRE";
const unsigned char Texto_1[] = "** Sequencial **";    

// Configura LCD e tela de saudação
  
    ConfiguraLCD();
    delay_ms(2);
    PosicaoCursorLCD(1,1);
    EscreveFraseRamLCD(Texto_0);
    PosicaoCursorLCD(2,1);
    EscreveFraseRamLCD(Texto_1);
    DesligaCursor();
    delay_ms(3000); 
    
 while(1)
 {    
    vetor_leds = 0x01;
    Enquanto(vetor_leds > 0)
    {   
// Faz a sequência da direita para esquerda               
      LATB = ~(vetor_leds);  
      vetor_leds = vetor_leds << 1;
      delay_ms(tempo);
      incrementa(tempo);
      decrementa(tempo);
    }
    
    vetor_leds = 0x80;
    Enquanto(vetor_leds > 0)
    {
// Faz a sequência da esquerda para direita      
      LATB = ~(vetor_leds);      
      vetor_leds = vetor_leds >> 1;
      delay_ms(tempo);
      incrementa(tempo);
      decrementa(tempo);
    } 
    
    vetor_leds = 0x01;
    Enquanto(vetor_leds > 0)
    {
// Faz a sequência da esquerda para direita     
      vetor_leds = saida(vetor_leds); 
      vetor_leds = vetor_leds << 1;
      delay_ms(tempo);
      incrementa(tempo);
      decrementa(tempo);
    }    
  }       
}
     
