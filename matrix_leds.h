#ifndef MATRIX_LEDS_H
#define MATRIX_LEDS_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pio_matrix.pio.h"

extern uint sm;

void init_led(uint8_t pin); //Inicia LED

void muda_estado(uint8_t pin); //Alterna estado do LED, se 1->0, se 0->1

uint8_t obter_index(uint8_t i); //Função auxiliar para preencher a matriz de LEDS

void desenha_frame(const uint32_t matriz[10][25],uint8_t frame); //Desenha frame especifico do vetor de frames

void init_led_matrix(); //Configurações para uso da matriz de LEDs

void apaga_matriz(); //Apaga os LEDs ligados da matriz de LEDs

extern const uint32_t numeros[10][25]; //Vetor  de frames, com os números de 0 a 9
#endif