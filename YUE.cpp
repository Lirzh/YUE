// ���������ͷ�ļ���bits/stdc++.h��һ���Ǳ�׼���㷺ʹ�õ�ͷ�ļ���������C++��׼��Ĵ󲿷�����
#include <bits/stdc++.h>
// ����Windows API������ִ��ϵͳ�����
#include <windows.h>
// ����endlΪ���з�������ÿ�����ʱ�ظ�д'\n'
#define endl '\n'
// ʹ�ñ�׼�����ռ䣬�򻯴����жԱ�׼�������
using namespace std;
// ������������Щ��������main����֮����
void ProcessFile(ifstream& in, ofstream& out);           // �����ļ�����
void CopyFile(const char* source, const char* destination); // �����ļ�
int main(int argc, char* argv[]) {
	if(argc==2&&(strcmp(argv[1],"-h")==0||strcmp(argv[1],"-help")==0)){
		cout<<"Use \"YUE.exe [address]\" or \"YUE [address]\"to make your file beautiful."<<endl;
		return 0;	
	}else
	if(argc==2&&!(strcmp(argv[1],"-h")==0||strcmp(argv[1],"-help")==0)){
		// ����ifstream�������ڶ�ȡ�ļ�,ofstream��������д����ʱ�ļ�
    	ifstream in(argv[1]);
    	ofstream out("Temporary");
    	// ����ProcessFile�������������ļ���ÿһ�У���д�뵽��ʱ�ļ���
    	ProcessFile(in, out);
    	// �ر��ļ������ͷ�ϵͳ��Դ
    	in.close();
    	out.close();
    	// ����CopyFile��������ʱ�ļ����Ƶ��û�ָ����λ�ã����������ļ�
    	CopyFile("Temporary", argv[1]);
    	cout << "Success!";
    	return 0;
	}else{
		cerr<<"What do you do?"<<endl;
		return 1;
	}
	return 1;
}
// ProcessFile������ȡ�����ļ���ÿһ�У��������ض�����д�뵽����ļ�
void ProcessFile(ifstream& in, ofstream& out) {
    // str���ڴ洢��ǰ�У�ls���ڴ洢��һ��
    string str, ls;
    // �����������ڸ�������
    long long ti = 0;
    // ѭ����ȡ�ļ�ֱ���ļ�����
    while (getline(in, str)) {
        // ȥ����ĩ�ո�
        while (str.back() == ' ') str.erase(str.length() - 1, 1);
        // �����ȡ�����ǿյģ�����ֻ�����ո���Ʊ��������������
        if (str.empty() || count(str.begin(), str.end(), ' ') + count(str.begin(), str.end(), '\t') >= str.size()) continue;
        // �����ض�����������һ����')'��������ǰ����'{'��ʼ
        if (!ls.empty() && ls.back() == ')') {
            size_t pos = str.find_first_not_of('\t');
            if (pos != string::npos && str[pos] == '{') {
                out << '{'; // ���'{'
                str.erase(pos, 1); // �ӵ�ǰ����ɾ��'{'
            }
            pos = str.find_first_not_of(' ');
            if (pos != string::npos && str[pos] == '{') {
                out << '{'; // ���'{'
                str.erase(pos, 1); // �ӵ�ǰ����ɾ��'{'
            }
        }
        // ������ǵ�һ�У������ڵ�ǰ��ǰ�����㹻�Ŀո���������ļ��в���һ�����з�
        if (ti != 0 && count(str.begin(), str.end(), ' ') < str.size()) {
            out << endl;
        }
        // �������ĵ�ǰ��д�뵽����ļ�
        out << str;
        // ������һ�е��ı�Ϊ��ǰ�У�Ϊ��һ��ѭ����׼��
        ls = str;
        ti++; // �м���������
    }
}
// CopyFile����ʹ��system�����������ļ�
void CopyFile(const char* source, const char* destination) {
    // ����һ���ַ����飬���ڴ洢����������
    char command[256];
    // ���������ļ�������
    sprintf_s(command, sizeof(command), "copy %s %s /y", source, destination);
    // ִ�и����ļ�����
    system(command);
}