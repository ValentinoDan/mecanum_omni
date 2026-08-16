cmake_minimum_required(VERSION 3.8)
project(mecanum_omni)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(mecanum_omni_node
  src/main.cpp
  src/mecanum.cpp
  src/omni.cpp)
target_include_directories(mecanum_omni_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(mecanum_omni_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
  mecanum_omni_node
  "rclcpp"
  "geometry_msgs"
  "std_msgs"
)

install(TARGETS mecanum_omni_node
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  find_package(ament_cmake_gtest REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()

  ament_add_gtest(test_mecanum tests/test_mecanum.cpp src/mecanum.cpp)
  target_include_directories(test_mecanum PUBLIC include)

  ament_add_gtest(test_omni tests/test_omni.cpp src/omni.cpp)
  target_include_directories(test_omni PUBLIC include)
endif()

ament_package()
