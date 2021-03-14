#include "shots.hpp"

#include <cppitertools/itertools.hpp>
#include <glm/gtx/rotate_vector.hpp>

void Shots::initializeGL(GLuint program) {
  terminateGL();

  m_program = program;
  m_colorLoc = glGetUniformLocation(m_program, "color");
  m_rotationLoc = glGetUniformLocation(m_program, "rotation");
  m_scaleLoc = glGetUniformLocation(m_program, "scale");
  m_translationLoc = glGetUniformLocation(m_program, "translation");

  shots_vector.clear();

  drawInitShoot();
}

void Shots::drawInitShoot(){

  std::vector<glm::vec2> positions(0);

  positions.emplace_back(0, 0.5);
  positions.emplace_back(0.5, 0);
  positions.emplace_back(-0.5, 0);
  positions.emplace_back(0, -0.5);
  

  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec2),
               positions.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  
  GLint positionAttribute{glGetAttribLocation(m_program, "inPosition")};

  glGenVertexArrays(1, &m_vao);

  glBindVertexArray(m_vao);
  glEnableVertexAttribArray(positionAttribute);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  
  glBindVertexArray(0);
}

void Shots::paintGL() {
  glUseProgram(m_program);

  glBindVertexArray(m_vao);
  glUniform4f(m_colorLoc, 1, 1, 1, 1);
  glUniform1f(m_rotationLoc, 0);
  glUniform1f(m_scaleLoc, size);

  for (auto &shot : shots_vector) {
    glUniform2f(m_translationLoc, shot.displacement.x,
                shot.displacement.y);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 12);
  }

  glBindVertexArray(0);

  glUseProgram(0);
}

void Shots::terminateGL() {
  glDeleteBuffers(1, &m_vbo);
  glDeleteVertexArrays(1, &m_vao);
}

void Shots::update(Player &player, const InfosGame &infos_game, float frames_diff_time) {

  float wait_time_to_shoot;
  float speed = 2.0f;

  if(player.using_especial == true)
    wait_time_to_shoot = 0.0250;
  else
    wait_time_to_shoot = 0.250;
  
  
  if (infos_game.player_command[static_cast<size_t>(Input::Shoot)] &&
      infos_game.game_state == State::Going) {
    
    if ( time_shots.elapsed() > wait_time_to_shoot) {
       time_shots.restart();

      
      glm::vec2 moviment1{glm::rotate(glm::vec2{0.0f, 1.0f}, player.m_rotation)};

      auto shoot_translation{player.displacement};
      auto shoot_velocity{moviment1 * speed};

      Shot shot{.displacement = shoot_translation,
                .displacement_speed = shoot_velocity,
                .is_ended = false};

      shots_vector.push_back(shot);
    }
  }

  for (auto &shot : shots_vector) {
  
    shot.displacement += shot.displacement_speed * frames_diff_time;

    float limit = 0.9f;
 
    if (shot.displacement.x < (-1)*limit || 
    shot.displacement.x > limit || 
    shot.displacement.y < (-1)*limit || 
    shot.displacement.y > limit) 
      shot.is_ended = true;

  }

  check_and_remove_ended_shots();
}

void Shots::check_and_remove_ended_shots(){
  shots_vector.remove_if([](const Shot &s) { return s.is_ended; });
}
