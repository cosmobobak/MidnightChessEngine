#include "wdl_model.h"

std::pair<i32, i32> win_rate_model(i32 score, i32 ply) {
	constexpr auto As = std::array {
		-9.50613608, 80.39483574, -91.01771303, 103.05370743
	};
	constexpr auto Bs = std::array {
		-6.41966158, 43.76916282, -63.29152600, 76.95812720
	};

	static_assert(NORMALISATION_K == static_cast<i32>(std::reduce(As.begin(), As.end())));

	const auto m = std::min(240.0, static_cast<f64>(ply)) / 64.0;

	const auto a = (((As[0] * m + As[1]) * m + As[2]) * m) + As[3];
	const auto b = (((Bs[0] * m + Bs[1]) * m + Bs[2]) * m) + Bs[3];

	const auto x = std::clamp(static_cast<f64>(score), -4000.0, 4000.0);

	return {
		static_cast<i32>(std::round(1000.0 / (1.0 + std::exp((a - x) / b)))),
		static_cast<i32>(std::round(1000.0 / (1.0 + std::exp((a + x) / b))))
	};
}