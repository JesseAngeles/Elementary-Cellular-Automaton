clear

# Limpiar directorio de compilación
mkdir -p build
rm -rf build/*
# rm -rf resources/*

# Compilar los archivos fuente
g++ -c -std=c++17 -I./include main.cpp -o build/main.o
g++ -c -std=c++17 -I./include src/ECA/ElementaryCellularAutomaton.cpp -o build/ECA.o
g++ -c -std=c++17 -I./include src/FileController.cpp -o build/FileController.o
g++ -c -std=c++17 -I./include src/PrimeGenerator.cpp -o build/PrimeGenerator.o



# Enlazar los objetos y generar el ejecutable
g++ build/main.o \
    build/ECA.o \
    build/FileController.o \
    build/PrimeGenerator.o \
    -o build/main.exe

# Ejecutar el programa
time ./build/main.exe