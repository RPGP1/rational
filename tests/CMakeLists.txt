add_executable(rational_test main.cpp)
target_compile_options(rational_test PUBLIC
  -Werror
  -Wall
  -Wextra
  -Wconversion
  -Wswitch-default
  -Wdisabled-optimization
  -Wformat
  -Winit-self
  -Woverloaded-virtual
  -Wfloat-equal
  -Wno-old-style-cast
  -Wno-pragmas
  -Wno-ignored-attributes
  -Wreturn-type
  -Wno-cast-function-type
)
target_link_libraries(rational_test PUBLIC rational)
target_link_libraries(rational_test PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(rational_test)
