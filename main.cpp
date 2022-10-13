#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Game.h"

using interface::Game;
using std::cout;

int main() {
  srand(time(nullptr));
  Game game;
  game.PlayGame();
}
