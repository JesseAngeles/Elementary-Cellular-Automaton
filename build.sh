clear

# Limpiar directorio de compilación
mkdir -p build
rm -rf build/*

# Compilar los archivos fuente
g++ -c -std=c++17 -I./include main.cpp -o build/main.o

g++ -c -std=c++17 -I./include src/Functions.cpp -o build/Functions.o

g++ -c -std=c++17 -I./include src/ECA/ElementaryCellularAutomaton.cpp -o build/ECA.o

g++ -c -std=c++17 -I./include src/GUI/Grapher.cpp        -o build/Grapher.o
g++ -c -std=c++17 -I./include src/GUI/EvolutionFrame.cpp -o build/EvolutionFrame.o
g++ -c -std=c++17 -I./include src/GUI/Frame.cpp          -o build/Frame.o
g++ -c -std=c++17 -I./include src/GUI/Button.cpp         -o build/Button.o
g++ -c -std=c++17 -I./include src/GUI/TextBox.cpp        -o build/TextBox.o

# Enlazar los objetos y generar el ejecutable
g++ build/main.o \
    build/Functions.o \
    build/ECA.o \
    build/Grapher.o build/EvolutionFrame.o build/Frame.o build/Button.o build/TextBox.o \
    -o build/main.exe \
    -Iinclude -lsfml-graphics -lsfml-window -lsfml-system

# Ejecutar el programa
./build/main.exe