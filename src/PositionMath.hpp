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
 */


/**
 * The following blocks of functions offer conversions between all used coordinate formats.
 */
uint8_t sq0x88ByRowAndColumn(uint8_t row, uint8_t column);
uint8_t sq0x88ByMask8x8(uint64_t mask8x8);
uint8_t sq0x88BySq8x8(uint8_t sq8x8);

uint8_t sq8x8ByRowAndColumn(uint8_t row, uint8_t column);
uint8_t sq8x8ByMask8x8(uint64_t mask8x8);
uint8_t sq8x8BySq0x88(uint8_t sq0x88);

uint64_t mask8x8ByRowAndColumn(uint8_t row, uint8_t column);
uint64_t mask8x8BySq8x8(uint8_t sq8x8);
uint64_t mask8x8BySq0x88(uint8_t sq0x88);

uint8_t rowByMask8x8(uint64_t mask8x8);
uint8_t rowBySq8x8(uint8_t sq8x8);
uint8_t rowBySq0x88(uint8_t sq0x88);

uint8_t columnByMask8x8(uint64_t mask8x8);
uint8_t columnBySq8x8(uint8_t sq8x8);
uint8_t columnBySq0x88(uint8_t sq0x88);


bool sq0x88Valid(uint8_t sq0x88);
uint8_t sq0x88Direction(uint8_t from, uint8_t to);


uint64_t addRowsAndColumnsToMask8x8(uint64_t mask8x8, int8_t rows, int8_t columns);


std::string algebraicByMask8x8(uint64_t mask8x8);
