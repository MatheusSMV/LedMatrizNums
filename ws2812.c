#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"
#include "ws2812.pio.h"

// Definição das variáveis globais
#define IS_RGBW false // Apenas o RGB sem LED Branco (RGBWhite)
#define NUM_PIXELS 25 // Matriz 5x5
#define WS2812_PIN 7 // A Matriz de LED GPIO 7
#define botao_a 5 // Botão A GPIO 5
#define botao_b 6 // Botão B GPIO 6
#define led_red 13 // O LED Vermelho GPIO 13
#define DEBOUNCE_MS 200 // Tempo para evitar múltiplas leituras

uint8_t led_r = 50;  // Força da Luz
uint8_t led_g = 0;  
uint8_t led_b = 0;   
volatile bool led_red_state = false; // Estado do LED vermelho

// Buffer de LEDs da matriz 5x5 - Armazenamento do Estado
bool led_buffer[NUM_PIXELS];

// Variável para controlar a animação atual
volatile int indice_animacao = 0; // Começa em 0 - Número 0

// Variável para controlar a cor atual
volatile int cor_atual = 0; // 0: Vermelho, 1: Verde, 2: Azul

// Função para enviar cor ao LED
static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

// Converter valores RGB para GRB (formato WS2812)
static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

//Todos os números, uma função p/ cada número.
void animacao_0()
{
    bool animacao[5][5] = {
        {0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0}
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            led_buffer[i * 5 + j] = animacao[i][j];
        }
    }
}

void animacao_1()
{
    bool animacao[5][5] = {
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0}
    };
    for (int k = 0; k < 5; k++) {
        for (int l = 0; l < 5; l++) {
            led_buffer[k * 5 + l] = animacao[k][l];
        }
    }
}

void animacao_2()
{
    bool animacao[5][5] = {
        {0, 1, 1, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0}
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            led_buffer[i * 5 + j] = animacao[i][j];
        }
    }
}

void animacao_3()
{
    bool animacao[5][5] = {
    {0, 1, 1, 1, 0},  
     {0, 0, 0, 1, 0}, 
     {0, 1, 1, 0, 0}, 
     {0, 0, 0, 1, 0}, 
     {0, 1, 1, 1, 0},
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            led_buffer[i * 5 + j] = animacao[i][j];
        }
    }
}

void animacao_4()
{
    bool animacao[5][5] = {
    {0, 1, 0, 0, 0},   
     {0, 0, 0, 1, 0}, 
     {0, 1, 1, 1, 0}, 
     {0, 1, 0, 1, 0}, 
     {0, 1, 0, 1, 0},
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            led_buffer[i * 5 + j] = animacao[i][j];
        }
    }
}

void animacao_5()
{
    bool animacao[5][5] = {
    {0, 1, 1, 1, 0},   
     {0, 0, 0, 1, 0}, 
     {0, 1, 1, 1, 0}, 
     {0, 1, 0, 0, 0}, 
     {0, 1, 1, 1, 0},
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            led_buffer[i * 5 + j] = animacao[i][j];
        }
    }
}

void animacao_6()
{
    bool animacao[5][5] = {
    {0, 1, 1, 1, 0}, 
     {0, 1, 0, 1, 0}, 
     {0, 1, 1, 1, 0}, 
     {0, 1, 0, 0, 0}, 
     {0, 1, 1, 1, 0},
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            led_buffer[i * 5 + j] = animacao[i][j];
        }
    }
}

void animacao_7()
{
    bool animacao[5][5] = {
     {0, 1, 0, 0, 0},   
     {0, 0, 0, 1, 0}, 
     {1, 1, 1, 0, 0}, 
     {0, 1, 0, 1, 0}, 
     {0, 1, 1, 0, 0},
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            led_buffer[i * 5 + j] = animacao[i][j];
        }
    }
}

void animacao_8()
{
    bool animacao[5][5] = {
    {0, 1, 1, 1, 0},   
     {0, 1, 0, 1, 0}, 
     {0, 1, 1, 1, 0}, 
     {0, 1, 0, 1, 0}, 
     {0, 1, 1, 1, 0},
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            led_buffer[i * 5 + j] = animacao[i][j];
        }
    }
}

void animacao_9()
{
    bool animacao[5][5] = {
    {0, 1, 1, 1, 0},  
     {0, 0, 0, 1, 0}, 
     {0, 1, 1, 1, 0}, 
     {0, 1, 0, 1, 0}, 
     {0, 1, 1, 1, 0},
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            led_buffer[i * 5 + j] = animacao[i][j];
 }
}
}

// Função para atualizar a matriz de LEDs com base no buffer
void set_one_led(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t color = urgb_u32(r, g, b);

    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (led_buffer[i])
        {
            put_pixel(color); // Liga LEDs ativos no buffer
        }
        else
        {
            put_pixel(0); // Mantém apagados os LEDs inativos
        }
    }
}

// Função para selecionar a animação correta com base no índice
void selecionar_animacao()
{
    switch (indice_animacao)
    {
        case 0: animacao_0(); break;
        case 1: animacao_1(); break;
        case 2: animacao_2(); break;
        case 3: animacao_3(); break;
        case 4: animacao_4(); break;
        case 5: animacao_5(); break;
        case 6: animacao_6(); break;
        case 7: animacao_7(); break;
        case 8: animacao_8(); break;
        case 9: animacao_9(); break;
        default: break;
    }
}

// Função de interrupção genérica para os botões
void gpio_irq_handler(uint gpio, uint32_t events)
{
    static absolute_time_t ultimo_tempo_a = 0;
    static absolute_time_t ultimo_tempo_b = 0;

    if (gpio == botao_a) {
        // Botão A
        if (absolute_time_diff_us(ultimo_tempo_a, get_absolute_time()) > DEBOUNCE_MS * 1000) {
            printf("Botão A pressionado (GPIO %d). Índice antes: %d\n", gpio, indice_animacao);
            indice_animacao = (indice_animacao + 1) % 10; // Incrementa o índice da animação
            cor_atual = (cor_atual + 1) % 3; // Alterna a cor
            printf("Índice depois: %d\n", indice_animacao);
            ultimo_tempo_a = get_absolute_time();
        }
    } 
    else if (gpio == botao_b) {
        // Botão B
        if (absolute_time_diff_us(ultimo_tempo_b, get_absolute_time()) > DEBOUNCE_MS * 1000) {
            printf("Botão B pressionado (GPIO %d). Índice antes: %d\n", gpio, indice_animacao);
            if (indice_animacao == 0) {
                indice_animacao = 9; // Caso esteja na animação 0, vai para a animação 9
            } else {
                indice_animacao--; // Decrementa o índice da animação
            }
            cor_atual = (cor_atual + 2) % 3; // Alterna a cor (volta uma cor)
            printf("Índice depois: %d\n", indice_animacao);
            ultimo_tempo_b = get_absolute_time();
        }
    }
}

// Função para configurar os botões com interrupções
void configurar_botao(uint pin, gpio_irq_callback_t handler)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);
    gpio_set_irq_enabled_with_callback(pin, GPIO_IRQ_EDGE_FALL, true, handler);
}

// Callback da interrupção do timer
bool piscar_led_red(struct repeating_timer *t)
{
    led_red_state = !led_red_state; // Alterna estado do LED vermelho
    gpio_put(led_red, led_red_state);
    return true; // Mantém a repetição do timer
}

int main()
{
    stdio_init_all(); // Inicializa comunicação serial 
    
    // Inicializa PIO e matriz de LEDs
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    // Configuração dos botões com interrupções usando o novo método
    configurar_botao(botao_a, gpio_irq_handler); // Interrupção para o Botão A
    configurar_botao(botao_b, gpio_irq_handler); // Interrupção para o Botão B

    // Configuração do LED vermelho
    gpio_init(led_red);
    gpio_set_dir(led_red, GPIO_OUT);

    // Configuração do timer para piscar LED vermelho
    struct repeating_timer timer;
    add_repeating_timer_ms(-100, piscar_led_red, NULL, &timer); // Chama a função a cada 100ms

    // Inicializa com a animação 0
    selecionar_animacao();

    while (1)
    {
        //Atualiza a matriz de LEDs com base na animação atual
        selecionar_animacao();
        switch (cor_atual) {
            case 0: set_one_led(50, 0, 0); break; // Vermelho
            case 1: set_one_led(0, 50, 0); break; // Verde
            case 2: set_one_led(0, 0, 50); break; // Azul
            case 3: set_one_led(50, 0, 0); break; // Vermelho
            case 4: set_one_led(0, 50, 0); break; // Verde
            case 5: set_one_led(0, 0, 50); break; // Azul
            case 6: set_one_led(50, 0, 0); break; // Vermelho
            case 7: set_one_led(0, 50, 0); break; // Verde
            case 8: set_one_led(0, 0, 50); break; // Azul
            case 9: set_one_led(50, 0, 0); break; // Vermelho
        }

        sleep_ms(10); // Reduz o uso da CPU
    }

    return 0;
}
