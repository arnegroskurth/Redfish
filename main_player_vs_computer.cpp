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

    Board::initialize();
    MoveGenerator::initialize();


    Board board;
    board.reset();

    std::string playerMoveString;
    Move lastMove;

    std::regex expression("^([a-h][1-8]):([a-h][1-8])$");
    std::smatch expressionMatch;

    // repeat until a final game state is reached
    do {

        std::cout << "\x1B[2J\x1B[H" << mastHead << board;

        if(board.whiteToMove()) {

            MoveGenerator moveGenerator(&board);

            Move playerMove;

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

                    playerMove.fromSq0x88 = sq0x88ByRowAndColumn(fromRow, fromColumn);
                    playerMove.toSq0x88 = sq0x88ByRowAndColumn(toRow, toColumn);

                    playerMove.movingPieceType = board.getPieceBySq0x88(playerMove.fromSq0x88);
                    playerMove.capturedPieceType = board.getPieceBySq0x88(playerMove.toSq0x88);


                    // break loop if valid move given
                    if(moveGenerator.hasMove(playerMove)) break;
                }
            }
            while(true);

            board.applyMove(playerMove);
        }

        else {

            std::cout << "Calculating..." << std::flush;

            Engine<> engine(&board, 6);

            board.applyMove(engine.getBestMove());
        }
    }
    while(!board.isFinalState());

    return 0;
}