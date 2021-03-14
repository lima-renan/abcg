#include "openglwindow.hpp"

#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <imgui.h>

#include <iostream>   
#include <string>  

#include "abcg.hpp"

void OpenGLWindow::handleEvent(SDL_Event &event) {

  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_SPACE)
      infos_game.player_command.set(static_cast<size_t>(Input::Shoot));
    if (event.key.keysym.sym == SDLK_LEFT)
      infos_game.player_command.set(static_cast<size_t>(Input::Left));
    if (event.key.keysym.sym == SDLK_RIGHT)
      infos_game.player_command.set(static_cast<size_t>(Input::Right));
    if(event.key.keysym.sym == SDLK_a)
      infos_game.player_command.set(static_cast<size_t>(Input::Especial));
  }

  if (event.type == SDL_KEYUP) {
    if (event.key.keysym.sym == SDLK_SPACE)
      infos_game.player_command.reset(static_cast<size_t>(Input::Shoot));
    if (event.key.keysym.sym == SDLK_LEFT )
      infos_game.player_command.reset(static_cast<size_t>(Input::Left));
    if (event.key.keysym.sym == SDLK_RIGHT)
      infos_game.player_command.reset(static_cast<size_t>(Input::Right));
    if(event.key.keysym.sym == SDLK_a)
      infos_game.player_command.reset(static_cast<size_t>(Input::Especial));
  }

  // Mouse events
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    if (event.button.button == SDL_BUTTON_LEFT)
      infos_game.player_command.set(static_cast<size_t>(Input::Shoot));
  }
  if (event.type == SDL_MOUSEBUTTONUP) {
    if (event.button.button == SDL_BUTTON_LEFT)
      infos_game.player_command.reset(static_cast<size_t>(Input::Shoot));
  }
  if (event.type == SDL_MOUSEMOTION) {
    float playerYPercent = 0.75f;
    float yFocus = vertical_screen*playerYPercent;
    float xFocus = horizonta_screen/2*(1+player_in_screen.displacement.x);

    glm::ivec2 mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    glm::vec2 direction{glm::vec2{mousePosition.x - xFocus ,
                                  yFocus - mousePosition.y}};
    auto player_rotation{std::atan2(direction.y, direction.x) - M_PI_2};
    player_in_screen.setPlayerRotation(player_rotation);
  }
}

void OpenGLWindow::initializeGL() {
  loadFont();

  auto vertPath{getAssetsPath() + "vertProgram.vert"};
  auto fragPath{getAssetsPath() + "fragProgram.frag"};
  
  m_program = createProgramFromFile(vertPath,fragPath);

  glClearColor(0.5725f, 0.3882f, 0.01176f, 1);

#if !defined(__EMSCRIPTEN__)
  glEnable(GL_PROGRAM_POINT_SIZE);
#endif

  auto seed{std::chrono::steady_clock::now().time_since_epoch().count()};
  random_numbers_generator.seed(seed);

  restart();
}

void OpenGLWindow::loadFont(){
  ImGuiIO &io{ImGui::GetIO()};
  auto filename{getAssetsPath() + "Inconsolata-Medium.ttf"};
  letters_font = io.Fonts->AddFontFromFileTTF(filename.c_str(), 60.0f);
  if (letters_font == nullptr) {
    throw abcg::Exception{abcg::Exception::Runtime("Cannot load font file")};
  }
}

void OpenGLWindow::restart() {
  infos_game.game_state = State::Going;
  infos_game.pontuation = 0;
  infos_game.especial = false;

  player_in_screen.initializeGL(m_program);
  enemies_in_screen.initializeGL(m_program, 10);
  shots_in_screen.initializeGL(m_program);
}

void OpenGLWindow::update() {
  float frames_diff_time{static_cast<float>(getDeltaTime())};

  player_in_screen.update(infos_game, frames_diff_time);
  enemies_in_screen.update(infos_game,frames_diff_time);
  shots_in_screen.update(player_in_screen, infos_game, frames_diff_time);


  collisionsDetection();
  checkCrossLine();

}

void OpenGLWindow::paintGL() {

  glClear(GL_COLOR_BUFFER_BIT);
  glViewport(0, 0, horizonta_screen, vertical_screen);

  if (infos_game.game_state == State::End && timer_to_wait.elapsed() > 5) 
    restart();
  

  if (infos_game.game_state == State::End)
    return;
  

  update();

  enemies_in_screen.paintGL();
  shots_in_screen.paintGL();
  player_in_screen.paintGL(infos_game);
}

void OpenGLWindow::paintUI() {
  abcg::OpenGLWindow::paintUI();

  {  
    setUISettings();
    
    if(infos_game.game_state == State::Going && 
    infos_game.especial == true){
      ImGui::Text("%d pontos\nEspecial", infos_game.pontuation);
    }else if (infos_game.game_state == State::Going){
      ImGui::Text("%d pontos", infos_game.pontuation);
    }else if (infos_game.game_state == State::End) {
      ImGui::Text("%d pontos \natingidos... \n\n  Fim do jogo", infos_game.pontuation);
    }

    ImGui::PopFont();
    ImGui::End();
  }
}

void OpenGLWindow::setUISettings(){
  auto position{ImVec2(0.1,0.5)};
    auto size{ImVec2(500, 500)};
    ImGui::SetNextWindowSize(size);
    ImGui::SetNextWindowPos(position);
    ImGuiWindowFlags flags{ImGuiWindowFlags_NoBackground |
                           ImGuiWindowFlags_NoTitleBar |
                           ImGuiWindowFlags_NoInputs};
    ImGui::Begin(" ", nullptr, flags);
    ImGui::PushFont(letters_font);
}

void OpenGLWindow::resizeGL(int width, int height) {
  horizonta_screen = width;
  vertical_screen = height;

  glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLWindow::terminateGL() {
  glDeleteProgram(m_program);

  enemies_in_screen.terminateGL();
  shots_in_screen.terminateGL();
  player_in_screen.terminateGL();
}

void OpenGLWindow::collisionsDetection() {
  float base_lenght_hit1 = 0.95f;
  float base_lenght_hit2 = 0.95f;
  for (auto &shot : shots_in_screen.shots_vector) {
    if (shot.is_ended) continue;

    for (auto &enemy : enemies_in_screen.enemies_vector) {

      auto enemyTranslation{enemy.displacement};
      auto distance{glm::distance(shot.displacement, enemyTranslation)};

      if (distance < shots_in_screen.size * base_lenght_hit1 + enemy.size * base_lenght_hit2) {
        infos_game.pontuation += 10;
        enemy.killed = true;
        shot.is_ended = true;
      }
    }
  }
}

void OpenGLWindow::checkCrossLine(){
  for (auto &enemy : enemies_in_screen.enemies_vector){
    if(enemy.displacement.y <= -1.0f){
      infos_game.game_state = State::End;
      timer_to_wait.restart();
    }
  }
}

