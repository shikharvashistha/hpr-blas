// matrix_utils.hpp :  include file containing templated utilities to work with matrices
//
// Copyright (C) 2017-2018 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

namespace sw {
	namespace hprblas {




	}; // namespace blas

}; // namespace sw

namespace mtl {

	namespace mat {

		// fill a dense MTL matrix with random values between (0, 1)
		template <typename Matrix>
		void rand(Matrix& A)
		{
			// Use random_device to generate a seed for Mersenne twister engine.
			std::random_device rd{};
			// Use Mersenne twister engine to generate pseudo-random numbers.
			std::mt19937 engine{ rd() };
			// "Filter" MT engine's output to generate pseudo-random double values,
			// **uniformly distributed** on the closed interval [0, 1].
			// (Note that the range is [inclusive, inclusive].)
			std::uniform_real_distribution<double> dist{ 0.0, 1.0 };
			// Pattern to generate pseudo-random number.
			// double rnd_value = dist(engine);

			typedef typename Collection<Matrix>::value_type    value_type;
			typedef typename Collection<Matrix>::size_type     size_type;

			// inserters add to the elements, so we need to set the value to 0 before we begin
			// A = 0.0;
			{ // extra block unfortunately needed for VS2013
				// Create inserter for matrix m
				inserter<Matrix> ins(A, num_cols(A));

				// generate and insert random values in A
				for (size_type r = 0; r < num_rows(A); r++) {
					for (size_type c = 0; c < num_cols(A); c++) {
						ins[r][c] << value_type(dist(engine));
					}
				}
				// Destructor of ins sets final state of m
			}
		}
	};
};