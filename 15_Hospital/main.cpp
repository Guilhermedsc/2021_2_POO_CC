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

    void addMedico(MEDICO *medico);

    void rmMedico(string nome);

    string getNome(){
        return this->nome;
    }

    string getDiagnostico(){
        return this->diagnostico;
    }

    map<string, MEDICO*> getMedicos(){
        return this->medicos;
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

    void addPaciente(PACIENTE *paciente){
        auto key = paciente->getNome();

        if(pacientes.find(key) != pacientes.end()){
            return;
        }
        this->pacientes[key] = paciente;
        paciente->addMedico(this);
    }

    void rmPaciente(string nome){
        auto it = pacientes.find(nome);

        if(it == pacientes.end()){
            cout << "Paciente nao encontrado" << endl;
            return;
        }
        PACIENTE *paciente = it->second;
        this->pacientes.erase(it);
        paciente->rmMedico(this->nome);
    }

    string getNome(){
        return this->nome;
    }

    string getEspecialidade(){
        return this->especialidade;
    }

    map<string, PACIENTE*> getPacientes(){
        return this->pacientes;
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

void PACIENTE::addMedico(MEDICO *medico){
    auto key = medico->getNome();

    if(medicos.find(key) != medicos.end()){
        return;
    }

    for(auto it = medicos.begin(); it != medicos.end(); it++){
        if(it->second->getEspecialidade() == medico->getEspecialidade()){
            cout << "Medico com essa especialidade ja existe\n" << endl;
            return;
        }
    }
    this->medicos[key] = medico;
    medico->addPaciente(this);
}

void PACIENTE::rmMedico(string nome){
    auto it = medicos.find(nome);

    if(it == medicos.end()){
        cout << "Medico nao encontrado" << endl;
        return;
    }
    MEDICO *medico = it->second;
    this->medicos.erase(it);
    medico->rmPaciente(this->nome);
}

class SISTEMA{
    map<string, PACIENTE*> pacientes;
    map<string, MEDICO*> medicos;
public:
    SISTEMA(){
    }

    void addPaciente(PACIENTE *paciente){
        auto key = paciente->getNome();

        if(pacientes.find(key) != pacientes.end()){
            cout << "Paciente ja cadastrado no sistema" << endl;
            return;
        }
        this->pacientes[key] = paciente;
    }

    void addMedico(MEDICO *medico){
        auto key = medico->getNome();

        if(medicos.find(key) != medicos.end()){
            cout << "Medico ja cadastrado no sistema" << endl;
            return;
        }
        this->medicos[key] = medico;
    }

    void rmMedico(string nome){
        auto it = medicos.find(nome);

        if(it == medicos.end()){
            cout << "Medico nao encontrado no sistema" << endl;
            return;
        }
        this->medicos.erase(it);        
    }

    void rmPaciente(string nome){
        auto it = pacientes.find(nome);

        if(it == pacientes.end()){
            cout << "Paciente nao encontrado no sistema" << endl;
            return;
        }
        this->pacientes.erase(it);
    }

    void vincular(string nomeP, string nomeM){
        auto itP = pacientes.find(nomeP);
        auto itM = medicos.find(nomeM);

        if(itP != pacientes.end() && itM != medicos.end()){
            itP->second->addMedico(itM->second);    // &(*itM->second) -> pega o endereco do medico
            return;
        }
        cout << "Paciente ou medico nao encontrado" << endl;
    }

    void desvincular(string nomeP, string nomeM){
        auto itP = pacientes.find(nomeP);
        auto itM = medicos.find(nomeM);

        if(itP != pacientes.end() && itM != medicos.end()){
            itP->second->rmMedico(itM->second->getNome());
            return;
        }
        cout << "Paciente ou medico nao encontrado" << endl;
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

    sistema.addPaciente(new PACIENTE("ze", "1"));
    sistema.addPaciente(new PACIENTE("luis", "2"));

    sistema.addMedico(new MEDICO("DrFelipe", "1"));
    sistema.addMedico(new MEDICO("DrJunior", "2"));
    //sistema.addMedico(new MEDICO("Dr", "1"));

    sistema.IMPRIMIR();
    cout << endl;

    sistema.vincular("ze", "DrFelipe");
    sistema.vincular("luis", "DrJunior");
    //sistema.vincular("ze", "Dr");

    sistema.IMPRIMIR();
    cout << endl;

    sistema.desvincular("ze", "DrFelipe");

    sistema.IMPRIMIR();
}