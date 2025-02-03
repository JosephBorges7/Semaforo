# Semáforo com Raspberry Pi Pico

Este projeto implementa um semáforo utilizando a Raspberry Pi Pico. Os LEDs mudam de estado automaticamente em um ciclo definido.

## 🚦 Funcionamento

O semáforo segue a seguinte lógica:
1. **Vermelho** aceso por 3 segundos.
2. **Amarelo** aceso por 3 segundos.
3. **Verde** aceso por 3 segundos.
4. Repete o ciclo.

A troca de estados é gerenciada por um temporizador repetitivo, que chama uma função de callback a cada 3 segundos para atualizar o semáforo.

## 🛠️ Componentes Necessários
- Raspberry Pi Pico
- LEDs (Vermelho, Amarelo e Verde)
- Resistores (220Ω ou similar)
- Jumpers
- Protoboard

## 📌 Ligação dos LEDs

Os LEDs devem ser conectados aos seguintes pinos da Raspberry Pi Pico:

| LED         | Pino GPIO |
|------------|-----------|
| Vermelho   | GPIO 11   |
| Amarelo    | GPIO 12   |
| Verde      | GPIO 13   |

## 💻 Código Fonte

```c
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_VERMELHO 11
#define LED_AMARELO 12
#define LED_VERDE 13

int estado_semaforo = 0;

bool semaforo_callback(struct repeating_timer *t) {
    gpio_put(LED_VERMELHO, false);
    gpio_put(LED_AMARELO, false);
    gpio_put(LED_VERDE, false);

    if (estado_semaforo == 0) {
        gpio_put(LED_VERMELHO, true);
        estado_semaforo = 1;
    } else if (estado_semaforo == 1) {
        gpio_put(LED_AMARELO, true);
        estado_semaforo = 2;
    } else {
        gpio_put(LED_VERDE, true);
        estado_semaforo = 0;
    }
    return true;
}

int main() {
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_init(LED_AMARELO);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    gpio_put(LED_VERMELHO, true);

    struct repeating_timer timer;
    add_repeating_timer_ms(3000, semaforo_callback, NULL, &timer);

    while (true) {
        printf("Aguardando mudança de cor do semaforo...\n");
        sleep_ms(1000);
    }
    return 0;
}
```

## 🔧 Como Compilar e Executar

1. Instale o **SDK do Raspberry Pi Pico**.
2. Compile o código usando **CMake** e **Make**.
3. Transfira o arquivo `.uf2` para a Pico.

## 📜 Licença
Este projeto é de uso livre para fins educacionais e experimentação.

