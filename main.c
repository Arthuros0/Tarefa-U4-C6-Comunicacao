#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include "font.h"
#include "matrix_leds.h"
#include "hardware/timer.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define ENDERECO 0x3C

#define GREEN 11
#define BLUE 12

#define BUTTON_A 5
#define BUTTON_B 6

ssd1306_t ssd; //Váriavel do tipo ssd1306_t, armazena as informações relacionados ao display

void init_button(uint8_t pin); //Função de inicialização dos botões
void button_callback(uint gpio,uint32_t events); //Função de callback dos botões
bool usb_comm_callback(struct repeating_timer *t);

absolute_time_t button_debounce; //Váriavel que armazena o intervalo de debounce do botão
absolute_time_t serial_debounce;

bool cor=true;      //Boleano usado para piscar o retangulo do display
char caracter;      //Váriavel que armazena o caracter digitado
bool serial=true;

int main(){

  stdio_init_all(); //Inicialização dos uart serial

  //Inicialização do i2c e configuração dos pinos i2c
  i2c_init(I2C_PORT,400*1000);
  init_i2c_pins(I2C_SDA,I2C_SCL);

  init_display(&ssd,ENDERECO,I2C_PORT); //Inicialização e configuração do display

  //Inicialização e configuração dos botões, LEDs e matriz de LEDs
  init_led_matrix();
  init_led(GREEN);
  init_led(BLUE);
  init_button(BUTTON_A);
  init_button(BUTTON_B);

  //Configuração das interrupções via botões
  gpio_set_irq_enabled_with_callback(BUTTON_A,GPIO_IRQ_EDGE_FALL,true,&button_callback);
  gpio_set_irq_enabled_with_callback(BUTTON_B,GPIO_IRQ_EDGE_FALL,true,&button_callback);

  button_debounce=delayed_by_ms(get_absolute_time(), 200); //Inicialização da váriavel de debounce
  serial_debounce=delayed_by_ms(get_absolute_time(), 2000); //Inicialização da váriavel de debounce do serial

  struct repeating_timer timer;

  bool matriz=false;  //Boleano usado para evitar sucessivas chamadas da função apaga_matriz()
  bool input=true;    //Boleano usado para verificar se entrada é válida

  uart_comm(&ssd);
  boas_vindas(&ssd);
  add_repeating_timer_ms(1000,usb_comm_callback,false,&timer);
  
  while (1)
  {
    //uart_comm(&ssd);
    cor=!cor; //Alterna valor de cor
    
    if(stdio_usb_connected()){
      scanf("%c",&caracter);
      printf("%c\n", caracter);
      button_debounce=delayed_by_ms(get_absolute_time(), 100); //Debounce para evitar interrupção enquanto display é preenchido
      
      input=input_invalido(&ssd,caracter); //Caso o input seja válido o caracter é impresso normalmente, caso não, há uma mensagem de input invalido
      if(input){
        //Verifica se caracter é um número e caso for imprime na matriz, se não for verifica
        //se matriz está acesa e apaga caso esteja
        if(caracter >= '0' && caracter <= '9'){
          desenha_frame(numeros,caracter-48);
          matriz=true;
        }else if(matriz){
          apaga_matriz();
          matriz=false;
        }

        mensagem_caracter(&ssd,cor,caracter);

      }
    }
    sleep_ms(50); 
  }
  
}


void init_button(uint8_t pin){
  gpio_init(pin);
  gpio_set_dir(pin, GPIO_IN);
  gpio_pull_up(pin);
}

void button_callback(uint gpio,uint32_t events){
  if (time_reached(button_debounce)) //Verifica se o tempo de debounce foi atigindo
  {
    ssd1306_fill(&ssd,!cor); //Limpa display
    ssd1306_rect(&ssd,3,3,122,58,cor,!cor); //Desenha retângulo
    if(gpio == BUTTON_A){ //Se tiver sido o botão A a chamar a interrupção o led verde muda
      muda_estado(GREEN);

      if(gpio_get(BLUE))muda_estado(BLUE); //Se o led azul estiver ligado, desliga

      //Imprime o status do led verde
      ssd1306_draw_string(&ssd,gpio_get(GREEN) ?"Led Verde ON! " : "Led Verde OFF!",8,30);
      printf(gpio_get(GREEN) ?"Led Verde ON! " : "Led Verde OFF! ");
    }else if (gpio == BUTTON_B){ //Se tiver sido o botão B a chamar a interrupção o led azul muda
      muda_estado(BLUE);

      if(gpio_get(GREEN))muda_estado(GREEN);//Se o led verde estiver ligado, desliga
      
      //Imprime o status do led azul
      ssd1306_draw_string(&ssd,gpio_get(BLUE) ?"Led Azul ON! " : "Led Azul OFF!",8,30);
      printf(gpio_get(BLUE) ?"Led Azul ON! " : "Led Azul OFF! ");
    }
    printf("\n");
    ssd1306_send_data(&ssd); //Atualiza display
    button_debounce=delayed_by_ms(get_absolute_time(), 200); //Atualiza debounce
    serial_debounce=delayed_by_ms(get_absolute_time(), 3000); //Permite que a mensagem de status do led fique ativa por 3seg se o serial estiver desconectado
  }
  
}

bool usb_comm_callback(struct repeating_timer *t){
  if(!stdio_usb_connected()){
    if(time_reached(serial_debounce)){
      mensagem_serial(&ssd); //Informa que é preciso iniciar o caracter
      serial=false;
    }
  }else if(!serial){ //Caso o serial volte imprime a mensagem do caracter
    serial=true;
    mensagem_caracter(&ssd, cor, caracter);
  }
  return 1;
}