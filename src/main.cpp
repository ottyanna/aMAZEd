#include <iostream>
#include <vector>

using namespace std;

//tipo di archi
enum MazeEdge{

    WALL, //è zero, all'inizio nessuno è collegato
    FREE
    //START, //non qui
    //END

};


// Formato COO
class EdgeAdjMatrix {

    int node;
    int adj;
    MazeEdge type; //magari di tipo puntatore al nodo, così ha lui dentro la variabile e non ho due liste?

    public: //se no figlio di maze no??

    EdgeAdjMatrix(int _node, int _adj) {
        node=_node;
        adj=_adj;
        type=WALL;
    }

    void print();
};


class Maze {

    vector<EdgeAdjMatrix> adjMatrix; //array? 
    
    public:
    void initGrid(int,int,int,int);
    void print();

};

void Maze::initGrid(int start, int finish, int sizeR, int sizeC) { //nodefault per sizeC?? //start e finish come li uso nel ptr???

    int k; //counter for me
    for(int u=0; u < sizeC*sizeR ; u++) { //simmetria portami via //questa è come potessi andare solo a dx e sotto
        if((u+1)%sizeR!=0 && (u+1)<sizeC*sizeR) {
            adjMatrix.push_back(EdgeAdjMatrix(u,u+1)); //adiacenti destra e sinistra
            k++;
        }
        if(u+sizeR<sizeC*sizeR)
            adjMatrix.push_back(EdgeAdjMatrix(u,u+sizeR)); k++; //adiacenti giù e su
    }
    
}

void EdgeAdjMatrix::print(){

    cout<<endl;
    cout << this->node << " ";
    cout << this->adj;
    cout << "-----" << endl;

}

void Maze::print(){

    for(auto elem: adjMatrix)
        elem.print();

    cout << endl;
    cout << sizeof(adjMatrix);

}



int main(){
cout << "hello world";

Maze m;
m.initGrid(0,8,3,3);
m.print();

return 0;



} 
