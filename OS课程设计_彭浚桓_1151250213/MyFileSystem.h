#pragma once

#include <string>

struct TxtBlock;
using namespace std;

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�

//һЩ�����Ķ���
const int BLOCK_SIZE = 64; //���̿�Ĵ�С����64�ֽ�
const int DIRECORY_ENTRY = 16;//Ŀ¼��Ĵ�С����16�ֽ�
const int I_NODE_BITMAP_SIZE = BLOCK_SIZE;//i-node λͼ һ��64�ֽڣ���512λ��,����һ�����̿�

struct Disc;
struct RootDirectory;
struct I_NodeBitmap;
struct BlockBitmap;
struct I_NODE;
union DataBlock;

struct DirecoryEntry;
struct IndexBlock;
struct TxtBlock;
struct DirectoryFileBlock;

//Ŀ¼��
struct DirecoryEntry
{
	char fileName[16];//�ļ���Ŀ¼��
	unsigned char flag;//0 ��ʾһ���ļ���1 ��ʾĿ¼
	int i_node_number;//i-node ��š���ָ���ļ�����Ŀ¼�������ڵ�
};

//�������ݿ�
struct IndexBlock
{
	int indexs[16];
};
//�ı��ļ����ݿ�
struct TxtBlock
{
	char txt[64];
};
//Ŀ¼�ļ����ݿ�
struct DirectoryFileBlock
{
	DirecoryEntry direcoryEntry[4];
};

union DataBlock
{
	IndexBlock indexBlock;//������
	TxtBlock txtBlock;//�ı��ļ����ݿ�
	DirectoryFileBlock directoryBlock;//Ŀ¼�ļ����ݿ�
};


//��Ŀ¼��������ĸ�Ŀ¼��
struct RootDirectory
{
	DirecoryEntry direcoryEntry[4];
};

//i-nodeλͼ
struct I_NodeBitmap
{
	bool i_node[I_NODE_BITMAP_SIZE * 8];
};

//���ݿ�λͼ�����������̵�״̬
struct BlockBitmap
{
	bool BlocksStates[512 * BLOCK_SIZE];
};

//i-node ����Ϊ16�ֽڣ�1+1+1+1+2*4+4��
//���ļ����������̿�ʱ����ʹ��һ��������ַ������˵�ļ����Ϊ18���̿�
struct I_NODE
{
	unsigned char isReadOnly;// �Ƿ�ֻ��
	unsigned char isHide;// �Ƿ�����
	unsigned char hour;// �����ļ�ϵͳʱ���Сʱ
	unsigned char minutes;// �����ļ�ϵͳʱ��ķ���
	int directAddress[2];// ֱ���̿��ַ����ָ��һ�����ݿ�
	int firstClassIndexAddress;// һ��������ַ����ָ��һ��������
};

//����
struct Disc
{
	RootDirectory rootDirectory;
	I_NodeBitmap i_nodeBitMap;
	BlockBitmap blockBitMap[2];//����1024����̿��״̬
	I_NODE i_node[512];//512��i-nodeռ�ô���128��
	DataBlock dataBlock[1024];
};




class Cmd{
public:
	
	~Cmd();
	bool parse(string cmd);
	static Cmd* getInstance();
	static string* split(string s, char c);
private:
	Cmd();
	static Cmd *instance;
	bool Format();//��ʼ�����̣������ṹ
	bool MkFile(string cmd);//�����ļ�
	bool MkDir(string cmd);//����Ŀ¼
	bool Cd(string cmd);//�ı䵱ǰĿ¼
	bool DelFile(string cmd);//ɾ���ļ���ע��ֻ�����ԣ�
	bool DelDir(string cmd);//ɾ��Ŀ¼
	bool Dir();//���ļ�Ŀ¼
	bool Copy(string orign_path,string goal_path);//�����ļ���ĳһ·��
	bool Open(string cmd);//�򿪲��༭�ļ�
	bool Attrib(string file_path,string operation);//�����ļ����ԣ��Ƿ�Ϊֻ�����Ƿ����أ�
	bool ViewINodeMap();//��ʾ��ǰi-nodeλʾͼ״��
	bool ViewBlockMap();//��ʾ��ǰblockλʾͼ״��

};

inline Cmd::Cmd(){
}

inline Cmd::~Cmd(){
}

inline Cmd* Cmd::getInstance(){
	if (instance == nullptr){
		instance = new Cmd();
	}

	return instance;
}

//�������ķָ��Ĭ���Կո���Ϊ�ָ���
inline string* Cmd::split(string s, char c=' '){
	string* strings = new string[3];
	string temps(s);
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	for (auto i = 0,j=0;;j++)
	{
		if ((i = temps.find_first_of(c))!=string::npos){
			strings[j] = string(temps, 0, i);
			temps = string(temps, i + 1);
		}
		else
		{
			strings[j] = string(temps, 0, i);
			break;
		}
	}
	return strings;
}

