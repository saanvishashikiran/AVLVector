# AVL Vector Class

A C++ implementation of a dynamic vector-like container using an AVL tree for efficient indexed operations. This data structure maintains elements in ranked order and supports insertion, deletion, replacement, and search operations in `O(log N)` time.

## Features

- Backed by a balanced AVL tree using pointers
- Efficient random access by rank
- Insert and delete operations shift ranks as needed
- Optional support for retrieving the rank of a given element
- Command-driven interface for testing and demonstration

## Supported Operations

- `INSERT <rank> <value>`: Inserts `value` at the given `rank`
- `DELETE <rank>`: Removes the element at the specified `rank`
- `REPLACE <rank> <value>`: Replaces the element at `rank` with `value`
- `ELEMENT-AT <rank>`: Returns the value at the specified `rank`
- `RANK <value>`: Returns the rank of the specified value
- `PRINT`: Outputs all elements in rank order
- `QUIT`: Exits the program

## Instructions for compiling and running code:

- Compile by typing "g++ AVL.cpp main.cpp" into the command line and hitting enter
- Run code by typing "./a.out" into the command line and hitting enter

## Example Usage

```bash
> INSERT 0 10
> INSERT 1 20
> INSERT 1 15
> ELEMENT-AT 1
15
> REPLACE 1 17
> ELEMENT-AT 1
17
> DELETE 1
> PRINT
10 20
