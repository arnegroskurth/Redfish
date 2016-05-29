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

#include <iostream>

#include "Constants.hpp"
#include "Misc.hpp"
#include "PositionMath.hpp"


struct Move {

    PieceType movingPieceType;
    PieceType capturedPieceType;

    uint8_t fromSq0x88;
    uint8_t toSq0x88;


    Move() {}
    FORCE_INLINE Move(const Move &other) {

        movingPieceType = other.movingPieceType;
        capturedPieceType = other.capturedPieceType;
        fromSq0x88 = other.fromSq0x88;
        toSq0x88 = other.toSq0x88;
    }


    friend std::ostream& operator<< (std::ostream& out, const Move &move) {

        out << algebraicByMask8x8(mask8x8BySq0x88(move.fromSq0x88)) << ":" << algebraicByMask8x8(mask8x8BySq0x88(move.toSq0x88));

        return out;
    }
};