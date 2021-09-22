# OI-Utility

## Overview

`OI-Utility` is a powerful library for OI contests. It's different from other data structure library. **It's fast, safy and easy-to-use. And it's simple enough to extend.**

## Features

- **Cross-platform** : There are no external libraries that `OI-Utility` needs. It may not even need the `C++ Standard Library`.
- **Simpler than others** : You will understand the its purpose as soon as you see a function. Its naming style is similar to `STL`.
- **More secure** : Never use the dynamic memory allocation in order to have less problems and mistakes.

## Usage

### Getting Started

There are two kinds of utilities in this library: **Algorithm & Data Structure**. All of them have no dependence on each other. By this way, you can just move the source codes to your project. It's easy to find the algorithm you need.

### Compilation

Maybe you wanna use `OI-Utility` as a external library instead of copying the source code and then compile it. In reality, it is feasible for `OI-utility` to be used without compiling. You hust need to include it like this:

```cpp
#include "\OI-Utility\Algorithm\QuickIO.hpp"
using namespace QuickIO;
```

