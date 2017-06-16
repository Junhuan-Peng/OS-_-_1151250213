#pragma once

#include <string>
#include <time.h>

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
	bool i_node[512]{false};
};

//���ݿ�λͼ�����������̵�״̬
struct BlockBitmap
{
	bool BlocksStates[512 * 2]{false};
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

	I_NODE()
	{
		isReadOnly = '0';
		isHide = '0';

		time_t t = time(nullptr);
		char temp[1];
		strftime(temp, sizeof(temp), "%H", localtime(&t));
		hour = *temp;
		strftime(temp, sizeof(temp), "%M", localtime(&t));
		minutes = *temp;
		directAddress[0] = -1;
		directAddress[1] = -1;
		firstClassIndexAddress = -1;
	}
};

//����
struct Disc
{
	RootDirectory *rootDirectory;
	I_NodeBitmap *i_nodeBitMap;//����512��i-node��״̬
	BlockBitmap *blockBitMap;//����1024����̿��״̬
	I_NODE *i_node_s;//512��i-nodeռ�ô���128��
	DataBlock *dataBlock;

	void init()
	{
		rootDirectory = new RootDirectory;
		i_nodeBitMap = new I_NodeBitmap;
		blockBitMap = new BlockBitmap;
		
		i_node_s = new I_NODE[512];
		dataBlock = new DataBlock[1024];
	}
};




class Cmd{
public:

	Cmd(Disc* disc);
	~Cmd();
	bool parse(string cmd);
	static Cmd* getInstance(Disc* disc);
	static string* split(string s, char c);
private:
	Disc *disc;
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

inline Cmd::Cmd(Disc *disc){
	this->disc = disc;
}

inline Cmd::~Cmd(){
}

inline Cmd* Cmd::getInstance(Disc *disc){
	if (instance == nullptr){
		instance = new Cmd(disc);
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

