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

#include <algorithm>
#include <iterator>

#include "Move.hpp"
#include "MoveGenerator.hpp"


class SortedMoveGenerator : public MoveGenerator {

public:

    FORCE_INLINE TMovesArray::size_type generateMoves(Board &board) {

        MoveGenerator::generateMoves(board);

        std::sort(_moves.begin(), std::next(_moves.begin(), _totalMoveCount), [](const Move &move1, const Move &move2) {

            return move1.capturedPieceType < move2.capturedPieceType;
        });

        return _totalMoveCount;
    }
};