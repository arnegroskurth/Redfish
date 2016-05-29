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

#include <limits>

#include "Engine.hpp"


void Engine::findBestMove() {

    max(_initialBoard, _initialDepth, std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max());
}


int64_t Engine::max(Board *currentBoard, uint8_t depth, int64_t alpha, int64_t beta) {

    MoveGenerator moveGenerator;
    Board nextBoard;
    auto maxValue = alpha;

    if(depth == 0 || moveGenerator.generateMoves(currentBoard) == 0) {

        return evaluation.evaluate(currentBoard);
    }

    while(!moveGenerator.empty()) {

        new (&nextBoard) Board(*currentBoard);
        nextBoard.applyMove(*moveGenerator);

        auto minValue = min(&nextBoard, depth - 1, maxValue, beta);

        if(minValue > maxValue) {

            maxValue = minValue;

            // beta cutoff
            if(maxValue >= beta) break;

            if(depth == _initialDepth) {

                new (&_bestMove) Move(*moveGenerator);
            }
        }

        ++moveGenerator;
    }

    return maxValue;
}


int64_t Engine::min(Board *currentBoard, uint8_t depth, int64_t alpha, int64_t beta) {

    MoveGenerator moveGenerator;
    Board nextBoard;
    auto minValue = beta;

    if(depth == 0 || moveGenerator.generateMoves(currentBoard) == 0) {

        return evaluation.evaluate(currentBoard);
    }

    while(!moveGenerator.empty()) {

        new (&nextBoard) Board(*currentBoard);
        nextBoard.applyMove(*moveGenerator);

        auto maxValue = max(&nextBoard, depth - 1, alpha, minValue);

        if(maxValue < minValue) {

            minValue = maxValue;

            // alpha cutoff
            if(minValue <= alpha) break;
        }

        ++moveGenerator;
    }

    return minValue;
}