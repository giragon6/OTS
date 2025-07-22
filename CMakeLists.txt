# CMakeList.txt : CMake project for OTS_CMake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("OTS_CMake")

file(GLOB SOURCES "OTS/*.cpp" "OTS/*.h")

find_package(ZLIB REQUIRED)

# Add source to this project's executable.
add_executable (OTS_CMake ${SOURCES})

target_link_libraries(OTS_CMake PRIVATE ZLIB::ZLIB)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OTS_CMake PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
