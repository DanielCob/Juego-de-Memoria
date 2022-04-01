#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using std::fstream;
using std::ofstream;
using std::ios;

fstream vmem;
int rows = 3, cols = 3;

struct card {
    int posX;
    int posY;
    const char* image;
};

void initializeMemory() {
    vmem = fstream("vmemory", ios::in | ios::out | ios::binary);
    if (!vmem.good()) {
        ofstream newFile("vmemory");
        newFile.close();
        vmem = fstream("vmemory", ios::in | ios::out | ios::binary);
    }
};

void buildMatrix(int rows, int cols) {
    initializeMemory();
    card matrix[rows][cols];
    for (int i = 0; i < rows; i++) { //construir algoritmo de contrucción aqui
        for (int j = 0; j < cols; j++) {
            matrix[i][j].posX = i;
            matrix[i][j].posY = j;
            matrix[i][j].image = "imagen fachera";
        }
    }

    vmem.write((char*) &matrix, sizeof(card[rows][cols])); //Escribe en vmem la matriz recién hecha
};

int main() {
    initializeMemory();
    buildMatrix(rows, cols);
    
    card new_matrix; // se crea una nueva matriz

    int i = 2, j=2;
    
    vmem.seekg(16*cols*i+16*j, ios::beg); //16 es el tamaño en bytes del struct carta.
    vmem.read((char*) &new_matrix, sizeof(card)); //escribimos en la nueva matriz los datos de la memoria virtual.

    cout << new_matrix.posX << endl;
    cout << new_matrix.posY << endl;
    cout << new_matrix.image << endl;
    cout << "Tamaño en bytes de carta: " << sizeof(card) << " bytes" << endl;
    cout << sizeof(card[3][3]) << endl;
    
    return 0;
}