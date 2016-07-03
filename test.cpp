
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <bitset>

#include "src/Board.hpp"
#include "src/Constants.hpp"
#include "src/Engine.hpp"
#include "src/Evaluation.hpp"
#include "src/Misc.hpp"
#include "src/Move.hpp"
#include "src/MoveGenerator.hpp"
#include "src/PositionMath.hpp"

using namespace std::chrono;


int main() {

    Board::initialize();
    MoveGenerator::initialize();

    Board board;
    board.reset();

    while(!board.isFinalState()) {

        std::cout << "\x1B[2J\x1B[H" << mastHead << board;

        Engine<true> engine1(&board, 6);
        Engine<false> engine2(&board, 6);

        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        Move move1 = engine1.getBestMove();
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        Move move2 = engine2.getBestMove();
        high_resolution_clock::time_point t3 = high_resolution_clock::now();

        auto duration1 = duration_cast<microseconds>(t2 - t1).count();
        auto duration2 = duration_cast<microseconds>(t3 - t2).count();

        std::cout << duration1 << " / " << duration2 << std::endl;
        std::cout << move1 << " / " << move2 << std::endl;

        if(move1 != move2) {

            std::cerr << "Unequal move computed!" << std::endl;

            break;
        }

        board.applyMove(move1);
    }

    return 0;
}