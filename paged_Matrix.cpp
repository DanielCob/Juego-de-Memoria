#include <iostream>
#include <string>
#include <vector>
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
    bool temp = true;

public:
    paged_Matrix();
    void initializeMemory();
    void buildMatrix(int rows, int cols);
    card seekInMatrix(int i, int j);
    vector <const char*> shuffleCards();
    const char* getImage(card c);
    const char* isPairs();
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
    vector <const char*> cards = shuffleCards();
    card matrix[rows][cols];
    int k = 0;
    for (int i = 0; i < rows; i++) { //construir algoritmo de contrucción de matriz aqui
        for (int j = 0; j < cols; j++) {
            matrix[i][j].posX = i;
            matrix[i][j].posY = j;
            matrix[i][j].image = cards[k];
            k++;
        }
    }

    vmem.write((char*) &matrix, sizeof(card[rows][cols])); //Escribe en vmem la matriz recién hecha
}

vector <const char*> paged_Matrix::shuffleCards() {
    vector <const char*> deck = {"gato1", "gato2", "gato3", "gato4", "gato5", "gato6", "gato7", "gato8"
    , "gato9", "gato10", "gato11", "gato12", "gato13", "gato14", "gato15", "gato1", "gato2", "gato3"
    , "gato4", "gato5", "gato6", "gato7", "gato8", "gato9", "gato10", "gato11", "gato12", "gato13"
    , "gato14", "gato15"};

    vector <const char*> shuffledDeck;

    while (!deck.empty())
    {
        size_t rand_index = rand()%deck.size();
        shuffledDeck.push_back(deck[rand_index]);
        deck.erase(deck.begin() + rand_index);
    }
    
    return shuffledDeck;
}

card paged_Matrix::seekInMatrix(int i, int j) {
    card c;
    vmem.seekg(16*cols*i+16*j, ios::beg); //16 es el tamaño en bytes del struct carta.
    vmem.read((char*) &c, sizeof(card)); //escribimos en la nueva matriz los datos de la memoria virtual.
    if (temp) { //muy propenso a cambiar
        tempCard1 = c;
        temp = false;
    } else {
        tempCard2 = c;
        temp = true;
    }
    return c;
}

const char* paged_Matrix::getImage(card c) {
    return c.image;
}

const char* paged_Matrix::isPairs() {
    if (tempCard1.image == tempCard2.image) {
        return "1";
    }
    return "0";
}
