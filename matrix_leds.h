#ifndef MATRIX_LEDS_H
#define MATRIX_LEDS_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pio_matrix.pio.h"

extern uint sm;

void init_led(uint8_t pin);

void muda_estado(uint8_t pin);

uint8_t obter_index(uint8_t i);

void desenha_frame(const uint32_t matriz[10][25],uint8_t frame);

void init_led_matrix();

void apaga_matriz();

extern const uint32_t numeros[10][25];
#endif