#ifndef TICTACTOEINCPP__GAME_H_
#define TICTACTOEINCPP__GAME_H_
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>

namespace interface {

class GridMat {
 private:
  int grid_mat[3][3] = {{0, 0, 0},
						{0, 0, 0},
						{0, 0, 0}};
  const char marks[3] = {' ', 'O', 'X'};

 public:
  GridMat();
  void ReSet();
  void UpdateAtLoc(int loc, int player_id);
  int DetermineWinner();
  void DrawGrid(bool draw_remain=false);
  int ValueAtLoc(int loc);
};

class Game {
 private:
  char play_cpu = 'N';  // TODO: figure out how to input bool directly
  const char marks[3] = {' ', 'O', 'X'};
  bool play_game;
  std::vector<std::string> player_names = {"", ""};
  std::unordered_map<std::string, int> player_name_to_id;
  GridMat grid_mat;
  int GetPlayerInput();
  void CheckPlayCpu();
  void PrintEnd();
  void GameIterPlayer(int player_id);
  void PrintStart();
  void PrintPlayerNames();
  void GetPlayerNames(int player_id);
  void PrintGameOver(int winner_id);
  void GameLoop();
  bool AskContinue();

 public:
  Game();
  void PlayGame();
};

}// interface

#endif //TICTACTOEINCPP__GAME_H_
