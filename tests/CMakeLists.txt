# [1] Setup the executable that will run the tests.

add_executable(${TEST_DRIVER} 
    main.cpp  # Arquivo principal de testes
    ${CMAKE_SOURCE_DIR}/src/neander/neander.cpp
    ${CMAKE_SOURCE_DIR}/src/neander/memoria.cpp
    ${CMAKE_SOURCE_DIR}/src/neander/instrucao.cpp
    ${CMAKE_SOURCE_DIR}/src/neander/ula.cpp
)

target_compile_options(${TEST_DRIVER} PRIVATE -Wall -pedantic -g)
set_target_properties( ${TEST_DRIVER} PROPERTIES CXX_STANDARD 17 )


# Configurações de compilação
target_compile_options(${TEST_DRIVER} PRIVATE -Wall -pedantic -g)
set_target_properties(${TEST_DRIVER} PROPERTIES CXX_STANDARD 17)

# [2] Define where the binary will be output to.
set_target_properties(${TEST_DRIVER} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# [3] Incluir diretórios com cabeçalhos
target_include_directories(${TEST_DRIVER} PRIVATE ${CMAKE_SOURCE_DIR}/inc
)
