#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "abcg.hpp"
#include "infosgame.hpp"
#include <imgui.h>

class Enemies;
class Shots;
class OpenGLWindow;

class Player {
 public:
  void initializeGL(GLuint program);
  void glDrawInit();
  void paintGL(const InfosGame &info_game);
  void terminateGL();

  void update(InfosGame &info_game, float frames_diff_time);
  void setPlayerRotation(float rotation);
 private:
  friend Enemies;
  friend Shots;
  friend OpenGLWindow;

  GLuint m_vao{};
  GLuint m_vbo{};
  GLuint m_ebo{};

  GLuint m_program{};
  GLint m_translationLoc{};
  GLint m_colorLoc{};
  GLint m_scaleLoc{};
  GLint m_rotationLoc{};


  glm::vec2 displacement{glm::vec2(0)};
  glm::vec4 m_color{0.01568f,0.4862f,0.1450f,1};
  float m_rotation{};
  float size{0.125f};
  bool special_atack = false;
  bool using_especial = false;
  
  abcg::ElapsedTimer timer_to_cancel_especial;

};

#endif