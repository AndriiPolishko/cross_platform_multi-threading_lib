# Cross-platform multi-threading library
<b>Small student clone of std::thread with additional thread-safe data structures and async capabilities</b>

| Functionality                 | Status |
|-------------------------------|--------|
| Handy cross-platform creation | ✅      |
| Synchronisation primitives    | ✅      |
| Thread safe queue             | ✅    |
| Thread pool                   | ✅     |
| Cross platform async          | ✅      |



## Documentation


### Async

```cpp
template<typename F, typename... Args>
MyFuture<typename std::invoke_result<std::decay_t<F>, std::decay_t<Args>...>::type>  
    my_async(LaunchPolicy policy, F&& f, Args&&... args);
```

The function template my_async runs the function 
f asynchronously (potentially in a separate thread) and returns a MyFuture that will eventually hold the result of that function call.

#### Parameters

- **policy** (`LaunchPolicy`): Determines how the function `f` is executed.
    - `LaunchPolicy::Immediate`: The function is executed immediately in a separate thread.
    - `LaunchPolicy::Deferred`: The function execution is deferred until the `MyFuture::get` method is called in a current thread.
- **f** (`F`): The function to be executed asynchronously.
- **args** (`Args...`): The arguments to be forwarded to the function `f`.


#### Return value

- Returns a `MyFuture` object associated with the shared state created by this call to `my_async`. The `MyFuture` object will eventually contain the result of executing function `f`.

#### Example

```cpp
#include <iostream>
#include "my_async.h"

int foo(int a, int b) {
    return a + b;
}

void hello(std::string const& s, int n) {
    std::cout << s << " " << n << std::endl;
}

int main() {
    auto future = my_async(LaunchPolicy::Immediate, foo, 1, 2);
    auto future2 = my_async(LaunchPolicy::Deferred, hello, "Hello", 1);

    std::cout << future.get() << std::endl;
    future2.get();

    return 0;
}
```
Output:
```
3
Hello 1
```

### MyFuture

```cpp
template<typename T> class MyFuture;

template<> class MyFuture<void>;
```

The class template `MyFuture` provides a mechanism to access the result of asynchronous operations.

#### Member functions

- **(constructor)**: Constructs a new `MyFuture` object.
- **(destructor)**: Destroys the `MyFuture` object.
- **get**: Waits for the result to become available and retrieves it.
- **set_function**: Sets the function to be executed asynchronously.
  -  **f** (`std::function<void()>`) - The bound function to be executed asynchronously.
  
#### Example
  
```cpp
#include <iostream>
#include "my_async.h"

int foo(int a, int b) {
    return a + b;
}

int main() {
    // future from my_async
    auto future = my_async(LaunchPolicy::Immediate, foo, 1, 2); 

    // future from promise
    MyPromise<int> promise;
    auto future2 = promise.get_future();
    promise.set_value(20);
    
    std::cout << future.get() << std::endl;
    std::cout << future2.get() << std::endl;
    
    return 0;
}
```

Output:
```
3
20
```

### MyPromise

```cpp
template<typename T> class MyPromise;
template<> class MyPromise<void>;
```

The class template `MyPromise` provides a facility to store a value or an exception that is later acquired asynchronously via a `MyFuture` object created by the `MyPromise` object.

#### Member functions

- **(constructor)**: Constructs a new `MyPromise` object.
  - **policy** (`LaunchPolicy`): Determines how the function `f` is executed. It does not execute in the constructor. Default value is `LaunchPolicy::Immediate`.
    - `LaunchPolicy::Immediate`: The function is executed immediately in a separate thread.
    - `LaunchPolicy::Deferred`: The function execution is deferred until the `MyFuture::get` method is called in a current thread.
- **(destructor)**: Destroys the `MyPromise` object.
- **get_future**: Returns a `MyFuture<T>` object associated with the same shared state.
- **set_value**: Stores the value as the asynchronous result.
  - **value** (`T`) - The value to be stored.
- **set_exception**: Stores the exception as the asynchronous result.
  - **e** (`std::exception_ptr`) - The exception to be stored.

#### Example

```cpp
#include <iostream>
#include "my_async.h"

int foo(int a, int b) {
    return a + b;
}

int main() {
    MyPromise<int> promise;
    auto future = promise.get_future();
    promise.set_value(foo(1, 2));
    
    std::cout << future.get() << std::endl;
    
    MyPromise<int> promise2;
    auto future2 = promise2.get_future();
    promise2.set_exception(std::make_exception_ptr(std::runtime_error("error")));
    
    try {
        future2.get();
    } catch (std::exception const& e) {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}
```

Output:
```
3
error
```
  



