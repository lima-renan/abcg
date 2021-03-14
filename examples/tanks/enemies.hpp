#ifndef ENEMIES_HPP_
#define ENEMIES_HPP_

#include <list>
#include <random>

#include "abcg.hpp"
#include "infosgame.hpp"
#include "player.hpp"

class OpenGLWindow;

class Enemies {
 public:
  void initializeGL(GLuint program, int quantity);
  void gerenateEnemies(int quantity);
  int  countEnemiesThatCanWalk();
  void paintGL();
  void terminateGL();
  void update(InfosGame &info_game, float frames_diff_time);

 private:

  

  friend OpenGLWindow;

  GLuint m_program{};
  GLint m_colorLoc{};
  GLint m_rotationLoc{};
  GLint m_translationLoc{};
  GLint m_scaleLoc{};

  struct Enemy {
    GLuint m_vao{};
    GLuint m_vbo{};
    GLuint m_ebo{};

    int can_walk;
    float speed;
    glm::vec4 m_color{1};
    bool killed{false};
    float size{};
    glm::vec2 displacement{glm::vec2(0)};
  };

  float base_rotation = 3.1415;

  std::list<Enemy> enemies_vector;

  std::default_random_engine numberGenerator;
  std::uniform_real_distribution<float> numberGeneratorDist{-1.0f, 1.0f};


  Enemies::Enemy generateEnemy();

  
};

#endif