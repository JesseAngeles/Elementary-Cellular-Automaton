clear

# Limpiar directorio de compilación
mkdir -p build
rm -rf build/*
# rm -rf resources/*

# Compilar los archivos fuente
g++ -c -std=c++17 -I./include main.cpp -o build/main.o
g++ -c -std=c++17 -I./include src/ECA/ElementaryCellularAutomaton.cpp -o build/ECA.o
g++ -c -std=c++17 -I./include src/ECA/Rule30.cpp -o build/Rule30.o
g++ -c -std=c++17 -I./include src/ECA/Rule30.analisis.cpp -o build/Rule30.analisis.o

g++ -c -std=c++17 -I./include src/FileController.cpp -o build/FileController.o
g++ -c -std=c++17 -I./include src/PrimeGenerator.cpp -o build/PrimeGenerator.o
g++ -c -std=c++17 -I./include src/Functions.cpp -o build/Functions.o

# g++ -c -std=c++17 -I./include src/GUI/Grapher.cpp        -o build/Grapher.o
# g++ -c -std=c++17 -I./include src/GUI/EvolutionFrame.cpp -o build/EvolutionFrame.o
# g++ -c -std=c++17 -I./include src/GUI/Frame.cpp          -o build/Frame.o
# g++ -c -std=c++17 -I./include src/GUI/Button.cpp         -o build/Button.o
# g++ -c -std=c++17 -I./include src/GUI/TextBox.cpp        -o build/TextBox.o

# Enlazar los objetos y generar el ejecutable
g++ build/main.o \
    build/FileController.o build/PrimeGenerator.o build/Functions.o \
    build/ECA.o build/Rule30.o build/Rule30.analisis.o\
    -o build/main.exe 
    # build/Grapher.o build/EvolutionFrame.o build/Frame.o build/Button.o build/TextBox.o \
    # -Iinclude -lsfml-graphics -lsfml-window -lsfml-system

# Ejecutar el programa
time ./build/main.exe