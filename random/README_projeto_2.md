 <img src="https://upload.wikimedia.org/wikipedia/commons/e/ee/Ufabc_logo.png" width="75"/> <br /> <br /> Universidade Federal do ABC <br />
NAMCTA008-17SA - Computação Gráfica - Prof. Harlen Costa Batagelo - 2021.1



**Bruno Storer Franco Martins** <br /> Github: Bstorer <br /> RA: 11201721797 <br /> <br />
**Renan Ferreira Lima** <br /> GitHub: lima-renan	<br /> RA: 11201722759


## Screensaver: Random Forms In Space <br />
### Descrição: O programa gera polígonos coloridos em 3D, a quantidade destes é crescente e não há interação com o teclado ou mouse, a ideia é remeter a um protetor de tela (screensaver). A definição das formas é aleatória, assim como a direção que elas se deslocam, as formas estão limitadas a um espaço de deslocamento (caixa), cada vez que uma forma atinge a borda da caixa, há uma mudança de cor e de posicionamento. O projeto inicia com uma única forma e é limitado a 2000 formas simultâneas, ao atingir esse limite ocorre um decrescimento constante de 1 forma até atingir o estado inicial. <br /><br />


#### Estrutura do projeto: <br />
**assets:** Nessa pasta estão os arquivos com atributos de cores e formas dos polígonos.

**object.hpp/object.cpp:** Definem a estrutura dos objetos projetados na tela, contém indíces, veŕtices, funções, entre outras características do que é projetado na tela.

**openglwindow.hpp/openglwindow.cpp:** Contêm a definição de como os elementos devem ser plotados na tela.

**main.cpp:** Executa a inicialização do programa.

**Observação:** Notamos um pequeno bug ao trocar de aba no browser, estamos analisando e estudaremos as correções para a próxima versão.

**Implementação:** O screensaver foi desenvolvido em C++ usando uma fork da ABCg, como IDE utilizou-se o Visual Studio Code com os plug-ins (CMake 0.0.17, CMake Tools 1.6.0 e C/C++ IntelliSense, debugging and code browsing 1.2.2)

**Link para a página do screensaver:** <https://lima-renan.github.io/abcg/random> <br />
**Link para código fonte:**  <https://github.com/lima-renan/COMP_GRAFICA_UFABC_2021/tree/main/Projeto%202/RandomFormsInSpace>







# Fork from: <br />
# ABCg

Development framework accompanying the course [MCTA008-17 Computer Graphics](http://professor.ufabc.edu.br/~harlen.batagelo/cg/) at [UFABC](https://www.ufabc.edu.br/).

## Author

Harlen Batagelo

## License

MIT
