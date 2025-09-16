#ifndef PAULISTA_SPARSE_HPP__
#define PAULISTA_SPARSE_HPP__

#include "paulista-stiffness.hpp"
#include <vector>
#include <algorithm>
#include <map>

namespace paulista {
namespace sparse {
    using Column = std::vector<std::size_t>;
    using Row = std::vector<std::size_t>;

    template<typename T>
    struct Matrix {
        static_assert(std::is_floating_point_v<T>, "T must be a floating point type");

        std::size_t         rows;
        std::size_t         cols;
        std::size_t         nnz;
        Column              pointers;
        Row                 indices;
        std::vector<T>      values;

        Matrix(const stiffness::Triplets<T>& triplets, std::size_t rows, std::size_t cols)
            : rows(rows)
            , cols(cols)
            , nnz(0)
        {
            using Entry = std::pair<std::size_t, T>;
            std::vector<std::vector<Entry>> columns(cols);

            for (const stiffness::Triplet<T>& triplet : triplets) {
                if (triplet.row < rows and triplet.col < cols) {
                    columns[triplet.col].emplace_back(triplet.row, triplet.value);

                    if (triplet.row != triplet.col) {
                        columns[triplet.row].emplace_back(triplet.col, triplet.value);
                    }
                }
            }

            pointers.resize(cols + 1);
            pointers[0] = 0;

            for (std::size_t col = 0; col < cols; ++col) {
                std::map<std::size_t, T> merged;

                for (const Entry& entry : columns[col]) {
                    merged[entry.first] += entry.second;
                }

                for (const std::pair<const std::size_t, T>& pair : merged) {
                    if (std::abs(pair.second) > std::numeric_limits<T>::epsilon()) {
                        indices.push_back(pair.first);
                        values.push_back(pair.second);
                    }
                }

                pointers[col + 1] = indices.size();
            }

            nnz = indices.size();
        }
    };

} // namespace sparse
} // namespace paulista

#endif // PAULISTA_SPARSE_HPP__