/*
 * matrix.h
 *
 *  Created on: Feb 20, 2012
 *      Author: alberto
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <limits>
#include <cmath>
#include <cfloat>

#include <vector>

#include <armadillo>

using namespace arma;
using namespace std;

static mat get_cols(mat X, uvec c) {
	/*
	 * return only column in vector col.
	 * to simulate this:
	 * MATLAB code> a = [1 2 3;4 5 6;7 8 9]
	 * MATLAB code> a(:,[2 3])
	 * .. should return
	 * 				 2     3
     * 	   	   	     5     6
     *               8     9
	 */

	mat Y(X.n_rows, c.n_elem);
	uvec::iterator a = c.begin();
	uvec::iterator b = c.end();
	int l, m=0;
	for(uvec::iterator i=a; i!=b; ++i) {
		l = *i;
		Y.col(m) = X.col(l);
		m++;
	}
	return Y;
}

static mat log(mat A) {
	/*
	 * log function operates element-wise on matrix A
	 */
	mat X(A);
	mat::iterator a = X.begin();
	mat::iterator b = X.end();

	for(mat::iterator i=a; i!=b; ++i) {
		(*i) = log(*i);
	}
	return X;
}

static mat vectorize(mat A) {
	/*
	 * vectorise a matrix (ie. concatenate all the columns or rows)
	 * MATLAB code> M(:)
	 */
	mat B = mat(A);
	B.reshape(B.n_rows*B.n_cols, 1);
	return B;
}

static std::pair<mat,double> normaliseC(mat A) {
	/*
	 * Make the entries of matrix A array sum to 1 and return the normalization constant
	 * in a std::pair<normalized matrix, normalization constant>
	 */
	double z = accu(vectorize(A));
	double s = z + (z==0);		// Set any zeros to one before dividing
								// This is valid, since c=0 => all i. A(i)=0 => the answer should be 0/1=0
	mat M = A / s;
	return std::pair<mat,double>(M, z);
}

static mat normalise(mat A) {
	/*
	 * Make the entries of matrix A array sum to 1
	 */
	std::pair<mat,double> ret = normaliseC(A);
	return ret.first;
}

static mat mk_stochastic(mat T) {
	/*
	 * Ensure the argument is a stochastic matrix, i.e., the sum over the last dimension is 1.
	 * If T is a vector, it will sum to 1 (TODO).
	 * If T is a matrix, each row will sum to 1.
	 * If T is a 3D array, then sum_k T(i,j,k) = 1 for all i,j (TODO).
	 *
	 */
	mat Z = sum(T,1);
	mat S = Z + (Z==0);
	mat norm = repmat(S, 1, T.n_cols);
	T = T / norm;
	return T;
}

static mat multinomial_prob(mat data, mat obsmat) {
	/*
	 * Evaluate pdf of conditional multinomial
	 * Notation: Y = observation (O values), Q = conditioning variable (K values)
	 *
	 * Inputs:
	 *  data(t) = t'th observation - must be an integer in {1,2,...,K}: cannot be 0!
	 *  obsmat(i,o) = Pr(Y(t)=o | Q(t)=i)
	 *
	 * Output:
	 *  B(i,t) = Pr(y(t) | Q(t)=i)
	 *
	 */

	int Q = obsmat.n_rows;
	int T = data.n_elem;
	mat B = zeros(Q,T);

	for (int t = 0; t < T; ++t) {
		if (data(t)>obsmat.n_cols) {
			std::cout << "Index exceeds matrix dimension. data(t):" << data(t) <<" obsmat.n_cols:" << obsmat.n_cols << std::endl;
			//return B;
		}
		else {
			B.col(t) = obsmat.col(data(t)-1);
		}
	}
	return B;
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

template<typename Stream>
void fix_stream(Stream& stream){
    stream.precision(4);
    stream.setf(ios::fixed);
}

template<typename Matrix>
string matrix_to_string(Matrix& m) {
	stringstream ss;
	fix_stream(ss);
	m.save(ss, arma::arma_ascii);
	return ss.str();
}

template<class Matrix>
Matrix matrix_from_string(string s) {
	stringstream ss;
	ss << s;
	Matrix m;
	m.load(ss, arma::arma_ascii);
	return m;
}

#endif /* MATRIX_H_ */
