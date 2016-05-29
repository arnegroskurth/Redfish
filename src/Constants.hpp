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

#include <map>
#include <string>


/**
 * Piece types are encoded as a 8-bit numbers.
 */
enum PieceType : uint8_t {

    PAWN            = 0b00000001,
    KNIGHT          = 0b00000010,
    BISHOP          = 0b00000011,
    ROOK            = 0b00000100,
    QUEEN           = 0b00000101,
    KING            = 0b00000110,

    WHITE_PAWN      = 0b00001001,
    WHITE_KNIGHT    = 0b00001010,
    WHITE_BISHOP    = 0b00001011,
    WHITE_ROOK      = 0b00001100,
    WHITE_QUEEN     = 0b00001101,
    WHITE_KING      = 0b00001110,

    BLACK_PAWN      = 0b00010001,
    BLACK_KNIGHT    = 0b00010010,
    BLACK_BISHOP    = 0b00010011,
    BLACK_ROOK      = 0b00010100,
    BLACK_QUEEN     = 0b00010101,
    BLACK_KING      = 0b00010110,

    NONE            = 0b01000000,
    INVALID         = 0b10000000
};

/**
 * This mask can be used to extract the impersonal pieceType from a given piece.
 */
const uint8_t pieceTypeMask = 0b00000111;

/**
 * Owner is encoded in bit 4/5 of PieceType
 */
enum Player : uint8_t {

    WHITE   = 0b00001000,
    BLACK   = 0b00010000
};

/**
 * This mask can be used to extract the player information from a given piece.
 */
const uint8_t playerMask = 0b00011000;


/**
 * Some macros to extract basic information about a given piece.
 */
#define PIECE_TYPE(X) (static_cast<PieceType>(pieceTypeMask & X))
#define IS_PAWN(X) (PieceType::PAWN == (pieceTypeMask & X))
#define IS_KNIGHT(X) (PieceType::KNIGHT == (pieceTypeMask & X))
#define IS_BISHOP(X) (PieceType::BISHOP == (pieceTypeMask & X))
#define IS_ROOK(X) (PieceType::ROOK == (pieceTypeMask & X))
#define IS_QUEEN(X) (PieceType::QUEEN == (pieceTypeMask & X))
#define IS_KING(X) (PieceType::KING == (pieceTypeMask & X))

#define GET_PLAYER(X) (static_cast<Player>(playerMask & X))
#define GET_OTHER_PLAYER(X) (static_cast<Player>(((Player::WHITE & X) << 1) | ((Player::BLACK & X) >> 1)))
#define IS_WHITE(X) ((Player::WHITE & X) == Player::WHITE)
#define IS_BLACK(X) ((Player::BLACK & X) == Player::BLACK)
#define IS_OPPONENT(X, Y) (X == GET_OTHER_PLAYER(Y))

#define IS_EMPTY(X) (PieceType::NONE == (PieceType::NONE & X))


/**
 * The following constants are used to parse FEN strings and to draw board states.
 */
extern std::map<PieceType, char> fenCharacters;
extern const std::string rowCharacterByIndex[8];
extern const std::string columnCharacterByIndex[8];


/**
 * DirectionDelta0x88 = 119 + (from - to)
 */
enum DirectionDelta0x88 : uint8_t {
    NORTH       = 119 + 16,
    NORTH_EAST  = 119 + 17,
    EAST        = 119 + 1,
    SOUTH_EAST  = 119 - 15,
    SOUTH       = 119 - 16,
    SOUTH_WEST  = 119 - 17,
    WEST        = 119 - 1,
    NORTH_WEST  = 119 + 15
};


/**
 * Some low-level bit macros
 */
#define HAS_SET_BITS_64(X) (__builtin_ffsll(X) > 0)
#define HAS_SET_BITS_32(X) (__builtin_ffsl(X) > 0)
#define HAS_SET_BITS_8(X) (__builtin_ffs(X) > 0)
#define SET_BITS_64(X) (__builtin_popcountll(X))
#define SET_BITS_32(X) (__builtin_popcountl(X))
#define SET_BITS_8(X) (__builtin_popcount(X))


/**
 * Every inlined function gets inlined with this statement
 */
#define FORCE_INLINE __attribute__((__always_inline__)) inline
#define UNROLL_LOOPS __attribute__((optimize("unroll-loops")))
#define HOT __attribute__ ((hot))


/**
 * Headline that gets shown on startup
 */
const std::string mastHead =
    "Redfish Copyright (C) 2016 Arne Groskurth.\n"
    "(Licensed under the GNU General Public License v3.0.)\n\n";

