# data-hazard-corrector
 A C++ corrector of data hazards in RISC-V architecture

## Compile

Be sure to be in the right spot
```
cd main
```
Then compile using `g++`
```
g++ -o main main.cpp DataHazardCorrector.cpp DataHazardCorrectorFactory.cpp Instruction.cpp NOPInsertionDataHazardCorrector.cpp WithForwardingDataHazardCorrectors.cpp ReorderDataHazardCorrector.cpp BinaryOperationType.cpp -std=c++17
```
