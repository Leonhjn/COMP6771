#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <compare>
#include <functional>
#include <list>
#include <memory>
#include <ostream>
#include <range/v3/algorithm.hpp>
#include <range/v3/detail/config.hpp>
#include <range/v3/iterator.hpp>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what) noexcept
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		// constructor
		explicit euclidean_vector(int size) noexcept;
		explicit euclidean_vector() noexcept;
		explicit euclidean_vector(int size, double value) noexcept;
		euclidean_vector(std::vector<double>::const_iterator,
		                 std::vector<double>::const_iterator) noexcept;
		euclidean_vector(std::initializer_list<double>) noexcept;
		// copy constructor
		euclidean_vector(const euclidean_vector&) noexcept;
		// move constructor
		euclidean_vector(euclidean_vector&&) noexcept;
		// copy&move assignment
		auto operator=(const euclidean_vector&) noexcept -> euclidean_vector&;
		auto operator=(euclidean_vector&&) noexcept -> euclidean_vector&;
		// destructor
		~euclidean_vector() = default;

		// operator overloads
		auto operator[](int index) -> double&;
		auto operator[](int index) const -> double;
		auto operator+() const -> euclidean_vector;
		auto operator-() const -> euclidean_vector;
		auto operator+=(const euclidean_vector&) -> euclidean_vector&;
		auto operator-=(const euclidean_vector&) -> euclidean_vector&;
		auto operator*=(double) -> euclidean_vector&;
		auto operator/=(double) -> euclidean_vector&;
		explicit operator std::vector<double>();
		explicit operator std::list<double>();

		// member function
		[[nodiscard]] auto at(int) const -> double;
		auto at(int) -> double&;
		[[nodiscard]] auto dimensions() const -> int;

		// friend function
		friend auto operator<<(std::ostream& os, const euclidean_vector& v) -> std::ostream& {
			os << '[';
			for (auto i = 0; i < v.size_; ++i) {
				os << v.magnitudes_[static_cast<size_t>(i)];
				if (i != (v.size_ - 1)) {
					os << ' ';
				}
			}
			os << ']';
			return os;
		}
		// ==
		friend auto operator==(const euclidean_vector& v1, const euclidean_vector& v2) -> bool {
			if (v1.size_ != v2.size_) {
				return false;
			}

			for (auto i = 0; i < v1.size_; ++i) {
				if (v1.magnitudes_[static_cast<size_t>(i)] != v2.magnitudes_[static_cast<size_t>(i)]) {
					return false;
				}
			}
			return true;
		}

		// !=
		friend auto operator!=(const euclidean_vector& v1, const euclidean_vector& v2) -> bool {
			return !(v1 == v2);
		}

		//+
		friend auto operator+(const euclidean_vector& v1, const euclidean_vector& v2)
		   -> euclidean_vector {
			if (v1.size_ != v2.size_) {
				throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(v1.size_) + ") and RHS("
				                             + std::to_string(v2.size_) + ") do not match");
			}
			euclidean_vector sum{v1};
			sum += v2;
			return sum;
		}

		//-
		friend auto operator-(const euclidean_vector& v1, const euclidean_vector& v2)
		   -> euclidean_vector {
			if (v1.size_ != v2.size_) {
				throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(v1.size_) + ") and RHS("
				                             + std::to_string(v2.size_) + ") do not match");
			}
			euclidean_vector sub{v1};
			sub -= v2;
			return sub;
		}

		// v*i
		friend auto operator*(const euclidean_vector& v1, double i) -> euclidean_vector {
			euclidean_vector mul{v1};
			return (mul *= i);
		}

		// v/i
		friend auto operator/(const euclidean_vector& v1, double i) -> euclidean_vector {
			if (i == 0) {
				throw euclidean_vector_error("Invalid vector division by 0");
			}

			euclidean_vector div{v1};
			return (div /= i);
		}

	private:
		int size_;
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<double[]> magnitudes_;
	};

	auto euclidean_norm(euclidean_vector const& v) -> double;
	auto unit(euclidean_vector const& v) -> euclidean_vector;
	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double;

} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
