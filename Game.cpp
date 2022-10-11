#include "Game.h"

using std::cout;

namespace interface {


GridMat::GridMat() {
  ReSet();
}

void GridMat::ReSet() {
  for (auto row: grid_mat) {
	for (int i = 0; i < 3; i++) {
	  *(row + i) = 0;
	}
  }
}

void GridMat::UpdateAtLoc(int loc, int player_id) {
  grid_mat[loc / 3][loc % 3] = player_id;
}

int GridMat::DetermineWinner() {
  for (auto rptr: grid_mat) {
	if (*rptr == 0) {
	  continue;
	}
	if (*rptr == *(rptr + 1) && *rptr == *(rptr + 2)) {
	  return *rptr;
	}
  }
  for (auto i = 0; i < 3; i++) {
	auto cptr = &grid_mat[0][i];
	if (*cptr == 0) {
	  continue;
	}
	if (*cptr == *(cptr + 3) && *cptr == *(cptr + 6)) {
	  return *cptr;
	}
  }
  auto center = grid_mat[1][1];
  if (center != 0) {
	if (center == grid_mat[0][0] && center == grid_mat[2][2]) {
	  return center;
	}
	if (center == grid_mat[0][2] && center == grid_mat[2][0]) {
	  return center;
	}
  }
  for (auto rptr: grid_mat) {
	for (auto j = 0; j < 3; j++) {
	  if (*(rptr + j) == 0) {
		return 0;
	  }
	}
  }
  return -1;
}

void GridMat::DrawGrid(bool draw_remain) {
  // TODO: refactor this
  for (auto i = 0; i < 5; i++) {
	for (auto j = 0; j < 11; j++) {
	  if (i % 2 == 0) {
		if ((j + 1) % 4 == 0) {
		  cout << "|";
		} else if (j % 4 == 1) {
		  if (draw_remain) {
			cout << (grid_mat[i / 2][j / 4] > 0 ? ' ' : i / 2 * 3 + j / 4 + 1);
		  } else {
			cout << MARKS[grid_mat[i / 2][j / 4]];
		  }
		} else {
		  cout << " ";
		}
	  } else {
		if ((j + 1) %  4 == 0) {
		  cout << "|";
		} else {
		  cout << "-";
		}
	  }
	}
	cout << "\n";
  }
}
} // interface