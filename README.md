# Stardots Framework

Stardots is a C++ framework designed for managing nodal algorithms. It provides a flexible and efficient system to define, connect, and manage computational nodes and their relationships.

---

## Features

- **Node Management**: Easily create, manage, and iterate over computational nodes.
- **Plug System**: Define input and output connections between nodes with a type-safe interface.
- **Customizable**: Extendable design to adapt to various use cases in computational workflows.
- **Scalable**: Designed to handle complex graphs of nodes with multiple connections.

---

## Getting Started

### Prerequisites

- **C++ Compiler**: Support for C++17 or later (e.g., GCC, Clang, or MSVC).
- **CMake**: Version 3.15 or later.

### Building the Project

1. Clone the repository:
    ```bash
    git clone https://github.com/your-username/stardots.git
    cd stardots
    ```

2. Create a build directory and configure the project:
    ```bash
    mkdir build
    cd build
    cmake ..
    ```

3. Build the project:
    ```bash
    cmake --build .
    ```

### Running Tests (if applicable)
To run tests, ensure you have configured the project with the BUILD_TESTS option enabled:

---

### Usage
Including Stardots in Your Project
You can integrate Stardots into your project by adding it as a dependency. If you're using CMake, include Stardots using add_subdirectory or a package manager like CPM:

```cmake
add_subdirectory(stardots)
target_link_libraries(your_project PRIVATE stardots)
```

## Example

```cpp
#include "stardots/core/node_manager.h"

using namespace stardots::core;

int main() {
    NodeManager nodeManager;

    auto node1 = nodeManager.addNode();
    auto node2 = nodeManager.addNode();

    auto plug1 = node1->addOutputPlug<int>(42, "Output1");
    auto plug2 = node2->addInputPlug<int>(0, "Input1");

    plug1->next(dynamic_cast<Plug<int>*>(plug2));

    return 0;
}
```

## Documentation
Documentation
The project documentation is generated using Doxygen. To build the documentation:

1. Ensure Doxygen is installed.
2. Run:
    ```bash
    doxygen Doxyfile
    ```
3. Open the generated `docs/html/index.html` file in a browser.

### License
This project is licensed under the MIT License. See the LICENSE file for details.

### Contact
For questions or feedback, reach out to Gabriel Valderramos at `gabrielvalderramos@gmail.com`.