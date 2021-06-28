# CMakeList.txt: CMake-Projekt für "CodingChallengeRytle". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

#The next part is copied from https://google.github.io/googletest/quickstart-cmake.html as part as setting up GoogleTest to use for unittests-----------------------------------

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#End of copied statements from website-------------------------------------------------------------------------------------------------------------------------------------------

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (CodingChallengeRytle "main.cpp"  "Cube.cpp" "Cube.h")

enable_testing()

add_executable (
	UnitTest
	UnitTester.cpp
	Cube.h
	Cube.cpp
)

target_link_libraries(
	UnitTest
	gtest_main
)

include(GoogleTest)
gtest_discover_tests(UnitTest)
