#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

long long hashcode(long long x);
void printTree(struct node* arvore);
void printTree2(struct node* arvore);
void printLevelOrder(node* arvore);
void printLevel(node* arvore, long nivel);

struct node {
    long chave;
    long long hash;
    int nivel;          //TODO probs depois vai ser o que uso para imprimir as cenas por nivel
    struct node *esquerdo;
    struct node *direito;
    struct node *pai;
};

vector<node> elementosIniciais;
vector<node> elementosTotais;
struct node *head;
int nrNodes = 1;
long nNiveis;

void addBegin(long chave, long hash, long nivel) {
    //struct node* novo = (struct node*)malloc(sizeof(struct node));
    struct node* novo = new node;

    novo->chave = chave;            //defini�ao das variaveis do elemento novo
    novo->hash = hash;
    novo->nivel = nivel;
    novo->esquerdo = NULL;
    novo->direito = NULL;
    novo->pai = NULL;

    if (nivel == 1) {
        head = novo;
        printLevelOrder(head);
        return;
    }

    elementosIniciais.push_back(*novo);
    elementosTotais.push_back(*novo);
    nrNodes++;
            //cout << "confirm added in addBegin(): " << chave << " hash: " << hash << "\n";
}

void buildCycle(vector<node> camadaAbaixo, long nivel) {
    vector<node> currentElementos;

    if (nivel == 0) {
        return;
    }
    for (long unsigned int i = 0; i < (camadaAbaixo.size() / 2); i++) {           
        struct node* novo = new node;

        node *elEsq = &camadaAbaixo[0 + i * 2];
        node *elDir = &camadaAbaixo[1 + i * 2];

        novo->chave = nrNodes;
        novo->hash = hashcode(elEsq->hash + elDir->hash);
        novo->nivel = nivel;
        novo->esquerdo = elEsq;
        novo->direito = elDir;
        novo->pai = NULL;

        elEsq->pai = novo;
        elDir->pai = novo;

        currentElementos.push_back(*novo);
        elementosTotais.push_back(*novo);
        nrNodes++;

        if (nivel == 1) {
            head = novo;
            printLevelOrder(head);
            return;
        }
        if (nivel > 1) {
                    //isto est� aqui dentro do ciclo e nao fora porque se nao os ponteiros saem do scope e ficam sem um valor que seja util, logo preciso de fazer tudo dentro do buildCycle()
            buildCycle(currentElementos, nivel - 1);
        }
    }   
    
    return;
}

//Replaced it with ht printLevels functions
/*
void printTree(struct node *arvore) {

            //cout << "/////////////////////printing begins\n";
            //cout << "id: " << arvore->chave << " hash: " <<arvore->hash << "\n" << "arvoreEsqeurda chave: " << arvore->esquerdo->chave << "arvoreDireita chave: " << arvore->direito->chave << "\n";
            //cout << "esquerdo: " << arvore->esquerdo->hash << "\n";
    cout << arvore->hash << "\n";
    cout << arvore->esquerdo->hash << "\n";
    cout << arvore->direito->hash << "\n";
    if (arvore->esquerdo != NULL) {
        printTree2(arvore->esquerdo); 
    }
    if (arvore->direito != NULL) {
        printTree2(arvore->direito);
    }
}

//TODO not displaying correct answer
void printTree2(struct node* arvore) {

    //cout << "/////////////////////printing begins\n";
    //cout << "id: " << arvore->chave << " hash: " <<arvore->hash << "\n" << "arvoreEsqeurda chave: " << arvore->esquerdo->chave << "arvoreDireita chave: " << arvore->direito->chave << "\n";
    //cout << "esquerdo: " << arvore->esquerdo->hash << "\n";

    if (arvore->esquerdo != NULL && arvore->direito != NULL) {
        
        cout << arvore->esquerdo->hash << "\n";
        cout << arvore->direito->hash << "\n";
        printTree2(arvore->esquerdo);
        printTree2(arvore->direito);
        

    }
    
    if (arvore->esquerdo != NULL) {
        printTree2(arvore->esquerdo);
    }
    if (arvore->direito != NULL) {
        printTree2(arvore->direito);
    }
    
}
*/

long long hashcode(long long x) {
    return x % 1000000007;
}

void printLevelOrder(node *arvore)        //probs trocar a height pelo nNiveis e fazer inverso
{
    int h = nNiveis;
    int i;
    for (i = 1; i <= h; i++)
        printLevel(arvore, i);
}

void printLevel(node * arvore, long nivel)
{
    if (arvore == NULL)
        return;
    if (nivel == 1)
        cout << arvore->hash << "\n";
    else if (nivel > 1)
    {
        printLevel(arvore->esquerdo, nivel - 1);
        printLevel(arvore->direito, nivel - 1);
    }
}

int main()
{
    long nrFolhas;
    int atual = 0;
    vector<long long> elementos;
    long long input;

    cin >> nrFolhas;
    long nNiveisD = log2(nrFolhas) + 1.0;
    if (nNiveisD == 0) {
        nNiveisD = 1;
    }
    nNiveis = (long)nNiveisD;

    while (atual < nrFolhas) {      //preenche o vetor que tem todos os valores de hash das folhas
        cin >> input;

        elementos.push_back(input);
        atual++;
    }
    for (int i = 1; i < nrFolhas + 1; i++) {
        addBegin(i, hashcode(elementos[i - 1]), nNiveis);
    }
    buildCycle(elementosIniciais, nNiveisD - 1); 
}

