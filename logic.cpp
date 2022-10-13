#include <vector>
#include <cstdlib>

#include "logic.h"

namespace logic {
int random_select(interface::GridMat &grid_mat) {
  std::vector<int> available_index;
  for (auto index = 0; index < 9; index++) {
	if (grid_mat.ValueAtIndex(index) == 0) {
	  available_index.push_back(index);
	}
  }
  if (!available_index.empty()) {
	return available_index[rand() % available_index.size()];
  } else {
	return -1;
  }
}
}

