#include <bits/stdc++.h>
using namespace std;

class MEDICO;

class PACIENTE{
    string nome;
    string diagnostico;
    map<string, MEDICO*> medicos;
public:
    PACIENTE(string nome, string diagnostico) : nome(nome), diagnostico(diagnostico){
    }

    void addMedico(MEDICO* medico);

    void rmMedico(string nome);

    string getNome(){
        return this->nome;
    }

    string getDiagnostico(){
        return this->diagnostico;
    }

    string getMedicos(){
        string medicos;
        for(auto it = this->medicos.begin(); it != this->medicos.end(); it++){
            medicos += it->first + " ";
        }
        return medicos;
    }

    void IMPRIMIRpaciente(){
        cout << "Pac: ";
        cout << nome << ":" << diagnostico;
        cout << " Meds: [";
        for(auto it = medicos.begin(); it != medicos.end(); it++){
            cout << it->first << ", ";
        }
        cout << "]" << endl;
    }

};

class MEDICO{
    string nome;
    string especialidade;
    map<string, PACIENTE*> pacientes;
public:
    MEDICO(string nome, string especialidade) : nome(nome), especialidade(especialidade){
    }

    void addPaciente(PACIENTE* paciente);

    void rmPaciente(string nome);

    string getNome(){
        return this->nome;
    }

    string getEspecialidade(){
        return this->especialidade;
    }

    string getPacientes(){
        string pacientes;
        for(auto it = this->pacientes.begin(); it != this->pacientes.end(); it++){
            pacientes += it->first + " ";
        }
        return pacientes;
    }

    void IMPRIMIRmedico(){
        cout << "Meds: ";
        cout << nome << ":" << especialidade;
        cout << " Pac: [";
        for(auto it = pacientes.begin(); it != pacientes.end(); it++){
            cout << it->first << ", ";
        }
        cout << "]" << endl;
    }
};

void PACIENTE::addMedico(MEDICO* medico){
    this->medicos[medico->getNome()] = medico;
}

void MEDICO::addPaciente(PACIENTE* paciente){
    this->pacientes[paciente->getNome()] = paciente;
}

void PACIENTE::rmMedico(string nome){
    this->medicos.erase(nome);
}

void MEDICO::rmPaciente(string nome){
    this->pacientes.erase(nome);
}

class SISTEMA{
    map<string, PACIENTE*> pacientes;
    map<string, MEDICO*> medicos;
public:
    SISTEMA(){
    }

    void addPaciente(PACIENTE* paciente){
        this->pacientes[paciente->getNome()] = paciente;
    }

    void addMedico(MEDICO* medico){
        this->medicos[medico->getNome()] = medico;
    }

    void rmMedico(string nome){
        this->medicos.erase(nome);
    }

    void rmPaciente(string nome){
        this->pacientes.erase(nome);
    }

    void vincular(string nomeP, string nomeM){
        this->pacientes[nomeP]->addMedico(this->medicos[nomeM]);
        this->medicos[nomeM]->addPaciente(this->pacientes[nomeP]);
    }

    void IMPRIMIR(){
        for(auto it = pacientes.begin(); it != pacientes.end(); it++){
            it->second->IMPRIMIRpaciente();
        }
        for(auto it = medicos.begin(); it != medicos.end(); it++){
            it->second->IMPRIMIRmedico();
        }
    }
};


int main(){
    SISTEMA sistema;

    sistema.addPaciente(new PACIENTE("Joao", "Cancer"));
    sistema.addPaciente(new PACIENTE("Maria", "pernaruim"));
    sistema.addMedico(new MEDICO("ze", "c"));
    sistema.addMedico(new MEDICO("zeze", "osso"));
    sistema.IMPRIMIR();

    cout << endl;

    sistema.rmMedico("ze");
    sistema.rmPaciente("Maria");
    sistema.IMPRIMIR();

    cout << endl;

    sistema.vincular("Joao", "zeze");
    sistema.IMPRIMIR();
}