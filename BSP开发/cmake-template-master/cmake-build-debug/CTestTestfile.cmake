# CMake generated Testfile for 
# Source directory: E:/SoftwareProject/cmake-template-master
# Build directory: E:/SoftwareProject/cmake-template-master/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_add "E:/SoftwareProject/cmake-template-master/cmake-build-debug/test_add.exe")
set_tests_properties(test_add PROPERTIES  _BACKTRACE_TRIPLES "E:/SoftwareProject/cmake-template-master/CMakeLists.txt;149;add_test;E:/SoftwareProject/cmake-template-master/CMakeLists.txt;0;")
add_test(test_minus "E:/SoftwareProject/cmake-template-master/cmake-build-debug/test_minus.exe")
set_tests_properties(test_minus PROPERTIES  _BACKTRACE_TRIPLES "E:/SoftwareProject/cmake-template-master/CMakeLists.txt;150;add_test;E:/SoftwareProject/cmake-template-master/CMakeLists.txt;0;")
add_test(test_gtest_demo "E:/SoftwareProject/cmake-template-master/cmake-build-debug/test_gtest_demo.exe")
set_tests_properties(test_gtest_demo PROPERTIES  _BACKTRACE_TRIPLES "E:/SoftwareProject/cmake-template-master/CMakeLists.txt;151;add_test;E:/SoftwareProject/cmake-template-master/CMakeLists.txt;0;")
subdirs("src/c/math")
subdirs("src/c/nn")
subdirs("third_party/googletest-release-1.10.0")
