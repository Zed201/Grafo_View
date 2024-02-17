cmake_minimum_required(VERSION 3.0)
project(Grafo_View)

# Encontrar o pacote Python
find_package(Python REQUIRED COMPONENTS Development)

# Adicionar o diretório de cabeçalhos do Python
include_directories(${Python_INCLUDE_DIRS})

# Definir os arquivos fonte do seu projeto
set(SOURCE_FILES index.cpp)

# Adicione o executável do seu projeto
add_executable(Grafo_View ${SOURCE_FILES})

# Link com a biblioteca Python
target_link_libraries(Grafo_View ${Python_LIBRARIES})
