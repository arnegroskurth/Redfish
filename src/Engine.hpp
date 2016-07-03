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

#include <limits>
#include <map>

#include "Board.hpp"
#include "Constants.hpp"
#include "Evaluation.hpp"
#include "Move.hpp"
#include "SortedMoveGenerator.hpp"


template<bool useLookupTable = true>
class Engine {

protected:

    Evaluation _evaluation;

    Board &_initialBoard;
    uint8_t _initialDepth;

    Move _bestMove;

    std::map<uint64_t, int64_t> _knownPositions;


    /**
     * Initial call to finding
     */
    FORCE_INLINE void findBestMove() {

        if(_initialBoard.whiteToMove()) {

            max(_initialBoard, _initialDepth, std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max());
        }
        else {

            min(_initialBoard, _initialDepth, std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max());
        }
    }


    /**
     * Alpha-Beta-Pruning
     */
    HOT int64_t max(Board &currentBoard, uint8_t depth, int64_t alpha, int64_t beta) {

        SortedMoveGenerator moveGenerator;
        Board nextBoard;
        auto maxValue = alpha;

        if(depth == 0 || moveGenerator.generateMoves(currentBoard) == 0) {

            return _evaluation.evaluate(currentBoard);
        }

        while(!moveGenerator.empty()) {

            new (&nextBoard) Board(currentBoard);
            nextBoard.applyMove(*moveGenerator);


            int64_t minValue;

            if(useLookupTable) {

                auto hash = nextBoard.getHash() ^ static_cast<uint64_t>(depth);
                auto it = _knownPositions.find(hash);

                if(it == _knownPositions.end()) {

                    minValue = min(nextBoard, depth - 1, maxValue, beta);

                    _knownPositions[hash] = minValue;
                }
                else {

                    minValue = it->second;
                }
            }

            else {

                minValue = min(nextBoard, depth - 1, maxValue, beta);
            }


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


    HOT int64_t min(Board &currentBoard, uint8_t depth, int64_t alpha, int64_t beta) {

        SortedMoveGenerator moveGenerator;
        Board nextBoard;
        auto minValue = beta;

        if(depth == 0 || moveGenerator.generateMoves(currentBoard) == 0) {

            return _evaluation.evaluate(currentBoard);
        }

        while(!moveGenerator.empty()) {

            new (&nextBoard) Board(currentBoard);
            nextBoard.applyMove(*moveGenerator);


            int64_t maxValue;

            if(useLookupTable) {

                auto hash = nextBoard.getHash() ^ static_cast<uint64_t>(depth);
                auto it = _knownPositions.find(hash);

                if(it == _knownPositions.end()) {

                    maxValue = max(nextBoard, depth - 1, alpha, minValue);

                    _knownPositions[hash] = maxValue;
                }
                else {

                    maxValue = it->second;
                }
            }

            else {

                maxValue = max(nextBoard, depth - 1, alpha, minValue);
            }


            if(maxValue < minValue) {

                minValue = maxValue;

                // alpha cutoff
                if(minValue <= alpha) break;

                if(depth == _initialDepth) {

                    new (&_bestMove) Move(*moveGenerator);
                }
            }

            ++moveGenerator;
        }

        return minValue;
    }


public:

    Engine(Board &initialBoard, uint8_t initialDepth) : _initialBoard(initialBoard), _initialDepth(initialDepth) {}


    Move &getBestMove() {

        findBestMove();

        return _bestMove;
    }
};