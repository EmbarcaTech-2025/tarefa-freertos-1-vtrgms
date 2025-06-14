
# Tarefa: Roteiro de FreeRTOS #1 - EmbarcaTech 2025

Autor: Vitor Gomes

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Campinas, ___ de 2025

---

## Objetivo

Este projeto faz parte do desenvolvimento da segunda fase do curso **Embarcatech**. Para isto desenvolvi um programa capaz de gerenciar tarefas simultâneas usando [FreeRTOS](https://www.freertos.org), feito com a placa de desenvolvimento [BitDogLab](https://github.com/BitDogLab).

## Funcionamento

Este programa faz o gerenciamento de duas tarefas simples: piscar um LED RGB alternando suas cores e "beepar" um buzzer a uma frequência específica, tudo isso controlado por dois botões, que devem pausar e retomar a execução de cada tarefa. Porém o desafio real é implementar este processo usando RTOS.

## Componentes usados

- Raspberry Pi Pico W
- Buzzer → Pino 27 (GP21)
- LED RGB → Vermelho no pino 17 (GP13), verde no pino 15 (GP11) e azul no pino 16 (GP12)
- Botões: A → Pino 7 (GP5) e B → Pino 9 (GP6)

## Como reutilizar

É necessário instalar a [extensão oficial da Raspberry Pi Pico](https://github.com/raspberrypi/pico-vscode) no seu VSCode e criar um novo projeto C/C++.
Clone os arquivos presentes neste diretório e execute com sua placa conectada no modo BOOTSEL para compilar e importar o projeto.

> _Atente-se para a versão do SDK, este programa foi feito usando a 2.1.1_

## Mídia


## Resultados

O resultado foi o esperado e conforme estipulado pelo professor. O processo de criação foi rápido e eficaz para fins de apredizagem.


---

## 📜 Licença
GNU GPL-3.0.
