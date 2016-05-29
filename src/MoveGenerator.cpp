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

#include <cstring>

#include "Constants.hpp"
#include "MoveGenerator.hpp"
#include "PositionMath.hpp"


std::array<std::array<uint64_t, 256>, 64> MoveGenerator::_jumpTable;
std::array<std::array<uint64_t, 64>, 64> MoveGenerator::_emptyMaskTable;
std::array<std::array<uint64_t, 256>, 64> MoveGenerator::_opponentRequiredMaskTable;


void MoveGenerator::initialize() {

    std::memset(&_jumpTable, 0, sizeof(_jumpTable));

    for(uint8_t fromSq8x8 = 0; fromSq8x8 < 63; fromSq8x8++) {

        uint64_t fromMask8x8 = mask8x8BySq8x8(fromSq8x8);
        uint8_t row = rowBySq8x8(fromSq8x8);

        if(row == 1) _jumpTable[fromSq8x8][PieceType::WHITE_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, 2, 0);
        _jumpTable[fromSq8x8][PieceType::WHITE_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, 1, -1);
        _jumpTable[fromSq8x8][PieceType::WHITE_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, 1, 0);
        _jumpTable[fromSq8x8][PieceType::WHITE_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, 1, 1);
        _jumpTable[fromSq8x8][PieceType::WHITE_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, -1);
        _jumpTable[fromSq8x8][PieceType::WHITE_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, 1);

        if(row == 6) _jumpTable[fromSq8x8][PieceType::BLACK_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, -2, 0);
        _jumpTable[fromSq8x8][PieceType::BLACK_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, -1, -1);
        _jumpTable[fromSq8x8][PieceType::BLACK_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, -1, 0);
        _jumpTable[fromSq8x8][PieceType::BLACK_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, -1, 1);
        _jumpTable[fromSq8x8][PieceType::BLACK_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, -1);
        _jumpTable[fromSq8x8][PieceType::BLACK_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, 1);

        _jumpTable[fromSq8x8][PieceType::WHITE_KNIGHT] |= addRowsAndColumnsToMask8x8(fromMask8x8, -2, -1);
        _jumpTable[fromSq8x8][PieceType::WHITE_KNIGHT] |= addRowsAndColumnsToMask8x8(fromMask8x8, -2, 1);
        _jumpTable[fromSq8x8][PieceType::WHITE_KNIGHT] |= addRowsAndColumnsToMask8x8(fromMask8x8, -1, -2);
        _jumpTable[fromSq8x8][PieceType::WHITE_KNIGHT] |= addRowsAndColumnsToMask8x8(fromMask8x8, -1, 2);
        _jumpTable[fromSq8x8][PieceType::WHITE_KNIGHT] |= addRowsAndColumnsToMask8x8(fromMask8x8, 1, -2);
        _jumpTable[fromSq8x8][PieceType::WHITE_KNIGHT] |= addRowsAndColumnsToMask8x8(fromMask8x8, 1, 2);
        _jumpTable[fromSq8x8][PieceType::WHITE_KNIGHT] |= addRowsAndColumnsToMask8x8(fromMask8x8, 2, -1);
        _jumpTable[fromSq8x8][PieceType::WHITE_KNIGHT] |= addRowsAndColumnsToMask8x8(fromMask8x8, 2, 1);
        _jumpTable[fromSq8x8][PieceType::BLACK_KNIGHT] = _jumpTable[fromSq8x8][PieceType::WHITE_KNIGHT];

        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, -7, -7);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, -6, -6);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, -5, -5);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, -4, -4);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, -3, -3);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, -2, -2);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, -1, -1);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, -7, 7);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, -6, 6);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, -5, 5);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, -4, 4);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, -3, 3);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, -2, 2);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, -1, 1);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, 7, -7);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, 6, -6);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, 5, -5);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, 4, -4);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, 3, -3);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, 2, -2);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, 1, -1);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, 7, 7);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, 6, 6);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, 5, 5);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, 4, 4);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, 3, 3);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, 2, 2);
        _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP] |= addRowsAndColumnsToMask8x8(fromMask8x8, 1, 1);
        _jumpTable[fromSq8x8][PieceType::BLACK_BISHOP] = _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP];

        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, -1, 0);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, -2, 0);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, -3, 0);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, -4, 0);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, -5, 0);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, -6, 0);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, -7, 0);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, -1);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, -2);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, -3);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, -4);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, -5);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, -6);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, -7);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, 1);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, 2);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, 3);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, 4);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, 5);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, 6);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, 7);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 1, 0);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 2, 0);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 3, 0);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 4, 0);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 5, 0);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 6, 0);
        _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] |= addRowsAndColumnsToMask8x8(fromMask8x8, 7, 0);
        _jumpTable[fromSq8x8][PieceType::BLACK_ROOK] = _jumpTable[fromSq8x8][PieceType::WHITE_ROOK];

        _jumpTable[fromSq8x8][PieceType::WHITE_QUEEN] = _jumpTable[fromSq8x8][PieceType::WHITE_ROOK] | _jumpTable[fromSq8x8][PieceType::WHITE_BISHOP];
        _jumpTable[fromSq8x8][PieceType::BLACK_QUEEN] = _jumpTable[fromSq8x8][PieceType::WHITE_QUEEN];

        _jumpTable[fromSq8x8][PieceType::WHITE_KING] |= addRowsAndColumnsToMask8x8(fromMask8x8, -1, -1);
        _jumpTable[fromSq8x8][PieceType::WHITE_KING] |= addRowsAndColumnsToMask8x8(fromMask8x8, -1, 0);
        _jumpTable[fromSq8x8][PieceType::WHITE_KING] |= addRowsAndColumnsToMask8x8(fromMask8x8, -1, 1);
        _jumpTable[fromSq8x8][PieceType::WHITE_KING] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, -1);
        _jumpTable[fromSq8x8][PieceType::WHITE_KING] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, 1);
        _jumpTable[fromSq8x8][PieceType::WHITE_KING] |= addRowsAndColumnsToMask8x8(fromMask8x8, 1, -1);
        _jumpTable[fromSq8x8][PieceType::WHITE_KING] |= addRowsAndColumnsToMask8x8(fromMask8x8, 1, 0);
        _jumpTable[fromSq8x8][PieceType::WHITE_KING] |= addRowsAndColumnsToMask8x8(fromMask8x8, 1, 1);
        _jumpTable[fromSq8x8][PieceType::BLACK_KING] = _jumpTable[fromSq8x8][PieceType::WHITE_KING];
    }


    std::memset(&_emptyMaskTable, 0, sizeof(_emptyMaskTable));

    for(uint8_t fromSq0x88 = 0; fromSq0x88 < 120; fromSq0x88++) {

        uint8_t fromSq8x8 = sq8x8BySq0x88(fromSq0x88);

        // north
        for(uint8_t toSq0x88 = fromSq0x88 + 32; sq0x88Valid(toSq0x88); toSq0x88 += 16) {

            uint8_t toSq8x8 = sq8x8BySq0x88(toSq0x88);
            uint8_t lastToSq8x8 = sq8x8BySq0x88(toSq0x88 - 16);

            _emptyMaskTable[fromSq8x8][toSq8x8] = _emptyMaskTable[fromSq8x8][lastToSq8x8] | mask8x8BySq0x88(toSq0x88 - 16);
        }

        // north-east
        for(uint8_t toSq0x88 = fromSq0x88 + 34; sq0x88Valid(toSq0x88); toSq0x88 += 17) {

            uint8_t toSq8x8 = sq8x8BySq0x88(toSq0x88);
            uint8_t lastToSq8x8 = sq8x8BySq0x88(toSq0x88 - 17);

            _emptyMaskTable[fromSq8x8][toSq8x8] = _emptyMaskTable[fromSq8x8][lastToSq8x8] | mask8x8BySq0x88(toSq0x88 - 17);
        }

        // east
        for(uint8_t toSq0x88 = fromSq0x88 + 2; sq0x88Valid(toSq0x88); toSq0x88 += 1) {

            uint8_t toSq8x8 = sq8x8BySq0x88(toSq0x88);
            uint8_t lastToSq8x8 = sq8x8BySq0x88(toSq0x88 - 1);

            _emptyMaskTable[fromSq8x8][toSq8x8] = _emptyMaskTable[fromSq8x8][lastToSq8x8] | mask8x8BySq0x88(toSq0x88 - 1);
        }

        // south-east
        for(uint8_t toSq0x88 = fromSq0x88 - 30; sq0x88Valid(toSq0x88); toSq0x88 -= 15) {

            uint8_t toSq8x8 = sq8x8BySq0x88(toSq0x88);
            uint8_t lastToSq8x8 = sq8x8BySq0x88(toSq0x88 + 15);

            _emptyMaskTable[fromSq8x8][toSq8x8] = _emptyMaskTable[fromSq8x8][lastToSq8x8] | mask8x8BySq0x88(toSq0x88 + 15);
        }

        // south
        for(uint8_t toSq0x88 = fromSq0x88 - 32; sq0x88Valid(toSq0x88); toSq0x88 -= 16) {

            uint8_t toSq8x8 = sq8x8BySq0x88(toSq0x88);
            uint8_t lastToSq8x8 = sq8x8BySq0x88(toSq0x88 + 16);

            _emptyMaskTable[fromSq8x8][toSq8x8] = _emptyMaskTable[fromSq8x8][lastToSq8x8] | mask8x8BySq0x88(toSq0x88 + 16);
        }

        // south-west
        for(uint8_t toSq0x88 = fromSq0x88 - 34; sq0x88Valid(toSq0x88); toSq0x88 -= 17) {

            uint8_t toSq8x8 = sq8x8BySq0x88(toSq0x88);
            uint8_t lastToSq8x8 = sq8x8BySq0x88(toSq0x88 + 17);

            _emptyMaskTable[fromSq8x8][toSq8x8] = _emptyMaskTable[fromSq8x8][lastToSq8x8] | mask8x8BySq0x88(toSq0x88 + 17);
        }

        // west
        for(uint8_t toSq0x88 = fromSq0x88 - 2; sq0x88Valid(toSq0x88); toSq0x88 -= 1) {

            uint8_t toSq8x8 = sq8x8BySq0x88(toSq0x88);
            uint8_t lastToSq8x8 = sq8x8BySq0x88(toSq0x88 + 1);

            _emptyMaskTable[fromSq8x8][toSq8x8] = _emptyMaskTable[fromSq8x8][lastToSq8x8] | mask8x8BySq0x88(toSq0x88 + 1);
        }

        // north-west
        for(uint8_t toSq0x88 = fromSq0x88 + 30; sq0x88Valid(toSq0x88); toSq0x88 += 15) {

            uint8_t toSq8x8 = sq8x8BySq0x88(toSq0x88);
            uint8_t lastToSq8x8 = sq8x8BySq0x88(toSq0x88 - 15);

            _emptyMaskTable[fromSq8x8][toSq8x8] = _emptyMaskTable[fromSq8x8][lastToSq8x8] | mask8x8BySq0x88(toSq0x88 - 15);
        }


        // jump to next row if in last column
        fromSq0x88 += ((fromSq0x88 + 1) & uint8_t(8));
    }


    std::memset(&_opponentRequiredMaskTable, 0, sizeof(_opponentRequiredMaskTable));

    for(uint8_t fromSq8x8 = 0; fromSq8x8 < 63; fromSq8x8++) {

        uint64_t fromMask8x8 = mask8x8BySq8x8(fromSq8x8);

        _opponentRequiredMaskTable[fromSq8x8][PieceType::WHITE_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, 1, -1);
        _opponentRequiredMaskTable[fromSq8x8][PieceType::WHITE_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, 1, 1);
        _opponentRequiredMaskTable[fromSq8x8][PieceType::WHITE_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, -1);
        _opponentRequiredMaskTable[fromSq8x8][PieceType::WHITE_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, 1);

        _opponentRequiredMaskTable[fromSq8x8][PieceType::BLACK_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, -1, -1);
        _opponentRequiredMaskTable[fromSq8x8][PieceType::BLACK_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, -1, 1);
        _opponentRequiredMaskTable[fromSq8x8][PieceType::BLACK_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, -1);
        _opponentRequiredMaskTable[fromSq8x8][PieceType::BLACK_PAWN] |= addRowsAndColumnsToMask8x8(fromMask8x8, 0, 1);
    }
}