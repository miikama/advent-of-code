# Advent of code

Having fun and testing stuff.

Implementations of problems of https://adventofcode.com/.

Solutions in C++, bindings for running the solutions in Python using `Pybind11`.

## Installation

### Prerequisites

Clone the repository with 

```bash
git clone --recurse-submodules https:repo-url.com.git 
cd advent-of-code
```

This repository includes the `pybind11` as a submodule for the ease of use.

We use `Cmake` for compiling the C++, required version is about `Cmake>=3.4`.

### Installing the advent_of_code Python package

Install in a fresh Python virtual environment

```bash
python3 -m venv env
source env/bin/activate
```

Once the virtual environment is active, install with

```bash
python setup.py develop

# OR

python -m pip install -e .
```
You can use pip install -e . --no-deps to use globally installed packages. Otherwise, `pip` will download a build environment according to one specified in `pyproject.toml`

### Just compiling the C++ side

If you install the `advent_of_code` Python package the C++ code is compile during the installation process. If you want to test out the C++ compilation separately, you can do it with

```
mkdir build
cd build
cmake ..
make
```

Which builds the libraries and the `advent_processing.cpython-36m-x86_64-linux-gnu.so`.

## Repository contents

The source code is split between python code in `src/advent_of_code` and C++ code in `src/advent_processing`. The Python bindings are defined in `src/advent_processing/bindings.cpp`.

```bash
├── CMakeLists.txt
├── MANIFEST.in
├── README.md
├── pyproject.toml
├── setup.py
├── setup.cfg
|
├── inputs
|   ├── day1.txt
|   ...
└── src
    ├── advent_of_code
    │   ├── __init__.py
    │   └── processing.py
    └── advent_processing
        ├── CMakeLists.txt
        ├── bindings.cpp
        ├── day.h
        ├── day1.cpp
        ├── day1.h
        ...
```


## Sources and related things

### Pybind

- https://speakerdeck.com/aldanor/pybind11-seamless-operability-between-c-plus-plus-11-and-python?slide=20
- https://www.youtube.com/watch?v=jQedHfF1Jfw
- https://pybind11.readthedocs.io/en/stable/index.html

### Examples 

- https://github.com/pybind/python_example
- https://github.com/pybind/cmake_example

### Other wrapper systems

- https://scikit-build.readthedocs.io/en/latest/
  - a wrapper between cmake and python build tools
- http://www.swig.org/
  - a breeze from the past
- Cython
  - more boilerplate
  - more suited when one wants to do some python processing in C/C++, not when building bindings for large C++ codebase
- Boost.python
  - requires boost
  - pybind11 gets inspiration from Boost.python

### setup.cfg

- https://github.com/pypa/setuptools/pull/862
- https://www.python.org/dev/peps/pep-0517/

### pyproject.toml

- https://www.python.org/dev/peps/pep-0518/