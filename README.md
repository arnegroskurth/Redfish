# Redfish #

Redfish (with reference to the popular stockfish project) is a chess engine that I created out of interest for game theory and to strengthen my C++ programming capabilities. It uses a combination of 0x88 and bitboards as board representation, alpha-beta-pruning as search algorithm on the tree of possible game states and a simple piece-counting evaluation function.

## Building & Running ##

```
cd {PROJECT_DIR}
make -j
./build/player_vs_computer
```

Apart from gcc and libc there are no external dependencies.

## Todo ##

- Implement casteling, en-passent pawn-captures and 50-moves-rule
- Implement pawn replacement
- Validate pawn movements as there seem to be some bugs
- Parallelize search algorithm (OpenMP/MPI/OpenCL)

## License ##

Redfish is licensed under the GNU General Public License v3.0. See LICENSE.txt for details.