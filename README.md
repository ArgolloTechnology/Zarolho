# 👀 Robo Eyes com OLED SSD1306 e Arduino Zarollo

Este projeto usa a biblioteca **FluxGarage Robo Eyes** como base, com um display OLED SSD1306 via I2C para criar uma animação interativa de olhos robóticos, controlados por sensores de luz e sensores de posição. Também há sons emitidos via buzzer em diferentes situações (ligando, acordando, incomodado).

## 📦 Componentes Necessários

- Arduino Nano R3 (ou compatível)
- Display OLED I2C com driver SSD1306 ou SSD1309
- Sensor de luminosidade (LDR) conectado ao pino A3
- Buzzer passivo no pino digital 8
- Sensor de posição "em pé" no pino digital 12 (ex: botão, reed switch)
- Sensor de posição "deitado" no pino digital 4
- Jumpers e protoboard

## 🧠 Funcionalidades

- Olhos animados com piscadas automáticas e movimentos de curiosidade
- Reações ao nível de luz:
  - **Ambiente escuro:** olhos vão fechando até dormir
  - **Ambiente muito claro:** olhos se contraem e emitem som de incômodo
  - **Luz média:** olhos normais e alerta
- Sons diferentes para:
  - Inicialização
  - Acordar
  - Irritação
- Animação de olhos confusos ao acordar do "sono"
- Ajustes automáticos de altura dos olhos conforme o ambiente

## 📁 Estrutura do Código

- `setup()`: Inicializa o display, os olhos e o sistema de som
- `loop()`: Atualiza os olhos e monitora os sensores
- `lightInteraction()`: Lê o sensor de luz e altera os olhos e sons conforme necessário
- `playSound()` / `updateSound()`: Sistema de reprodução de sons não-bloqueante

## 🖼️ Exemplo de Animação

Ao ligar o sistema:
- Os olhos abrem
- É reproduzido um som de "ligando"
- Dependendo da luminosidade, o comportamento muda automaticamente

## 📚 Bibliotecas Utilizadas

- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)
- [FluxGarage RoboEyes](https://github.com/FluxGarage/RoboEyes)

> Certifique-se de instalar todas as bibliotecas via o Gerenciador de Bibliotecas da IDE Arduino.

## ⚙️ Configurações

- Endereço I2C do display: `0x3C` (ajuste se o seu for `0x3D`)
- Resolução do display: 128x64
- Frequência serial: `9600 bps`

## 🧪 Possíveis Expansões

- **Estilos de olhos diferentes:** adicionar olhos em formato de coração, espiral, etc.
- **Integração com controle remoto ou comandos por Bluetooth**
- **Adicionar expressões com base em humor ou sensores adicionais (temperatura, som, etc)**

## 📸 Créditos

Este projeto é baseado no exemplo da biblioteca **FluxGarage Robo Eyes**, criado por Dennis Hoelscher (FluxGarage).

- [YouTube - FluxGarage](https://www.youtube.com/@FluxGarage)
- [Website - FluxGarage](https://www.fluxgarage.com)

---

> Sinta-se livre para contribuir com melhorias, animações personalizadas ou integração com novos sensores!
