cmake_minimum_required(VERSION 3.20.0)
project(map-diplom VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB project
    src/*
)
add_executable(map-diplom ${project})

