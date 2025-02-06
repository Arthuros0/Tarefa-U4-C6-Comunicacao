#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include "font.h"
#include "matrix_leds.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define ENDERECO 0x3C

#define GREEN 11
#define BLUE 12

#define BUTTON_A 5
#define BUTTON_B 6

ssd1306_t ssd;

void init_button(uint8_t pin);
void button_callback(uint gpio,uint32_t events);

absolute_time_t button_debounce;


int main(){

  stdio_init_all();

  i2c_init(I2C_PORT,400*1000);
  init_i2c_pins(I2C_SDA,I2C_SCL);
  
  ssd1306_init(&ssd,WIDTH,HEIGHT,false,ENDERECO,I2C_PORT);
  ssd1306_config(&ssd);
  ssd1306_send_data(&ssd);

  ssd1306_fill(&ssd, false);
  ssd1306_send_data(&ssd);

  init_led_matrix();
  init_led(GREEN);
  init_led(BLUE);
  init_button(BUTTON_A);
  init_button(BUTTON_B);

  gpio_set_irq_enabled_with_callback(BUTTON_A,GPIO_IRQ_EDGE_FALL,true,&button_callback);
  gpio_set_irq_enabled_with_callback(BUTTON_B,GPIO_IRQ_EDGE_FALL,true,&button_callback);

  button_debounce=delayed_by_ms(get_absolute_time(), 250);

  bool cor=true;
  bool matriz=false;
  char caracter;

  while (1)
  {
    cor=!cor;

    scanf("%c",&caracter);
    printf("%c\n", caracter);

    if(caracter >= '0' && caracter <= '9'){
      desenha_frame(numeros,caracter-48);
      matriz=true;
    }else if(matriz){
      apaga_matriz();
      matriz=false;
    }

    ssd1306_fill(&ssd,!cor);
    ssd1306_rect(&ssd,3,3,122,58,cor,!cor);
    ssd1306_draw_string(&ssd,"Caracter ",8,10);
    ssd1306_draw_char(&ssd,caracter,90,10);    
    ssd1306_send_data(&ssd);
    sleep_ms(1000);
  }
  
}


void init_button(uint8_t pin){
  gpio_init(pin);
  gpio_set_dir(pin, GPIO_IN);
  gpio_pull_up(pin);
}

void button_callback(uint gpio,uint32_t events){
  if (time_reached(button_debounce))
  {
    if(gpio == BUTTON_A){
      muda_estado(GREEN);

      if(gpio_get(BLUE))muda_estado(BLUE);

      ssd1306_draw_string(&ssd,gpio_get(GREEN) ?"Led Verde ON " : "Led Verde OFF ",8,30);
    }else if (gpio == BUTTON_B)
    {
      muda_estado(BLUE);

      if(gpio_get(GREEN))muda_estado(GREEN);
      
      ssd1306_draw_string(&ssd,gpio_get(BLUE) ?"Led Azul ON " : "Led Azul OFF ",8,30);
    }
    ssd1306_send_data(&ssd);
    button_debounce=delayed_by_ms(get_absolute_time(), 200);
  }
  
}