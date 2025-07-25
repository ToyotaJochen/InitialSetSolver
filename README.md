[![License: GPL3.0](https://img.shields.io/badge/License-GPL3-blue.svg)](https://opensource.org/license/gpl-3-0)

# initial set solver (iss)

Implements algorithms for computing initial sets for argumentation frameworks.

Supports i23 format for abstract argumentation frameworks.


## Installation

### Building SAT Solver
This solver works with [CaDiCal](https://github.com/arminbiere/cadical) (version 2.1.3)
The relevant source files are included and the solver can easily be built as follows

```
  cd lib/cadical-rel-2.1.3
  ./configure && make
```

## Compile and Build Solver
To compile the solver, cd into the project root and use
```
  cmake -G build
  cmake --build
```

The binary can be found under `build/bin/serial-solver`

## Command-line usage

```
./InitialSetSolver -p <task> -f <file> -fo <format>
  
  <task>      computational problem
  <file>      input argumentation framework
  <format>    file format for input AF

Options:
  --help      Displays this help message.
  --version   Prints version and author information.
  --formats   Prints available file formats.
  --problems  Prints available computational problems.
```

Example usage: