find_package(Catch2 REQUIRED)

add_executable(unit-test
  main.cpp
  Callback_ref_test.cpp
  Event_test.cpp
  Scoped_callbacks_test.cpp
  Scoped_defer_test.cpp
  Scoped_disable_test.cpp
)

target_link_libraries(unit-test
  eventi
  Catch2::Catch2
)
