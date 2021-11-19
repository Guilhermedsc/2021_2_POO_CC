#include <bits/stdc++.h>
using namespace std;

class FONE{
    string operadora;
    string numero;

public:
    FONE(string operadora="", string numero="") : operadora(operadora), numero(numero) {}
    friend ostream& operator<<(ostream& os, const FONE& p) {
        os << p.operadora << ":" << p.numero;
        return os;
    }

    string getOperadora() { return operadora; }
    string getNumero() { return numero; }

    void setOperadora(string operadora) { this->operadora = operadora; }
    void setNumero(string numero) { this->numero = numero; }
};

class CONTATO{
    vector<FONE> fones;
    string nome;

    //bool
    int validarNumero(string number){
        int temLetra;
        for(int i=0; i<number.size(); i++){
            if(number[i] >= 48 && number[i] <= 57){
                temLetra=0;
            }else{
                temLetra=1;
                break;
            }
        }
        return temLetra;
    }

public:
    CONTATO(string nome) : nome(nome) {}
    
    void addFone(string operadora, string numero){
        int flag = validarNumero(numero);

        if(flag == 0){
            fones.push_back(FONE(operadora, numero));
        }else{
            cout << "Numero invalido" << endl;
        }
    }

    void remover(int indice){
        for(int i=0; i<fones.size(); i++){
            if(i == indice){
                fones.erase(fones.begin() + i);
            }
        }
    }

    void imprimir(){
        cout << nome << "  ";
        for(int i=0; i<fones.size(); i++){
            cout << "[ ";
            cout << i << ":";
            cout << fones[i] << " ";
            cout << "]";
        }
        cout << endl;
    }
};

int main(){
    CONTATO pessoa("ze");
    
    while(true){
        string cmd, nome, operadora, numero;
        int indice=0;
        cout << "\n$ ";
        cin >> cmd;

        if(cmd == "init"){
            cin >> nome;
            pessoa = CONTATO(nome);

        }else if(cmd == "add"){
            cin >> operadora >> numero;
            pessoa.addFone(operadora, numero);

        }else if(cmd == "print"){
            pessoa.imprimir();

        }else if(cmd == "delete"){
            cin >> indice;
            pessoa.remover(indice);

        }else { cout << "Comando invalido" << endl; }        
    }
    
}