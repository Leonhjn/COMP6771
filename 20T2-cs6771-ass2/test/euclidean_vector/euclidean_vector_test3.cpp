#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <vector>

TEST_CASE("basic test") {
	// Please note - this test may not function, it's just here for stubbing purposes
	std::vector<double> v{1.0,2.0,3.0};
	auto a1 = comp6771::euclidean_vector(v.begin(),v.end());
	CHECK(a1[0] == 1.0);
	auto a2 = comp6771::euclidean_vector{-1.0, -2.0, -3.0};
	CHECK(a1 == -a2);
	CHECK(fmt::format("{}", a1 * a2) == "[-1 -4 -9]");
}