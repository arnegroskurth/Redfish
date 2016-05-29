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
 *
 * Todo:
 *  - Implement/compare NegaScout/MTD-f search algorithms
 *  - Use transposition table
 */

#pragma once

#include "Evaluation.hpp"
#include "Move.hpp"
#include "MoveGenerator.hpp"


class Engine {

protected:

    Evaluation evaluation;

    Board *_initialBoard;
    uint8_t _initialDepth;

    Move _bestMove;


    void findBestMove();

    /**
     * Alpha-Beta-Pruning
     */
    int64_t max(Board *currentBoard, uint8_t depth, int64_t alpha, int64_t beta);
    int64_t min(Board *currentBoard, uint8_t depth, int64_t alpha, int64_t beta);


public:

    Engine(Board *initialBoard, uint8_t initialDepth) {

        _initialBoard = initialBoard;
        _initialDepth = initialDepth;

        findBestMove();
    }


    Move &getBestMove() {

        return _bestMove;
    }
};