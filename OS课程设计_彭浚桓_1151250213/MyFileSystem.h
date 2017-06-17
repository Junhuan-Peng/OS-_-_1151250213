#pragma once

#include <string>
#include <time.h>

struct TxtBlock;
using namespace std;

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�

//һЩ�����Ķ���
const int BLOCK_SIZE = 64; //���̿�Ĵ�С����64�ֽ�
const int DIRECORY_ENTRY = 16;//Ŀ¼��Ĵ�С����16�ֽ�

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
	char fileName[11];//�ļ���Ŀ¼��
	unsigned char flag;//0 ��ʾһ���ļ���1 ��ʾĿ¼
	int i_node_number;//i-node ��š���ָ���ļ�����Ŀ¼�������ڵ�
	DirecoryEntry(){
		fileName[0] = '\0';
		flag = -1;
		i_node_number = -1;
	}
	bool init(char fileName_[11],int flag_,int i_node_number_)
	{

		strcpy(this->fileName, fileName_);
		this->flag = flag_;
		this->i_node_number = i_node_number_;
		return true;
	}

};

//�������ݿ�
struct IndexBlock
{
	int indexs[16];
};

//�ı��ļ����ݿ�
struct TxtBlock
{
	char txt[BLOCK_SIZE];
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
	DataBlock(void)
	{
		
	}
};


//��Ŀ¼��������ĸ�Ŀ¼��
struct RootDirectory
{
	DirecoryEntry direcoryEntries[4];
	bool getAnVoidDirecoryEntry(int &j)
	{
		for (int i = 0; i < 4; i++){
			if(direcoryEntries[i].fileName[0]=='\0')
			{
				j = i;
				return true;
			}
		}
		return false;
	}
	
};

//i-nodeλͼ
struct I_NodeBitmap
{
	bool i_node_bitmap[512]{false};
	//��ȡһ���ܹ�ʹ�õ�i-node���±�

	/**
	 * \brief ��ȡһ���ܹ�ʹ�õ�i-node�±�
	 * \param i ���ڴ洢�±������
	 * \return �������->true
	 */
	bool getAnINodeNum(int& i)
	{
		i = 0;
		// ReSharper disable once CppPossiblyErroneousEmptyStatements
		while (i < 1024 && i_node_bitmap[i++] != false);
		i -= 1;//���������һ��i++

		//������ڣ����Ӧλ��false���򷵻�=��false->true
		//��������ڣ���i������1023�����ӦλΪtrue���򷵻�=��true -> false

		return !i_node_bitmap[i];
	}
};

//���ݿ�λͼ�����������̵�״̬
struct BlockBitmap
{
	bool blocks[512 * 2]{false};

	
	/**
	 * \brief ��ȡһ���ܹ�ʹ�õ����ݿ���±�
	 * \param i 
	 * \return �������->true
	 */
	bool getABlockNum(int& i)
	{
		i = 0;
		// ReSharper disable once CppPossiblyErroneousEmptyStatements
		while (i < 1024 && blocks[i++] != false);
		return !blocks[i];
	}
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

	void init()
	{
		time_t t = time(nullptr);
		char temp[1];
		strftime(temp, sizeof(temp), "%H", localtime(&t));
		hour = *temp;
		strftime(temp, sizeof(temp), "%M", localtime(&t));
		minutes = *temp;
	}

	//�жϵ�ǰi-node�ܷ���������i-node(��Ŀ¼�������ļ���
	bool isFull()
	{
		//TODO �����ж�i-node�Ƿ���
		return false;
	}

	bool addChild(int childINodeNum)
	{
		//TODO ��������ӹ��������ӽڵ�Ĵ���
		return true;
	}

};

//����
struct Disc
{
	RootDirectory rootDirectory;
	I_NodeBitmap i_nodeBitMap;//����512��i-node��״̬
	BlockBitmap blockBitMap;//����1024����̿��״̬
	I_NODE i_node_s[512];//512��i-nodeռ�ô���128��
	DataBlock dataBlock[1024];

};


class Cmd
{
public:

	Cmd(Disc* disc);
	~Cmd();
	bool parse(string cmd);
	static Cmd* getInstance(Disc* disc);
	static string* split(string s, char c);

	Disc* disc;

private:

	int cwd_inode;
	string cwd;
public:
	int getCwdINode() const
	{
		return cwd_inode;
	}

	void setCwdINode(int cwd_inode)
	{
		this->cwd_inode = cwd_inode;
	}

	string getCwd() const
	{
		return cwd;
	}

	void setCwd(const string& cwd)
	{
		this->cwd = cwd;
	}

private:
	Cmd();
	static Cmd* instance;
	bool Format();//��ʼ�����̣������ṹ
	bool MkFile(string filepath);//�����ļ�
	bool MkDir(string dir);//����Ŀ¼
	bool Cd(string dir);//�ı䵱ǰĿ¼
	bool DelFile(string filepath);//ɾ���ļ���ע��ֻ�����ԣ�
	bool DelDir(string dir);//ɾ��Ŀ¼
	bool Dir();//���ļ�Ŀ¼
	bool Copy(string orign_path, string goal_path);//�����ļ���ĳһ·��
	bool Open(string filepath);//�򿪲��༭�ļ�
	bool Attrib(string file_path, string operation);//�����ļ����ԣ��Ƿ�Ϊֻ�����Ƿ����أ�
	bool ViewINodeMap();//��ʾ��ǰi-nodeλʾͼ״��
	bool ViewBlockMap();//��ʾ��ǰblockλʾͼ״��
};

inline Cmd::Cmd() : disc(nullptr), cwd_inode(-1){
}


inline Cmd::Cmd(Disc* disc):cwd_inode(-1)
{
	
	this->disc = disc;
}

inline Cmd::~Cmd()
{
}

inline Cmd* Cmd::getInstance(Disc* disc)
{
	if (instance == nullptr)
	{
		instance = new Cmd(disc);
	}

	return instance;
}

//�������ķָ��Ĭ���Կո���Ϊ�ָ���
inline string* Cmd::split(string s, char c = ' ')
{
	string* strings = new string[3];
	string temps(s);
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	for (auto i = 0, j = 0;; j++)
	{
		if ((i = temps.find_first_of(c)) != string::npos)
		{
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
