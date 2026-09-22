# Star

Star is a scripting language implemented in C++.

The project was created to explore the design and implementation of a
programming language, from lexical analysis and parsing through runtime
execution.

> **Development status:** Star is currently under active development.
> APIs, language features, and build infrastructure may change as the
> project evolves.

## Overview

Star is designed as a general-purpose scripting language with an
interpreter implemented in C++.

The project focuses on providing a complete language implementation,
including source-code scanning, parsing, abstract syntax tree
construction, interpretation, runtime values, environments, functions,
and object-oriented features.

## Embedding

Star's runtime was designed to be easily embedded in C++ Applications, is a key feature. It adds a cmake target that can be easily integrated with cmake:

``` cmake
find_package(Starlang REQUIRED)
target_link_libraries(target PUBLIC star::star)
```

## Features

- C++ implementation
- Lexical analysis
- Recursive-descent parsing
- Abstract syntax tree
- Tree-walk interpreter
- Runtime environments and lexical scoping
- Functions and function calls
- Classes and object-oriented features
- Control-flow statements
- Runtime values and type handling
- Native/runtime integration
- Automated tests

Additional language features are being developed as the project
progresses.

## Getting Started

### Requirements

Star currently requires:

- A C++ compiler with modern C++ support
- CMake
- A supported build system generator

### Building

Star uses CMake as its build system.

The repository provides CMake presets following this naming pattern:

```text
<OS>(-<vcpkg>)?(-<config>)
```

Where:

- `<OS>` identifies the target operating system.
- `-vcpkg` indicates a configuration using vcpkg.
- `<config>` identifies the build configuration.

Available configurations are:

- `debug` — Development build with debugging information.
- `release` — Standard release build.
- `redist-release` — Release configuration intended for redistribution.

For example:

```text
linux-debug
linux-release
linux-redist-release

windows-vcpkg-debug
windows-vcpkg-release
windows-vcpkg-redist-release
```

The exact operating-system identifiers are defined by the available
presets in `CMakePresets.json`.

Configure and build Star using the desired preset:

```bash
cmake --preset <preset>
cmake --build --preset <preset>
```

> The CMake infrastructure is actively being developed. The preset
> naming convention is intended to remain consistent while individual
> build configurations and implementation details may evolve.

For Linux distros I highly recommend llvm and clang compilers to develop, as clangd,
for debian based distros, just run:

```sh
sudo apt update -y
sudo apt install clang clang++ llvm lldb clangd ninja-build cmake -y
```


### Running

After building Star, the generated executable can be used to execute
Star programs.

Refer to the command-line documentation for the available options and
invocation modes.

## Project Structure

```text
.
├── src/                      # Star implementation
├── samples/                  # Example Star programs
├── config_samples/           # Example configuration files (for vscode and msvc debug)
├── wix/                      # Windows installer configuration
├── docs/                     # Project documentation
├── CMakeLists.txt            # CMake project configuration
└── THIRD_PARTY_LICENSES.txt  # Third-party license notices
```

## Documentation

Detailed documentation is maintained separately from this README.

Some documentation is still being developed alongside the project.

You can see the full documentation at `docs/`

## Dependencies

Star currently uses the following third-party libraries:

| Dependency | Purpose |
|------------|---------|
| magic_enum | Compile-time enum utilities |
| PCRE2 | Regular-expression support |
| fmt | Formatting and output |
| GoogleTest | Automated testing |

GoogleTest is used by the project's test suite and is a development
dependency.

License information for third-party components is available in

## Contributing

Star is currently under active development.

Contributions (issues and pull requests), bug reports, suggestions, and improvements are welcome.
Before making substantial changes, please review the project
documentation and existing source organization. Also the changes must be covered by unit tests, with coverage reports.

You can see key features at the issues, all planned improvements will be organized with milestones, also at [roadmap](docs/roadmap.md)

## License

Star is distributed under the BSD 3-Clause License.

See [LICENSE](LICENSE) for the complete license text.

Third-party dependencies are distributed under their respective
licenses. See [third_party_licensing.txt](third_party_licensing.txt)
for their license information.

## Trade

Star has a provisory icon: 

<img align="center" alt="Star" height="64" width="64" src="./star-logo.svg">

If you are a designer and would like to improve Star's logo, just open an issue, consider also add star as a sticker

## Get In Touch

The easiest way to get in touch is open an issue, there are also my social media, [LinkedIn](https://www.linkedin.com/in/bruno-silva-marques)
