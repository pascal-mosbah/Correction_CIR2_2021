cmake_minimum_required (VERSION 3.9)

project(Partiel_2021)

set(SRCS "Partiel_2021.cpp")
add_executable (Partiel_2021 ${SRCS})
target_compile_features(Partiel_2021 PUBLIC cxx_std_17)
add_compile_options("-Wall")
