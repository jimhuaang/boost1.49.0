set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(
  LambdaTest1
  lambda_test_1.cpp
)
add_test(NAME lambda_test_1 COMMAND LambdaTest1)

add_executable(
  IsPointer
  is_pointer_test.cpp
)
add_test(NAME is_pointer_test COMMAND IsPointer)

add_executable(
  ForEach
  foreach_test.cpp
)
add_test(NAME foreach_test COMMAND ForEach)

add_executable(
  NonCopyable
  noncopyable_test.cpp
)
add_test(NAME noncopyable_test COMMAND NonCopyable)

add_executable(
  ToString
  tostring_test.cpp
)
add_test(NAME tostring_test COMMAND ToString)

add_executable(
  Singleton
  singleton_test.cpp
)
target_link_libraries(Singleton boost_thread pthread)
add_test(NAME singleton_test COMMAND Singleton)

add_executable(
  UnorderedMap
  unordered_map_test.cpp
)
add_test(NAME unordered_map_test COMMAND UnorderedMap)

add_executable(
  Bind
  bind_test.cpp
)
target_link_libraries(Bind boost_thread pthread)
add_test(NAME bind_test COMMAND Bind)

add_executable(
  SharedPtr
  shared_ptr_test.cpp
)
add_test(NAME shared_ptr_test COMMAND SharedPtr)

add_executable(
  Func
  function_test.cpp
)
add_test(NAME function_test COMMAND Func)


add_executable(
  MemberFunc
  mem_fn_test.cpp
)
add_test(NAME mem_fn_test COMMAND MemberFunc)

add_executable(
  Mutex
  mutex_test.cpp
)
target_link_libraries(Mutex boost_thread pthread)
add_test(NAME mutex_test COMMAND Mutex)

add_executable(
  ScopeExit
  scope_exit_test.cpp
)
add_test(NAME scope_exit_test COMMAND ScopeExit)

add_executable(
  MoveForward
  move_forward_test.cpp
)
add_test(NAME move_forward_test COMMAND MoveForward)

add_executable(
  MovePerfectForward
  move_forward_test.cpp
)
add_test(NAME move_perfect_forward_test COMMAND MovePerfectForward)

add_executable(
  ForwardAdapter
  forward_adapter_test.cpp
)
add_test(NAME forward_adapter_test COMMAND ForwardAdapter)

add_executable(
  ArrayTest
  array_test.cpp
)
add_test(NAME array_test COMMAND ArrayTest)