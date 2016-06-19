# Redfish #

Redfish (with reference to the popular stockfish project) is an open-source chess engine that I created out of interest for game theory and to strengthen my C++ programming capabilities. It uses a combination of 0x88 and bitboards as board representation, alpha-beta-pruning as search algorithm on the tree of possible game states and a simple piece-counting evaluation function. Move-generation, move-application and board evaluation are implemented completely branchless. Beside my ambition to find solutions for all problems related to that it significantly increases performance on pipelined processors.

## Building & Running ##

There is a makefile in the project root to enable an easy building process in a linux environment.

```
cd {PROJECT_DIR}
make -j
./build/player_vs_computer
```

Apart from gcc and libc there are no external dependencies.

## Todo ##

- Add a lookup table for already evaluated positions
- Move ordering for faster cutoffs in alpha-beta-pruning
- Implement casteling, pawn-captures and 50-moves-rule
- Enhance evaluation function
- Parallize search algorithm
- Evaluation of user-input (as long as the required format for a move is matched a human player move is considered valid)

## License ##

Redfish is licensed under the GNU General Public License v3.0.