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

#include "Misc.hpp"
#include "PositionMath.hpp"


void drawMask8x8(uint64_t mask8x8) {

    std::cout << "     a   b   c   d   e   f   g   h" << std::endl;
    std::cout << "   +---+---+---+---+---+---+---+---+" << std::endl;

    for(int row = 7; row >= 0; row--) {

        std::cout << " " << (row + 1) << " +";

        for(int column = 0; column < 8; column++) {

            std::cout << " " << ((mask8x8ByRowAndColumn(row, column) & mask8x8) ? 'x' : ' ') << " +";
        }

        std::cout << std::endl << "   +---+---+---+---+---+---+---+---+" << std::endl;
    }
}