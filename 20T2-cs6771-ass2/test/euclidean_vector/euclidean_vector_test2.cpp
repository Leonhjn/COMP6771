#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>

TEST_CASE("basic test") {
	// Please note - this test may not function, it's just here for stubbing purposes
	auto a1 = comp6771::euclidean_vector{1.0,2.0,3.0};
	auto a2 = comp6771::euclidean_vector{1.0,2.0,3.0};
	REQUIRE(a1 == a2);
	auto a3 = comp6771::euclidean_vector(3, 3.0);
	a1 += a2;
	CHECK(fmt::format("{}",a1) == "[2 4 6]");
	a1 *= 2;
	CHECK(fmt::format("{}",a1) == "[4 8 12]");
	a1 -= a3;
	CHECK(fmt::format("{}",a1) == "[1 5 9]");
}