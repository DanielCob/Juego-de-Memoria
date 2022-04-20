/**
 * @file paged_Matrix.cpp
 * @author Daniel Cob Beirute
 * @brief la clase se encarga de administrar la matriz paginada, esto implica almacenar, buscar y paginar cartas
 * @version 0.1
 * @date 2022-04-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>

using namespace std;
using std::fstream;
using std::ofstream;
using std::ios;
/**
 * @brief almacena la posición en X y Y, así como la imagen en base64
 * 
 */
struct card {
    int posX;
    int posY;
    char image[19000];
};

class paged_Matrix
{
private:
    /**
     * @brief objeto utilizado para escribir y leer de vmemory.bin
     * 
     */
    fstream vmem;
    int rows = 5, cols = 6;
    int cardsLeft = rows*cols;
    /**
     * @brief almacena 1/3 de las cartas restantes en memoria
     * 
     */
    vector <card> memoryMatrix;
    /**
     * @brief imagen de la última carta seleccionada
     * 
     */
    string tempCard1; 
        /**
     * @brief imagen de la última carta seleccionada
     * 
     */
    string tempCard2;
    /**
     * @brief indica si alguna de las últimas dos tarjetas estaba en memoria
     * 
     */
    bool inMemory = false;
    bool temp = true;
    int pageHit = 0;
    int pageFault = 0;

public:
    paged_Matrix();
    int get_cardsLeft();
    bool get_inMemory();
    void set_inMemory(bool i);
    void initializeMemory();
    string readImage(const char* i);
    void buildMatrix(int rows, int cols);
    void shuffleMemoryMatrix();
    card seekCard(int i, int j);
    card seekinMatrix(int i, int j, bool shuffle);
    void saveTempCard(string cardImage);
    vector <string> shuffleCards();
    string getImage(card c);
    bool isPairs();
};

paged_Matrix::paged_Matrix() {
    buildMatrix(rows, cols);
    shuffleMemoryMatrix();
}

int paged_Matrix::get_cardsLeft() {
    return cardsLeft;
}

bool paged_Matrix::get_inMemory() {
    return inMemory;
}

void paged_Matrix::set_inMemory(bool i) {
    inMemory = i;
}
/**
 * @brief crea el archivo vmemory.bin para almacenar la matriz en disco
 * 
 */
void paged_Matrix::initializeMemory() {
    vmem = fstream("vmemory", ios::in | ios::out | ios::binary);
    if (!vmem.good()) {
        ofstream newFile("vmemory");
        newFile.close();
        vmem = fstream("vmemory", ios::in | ios::out | ios::binary);
    }
}
/**
 * @brief abre el archivo .txt que contiene la imagen en base64 y la retorna como un string.
 * 
 * @param i número de la imagen
 * @return string imagen en base64
 */
string paged_Matrix::readImage(const char* i){
    ifstream image;
    string img_dir;
    string img_string;
    img_dir.append("img/");
    img_dir.append(i);
    img_dir.append(".txt");
    image.open(img_dir);
    getline(image, img_string);
    image.close();

    return img_string;
}
/**
 * @brief construye la matriz con imagenes aleatorias, luego las escribe en el archivo vmemory.bin
 * 
 * @param rows 
 * @param cols 
 */
void paged_Matrix::buildMatrix(int rows, int cols) {
    initializeMemory();
    vector <string> cards = shuffleCards();
    card matrix[rows][cols];
    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j].posX = i;
            matrix[i][j].posY = j;
            for (int z = 0; z < sizeof(char[19000]); z++) {
                matrix[i][j].image[z] = cards[k][z];
            }
            k++;
        }
    }

    vmem.write((char*) &matrix, sizeof(card[rows][cols])); //Escribe en vmem la matriz recién hecha
}
/**
 * @brief baraja las imagenes y las almacena como un vector de strings
 * 
 * @return vector <string> 
 */
vector <string> paged_Matrix::shuffleCards() {
    vector <string> deck;
    for (int i = 1; i < 16; i++)
    {
        deck.push_back(readImage(to_string(i).c_str()));
        deck.push_back(readImage(to_string(i).c_str()));
    }

    vector <string> shuffledDeck;

    srand(time(0));

    while (!deck.empty())
    {
        size_t rand_index = rand()%(deck.size());
        shuffledDeck.push_back(deck[rand_index]);
        deck.erase(deck.begin() + rand_index);
    }
    
    return shuffledDeck;
}
/**
 * @brief elimina las cartas almacenadas en memoria y las intercambia por otras elegidas aleatoriamente
 * 
 */
void paged_Matrix::shuffleMemoryMatrix() {
    memoryMatrix.clear();
    for (int i = 0; i < cardsLeft/3; i++)
    {
        size_t rand_i = rand()%rows;
        size_t rand_j = rand()%cols;
        memoryMatrix.push_back(seekinMatrix(rand_i, rand_j, true));
    }
    cout << "Cards in memory:" << endl;
    for (int i = 0; i < memoryMatrix.size(); i++) //imprime la matriz
        {
            cout << memoryMatrix[i].posX << memoryMatrix[i].posY << " ";
        }
    cout << endl;
}
/**
 * @brief busca la tarjeta solicitada. Primero realiza la busqueda en la memoria, si no la encuentra le pide a seekinMatrix que la lea en disco
 * 
 * @param i posición en X
 * @param j posición en Y
 * @return card 
 */
card paged_Matrix::seekCard(int i, int j) {
    for (size_t x = 0; x < memoryMatrix.size(); x++) //busca en la matriz en memoria la carta solicitada
    {
        if (memoryMatrix[x].posX == i)
        {
            if (memoryMatrix[x].posY == j)
            {
                pageHit++;
                cout << "pageHits: "<< pageHit << endl;
                saveTempCard(memoryMatrix[x].image);
                inMemory = true;
                return memoryMatrix[x];
            } 
        }
    }
    pageFault++;
    cout << "pageFaults: " << pageFault << endl;
    return seekinMatrix(i, j, false);
}
/**
 * @brief lee la tarjeta solicitada almacenada en disco (vmemory.bin)
 * 
 * @param i posición en X
 * @param j posición en Y
 * @param shuffle indica si el algoritmo se está solicitando para la fase de shuffle
 * @return card 
 */
card paged_Matrix::seekinMatrix(int i, int j, bool shuffle) {
    card c; //busca en la matriz en disco
    vmem.seekg(sizeof(card)*cols*i+sizeof(card)*j, ios::beg); //18009 es el tamaño en bytes del struct carta.
    vmem.read((char*) &c, sizeof(card)); //leemos de la matriz los datos de la memoria virtual.
    if (!shuffle) {    
        size_t rand_index = rand()%(memoryMatrix.size()+1);
        memoryMatrix[rand_index] = c; // se realiza el swap
        saveTempCard(c.image);
        cout << "Cards in memory:" << endl;
        for (int i = 0; i < memoryMatrix.size(); i++) //imprime la matriz
        {
            cout << memoryMatrix[i].posX << memoryMatrix[i].posY << " ";
        }
        cout << endl;
    }

    return c;
}
/**
 * @brief almacena la última imagen solicitada
 * 
 * @param cardImage string de la imagen
 */
void paged_Matrix::saveTempCard(string cardImage) {
        if (temp) {
        tempCard1 = cardImage;
        temp = false;
    } else {
        tempCard2 = cardImage;
        temp = true;
    }
}

string paged_Matrix::getImage(card c) {
    return c.image;
}
/**
 * @brief verifica si las últimas dos tarjetas solicitadas tienen las misma imagen
 * 
 * @return true 
 * @return false 
 */
bool paged_Matrix::isPairs() {
    if (tempCard1 == tempCard2) {
        cardsLeft -= 2;
        shuffleMemoryMatrix();
        return true;
    }
    return false;
}
