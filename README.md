# Tarefa: Comunicação Serial com RP2040

Esta projeto implementa comunicação serial usando UART e I2C no RP2040 com a placa BitDogLab, incluindo controle de LEDs e interação com botões.

## 📌 Funcionalidades

- Suporte para caracteres minúsculos.
- Entrada de caracteres via UART para exibição no display SSD1306.
- Exibição de números (0-9) na matriz WS2812 quando digitados via Serial Monitor.
- Interação com botões:
  - **Botão A:** Alterna LED Verde e exibe mensagem no display e Serial Monitor.
  - **Botão B:** Alterna LED Azul e exibe mensagem no display e Serial Monitor.
- Implementação de interrupções para leitura dos botões.
- Implementação de debouncing via software.

## 🛠️ Componentes Utilizados

- Placa **BitDogLab**
- Matriz de LEDs **WS2812** (5x5) - GPIO 7
- **LED RGB** - GPIOs 11, 12, 13
- **Botão A** - GPIO 5
- **Botão B** - GPIO 6
- **Display OLED SSD1306** - I2C (GPIO 14 e 15)

 ### **Pré-requisitos para utilização**
Certifique-se de que os seguintes itens estão instalados:

1. **Visual Studio Code**  
   - Ambiente de desenvolvimento integrado (IDE) para edição, compilação e depuração do código.

2. **Git**  
   - Ferramenta para versionamento de código e controle de repositórios.  

3. **Extensões do Visual Studio Code**  
   - **C/C++**: Suporte à linguagem C/C++ para análise de código, depuração e IntelliSense.  
   - **CMake Tools**: Para gerenciar e configurar projetos que utilizam o CMake.  
   - **Raspberry Pi Pico**: Extensão para facilitar o desenvolvimento e a comunicação com a placa Raspberry Pi Pico.  

4. **Zadig**  
   - Software necessário para instalar drivers USB.  
   - Permite a conexão via USB da placa Raspberry Pi Pico com o desktop ou notebook.  

5. **Versão 2.0.0+ do Raspberry Pi Pico SDK**  
   - Certifique-se de que a versão 2.0.0 ou superior do SDK para Raspberry Pi Pico está instalada.  
---

## 🚀 Como Executar

### **1. Configuração Inicial**
1. Certifique-se de que todas as dependências acima estão instaladas no seu computador.
2. Clone o repositório do projeto usando os comandos abaixo no terminal:  
   ```bash
   git init
   ```
   ```bash
   git clone https://github.com/Arthuros0/Tarefa-U4-C6-Comunicacao.git
   ```
3. Abra o projeto clonado no VS Code

### **2. Compilação e Carregamento na Placa**
1. Compile o projeto clicando na opção "**Compile Project**" da extensão Raspberry Pi Pico no **Visual Studio Code**.
2. Após a compilação bem-sucedida, conecte a Raspberry Pi Pico W ao computador utilizando um cabo USB.
3. Coloque a placa em modo **BootSel**:
   - Pressione e segure o botão **BOOTSEL** enquanto conecta a placa pelo cabo USB.
   - Caso esteja utilizando a BitDogLab, aperte o botão **RESET** enquanto pressiona e segura o botão **BOOTSEL** (este método não exige a reconexão do cabo USB) 
4. Localize o arquivo gerado com extensão .uf2 (como **tarefa_interrupcao.uf2**) e arraste-o para o dispositivo que aparecerá no computador. Ou selecione a opção "**Run Project(USB)**" da extensão Raspberry Pi Pico no **Visual Studio Code**.

### 3. Operação na Prática

1. Inicie a placa conectada via usb ao computador.
2. Abra o **monitor serial** do Visual Studio Code.
3. Configure o serial com a porta a qual a BitDogLab está conectada e com o Baud Rate(taxa de envio) em **115200**.
4. Inicie o monitoramento e dê as entradas que desejar.
5. Use os botões para interagir com o led RGB:
   - Pressione o botão A para alternar o led verde.
   - Pressione o botão B para alternar o led azul.
