cmake_minimum_required (VERSION 3.9)

project(interrogation_2021)

set(SRCS "interrogation_2021.cpp")
add_executable (interrogation_2021 ${SRCS})
target_compile_features(interrogation_2021 PUBLIC cxx_std_17)
add_compile_options("-Wall")
