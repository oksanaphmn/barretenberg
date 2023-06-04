#pragma once
#include "barretenberg/ecc/curves/bn254/g1.hpp"
#include "barretenberg/common/mem.hpp"
#include "barretenberg/common/thread.hpp"
#include <memory>

namespace barretenberg {
namespace scalar_multiplication {

inline size_t point_table_size(size_t num_points)
{
    const size_t num_threads = get_num_cpus_pow2();
    const size_t prefetch_overflow = 16 * num_threads;

    return 2 * num_points + prefetch_overflow;
}

inline size_t point_table_buf_size(size_t num_points)
{
    return sizeof(g1::affine_element) * point_table_size(num_points);
}

inline std::shared_ptr<g1::affine_element[]> point_table_alloc(size_t num_points)
{
    return std::static_pointer_cast<g1::affine_element[]>(get_mem_slab(point_table_buf_size(num_points)));
}

} // namespace scalar_multiplication
} // namespace barretenberg
