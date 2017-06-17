// MyFileSystem.cpp : �������̨Ӧ�ó������ڵ㡣
//


#include "MyFileSystem.h"//��������ṹ
#include <iostream>

void usage();
Cmd* Cmd::instance = nullptr;

int main(int args, char* argv[])
{
	Disc* disc = nullptr;


	cout << "���� help ��ȡ����" << ",���� Exit �˳�" << endl;
	string input_cmd;
	Cmd* cmd = Cmd::getInstance(disc);
	while (true)
	{
		cout << cmd->getCwd() << "  >>";
		getline(cin, input_cmd);
		if (input_cmd._Equal("Exit") || input_cmd._Equal("exit"))
			break;
		if (input_cmd._Equal("help"))
		{
			usage();
			continue;
		}

		auto flag = cmd->parse(input_cmd);
		if (!flag)
		{
			cout << "Error" << endl;
		}
	}
	return 0;
}

bool Cmd::parse(string cmd)
{
	string* strings = split(cmd);

	if (strings[0]._Equal("Format"))
	{
		Format();
	}
	else if (disc == nullptr)
	{
		cout << "Ӳ��δ��ʼ�������������� help �鿴�����" << endl;
		return false;
	}
	else if (strings[0]._Equal("MKfile"))
	{
		MkFile(strings[1]);
	}
	else if (strings[0]._Equal("MKdir"))
	{
		MkDir(strings[1]);
	}
	else if (strings[0]._Equal("Cd"))
	{
		Cd(strings[1]);
	}
	else if (strings[0]._Equal("Delfile"))
	{
		DelFile(strings[1]);
	}
	else if (strings[0]._Equal("Dir"))
	{
		Dir();
	}
	else if (strings[0]._Equal("Copy"))
	{
		Copy(strings[1], strings[2]);
	}
	else if (strings[0]._Equal("Open"))
	{
		Open(strings[1]);
	}
	else if (strings[0]._Equal("Attrib"))
	{
		Attrib(strings[1], strings[2]);
	}
	else if (strings[0]._Equal("Viewinodemap"))
	{
		ViewINodeMap();
	}
	else if (strings[0]._Equal("Viewblockmap"))
	{
		ViewBlockMap();
	}
	else
	{
		cout << strings[0] << " �Ҳ����������������" << endl;
	}
	return true;
}

bool Cmd::Format()
{
	cout << "���ڳ�ʼ��Ӳ�̡�����ȴ�" << endl;
	disc = new Disc;
	if (disc->dataBlock != nullptr)
	{
		cout << "��ʼ���ɹ�����" << endl;
		cwd = "Root/";
		return true;
	}
	return false;
}

bool Cmd::MkFile(string filepath)
{
	return true;
}

bool Cmd::MkDir(string dir)
{
	int i_node_num;
	if (cwd_inode != -1)
	{//�Ǹ�Ŀ¼
		I_NODE parentINode = disc->i_node_s[cwd_inode];
		if (parentINode.isFull())
		{
			cout << "��Ŀ¼������������������κ�Ŀ¼�����ļ�" << endl;
			return false;
		}


		if (disc->i_nodeBitMap.getAnINodeNum(i_node_num))
		{//�ҵ���i-node
			disc->i_nodeBitMap.i_node_bitmap[i_node_num] = true;//���Ķ�Ӧi-node��״̬
			disc->i_node_s[i_node_num].init();//��ʼ��i-node������Ҫ�Ƕ�ʱ��ĸ���
			parentINode.addChild(i_node_num);//��ɸ��ڵ㵽�ӽڵ������
		}
		else
		{
			cout << "�ռ䲻�㣬�޷�����Ŀ¼��";
			return false;
		}
	}
	else//���ڵ�
	{
		int j;
		if (disc->rootDirectory.getAnVoidDirecoryEntry(j))//��ȡ���ø�Ŀ¼
		{
			if (disc->i_nodeBitMap.getAnINodeNum(i_node_num))
			{
				disc->i_nodeBitMap.i_node_bitmap[i_node_num] = true;
				disc->i_node_s[i_node_num].init();
			}

			disc->rootDirectory.direcoryEntries[j].init(dir._Myptr(), 1, i_node_num);
		}
		else
		{
			cout << "��Ŀ¼�������������������Ŀ¼" << endl;
		}
	}


	return true;
}

bool Cmd::Cd(string cmd)
{
	return true;
}

bool Cmd::DelFile(string cmd)
{
	return true;
}

bool Cmd::DelDir(string cmd)
{
	return true;
}

bool Cmd::Dir()
{
	return true;
}

bool Cmd::Copy(string orign_path, string goal_path)
{
	return true;
}

bool Cmd::Open(string cmd)
{
	return true;
}

bool Cmd::Attrib(string file_path, string operation)
{
	return true;
}

bool Cmd::ViewINodeMap()
{
	return true;
}

bool Cmd::ViewBlockMap()
{
	return true;
}


void usage()
{
	cout << "Format\t\t\t��ʼ�����̣������ṹ" << endl <<
		"Mkfile [file path]\t\t�����ļ�" << endl <<
		"Mkdir [dir path]\t\t����Ŀ¼" << endl <<
		"Cd [dir path]\t\t�ı䵱ǰĿ¼" << endl <<
		"Delfile [file path]\tɾ���ļ���ע��ֻ�����ԣ�" << endl <<
		"Deldir [dir path]\tɾ��Ŀ¼��ע��ֻ�����ԣ�" << endl <<
		"Dir\t\t\t���ļ�Ŀ¼ ���г����ֺͽ���ʱ�䣬ע���������ԣ�" << endl <<
		"Copy [origin file path] [goal file path]\t\t\t�����ļ���ĳһ·��" << endl <<
		"Open [file path]\t�򿪲��༭�ļ���ע��ֻ�����ԣ�" << endl <<
		"Attrib [+r|-r] [+h|-h]  [file path]\t\t�����ļ����ԣ���ֻ������ֻ���������أ�������" << endl <<
		"Viewinodemap\t\t��ʾ��ǰinodeλʾͼ״��" << endl <<
		"Viewblockmap\t\t��ʾ��ǰblockλʾͼ״��" << endl;
}
