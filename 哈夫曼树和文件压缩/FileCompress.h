#pragma once
#include <string>
#include <algorithm>


typedef long long LongType;
struct FileInfo
{
	unsigned char _ch;
	LongType _count;
	string _code;
	FileInfo(unsigned char ch=0)
		:_ch(ch)
		, _count(0)
	{}
	bool operator!=(const FileInfo& right)const
	{
		return this->_count != right._count;
	}
	bool operator<=(const FileInfo& right)const
	{
		return this->_count <= right._count;
	}
	FileInfo operator+(const FileInfo& right)const
	{
		FileInfo tmp;
		tmp._count = this->_count + right._count;
		return tmp;
	}
};

class FileCompress
{
public:
	FileCompress()
	{
		for (int i = 0; i < 256; i++)
		{
			_info[i]._ch = i;
		}
	}
	bool Compress(const char* filename)
	{
		FILE* fOut = fopen(filename,"rb");
		unsigned char ch ;
		fread(&ch, 1, 1, fOut);
		//统计每个字符出现的次数
		while (!feof(fOut))
		{
			_info[ch]._count++;
			fread(&ch, 1, 1, fOut);
		}

		HuffManTree<FileInfo> tree;
		FileInfo invalid;
		tree.CreateTree(_info,256, invalid);
		
		_GenerateHuffmanCode(tree._root);
		fseek(fOut,0,SEEK_SET);

		//count记录最后一个字节中补的位数
		char count=_GetCompressFile(filename);
		fseek(fOut, 0, SEEK_SET);

		//把最后一个字节中补的位数count放在配置文件的第一行
		_GetConfigurationFile(filename,count);

		fclose(fOut);
		return true;
	}

	bool unCompress(const char*fileHuffMan)
	{
		string fileConfig(fileHuffMan);

		//得到名字
		while (fileConfig[fileConfig.size() - 1] != 'H')
		{
			fileConfig.pop_back();
		}
		fileConfig.pop_back();
		char s[] = "Configuration";
		fileConfig += s;


		FILE* fOutConfig = fopen(fileConfig.c_str(), "rb");
		assert(fOutConfig);

		//取出补位的位数大小
		unsigned char Count ;
		fread(&Count,1,1,fOutConfig);
		//配置文件中按_ch 逗号 次数排列
		char *_ch=new char[sizeof(LongType) + 2];
		int size = sizeof(LongType) + 2;
		fread(_ch, size, 1, fOutConfig);
		while (!feof(fOutConfig))
		{
			_info[(unsigned char)_ch[0]]._count = *(LongType*)(&_ch[2]);
			fread(_ch, size, 1, fOutConfig);
		}
		fclose(fOutConfig);

		 
		HuffManTree<FileInfo> tree;
		FileInfo invalid;
		tree.CreateTree(_info,256,invalid);
		_GetUnCompressFile(tree._root,fileHuffMan,Count);
		return true;
	}
protected:
	void _GetUnCompressFile(HuffManTreeNode<FileInfo>* root,const char* fileHuffMan,int Count)
	{
		assert(root);
		string name(fileHuffMan);
		while (name[name.size() - 1] != 'H')
		{
			name.pop_back();
		}
		name.pop_back();
		int i = 0;
		while (name[i] != '.') 
		{ i++; }
		char a[8] = "HuffMan";
		name.insert(i,a,7);
		FILE* fWrite = fopen(name.c_str(),"wb");
		FILE* fRead = fopen(fileHuffMan, "rb");
		assert(fRead);
		assert(fWrite);
		HuffManTreeNode<FileInfo>* cur = root;
		char firstch[1];
		int secondch[1] = {0};
		fread(secondch, 1, 1, fRead);
		while (1)
		{	
			firstch[0] =(unsigned char) secondch[0];
			fread(secondch, 1, 1, fRead);
			if (feof(fRead))
				break;
			unsigned char temp = firstch[0];
			int count = 7;
			while (count >= 0)
			{
				temp >>= count;
				if ((temp&1) == 0)
				{
					cur=cur->_left;
				}
				else if ((temp&1) == 1)
				{
					cur=cur->_right;
				}
				temp= firstch[0];
				count--;
				if (cur->_left == NULL&&cur->_right == NULL)
				{
					unsigned char wr[1] = { cur->_weight._ch };
					fwrite(wr,1,1,fWrite);
					cur = root;
				}
			}
			
		}
		unsigned char temp=firstch[0];
		int count = 7;
		while (count >= Count)
		{
			temp >>= count;
			if ((temp&1) == 0)
			{
				cur = cur->_left;
			}
			else if ((temp & 1) == 1)
			{
				cur = cur->_right;
			}
			temp = firstch[0];
			count--;
		}
		unsigned char wr[1] = { cur->_weight._ch };
		fwrite(wr, 1, 1, fWrite);
		

		fclose(fWrite);
		fclose(fRead);

	}
	
	void _GetConfigurationFile(const char* filename,char count)
	{
		string fGetName(filename);
		fGetName += "Configuration";
		FILE* fGet = fopen(fGetName.c_str(), "wb");
		assert(fGet);
		//把最后一个字节中补的位数count放在配置文件的第一行
		fwrite(&count,1,1,fGet);

		int size = sizeof(LongType);
		for (int i = 0; i < 256; i++)
		{
			if (_info[(unsigned char)i]._count != 0)
			{
				//在配置文件中写入_ch,count
				char ch[2];
				ch[0] = i;
				ch[1] = ',';
				fwrite(ch, 2, 1, fGet);
				LongType count = { _info[(unsigned char)i]._count };
				fwrite(&count, size, 1, fGet);
			}
		}
		fclose(fGet);

	}
	int _GetCompressFile(const char* filename)
	{
		FILE* fOut = fopen(filename, "rb");
		assert(fOut);
		string fGetName(filename);
		fGetName += "HuffMan";
		FILE* fGet = fopen(fGetName.c_str(), "wb");
		assert(fGet);

		unsigned char ch ;
		unsigned char inCh = 0;
		int count = 0;
		fread(&ch, 1, 1, fOut);
		while (!feof(fOut))
		{
			string& code = _info[ch]._code;
			for (int i = 0; i < code.size(); i++)
			{
				inCh <<= 1;
				if (code[i] == '1')
				{
					inCh |= 1;
				}

				if (++count == 8)
				{
					fwrite(&inCh,1,1,fGet);
					count = 0;
				}

			}
			fread(&ch, 1, 1, fOut);
		}
		int Count = 0;
		if (count != 0)
		{
			inCh <<= (8 - count);
			Count = 8 - count;
			fwrite(&inCh,1,1, fGet);
		}
		fclose(fOut);
		fclose(fGet);

		return Count;
	}
	void _GenerateHuffmanCode(HuffManTreeNode<FileInfo>* root)
	{
		if (root == NULL)
			return;
		_GenerateHuffmanCode(root->_left);
		_GenerateHuffmanCode(root->_right);

		if (root->_left == NULL&&root->_right == NULL)
		{
			HuffManTreeNode<FileInfo>*cur = root;
			string& code = _info[cur->_weight._ch]._code;
			HuffManTreeNode<FileInfo>* parent = cur->_parent;
			while (cur->_parent != NULL)
			{
				if (parent->_left == cur)
				{
					code += '0';
				}
				else if (parent->_right == cur)
				{
					code += '1';
				}
				cur = parent;
				parent = cur->_parent;
			}
			reverse(code.begin(),code.end());
		}

	}

	FileInfo _info[256];
};

