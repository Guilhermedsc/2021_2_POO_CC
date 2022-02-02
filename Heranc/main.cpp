#include <bits/stdc++.h>
using namespace std;

class ANIMAL{
    bool vida {true};

public:
    ANIMAL(){
        cout << "Animal criado" << endl;
    }

    virtual void comer(){
        cout << "Animal comendo" << endl;
    }

    virtual void morrer(){
        vida = false;
        cout << "Animal morreu" << endl;
    }
};

class PEIXE : public ANIMAL{
    bool temAgua {true};
    string porte {""};

public:
    PEIXE(string porte, bool temAgua) : porte(porte), temAgua(temAgua){
        cout << "Peixe de porte " << porte << " criado" << endl;
    }

    virtual void nadar(){
        if(!temAgua){
            cout << "Sem agua o peixe nao pode nadar e viver" << endl;
            ANIMAL::morrer();
            return;
        }
        cout << "Peixe de porte " << porte << " nadando" << endl;
    }
};

class TUBARAO : public PEIXE{
    int fome {0}; //5 morre 

public:
    TUBARAO(int fome, string porte, bool temAgua) : PEIXE(porte, temAgua), fome(fome){
        cout << "Tubarao criado com fome: " << fome << endl;
    }

    void comer(){
        fome--;
        cout << "Tubarao comendo. Fome: " << fome << endl;
        ANIMAL::comer();
    }

    void nadar(){
        PEIXE::nadar();
        fome++;
    }

    void morrer(){
        if(fome == 5){
            cout << "Tubarao morreu por fome" << endl;
            ANIMAL::morrer();
            return;
        }    
    }

};

int main(){
    TUBARAO tubarao(5, "grande", true);
    ANIMAL &animal = tubarao;
    PEIXE &peixe = tubarao;
    animal.comer();
    peixe.nadar();
    animal.morrer();
}