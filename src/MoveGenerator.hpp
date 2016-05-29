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

#include <array>

#include "Board.hpp"
#include "Constants.hpp"
#include "Move.hpp"
#include "PositionMath.hpp"


class MoveGenerator {

protected:

    // 4096 moves is the theoretical maximum number of possible 1-piece moves on a 64*64 board
    // an array instead of a vector is used to avoid branching during boundary-check when appending a move
    typedef std::array<Move, 4096> TMovesArray;


    // board the generation is based on
    Board *_board;

    // generated moves to be made accessible via the streaming interface
    TMovesArray _moves;
    TMovesArray::size_type _totalMoveCount = 0;
    TMovesArray::size_type _currentMove = 0;


    // Pre-generated jump table
    // _jumpTable[fromSq8x8][fromPieceType] - valid targets as mask8x8
    // _emptyMaskTable[fromSq8x8][toSq8x8] - fields that need to be empty as mask8x8
    // _opponentRequiredMaskTable[fromSq8x8][fromPieceType] - fields that need an opponent piece (pawn attacks)
    static std::array<std::array<uint64_t, 256>, 64> _jumpTable;
    static std::array<std::array<uint64_t, 64>, 64> _emptyMaskTable;
    static std::array<std::array<uint64_t, 256>, 64> _opponentRequiredMaskTable;


public:

    /**
     * Pre-generate jump tables.
     */
    static void initialize();


    MoveGenerator() {}
    FORCE_INLINE MoveGenerator(Board *board) {

        generateMoves(board);
    }


    /**
     * Generates all pseudo-legal moves.
     *
     * todo:
     *  - add casteling
     *  - add last-move-check for pawn en-passent captures
     *  - force unroll_loop? (only inner/outer?)
     *  - add piece-traversing version to speed up generation process in end-games
     */
    FORCE_INLINE UNROLL_LOOPS TMovesArray::size_type generateMoves(Board *board) {

        TMovesArray::size_type incrementor;

        _totalMoveCount = 0;
        _currentMove = 0;

        for(uint8_t fromSq8x8 = 0; fromSq8x8 < 63; fromSq8x8++) {

            PieceType fromPieceType = board->getPieceBySq8x8(fromSq8x8);

            for(uint8_t toSq8x8 = 0; toSq8x8 < 63; toSq8x8++) {

                PieceType toPieceType = board->getPieceBySq8x8(toSq8x8);
                uint64_t toMask8x8 = mask8x8BySq8x8(toSq8x8);


                // write current move
                _moves[_totalMoveCount].movingPieceType = fromPieceType;
                _moves[_totalMoveCount].capturedPieceType = toPieceType;
                _moves[_totalMoveCount].fromSq0x88 = sq0x88BySq8x8(fromSq8x8);
                _moves[_totalMoveCount].toSq0x88 = sq0x88BySq8x8(toSq8x8);


                // test for validity
                // current move is valid as default
                // subsequent tests might change this to zero resulting in this move being overwritten
                incrementor = 1;


                // cannot be the same field (todo: needed??)
                incrementor = incrementor >> (fromSq8x8 == toSq8x8);

                // fromPieceType has to be of current player
                incrementor = incrementor >> (board->playerToMove() != GET_PLAYER(fromPieceType));

                // targetPiece is not of current player
                incrementor = incrementor >> (board->playerToMove() == GET_PLAYER(toPieceType));

                // as valid move in jump tables
                incrementor = incrementor >> HAS_SET_BITS_64((~_jumpTable[fromSq8x8][fromPieceType]) & toMask8x8);
                incrementor = incrementor >> HAS_SET_BITS_64(_emptyMaskTable[fromSq8x8][toSq8x8] & board->getOccupiedMask());
                incrementor = incrementor >> HAS_SET_BITS_64(_opponentRequiredMaskTable[fromSq8x8][fromPieceType] & toMask8x8 & ~board->getOtherPlayerPiecesMask());


                // go to next move if valid
                _totalMoveCount += incrementor;
            }
        }

        return _totalMoveCount;
    }


    /**
     * Advance internal pointer
     */
    FORCE_INLINE MoveGenerator & operator++() {

        _currentMove++;

        return *this;
    }


    /**
     * @return
     */
    FORCE_INLINE bool empty() const {

        return _totalMoveCount == _currentMove;
    }


    /**
     * @return Current move
     */
    FORCE_INLINE const Move & operator*() const {

        return _moves[_currentMove];
    }


    /**
     * @return Total count of possible moves that have been generated.
     */
    FORCE_INLINE TMovesArray::size_type getTotalMoveCount() const {

        return _totalMoveCount;
    }


    /**
     * These shortcuts to internal pre-calculations are only used for debugging.
     */
    static uint64_t getJumpTableEntry(uint8_t fromSq8x8, PieceType pieceType) {

        return _jumpTable[fromSq8x8][pieceType];
    }
    static uint64_t getEmptyMaskTableEntry(uint8_t fromSq8x8, uint8_t toSq8x8) {

        return _emptyMaskTable[fromSq8x8][toSq8x8];
    }
    static uint64_t getOpponentRequiredMaskTableEntry(uint8_t fromSq8x8, PieceType pieceType) {

        return _opponentRequiredMaskTable[fromSq8x8][pieceType];
    }
};