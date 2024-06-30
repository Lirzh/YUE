// ���������ͷ�ļ���bits/stdc++.h��һ���Ǳ�׼���㷺ʹ�õ�ͷ�ļ���������C++��׼��Ĵ󲿷�����
#include <bits/stdc++.h>
// ����Windows API������ִ��ϵͳ�����
#include <windows.h>
// ����endlΪ���з�������ÿ�����ʱ�ظ�д'\n'
#define endl '\n'
// ʹ�ñ�׼�����ռ䣬�򻯴����жԱ�׼�������
using namespace std;
// ������������Щ��������main����֮����
bool OpenFile(ifstream& inStream, const char* address); // ���Դ��ļ��������سɹ����
void ProcessFile(ifstream& in, ofstream& out);           // �����ļ�����
void CopyFile(const char* source, const char* destination); // �����ļ�
void RestoreWindowPosition(HWND hwnd); // ���洰��λ��
void SaveWindowPosition(HWND hwnd); // ��ȡ����λ��
int main() {
    // �������ڵ㣬���岢��ʼ������λ��
    RestoreWindowPosition(GetForegroundWindow());
    // ����ѭ������������ظ�ִ��
    while (1) {
        // ����һ���㹻����ַ��������洢�ļ�·��
        char address[128];
        // �����ʾ��Ϣ��Ҫ���û������ļ�·��
        cout << "Address(\"exit\" to exit): ";
        // ʹ��cin.getline��ȫ�ض�ȡ�û�������ļ�·��
        cin.getline(address, 128);
        // ����ifstream�������ڶ�ȡ�ļ�
        ifstream in;
        // ����ofstream��������д����ʱ�ļ�
        ofstream out("Temporary");
        // ����û�����"exit"�����˳�ѭ��
        if (strcmp(address, "exit") == 0) break;
        // ����OpenFile�������Դ��û�ָ�����ļ������ʧ�������������Ϣ���˳�����
        if (!OpenFile(in, address) || !out.is_open()) {
            cerr << "Failed to open files." << endl;
            // ��ͣ500����
            Sleep(500);
            // ����
            system("cls");
            // ������һ��ѭ��
            continue;
        }
        // ����ProcessFile�������������ļ���ÿһ�У���д�뵽��ʱ�ļ���
        ProcessFile(in, out);
        // �ر��ļ������ͷ�ϵͳ��Դ
        in.close();
        out.close();
        // ����CopyFile��������ʱ�ļ����Ƶ��û�ָ����λ�ã����������ļ�
        CopyFile("Temporary", address);
        // ����������Ϊ��һ�γ���ִ����׼��
        cout << "Success!";
        // ���洰��λ��
        SaveWindowPosition(GetForegroundWindow());
        // ��ͣ500����
        Sleep(500);
        // ����
        system("cls");
    }
    // �˳�ѭ���󱣴洰��λ��
    SaveWindowPosition(GetForegroundWindow());
    // �����˳�ʱ���
    cout << "Exit successfully!";
    // ���������˳��ķ���ֵ
    return 0;
}
// OpenFile�������Դ�һ���ļ��������ز����Ƿ�ɹ�
bool OpenFile(ifstream& inStream, const char* address) {
    // ���Դ��ļ�����ַ��address�����ṩ
    inStream.open(address);
    // ����ļ��ɹ��򿪣�����true�����򷵻�false
    return inStream.is_open();
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
// ���洰��λ��
void SaveWindowPosition(HWND hwnd) {
    // ��ȡ����λ��
    RECT rect;
    GetWindowRect(hwnd, &rect);
    char buffer[100];
    // ������λ�ø�ʽ��Ϊ�ַ���
    sprintf_s(buffer, sizeof(buffer), "%ld,%ld", rect.left, rect.top);
    // �������ע����
    HKEY hKey;
    RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\YUE", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
    // ������λ�ñ��浽ע���
    RegSetValueEx(hKey, "WindowPosition", 0, REG_SZ, (BYTE*)buffer, strlen(buffer) + 1);
    // �ر�ע����
    RegCloseKey(hKey);
}
// ��ȡ����λ��
void RestoreWindowPosition(HWND hwnd) {
    // ���Դ�ע����
    HKEY hKey;
    char buffer[100];
    DWORD size = sizeof(buffer);
    if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\YUE", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        // ��ע����ȡ����λ��
        RegQueryValueEx(hKey, "WindowPosition", NULL, NULL, (BYTE*)buffer, &size);
        // �ر�ע����
        RegCloseKey(hKey);
        int x, y;
        // ��������λ��
        sscanf_s(buffer, "%d,%d", &x, &y);
        // ���ô���λ��
        SetWindowPos(hwnd, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    }
}