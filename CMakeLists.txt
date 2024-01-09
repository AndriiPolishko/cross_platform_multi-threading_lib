cmake_minimum_required(VERSION 3.24)
project(my_thread)
set(PROJECT_NAME klubochok)

set(TEST0 test_thread)
set(TEST1 test_cond_var)
set(TEST2 test_mutex)
set(TEST3 test_queue)
set(TEST4 test_thread_pool)
set(TEST5 test_lock_guard)
set(TEST6 test_async)
set(TEST7 test_unique_lock)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SRC     src/my_thread.cpp   src/my_mutex.cpp   src/my_conditional_variable.cpp    src/my_unique_lock.cpp )
set(INCLUDE include/my_thread.h include/my_mutex.h include/my_conditional_variable.h  include/my_unique_lock.h include/my_lock_guard.h )

set(TYPES portable_types/portable_thread.h portable_types/portable_mutex.h portable_types/portable_cond_var.h)

add_executable( ${TEST0}
        tests/basic_thread_test.cpp
        src/my_thread.cpp
        include/my_thread.h
        portable_types/portable_thread.h)

add_executable( ${TEST1}
        tests/cond_var_test.cpp
        ${SRC} ${INCLUDE} ${TYPES}
        )

add_executable( ${TEST2}
        tests/mutex_test.cpp
        ${SRC} ${INCLUDE} ${TYPES})

add_executable( ${TEST3}
        tests/queue_test.cpp
        ${SRC} ${INCLUDE} ${TYPES}
        src/my_thread_pool.cpp
        include/my_thread_pool.h
        src/my_thread_safe_queue.cpp
        include/my_thread_safe_queue.h)

add_executable( ${TEST4}
        tests/thread_pool_test.cpp
        ${SRC} ${INCLUDE} ${TYPES}
        src/my_thread_pool.cpp
        include/my_thread_pool.h
        src/my_thread_safe_queue.cpp
        include/my_thread_safe_queue.h include/my_joiner.h)

add_executable( ${TEST5}
        tests/async_test.cpp
        ${SRC} ${INCLUDE} ${TYPES}
        include/my_promise.h
        include/my_future.h
        include/my_async.h
        include/launch_policy.h
        src/my_future.cpp
        src/my_promise.cpp)

add_executable( ${TEST6}
        tests/lock_guard_test.cpp
        ${SRC} ${INCLUDE} ${TYPES}
        )

add_executable( ${TEST7}
        tests/unique_lock_test.cpp
        ${SRC} ${INCLUDE} ${TYPES}
        src/my_unique_lock.cpp
        include/my_unique_lock.h)


set(TESTS ${TEST0} ${TEST1} ${TEST2} ${TEST3} ${TEST4} ${TEST5} ${TEST6} ${TEST7})

foreach(test_name IN LISTS TESTS)
    target_link_libraries(${test_name} PRIVATE -pthread)
endforeach()