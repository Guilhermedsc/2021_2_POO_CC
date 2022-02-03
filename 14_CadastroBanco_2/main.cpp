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

    void transferir(CONTA &destino, float valor){
        if(this->saldo < valor){
            cout << "\nSaldo insuficiente" << endl;
            return;
        }else if(destino.id == this->id){
            cout << "\nMesma conta" << endl;
            return;
        }else if(valor <= 0){
            cout << "\nValor invalido" << endl;
            return;
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

    void imprimirC(){
        cout << id << ":" << clienteID << ":" << saldo << ":" << tipo << endl;
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

    void imprimirCli(){
        cout << "- " << nomeID << " ";
        for(int i=0; i<contas.size(); i++){
            cout << "[";
            cout << contas[i]->getId();
            cout << "] ";
        }
        cout << endl;
    }
};

class AGENCIA{
private:
    map<string, shared_ptr<CLIENTE>> clientes;
    map<int, shared_ptr<CONTA>> contas;
public:
    AGENCIA(){
    }

    void addCliente(string clienteID){    
        shared_ptr<CLIENTE> cliente = make_shared<CLIENTE>(clienteID);
        clientes.insert(pair<string, shared_ptr<CLIENTE>>(clienteID, cliente));

        int N = contas.size(), n1 = N+1, n2 = N+2;

        shared_ptr<CONTA> contaP = make_shared<POUPANCA>(0, clienteID, n1, "CP");
        cliente->addConta(contaP);
        contas.insert(pair<int, shared_ptr<CONTA>>(n1, contaP));

        shared_ptr<CONTA> contaC = make_shared<CORRENTE>(0, clienteID, n2, "CC");
        cliente->addConta(contaC);
        contas.insert(pair<int, shared_ptr<CONTA>>(n2, contaC));
    }

    void depositar(int contaID, float valor){
        auto it = contas.find(contaID);

        if(it != contas.end()){
            it->second->depositar(valor);
            return;
        }
        cout << "\nConta nao encontrada" << endl;
    }

    void sacar(int contaID, float valor){
        auto it = contas.find(contaID);

        if(it != contas.end()){
            it->second->sacar(valor);
            return;
        }
        cout << "\nConta nao encontrada" << endl;
    }

    void at_mensal_ag(){
        for(auto it = contas.begin(); it != contas.end(); it++){
            it->second->at_mensal();
        }
    }

    void transferir(int contaID1, int contaID2, float valor){
        auto it1 = contas.find(contaID1);
        auto it2 = contas.find(contaID2);

        if(it1 != contas.end() && it2 != contas.end()){
            it1->second->transferir(*it2->second, valor);
            return;
        }
        cout << "\nConta nao encontrada" << endl;
    }

    void imprime_contas_clientes(){
        cout << "\nClientes:" << endl;
        for(auto &cliente: clientes){
            cliente.second->imprimirCli();
        }

        cout << "\nContas:" << endl;
        for(auto &conta: contas){
            conta.second->imprimirC();
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
    ag.depositar(1, 150);
    ag.depositar(2, 100);
    ag.imprime_contas_clientes();

    //sacando
    ag.sacar(1, 50);
    ag.sacar(2, 50);
    ag.imprime_contas_clientes();

    //atualizando mensalmente
    ag.at_mensal_ag();
    ag.imprime_contas_clientes();

    //transferindo
    ag.transferir(1, 2, 50);
    ag.imprime_contas_clientes();
}
