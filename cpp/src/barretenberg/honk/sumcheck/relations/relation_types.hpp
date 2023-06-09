#pragma once
#include <array>
#include <tuple>

#include "../polynomials/univariate.hpp"
#include "relation_parameters.hpp"

namespace proof_system::honk::sumcheck {

/**
 * @brief The templates defined herein facilitate sharing the relation arithmetic between the prover and the verifier.
 *
 * The sumcheck prover and verifier accumulate the contributions from each relation (really, each sub-relation) into,
 * respectively, Univariates and individual field elements. When performing relation arithmetic on Univariates, we
 * introduce UnivariateViews to reduce full length Univariates to the minimum required length and to avoid unnecessary
 * copies.
 *
 * To share the relation arithmetic, we introduce simple structs that specify two types: Accumulators and
 * AccumulatorViews. For the prover, who accumulates Univariates, these are respectively std::tuple<Univariate> and
 * std::tuple<UnivariateView>. For the verifier, who accumulates FFs, both types are simply aliases for std::array<FF>
 * (since no "view" type is necessary). The containers std::tuple and std::array are needed to accommodate multiple
 * sub-relations within each relation, where, for efficiency, each sub-relation has its own specified degree.
 */

// Helper struct to allow passing an arbitrary collection of lengths to the AccumulatorTypes
template <size_t... Values> struct LengthsWrapper {};

// Forward declarations of AccumulatorTypesHelpers
template <typename FF, typename LengthsWrapper> struct UnivariateAccumulatorTypesHelper;
template <typename FF, typename LengthsWrapper> struct ValueAccumulatorTypesHelper;

// Helper to define value (FF) based accumulator types
template <typename FF, size_t... Values> struct ValueAccumulatorTypesHelper<FF, LengthsWrapper<Values...>> {
    using Accumulators = std::array<FF, sizeof...(Values)>;
    using AccumulatorViews = std::array<FF, sizeof...(Values)>; // there is no "view" type here
};

// Accumulator types for values (FFs)
template <typename FF, typename Lengths> using ValueAccumulatorTypes = ValueAccumulatorTypesHelper<FF, Lengths>;

// Helper to define Univariate based accumulator types
template <typename FF, size_t... Values> struct UnivariateAccumulatorTypesHelper<FF, LengthsWrapper<Values...>> {
    using Accumulators = std::tuple<Univariate<FF, Values>...>;
    using AccumulatorViews = std::tuple<UnivariateView<FF, Values>...>;
};

// Accumulator types for Univariates
template <typename FF, typename Lengths>
using UnivariateAccumulatorTypes = UnivariateAccumulatorTypesHelper<FF, Lengths>;

} // namespace proof_system::honk::sumcheck