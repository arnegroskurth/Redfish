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

#include "Constants.hpp"


std::map<PieceType, char> fenCharacters = {
    {PieceType::WHITE_PAWN, 'P'},
    {PieceType::WHITE_KNIGHT, 'N'},
    {PieceType::WHITE_BISHOP, 'B'},
    {PieceType::WHITE_ROOK, 'R'},
    {PieceType::WHITE_QUEEN, 'Q'},
    {PieceType::WHITE_KING, 'K'},
    {PieceType::BLACK_PAWN, 'p'},
    {PieceType::BLACK_KNIGHT, 'n'},
    {PieceType::BLACK_BISHOP, 'b'},
    {PieceType::BLACK_ROOK, 'r'},
    {PieceType::BLACK_QUEEN, 'q'},
    {PieceType::BLACK_KING, 'k'}
};

const std::string rowCharacterByIndex[8] = {
    "1", "2", "3", "4", "5", "6", "7", "8"
};

const std::string columnCharacterByIndex[8] = {
    "a", "b", "c", "d", "e", "f", "g", "h"
};