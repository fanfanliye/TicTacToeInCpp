#ifndef TICTACTOEINCPP__GAME_H_
#define TICTACTOEINCPP__GAME_H_
#include <string>
#include <unordered_map>
#include <iostream>

namespace interface {
class GridMat {
 private:
  int grid_mat[3][3] = {{0, 0, 0},
						{0, 0, 0},
						{0, 0, 0}};
  const char MARKS[3] = {' ', 'O', 'X'};

 public:
  GridMat();
  void ReSet();
  void UpdateAtLoc(int loc, int player_id);
  int DetermineWinner();
  void DrawGrid(bool draw_remain=false);
};

}// interface

#endif //TICTACTOEINCPP__GAME_H_
