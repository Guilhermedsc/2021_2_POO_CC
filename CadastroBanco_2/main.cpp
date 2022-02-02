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
        if(valor > saldo){
            cout << "\nSaldo insuficiente" << endl;
            return;
        }else{
            this->saldo -= valor;
        }
    }

    virtual void at_mensal() = 0;

    void transferir(){
        
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
    POUPANCA(float saldo, string clienteID, int id, string tipo) : CONTA(saldo, clienteID, id, tipo){
    }

    void at_mensal() override {
        this->saldo = this->saldo + (saldo * 0.01);
    }
};

class CORRENTE : public CONTA{
public:
    CORRENTE(float saldo, string clienteID, int id, string tipo) : CONTA(saldo, clienteID, id, tipo){
    }

    void at_mensal() override {
        if(this->saldo-20 < 0){
            this->saldo = 0;
            cout << "\nSaldo zerado" << endl;
        }else{
            this->saldo = this->saldo - 20;
        }
    }
};

class CLIENTE{
    vector<shared_ptr<CONTA>> contas;
    string nomeID;
public:
    CLIENTE(string nomeID){
        this->nomeID = nomeID;
    }

    void addConta(shared_ptr<CONTA> conta){
        contas.push_back(conta);
    }

    string getNomeID(){
        return nomeID;
    }

    vector<shared_ptr<CONTA>> getContas(){
        return contas;
    }

    void setContas(vector<shared_ptr<CONTA>> contas){
        this->contas = contas;
    }

    void setNomeID(string nomeID){
        this->nomeID = nomeID;
    }
};

class AGENCIA{
private:
    vector<shared_ptr<CLIENTE>> clientes;
    vector<shared_ptr<CONTA>> contas;
public:
    AGENCIA(){
    }

    void addCliente(string clienteID){
        shared_ptr<CLIENTE> cliente = make_shared<CLIENTE>(clienteID);
        clientes.push_back(cliente);

        int N = contas.size(), n1 = N+1, n2 = N+2;

        shared_ptr<CONTA> contaP = make_shared<POUPANCA>(0, clienteID, n1, "POUPANCA");
            cliente->addConta(contaP);
            contas.push_back(contaP);

        shared_ptr<CONTA> contaC = make_shared<CORRENTE>(0, clienteID, n2, "CORRENTE");
            cliente->addConta(contaC);
            contas.push_back(contaC);
    }

    void depositar(int contaID, float valor){
        for(auto &conta: contas){
            if(conta->getId() == contaID){
                conta->depositar(valor);
                return;
            }
        }
        cout << "\nConta nao encontrada" << endl;
    }

    void sacar(int contaID, float valor){
        for(auto &conta: contas){
            if(conta->getId() == contaID){
                conta->sacar(valor);
                return;
            }
        }
        cout << "\nConta nao encontrada" << endl;
    }

    void at_mensal_ag(){
        for(auto &conta: contas){
            conta->at_mensal();
        }
    }

    void tranferir(){
        
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

    //adicionando clientes
    ag.addCliente("Joao");
    ag.addCliente("Maria");
    ag.imprime_contas_clientes();

    //depositando
    ag.depositar(1, 100);
    ag.imprime_contas_clientes();

    //sacando
    ag.sacar(2, 50);
    ag.imprime_contas_clientes();

    //atualizando mensalmente
    ag.at_mensal_ag();
    ag.imprime_contas_clientes();
}