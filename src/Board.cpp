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

#include <iostream>

#include "Board.hpp"
#include "Misc.hpp"


std::ostream& operator<< (std::ostream &out, const Board &board) {

    out << "     a   b   c   d   e   f   g   h" << std::endl;
    out << "   +---+---+---+---+---+---+---+---+" << std::endl;

    for(uint8_t row = 0; row < 8; row++) {

        out << " " << (8 - row) << " +";

        for(uint8_t column = 0; column < 8; column++) {

            auto it = fenCharacters.find(board.getPieceBySq8x8(63 - (row * 8 + column)));

            out << " " << ((it == fenCharacters.end()) ? ' ' : it->second) << " +";
        }

        out << std::endl << "   +---+---+---+---+---+---+---+---+" << std::endl;
    }

    return out;
}