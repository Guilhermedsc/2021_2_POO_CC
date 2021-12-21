#include <bits/stdc++.h>
using namespace std;

class CONTA{
protected:
    float saldo;
    string clienteID;
    int id;
    string tipo;

public:
    CONTA(float saldo, string clienteID, int id, string tipo){
        this->saldo = saldo;
        this->clienteID = clienteID;
        this->id = id;
        this->tipo = tipo;
    }

    void depositar(float valor){
        this->saldo += valor;
    }

    void sacar(float valor){
        if(valor > this->saldo){
            throw runtime_error("ERROR: Saldo insuficiente");
        }else{
            this->saldo -= valor;
        }
    }

    virtual void at_mensal() = 0;

    void transferir(CONTA &destino, float valor){
        if(this->saldo < valor){
            throw runtime_error("ERROR: Saldo insuficiente");
        }else if(destino.id == this->id){
            throw runtime_error("ERROR: Mesma conta");
        }else if(valor <= 0){
            throw runtime_error("ERROR: Valor invalido");
        }
        this->sacar(valor);
        destino.depositar(valor);
    }

    float getSaldo(){
        return this->saldo;
    }

    string getClienteID(){
        return this->clienteID;
    }

    int getId(){
        return id;
    }

    string getTipo(){
        return this->tipo;
    }

    virtual ~CONTA(){
    }
};

class POUPANCA : public CONTA{  
public:
    POUPANCA(float saldo, string clienteID, int id, string tipo):CONTA(saldo, clienteID, id, tipo){
    }

    void at_mensal() override {
        this->saldo = this->saldo + (saldo * 0.01);
    }
};

class CORRENTE : public CONTA{
public:
    CORRENTE(float saldo, string clienteID, int id, string tipo):CONTA(saldo, clienteID, id, tipo){
    }

    void at_mensal() override {
        if(this->saldo-5 < 0){
            this->saldo = 0;
            throw runtime_error("ERROR: Saldo zerado");
        }else{
            this->saldo = this->saldo - 5;
        }
    }
};

class CLIENTE{
private:
    vector<CONTA*> contas;
    string nomeID;

public:
    CLIENTE(string nomeID){
        this->nomeID = nomeID;
    }

    void addConta(CONTA* conta){
        contas.push_back(conta);
    }

    string getNomeID(){
        return nomeID;
    }

    vector<CONTA*> getContas(){
        return contas;
    }

    void setContas(vector<CONTA*> contas){
        this->contas = contas;
    }

    void setNomeID(string nomeID){
        this->nomeID = nomeID;
    }
};

class AGENCIA{
private:
    vector<CLIENTE*> clientes;
    vector<CONTA*> contas;

public:
    AGENCIA(){
    }

    void addCliente(string clienteID){
        CLIENTE* cliente = new CLIENTE(clienteID);
        clientes.push_back(cliente);

        int n1 = rand() % 50 + 1;
        int n2 = rand() % 50 + 1;

        //copilot god 
        for(auto &conta: contas){
            if(conta->getId() == n1){
                n1 = rand() % 50 + 1;
            }
            if(conta->getId() == n2){
                n2 = rand() % 50 + 1;
            }
        }

        //copilot god 
        CONTA* contaCP = new POUPANCA(0, clienteID, n1, "CP");
        CONTA* contaCC = new CORRENTE(0, clienteID, n2, "CC");
        cliente->addConta(contaCP);
        cliente->addConta(contaCC);
        contas.push_back(contaCP);
        contas.push_back(contaCC);
    }

    void depositar(int contaID, float valor){
        for(auto &conta: contas){
            if(conta->getId() == contaID){
                conta->depositar(valor);
                return;
            }
        }
        throw runtime_error("ERROR: Conta nao encontrada");
    }

    void sacar(int contaID, float valor){
        for(auto &conta: contas){
            if(conta->getId() == contaID){
                conta->sacar(valor);
                return;
            }
        }
        throw runtime_error("ERROR: Conta nao encontrada");
    }

    void at_mensal(){
        for(auto &conta: contas){
            conta->at_mensal();
        }
    }

    CONTA* getConta(int contaID){
        for(auto &conta: contas){
            if(conta->getId() == contaID){
                return conta;
            }
        }
        throw runtime_error("ERROR: Conta nao encontrada");
    }

    void tranferir(int contaID1, int contaID2, float valor){
        for(auto &conta: contas){
            if(conta->getId() == contaID1){
               for(auto &conta2: contas){
                    if(conta2->getId() == contaID2){
                        conta->transferir(*conta2, valor);
                        return;
                    }
               }
               throw runtime_error("ERROR: Conta nao encontrada");
            }
        }
        throw runtime_error("ERROR: Conta nao encontrada");
    }

    void imprime_contas_clientes(){
        cout << "\nClientes:" << endl;
        for(int i=0; i<clientes.size(); i++){
            cout << "- " << clientes[i]->getNomeID() << " ";
            for(int j=0; j<clientes[i]->getContas().size(); j++){
                cout << "[" << clientes[i]->getContas()[j]->getId() << "]" << " ";
            }
            cout << endl;
        }

        cout << "\nContas:" << endl;
        for(int i=0; i<contas.size(); i++){
            cout << contas[i]->getId() << ":" << contas[i]->getClienteID() << ":" << contas[i]->getSaldo() << ":" << contas[i]->getTipo() << endl;
        }
    }
};

int main(){
    AGENCIA ag;

    while(true){
        cout << "$ ";
        string cmd="";
        cin >> cmd;

        try{
            if(cmd == "add"){
                string clienteID;
                cin >> clienteID;
                ag.addCliente(clienteID);

            }else if(cmd == "print"){
                ag.imprime_contas_clientes();

            }else if(cmd == "transferir"){
                int contaID1, contaID2;
                float valor;
                cin >> contaID1 >> contaID2 >> valor;
                ag.tranferir(contaID1, contaID2, valor);

            }else if(cmd == "atualizar"){
                ag.at_mensal();

            }else if(cmd == "sacar"){
                int contaID;
                float valor;
                cin >> contaID >> valor;
                ag.sacar(contaID, valor);

            }else if(cmd == "depositar"){
                int contaID;
                float valor;
                cin >> contaID >> valor;
                ag.depositar(contaID, valor);

            }else if(cmd == "atualizar"){
                ag.at_mensal();

            }else if(cmd == "sair"){
                break;

            }else{
                throw runtime_error("ERROR: Comando invalido");
            }
        } catch(runtime_error &e){
            cout << e.what() << endl;
        }
    }

    return 0;
}