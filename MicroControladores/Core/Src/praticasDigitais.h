#include "Utility.h"

void pausar(float valor){
	int contador = valor;
	while(contador)contador--;
}

void entrada(void){

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= 1 << 4; // Ligando o clock do GPIOE

	GPIOE->MODER &= ~(0b11 << 6); // Configurando o pino PE3 como entrada
	GPIOE->MODER &= ~(0b11 << 8); // Configurando o pino PE4 como entrada

	GPIOE->PUPDR |= 0b01 << 6; // Habilita o resistor pull-up do pino PE3
	GPIOE->PUPDR |= 0b01 << 8; // Habilita o resistor pull-up do pino PE4

	GPIOA->ODR |= 1 << 6;
	GPIOA->ODR |= 1 << 7;

	GPIOA->MODER |= 0b01 << 12;
	GPIOA->MODER |= 0b01 << 14;

	while(1){
		uint16_t vark0 = GPIOE->IDR & (1 << 4);
		uint16_t vark1 = GPIOE->IDR & (1 << 3);

		if(vark0)
			GPIOA->ODR |= 0b01 << 6;

		else
			GPIOA->ODR &= ~(0b01 << 6);

		if (vark1)
			GPIOA->ODR |= (1 << 7);

		else
			GPIOA->ODR &= ~(1 << 7);
	}
}

// Operação | serve para set
// Operação & serve para reset

void buffer(void){
	//Configurando pino  como saida e ligando clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	GPIOD->MODER |= 0b01 << 6;
	GPIOA->MODER |= 0b01 << 12;
	GPIOA->MODER |= 0b01 << 14;

	while(1){
		for(int i = 0; i < 4; i++){
			GPIOD->ODR |= 0b01 << 3;
			GPIOA->ODR |= 0b11 << 6;
			GPIOA->ODR &= ~(1 << 7);
			pausar(100000);
			GPIOD->ODR &= ~(1 << 3);
			GPIOA->ODR &= ~(1 << 6);
			GPIOA->ODR |= 1 << 7;
			pausar(100000);

		}
		GPIOA->ODR |= 1 << 6;
		GPIOA->ODR |= 1 << 7;
		pausar(1000000);
	}
}

void ledInterno(void) {

		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  //Gravando valor 1 no registrador AHB1ENR que ativa o clock do GPIOA porém mantendo o valor antigo

		GPIOA->MODER |= 0b010001 << 12; // Escrevendo valor binário 01 no registrador MODER para configurar PA6 e PA7 como saida

	for(int i = 0; i < 10; i++){

		GPIOA->ODR |= 1 << 6; // ligando led
		GPIOD->ODR |= 1 << 7; // Configurando OUTPUT DATA REGISTER para mandar nivel alto para PD7

		pausar(2000000); // pausando execução por um segundo

		GPIOA->ODR &= ~(1 << 6); // desligando led
		GPIOA->ODR &= ~(1 << 7); // desligando led

		pausar(100000); // Pausando execução por alguns segundos

		GPIOD->ODR &= ~(1 << 7);  // Configurando OUTPUT DATA REGISTER para mandar nivel baixo para PD7

	}
}

void pwm(void){

	Utility_Init(); // Inicializa o sistema de clock do stm32

	GPIO_Clock_Enable(GPIOA); // Ativando o clock do GPIOA

	GPIO_Pin_Mode(GPIOA, PIN_4, OUTPUT); // Configurando o pino PA4 como saída

	int tempoLigado = 0;
	int subida;
	while(1){
		if(tempoLigado == 10000)
			subida = 0;
		if(tempoLigado == 0)
			subida = 1;
		GPIO_Write_Pin(GPIOA, PIN_4, HIGH);
		Delay_us(tempoLigado);
		GPIO_Write_Pin(GPIOA, PIN_4, LOW);
		Delay_us(10000 - tempoLigado);
		if(subida)
			tempoLigado+=50;
		else
			tempoLigado-=200;
	}

}

void ligaTroca(void){
	// Ligando os clocks por meio dos métodos da biblioteca
	GPIO_Clock_Enable(GPIOA);
	GPIO_Clock_Enable(GPIOE);

	// Determinando pinos como saída
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);

	// Determinando pinos como entrada
	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);
	GPIO_Pin_Mode(GPIOE, PIN_4, INPUT);

	// Ligando resistores de PULL_UP
	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);
	GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP);

	// Enviando sinais para saída para determinar sinal inicial
	GPIO_Write_Pin(GPIOA, PIN_6, LOW);
	GPIO_Write_Pin(GPIOA, PIN_7, HIGH);

	// Implementando lógica de mudança de estados dos leds
	while(1){
		int botao1 = !(GPIO_Read_Pin(GPIOE, PIN_3));
		int botao2 = !(GPIO_Read_Pin(GPIOE, PIN_4));
		if(botao1 ^ botao2){
			GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
			GPIO_Write_Pin(GPIOA, PIN_7, LOW);
		}
		else{
			GPIO_Write_Pin(GPIOA, PIN_6, LOW);
			GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
		}
	}
}

