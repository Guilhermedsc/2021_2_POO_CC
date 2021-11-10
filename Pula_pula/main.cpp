#include <bits/stdc++.h>
using namespace std;

class KID{
public:
    int idade;
    string nome;

    KID(int idade = 0, string nome = "") : idade(idade), nome(nome) {}
    friend ostream& operator<<(ostream& os, const KID& p) {
        os << p.nome << ":" << p.idade;
        return os;
    }
};

class PULAp{
    list <shared_ptr<KID>> fila;
    list <shared_ptr<KID>> pulap;

public:
    PULAp(int lugares) : fila(lugares, nullptr  ) {}

    void inserir(std::shared_ptr<KID> pessoa) {      
        fila.push_back(pessoa);
    }

    void mover_pulapula(int flag) {
        if(flag == 1){
            pulap.push_front(fila.back());
            fila.pop_back();
        }
    }

    void saindo_pulapula(int flag) {
        if(flag == 1){
            fila.push_front(pulap.back());
            pulap.pop_back();
        }
    }

    shared_ptr<KID> remover(string nome, int lista) {
        if(lista == 1){
            for(auto it = fila.begin(); it != fila.end(); it++){
                if((*it)->nome == nome){
                    shared_ptr<KID> pessoa = *it;
                    fila.erase(it);
                    return pessoa;
                }
            }
        }else{
            for(auto it = pulap.begin(); it != pulap.end(); it++){
                if((*it)->nome == nome){
                    shared_ptr<KID> pessoa = *it;
                    pulap.erase(it);
                    return pessoa;
                }
            }
        }
    }

    friend ostream& operator<<(ostream& os, const PULAp& p) {
        os << "\n| ";
        for (auto pessoa : p.fila){ 
            if (pessoa != nullptr) {
                os << *pessoa << " ";
            }
        }
        os << "|";
        os << " => ";

        os << "[ ";
        for (auto pessoa : p.pulap){ 
            if (pessoa != nullptr) {
                os << *pessoa << " ";
            }
        }
        os << "]";

        return os;
    }
};

int main(){
    PULAp fila(3);
    
    fila.inserir(make_shared<KID>(10, "Joao"));
    fila.inserir(make_shared<KID>(20, "Maria"));
    fila.inserir(make_shared<KID>(30, "Pedro"));
    cout << fila << endl;

    fila.mover_pulapula(1);    
    cout << fila << endl;

    fila.mover_pulapula(1);
    cout << fila << endl;

    fila.saindo_pulapula(1);
    cout << fila << endl;

    fila.remover("Pedro", 1);
    cout << fila << endl;
    
    fila.remover("Maria", 2);
    cout << fila << endl;


    return 0;
}