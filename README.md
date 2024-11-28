# Advent of Code

This repository contains my solutions to the [Advent of Code](https://adventofcode.com/) challenges.

I've developed a custom library to simplify running the solutions and testing the provided examples, ensuring they pass as expected. The library streamlines the process, making it more efficient to solve and verify challenges.

## Features

- **Custom Solution Manager**: Easily register and run solutions for each day and year.
- **Test Framework**: Define and run tests based on the examples provided in the challenges.
- **Instrumentation and Logging**: Built-in profiling and logging utilities to aid in debugging and performance analysis.

## Usage

To compile and run the solutions:

```sh
cd tools
make clean
make
make run
```
```log
[0001] Info: Starting the program
[0002] Info: Running all challenges and tests
[0003] Info: 2023::01-1: [PASS]
[0004] Info: 2023::01-1: Answer: 54990
[0003] Info: 2023::01-2: [PASS]
[0004] Info: 2023::01-2: Answer: 54473
```

This will build the project and execute all registered solutions and tests, displaying the results.

if you only want it too run a specific year/day. you can edit the `AOCManager::getInstance().run();` line in `main.cpp` to only run the desired year/day.
eg
```cpp
AOCManager::getInstance().run();            // run all solutions
AOCManager::getInstance().run(2020);        // run all solutions for 2020
AOCManager::getInstance().run(2020, 1);     // run only the solution for 2020 day 1
AOCManager::getInstance().run(2020, 1, 1);  // run only the first part of the solution for 2020 day 1
```