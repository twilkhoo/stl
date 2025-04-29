# Vector
This is my implementation of a vector. This container wraps a c-style array, and doubles its capacity after running out of space.

Check `vector.h` for the interface.

## Differences
The stl vector uses a `std::allocator` as the default allocator. This allows more specialized allocation- users can use their own allocator which allows more fine-grained control on when/where/how heap memory is allocated, compared to just using new and delete. The `new` operator is effectively both allocation and construction, whereas with `std::allocator<T>`, `allocator.allocate(n)` allocates storage for n `Ts`, and `allocator.construct(p, args...)` conducts a **placement new** (new but with specified location).

By default, the `std::allocator<T>` as the default parameter in a vector just calls `operator new` and `operator delete`, which lets you allocate the same way as `new[]`. So, there's not much of a difference.

> Note that in practice, std::allocator_traits is wrapped over the allocator, which creates a more uniform interface for any allocator which may not have each of `allocate`, `deallocate`, `construct`, `destroy` allocations.

Also, the `operator[]` performs more like the `.at()` method, throwing an exception (`std::out_of_range`) if we're accessing invalid memory.
