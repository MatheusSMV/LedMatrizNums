# Funcionamento

Este código controla uma matriz de 25 LEDs WS2812 conectada ao Raspberry Pi Pico, exibindo animações numéricas de 0 a 9. 

- **Animações:** Cada número é representado por uma animação definida em uma matriz 5x5, que atualiza um buffer de LEDs.
- **Controle via Botões:**  
  - **Botão A (GPIO 5):** Avança para a próxima animação.  
  - **Botão B (GPIO 6):** Retrocede para a animação anterior.  
- **LED de Status:** Um LED vermelho (GPIO 13) pisca periodicamente para indicar que o sistema está ativo (5 vezes por segundo).
- **Comunicação com os LEDs:** Utiliza o PIO para enviar os dados de cor no formato GRB para cada LED, conforme o estado definido no buffer.

O código garante leituras confiáveis dos botões com debounce e atualiza continuamente a matriz de LEDs de acordo com a animação selecionada.

[Vídeo de explicação e demonstração](https://youtu.be/dikOrUGiTyk)

# Matheus Santos Souza
