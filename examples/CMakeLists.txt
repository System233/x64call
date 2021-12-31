
add_executable(NtCreateThreadEx NtCreateThreadEx.cpp)
target_link_libraries(NtCreateThreadEx x64call)
add_executable(TargetHost TargetHost.cpp)
target_link_libraries(TargetHost x64call)
add_executable(TestC TestC.c)
target_link_libraries(TestC x64call)
add_executable(TestCPP TestCPP.cpp)
target_link_libraries(TestCPP x64call)