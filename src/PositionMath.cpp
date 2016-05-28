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

#include "Constants.hpp"
#include "PositionMath.hpp"


/**
 * Todo:
 *  - lookup tables
 *  - force_inline
 */


uint8_t sq0x88ByRowAndColumn(uint8_t row, uint8_t column) {

    return 16 * row + column;
}

uint8_t sq0x88ByMask8x8(uint64_t mask8x8) {

    return __builtin_ffsll(mask8x8) - 1;
}

uint8_t sq0x88BySq8x8(uint8_t sq8x8) {

    return sq8x8 + (sq8x8 & ~7);
}


uint8_t sq8x8ByRowAndColumn(uint8_t row, uint8_t column) {

    return 8 * row + column;
}

uint8_t sq8x8ByMask8x8(uint64_t mask8x8) {

    return __builtin_ffsll(mask8x8) - 1;
}

uint8_t sq8x8BySq0x88(uint8_t sq0x88) {

    return (sq0x88 + (sq0x88 & 7)) >> 1;
}


uint64_t mask8x8ByRowAndColumn(uint8_t row, uint8_t column) {

    return uint64_t(1) << (row * 8 + column);
}

uint64_t mask8x8BySq8x8(uint8_t sq8x8) {

    return uint64_t(1) << sq8x8;
}

uint64_t mask8x8BySq0x88(uint8_t sq0x88) {

    return mask8x8ByRowAndColumn(rowBySq0x88(sq0x88), columnBySq0x88(sq0x88));
}


uint8_t rowByMask8x8(uint64_t mask8x8) {

    return sq8x8ByMask8x8(mask8x8) / 8;
}

uint8_t rowBySq8x8(uint8_t sq8x8) {

    return sq8x8 / 8;
}

uint8_t rowBySq0x88(uint8_t sq0x88) {

    return sq0x88 / 16;
}


uint8_t columnByMask8x8(uint64_t mask8x8) {

    return sq8x8ByMask8x8(mask8x8) % 8;
}

uint8_t columnBySq8x8(uint8_t sq8x8) {

    return sq8x8 % 8;
}

uint8_t columnBySq0x88(uint8_t sq0x88) {

    return sq0x88 % 16;
}


bool sq0x88Valid(uint8_t sq0x88) {

    return !(sq0x88 & 0x88);
}

bool sq0x88Valid64(uint64_t sq0x88) {

    return !(sq0x88 & 0b1111111111111111111111111111111111111111111111111111111110001000);
}

uint8_t sq0x88Diff(uint8_t from, uint8_t to) {

    return 119 + from - to;
}


uint64_t addRowsAndColumnsToMask8x8(uint64_t mask8x8, int8_t rows, int8_t columns) {

    int row = rowByMask8x8(mask8x8) + rows;
    int column = columnByMask8x8(mask8x8) + columns;

    return (row >= 0 && row < 8 && column >= 0 && column < 8) ? mask8x8ByRowAndColumn(uint8_t(row), uint8_t(column)) : 0;
}


std::string algebraicByMask8x8(uint64_t mask8x8) {

    return mask8x8 ? (std::string(columnCharacterByIndex[columnByMask8x8(mask8x8)]) + std::string(rowCharacterByIndex[rowByMask8x8(mask8x8)])) : "invalid";
}
