#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
ifstream f("mergeheap.in");
ofstream g("mergeheap.out");
struct nod{
    int val;
    int grad;
    nod *fiu;
    nod *parinte;
    nod *st;
    nod *dr;
    bool marcat;
};
class heapfibonacci
{
    int noduri;
    nod *maxim;
public:
    heapfibonacci();
    ~heapfibonacci();
    void insereazanod(int nr);
    int extragemaxim();
    void reuniuneheap(heapfibonacci &heap);

    nod *reuniunenoduri(nod *x, nod *y);
    void curata(nod *x);
    void mutacopii(nod *copil);
    nod *izoleazamaxim();
    void consolideaza();
    void adaugacopil(nod *copil, nod *tata);
    void stergedinlista(nod *x);

    void cresteval(nod *x, int valnoua);
    void taie(nod *copil, nod *tata);
    void taiemarcat(nod *tata);
    void stergenod(nod *x);
    void scadeval(nod *x, int valnoua);
    nod *getmaxim()
    {
        return maxim;
    }
};
void heapfibonacci::stergedinlista(nod *x)
{
    if (x->dr == x)
        return;
    (x->st)->dr = x->dr;
    (x->dr)->st = x->st;
    x->st = x->dr = x;
}
heapfibonacci::heapfibonacci()
{
    maxim = nullptr;
    noduri = 0;
}
heapfibonacci::~heapfibonacci()
{
    curata(maxim);
}
void heapfibonacci::curata(nod *x)
{
    if(x != nullptr)
    {
        nod *temp = x;
        do
        {
            nod *aux = temp;
            temp = temp->dr;
            curata(aux->fiu);
            delete aux;
        }while(temp != x);
    }
}
void heapfibonacci::insereazanod(int nr)
{
    nod *n = new nod;
    n->val = nr;
    n->grad = 0;
    n->fiu = nullptr;
    n->parinte = nullptr;
    n->st = n;
    n->dr = n;
    n->marcat = false;
    maxim = reuniunenoduri(maxim, n);
    noduri++;
}
nod *heapfibonacci::reuniunenoduri(nod *x, nod *y)
{
    if(x == nullptr)
        return y;
    if(y == nullptr)
        return x;
    if(x->val < y->val)
    {
        nod *temp = x;
        x = y;
        y = temp;
    }
    nod *fost_dreapta_x = x->dr;
    nod *fost_stanga_y = y->st;
    x->dr = y;
    y->st = x;
    fost_dreapta_x->st = fost_stanga_y;
    fost_stanga_y->dr = fost_dreapta_x;
    return x;
}
void heapfibonacci::reuniuneheap(heapfibonacci &heap)
{
    maxim = reuniunenoduri(maxim, heap.maxim);
    noduri += heap.noduri;
    heap.maxim = nullptr;
    heap.noduri = 0;
}
void heapfibonacci::mutacopii(nod *copil)
{
    if(copil == nullptr)
        return;
    nod *temp = copil;
    do
    {
        temp->parinte = nullptr;
        temp = temp->dr;
    }while(copil != temp);
}
int heapfibonacci::extragemaxim()
{
    if(maxim != nullptr)
    {
        nod *maxsters = izoleazamaxim();
        int valoare = maxsters->val;
        delete maxsters;
        return valoare;
    }
    cout << "Heap gol ";
    return 0;
}
nod *heapfibonacci::izoleazamaxim()
{
    nod *maxim_curr = maxim;
    if(maxim_curr == nullptr)
    {
        return nullptr;
    }
    mutacopii(maxim_curr->fiu);
    reuniunenoduri(maxim_curr, maxim_curr->fiu);
    if(maxim_curr == maxim_curr->dr)
    {
        maxim = nullptr;
    }else
    {
        maxim = maxim_curr->dr;
    }

    stergedinlista(maxim_curr);
    if(maxim != nullptr)
    {
        consolideaza();
    }
    noduri--;
    return maxim_curr;
}
void heapfibonacci::adaugacopil(nod *copil, nod *tata)
{
    copil->parinte = tata;
    tata->fiu = reuniunenoduri(tata->fiu, copil);
    tata->grad++;
    copil->marcat = false;
}
void heapfibonacci::consolideaza()
{
    int copie = noduri;
    int casute = 0;
    while(copie > 0)
    {
        copie >>= 1;
        casute++;
    }
    nod *duble[casute];
    for(int i = 0; i <= casute; i++)
    {
        duble[i] = nullptr;
    }
    vector<nod*> radacini;
    nod *node = maxim;

    do
    {
        radacini.push_back(node);
        node = node->dr;
    } while (node != maxim);


    for (nod *curent : radacini)
    {
        int grd = curent->grad;
        stergedinlista(curent);

        while(duble[grd] != nullptr)
        {
            if (curent->val < duble[grd]->val)
            {
                nod *temp = curent;
                curent = duble[grd];
                duble[grd] = temp;
            }
            adaugacopil(duble[grd], curent);
            duble[grd] = nullptr;
            grd++;
        }

        duble[grd] = curent;
        maxim = curent;
    }



    for (int i = 0; i <= casute; i++)
    {
        if (duble[i] != nullptr && duble[i] != maxim)
        {
            reuniunenoduri(maxim, duble[i]);
        }
    }

    nod* primul = maxim;
    nod* curent = maxim;
    do{
        if (curent->val > maxim->val)
        {
            maxim = curent;
        }
        curent = curent->dr;
    } while (curent != primul);
}
void heapfibonacci::cresteval(nod *x, int valnoua)
{
    x->val = valnoua;
    if(x->parinte != nullptr && x->val > x->parinte->val)
    {
        taie(x, x->parinte);
        taiemarcat(x->parinte);
    }
    if(x->val > maxim->val)
        maxim = x;
}
void heapfibonacci::taie(nod *copil, nod *tata)
{
    if(copil == copil->dr)
    {
        tata->fiu = nullptr;
    }
    else
    {
        tata->fiu = copil->dr;
    }
    stergedinlista(copil);
    copil->parinte = nullptr;
    copil->marcat = false;
    tata->grad--;
    reuniunenoduri(maxim, copil);
}
void heapfibonacci::taiemarcat(nod *tata)
{
    if(tata->parinte != nullptr)
    {
        if(tata->marcat == true)
        {
            taie(tata, tata->parinte);
            taiemarcat(tata->parinte);
        }
        else
        {
            tata->marcat = true;
        }
    }
}
void heapfibonacci::stergenod(nod *x)
{
    cresteval(x, 2147483647);
    extragemaxim();
}
void heapfibonacci::scadeval(nod *x, int valnoua)
{
    if(valnoua < x->fiu->val)
    {
        stergenod(x);
        insereazanod(valnoua);
    }
}
int main()
{
    heapfibonacci f1;
    heapfibonacci g1;
    f1.insereazanod(17);
    f1.insereazanod(12);
    f1.insereazanod(9);
    f1.insereazanod(2);
    g1.insereazanod(121);
    g1.insereazanod(183);
    g1.insereazanod(340);
    g1.insereazanod(490);
    cout << f1.extragemaxim() << " ";
    cout << f1.extragemaxim() << " ";
    f1.reuniuneheap(g1);
    cout << f1.extragemaxim() << " ";
    f1.scadeval(f1.getmaxim(), -32);
    cout << f1.extragemaxim() << " ";
    cout << f1.extragemaxim() << " ";
    cout << f1.extragemaxim() << " ";
    cout << f1.extragemaxim() << " ";
    f1.stergenod(f1.getmaxim());
    cout << f1.extragemaxim() << " ";


    return 0;
}
