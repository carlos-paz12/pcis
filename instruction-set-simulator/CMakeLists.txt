cmake_minimum_required(VERSION 3.10)

# Define o nome do projeto
project(InstructionSetSimulator)

# Define o padrão de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Adiciona o diretório src
include_directories(src)

# Adiciona os arquivos fonte
file(GLOB SOURCES
    src/*.cpp
)

# Cria o executável
add_executable(InstructionSetSimulator ${SOURCES})