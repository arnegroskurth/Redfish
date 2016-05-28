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

    Board(const Board &other) {

        // todo: copy???
        _bitboards = other._bitboards;
        _0x88 = other._0x88;
        _player = other._player;
        _bitfield = other._bitfield;
    }

    uint64_t getWhiteMask() const { return this->_bitboards[7]; }
    uint64_t getWhitePawnsMask() const { return this->_bitboards[7 + PieceType::PAWN]; }
    uint64_t getWhiteKnightsMask() const { return this->_bitboards[7 + PieceType::KNIGHT]; }
    uint64_t getWhiteBishopsMask() const { return this->_bitboards[7 + PieceType::BISHOP]; }
    uint64_t getWhiteRooksMask() const { return this->_bitboards[7 + PieceType::ROOK]; }
    uint64_t getWhiteQueenMask() const { return this->_bitboards[7 + PieceType::QUEEN]; }
    uint64_t getWhiteKingMask() const { return this->_bitboards[7 + PieceType::KING]; }

    uint64_t getBlackMask() const { return this->_bitboards[0]; }
    uint64_t getBlackPawnsMask() const { return this->_bitboards[0 + PieceType::PAWN]; }
    uint64_t getBlackKnightsMask() const { return this->_bitboards[0 + PieceType::KNIGHT]; }
    uint64_t getBlackBishopsMask() const { return this->_bitboards[0 + PieceType::BISHOP]; }
    uint64_t getBlackRooksMask() const { return this->_bitboards[0 + PieceType::ROOK]; }
    uint64_t getBlackQueenMask() const { return this->_bitboards[0 + PieceType::QUEEN]; }
    uint64_t getBlackKingMask() const { return this->_bitboards[0 + PieceType::KING]; }

    uint64_t getCurrentPlayerPiecesMask() const { return this->_bitboards[this->whiteToMove() * 7]; }
    uint64_t getCurrentPlayerPawnsMask() const { return this->_bitboards[this->whiteToMove() * 7 + PieceType::PAWN]; }
    uint64_t getCurrentPlayerKnightsMask() const { return this->_bitboards[this->whiteToMove() * 7 + PieceType::KNIGHT]; }
    uint64_t getCurrentPlayerBishopsMask() const { return this->_bitboards[this->whiteToMove() * 7 + PieceType::BISHOP]; }
    uint64_t getCurrentPlayerRooksMask() const { return this->_bitboards[this->whiteToMove() * 7 + PieceType::ROOK]; }
    uint64_t getCurrentPlayerQueenMask() const { return this->_bitboards[this->whiteToMove() * 7 + PieceType::QUEEN]; }
    uint64_t getCurrentPlayerKingMask() const { return this->_bitboards[this->whiteToMove() * 7 + PieceType::KING]; }

    uint64_t getOtherPlayerPiecesMask() const { return this->_bitboards[this->blackToMove() * 7]; }
    uint64_t getOtherPlayerPawnsMask() const { return this->_bitboards[this->blackToMove() * 7 + PieceType::PAWN]; }
    uint64_t getOtherPlayerKnightsMask() const { return this->_bitboards[this->blackToMove() * 7 + PieceType::KNIGHT]; }
    uint64_t getOtherPlayerBishopsMask() const { return this->_bitboards[this->blackToMove() * 7 + PieceType::BISHOP]; }
    uint64_t getOtherPlayerRooksMask() const { return this->_bitboards[this->blackToMove() * 7 + PieceType::ROOK]; }
    uint64_t getOtherPlayerQueenMask() const { return this->_bitboards[this->blackToMove() * 7 + PieceType::QUEEN]; }
    uint64_t getOtherPlayerKingMask() const { return this->_bitboards[this->blackToMove() * 7 + PieceType::KING]; }

    uint64_t getOccupiedMask() const { return this->_bitboards[14]; }
    uint64_t getNotOccupiedMask() const { return this->_bitboards[15]; }

    PieceType getPieceBySq0x88(uint8_t sq0x88) const { return _0x88[sq0x88]; }
    PieceType getPieceBySq8x8(uint8_t sq8x8) const { return _0x88[sq0x88BySq8x8(sq8x8)]; }
    PieceType getPieceByMask8x8(uint64_t mask8x8) const { return _0x88[sq0x88ByMask8x8(mask8x8)]; }

    Player playerToMove() const { return _player; }
    Player playerNotToMove() const { return GET_OTHER_PLAYER(_player); }
    bool whiteToMove() const { return _player & Player::WHITE; }
    bool blackToMove() const { return _player & Player::BLACK; }


    void applyMove(Move *move) {

        // todo: actual application
        // todo: switch player
    }


    /**
     * Reset the board to the default position.
     */
    void reset() {

        this->_bitboards[7]                                             = 0b0000000000000000000000000000000000000000000000001111111111111111;
        this->_bitboards[7 + (0b00000111 & PieceType::WHITE_PAWN)]      = 0b0000000000000000000000000000000000000000000000001111111100000000;
        this->_bitboards[7 + (0b00000111 & PieceType::WHITE_ROOK)]      = 0b0000000000000000000000000000000000000000000000000000000010000001;
        this->_bitboards[7 + (0b00000111 & PieceType::WHITE_KNIGHT)]    = 0b0000000000000000000000000000000000000000000000000000000001000010;
        this->_bitboards[7 + (0b00000111 & PieceType::WHITE_BISHOP)]    = 0b0000000000000000000000000000000000000000000000000000000000100100;
        this->_bitboards[7 + (0b00000111 & PieceType::WHITE_QUEEN)]     = 0b0000000000000000000000000000000000000000000000000000000000010000;
        this->_bitboards[7 + (0b00000111 & PieceType::WHITE_KING)]      = 0b0000000000000000000000000000000000000000000000000000000000001000;

        this->_bitboards[0]                                             = 0b1111111111111111000000000000000000000000000000000000000000000000;
        this->_bitboards[0 + (0b00000111 & PieceType::BLACK_PAWN)]      = 0b0000000011111111000000000000000000000000000000000000000000000000;
        this->_bitboards[0 + (0b00000111 & PieceType::BLACK_ROOK)]      = 0b1000000100000000000000000000000000000000000000000000000000000000;
        this->_bitboards[0 + (0b00000111 & PieceType::BLACK_KNIGHT)]    = 0b0100001000000000000000000000000000000000000000000000000000000000;
        this->_bitboards[0 + (0b00000111 & PieceType::BLACK_BISHOP)]    = 0b0010010000000000000000000000000000000000000000000000000000000000;
        this->_bitboards[0 + (0b00000111 & PieceType::BLACK_QUEEN)]     = 0b0001000000000000000000000000000000000000000000000000000000000000;
        this->_bitboards[0 + (0b00000111 & PieceType::BLACK_KING)]      = 0b0000100000000000000000000000000000000000000000000000000000000000;

        this->_bitboards[14]                                            = 0b1111111111111111000000000000000000000000000000001111111111111111;
        this->_bitboards[15]                                            = 0b0000000000000000111111111111111111111111111111110000000000000000;

        this->_0x88 = {
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

        this->_player = Player::WHITE;

        // todo: init bitfield
    }
};


extern std::ostream& operator<< (std::ostream &out, const Board &board);
