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

#define GREEN


int main(){

  stdio_init_all();

  i2c_init(I2C_PORT,400*1000);
  init_i2c_pins(I2C_SDA,I2C_SCL);
  
  ssd1306_t ssd;
  ssd1306_init(&ssd,WIDTH,HEIGHT,false,ENDERECO,I2C_PORT);
  ssd1306_config(&ssd);
  ssd1306_send_data(&ssd);

  ssd1306_fill(&ssd, false);
  ssd1306_send_data(&ssd);

  init_led_matrix();

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
    ssd1306_draw_char(&ssd,caracter,50,10);
    ssd1306_send_data(&ssd);
    sleep_ms(1000);
  }
  
}