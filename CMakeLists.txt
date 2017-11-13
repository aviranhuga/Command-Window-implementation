cmake_minimum_required(VERSION 3.8)
project(Ass1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/BaseCommand.cpp src/PwdCommand.cpp include/Commands.h include/Files.h include/Environment.h src/BaseFile.cpp src/Directory.cpp src/File.cpp src/testMain.cpp src/testMain.cpp include/FileSystem.h src/FileSystem.cpp src/Environment.cpp src/ErrorCommand.cpp src/LsCommand.cpp src/MkdirCommand.cpp src/CdCommand.cpp)
#set(SOURCE_FILES include/Commands.h include/Environment.h include/Files.h include/FileSystem.h include/GlobalVariables.h src/BaseFile.cpp src/Main.cpp src/File.cpp src/Directory.cpp)
add_executable(Ass1 ${SOURCE_FILES})