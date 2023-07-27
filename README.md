# Eventi

Eventi is a library for creating custom events with callbacks in C++.

## Features

- Custom events, with or without parameters.
- Multiple ordered callbacks.
- The lifetime of callbacks can be scoped using RAII.
- Events can be deferred/disabled during a scope.
- CMake support.
- No dependencies.

## Example

```
#include <eventi/Event.h>
#include <eventi/Scoped_callbacks.h>
#include <eventi/Scoped_defer.h>
#include <eventi/Scoped_disable.h>
#include <iostream>

class Counter {
public:
    eventi::Event<> counter_reset;
    eventi::Event<int> counter_updated;

    void increment() {
        m_counter++;
        counter_updated(m_counter);
    }

    void reset() {
        m_counter = 0;
        counter_reset();
    }

private:
    int m_counter = 0;
};

void free_func() {
    std::cout << "Reset, free function callback" << std::endl;
}

int main() {
    Counter counter;

    // Both free functions and lambdas can be added as callbacks.
    counter.counter_reset.add_callback(free_func);
    counter.counter_reset.add_callback([] {std::cout << "Reset, lambda callback" << std::endl;});
    counter.counter_updated.add_callback([] (int i) {std::cout << "New value: " << i << std::endl;});

    // Callbacks can be removed.
    eventi::Callback_ref ref = counter.counter_reset.add_callback([] {std::cout << "Foo" << std::endl;});
    ref.remove_callback();

    // The lifetime of callbacks can be scoped using RAII.
    {
        eventi::Scoped_callbacks scoped_callbacks;
        ref = counter.counter_reset.add_callback([] {std::cout << "Bar" << std::endl;});
        scoped_callbacks.add_to_scope(ref);
    }

    // Events without parameters can be deferred during a scope. The `counter_reset` event
    // will be triggered a single time when the `defer` object goes out of scope.
    {
        eventi::Scoped_defer defer(counter.counter_reset);
        for(int i = 0; i < 3; i++) {
            counter.reset();
        }
    }

    // Events can be disabled during a scope. The `counter_updated` event wont be triggered
    // during this scope.
    {
        eventi::Scoped_disable disable(counter.counter_updated);
        counter.increment();
        counter.increment();
        counter.increment();
    }

    counter.increment();
    counter.reset();

    return 0;
}
```

## Installation

In a CMake project the easiest way to install is using `FetchContent`.
See the excellent [cmake-examples](https://github.com/pr0g/cmake-examples) for more help.
