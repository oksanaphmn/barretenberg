#pragma once
#include "barretenberg/honk/sumcheck/relations/relation_types.hpp"

namespace proof_system::honk::sumcheck {

/**
 * @brief MSM relations that evaluate the Strauss multiscalar multiplication algorithm.
 *
 * @details
 * The Strauss algorithm for a size-k MSM takes scalars/points (a_i, [P_i]) for i = 0 to k-1.
 * The specific algoritm we use is the following:
 *
 * PHASE 1: Precomputation (performed in ecc_wnaf_relation.hpp, ecc_point_table_relation.hpp)
 * Each scalar a_i is split into 4-bit WNAF slices s_{j, i} for j = 0 to 31, and a skew bool skew_i
 * For each point [P_i] a size-16 lookup table of points, T_i, is computed { [-15 P_i], [-13 P_i], ..., [15 P_i] }
 *
 * PHASE 2: MSM evaluation
 * MSM evaluation is split into 32 rounds that operate on an accumulator point [Acc]
 * The first 31 rounds are composed of an ADDITION round and a DOUBLE round.
 * The final 32nd round is composed of an ADDITION round and a SKEW round.
 *
 * ADDITION round (round = j):
 * [Acc] = [Acc] + T_i[a_{i, j}] for all i in [0, ... k-1]
 *
 * DOUBLE round:
 * [Acc] = 16 * [Acc] (four point doublings)
 *
 * SKEW round:
 * If skew_i == 1, [Acc] = [Acc] - [P_i] for all i in [0, ..., k - 1]
 *
 * The relations in ECCVMMSMRelationBase constrain the ADDITION, DOUBLE and SKEW rounds
 * @param evals transformed to `evals + C(extended_edges(X)...)*scaling_factor`
 * @param extended_edges an std::array containing the fully extended Accumulator edges.
 * @param parameters contains beta, gamma, and public_input_delta, ....
 * @param scaling_factor optional term to scale the evaluation before adding to evals.
 */
template <typename FF> class ECCVMMSMRelationBase {
  public:
    // 1 + polynomial degree of this relation
    static constexpr size_t RELATION_LENGTH = 8;

    // blarp... add
    static constexpr size_t LEN_1 = 8; // arithmetic sub-relation
    template <template <size_t...> typename AccumulatorTypesContainer>
    using AccumulatorTypesBase = AccumulatorTypesContainer<LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1,
                                                           LEN_1>;
    /**
     * @brief Expression for the StandardArithmetic gate.
     * @details The relation is defined as C(extended_edges(X)...) =
     *    (q_m * w_r * w_l) + (q_l * w_l) + (q_r * w_r) + (q_o * w_o) + q_c
     *
     * @param evals transformed to `evals + C(extended_edges(X)...)*scaling_factor`
     * @param extended_edges an std::array containing the fully extended Accumulator edges.
     * @param parameters contains beta, gamma, and public_input_delta, ....
     * @param scaling_factor optional term to scale the evaluation before adding to evals.
     */
    template <typename AccumulatorTypes>
    void add_edge_contribution_impl(typename AccumulatorTypes::Accumulators& accumulator,
                                    const auto& extended_edges,
                                    const RelationParameters<FF>& /*unused*/,
                                    const FF& scaling_factor) const;
};

template <typename FF> using ECCVMMSMRelation = RelationWrapper<FF, ECCVMMSMRelationBase>;

} // namespace proof_system::honk::sumcheck