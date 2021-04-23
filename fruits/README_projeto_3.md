 <img src="https://upload.wikimedia.org/wikipedia/commons/e/ee/Ufabc_logo.png" width="75"/> <br /> <br /> Universidade Federal do ABC <br />
NAMCTA008-17SA - Computação Gráfica - Prof. Harlen Costa Batagelo - 2021.1



**Bruno Storer Franco Martins** <br /> Github: Bstorer <br /> RA: 11201721797 <br /> <br />
**Renan Ferreira Lima** <br /> GitHub: lima-renan	<br /> RA: 11201722759


## Jogo: Fruits! <br />
### Objetivo do jogo: Acertar a ordem que as frutas serão exibidas na tela, são  três frutas diferentes: manga, melão e banana. Há uma caixa de seleção em que o jogador pode selecionar uma das ordens possíveis, em seguida pode verificar apertando o botão correspondente, por fim é exibida uma mensagem com o resultado. <br />
### Características: As frutas são representadas em 3D, cada uma possui textura e iluminação. As frutas rotacionam na tela enquanto se deslocam, a interção com o jogador é feita através do uso do mouse na caixa de seleção. <br />


#### Estrutura: <br />
**assets:** Os assets estão subdivididos em pastas que contêm os maps, shaders, .obj e .mtl; esses arquivos possuem os dados relativos a geometria, textura, coloração, iluminação e demais aspectos visuais relativos aos objetos que serão renderizados. No projeto temos os .obj, .mlt e .jpg de todas as frutas que são representadas, os arquivos são denominados banana, mango e melon.

**openglwindow.hpp/openglwindow.cpp:** Definem como os elementos devem ser plotados na tela, neles estão definidas as interações com o jogador e as condições lógicas do jogo. 

**fruits.h/fruits.cpp:** Estruturam a maneira com que os dados visuais e geométricos de cada fruta serão recebidos, além de definir a posição e referência de cada elemento. 

**main.cpp:** Executa a inicialização do programa, lá é definido o título do jogo.

**Implementação:** O jogo foi desenvolvido em C++ usando uma fork da ABCg, como IDE utilizou-se o Visual Studio Code com os plug-ins (CMake 0.0.17, CMake Tools 1.6.0 e C/C++ IntelliSense, debugging and code browsing 1.2.2)

**Link para a página do jogo:** <https://lima-renan.github.io/abcg/tanks/> <br />
**Link para código fonte (privado, necessário estar logado):**  <https://github.com/lima-renan/COMP_GRAFICA_UFABC_2021/tree/main/Projeto%201/tanks>







# Fork from: <br />
# ABCg

Development framework accompanying the course [MCTA008-17 Computer Graphics](http://professor.ufabc.edu.br/~harlen.batagelo/cg/) at [UFABC](https://www.ufabc.edu.br/).

## Author

Harlen Batagelo

## License

MIT
