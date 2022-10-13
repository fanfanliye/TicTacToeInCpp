#include "Game.h"
#include "logic.h"

using std::cout;
using std::cin;

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

void GridMat::UpdateAtIndex(int index, int player_id) {
  grid_mat[index / 3][index % 3] = player_id;
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
			cout << char(grid_mat[i / 2][j / 4] > 0 ? ' ' : i / 2 * 3 + j / 4 + 1 + 48);
		  } else {
			cout << marks[grid_mat[i / 2][j / 4]];
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

int GridMat::ValueAtIndex(int index) {
  if (index >= 0 && index <9) {
	return grid_mat[index / 3][index % 3];
  } else {
	std::cerr << "Not a valid location!" << std::endl;
	return -1;
  }
}

void Game::PrintStart() {
  cout << "###############################" << std::endl;
  cout << "Welcome to Tic-Tac-Toe!" << std::endl;
  cout << "The game will start!" << std::endl;
}

int Game::GetPlayerInput() {
  cout << "The current available spots:" << std::endl;
  grid_mat.DrawGrid(true);
  cout << "Please select your location: ";
  int loc;
  cin >> loc;
  loc--;
  while (grid_mat.ValueAtIndex(loc) != 0) {
	cout << "Please select again: ";
	cin >> loc;
	loc--;
  }
  cout << "OK, you select location: " << loc + 1 << std::endl;
  return loc;
}

bool Game::CheckPlayCpu() {
  cout << "Do you want to compete with Computer? (Y/N)" << std::endl;
  char play_cpu_char;
  cin >> play_cpu_char;
  if (play_cpu_char == 'Y' || play_cpu_char == 'y') {
	cout << "OK, you will play against CPU." << std::endl;
	return true;
  } else {
	cout << "All right, I take that a NO." << std::endl;
	return false;
  }
}

void Game::GetPlayerNames(int player_id) {
  std::string player_name;
  if (play_cpu && player_id == 2) {
	cout << "Player 2 will be CPU." << std::endl;
	player_name = "CPU";
  } else {
	cout << "Please enter the name for player " << player_id << ": ";
	cin >> player_name;
  }
  cout << "Player " << player_id << " name: " << player_name << std::endl;
  player_name_to_id[player_name] = player_id;
  player_names[player_id - 1] = player_name;
}

void Game::PrintPlayerNames() {
  cout << "######" << std::endl;
  int player_id;
  for (const auto& name : player_names) {
	player_id = player_name_to_id[name];
	cout << "Player " << player_id << ": " << name << " --- " << marks[player_id] << std::endl;
  }
  cout << "######" << std::endl;
}

void Game::PrintGameOver(int winner_id) {
  cout << "Game Over!" << std::endl;
  if (winner_id > 0) {
	cout << "Winner is: " << player_names[winner_id - 1] << std::endl;
  } else {
	cout << "It is a draw!\n";
  }
}

void Game::PrintEnd() {
  cout << "Exiting game...\nDone\n";
}

void Game::GameIterCPU() {
  cout << "-------------------\n";
  cout << "It is CPU\'s turn!\n";
  int cpu_loc = logic::random_select(grid_mat);
  cout << "He choose the location: " << cpu_loc + 1;
  grid_mat.UpdateAtIndex(cpu_loc, 2);
  cout << "Current Grid:\n";
  grid_mat.DrawGrid(false);
  cout << "-------------------\n\n";
}

void Game::GameIterPlayer(int player_id) {
  cout << "-------------------\n";
  cout << "It is your turn, " << player_names[player_id - 1] << std::endl;
  int loc = GetPlayerInput();
  grid_mat.UpdateAtIndex(loc, player_id);
  cout << "Current Grid:\n";
  grid_mat.DrawGrid(false);
  cout << "-------------------\n\n";
}

Game::Game() {
  play_game = true;
  PrintStart();
  play_cpu = CheckPlayCpu();
  GetPlayerNames(1);
  GetPlayerNames(2);
  PrintPlayerNames();
  grid_mat.ReSet();
}

void Game::GameLoop() {
  cout << "Let's start the game! We start from player 1.\n";
  int cur_player_id = 2;
  while (grid_mat.DetermineWinner() == 0) {
	cur_player_id = 3 - cur_player_id;
	if (cur_player_id == 2 && play_cpu) {
	  GameIterCPU();
	} else {
	  GameIterPlayer(cur_player_id);
	}
  }
  PrintGameOver(grid_mat.DetermineWinner());
}

bool Game::AskContinue() {
  char play;
  cout << "Another round? (Y/N)" << std::endl;
  cin >> play;
  if (play == 'Y' || play == 'y') {
	cout << "OK, a new game will be started!" << std::endl;
	return true;
  } else {
	cout << "All right, I take that a NO." << std::endl;
	return false;
  }
}

void Game::PlayGame() {
  while (play_game) {
	grid_mat.ReSet();
	GameLoop();
	play_game = AskContinue();
  }
  PrintEnd();
}
} // interface