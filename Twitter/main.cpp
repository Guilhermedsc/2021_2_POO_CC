#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <sstream>
//#include "auxiliar.hpp"

using namespace std;

class MessageException : public exception {
    string message;
public:
    MessageException(const string& message) : 
        message(message) {
    }
    const char* what() const noexcept override {
        return message.c_str(); 
    }
};

class Message {
    int id;
    string username;
    string msg;
    set<string> likes;
public:
    Message(int id, const string& username, const string& msg) : id(id), username(username), msg(msg) {
    }

    int getId() const { 
        return id; 
    }

    void like(const string& username) {
        likes.insert(username);
    }

    friend ostream& operator<<(ostream& os, const Message& msg){
        os << msg.id << ":" << msg.username << " (" << msg.msg << ")";
        if(!msg.likes.empty()) {
            os << " [ ";
            for(const auto& like : msg.likes) {
                os << like << " ";
            }
            os << "]";
        }
        return os;
    }
};

class Inbox {
    map<int, Message*> unread;
    map<int, Message*> allMsgs;
public:
    Inbox() {
    }

    void storeUnread(Message* tweet){
        unread.insert(pair<int, Message*>(tweet->getId(), tweet));
    }

    void storeReaded(Message* tweet){
        allMsgs.insert(pair<int, Message*>(tweet->getId(), tweet));
    }

    vector<Message*> getUnread(){
        vector<Message*> unreadMsgs;
        for(auto& msg : unread) {
            unreadMsgs.push_back(msg.second);
            allMsgs.insert(pair<int, Message*>(msg.first, msg.second));
        }
        unread.clear();
        return unreadMsgs;        
    }

    vector<Message*> getAll(){
        vector<Message*> allMsgsVec;
        for(auto& msg : allMsgs) {
            allMsgsVec.push_back(msg.second);
        }
        return allMsgsVec;
    }

    Message* getTweet(int id){
        auto it = allMsgs.find(id);
        if(it == allMsgs.end()) {
            throw MessageException("Mensagem nao encontrada");
        }
        return it->second;
    }

    void imprimirIbox(){ //mudar para ostream
        for(auto& msg : this->getUnread()) {
            cout << *msg << endl;
        }
        if(this->getUnread().empty()) {
            for(auto& msg : this->getAll()) {
                cout << *msg << endl;
            }
        }
        cout << endl;
    }
};

class User {
    string username;
    Inbox inbox;
    map<string, User*> followers;
    map<string, User*> following;
public:
    User(const string& username) : username(username) {
    }

    void follow(User * other){
        if(following.find(other->username) != following.end()) {
            throw MessageException("Ja segue este usuario"); 
        }
        following.insert(pair<string, User*>(other->username, other));
        other->followers.insert(pair<string, User*>(username, this));
    }

    void unfollow(string username){
        auto it = following.find(username);
        if(it == following.end()) {
            throw MessageException("Nao segue este usuario");
        }
        auto it2 = it->second->followers.find(this->username);
        it->second->followers.erase(it2);
        following.erase(it);
    }

    void like(int twId){
        Message* msgT = inbox.getTweet(twId);
        if(msgT == nullptr) {
            throw MessageException("Mensagem nao encontrada");
        }
        msgT->like(username);
    }

    Inbox& getInbox(){
        return inbox;
    }

    void sendTweet(Message * msg){
        inbox.storeUnread(msg);
        for(auto& follower : followers) {
            follower.second->getInbox().storeUnread(msg);
        }
    }

    void imprimirUser(){ //mudar para ostream
        cout << username << endl;
        cout << " seguidores: [ ";
        for(auto& follower : followers) {
            cout << follower.first << " ";
        }
        cout << "]" << endl;

        cout << " seguindo: [ ";
        for(auto& following : following) {
            cout << following.first << " ";
        }
        cout << "]" << endl;
    }
};

class Controller {
    map<string, shared_ptr<User>> users;
    map<int, shared_ptr<Message>> tweets;
    int nextTweetId { 0 };
    Message* createMsg(string username, string msg){
        Message* msgT = new Message(nextTweetId, username, msg);
        tweets.insert(pair<int, shared_ptr<Message>>(nextTweetId, shared_ptr<Message>(msgT)));
        nextTweetId++;
        return msgT;
    }
public:
    Controller() {
    }

    void addUser(string username){
        if(users.find(username) != users.end()) {
            throw MessageException("Usuario ja existe");
        }
        users.insert(pair<string, shared_ptr<User>>(username, shared_ptr<User>(new User(username))));
    }

    User* getUser(string username){
        auto it = users.find(username);
        if(it == users.end()) {
            throw MessageException("Usuario nao existe");
        }
        return it->second.get();
    }

    void sendTweet(string username, string msg){
        User* user = getUser(username);
        Message* msgT = createMsg(username, msg);
        user->sendTweet(msgT);
    }

    void imprimirConller(){ //mudar para ostream
        for(auto& user : users) {
            user.second->imprimirUser();
        }
        cout << endl;
    }
};

int main(){
    Controller sistema;

    while(true){
        cout << endl;
        cout << "$ ";
        string cmd="";        
        cin >> cmd;

        try{
            if(cmd == "end"){
                break;

            }else if (cmd == "add") {
                string username;
                cin >> username;
                sistema.addUser(username);
            
            }else if (cmd == "show") {
                sistema.imprimirConller();
            
            }else if (cmd == "follow") {
                string username1, username2;
                cin >> username1 >> username2;
                sistema.getUser(username1)->follow(sistema.getUser(username2));
            
            }else if (cmd == "unfollow") {
                string username1, username2;
                cin >> username1 >> username2;
                sistema.getUser(username1)->unfollow(username2);
            
            }else if (cmd == "twittar") {
                string username, msg;
                cin >> username >> msg;
                sistema.sendTweet(username, msg);
            
            } else if (cmd == "timeline") {
                string username;
                cin >> username;
                sistema.getUser(username)->getInbox().imprimirIbox();
            
            }else if (cmd == "like") {
                string username;
                int twId;
                cin >> username >> twId;
                sistema.getUser(username)->like(twId);            
            
            }else if (cmd == "unread") {
                string username;
                cin >> username;
                sistema.getUser(username)->getInbox().getUnread().clear();
            
            } else {
                std::cout << "fail: comando invalido" << '\n';
            }

        } catch (MessageException &e) {
            std::cout << e.what() << '\n';
        }
    }

    return 0;
}