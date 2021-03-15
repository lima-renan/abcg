 <img src="https://upload.wikimedia.org/wikipedia/commons/e/ee/Ufabc_logo.png" width="75"/> <br /> Universidade Federal do ABC
NAMCTA008-17SA - Computação Gráfica - Prof. Harlen Costa Batagelo - 2021.1



Bruno Storer Franco Martins <br /> Github: Bstorer <br /> RA: 11201721797 <br /> <br />
Renan Ferreira Lima <br /> GitHub: lima-renan	<br /> RA: 11201722759


# Jogo: Tank Attack <br />
## Objetivo do jogo: Não permitir que os tanques inimigos cruzem o limiar inferior do tanque do jogador.


## Classes: <br />
**enemies.h/enemies.cpp:** Esses arquivos contém a declaração e definição da classe *enemie*. Essa classe guarda informações de todos os inimigos, isto é, controla a quantidade, gerencia o status (se o inimigo foi atingido ou não), atualiza a posição dos tanques e verifica se o tanque inimigo pode se movimentar ou não, entre outras. Além disso, a classe *enemies* possui uma correlação com a quantidade de pontos atingida pelo jogador, ou seja, a partir de 500 pontos maior é a quantidade de inimigos se movimentando, tal quantidade é proporcional, logo quanto maior a pontuação mais difícil o jogo vai se tornando. Em suma, é uma das classes fundamentais do jogo.

**player.h/player.cpp:** Esses arquivos contém a declaração e definição da classe *player*. Essa classe define o desenho do tanque do jogador e as movimentações permitidas, no caso, apenas na horizontal e com translação de amplitude máxima de 90º em relação a um referencial na tela, definido em função do cursor do *mouse*. Nessa classe há a implementação do modo de ataque especial, onde a partir de 500 pontos é possível que o jogador realize um ataque mais potente apertando a *tecla A*. 

**shots.h/shots.cpp:** Esses arquivos contém a declaração e definição da classe *shot*. Essa classe define os tiros do tanque do jogador, onde esses são pequenos losangos que saem de uma posição próxima da tanque, de tal forma que isso é transparente ao jogador, aparentando que os tiros partem do próprio tanque. Os tiros são controlados pelo jogador através da tecla *Space*, sendo limitados a determinada quantidade por intervalo de tempo, i.e., 1 tiro a cada 0,25s no modo normal e 1 tiro a cada 0,025s no modo especial, nesse último caso, durante um intervalo de até 3s, voltando para o estado normal após isso.

**Infosgame.h/infosgame.cpp:** Esses arquivos contém a declaração e definição da classe *infosgame*. A qual contém o status do jogo, i.e., se está em andamento ou se foi finalizado. Controla também o que os inputs do jogador, é possível utilizar as seguintes teclas: *seta direita* (desloca o tanque para a direita), *seta esquerda* (desloca o tanque para a esquerda), o *cursor do mouse* (para definir a posição dos tiros), *Space* (realiza o tiro), *A* (modo especial, realiza o tiro de “maior intensidade”). Essa classe também gerencia a pontuação, cada tiro que o jogador acerta no tanque inimigo, são acumulados 10 pontos.

**Implementação:** O jogo foi desenvolvido em C++ usando um fork da ABCg, como IDE utilizou-se o Visual Studio Code com os plug-ins (CMake 0.0.17, CMake Tools 1.6.0 e C/C++ IntelliSense, debugging and code browsing 1.2.2)

# Link para a página do jogo: <br />
<https://lima-renan.github.io/abcg/tanks/>







# Fork from: <br />
# ABCg

Development framework accompanying the course [MCTA008-17 Computer Graphics](http://professor.ufabc.edu.br/~harlen.batagelo/cg/) at [UFABC](https://www.ufabc.edu.br/).

## Author

Harlen Batagelo

## License

MIT
