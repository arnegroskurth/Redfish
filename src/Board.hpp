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
#include <cstdlib>
#include <iostream>
#include <string>

#include "Constants.hpp"
#include "Misc.hpp"
#include "Move.hpp"
#include "PositionMath.hpp"


class Board {

protected:

    // bitboard representation
    // [0] all black pieces
    // [1-6] black piece types
    // [7] all white pieces
    // [8-13] white piece types
    // [14] occupied
    // [15] not occupied
    std::array<uint64_t, 16> _bitboards;

    // 0x88 representation
    std::array<PieceType, 128> _0x88;

    // player to move
    Player _player;

    // bit  description
    // 0
    // 1    white castling possible
    // 2    black castling possible
    // 3    white king in cheque
    // 4    black king in cheque
    uint8_t _bitfield;


public:

    Board() {}

    FORCE_INLINE Board(const Board &other) {
        
        _bitboards = other._bitboards;
        _0x88 = other._0x88;
        _player = other._player;
        _bitfield = other._bitfield;
    }

    FORCE_INLINE uint64_t getWhiteMask() const { return _bitboards[7]; }
    FORCE_INLINE uint64_t getWhitePawnsMask() const { return _bitboards[7 + PieceType::PAWN]; }
    FORCE_INLINE uint64_t getWhiteKnightsMask() const { return _bitboards[7 + PieceType::KNIGHT]; }
    FORCE_INLINE uint64_t getWhiteBishopsMask() const { return _bitboards[7 + PieceType::BISHOP]; }
    FORCE_INLINE uint64_t getWhiteRooksMask() const { return _bitboards[7 + PieceType::ROOK]; }
    FORCE_INLINE uint64_t getWhiteQueenMask() const { return _bitboards[7 + PieceType::QUEEN]; }
    FORCE_INLINE uint64_t getWhiteKingMask() const { return _bitboards[7 + PieceType::KING]; }

    FORCE_INLINE uint64_t getBlackMask() const { return _bitboards[0]; }
    FORCE_INLINE uint64_t getBlackPawnsMask() const { return _bitboards[0 + PieceType::PAWN]; }
    FORCE_INLINE uint64_t getBlackKnightsMask() const { return _bitboards[0 + PieceType::KNIGHT]; }
    FORCE_INLINE uint64_t getBlackBishopsMask() const { return _bitboards[0 + PieceType::BISHOP]; }
    FORCE_INLINE uint64_t getBlackRooksMask() const { return _bitboards[0 + PieceType::ROOK]; }
    FORCE_INLINE uint64_t getBlackQueenMask() const { return _bitboards[0 + PieceType::QUEEN]; }
    FORCE_INLINE uint64_t getBlackKingMask() const { return _bitboards[0 + PieceType::KING]; }

    FORCE_INLINE uint64_t getCurrentPlayerPiecesMask() const { return _bitboards[whiteToMove() * 7]; }
    FORCE_INLINE uint64_t getCurrentPlayerPawnsMask() const { return _bitboards[whiteToMove() * 7 + PieceType::PAWN]; }
    FORCE_INLINE uint64_t getCurrentPlayerKnightsMask() const { return _bitboards[whiteToMove() * 7 + PieceType::KNIGHT]; }
    FORCE_INLINE uint64_t getCurrentPlayerBishopsMask() const { return _bitboards[whiteToMove() * 7 + PieceType::BISHOP]; }
    FORCE_INLINE uint64_t getCurrentPlayerRooksMask() const { return _bitboards[whiteToMove() * 7 + PieceType::ROOK]; }
    FORCE_INLINE uint64_t getCurrentPlayerQueenMask() const { return _bitboards[whiteToMove() * 7 + PieceType::QUEEN]; }
    FORCE_INLINE uint64_t getCurrentPlayerKingMask() const { return _bitboards[whiteToMove() * 7 + PieceType::KING]; }

    FORCE_INLINE uint64_t getOtherPlayerPiecesMask() const { return _bitboards[blackToMove() * 7]; }
    FORCE_INLINE uint64_t getOtherPlayerPawnsMask() const { return _bitboards[blackToMove() * 7 + PieceType::PAWN]; }
    FORCE_INLINE uint64_t getOtherPlayerKnightsMask() const { return _bitboards[blackToMove() * 7 + PieceType::KNIGHT]; }
    FORCE_INLINE uint64_t getOtherPlayerBishopsMask() const { return _bitboards[blackToMove() * 7 + PieceType::BISHOP]; }
    FORCE_INLINE uint64_t getOtherPlayerRooksMask() const { return _bitboards[blackToMove() * 7 + PieceType::ROOK]; }
    FORCE_INLINE uint64_t getOtherPlayerQueenMask() const { return _bitboards[blackToMove() * 7 + PieceType::QUEEN]; }
    FORCE_INLINE uint64_t getOtherPlayerKingMask() const { return _bitboards[blackToMove() * 7 + PieceType::KING]; }

    FORCE_INLINE uint64_t getOccupiedMask() const { return _bitboards[14]; }
    FORCE_INLINE uint64_t getNotOccupiedMask() const { return _bitboards[15]; }

    FORCE_INLINE PieceType getPieceBySq0x88(uint8_t sq0x88) const { return _0x88[sq0x88]; }
    FORCE_INLINE PieceType getPieceBySq8x8(uint8_t sq8x8) const { return _0x88[sq0x88BySq8x8(sq8x8)]; }
    FORCE_INLINE PieceType getPieceByMask8x8(uint64_t mask8x8) const { return _0x88[sq0x88ByMask8x8(mask8x8)]; }

    FORCE_INLINE Player playerToMove() const { return _player; }
    FORCE_INLINE Player playerNotToMove() const { return GET_OTHER_PLAYER(_player); }
    FORCE_INLINE bool whiteToMove() const { return IS_WHITE(_player); }
    FORCE_INLINE bool blackToMove() const { return IS_BLACK(_player); }


    /**
     * Applies given move to the current board state.
     */
    template<bool verifyAfterwards = false>
    FORCE_INLINE void applyMove(Move move) {

        uint64_t fromMask8x8 = mask8x8BySq0x88(move.fromSq0x88);
        uint64_t toMask8x8 = mask8x8BySq0x88(move.toSq0x88);
        PieceType movingPieceType = PIECE_TYPE(move.movingPieceType);
        PieceType capturedPieceType = PIECE_TYPE(move.capturedPieceType);
        Player movingPlayer = GET_PLAYER(move.movingPieceType);
        Player otherPlayer = GET_OTHER_PLAYER(movingPlayer);

        _0x88[move.toSq0x88] = move.movingPieceType;
        _0x88[move.fromSq0x88] = PieceType::NONE;

        _bitboards[IS_WHITE(movingPlayer) * 7] ^= fromMask8x8;
        _bitboards[IS_WHITE(movingPlayer) * 7] |= toMask8x8;
        _bitboards[IS_WHITE(movingPlayer) * 7 + movingPieceType] ^= fromMask8x8;
        _bitboards[IS_WHITE(movingPlayer) * 7 + movingPieceType] |= toMask8x8;

        _bitboards[IS_WHITE(otherPlayer) * 7] &= ~toMask8x8;
        _bitboards[IS_WHITE(otherPlayer) * 7 + capturedPieceType] &= ~toMask8x8;

        _bitboards[14] ^= fromMask8x8;
        _bitboards[14] |= toMask8x8;
        _bitboards[15] ^= fromMask8x8;
        _bitboards[15] &= ~toMask8x8;

        _player = GET_OTHER_PLAYER(_player);


        if(verifyAfterwards) verify();
    }


    /**
     * Reset the board to the default position.
     */
    void reset() {

        _bitboards[7]                       = 0b0000000000000000000000000000000000000000000000001111111111111111;
        _bitboards[7 + PieceType::PAWN]     = 0b0000000000000000000000000000000000000000000000001111111100000000;
        _bitboards[7 + PieceType::ROOK]     = 0b0000000000000000000000000000000000000000000000000000000010000001;
        _bitboards[7 + PieceType::KNIGHT]   = 0b0000000000000000000000000000000000000000000000000000000001000010;
        _bitboards[7 + PieceType::BISHOP]   = 0b0000000000000000000000000000000000000000000000000000000000100100;
        _bitboards[7 + PieceType::QUEEN]    = 0b0000000000000000000000000000000000000000000000000000000000001000;
        _bitboards[7 + PieceType::KING]     = 0b0000000000000000000000000000000000000000000000000000000000010000;

        _bitboards[0]                       = 0b1111111111111111000000000000000000000000000000000000000000000000;
        _bitboards[0 + PieceType::PAWN]     = 0b0000000011111111000000000000000000000000000000000000000000000000;
        _bitboards[0 + PieceType::ROOK]     = 0b1000000100000000000000000000000000000000000000000000000000000000;
        _bitboards[0 + PieceType::KNIGHT]   = 0b0100001000000000000000000000000000000000000000000000000000000000;
        _bitboards[0 + PieceType::BISHOP]   = 0b0010010000000000000000000000000000000000000000000000000000000000;
        _bitboards[0 + PieceType::QUEEN]    = 0b0000100000000000000000000000000000000000000000000000000000000000;
        _bitboards[0 + PieceType::KING]     = 0b0001000000000000000000000000000000000000000000000000000000000000;

        _bitboards[14]                      = 0b1111111111111111000000000000000000000000000000001111111111111111;
        _bitboards[15]                      = 0b0000000000000000111111111111111111111111111111110000000000000000;

        _0x88 = {
            PieceType::WHITE_ROOK, PieceType::WHITE_KNIGHT, PieceType::WHITE_BISHOP, PieceType::WHITE_QUEEN, PieceType::WHITE_KING, PieceType::WHITE_BISHOP, PieceType::WHITE_KNIGHT, PieceType::WHITE_ROOK,
            PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID,
            PieceType::WHITE_PAWN, PieceType::WHITE_PAWN, PieceType::WHITE_PAWN, PieceType::WHITE_PAWN, PieceType::WHITE_PAWN, PieceType::WHITE_PAWN, PieceType::WHITE_PAWN, PieceType::WHITE_PAWN,
            PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID,
            PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE,
            PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID,
            PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE,
            PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID,
            PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE,
            PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID,
            PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE,
            PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID,
            PieceType::BLACK_PAWN, PieceType::BLACK_PAWN, PieceType::BLACK_PAWN, PieceType::BLACK_PAWN, PieceType::BLACK_PAWN, PieceType::BLACK_PAWN, PieceType::BLACK_PAWN, PieceType::BLACK_PAWN,
            PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID,
            PieceType::BLACK_ROOK, PieceType::BLACK_KNIGHT, PieceType::BLACK_BISHOP, PieceType::BLACK_QUEEN, PieceType::BLACK_KING, PieceType::BLACK_BISHOP, PieceType::BLACK_KNIGHT, PieceType::BLACK_ROOK,
            PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID, PieceType::INVALID
        };

        _player = Player::WHITE;

        // todo: init bitfield
    }


    bool isFinalState() const {

        // todo: check for cheque-mate

        return false;
    }


    /**
     * Can be used to check for consistency between 0x88 and bitboard representations.
     */
    FORCE_INLINE void verify() const {

        #define __CHECK(Y, X) if(!(X)) { std::cerr << algebraicByMask8x8(Y) << ": !(" << #X << ")" << std::endl; std::exit(1); }

        for(uint8_t sq0x88 = 0; sq0x88 < 120; ++sq0x88) {

            if(!sq0x88Valid(sq0x88)) continue;

            uint64_t mask8x8 = mask8x8BySq0x88(sq0x88);

            PieceType piece = _0x88[sq0x88];
            PieceType pieceType = PIECE_TYPE(piece);
            Player player = GET_PLAYER(piece);

            __CHECK(mask8x8, IS_EMPTY(piece) != HAS_SET_BITS_64(mask8x8 & _bitboards[IS_WHITE(player) * 7]));
            __CHECK(mask8x8, IS_EMPTY(piece) != HAS_SET_BITS_64(mask8x8 & _bitboards[IS_WHITE(player) * 7 + pieceType]));
            __CHECK(mask8x8, IS_EMPTY(piece) != HAS_SET_BITS_64(mask8x8 & _bitboards[14]));
            __CHECK(mask8x8, IS_EMPTY(piece) == HAS_SET_BITS_64(mask8x8 & _bitboards[15]));
        }
    }


    friend std::ostream& operator<< (std::ostream &out, const Board &board) {

        out << "     a   b   c   d   e   f   g   h" << std::endl;
        out << "   +---+---+---+---+---+---+---+---+" << std::endl;

        for(uint8_t row = 0; row < 8; row++) {

            out << " " << (8 - row) << " +";

            for(uint8_t column = 0; column < 8; column++) {

                PieceType pieceType = board.getPieceBySq0x88(sq0x88ByRowAndColumn(7 - row, column));

                auto it = fenCharacters.find(pieceType);

                out << " " << ((it == fenCharacters.end()) ? ' ' : it->second) << " +";
            }

            out << std::endl << "   +---+---+---+---+---+---+---+---+" << std::endl;
        }

        return out;
    }
};
