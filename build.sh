clear

# Limpiar directorio de compilación
mkdir -p build
rm -rf build/*

# Compilar los archivos fuente
g++ -c -std=c++17 -I./include main.cpp -o build/main.o
g++ -c -std=c++17 -I./include src/ECA/Rule30.cpp -o build/Rule30.o

g++ -c -std=c++17 -I./include src/FileController.cpp -o build/FileController.o
g++ -c -std=c++17 -I./include src/PrimeGenerator.cpp -o build/PrimeGenerator.o
g++ -c -std=c++17 -I./include src/Functions.cpp -o build/Functions.o

# Enlazar los objetos y generar el ejecutable
g++ build/main.o \
    build/FileController.o build/PrimeGenerator.o build/Functions.o \
    build/Rule30.o \
    -o build/main.exe 

# Ejecutar el programa
time ./build/main.exe