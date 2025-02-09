#include "LCD_Blio.h"
#include "Utility.h"


void questao1(void){

	Utility_Init(); // Inicializa o sistema de clock do stm32

	GPIO_Clock_Enable(GPIOA); // Ativando o clock do GPIOA

	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT); // Configurando o pino PA4 como saída

	int tempoLigado = 100;
	int tempo_desligado = 100;

	while(1){

		GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
		Delay_ms(tempoLigado);
		GPIO_Write_Pin(GPIOA, PIN_6, LOW);
		Delay_ms(tempo_desligado);

	}

}

void questao3(void) {
	Utility_Init(); // Inicializa o sistema de clock do stm32

	GPIO_Clock_Enable(GPIOA); // Ativando o clock do GPIOA

	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT); // Configurando o pino PA4 como saída
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);
	int tempoLigado = 0;
	int subida = 0;

	while(1){
			if(tempoLigado == 10000)
				subida = 0;
			if(tempoLigado == 0)
				subida = 1;
			GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
			GPIO_Write_Pin(GPIOA, PIN_7, LOW);
			Delay_us(tempoLigado);
			GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
			GPIO_Write_Pin(GPIOA, PIN_6, LOW);
			Delay_us(10000 - tempoLigado);
			if(subida)
				tempoLigado+=50;
			else
				tempoLigado-=200;
	}
}

void questao13(void) {
	Utility_Init(); // Inicializa o sistema de clock do stm32

	GPIO_Clock_Enable(GPIOA); // Ativando o clock do GPIOA
	GPIO_Clock_Enable(GPIOE);

	GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
	GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);
	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);
	GPIO_Pin_Mode(GPIOE, PIN_4, INPUT);

	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);
	GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP);

	while(1){
		int botao1 = !(GPIO_Read_Pin(GPIOE, PIN_3));
		int botao2 = !(GPIO_Read_Pin(GPIOE, PIN_4));
		if(botao1){
			GPIO_Write_Pin(GPIOA, PIN_6, LOW);
		}
		else if(botao2){
			GPIO_Write_Pin(GPIOA, PIN_7, LOW);
		}
		else{
			GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
			GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
		}
	}

}

void questao14(void) {
	Utility_Init(); // Inicializa o sistema de clock do stm32

	GPIO_Clock_Enable(GPIOA); // Ativando o clock do GPIOA
	GPIO_Clock_Enable(GPIOE);

	GPIO_Write_Pin(GPIOA, PIN_6, HIGH);

	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);

	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);


	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);

		int ligado = 0;

	while(1){
		int botao1 = !(GPIO_Read_Pin(GPIOE, PIN_3));

		if (botao1)
			ligado = !ligado;

		if(ligado){
			GPIO_Write_Pin(GPIOA, PIN_6, LOW);
		}

		else{
			GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
		}
		Delay_ms(100);
	}

}

void questao15(void){
	Utility_Init(); // Inicializa o sistema de clock do stm32

	GPIO_Clock_Enable(GPIOA); // Ativando o clock do GPIOA
	GPIO_Clock_Enable(GPIOE);

	GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
	GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);
	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);
	GPIO_Pin_Mode(GPIOE, PIN_4, INPUT);

	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);
	GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP);


	while(1){
		int botao2 = !(GPIO_Read_Pin(GPIOE, PIN_3));
		int botao1 = !(GPIO_Read_Pin(GPIOE, PIN_4));

		if(!botao2 && botao1) {

			while (1) {
				Delay_ms(500);
				botao1 = !(GPIO_Read_Pin(GPIOE, PIN_3));
				botao2 = !(GPIO_Read_Pin(GPIOE, PIN_4));
				if(!botao2 && botao1)
					break;
				if (botao1 && botao2) {
					GPIO_Write_Pin(GPIOA, PIN_6, LOW);
					while(botao1 && botao2)
						botao1 = !(GPIO_Read_Pin(GPIOE, PIN_3));
						botao2 = !(GPIO_Read_Pin(GPIOE, PIN_4));
					Delay_ms(100);
				}

				GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
				break;
			}
		}
	}
}

int tempo(void){
	int k1;
	int k0;

	for(int i = 0 ; i < 1000; i++){
		Delay_ms(1);
		k1 = !(GPIO_Read_Pin(GPIOE, PIN_3));
		k0 = !(GPIO_Read_Pin(GPIOE, PIN_4));
		if(k0 && k1)
			return 1;
	}
	return 0;
}

void questao16(void) {
	Utility_Init(); // Inicializa o sistema de clock do stm32

		GPIO_Clock_Enable(GPIOA); // Ativando o clock do GPIOA
		GPIO_Clock_Enable(GPIOE);

		GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
		GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
		GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
		GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);
		GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);
		GPIO_Pin_Mode(GPIOE, PIN_4, INPUT);

		GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);
		GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP);


		while(1){
			int k1 = !(GPIO_Read_Pin(GPIOE, PIN_3));
			int k0 = !(GPIO_Read_Pin(GPIOE, PIN_4));

			if(!k1 && k0) {
				if(tempo()){
					while (1) {
						Delay_ms(10);
						k0 = !(GPIO_Read_Pin(GPIOE, PIN_3));
						k1 = !(GPIO_Read_Pin(GPIOE, PIN_4));
						if(!k0 && k1)
							break;
						if (k0 && k1) {
							GPIO_Write_Pin(GPIOA, PIN_6, LOW);
							while(k1 && k0)
								k1 = !(GPIO_Read_Pin(GPIOE, PIN_3));
							//Delay_ms(100);
						}

						GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
						break;
					}
				}
				else{
					while(k0){
						k0 = !(GPIO_Read_Pin(GPIOE, PIN_4));
					}
				}
			}
		}
}

void questao2(void) {
	Utility_Init();

	GPIO_Clock_Enable(GPIOA);

	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);

	while (1) {
		GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
		Delay_ms(100);
		GPIO_Write_Pin(GPIOA, PIN_6, LOW);
		Delay_ms(500);
		GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
		Delay_ms(100);
		GPIO_Write_Pin(GPIOA, PIN_6, LOW);
		Delay_ms(100);
		GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
		Delay_ms(100);
		GPIO_Write_Pin(GPIOA, PIN_6, LOW);
		Delay_ms(900);
	}
}

void questao18(void) {

	Utility_Init();
	GPIO_Clock_Enable(GPIOA);
	GPIO_Clock_Enable(GPIOE);

	GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_2, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_3, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_4, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_5, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);

	GPIO_Pin_Mode(GPIOE, PIN_0, OUTPUT);
	GPIO_Pin_Mode(GPIOE, PIN_1, OUTPUT);
	GPIO_Pin_Mode(GPIOE, PIN_2, OUTPUT);
	GPIO_Pin_Mode(GPIOE, PIN_3, OUTPUT);
	GPIO_Pin_Mode(GPIOE, PIN_4, INPUT);
	GPIO_Pin_Mode(GPIOE, PIN_5, INPUT);
	GPIO_Pin_Mode(GPIOE, PIN_6, INPUT);
	GPIO_Pin_Mode(GPIOE, PIN_7, INPUT);

	GPIO_Resistor_Enable(GPIOE, PIN_0, PULL_UP);
	GPIO_Resistor_Enable(GPIOE, PIN_1, PULL_UP);
	GPIO_Resistor_Enable(GPIOE, PIN_2, PULL_UP);
	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);
	GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP);
	GPIO_Resistor_Enable(GPIOE, PIN_5, PULL_UP);
	GPIO_Resistor_Enable(GPIOE, PIN_6, PULL_UP);
	GPIO_Resistor_Enable(GPIOE, PIN_7, PULL_UP);

	const uint8_t teclado[4][4] = {
			{
				0b00000110, // 1
				0b01011011, // 2
				0b01001111, // 3
				0b01110111 // A
			},
			{
				0b01100110, // 4
				0b01101101, // 5
				0b01111101, // 6
				0b01111100 // B
			},
			{
				0b00000111, // 7
				0b01111111, // 8
				0b01101111, // 9
				0b00111001 // C
			},
			{
				0b01000000, // *
				0b00111111, // 0
				0b01110110, // #
				0b01011110 // D
			}
	};


	while (1) {
		int linha, coluna, apertou = 0;
		for (int i = 0; i < 4; i++) {
			GPIO_Write_Pin(GPIOE, i, LOW);

			for (int j = 4; j < 8; j++) {
				if (!GPIO_Read_Pin(GPIOE, j)) {
					linha = i;
					coluna = j - 4;
					apertou = 1;
					break;
				}
			}

			if (apertou) {
				GPIO_Write_Port(GPIOA, teclado[linha][coluna]);
				break;
			}
		}

		for (int i = 0; i < 4; i++)
			GPIO_Write_Pin(GPIOE, i, HIGH);

		GPIO_Write_Port(GPIOA, 0x0);
	}
}



void questao7(void) {
	Utility_Init();
	GPIO_Clock_Enable(GPIOA);

	GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_2, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_3, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_4, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_5, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);

	const uint8_t teclado[16] = {
				0b00111111, // 0
				0b00000110, // 1
				0b01011011, // 2
				0b01001111, // 3
				0b01100110, // 4
				0b01101101, // 5
				0b01111101, // 6
				0b00000111, // 7
				0b01111111, // 8
				0b01101111, // 9
				0b01110111, // A
				0b01111100, // B
				0b00111001, // C
				0b01011110, // D
				0b01111001, // E
				0b01110001 // F
	};

	while (1) {
		for (int i = 0; i < 16; i++) {
			GPIO_Write_Port(GPIOA, teclado[i]);
			Delay_ms(300);
		}
		Delay_ms(100);

		for (int i = 15; i >= 0; i--) {
			GPIO_Write_Port(GPIOA, teclado[i]);
			Delay_ms(300);
		}
		Delay_ms(100);
	}
}

void questao4 (void)
{
	// Preparando o sistema para inicializar o clock
	Utility_Init();

	// Inicializando o clock do registrador A
	GPIO_Clock_Enable(GPIOA);

	// Definindo os pinos como saída
	GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_2, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_3, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_4, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_5, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);

	while (1)
	{
		for (int i = 0; i <= 255; i++)
		{
			GPIO_Write_Port(GPIOA, i);
			Delay_ms(150);
		}
	}
}

void questao5 (void)
{
	// Preparando o sistema para inicializar o clock
	Utility_Init();

	// Inicializando o clock do registrador A
	GPIO_Clock_Enable(GPIOA);

	// Definindo os pinos como saída
	GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_2, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_3, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_4, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_5, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);

	int inverte = 0;
	int contador = 0;
	while(1)
	{
		for (int i = 0; i < 8; i++) {
			GPIO_Write_Pin(GPIOA, i, LOW);
		}

		GPIO_Write_Pin(GPIOA, contador, HIGH);
		if (inverte == 0) {
			contador++;
		} else {
			contador--;
		}

		if (contador == 7 || contador == 0) {
			inverte = !inverte;
		}

		Delay_ms(100);
	}
}

void questao6 (void)
{
	// Preparando o sistema para inicializar o clock
	Utility_Init();

	// Inicializando o clock do registrador A
	GPIO_Clock_Enable(GPIOA);

	// Definindo os pinos como saída
	GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT); // LED Vermelho Semaforo 1
	GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT); //	LED Amarelo Semaforo 1
	GPIO_Pin_Mode(GPIOA, PIN_2, OUTPUT); // LED Verde Semaforo 1
	GPIO_Pin_Mode(GPIOA, PIN_3, OUTPUT); // LED Vermelho Semaforo 2
	GPIO_Pin_Mode(GPIOA, PIN_4, OUTPUT); // LED Amarelo Semaforo 2
	GPIO_Pin_Mode(GPIOA, PIN_5, OUTPUT); // LED Verde Semaforo 2

	int array1[] = {0, 1, 2};
	int array2[] = {3, 4, 5};

	void manipularSemaforo(int array[]) {
	  for (int i = 0; i < 3; i++) {
	  GPIO_Write_Pin(GPIOA, array[i], HIGH);

	  if (i == 1)
	    Delay_ms(1100);

	  else if (!i)
		  Delay_ms(2000);

	  if (i != 2)
		  GPIO_Write_Pin(GPIOA,array[i], LOW);
	  }
	}

	while(1){
	  GPIO_Write_Pin(GPIOA, 5, HIGH);

	  manipularSemaforo(array1);

	  GPIO_Write_Pin(GPIOA, 5, LOW);
	  GPIO_Write_Pin(GPIOA, 2, HIGH);

	  manipularSemaforo(array2);

	  GPIO_Write_Pin(GPIOA, 2, LOW);
	}
}

void questao8(void){

	Utility_Init();
	LCD_Init(4,20);
	LCD_Clear();
//	LCD_Display_ON();

	GPIO_Clock_Enable(GPIOA);
	GPIO_Clock_Enable(GPIOD);

	GPIO_Pin_Mode(GPIOA, PIN_4, OUTPUT);


	GPIO_Pin_Mode(GPIOD, PIN_0, OUTPUT);
	GPIO_Pin_Mode(GPIOD, PIN_1, OUTPUT);
	GPIO_Pin_Mode(GPIOD, PIN_2, OUTPUT);
	GPIO_Pin_Mode(GPIOD, PIN_3, OUTPUT);
	GPIO_Pin_Mode(GPIOD, PIN_4, OUTPUT);
	GPIO_Pin_Mode(GPIOD, PIN_5, OUTPUT);

	char nome[] = "Marcos";
	char sobrenome[] = "Belo\n";

	while(1){
		for(int i = 10; i >= 0; i--){
			LCD_Clear();
			LCD_Write_String(1, 1 , nome);
			LCD_Write_String(2, 1 , sobrenome);
			Delay_ms(1000);
			LCD_Write_Char(i + '0');
			Delay_ms(500);
		}
	}
}

void testar_display(void) {

	LCD_Clear();
	Utility_Init();
	GPIO_Clock_Enable(GPIOA);

	GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_2, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_3, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_4, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_5, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);

	GPIO_Write_Port(GPIOA, 0b11111111);
//	Delay_ms(3000);
//	GPIO_Write_Port(GPIOA, 0b01001111);
//	Delay_ms(3000);
//	GPIO_Write_Port(GPIOA, 0b01011011);
//	Delay_ms(3000);
//	GPIO_Write_Port(GPIOA, 0b01011110);
//	Delay_ms(3000);

}

void questao9(void) {
	// Inicializando o sistema e configurando o GPIO
	Utility_Init();
	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT);

	// Função para enviar um pulso PWM ao servomotor
	void Servo_Pulse(uint16_t pulse_width_us) {
	    GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
	    Delay_us(pulse_width_us);
	    GPIO_Write_Pin(GPIOA, PIN_0, LOW);
	    Delay_us(20000 - pulse_width_us);
	}

	// Função para posicionar o servomotor em um ângulo específico
	void Servo_Set_Position(uint16_t angle) {
	    // Mapeamento: 0 graus -> 500us, 180 graus -> 2500us
	    uint16_t pulse_width = 500 + ((angle * 2000) / 180);
	    Servo_Pulse(pulse_width);
	}

	while (1) {
		// Mover suavemente de 0° a 180° e retornar
		for (int angle = 0; angle <= 180; angle += 1) {
			Servo_Set_Position(angle);
			Delay_us(500);
		}

		for (int angle = 180; angle >= 0; angle -= 1) {
			Servo_Set_Position(angle);
			Delay_us(500);
		}
	}
}

void questao17(void) {
	// Inicializando o sistema e configurando o GPIO
	Utility_Init();
	GPIO_Clock_Enable(GPIOA);
	GPIO_Clock_Enable(GPIOE);
	GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_3, INPUT);
	GPIO_Pin_Mode(GPIOA, PIN_4, INPUT);

	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);
	GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP);

	// Função para enviar um pulso PWM ao servomotor
	void Servo_Pulse(uint16_t pulse_width_us) {
	    GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
	    Delay_us(pulse_width_us);
	    GPIO_Write_Pin(GPIOA, PIN_0, LOW);
	    Delay_us(20000 - pulse_width_us);
	}

	// Função para posicionar o servomotor em um ângulo específico
	void Servo_Set_Position(uint16_t angle) {
	    // Mapeamento: 0 graus -> 500us, 180 graus -> 2500us
	    uint16_t pulse_width = 500 + ((angle * 2000) / 180);
	    Servo_Pulse(pulse_width);
	}





	int angle = 0;

	while(1){

		int k0 = !GPIO_Read_Pin(GPIOE, PIN_4);
		int k1 = !GPIO_Read_Pin(GPIOE, PIN_3);

		if (k0 && angle <= 180) {
			angle += 15;
		}

		else if (k1 && angle > 0) {
			angle -= 15;
		}
		Servo_Set_Position(angle);

	}

}

void questao10(void) {
	Utility_Init();
	GPIO_Clock_Enable(GPIOA);

	GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_2, OUTPUT);// Configurando o pino PA4 como saída

	void inverter(int i) {
		if (i) {
			GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
			GPIO_Write_Pin(GPIOA, PIN_1, LOW);
		} else {
			GPIO_Write_Pin(GPIOA, PIN_0, LOW);
			GPIO_Write_Pin(GPIOA, PIN_1, HIGH);
		}
	}

	int inv = 0;
	int tempoLigado = 0;
	int subida;
	while(1){
		if(tempoLigado == 10000) {
			subida = 0;
		}
		if(tempoLigado == 0) {
			subida = 1;
			inv = !inv;
			inverter(inv);
		}
		GPIO_Write_Pin(GPIOA, PIN_2, HIGH);
		Delay_us(tempoLigado);
		GPIO_Write_Pin(GPIOA, PIN_2, LOW);
		Delay_us(10000 - tempoLigado);
		if(subida)
			tempoLigado+=100;
		else
			tempoLigado-=50;

	}
}

void questao11(){
 Utility_Init();
 GPIO_Clock_Enable(GPIOA);
 GPIO_Pin_Mode(GPIOA, PIN_4, INPUT);
 GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT);

 GPIO_Resistor_Enable(GPIOA, PIN_4, PULL_UP);
 GPIO_Output_Mode(GPIOA, PIN_0, OPEN_DRAIN);

 GPIO_Write_Pin(GPIOA, PIN_9, HIGH);

 while(1){
  if(!GPIO_Read_Pin(GPIOA, PIN_4)){
   GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
  }
  else{
   GPIO_Write_Pin(GPIOA, PIN_0, LOW);
  }

 }

}

void questao12(){
 Utility_Init();
 GPIO_Clock_Enable(GPIOA);

 GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT); //INB1
 GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT); //INB2
 GPIO_Pin_Mode(GPIOA, PIN_2, OUTPUT); //INA1
 GPIO_Pin_Mode(GPIOA, PIN_3, OUTPUT); //INA2

 void gira_motor(int delay, int sentido, int rotacoes){ // sentido = 1 -> Horário, sentido = 0 -> Anti-horário

  for(int a=0;a<(50*rotacoes);a++){
   if(sentido == 1){
    for(int i = 0;i<4;i++){
     GPIO_Write_Port(GPIOA, (1 << i));
     Delay_ms(delay);
    }
   }
   else if(sentido == 0){

    for(int i=0;i<4;i++){
     GPIO_Write_Port(GPIOA, (8 >> i));
     Delay_ms(delay);
    }
   }
  }
 }

 while(1){
  gira_motor(10, 1, 2);
  gira_motor(10, 0, 1);
 }
}

void questao20(){
 Utility_Init();
 GPIO_Clock_Enable(GPIOA);
 GPIOA->MODER |= 0b01010101;

 GPIO_Resistor_Enable(GPIOA, PIN_4, PULL_UP);
 GPIO_Resistor_Enable(GPIOA, PIN_5, PULL_UP);
 GPIO_Resistor_Enable(GPIOA, PIN_6, PULL_UP);
 GPIO_Resistor_Enable(GPIOA, PIN_7, PULL_UP);

 uint32_t tamanho_sequencia = 0;
 uint32_t sequencia[32];

 GPIO_Write_Pin(GPIOA, PIN_0, LOW);
 GPIO_Write_Pin(GPIOA, PIN_1, LOW);
 GPIO_Write_Pin(GPIOA, PIN_2, LOW);
 GPIO_Write_Pin(GPIOA, PIN_3, LOW);

 Delay_ms(1000);

 while(1){
  sequencia[tamanho_sequencia] = Random_Number() % 4;
  tamanho_sequencia++;

  for(uint32_t i = 0; i < tamanho_sequencia; ++i){
      switch(sequencia[i]){
      case 0:
          GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
          break;
      case 1:
          GPIO_Write_Pin(GPIOA, PIN_1, HIGH);
          break;
      case 2:
          GPIO_Write_Pin(GPIOA, PIN_2, HIGH);
          break;
      case 3:
          GPIO_Write_Pin(GPIOA, PIN_3, HIGH);
          break;
      }

      Delay_ms(500);

      // Apaga todos os LEDs antes de exibir o próximo
      GPIO_Write_Port(GPIOA, 0b0);
      Delay_ms(200); // Pequena pausa entre LEDs
  }

  GPIO_Write_Port(GPIOA, 0b0);

  uint32_t posicao_sequencia = 0;
  int8_t completou_round = 0;

  while(completou_round == 0){
   for(uint8_t j=4;j<=7;j++){
    if(!GPIO_Read_Pin(GPIOA, j)){
     Delay_ms(50);
     if(!GPIO_Read_Pin(GPIOA, j)){
      if (sequencia[posicao_sequencia] == (j-4)){
       posicao_sequencia++;
       if(posicao_sequencia == tamanho_sequencia)
       completou_round = 1;
       while(!GPIO_Read_Pin(GPIOA, j))
        GPIO_Write_Pin(GPIOA, j-4, HIGH);

       GPIO_Write_Pin(GPIOA, j-4, LOW);
      } else completou_round = -1;
     }
    }
   }
  }



  if(completou_round == -1){
   GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
   GPIO_Write_Pin(GPIOA, PIN_1, HIGH);
   GPIO_Write_Pin(GPIOA, PIN_2, HIGH);
   GPIO_Write_Pin(GPIOA, PIN_3, HIGH);
   break;
  }
  Delay_ms(1000);
 }
}

void questao19(){
 Utility_Init();
 GPIO_Clock_Enable(GPIOA);

 GPIO_Pin_Mode(GPIOA, PIN_4, OUTPUT); //Buzzer
 GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT); //TrigUE
 GPIO_Pin_Mode(GPIOA, PIN_0, INPUT); //Echo

 GPIO_Resistor_Enable(GPIOA, PIN_0, PULL_DOWN);
 GPIO_Write_Pin(GPIOA, PIN_4, LOW);

 while(1){
  Delay_ms(10);
  GPIO_Write_Pin(GPIOA, PIN_1, HIGH);
  Delay_us(10);
  GPIO_Write_Pin(GPIOA, PIN_1, LOW);

  while(!GPIO_Read_Pin(GPIOA, PIN_0));

  uint32_t tempo_us = 0;
  while(GPIO_Read_Pin(GPIOA, PIN_0)){
   tempo_us++;
   Delay_us(1);
  }

  uint32_t distancia_cm = tempo_us/58;

  if(distancia_cm >= 30){
   GPIO_Write_Pin(GPIOA, PIN_4, LOW);
  }
  else if(distancia_cm < 30 && distancia_cm >= 20){
   GPIO_Write_Pin(GPIOA, PIN_4, HIGH);
   Delay_ms(500);
   GPIO_Write_Pin(GPIOA, PIN_4, LOW);
   Delay_ms(500);
  }
  else if(distancia_cm < 20 && distancia_cm >= 10){
   GPIO_Write_Pin(GPIOA, PIN_4, HIGH);
   Delay_ms(100);
   GPIO_Write_Pin(GPIOA, PIN_4, LOW);
   Delay_ms(100);
  }
  else if(distancia_cm < 10){
   GPIO_Write_Pin(GPIOA, PIN_4, HIGH);
  }
 }
}

