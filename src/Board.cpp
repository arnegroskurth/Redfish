/**
 * Redfish is an open-source chess engine.
 * Copyright (C) 2016 Arne Groskurth
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Board.hpp"

#include <chrono>
#include <cstring>
#include <random>


std::array<std::array<uint64_t, 13>, 64> Board::_hashTable;


void Board::initialize() {

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 randomNumberEngine(seed);

    std::memset(&_hashTable, 0, sizeof(_hashTable));

    for(int i = 0; i < 64; i++) {

        for(int j = 1; j < 13; j++) {

            _hashTable[i][j] = randomNumberEngine();
        }
    }
}