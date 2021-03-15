#ifndef OPENGLWINDOW_HPP_
#define OPENGLWINDOW_HPP_

#include <imgui.h>

#include <random>

#include "abcg.hpp"

#include "player.hpp"
#include "shots.hpp"
#include "enemies.hpp"


class OpenGLWindow : public abcg::OpenGLWindow {
 protected:
  void handleEvent(SDL_Event& event) override;
  void initializeGL() override;
  void loadFont();
  void paintGL() override;
  void paintUI() override;
  void resizeGL(int width, int height) override;
  void terminateGL() override;
  void checkCrossLine();



 private:
  GLuint m_program{};

  int horizonta_screen{};
  int vertical_screen{};

  InfosGame infos_game;

  Enemies enemies_in_screen;
  Shots shots_in_screen;
  Player player_in_screen;

  abcg::ElapsedTimer timer_to_wait;

  ImFont* letters_font{};

  std::default_random_engine random_numbers_generator;

  void collisionsDetection();
  void setUISettings();

  void restart();
  void update();

  //int a = 0;
};

#endif