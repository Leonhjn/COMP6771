#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>

TEST_CASE("basic test") {
	// Please note - this test may not function, it's just here for stubbing purposes
	auto  a1 = comp6771::euclidean_vector(3, 3.0);
	auto  a2 = comp6771::euclidean_vector(2, 3.0);
	try {
		a1 /= 0;
	}catch (...){
		std::cout << "error\n";
	}

	try {
		a1 += a2;
	}catch (...){
		std::cout << "error\n";
	}
	
}