
#include <numeric>
#include <algorithm>

#include "../move_search/types.h"

std::pair<i32, i32> win_rate_model(i32 score, i32 ply);

constexpr i32 NORMALISATION_K = 100;