// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "comp6771/euclidean_vector.hpp"

namespace comp6771 {
	// Implement solution here
	// constructor
	euclidean_vector::euclidean_vector() noexcept {
		this->size_ = 1;
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(this->size_));
		this->magnitudes_[0] = 0.0;
	}

	euclidean_vector::euclidean_vector(int size) noexcept {
		this->size_ = size;
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(this->size_));
		for (auto i = 0; i < this->size_; i++) {
			this->magnitudes_[static_cast<size_t>(i)] = 0.0;
		}
	}

	euclidean_vector::euclidean_vector(int size, double value) noexcept {
		this->size_ = size;
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(this->size_));
		for (auto i = 0; i < this->size_; i++) {
			this->magnitudes_[static_cast<size_t>(i)] = value;
		}
	}

	euclidean_vector::euclidean_vector(std::vector<double>::const_iterator begin,
	                                   std::vector<double>::const_iterator end) noexcept {
		auto temp = begin;
		this->size_ = 0;
		while (temp != end) {
			this->size_++;
			temp++;
		}
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(this->size_));
		auto i = 0;
		while (begin != end) {
			this->magnitudes_[static_cast<size_t>(i)] = *begin;
			i++;
			begin++;
		}
	}

	euclidean_vector::euclidean_vector(std::initializer_list<double> l) noexcept {
		this->size_ = static_cast<int>(l.size());
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(this->size_));
		auto temp = 0;
		for (auto i : l) {
			this->magnitudes_[static_cast<size_t>(temp)] = i;
			temp++;
		}
	}

	euclidean_vector::euclidean_vector(const euclidean_vector& old) noexcept {
		this->size_ = old.size_;
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(this->size_));
		for (auto i = 0; i < this->size_; i++) {
			this->magnitudes_[static_cast<size_t>(i)] = old.magnitudes_[static_cast<size_t>(i)];
		}
	}

	// NOLINTNEXTLINE(modernize-avoid-c-arrays)
	euclidean_vector::euclidean_vector(euclidean_vector&& old) noexcept
	: size_{old.size_}
	, magnitudes_{std::move(old.magnitudes_)} {
		old.size_ = 0;
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		old.magnitudes_ = std::make_unique<double[]>(0);
	}

	// operator overloads
	auto euclidean_vector::operator=(const euclidean_vector& old) noexcept -> euclidean_vector& {
		auto copy = comp6771::euclidean_vector(old);
		std::swap(*this, copy);
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		// this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(this->size_));
		// for (auto i = 0; i < this->size_; i++) {
		//	this->magnitudes_[static_cast<size_t>(i)] = old.magnitudes_[static_cast<size_t>(i)];
		//}
		return *this;
	}

	auto euclidean_vector::operator=(euclidean_vector&& old) noexcept -> euclidean_vector& {
		this->size_ = old.size_;
		this->magnitudes_ = std::move(old.magnitudes_);
		old.size_ = 0;
		return *this;
	}

	auto euclidean_vector::operator+=(const euclidean_vector& v) -> euclidean_vector& {
		if (this->size_ != v.size_) {
			throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(this->size_)
			                             + ") and RHS(" + std::to_string(v.size_) + ") do not match");
		}

		for (auto i = 0; i < this->dimensions(); i++) {
			this->magnitudes_[static_cast<size_t>(i)] += v.magnitudes_[static_cast<size_t>(i)];
		}
		return *this;
	}

	auto euclidean_vector::operator-=(const euclidean_vector& v) -> euclidean_vector& {
		if (this->size_ != v.size_) {
			throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(this->size_)
			                             + ") and RHS(" + std::to_string(v.size_) + ") do not match");
		}

		for (auto i = 0; i < this->dimensions(); i++) {
			this->magnitudes_[static_cast<size_t>(i)] -= v.magnitudes_[static_cast<size_t>(i)];
		}
		return *this;
	}

	auto euclidean_vector::operator*=(const double mul) -> euclidean_vector& {
		for (auto i = 0; i < this->dimensions(); i++) {
			this->magnitudes_[static_cast<size_t>(i)] *= mul;
		}
		return *this;
	}

	auto euclidean_vector::operator/=(const double div) -> euclidean_vector& {
		if (div == 0) {
			throw euclidean_vector_error("Invalid vector division by 0");
		}

		for (auto i = 0; i < this->dimensions(); i++) {
			this->magnitudes_[static_cast<size_t>(i)] /= div;
		}
		return *this;
	}

	//+
	auto euclidean_vector::operator+() const -> euclidean_vector {
		auto new_vec = euclidean_vector(*this);
		return new_vec;
	}

	//-
	auto euclidean_vector::operator-() const -> euclidean_vector {
		euclidean_vector new_vec(this->size_);
		for (auto i = 0; i < this->size_; i++) {
			new_vec.magnitudes_[static_cast<size_t>(i)] = -(this->magnitudes_[static_cast<size_t>(i)]);
		}
		return new_vec;
	}
	//[]
	auto euclidean_vector::operator[](int index) -> double& {
		assert(index >= 0 && index < this->size_);
		return this->magnitudes_[static_cast<size_t>(index)];
	}

	auto euclidean_vector::operator[](int index) const -> double {
		assert(index >= 0 && index < this->size_);
		return this->magnitudes_[static_cast<size_t>(index)];
	}

	euclidean_vector::operator std::vector<double>() {
		std::vector<double> new_vec(static_cast<size_t>(this->size_), 0.0);
		for (auto i = 0; i < this->size_; ++i) {
			new_vec.push_back(this->magnitudes_[static_cast<size_t>(i)]);
		}
		return new_vec;
	}

	euclidean_vector::operator std::list<double>() {
		std::list<double> l;
		for (int i = 0; i < this->size_; ++i) {
			l.push_back(this->magnitudes_[static_cast<size_t>(i)]);
		}
		return l;
	}

	// member function
	auto euclidean_vector::at(int index) const -> double {
		if (index < 0 || index >= this->size_) {
			throw euclidean_vector_error("Index " + std::to_string(index)
			                             + " is not valid for this euclidean_vector object");
		}
		return this->magnitudes_[static_cast<size_t>(index)];
	}

	auto euclidean_vector::at(int index) -> double& {
		if (index < 0 || index >= this->size_) {
			throw euclidean_vector_error("Index " + std::to_string(index)
			                             + " is not valid for this euclidean_vector object");
		}
		return this->magnitudes_[static_cast<size_t>(index)];
	}

	auto euclidean_vector::dimensions() const -> int {
		return this->size_;
	}

	auto euclidean_norm(euclidean_vector const& v) -> double {
		if (v.dimensions() == 0) {
			throw euclidean_vector_error("euclidean_vector with no dimensions does not have a norm");
		}
		auto norm = 0.0;
		for (auto i = 0; i < v.dimensions(); i++) {
			norm += pow(v.at(i), 2);
		}
		return sqrt(norm);
	}

	auto unit(euclidean_vector const& v) -> euclidean_vector {
		if (v.dimensions() == 0) {
			throw euclidean_vector_error("euclidean_vector with no dimensions does not have a unit "
			                             "vector");
		}
		auto norm = euclidean_norm(v);

		if (norm == 0) {
			throw euclidean_vector_error("euclidean_vector with euclidean normal of 0 does not have a "
			                             "unit vector");
		}
		auto unit_vector = comp6771::euclidean_vector(v);
		for (int i = 0; i < v.dimensions(); i++) {
			unit_vector.at(i) = unit_vector.at(i) / norm;
		}
		return unit_vector;
	}

	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double {
		if (x.dimensions() != y.dimensions()) {
			throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(x.dimensions())
			                             + ") and RHS(" + std::to_string(y.dimensions())
			                             + ") do not match");
		}
		auto result = 0.0;
		for (auto i = 0; i < x.dimensions(); i++) {
			result += x.at(i) * y.at(i);
		}
		return result;
	}

} // namespace comp6771
