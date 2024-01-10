# Klubochok
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

### Klubochok-thread interface
```
class MyThread
{
public:
    MyThread() = default;
    ~MyThread();

    template <typename Callable, typename... Args>
    explicit MyThread(Callable&& func, Args&&... args)
    {
        my_thread_create(std::forward<Callable>(func), std::forward<Args>(args)...);
    }
	
    void join(retval val = nullptr) const;
    void detach() const;

    template <typename Callable, typename... Args>
    void my_thread_create(Callable&& func, Args&&... args)
    {
        my_thread = thread_create(&my_thread, std::forward<Callable>(func), std::forward<Args>(args)...);
    }

    my_thread_t native_handle() const { return my_thread; }

private:
    my_thread_t my_thread{};
};
```

To run a function in new thread you have two options:
- either pass function and its parameters to the constructor of the thread 
```MyThread firstThread(getPower, 2, res)``` 
- or create thread first and then call ```my_thread_create``` method on it
```firstThread.my_thread_create(getPower, 2, res)```

After creation, you have to join it or detach by ```join``` and ```detach``` methods
respectively.

### Synchronisation primitives
Currently, we've implemented two main primitives:
- mutex
- conditional variable

<b>Mutex interface</b>
```
class MyMutex
{
public:
	MyMutex() = default;
	~MyMutex();
    MyMutex& operator=(const MyMutex&) = delete;
    MyMutex(const MyMutex &) = default;
public:
	void lock();
	void unlock();
	my_mutex_t* native_handle();
private:
	my_mutex_t my_mutex = create_mutex();
};
```
It's basically a thin wrapper around standard OS specific mutex with possibility 
to get this OS's mutex by ```native_handle()``` method. Copy and assignment operators are deleted.

<b>Conditional variable interface</b>
```
class MyCondVar
{
public:
	MyCondVar();
	~MyCondVar();
	MyCondVar(const MyCondVar &) = delete;
	MyCondVar operator=(const MyCondVar) = delete;
public:
	void wait(MyMutex* mutex);
	void signal();
    void broadcast();
private:
	my_cond my_cv;
};
```
Allows all essential CV operations. It can wait for signal ```wait```, signalise to one thread ```signal``` or to all threads ```broadcast```.

### ThreadPool

```cpp
class ThreadPool;
```

The class `ThreadPool` represents a group of threads that can be used to execute tasks concurrently. It is an effective way to reuse threads and improve the performance of an application.

#### Member functions

- **(constructor)**: Constructs a new `ThreadPool` object. The number of threads in the pool is equal to the number of hardware threads.
- **(destructor)**: Destroys the `ThreadPool` object.
- **submit**: Adds a new task to the queue of tasks.
  - **f** (``) - The function to be added to the task queue.
- **notify_all_tasks_done** (private): Notifies all threads that there are no more tasks to do.
- **worker_thread** (private): The function that manages the worker threads.

#### Example

```cpp
#include "my_thread_pool.h"
#include <iostream>
#include "my_mutex.h"

MyMutex outerMutex;

void square_task(int num) {
    {
		// For good-looking output
		outerMutex.lock();
        std::cout << "Thread ID: " << my_get_thread_id() << ", Square of " << num << ": " << num * num << std::endl;
		outerMutex.unlock();
    }
}

int main() {
    MyThreadPool threadPool;

    for (int i = 1; i <= 10; ++i) {
        threadPool.submit([i]() { square_task(i); });
    }
    return 0;
}
```

Possible output:
```
Thread ID: 11381, Square of 1: 1
Thread ID: 11381, Square of 5: 25
Thread ID: 11381, Square of 6: 36
Thread ID: 11381, Square of 7: 49
Thread ID: 11381, Square of 8: 64
Thread ID: 11381, Square of 9: 81
Thread ID: 11381, Square of 10: 100
Thread ID: 11380, Square of 2: 4
Thread ID: 11379, Square of 3: 9
Thread ID: 11382, Square of 4: 16
```



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
  



