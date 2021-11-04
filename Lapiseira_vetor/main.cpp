#include <bits/stdc++.h>
using namespace std;

struct GRAFITE {
    float calibre;
    string dureza;
    int tamanho;

    GRAFITE(float calibre=0, string dureza="", int tamanho=0) : calibre(calibre), dureza(dureza), tamanho(tamanho) {}

    friend ostream &operator<<(ostream &os, const GRAFITE &lapiseira) {
        os << "Grafite: " << lapiseira.calibre << ", " << lapiseira.dureza << ", " << lapiseira.tamanho << "." << endl;
        return os;
    }

    int desg_folha(){
        if(this->dureza == "HB"){ return 1;}
        else if(this->dureza == "2B"){ return 2;}
        else if(this->dureza == "4B"){ return 4;}
        else if(this->dureza == "6B"){ return 6;}
        else{ return 0;}
    }
};

struct LAPISEIRA{
    float calibre;
    vector<GRAFITE> grafite;

    LAPISEIRA(float calibre=0): calibre(calibre){}

    friend ostream &operator<<(ostream &os, const LAPISEIRA &lapiseira){
        os << "Calibre: " << lapiseira.calibre << "\n";
        if(lapiseira.grafite.empty()){ os << "Grafite: null\n"; }
        else{  
            for(int i=0; i<(int)lapiseira.grafite.size(); i++){
                os << lapiseira.grafite[i];
            }
        }
        return os;
    }

    bool inserir_grafite(GRAFITE &grafite){
        if(grafite.calibre != this->calibre){
            cout << "Calibre incompativel" << endl;
            return true;
        }
        if((int)this->grafite.size() == 4){
            cout << "Grafite completo" << endl;
            return true;
        }
        this->grafite.push_back(grafite);
        return true;
    }

    vector<GRAFITE> remover_grafite(int i){
        if(this->grafite.empty()){
            cout << "Grafite vazio" << endl;
            return this->grafite;
        }
        vector<GRAFITE> grafite_aux = this->grafite;
        this->grafite.erase(this->grafite.begin()+i);
        return grafite_aux;
    }

    void escrever_folha(int folhas){
        int aux = 0;
        
        if(this->grafite.empty()){
            cout << "Grafite vazio" << endl;
        }else{
            for(int i=0; i<(int)this->grafite.size(); i++){
                while(this->grafite[i].tamanho > 0 && folhas > 0){
                    this->grafite[i].tamanho -= this->grafite[i].desg_folha();
                    if(this->grafite[i].tamanho >= 0){
                        folhas--;
                        aux++;
                    }
                    if(this->grafite[i].tamanho <= 0){
                        this->grafite.erase(this->grafite.begin()+i);
                    }
                }
            }
            if(folhas > 0 && this->grafite.empty()){
                cout << "Grafite acabou" << endl;
                cout << "Folhas escritas: " << aux << endl;
            }
        }
    }
};

int main(){
    LAPISEIRA lapiseira;
    
    string L;
    cin >> L;
    stringstream cc(L);
    string cmd;
    cc >> cmd;

        if(cmd == "iniciar"){
            float calibre;
            cc >> calibre;
            lapiseira.calibre = calibre;
        }else if(cmd == "mostrar"){
            cout << lapiseira;
        }else if(cmd == "inserir"){
            float calibre;
            string dureza;
            int tamanho;
            cc >> calibre >> dureza >> tamanho;

            GRAFITE grafite{calibre, dureza, tamanho};
            lapiseira.inserir_grafite(grafite);
        }else if(cmd == "deletar"){
            int i;
            cc >> i;
            lapiseira.remover_grafite(i);
        }else if(cmd == "folhas"){
            int folhas;
            cc >> folhas;
            lapiseira.escrever_folha(folhas);
        }else cout << "ERROR" << endl;

    return 0;
}
