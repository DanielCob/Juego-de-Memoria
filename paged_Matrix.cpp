#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using std::fstream;
using std::ofstream;
using std::ios;

struct card {
    int posX;
    int posY;
    const char* image;
};

class paged_Matrix
{
private:
    fstream vmem;
    int rows = 6, cols = 5;
    card memoryMatrix; //usar para la paginación
    card tempCard1; //propenso a cambiar
    card tempCard2; //propenso a cambiar
    bool temp1 = true;

public:
    paged_Matrix();
    void initializeMemory();
    void buildMatrix(int rows, int cols);
    card seekInMatrix(int i, int j);
    const char* getImage(card c);
    bool isPairs();
};

paged_Matrix::paged_Matrix() {
    buildMatrix(rows, cols);
    tempCard1.image = "lol"; //BORRAR DEFINITIVAMENTE
    tempCard2.image = "xd"; //BORRAR DEFINITIVAMENTE
}

void paged_Matrix::initializeMemory() {
    vmem = fstream("vmemory", ios::in | ios::out | ios::binary);
    if (!vmem.good()) {
        ofstream newFile("vmemory");
        newFile.close();
        vmem = fstream("vmemory", ios::in | ios::out | ios::binary);
    }
}

void paged_Matrix::buildMatrix(int rows, int cols) {
    initializeMemory();
    card matrix[rows][cols];
    for (int i = 0; i < rows; i++) { //construir algoritmo de contrucción de matriz aqui
        for (int j = 0; j < cols; j++) {
            matrix[i][j].posX = i;
            matrix[i][j].posY = j;
            matrix[i][j].image = "imagen fachera";
        }
    }

    vmem.write((char*) &matrix, sizeof(card[rows][cols])); //Escribe en vmem la matriz recién hecha
}

card paged_Matrix::seekInMatrix(int i, int j) {
    card c;
    vmem.seekg(16*cols*i+16*j, ios::beg); //16 es el tamaño en bytes del struct carta.
    vmem.read((char*) &c, sizeof(card)); //escribimos en la nueva matriz los datos de la memoria virtual.
    
    if (temp1) { //muy propenso a cambiar
        tempCard1 = c;
        temp1 = false;
    } else {
        tempCard2 = c;
        temp1 = true;
    }
    return c;
}

const char* paged_Matrix::getImage(card c) {
    return c.image;
}

bool paged_Matrix::isPairs() {
    if (tempCard1.image == tempCard2.image) {
        return true;
    }
    return false;
}

// int main(int argc, char const *argv[]) {
//     paged_Matrix p;
    
//     int i = 2, j=2;

//     cout << p.seekInMatrix(2, 2).posX << endl;
//     cout << p.seekInMatrix(2, 2).posY << endl;
//     cout << p.seekInMatrix(2, 2).image << endl;
//     cout << "Tamaño en bytes de carta: " << sizeof(card) << " bytes" << endl;
//     cout << sizeof(card[3][3]) << endl;
    
//     return 0;
// }