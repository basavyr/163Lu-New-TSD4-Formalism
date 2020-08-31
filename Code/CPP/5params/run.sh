clang++ -std=c++17 -Xpreprocessor -fopenmp ./src/app.cpp ./src/energies.cpp ./src/rms.cpp main.cpp -o ./out/a.out -lomp
./out/a.out
