/*
 * LCD_Blio.h
 *
 *  Created on: 4 de jan de 2024
 *      Author: Fagner
 */

#ifndef LCD_BLIO_H_
#define LCD_BLIO_H_

/*Tutorial de uso da biblioteca:

	1. O pino PA4 � usado como controle de contraste do LCD e deve ser conectado ao pino VO(3) do LCD;
	2. Nas defini��es abaixo, escolha a porta GPIO e os pinos que ser�o utilizados no LCD;
	3. Chame a fun��o LCD_Init();
	4. Escreva no display usando a LCD_Write_String(uint8_t linha, uint8_t coluna, char* string);
	5. Opcionalmente, formate uma string com sprintf(char * endere�oString, formato, vari�vel1, vari�vel2, �) e em seguida escreva com LCD_Write_String();
	6. Use a fun��o LCD_Clear() quando desejar limpar o LCD;

	A biblioteca suporta o modo de opera��o de 4 bits
    Precisa de no m�nimo 6 pinos de GPIO, al�m do pino PA4
    Suporta diferentes tamanhos de LCD
    Pode mostrar/esconder o cursor
    Pode habilitar/desabilitar o cursor piscante
    Pode deslocar o conte�do � direita ou � esquerda
    Pula automaticamente para uma nova linha ao atingir o �ltimo caractere
    Strings com \n pula para a o in�cio da pr�xima linha

*/


//Defini��es da porta e dos pinos para o LCD
#define LCD_PORT	GPIOD
#define LCD_RS_PIN	PIN_0
#define LCD_E_PIN	PIN_1
#define LCD_D4_PIN	PIN_2
#define LCD_D5_PIN	PIN_3
#define LCD_D6_PIN	PIN_4
#define LCD_D7_PIN	PIN_5

//Defini��es de vari�veis globais
static uint8_t LCD_LINHAS;	//quantidade de linhas do LCD
static uint8_t LCD_COLUNAS;	//quantidade de colunas (caracteres em cada linha)
static uint8_t current_X;	//coluna atual do cursor
static uint8_t current_Y;	//linha atual do cursor


//Prot�tipos de fun��es de manipula��o do LCD
void LCD_Init(uint8_t linhas, uint8_t colunas);							//inicializa��o do LCD com interface de 4 bits
void LCD_Clear();                 										//limpa o LCD
static void LCD_CMD(uint8_t cmd);										//envia comando para o LCD
static void LCD_DATA(uint8_t Data);										//envia um dado de 4 bits para o LCD
static void LCD_Set_Cursor(uint8_t linha , uint8_t coluna);				//configura a posi��o do cursor no formato (linha,coluna)
static void LCD_Write_Char(char Data);											//escreve um caractere no LCD na posi��o do cursor
void LCD_Write_String(uint8_t linha , uint8_t coluna, char* string);	//escreve uma string no LCD a partir da posi��o do cursor
static void enable_pulse(void);	//pulso no pino enable
void LCD_Display_ON(void);		//liga o LCD
void LCD_Display_OFF(void);		//desliga o LCD
void LCD_Cursor_ON(void);		//liga o cursor
void LCD_Cursor_OFF(void);		//desliga o cursor
void LCD_Blink_ON(void);		//liga o cursor piscante
void LCD_Blink_OFF(void);		//desliga o cursor piscante
void LCD_SHL(void);				//desloca o conte�do do LCD para a esquerda
void LCD_SHR(void);				//desloca o conte�do do LCD para a direita



//****************Fun��es para manipula��o do LCD****************

//Escreve um dado de 4 bits no barramento de dados do LCD
static void LCD_DATA(uint8_t Data)
{
	(Data & (1 << 0)) ? (LCD_PORT->ODR |= (1 << LCD_D4_PIN)) : (LCD_PORT->ODR &= ~(1 << LCD_D4_PIN));
    (Data & (1 << 1)) ? (LCD_PORT->ODR |= (1 << LCD_D5_PIN)) : (LCD_PORT->ODR &= ~(1 << LCD_D5_PIN));
    (Data & (1 << 2)) ? (LCD_PORT->ODR |= (1 << LCD_D6_PIN)) : (LCD_PORT->ODR &= ~(1 << LCD_D6_PIN));
    (Data & (1 << 3)) ? (LCD_PORT->ODR |= (1 << LCD_D7_PIN)) : (LCD_PORT->ODR &= ~(1 << LCD_D7_PIN));
}

//Pulso de enable
static void enable_pulse(void)
{
	LCD_PORT->ODR |= (1 << LCD_E_PIN);
	Delay_us(1);
	LCD_PORT->ODR &= ~(1 << LCD_E_PIN);
	Delay_us(50);		//um comando precisa de mais de 37us para executar
}

//Envia um comando para o LCD
static void LCD_CMD(uint8_t cmd)
{
	LCD_PORT->ODR &= ~(1 << LCD_RS_PIN);	//seleciona o registrador de comando
	LCD_DATA(cmd);						//escreve o comando no barramento
    enable_pulse();							//pulso de enable
}

//Limpa o LCD
void LCD_Clear()
{
    LCD_CMD(0x0);
    LCD_CMD(0x1);
    Delay_ms(3);	//aguarda o comando ser executado
}

//Configura a posi��o do cursor
static void LCD_Set_Cursor(uint8_t linha, uint8_t coluna)
{
	uint8_t line_offsets[] = {0x00, 0x40, 0x14, 0x54};	//offset dos endere�os das linhas do LCD
    uint8_t address,Low_nibble,High_nibble;

    address  = 0x80 + line_offsets[linha-1] + coluna - 1;

    High_nibble = address >> 4;
    Low_nibble  = address & 0x0F;

    LCD_CMD(High_nibble);
    LCD_CMD(Low_nibble);

    //Configura a posi��o atual do cursor
    current_X = coluna;	//linha atual do cursor
    current_Y = linha;	//coluna atual do cursor
}

//Inicializa o LCD
void LCD_Init(uint8_t linhas, uint8_t colunas)
{
	//Configura a quantidade de linhas e colunas do LCD
	LCD_LINHAS = linhas;
	LCD_COLUNAS = colunas;

	//Configura a posi��o inicial do cursor
	current_X = 1;	//coluna inicial do cursor
	current_Y = 1;	//linha inicial do cursor

	//Configura��o dos pinos
	//Habilita��o do clock da porta escolhida para o LCD
	RCC->AHB1ENR |= (1 << ((uint32_t)LCD_PORT - (GPIOA_BASE)) / ((GPIOB_BASE) - (GPIOA_BASE)));

	//Reset dos pinos da porta
	LCD_PORT->ODR &= ~((1 << LCD_RS_PIN) | (1 << LCD_E_PIN) | (1 << LCD_D4_PIN) | (1 << LCD_D5_PIN) | (1<< LCD_D6_PIN) | (1 << LCD_D7_PIN));

	//Configura��o de sa�da dos pinos da porta
	LCD_PORT->MODER |=	(0b01 << 2*LCD_RS_PIN) | (0b01 << 2*LCD_E_PIN)  | (0b01 << 2*LCD_D4_PIN) | (0b01 << 2*LCD_D5_PIN) | (0b01 << 2*LCD_D6_PIN) | (0b01 << 2*LCD_D7_PIN);

	//Configura��o do DAC para controle de contraste do LCD por meio do pino PA4
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;	//habilita o clock do GPIOA
	GPIOA->MODER |= 0b11 << 8;				//inicializa��o do pino PA4 no modo anal�gico
	RCC->APB1ENR |= 1 << 29;				//habilita o clock da interface digital do DAC
	DAC->DHR12R1 = 500;					//valor de contraste
	DAC->CR |= 1;							//habilita o canal 1 do DAC

	//Processo de inicializa��o conforme descrito no datasheet
	Delay_ms(50);	//aguarda 50ms para se comunicar com o LCD

	LCD_CMD(0x3);	//reset e inicializa��o do controlador (ainda no modo de 8 bits)
    Delay_ms(5);	//espera pelo menos 4.1 ms

    LCD_CMD(0x3);
    Delay_ms(5);	//espera pelo menos 4.1 ms

    LCD_CMD(0x3);
    Delay_us(150);	//espera pelo menos 100 us

    LCD_CMD(0x2);	//modo de comunica��o de 4 bits
    Delay_us(150);	//espera pelo menos 100 us

    LCD_CMD(0x2);	//modo de 4 bits
    LCD_CMD(0x8);	//LCD com 2 ou mais linhas. Tipo de fonte do LCD (matriz 5x8 pontos)

    LCD_CMD(0x0);	//dire��o do texto da esquerda para direita
    LCD_CMD(0x6);

    LCD_Clear();	//limpa o LCD e posiciona o cursor no in�cio do display

    LCD_CMD(0x0);	//liga o display sem cursor vis�vel
    LCD_CMD(0xC);
}


//Escreve um caractere no LCD
static void LCD_Write_Char(char Data)
{
	char Low_nibble,High_nibble;
	Low_nibble  = (Data & 0x0F);
	High_nibble = (Data >> 4);

	LCD_PORT->ODR |= (1 << LCD_RS_PIN);	//seleciona o registrador de dados

	LCD_DATA(High_nibble);	//escreve o nible alto
	enable_pulse();			//pulso de enable

	LCD_DATA(Low_nibble);	//escreve o nible baixo
	enable_pulse();			//pulso de enable
}

//Escreve uma string no LCD
void LCD_Write_String(uint8_t linha, uint8_t coluna, char *string)
{
	LCD_Set_Cursor(linha, coluna);
	while(*string)
	{
		if(current_X > LCD_COLUNAS)
		{
			current_X = 1;
			current_Y++;
			LCD_Set_Cursor(current_Y, current_X);
		}
		if(*string == '\n')
		{
			current_Y++;
			LCD_Set_Cursor(current_Y, 1);
		}
		else
		{
			LCD_Write_Char(*string);
			current_X++;
		}
		string++;
	}
}

//Liga o LCD
void LCD_Display_ON(void)
{
	LCD_CMD(0x0);
	LCD_CMD(0xC);
}

//Desliga o LCD
void LCD_Display_OFF(void)
{
	LCD_CMD(0x0);
	LCD_CMD(0x8);
}

//Liga o cursor
void LCD_Cursor_ON(void)
{
	LCD_CMD(0x0);
	LCD_CMD(0xE);
}

//Desliga o cursor
void LCD_Cursor_OFF(void)
{
	LCD_CMD(0x0);
	LCD_CMD(0xC);
}

//liga o cursor piscante
void LCD_Blink_ON(void)
{
	LCD_CMD(0x0);
	LCD_CMD(0xD);
}

//desliga o cursor piscante
void LCD_Blink_OFF(void)
{
	LCD_CMD(0x0);
	LCD_CMD(0xC);
}

//Desloca o conte�do do LCD para a esquerda
void LCD_SHL(void)
{
	LCD_CMD(0x1);
	LCD_CMD(0x8);
}

//Desloca o conte�do do LCD para a direita
void LCD_SHR(void)
{
	LCD_CMD(0x1);
	LCD_CMD(0xC);
}



#endif /* LCD_BLIO_H_ */
