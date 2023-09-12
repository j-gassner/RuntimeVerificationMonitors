# Monitors
A `C++17` Implementation of four runtime verification monitor synthesis algorithms [[1]](#1) for LTLf and PLTLf formulas on finite traces:
- Dynamic Programming
- Event Consuming
- Multi-transition Finite State Machine (MT-FSM*)
- Binary Transition Finite State Machine (BTT-FSM*)

## Build and Compile

Tested with 
- CMake 3.18.3
- Clang compiler 10.0.1
- GCC 10.2.0

### Dependencies

#### External Dependencies:
You need the following software:
- [CommonRoad Environment Model](https://gitlab.lrz.de/maierhofer/environment-model) (Commit c989adda)
- [CommonRoad Curvilinear Coordinate System](https://gitlab.lrz.de/cps/commonroad-curvilinear-coordinate-system) (Commit 0f21a760)

#### Bundled Dependencies:
- [ANTLR4](https://www.antlr.org/) is used for parsing formulas. For this, the following files from [here](https://www.antlr.org/download/index.html) are used:
    - `antlr4-cpp-runtime-4.8-source.zip`
    - `antlr-4.7-complete.jar`

- [gtest](https://github.com/google/googletest) version 1.10.0 is used for tests.

## Build
Make a build folder:
```bash
mkdir build
```

Go into build folder:
```bash
cd build
```

Build with `cmake` and specify paths to external dependencies:
```
cmake \
-DCRCCOSY_LIBRARY_DIR=absolute/Path/To/CurvilinearCoordinateSystem \   
-DCRENV_LIBRARY_DIR=absolute/Path/To/EnvModel \
..
```

Or use `ccmake ..`

Compile the project running: 
```bash
make 
```

## Running:
Required command line argument (must be provided first):

```
--input-file       ../test_scenarios/DEU_test_consider_entering_vehicles_for_lane_change.xml
```

Additional command line arguments:

```
--h                Help
--algorithms       Options are dynamicprogramming, eventconsuming, mt-fsm*, btt-fsm*. You can pass more than one algorithm. Default: dynamicprogramming
--past             true if formula is in PLTLf, false otherwise. Default: false
--runs             Number of runs for each algorithm. Default: 1
--delays           Delay in microseconds in predicate evaluation functions. You can pass more than one delay. Default: 0
--lazyModes        true for lazy evaluation, false for non-lazy, or both. Default: false
--rebuildFSMs      true if MT-FSM* and BTT-FSM* should be built again in each run. Default: false
--consoleOutput    true if output is desired for each run. Default: true
--outputFile       Name of the output file. Default: Evaluation.csv
```

You can also use an input file and run the program with

```bash
./Monitors $(cat Path/To/File)
```

An example for such a file is `input.txt`
## Changing the formula
To change the formula adapt it in ``main()``. Also adapt the functions for predicate
evaluation in ``testRunner()``.

## Testing
The project contains tests using [gtest](https://github.com/google/googletest) that can be run with `ctest`

## Documentation
Documentation can be generated with 
```bash
make doc_doxygen
```

## References
<a id="1">[1]</a> 
G. Roşu and K. Havelund. “Rewriting-based techniques for runtime verification.”
In: Automated Software Engineering 12.2 (2005), pp. 151–197.
