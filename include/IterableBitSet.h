/*
* The following is taken from the serialisation-solver by Bengel and Thimm
* and is subject to the GPL 3.0.
*/ 
#ifndef BITSET_H
#define BITSET_H

#include <vector>
#include <cstdint>

class IterableBitSet {
    public:
        std::vector<uint32_t> _array;
        std::vector<uint8_t> _bitset;

        IterableBitSet() {}

        IterableBitSet(std::vector<uint32_t> array, std::vector<uint8_t> bitset) : _array{ array }, _bitset { bitset } {}

        ~IterableBitSet() {
            _array.clear();
            _bitset.clear();
        }

        void clear() {
            _array.clear();
            _bitset.clear();
        }

};

#endif