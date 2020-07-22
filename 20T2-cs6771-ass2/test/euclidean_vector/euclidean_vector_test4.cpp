#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>

TEST_CASE("basic test") {
	// Please note - this test may not function, it's just here for stubbing purposes
	auto a1 = comp6771::euclidean_vector{3.0,4.0};
	auto aMove = comp6771::euclidean_vector(std::move(a1));
	CHECK(fmt::format("{}", aMove) == "[3 4]");
	CHECK(aMove.at(1) == 3.0);
	CHECK(aMove.dimensions() == 2);
	CHECK(comp6771::euclidean_norm(aMove) == 5);
	CHECK(fmt::format("{}", comp6771::unit(aMove)) == "[0.6 0.8]");
	CHECK(comp6771::dot(a1,aMove) == 25);
}