#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs
#define LED_VERMELHO 11
#define LED_AMARELO 12
#define LED_VERDE 13

// Variável para controlar o estado do semáforo
int estado_semaforo = 0; // 0: Vermelho, 1: Amarelo, 2: Verde

// Função de callback do temporizador
bool semaforo_callback(struct repeating_timer *t) {
    // Desliga todos os LEDs
    gpio_put(LED_VERMELHO, false);
    gpio_put(LED_AMARELO, false);
    gpio_put(LED_VERDE, false);

    // Atualiza o estado do semáforo
    if(estado_semaforo == 0) {
         gpio_put(LED_VERMELHO, true); // Liga LED vermelho
         estado_semaforo = 1;
    } else if (estado_semaforo == 1) {
        gpio_put(LED_AMARELO, true); // Liga LED amarelo
        estado_semaforo = 2;
    } else {
        gpio_put(LED_VERDE, true); // Liga LED verde
        estado_semaforo = 0;
    }

    return true; // Mantém o temporizador repetindo
}

int main() {
    

    // Inicializa os pinos dos LEDs como saída
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_init(LED_AMARELO);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);


    // Inicia o semáforo com o LED vermelho ligado
    gpio_put(LED_VERMELHO, true);

    // Configuração do temporizador repetitivo
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, semaforo_callback, NULL, &timer);

    // Loop principal
    while (true) {
        printf("Aguardando mudança de cor do semaforo...\n"); // Imprime mensagem a cada segundo
        sleep_ms(1000);
    }

    return 0;
}