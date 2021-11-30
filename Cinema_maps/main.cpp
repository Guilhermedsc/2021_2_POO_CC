#include <bits/stdc++.h>
using namespace std;

class CLIENT {
    string nome;
    int telefone;

public:
    CLIENT(string nome = "", int telefone = 0) : nome(nome), telefone(telefone) {}
    friend ostream& operator<<(ostream& os, const CLIENT& p) {
        os << p.nome << ":" << p.telefone;
        return os;
    }

    string getNome() { return nome; }
    int getTelefone() { return telefone; }
    void setNome(string nome) { this->nome = nome; }
    void setTelefone(int telefone) { this->telefone = telefone; }
};

class SALA {
    map<int, shared_ptr<CLIENT>> cadeiras;
    bool validar_index(int index) {
        if (index < 0 || index >= (int) this->cadeiras.size()) {
            cout << "Cadeira invalido" << endl;
            return false;
        }
        return true;
    }

public:
    SALA(int numero_cadeiras) {
        for (int i = 0; i < numero_cadeiras; i++) {
            this->cadeiras[i] = nullptr;
        }
    }

    void inserir(shared_ptr<CLIENT> pessoa, int index) {
        if (!validar_index(index))
            return;
        
        if (cadeiras[index] == nullptr) {
            for (auto &c : cadeiras) {
                if (c.second != nullptr && c.second->getNome() == pessoa->getNome()) {
                    cout << "Cliente ja esta no cinema" << endl;
                    return;
                }
            }
            cadeiras[index] = pessoa;     
        } else {
            cout << "Cadeira ja esta ocupada" << endl;
        }
    }
    
    shared_ptr<CLIENT> remover(string nome) {       
        for(auto &c : cadeiras) {
            if (c.second != nullptr && c.second->getNome() == nome) {
                shared_ptr<CLIENT> pessoa = c.second;
                c.second = nullptr;
                return pessoa;
            }
        }
        cout << "Cliente nao esta no cinema" << endl;
        return nullptr;
    }

    friend ostream& operator<<(ostream& os, const SALA& c) {
        os << "\n[ ";
        for (auto pessoa : c.cadeiras) {
            if (pessoa.second != nullptr) {
                os << *pessoa.second << " ";
            } else {
                os << "- ";
            }
        }
        os << "]";
        return os;
    }
};

int main() {
    SALA test(5);

    while (true){
        string cmd, nome;
        int telefone=0, index=0;
        cout << "\n$ ";
        cin >> cmd;

        if (cmd == "init"){
            int tsala=0;
            cin >> tsala;
            test = SALA(tsala);
            cout << test << endl;

        } else if(cmd == "add"){
            cin >> nome >> telefone >> index;
            test.inserir(make_shared<CLIENT>(nome, telefone), index);
            cout << test << endl;

        } else if (cmd == "remover"){
            cin >> nome;
            test.remover(nome);
            cout << test << endl;

        } else if (cmd == "sair"){
            break;

        } else {
            cout << "Comando invalido" << endl;
        }
    }   
}
