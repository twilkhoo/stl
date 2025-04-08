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

To build and test everything (all tests in `tests` directory), run
```bash
bazel test //tests/...
```

To build and test a specific container, run
```bash
bazel test //tests/<some_test_target>
```
, e.g. `bazel test //tests:vector_test`

# Playground
There is a root main.cc file, to be used as a playground.
After adding any deps to the root level BUILD file, run
```bash
bazel run //:main
```

# Memory checking
To run with valgrind, run:
```bash
bazel run -c dbg --run_under="valgrind --leak-check=full --show-leak-kinds=all" //:main
```
