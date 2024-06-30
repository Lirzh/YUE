// 引入所需的头文件，bits/stdc++.h是一个非标准但广泛使用的头文件，包含了C++标准库的大部分内容
#include <bits/stdc++.h>
// 引入Windows API，用于执行系统命令等
#include <windows.h>
// 定义endl为换行符，避免每次输出时重复写'\n'
#define endl '\n'
// 使用标准命名空间，简化代码中对标准库的引用
using namespace std;
// 函数声明，这些函数将在main函数之后定义
bool OpenFile(ifstream& inStream, const char* address); // 尝试打开文件，并返回成功与否
void ProcessFile(ifstream& in, ofstream& out);           // 处理文件内容
void CopyFile(const char* source, const char* destination); // 复制文件
void RestoreWindowPosition(HWND hwnd); // 保存窗口位置
void SaveWindowPosition(HWND hwnd); // 读取窗口位置
int main() {
    // 程序的入口点，定义并初始化窗口位置
    RestoreWindowPosition(GetForegroundWindow());
    // 无限循环，允许程序重复执行
    while (1) {
        // 定义一个足够大的字符数组来存储文件路径
        char address[128];
        // 输出提示信息，要求用户输入文件路径
        cout << "Address(\"exit\" to exit): ";
        // 使用cin.getline安全地读取用户输入的文件路径
        cin.getline(address, 128);
        // 定义ifstream对象用于读取文件
        ifstream in;
        // 定义ofstream对象用于写入临时文件
        ofstream out("Temporary");
        // 如果用户输入"exit"，则退出循环
        if (strcmp(address, "exit") == 0) break;
        // 调用OpenFile函数尝试打开用户指定的文件，如果失败则输出错误信息并退出程序
        if (!OpenFile(in, address) || !out.is_open()) {
            cerr << "Failed to open files." << endl;
            // 暂停500毫秒
            Sleep(500);
            // 清屏
            system("cls");
            // 继续下一次循环
            continue;
        }
        // 调用ProcessFile函数处理输入文件的每一行，并写入到临时文件中
        ProcessFile(in, out);
        // 关闭文件流，释放系统资源
        in.close();
        out.close();
        // 调用CopyFile函数将临时文件复制到用户指定的位置，覆盖现有文件
        CopyFile("Temporary", address);
        // 清屏操作，为下一次程序执行做准备
        cout << "Success!";
        // 保存窗口位置
        SaveWindowPosition(GetForegroundWindow());
        // 暂停500毫秒
        Sleep(500);
        // 清屏
        system("cls");
    }
    // 退出循环后保存窗口位置
    SaveWindowPosition(GetForegroundWindow());
    // 程序退出时输出
    cout << "Exit successfully!";
    // 程序正常退出的返回值
    return 0;
}
// OpenFile函数尝试打开一个文件，并返回操作是否成功
bool OpenFile(ifstream& inStream, const char* address) {
    // 尝试打开文件，地址由address参数提供
    inStream.open(address);
    // 如果文件成功打开，返回true，否则返回false
    return inStream.is_open();
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
// 保存窗口位置
void SaveWindowPosition(HWND hwnd) {
    // 获取窗口位置
    RECT rect;
    GetWindowRect(hwnd, &rect);
    char buffer[100];
    // 将窗口位置格式化为字符串
    sprintf_s(buffer, sizeof(buffer), "%ld,%ld", rect.left, rect.top);
    // 创建或打开注册表键
    HKEY hKey;
    RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\YUE", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
    // 将窗口位置保存到注册表
    RegSetValueEx(hKey, "WindowPosition", 0, REG_SZ, (BYTE*)buffer, strlen(buffer) + 1);
    // 关闭注册表键
    RegCloseKey(hKey);
}
// 读取窗口位置
void RestoreWindowPosition(HWND hwnd) {
    // 尝试打开注册表键
    HKEY hKey;
    char buffer[100];
    DWORD size = sizeof(buffer);
    if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\YUE", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        // 从注册表读取窗口位置
        RegQueryValueEx(hKey, "WindowPosition", NULL, NULL, (BYTE*)buffer, &size);
        // 关闭注册表键
        RegCloseKey(hKey);
        int x, y;
        // 解析窗口位置
        sscanf_s(buffer, "%d,%d", &x, &y);
        // 设置窗口位置
        SetWindowPos(hwnd, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    }
}