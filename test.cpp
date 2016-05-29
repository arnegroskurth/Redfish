
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


int main() {

    MoveGenerator::initialize();

    drawMask8x8(MoveGenerator::getEmptyMaskTableEntry(uint8_t(7), uint8_t(63)));

    return 0;
}