//#include <iostream>
//#include <stdio.h>
//#include <queue>
//#include <stdlib.h>
//#include <algorithm>
//#include <cstring>
//#include <functional>


#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3


using namespace std;

struct vrchol {
    int x=0, y=0;
    struct vrchol *deti[4];
    int cesty[4] = {-1,-1,-1,-1};
};

struct node {
    int x=0, y=0;
    struct node *parent;
    int cena;
};

class Comparator {
public:
    bool operator() (const struct node *a, const struct node *b) {
        return a->cena > b->cena;
    }
};

bool isLeft(node *current, vrchol *ciel) {
    if(current->parent == NULL){
        return false;
    }
    if(current->parent->x == current->x){
        if(current->parent->y+1 == current->y){     //z hora
            return (ciel->y == current->y && ciel->x == current->x + 1);
        } else {                                    //z dola
            return (ciel->y == current->y && ciel->x == current->x - 1);
        }
    } else {
        if(current->parent->x+1 == current->x){     //z lava
            return (ciel->y == current->y - 1 && ciel->x == current->x);
        } else{                                     //z prava
            return (ciel->y == current->y + 1 && ciel->x == current->x);
        }
    }
}

int traversal(int velkost, vrchol *graf){
    std::priority_queue<struct node*, std::vector<struct node*>, Comparator> fronta;
    struct node *tmp = (node *) malloc(sizeof(struct node));
    int visited[200][200][4] = {};
    tmp->cena=0;
    tmp->x=0;
    tmp->y=0;
    tmp->parent=NULL;
    fronta.push(tmp);
    tmp=fronta.top();
    fronta.pop();
    while (!(tmp->y == velkost-1 && tmp->x == velkost-1)){
        for (int j = 0; j < 4; j++) {
            struct node *tmp2 = (node *) malloc(sizeof(struct node));
            if(visited[tmp->y][tmp->x][j]==0) {
                if (graf[tmp->x + tmp->y * velkost].cesty[j] != -1) {
                    if (tmp->parent == NULL || graf[tmp->x + tmp->y * velkost].deti[j]->y != tmp->parent->y ||
                        graf[tmp->x + tmp->y * velkost].deti[j]->x != tmp->parent->x) {
                        if (!isLeft(tmp, graf[tmp->x + tmp->y * velkost].deti[j]) ||
                                tmp->x == 0 || tmp->y == 0 || tmp->x == velkost-1 || tmp->y == velkost-1) {
                            tmp2->x = graf[tmp->x + tmp->y * velkost].deti[j]->x;
                            tmp2->y = graf[tmp->x + tmp->y * velkost].deti[j]->y;
                            tmp2->cena = tmp->cena + graf[tmp->x + tmp->y * velkost].cesty[j];
                            tmp2->parent = tmp;
                            visited[tmp->y][tmp->x][j] = 1;
                            fronta.push(tmp2);
                        }
                    }
                }
            }
        }
        tmp=fronta.top();
        fronta.pop();
    }
    cout << tmp->cena << endl;

}

void start(){
    int velkost;
    cin >> velkost;
    struct vrchol graf[velkost][velkost];
    graf[0][0].x = 0;
    graf[0][0].y = 0;
    for (int y = 0; y < velkost * 2 - 1; y++) {
        int cena;
        if(y % 2 == 0){
            for (int x = 0; x < velkost-1; x++) {
                cin >> cena;
                graf[y/2][x].deti[RIGHT] = &graf[y/2][x+1];
                graf[y/2][x].deti[RIGHT]->cesty[LEFT] = cena;
                graf[y/2][x].deti[RIGHT]->deti[LEFT] = &graf[y/2][x];
                graf[y/2][x].cesty[RIGHT] = cena;
                graf[y/2][x].deti[RIGHT]->x = x+1;
                graf[y/2][x].deti[RIGHT]->y = y/2;

            }
        } else {
            for (int x = 0; x < velkost; x++) {
                cin >> cena;
                graf[(y-1)/2][x].deti[DOWN] = &graf[y/2+1][x];
                graf[(y-1)/2][x].deti[DOWN]->cesty[UP] = cena;
                graf[(y-1)/2][x].deti[DOWN]->deti[UP] = &graf[(y-1)/2][x];
                graf[(y-1)/2][x].cesty[DOWN] = cena;
                graf[(y-1)/2][x].deti[DOWN]->x = x;
                graf[(y-1)/2][x].deti[DOWN]->y = (y+1)/2;
            }
        }
    }
    traversal(velkost,(struct vrchol *)graf);
}

int main() {
    int vstupov;
    cin >> vstupov;
    for (int i = 0; i < vstupov; ++i) {
        start();
    }
    return 0;
}
