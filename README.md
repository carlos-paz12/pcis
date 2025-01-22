# instruction-set-simulator/README.md
# Introduction

PCIS is an implementation of Programmable Circuit Simulators.

# Instruction Set Simulator

This project is a simulator for instruction set architecture models, implementing three processors: Neander, Cesar, and Ramses. The goal is to provide a platform to simulate basic arithmetic and data manipulation operations.

## Project Structure

The project is organized as follows:
## Project Structure

The project is organized as follows:

```
instruction-set-simulator
├── inc
│   ├── cesar.h          # Interface of the Cesar class
│   ├── neander.h        # Interface of the Neander class
│   ├── ramses.h         # Interface of the Ramses class
│   └── utils.h          # Interface of utility functions
├── src
│   ├── cesar.cpp        # Implementation of the Cesar class
│   ├── neander.cpp      # Implementation of the Neander class
│   ├── ramses.cpp       # Implementation of the Ramses class
│   └── main
│       ├── main.cpp     # Program entry point
│       └── Utils.cpp    # Implementation of utility functions
├── CMakeLists.txt       # CMake configuration script
└── README.md            # Project documentation
```

## Features

- **Cesar**: Methods to add and subtract 8-bit and 16-bit variables, and determine the largest value in a 32-position array.
- **Neander**: Methods to add and subtract 8-bit variables, add 16-bit variables, and determine the largest value in a 32-position array.
- **Ramses**: Methods to add and subtract 8-bit and 16-bit variables, determine the largest value in a 32-position array, and call the 16-bit addition subroutine.

## Compilation Instructions

To compile the project, use CMake. Run the following commands in the terminal:

```bash
cmake -S . -B build
cmake --build build
./build/pcis
```

## Usage Instructions

After compilation, run the generated program. The simulator will start and allow the simulation of the implemented processors' operations.

## Contributions

Contributions are welcome! Feel free to open issues or pull requests.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.
