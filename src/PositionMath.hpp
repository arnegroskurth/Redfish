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

#pragma once

#include <string>

#include "Constants.hpp"


/**
 * Row- and column indizes increase from a1 to h8.
 *
 * 8x8 board layout:
 *
 *         0   1   2   3   4   5   6   7
 *
 *         a   b   c   d   e   f   g   h
 *       +---+---+---+---+---+---+---+---+
 * 7   8 |056|   |   |   |   |   |   |063|
 *       +---+---+---+---+---+---+---+---+
 * 6   7 |   |   |   |   |   |   |   |   |
 *       +---+---+---+---+---+---+---+---+
 * 5   6 |   |   |   |   |   |   |   |   |
 *       +---+---+---+---+---+---+---+---+
 * 4   5 |   |   |   |   |   |   |   |   |
 *       +---+---+---+---+---+---+---+---+
 * 3   4 |   |   |   |   |   |   |   |   |
 *       +---+---+---+---+---+---+---+---+
 * 2   3 |   |   |   |   |   |   |   |   |
 *       +---+---+---+---+---+---+---+---+
 * 1   2 |008|   |   |   |   |   |   |015|
 *       +---+---+---+---+---+---+---+---+
 * 0   1 |000|   |   |   |   |   |   |007|
 *       +---+---+---+---+---+---+---+---+
 *
 * 0x88 board layout:
 *
 *         0   1   2   3   4   5   6   7
 *
 *         a   b   c   d   e   f   g   h
 *       +---+---+---+---+---+---+---+---+
 * 7   8 |112|   |   |   |   |   |   |119|
 *       +---+---+---+---+---+---+---+---+
 * 6   7 |   |   |   |   |   |   |   |   |
 *       +---+---+---+---+---+---+---+---+
 * 5   6 |   |   |   |   |   |   |   |   |
 *       +---+---+---+---+---+---+---+---+
 * 4   5 |   |   |   |   |   |   |   |   |
 *       +---+---+---+---+---+---+---+---+
 * 3   4 |   |   |   |   |   |   |   |   |
 *       +---+---+---+---+---+---+---+---+
 * 2   3 |   |   |   |   |   |   |   |   |
 *       +---+---+---+---+---+---+---+---+
 * 1   2 |016|   |   |   |   |   |   |023|
 *       +---+---+---+---+---+---+---+---+
 * 0   1 |000|   |   |   |   |   |   |007|
 *       +---+---+---+---+---+---+---+---+
 *
 * Todo:
 *  - lookup tables
 *  - force_inline
 */


/**
 * The following blocks of functions offer conversions between all used coordinate formats.
 */
FORCE_INLINE uint8_t sq0x88ByRowAndColumn(uint8_t row, uint8_t column) {

    return 16 * row + column;
}

FORCE_INLINE uint8_t sq0x88ByMask8x8(uint64_t mask8x8) {

    return __builtin_ffsll(mask8x8) - 1;
}

FORCE_INLINE uint8_t sq0x88BySq8x8(uint8_t sq8x8) {

    return sq8x8 + (sq8x8 & ~7);
}


FORCE_INLINE uint8_t sq8x8ByRowAndColumn(uint8_t row, uint8_t column) {

    return 8 * row + column;
}

FORCE_INLINE uint8_t sq8x8ByMask8x8(uint64_t mask8x8) {

    return __builtin_ffsll(mask8x8) - 1;
}

FORCE_INLINE uint8_t sq8x8BySq0x88(uint8_t sq0x88) {

    return (sq0x88 + (sq0x88 & 7)) >> 1;
}


FORCE_INLINE uint8_t rowByMask8x8(uint64_t mask8x8) {

    return sq8x8ByMask8x8(mask8x8) / 8;
}

FORCE_INLINE uint8_t rowBySq8x8(uint8_t sq8x8) {

    return sq8x8 / 8;
}

FORCE_INLINE uint8_t rowBySq0x88(uint8_t sq0x88) {

    return sq0x88 / 16;
}


FORCE_INLINE uint8_t columnByMask8x8(uint64_t mask8x8) {

    return sq8x8ByMask8x8(mask8x8) % 8;
}

FORCE_INLINE uint8_t columnBySq8x8(uint8_t sq8x8) {

    return sq8x8 % 8;
}

FORCE_INLINE uint8_t columnBySq0x88(uint8_t sq0x88) {

    return sq0x88 % 16;
}


FORCE_INLINE uint64_t mask8x8ByRowAndColumn(uint8_t row, uint8_t column) {

    return uint64_t(1) << (row * 8 + column);
}

FORCE_INLINE uint64_t mask8x8BySq8x8(uint8_t sq8x8) {

    return uint64_t(1) << sq8x8;
}

FORCE_INLINE uint64_t mask8x8BySq0x88(uint8_t sq0x88) {

    return mask8x8ByRowAndColumn(rowBySq0x88(sq0x88), columnBySq0x88(sq0x88));
}


FORCE_INLINE bool sq0x88Valid(uint8_t sq0x88) {

    return !(sq0x88 & 0x88);
}

FORCE_INLINE bool sq0x88Valid64(uint64_t sq0x88) {

    return !(sq0x88 & 0b1111111111111111111111111111111111111111111111111111111110001000);
}

FORCE_INLINE uint8_t sq0x88Diff(uint8_t from, uint8_t to) {

    return 119 + from - to;
}


FORCE_INLINE uint64_t addRowsAndColumnsToMask8x8(uint64_t mask8x8, int8_t rows, int8_t columns) {

    int row = rowByMask8x8(mask8x8) + rows;
    int column = columnByMask8x8(mask8x8) + columns;

    return (row >= 0 && row < 8 && column >= 0 && column < 8) ? mask8x8ByRowAndColumn(uint8_t(row), uint8_t(column)) : 0;
}


FORCE_INLINE std::string algebraicByMask8x8(uint64_t mask8x8) {

    return mask8x8 ? (std::string(columnCharacterByIndex[columnByMask8x8(mask8x8)]) + std::string(rowCharacterByIndex[rowByMask8x8(mask8x8)])) : "invalid";
}