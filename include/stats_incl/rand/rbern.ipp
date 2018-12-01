/*################################################################################
  ##
  ##   Copyright (C) 2011-2018 Keith O'Hara
  ##
  ##   This file is part of the StatsLib C++ library.
  ##
  ##   Licensed under the Apache License, Version 2.0 (the "License");
  ##   you may not use this file except in compliance with the License.
  ##   You may obtain a copy of the License at
  ##
  ##       http://www.apache.org/licenses/LICENSE-2.0
  ##
  ##   Unless required by applicable law or agreed to in writing, software
  ##   distributed under the License is distributed on an "AS IS" BASIS,
  ##   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  ##   See the License for the specific language governing permissions and
  ##   limitations under the License.
  ##
  ################################################################################*/

/*
 * Sample from a Bernoulli distribution
 */

//
// scalar ouput

/**
 * @brief Random sampling function for the Bernoulli distribution
 *
 * @param prob_par the probability parameter, a real-valued input.
 * @param engine a random engine, passed by reference.
 *
 * @return a pseudo-random draw from the Bernoulli distribution.
 *
 * Example:
 * \code{.cpp}
 * stats::rand_engine_t engine(1776);
 * stats::rbern(0.7,engine);
 * \endcode
 */

template<typename T>
statslib_inline
return_t<T> 
rbern(const T prob_par, rand_engine_t& engine)
{
    return( !internal::bern_sanity_check(prob_par) ? \
                STLIM<T>::quiet_NaN() :
            //
            runif(T(0),T(1),engine) <= prob_par );
}

/**
 * @brief Random sampling function for the Bernoulli distribution
 *
 * @param prob_par the probability parameter, a real-valued input.
 * @param seed_val initialize the random engine with a non-negative integral-valued seed.
 *
 * @return a pseudo-random draw from the Bernoulli distribution.
 *
 * Example:
 * \code{.cpp}
 * stats::rbern(0.7,1776);
 * \endcode
 */

template<typename T>
statslib_inline
return_t<T>
rbern(const T prob_par, const ullint_t seed_val)
{
    rand_engine_t engine(seed_val);
    return rbern(prob_par,engine);
}

//
// vector/matrix output

namespace internal
{

template<typename T1, typename rT>
statslib_inline
void
rbern_vec(const T1 prob_par, rT* __stats_pointer_settings__ vals_out, const ullint_t num_elem)
{
    RAND_DIST_FN_VEC(rbern,vals_out,num_elem,prob_par);
}

#ifdef STATS_ENABLE_MATRIX_FEATURES
template<typename mT, typename T1, typename not_blaze_mat<mT>::type*>
statslib_inline
mT
rbern_mat_check(mT& mat_out const T1 prob_par)
{
    GEN_MAT_RAND_FN(rbern_vec,prob_par);
}
#endif

#ifdef STATS_USE_BLAZE
template<typename eT, typename T1, typename T2, typename rT, bool To>
statslib_inline
BlazeMat<rT,To>
rbern_mat_check(BlazeMat<eT,To>& X, const T1 prob_par)
{
    BLAZE_RAND_DIST_FN(rbern,vals_out,num_elem,prob_par);
}
#endif

}

/**
 * @brief Random matrix sampling function for the Bernoulli distribution
 *
 * @param n the number of output rows
 * @param k the number of output columns
 * @param prob_par the probability parameter, a real-valued input.
 *
 * @return a matrix of pseudo-random draws from the Bernoulli distribution.
 *
 * Example:
 * \code{.cpp}
 * stats::rbern<arma::mat>(5,4,0.7);
 * \endcode
 *
 * @note This function requires template instantiation, and accepts Armadillo, Blaze, and Eigen dense matrices as output types.
 */

#ifdef STATS_ENABLE_MATRIX_FEATURES
template<typename mT, typename T1>
statslib_inline
mT
rbern(const ullint_t n, const ullint_t k, const T1 prob_par)
{
    GEN_MAT_RAND_FN(rbern_vec,prob_par);
}
#endif