#include <string>
#include <iostream>
using namespace std;

extern "C"{
	#include "svr4_queue.h"
}

int main(int argc, char* argv[]){
	string cmd = "";
	int msqid = -1;
	int key;
	mq_message* msg = NULL;
	
	while(cmd != "exit"){
	
		cin >> cmd;
	
		if (cmd == "c"){
			cin >> key;
			msqid = create(static_cast<key_t>(key));
			if(msqid == -1) continue;
			cout << "Создана очередь с id: " << msqid << endl;
		}
		else if(cmd == "d"){
			if(delete_(msqid) == 0){
				cout << "Удалена очередь." << endl;
				msqid = -1;
			}
		}
		else if(cmd == "w"){
			cin >> key;
			getline(cin, cmd);
			cmd = string(cmd.begin() + 1, cmd.end());			
			
			if(write(msqid, key, cmd.c_str()) == 0){
				cout << "Отправлено сообщение: " << cmd << endl;
			}
		}
		else if(cmd == "r"){
			cin >> key;
			msg = read(msqid, key);
			
			if(msg){
				cout << "Принято сообщение от: " << msg->type << endl;
				cout << "Текст сообщения: " << msg->text << endl;
				
				delete msg;
			}
		}	
	}
	return 0;
}

