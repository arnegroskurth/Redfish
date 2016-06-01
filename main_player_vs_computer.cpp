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
#include <regex>
#include <string>

#include "src/Board.hpp"
#include "src/Engine.hpp"
#include "src/MoveGenerator.hpp"


int main() {

    MoveGenerator::initialize();


    Board board;
    board.reset();

    std::string playerMoveString;
    Move lastMove;

    std::regex expression("^([a-h][1-8]):([a-h][1-8])$");
    std::smatch expressionMatch;

    while(!board.isFinalState()) {

        std::cout << "\x1B[2J\x1B[H" << mastHead << board;

        if(board.whiteToMove()) {

            Move move;

            // read move and validate until valid move
            do {

                std::cout << "Move (format: 'from:to'): ";
                std::cin >> playerMoveString;

                if(std::regex_match(playerMoveString, expressionMatch, expression)) {

                    std::string from = expressionMatch[1].str();
                    std::string to = expressionMatch[2].str();

                    uint8_t fromColumn = from[0] - 97;
                    uint8_t fromRow = from[1] - 49;

                    uint8_t toColumn = to[0] - 97;
                    uint8_t toRow = to[1] - 49;

                    move.fromSq0x88 = sq0x88ByRowAndColumn(fromRow, fromColumn);
                    move.toSq0x88 = sq0x88ByRowAndColumn(toRow, toColumn);

                    move.movingPieceType = board.getPieceBySq0x88(move.fromSq0x88);
                    move.capturedPieceType = board.getPieceBySq0x88(move.toSq0x88);

                    // invalid move.
                    if(GET_PLAYER(move.movingPieceType) != board.playerToMove()) continue;

                    // break loop
                    break;
                }
            }
            while(true);

            board.applyMove(move);
        }

        else {

            std::cout << "Calculating..." << std::flush;

            Engine engine(&board, 7);

            board.applyMove(engine.getBestMove());
        }
    }

    return 0;
}