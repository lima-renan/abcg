#include "enemies.hpp"

#include <cppitertools/itertools.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

void Enemies::initializeGL(GLuint program, int quantity) {
  terminateGL();

  auto seed{std::chrono::steady_clock::now().time_since_epoch().count()};
  numberGenerator.seed(seed);

  m_program = program;
  m_colorLoc = glGetUniformLocation(m_program, "color");
  m_rotationLoc = glGetUniformLocation(m_program, "rotation");
  m_scaleLoc = glGetUniformLocation(m_program, "scale");
  m_translationLoc = glGetUniformLocation(m_program, "translation");

  gerenateEnemies(quantity);
}

void Enemies::gerenateEnemies(int quantity){
  enemies_vector.clear();
  enemies_vector.resize(quantity);
  float y_init = 1.5f;
  float x_init;

  for (auto &enemy : enemies_vector) {
    enemy = generateEnemy();
    x_init = numberGeneratorDist(numberGenerator);
    enemy.displacement = {x_init,y_init};
  }
}

void Enemies::paintGL() {
  glUseProgram(m_program);

  for (auto &enemy : enemies_vector) {
    glBindVertexArray(enemy.m_vao);

    glUniform1f(m_scaleLoc, enemy.size);
    glUniform1f(m_rotationLoc, base_rotation);
    glUniform2fv(m_translationLoc, 1, &enemy.displacement.x);

    glUniform4fv(m_colorLoc, 1, &enemy.m_color.r);
    glDrawElements(GL_TRIANGLES, 36 , GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
  }

  glUseProgram(0);
}

void Enemies::terminateGL() {
  for (auto enemy : enemies_vector) {
    glDeleteBuffers(1, &enemy.m_vbo);
    glDeleteBuffers(1, &enemy.m_ebo);
    glDeleteVertexArrays(1, &enemy.m_vao);
  }
}

void Enemies::update(InfosGame &info_game, float frames_diff_time) {
  auto &re{numberGenerator};
  std::uniform_real_distribution<float> randomRadius(0.0f, 1.0f);
  int total_can_walk = (countEnemiesThatCanWalk() + 1);
  for (auto &enemy : enemies_vector) {
    auto prob{randomRadius(re)};
    float prob_to_walk;

    if(info_game.pontuation <= 500)
      prob_to_walk = (0.001f/total_can_walk);
    else
      prob_to_walk = (0.001f/total_can_walk)*((info_game.pontuation)/500);

    if(prob <= prob_to_walk && enemy.can_walk == 0){
      enemy.speed = 0.25f + randomRadius(re);
      if(enemy.speed > 1)
        enemy.speed = 1;
      enemy.can_walk = 1;
    }
      
    
    if(enemy.can_walk == 1){
      enemy.displacement.y -= enemy.speed * frames_diff_time;
    }
      
    if (enemy.displacement.y <= -1.1f || enemy.killed == true){
      auto x_disloc{randomRadius(re)};
      enemy.displacement.y = 1.5f;
      enemy.can_walk = 0;
      if (prob <= 0.5) enemy.displacement.x += x_disloc;
      else enemy.displacement.x -= x_disloc;
      if(enemy.displacement.x > 0.85) enemy.displacement.x = 0.85;
      if(enemy.displacement.x < -0.85) enemy.displacement.x = -0.85;
      enemy.killed = false;
    }
  }
}

int Enemies::countEnemiesThatCanWalk(){
  int total = 0;
  for (auto &enemy : enemies_vector) {
    if (enemy.can_walk == 1)
      total += 1;
  }
  return total;
}

Enemies::Enemy Enemies::generateEnemy() {
  Enemy enemy;

  auto &re{numberGenerator};  
  std::uniform_int_distribution<int> randomSides(6, 20);
  enemy.can_walk = 0;


  std::uniform_real_distribution<float> randomIntensity(0.5f, 1.0f);
  enemy.m_color = glm::vec4({0.01568f,0.4862f,0.1450f,1}) * randomIntensity(re);

  enemy.m_color.a = 1.0f;
  enemy.size = 0.125f;
  enemy.displacement = glm::vec2(0);


  glm::vec2 direction{numberGeneratorDist(re), numberGeneratorDist(re)};

  
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

  glGenBuffers(1, &enemy.m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, enemy.m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions.data(),
               GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);


  glGenBuffers(1, &enemy.m_ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, enemy.m_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(),
               GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

 
  GLint positionAttribute{glGetAttribLocation(m_program, "inPosition")};


  glGenVertexArrays(1, &enemy.m_vao);
  glBindVertexArray(enemy.m_vao);

  glEnableVertexAttribArray(positionAttribute);
  glBindBuffer(GL_ARRAY_BUFFER, enemy.m_vbo);
  glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, enemy.m_ebo);
  glBindVertexArray(0);

  return enemy;
}
