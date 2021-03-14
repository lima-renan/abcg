#ifndef SHOTS_HPP_
#define SHOTS_HPP_

#include <list>

#include "abcg.hpp"
#include "infosgame.hpp"
#include "player.hpp"

class OpenGLWindow;

class Shots {
 public:
  void initializeGL(GLuint program);
  void drawInitShoot();
  void paintGL();
  void terminateGL();
  void check_and_remove_ended_shots();
  void update(Player &player, const InfosGame &infos_game, float frames_diff_time);

 private:
  friend OpenGLWindow;

  GLuint m_vao{};
  GLuint m_vbo{};

  GLuint m_program{};
  GLint m_colorLoc{};
  GLint m_rotationLoc{};
  GLint m_translationLoc{};
  GLint m_scaleLoc{};

  struct Shot {
    glm::vec2 displacement{glm::vec2(0)};
    glm::vec2 displacement_speed{glm::vec2(0)};
    bool is_ended = false;
  };

  float size{0.03f};

  std::list<Shot> shots_vector;
  abcg::ElapsedTimer time_shots;
};

#endif