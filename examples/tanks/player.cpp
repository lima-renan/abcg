#include "player.hpp"
#include <fmt/core.h>
#include <imgui.h>
#include <chrono>


#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/rotate_vector.hpp>

void Player::initializeGL(GLuint program) {
  terminateGL();


  m_program = program;
  m_colorLoc = glGetUniformLocation(m_program, "color");
  m_rotationLoc = glGetUniformLocation(m_program, "rotation");
  m_scaleLoc = glGetUniformLocation(m_program, "scale");
  m_translationLoc = glGetUniformLocation(m_program, "translation");

  special_atack = false;
  m_rotation = 0.0f;
  displacement = glm::vec2(0);
  displacement.x = 0.0f;
  displacement.y = -0.7f;


  glDrawInit();

}

void Player::glDrawInit(){

  std::array<glm::vec2, 20> positions{
      glm::vec2{-2.5,20.5}, glm::vec2{-2.5,2.5},
      glm::vec2{-9.5,2.5},glm::vec2{-9.5,-12.5}, 
      glm::vec2{9.5,-12.5},glm::vec2{9.5,2.5}, 
      glm::vec2{2.5,2.5}, glm::vec2{2.5,20.5},
      glm::vec2{4.5,20.5}, glm::vec2{4.5,22.5},
      glm::vec2{-4.5,22.5}, glm::vec2{-4.5,20.5},
      glm::vec2{-9.5,5.5}, glm::vec2{-12.5,5.5},
      glm::vec2{-12.5,-15.5}, glm::vec2{-9.5,-15.5},
      glm::vec2{9.5,5.5}, glm::vec2{12.5,5.5},
      glm::vec2{12.5,-15.5}, glm::vec2{9.5,-15.5}
      };

  for (auto &position :positions) {
    position /= glm::vec2{15.5f, 15.5f};
  }

  std::array indices{0, 1, 6,
                     0, 7, 6,
                     2, 5, 4,
                     2, 3, 4,
                     10, 9, 8,
                     10, 11, 8, 
                     13, 12, 15, 
                     13, 14, 15, 
                     16, 17, 18, 
                     16, 19, 18};

  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions.data(),
               GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);


  glGenBuffers(1, &m_ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(),
               GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


  GLint positionAttribute{glGetAttribLocation(m_program, "inPosition")};
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  glEnableVertexAttribArray(positionAttribute);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBindVertexArray(0);
}

void Player::setPlayerRotation(float rotation) { 
  m_rotation = rotation; 
  m_rotation = glm::clamp(m_rotation, glm::radians(-45.0f), glm::radians(45.0f));
}

void Player::paintGL(const InfosGame &info_game) {
  if (info_game.game_state != State::Going) return;

  glUseProgram(m_program);

  glBindVertexArray(m_vao);

  glUniform1f(m_scaleLoc, size);
  glUniform1f(m_rotationLoc, m_rotation);
  glUniform2fv(m_translationLoc, 1, &displacement.x);

  glUniform4fv(m_colorLoc, 1, &m_color.r);
  glDrawElements(GL_TRIANGLES, 36 , GL_UNSIGNED_INT, nullptr);

  glBindVertexArray(0);

  glUseProgram(0);
}

void Player::terminateGL() {
  glDeleteBuffers(1, &m_vbo);
  glDeleteBuffers(1, &m_ebo);
  glDeleteVertexArrays(1, &m_vao);
}

void Player::update(InfosGame &info_game, float frames_diff_time) {

  if(using_especial == true && timer_to_cancel_especial.elapsed() > 3)
    using_especial = false;

  if(info_game.pontuation%info_game.base_special==0 && info_game.pontuation!=0){
    special_atack = true;
    info_game.especial = true;
  }

  if(special_atack ==  true && info_game.player_command[static_cast<size_t>(Input::Especial)]){
    timer_to_cancel_especial.restart();
    using_especial = true;
    special_atack = false;
    info_game.especial = false;
  }
    
  

  float speed_player = 2.0f;
  float limit_screen = 0.85f;

  if (info_game.player_command[static_cast<size_t>(Input::Left)]){
    if (displacement.x >= (-1)*limit_screen)
      displacement.x -= speed_player * frames_diff_time;
  }
  if (info_game.player_command[static_cast<size_t>(Input::Right)]){
    if (displacement.x <= limit_screen)
      displacement.x += speed_player * frames_diff_time;
  }
}
