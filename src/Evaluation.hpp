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

#include <cstdlib>

#include "Board.hpp"
#include "Constants.hpp"


class Evaluation {

public:

    /**
     * Evaluates a given board state.
     * Positive values indicate a benefit for white, negative for black.
     */
    FORCE_INLINE int64_t evaluate(Board &board) {

        int64_t ret = 0;

        ret += 1000 * (SET_BITS_64(board.getWhiteKingMask()) - SET_BITS_64(board.getBlackKingMask()));
        ret += 9 * (SET_BITS_64(board.getWhiteQueenMask()) - SET_BITS_64(board.getBlackQueenMask()));
        ret += 5 * (SET_BITS_64(board.getWhiteRooksMask()) - SET_BITS_64(board.getBlackRooksMask()));
        ret += 4 * (SET_BITS_64(board.getWhiteKnightsMask()) - SET_BITS_64(board.getBlackKnightsMask()));
        ret += 3 * (SET_BITS_64(board.getWhiteBishopsMask()) - SET_BITS_64(board.getBlackBishopsMask()));
        ret += 1 * (SET_BITS_64(board.getWhitePawnsMask()) - SET_BITS_64(board.getBlackPawnsMask()));

        return ret;
    }
};