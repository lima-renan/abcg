#ifndef INFOSGAME_HPP_
#define INFOSGAME_HPP_

#include <bitset>

enum class Input { Right, Left, Shoot, Especial};
enum class State { Going, End};

struct InfosGame {
  std::bitset<5> player_command;  
  State game_state{State::Going};
  int pontuation = 0;
  int base_special = 500;
  bool especial = false;
};

#endif