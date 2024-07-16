// 引入所需的头文件，bits/stdc++.h是一个非标准但广泛使用的头文件，包含了C++标准库的大部分内容
#include <bits/stdc++.h>
// 引入Windows API，用于执行系统命令等
#include <windows.h>
// 定义endl为换行符，避免每次输出时重复写'\n'
#define endl '\n'
// 使用标准命名空间，简化代码中对标准库的引用
using namespace std;
// 函数声明，这些函数将在main函数之后定义
void ProcessFile(ifstream& in, ofstream& out);           // 处理文件内容
void CopyFile(const char* source, const char* destination); // 复制文件
int main(int argc, char* argv[]) {
	if(argc==2&&(strcmp(argv[1],"-h")==0||strcmp(argv[1],"-help")==0)){
		cout<<"Use \"YUE.exe [address]\" or \"YUE [address]\"to make your file beautiful."<<endl;
		return 0;	
	}else
	if(argc==2&&!(strcmp(argv[1],"-h")==0||strcmp(argv[1],"-help")==0)){
		// 定义ifstream对象用于读取文件,ofstream对象用于写入临时文件
    	ifstream in(argv[1]);
    	ofstream out("Temporary");
    	// 调用ProcessFile函数处理输入文件的每一行，并写入到临时文件中
    	ProcessFile(in, out);
    	// 关闭文件流，释放系统资源
    	in.close();
    	out.close();
    	// 调用CopyFile函数将临时文件复制到用户指定的位置，覆盖现有文件
    	CopyFile("Temporary", argv[1]);
    	cout << "Success!";
    	return 0;
	}else{
		cerr<<"What do you do?"<<endl;
		return 1;
	}
	return 1;
}
// ProcessFile函数读取输入文件的每一行，并根据特定规则写入到输出文件
void ProcessFile(ifstream& in, ofstream& out) {
    // str用于存储当前行，ls用于存储上一行
    string str, ls;
    // 计数器，用于跟踪行数
    long long ti = 0;
    // 循环读取文件直到文件结束
    while (getline(in, str)) {
        // 去除行末空格
        while (str.back() == ' ') str.erase(str.length() - 1, 1);
        // 如果读取的行是空的，或者只包含空格或制表符，则跳过处理
        if (str.empty() || count(str.begin(), str.end(), ' ') + count(str.begin(), str.end(), '\t') >= str.size()) continue;
        // 处理特定规则，例如上一行以')'结束，当前行以'{'开始
        if (!ls.empty() && ls.back() == ')') {
            size_t pos = str.find_first_not_of('\t');
            if (pos != string::npos && str[pos] == '{') {
                out << '{'; // 输出'{'
                str.erase(pos, 1); // 从当前行中删除'{'
            }
            pos = str.find_first_not_of(' ');
            if (pos != string::npos && str[pos] == '{') {
                out << '{'; // 输出'{'
                str.erase(pos, 1); // 从当前行中删除'{'
            }
        }
        // 如果不是第一行，并且在当前行前面有足够的空格，则在输出文件中插入一个换行符
        if (ti != 0 && count(str.begin(), str.end(), ' ') < str.size()) {
            out << endl;
        }
        // 将处理后的当前行写入到输出文件
        out << str;
        // 更新上一行的文本为当前行，为下一次循环做准备
        ls = str;
        ti++; // 行计数器递增
    }
}
// CopyFile函数使用system调用来复制文件
void CopyFile(const char* source, const char* destination) {
    // 定义一个字符数组，用于存储命令行命令
    char command[256];
    // 构建复制文件的命令
    sprintf_s(command, sizeof(command), "copy %s %s /y", source, destination);
    // 执行复制文件命令
    system(command);
}