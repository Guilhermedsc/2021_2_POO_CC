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
            if((number[i] >= 48 && number[i] <= 57) || number[i] == '.' || number[i] == '-' || number[i] == '(' || number[i] == ')'){
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
                fones.erase(fones.begin()+i);
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
    }

    vector<FONE> getFones() { return fones; }
    string getNome() { return nome; }
    string setNome(string nome) { this->nome = nome; }
};

class AGENDA{
    map<string, CONTATO> contatos;

public:
    AGENDA() {}

    void addContato(CONTATO contato){
        for(auto it = contatos.begin(); it != contatos.end(); it++){
            if(it->first == contato.getNome()){
                for(int i=0; i<contato.getFones().size(); i++){
                    it->second.addFone(contato.getFones()[i].getOperadora(), contato.getFones()[i].getNumero());
                }
                return;
            }
        }
        contatos.insert(pair<string, CONTATO>(contato.getNome(), contato));        
    }

    void removerContato(string nome, int indice){
        if(indice == -1){
            for(auto it = contatos.begin(); it != contatos.end(); it++){
                if(it->first == nome){
                    contatos.erase(it);
                    return;
                }
            }
        }else{
            for(auto it = contatos.begin(); it != contatos.end(); it++){
                if(it->first == nome){
                    it->second.remover(indice);
                    return;
                }
            }
        }
    }

    void busca(string padrao){
        vector<CONTATO> aux;
        for(auto it = contatos.begin(); it != contatos.end(); it++){
            for(int i=0; i<it->second.getFones().size(); i++){
                if(it->second.getFones()[i].getNumero().find(padrao) != string::npos || it->second.getFones()[i].getOperadora().find(padrao) != string::npos){
                    aux.push_back(it->second);
                    break;

                }else if(it->first.find(padrao) != string::npos){
                    aux.push_back(it->second);
                    break;
                }                
            }
        }

        for(int i=0; i<aux.size(); i++){
            cout << "- ";
            aux[i].imprimir();
            cout << endl;
        }
        aux.clear();     
    }

    void imprimirAgenda(){
        for(auto it = contatos.begin(); it != contatos.end(); it++){
            it->second.imprimir();
            cout << endl;
        }
    }    
};

void ajuda(){
    cout << "\nComandos:" << endl;
    cout << "   add <nome> <operadora> <numero>, informe a quantidade de numeros a ser adcionados antes" << endl;
    cout << "   delete <nome> <indiceFone>, coloque indice como -1 para apagar o contato inteiro" << endl;
    cout << "   busca <padrao>" << endl;
    cout << "   print -> para mostra os contatos" << endl;
    cout << "   exit -> para sair" << endl;
}

int main(){
    AGENDA agenda;

    CONTATO pessoa("guilherme");
    pessoa.addFone("tim", "988");
    pessoa.addFone("tim", "455");   
    agenda.addContato(pessoa);

    pessoa = CONTATO("ana");
    pessoa.addFone("oi", "111");
    pessoa.addFone("claro", "988");
    agenda.addContato(pessoa);
    
    cout << "Digite ajuda para mostra os comandos";
    while (true){
        string cmd, nome, operadora, numero, padrao;
        int indice=0, n=0;
        cout << "\n$ ";
        cin >> cmd;

        if(cmd == "add"){
            cin >> n;
            for(int i=0; i<n; i++){
                cin >> nome;
                cin >> operadora >> numero;
                pessoa = CONTATO(nome);
                pessoa.addFone(operadora, numero);
                agenda.addContato(pessoa);
            }

        } else if(cmd == "print"){
            agenda.imprimirAgenda();

        } else if(cmd == "exit"){
            break;

        } else if(cmd == "delete"){
            cin >> nome >> indice;
            agenda.removerContato(nome, indice);

        } else if(cmd == "busca"){
            cin >> padrao;
            agenda.busca(padrao);

        } else if(cmd == "ajuda"){
            ajuda();

        } else {
            cout << "Comando invalido" << endl;

        }
    }
    return 0;   
}