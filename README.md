# board games move generators
Fast move generators for various board games.

### Games
* breakthrough
* connect4
* english draughts
* reversi

### Testing
Use script `run_benchmark.sh` to compile and run flat-MC test with statistics.

Usage:
```
./run_benchamark [game] [time] [random_generator]
```
`game` - the name of the game\
`time` - time in microseconds (without preprocessing)\
`random_generator` - random generator id
* 1 - reimplementation of the Java standard generator
* 2 - Lemire's enhanced method
* other - `std::mt19937`

Then you can run test again: `./[game] [time]`

Running tests for all games is also possible: `./run_all_benchmarks.sh [time]`

## RBG
Implementation is compatible with code generated by [RBG compiler](https://github.com/uicus/rbg2cpp).