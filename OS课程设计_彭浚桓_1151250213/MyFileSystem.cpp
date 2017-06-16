// MyFileSystem.cpp : �������̨Ӧ�ó������ڵ㡣
//


#include "MyFileSystem.h"//��������ṹ
#include <iostream>

void usage();
Cmd* Cmd::instance = nullptr;

int main(int args, char* argv[]){

	Disc disc;


	cout << "���� help ��ȡ����" << ",���� Exit �˳�" << endl;
	string input_cmd;
	Cmd* cmd = Cmd::getInstance();
	while (true){
		cout << ">>";
		getline(cin, input_cmd);
		if (input_cmd._Equal("Exit") || input_cmd._Equal("exit"))
			break;
		if (input_cmd._Equal("help")){
			usage();
			continue;
		}

		auto flag = cmd->parse(input_cmd);
		if (!flag){
			cout << "Error" << endl;
		}
	}
	return 0;
}

bool Cmd::parse(string cmd){
	string* strings = split(cmd);
	if (strings[0]._Equal("Format")){
		Format();
	} else if (strings[0]._Equal("MKfile")){
		MkFile(strings[1]);
	} else if (strings[0]._Equal("MKdir")){
		MkDir(strings[1]);
	} else if (strings[0]._Equal("Cd")){
		Cd(strings[1]);
	} else if (strings[0]._Equal("Delfile")){
		DelFile(strings[1]);
	} else if (strings[0]._Equal("Dir")){
		Dir();
	} else if (strings[0]._Equal("Copy")){
		Copy(strings[1],strings[2]);
	} else if (strings[0]._Equal("Open")){
		Open(strings[1]);
	} else if (strings[0]._Equal("Attrib")){
		Attrib(strings[1],strings[2]);
	} else if (strings[0]._Equal("Viewinodemap")){
		ViewINodeMap();
	} else if (strings[0]._Equal("Viewblockmap")){
		ViewBlockMap();
	} else{
		cout << strings[0] << " �Ҳ����������������" << endl;
	}
	return true;
}

bool Cmd::Format(){
	cout << "���ڳ�ʼ��Ӳ�̡�����ȴ�" << endl;
	
	return true;
}

bool Cmd::MkFile(string cmd){
	return true;
}

bool Cmd::MkDir(string cmd){
	return true;
}

bool Cmd::Cd(string cmd){
	return true;
}

bool Cmd::DelFile(string cmd){
	return true;
}

bool Cmd::DelDir(string cmd){
	return true;
}

bool Cmd::Dir(){
	return true;
}

bool Cmd::Copy(string orign_path, string goal_path){
	return true;
}

bool Cmd::Open(string cmd){
	return true;
}

bool Cmd::Attrib(string file_path, string operation){
	return true;
}

bool Cmd::ViewINodeMap(){
	return true;
}

bool Cmd::ViewBlockMap(){
	return true;
}


void usage(){
	cout << "Format\t\t\t��ʼ�����̣������ṹ" << endl <<
		"Mkfile\t\t\t�����ļ�" << endl <<
		"Mkdir\t\t\t����Ŀ¼" << endl <<
		"Cd\t\t\t�ı䵱ǰĿ¼" << endl <<
		"Delfile [file path]\tɾ���ļ���ע��ֻ�����ԣ�" << endl <<
		"Deldir [dir path]\tɾ��Ŀ¼��ע��ֻ�����ԣ�" << endl <<
		"Dir\t\t\t���ļ�Ŀ¼ ���г����ֺͽ���ʱ�䣬ע���������ԣ�" << endl <<
		"Copy [origin file path] [goal file path]\t\t\t�����ļ���ĳһ·��" << endl <<
		"Open [file path]\t�򿪲��༭�ļ���ע��ֻ�����ԣ�" << endl <<
		"Attrib [+r|-r] [+h|-h]  [file path]\t\t�����ļ����ԣ���ֻ������ֻ���������أ�������" << endl <<
		"Viewinodemap\t\t��ʾ��ǰinodeλʾͼ״��" << endl <<
		"Viewblockmap\t\t��ʾ��ǰblockλʾͼ״��" << endl;
}
