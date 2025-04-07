# Custom STL

This is a repo containing lots of custom C++ STL implementations.

# Done


# To-do

## Containers

### Sequence Containers

- `vector`
- `deque`
- `list`

### Associative Containers

- `unordered_map`
- `unordered_set`
- `map`
- `set`

### Container Adapters

- `stack`
- `queue`
- `priority_queue`


## Iterators
Respective iterators are included with the containers (e.g. `random access` for `vector`, `bidirectional` for `set`, etc.).


## Algorithms
- `copy`
- `fill`
- `transform`
- `rotate`
- `max_element`
- `min_element`
- `accumulate`
- `count`
- `find`

# Functors

- `plus`
- `minus`
- `less`
- `greater`


## Memory

- `unique_ptr`
- `shared_ptr`
- `weak_ptr`




# Testing
This repo uses GoogleTest to unit test.

```bash

cmake -S . -B build
cmake --build build
./build/CustomSTL

```

