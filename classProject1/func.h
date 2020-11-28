#pragma once
#include <iostream>
#include <windows.h>
#include <string>
/********************************************
*											*
*Coptright 2020								*
*Win32 API Graphic programming Class library*
*Made By wzx000000@outlook.com				*
*											*
********************************************/
using namespace std;
#pragma warning(disable : 4996)
#define MAX_STRING_SIZE 260
#define HEADER_FILE_VERSION 1

static char* U2G(const char* utf8) {
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}
static char* G2U(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

//获取打开的文件名
char* gfn1() {

	OPENFILENAME ofn;

	char szFileName[MAX_PATH];

	ZeroMemory(&ofn, sizeof(ofn));
	szFileName[0] = 0;

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0\0";
	ofn.lpstrFile = szFileName; //文件名将被保存在此变量中 
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = "txt";
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	//定义完了对话框
	GetOpenFileName(&ofn);
	char* str = new char[MAX_PATH];
	strcpy(str, szFileName);
	return str;

}

//获取打开的文件名,并将对话框作为子窗体
char* gfn1_child(HWND hwnd) {

	OPENFILENAME ofn;

	char szFileName[MAX_PATH];

	ZeroMemory(&ofn, sizeof(ofn));
	szFileName[0] = 0;

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0\0";
	ofn.lpstrFile = szFileName; //文件名将被保存在此变量中 
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = "txt";
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	//定义完了对话框
	GetOpenFileName(&ofn);
	char* str = new char[MAX_PATH];
	strcpy(str, szFileName);
	return str;
}

BOOL LoadFile(HWND hEdit, LPSTR pszFileName) {
	HANDLE hFile;
	BOOL bSuccess = FALSE;

	hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
	if (hFile != INVALID_HANDLE_VALUE) {
		DWORD dwFileSize;
		dwFileSize = GetFileSize(hFile, NULL);
		if (dwFileSize != 0xFFFFFFFF) {
			LPSTR pszFileText;
			pszFileText = (LPSTR)GlobalAlloc(GPTR, dwFileSize + 1);
			if (pszFileText != NULL) {
				DWORD dwRead;
				if (ReadFile(hFile, pszFileText, dwFileSize, &dwRead, NULL)) {
					pszFileText[dwFileSize] = 0; // Null terminator
					if (SetWindowText(hEdit, pszFileText))
						bSuccess = TRUE; // It worked!
				}
				GlobalFree(pszFileText);
			}
		}
		CloseHandle(hFile);
	}
	return bSuccess;
}//dev cpp中生成的 loadfile 
BOOL SaveFile(HWND hEdit, LPSTR pszFileName) {
	HANDLE hFile;
	BOOL bSuccess = FALSE;

	hFile = CreateFile(pszFileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile != INVALID_HANDLE_VALUE) {
		DWORD dwTextLength;
		dwTextLength = GetWindowTextLength(hEdit);
		if (dwTextLength > 0) {
			LPSTR pszText;
			pszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
			if (pszText != NULL) {
				if (GetWindowText(hEdit, pszText, dwTextLength + 1)) {
					DWORD dwWritten;
					if (WriteFile(hFile, pszText, dwTextLength, &dwWritten, NULL))
						bSuccess = TRUE;
				}
				GlobalFree(pszText);
			}
		}
		CloseHandle(hFile);
	}
	return bSuccess;
}//dev cpp中生成的 Savefile

void alert(const char str[], const char captain[]) {
	MessageBox(NULL, str, captain, NULL | MB_OK);
}
bool confirm(const char str[], const char captain[]) {
	int result = MessageBox(NULL, str, captain, NULL | MB_YESNO);
	if (result == IDYES)
		return true;

	return false;
}

//WNDCLASSEX wc1;
/*第一期*****************************************************************
第一批
*/

class window_ {
public:
	WNDCLASSEX wc; /* A properties struct of our window							窗口的属性结构 */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window			一个“句柄”，因此是H，或者指向我们窗口的指针  */
	MSG msg; /* A temporary location for all messages							 所有消息的临时位置*/
	HINSTANCE his;
	char caption[256]="Form";
	window_(/*WNDPROC , HINSTANCE*/);
	void histance_(HINSTANCE);
	void callback_(WNDPROC);
	bool create_wind(int width, int height);
	void alert(const char str[], const char captain[]);
	bool confirm(const char str[], const char captain[]);
	void set_text(const char str[]);
protected:
	void sett(const char str[], HWND hedit);
};
window_::window_(/*WNDPROC wndproc , HINSTANCE handle*/) {
	//构造函数
	memset(&this->wc, 0, sizeof(this->wc));
	this->wc.cbSize = sizeof(WNDCLASSEX);
	//this->wc.lpfnWndProc = WndProc; /* This is where we will send messages to		我们将向这里发送信息 */
	//this->wc.hInstance = hInstance;
	this->wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it
	白色，彩色窗口只是一个系统颜色的定义，请尝试按住Ctrl键并单击它  */
	this->wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	this->wc.lpszClassName = "WindowClass_";
	this->wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon	加载标准图标 */
	this->wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon 使用名称“A”来使用项目图标 */
	
	

}
void window_::callback_(WNDPROC wndproc) {
	this->wc.lpfnWndProc = wndproc;

}
void window_::histance_(HINSTANCE handle) {
	this->wc.hInstance = handle;
	his = handle;
}
bool window_::create_wind(int width,int height) {
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass_", caption, WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		width, /* width */
		height, /* height */
		NULL, NULL, this->wc.hInstance, NULL);

	if (hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	while (GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... 如果没有收到错误  */
		TranslateMessage(&msg); /* Translate key codes to chars if present 	将密钥代码转换为字符（如果存在）*/
		DispatchMessage(&msg); /* Send it to WndProc 发送给WndProc。*/
	}
	return msg.wParam;
}
void window_::alert(const char str[] , const char captain[]) {
	MessageBox(this->hwnd, str, captain, NULL | MB_OK);
}
bool window_::confirm(const char str[] , const char captain[]) {
	int result = MessageBox(this->hwnd, str, captain, NULL | MB_YESNO);
	if (result == IDYES) 
		return true;
	
	return false;
}
void window_::sett(const char str[], HWND hedit) {
	SetWindowText(hedit, str);
}
void window_::set_text(const char str[]) {
	sett(str,hwnd);
}



class Text_ {
public:
	unsigned int id;
	HWND hwnd;
	void create(const char str[], unsigned int Handle,HWND hparent);
	void set_text(const char str[]);
	char* get_str();
	HWND hwnd_parent;
	void Setlocation(int x, int y, int width, int heignt);
};
void Text_::create(const char str[], unsigned int Handle, HWND hparent) {
	hwnd=CreateWindow("EDIT", str, WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
	hwnd_parent = hparent;
	id = Handle;
	
	SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	
}
void Text_::set_text(const char str[]) {
	SetWindowText(hwnd, str);
}
void Text_::Setlocation(int x,int y,int width ,int heignt) {
	MoveWindow(GetDlgItem(hwnd_parent, this->id), x, y, width, heignt, TRUE);
}
char * Text_::get_str() {
	DWORD dwTextLength;
	dwTextLength = GetWindowTextLength(this->hwnd);
	LPSTR pszText;
	pszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
	GetWindowText(this ->hwnd, pszText, dwTextLength + 1);
	return (char*)pszText;

}

class SimpleText_ : public Text_ {
public:
	void create(const char str[], unsigned int Handle, HWND hparent) {
		hwnd = CreateWindow("EDIT", str, WS_CHILD | WS_VISIBLE | ES_WANTRETURN | WS_BORDER,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
		hwnd_parent = hparent;
		id = Handle;

		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));

	}
};

class BorderText_ : public Text_ {
public:
	void create(const char str[], unsigned int Handle, HWND hparent) {
		hwnd = CreateWindow("EDIT", str, WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | WS_BORDER,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
		hwnd_parent = hparent;
		id = Handle;

		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	}
};

/*第二批*/
class ListBox_ {
public:
	HWND hwnd;
	unsigned int id;
	HWND hwnd_parent;

	void create(unsigned int Handle, HWND hparent);
	void add(const char str[]);
	void Setlocation(int x, int y, int width, int heignt);
	char* getText(int size);
	int getindex();
	void removeItem(int index);
	void insertItem(int index, const char str[]);
	void setItemText(int index,const char str[]);
	char* getItemText(int index, int size);
	void clean();
	int getCount();
};
void ListBox_::create(unsigned int Handle, HWND hparent) {
	hwnd_parent = hparent;
	id = Handle;
	hwnd = CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VSCROLL | WS_TABSTOP | LBS_STANDARD | /*LBS_OWNERDRAWFIXED | */LBS_HASSTRINGS|WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
	ShowWindow(hwnd, SW_SHOW);
	SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	
}
void ListBox_::Setlocation(int x, int y, int width, int heignt) {
	MoveWindow(GetDlgItem(hwnd_parent, this->id), x, y, width, heignt, TRUE);
}
void ListBox_::add(const char str[]) {

	SendMessage(this->hwnd, LB_ADDSTRING, 0, (LPARAM)str);
	
}
char* ListBox_::getText(int size) {
	if (size <= 0)return (CHAR*)"";
	int lbItem = (int)SendMessage(this->hwnd, LB_GETCURSEL, 0, 0);
	char* str=new char[size];
	
	if (lbItem != -1)
		SendMessage(this->hwnd, LB_GETTEXT, lbItem, (LPARAM)str);
	else strcpy(str,"");
	return str;
}
int ListBox_::getindex() {
	int lbItem = (int)SendMessage(this->hwnd, LB_GETCURSEL, 0, 0);
	return lbItem;
}
void ListBox_::removeItem(int index) {
	SendMessage(this->hwnd, LB_DELETESTRING, index, 0);
}
void ListBox_::insertItem(int index, const char str[]) {
	SendMessage(this->hwnd, LB_INSERTSTRING, index, (LPARAM)str);
}
void ListBox_::setItemText(int index, const char str[]) {
	this->removeItem(index);
	this->insertItem(index, str);
}
char* ListBox_::getItemText(int index, int size) {
	if (size <= 0)return (CHAR*)"";
	char* str = new char[size];

	if (index != -1)
		SendMessage(this->hwnd, LB_GETTEXT, index, (LPARAM)str);
	else strcpy(str, "");
	return str;
}
void ListBox_::clean() {
	SendMessage(this->hwnd, LB_RESETCONTENT, 0, 0);
}
int ListBox_::getCount() {
	return (int)SendMessage(hwnd, LB_GETCOUNT, 0, 0);
}
/*第三批*/
class Button_ {
public:
	HWND hwnd;
	unsigned int id;
	HWND hwnd_parent;
	void create(const char captain[] ,unsigned int Handle, HWND hparent);
	void setLocation(int x, int y, int width, int heignt);
	void setText(const char str[]);
	char* getText();

};
void Button_::create(const char captain[], unsigned int Handle, HWND hparent) {
	hwnd_parent = hparent;
	id = Handle;
	hwnd=CreateWindow("BUTTON", captain, WS_CHILD | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, NULL, NULL);
	SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
}
void Button_::setLocation(int x, int y, int width, int heignt) {
	MoveWindow(GetDlgItem(hwnd_parent, this->id), x, y, width, heignt, TRUE);
}
void Button_::setText(const char str[]) {
	SetWindowText(this->hwnd, str);
}
char* Button_::getText() {
	DWORD dwTextLength;
	dwTextLength = GetWindowTextLength(this->hwnd);
	LPSTR pszText;
	pszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
	GetWindowText(this->hwnd, pszText, dwTextLength + 1);
	return (char*)pszText;
}

class ComboBox_ {
public:
	HWND hwnd;
	unsigned int id;
	HWND hwnd_parent;
	void create(unsigned int Handle, HWND hparent);
	void setLocation(int x, int y, int width, int heignt);
	void add(const char str[]);
	char* getText(int size);
	int getindex();
	void removeItem(int index);
	void insertItem(int index, const char str[]);
	void setItemText(int index, const char str[]);
	char* getItemText(int index, int size);
	void clean();
	int getCount();

	//char* getText_s();
};
void ComboBox_::create(unsigned int Handle, HWND hparent) {
	hwnd_parent = hparent;
	id = Handle;
	hwnd = CreateWindow("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | WS_VSCROLL|CBS_HASSTRINGS,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
	ShowWindow(hwnd, SW_SHOW);
	SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
}
void ComboBox_::setLocation(int x, int y, int width, int heignt) {
	MoveWindow(GetDlgItem(hwnd_parent, this->id), x, y, width, heignt, TRUE);
}
void ComboBox_::add(const char str[]) {
	SendMessage(this->hwnd, CB_ADDSTRING, 0, (LPARAM)str);
}
char* ComboBox_::getText(int size) {
	if (size <= 0)return (CHAR*)"";
	int lbItem = (int)SendMessage(this->hwnd, CB_GETCURSEL, 0, 0);
	char* str = new char[size];

	if (lbItem != -1)
		SendMessage(this->hwnd, CB_GETLBTEXT, lbItem, (LPARAM)str);
	else strcpy(str, "");
	return str;
}
int ComboBox_::getindex() {
	int lbItem = (int)SendMessage(this->hwnd, CB_GETCURSEL, 0, 0);
	return lbItem;
}
char* ComboBox_::getItemText(int index, int size) {
	if (size <= 0)return (CHAR*)"";
	char* str = new char[size];

	if (index != -1)
		SendMessage(this->hwnd, CB_GETLBTEXT, index, (LPARAM)str);
	else strcpy(str, "");
	return str;
}
void ComboBox_::removeItem(int index) {
	SendMessage(hwnd, CB_DELETESTRING, index, 0);
}
void ComboBox_::insertItem(int index, const char str[]) {
	SendMessage(hwnd, CB_INSERTSTRING, index, (LPARAM)str);
}
void ComboBox_::setItemText(int index, const char str[]) {
	this->removeItem(index);
	this->insertItem(index, str);
}
void ComboBox_::clean() {
	SendMessage(this->hwnd, CB_RESETCONTENT, 0, 0);
}
int ComboBox_::getCount() {
	return (int)SendMessage(hwnd, CB_GETCOUNT, 0, 0);
}


class ComboBoxList_ : public ComboBox_ {
public:
	void create(unsigned int Handle, HWND hparent) {
		hwnd_parent = hparent;
		id = Handle;
		hwnd = CreateWindow("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL | CBS_HASSTRINGS,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hparent, (HMENU)Handle, GetModuleHandle(NULL), NULL);
		ShowWindow(hwnd, SW_SHOW);
		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	}
};

class Label_ {
public:
	
	HWND hwnd;
	unsigned int id;
	HWND hwnd_parent;
	void create(const char captain[], unsigned int Handle, HWND hparent) {
		hwnd_parent = hparent;
		id = Handle;
		hwnd=CreateWindow(
			"STATIC",			
			captain,		
			WS_CHILD  | WS_VISIBLE  |  SS_LEFT ,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT ,
			hparent,		 
			(HMENU)Handle,	 
			GetModuleHandle(NULL),		
			NULL);
		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	}
	void setLocation(int x, int y, int width, int heignt) {
		MoveWindow(GetDlgItem(hwnd_parent, this->id), x, y, width, heignt, TRUE);
	}
	void setText(const char str[]);
	char* getText();
};
void Label_::setText(const char str[]) {
	SetWindowText(this->hwnd, str);
}
char* Label_::getText() {
	DWORD dwTextLength;
	dwTextLength = GetWindowTextLength(this->hwnd);
	LPSTR pszText;
	pszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
	GetWindowText(this->hwnd, pszText, dwTextLength + 1);
	return (char*)pszText;
}

class BorderLabel_ : public Label_{
	void create(const char captain[], unsigned int Handle, HWND hparent) {
		hwnd_parent = hparent;
		id = Handle;
		hwnd = CreateWindow(
			"STATIC",			
			captain,		
			WS_CHILD  | WS_VISIBLE  | WS_BORDER |  SS_LEFT ,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			hparent,		 
			(HMENU)Handle,	 
			GetModuleHandle(NULL),		
			NULL);
		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	}
};

class CenterLabel_ :public Label_ {
	void create(const char captain[], unsigned int Handle, HWND hparent) {
		hwnd_parent = hparent;
		id = Handle;
		hwnd = CreateWindow(
			"STATIC",			
			captain,		
			WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE ,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			hparent,		 
			(HMENU)Handle,	 
			GetModuleHandle(NULL),		 
			NULL);
		SendDlgItemMessage(hparent, Handle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	}
};

/*第二期*****************************************************************/
class Topmenu_ {
public:
	HMENU h_menu = CreateMenu();
	void show(HWND hparent);
};
void Topmenu_::show(HWND hparent) {
	SetMenu(hparent, this->h_menu);
}

class childMenu_ {
public:
	HMENU h_menu = CreateMenu();
	void create(HMENU parent,const char* str);
	void addItem(unsigned int Command, const char* str);

};
void childMenu_::create(HMENU parent, const char* str) {
	AppendMenu(parent, MF_POPUP, (UINT)h_menu, str);
}
void childMenu_::addItem(unsigned int Command, const char* str) {
	AppendMenu(this->h_menu, MF_STRING, Command, str);
}

class RtMenu_ {
public:
	HMENU h_menu= CreatePopupMenu();
	void addItem(unsigned int Command, const char* str);
	void showRectMenu(HWND h_parent, LPARAM lParam);
};
void RtMenu_::addItem(unsigned int Command, const char* str) {
	AppendMenu(this->h_menu, MF_STRING, Command, str);
}
void RtMenu_::showRectMenu(HWND h_parent, LPARAM lParam) {
	RECT rect;
	GetWindowRect(h_parent, &rect);
	TrackPopupMenu(this->h_menu, TPM_RIGHTBUTTON, LOWORD(lParam), HIWORD(lParam), 0, h_parent, &rect);
}

char* get_Win_Text(HWND hwnd) {
	DWORD dwTextLength;
	dwTextLength = GetWindowTextLength(hwnd);
	LPSTR pszText;
	pszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
	GetWindowText(hwnd, pszText, dwTextLength + 1);
	return (char*)pszText;
}
bool set_Win_Text(HWND hwnd,const char str[]) {
	return SetWindowText(hwnd, str);
}


/*
第一期 窗体、五个基本控件
第二期 菜单
第三期 对话框、滚动条、两个基本命令、可编辑控件disable功能
第四期 富文本框 
第五期 自定义（未定）
暂时搁置的项目
class str_char{
public:
	char value[256]="";
};
class volume {
public:
	int type;
	int data_int[256];
	str_char data_str[256];


};
class table_text : public Text_ {
public:

};




char* ComboBox_::getText_s() {

	int lbItem = (int)SendMessage(this->hwnd, CB_GETCURSEL, 0, 0);
	char* str ;
	str = (CHAR*)"";

	//if (lbItem != -1)
		SendMessage(this->hwnd, CB_GETLBTEXT, lbItem, (LPARAM)str);
	//else strcpy(str, "");
	return str;
}



class Dialogue_ {
	HWND hwnd; 
MSG msg; 
HINSTANCE his;
void create(HINSTANCE hInstance, LPCTSTR lpTemplate, HWND hWndParent, DLGPROC lpDialogFunc) {

	hwnd = CreateDialog(hInstance, lpTemplate, hWndParent, lpDialogFunc);
	ShowWindow(hwnd, );
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

};

void setReadOnly_(unsigned int id,HWND hparent){
	SendDlgItemMessage(hparent, id, EM_SETREADONLY, 0, 0);
}
void cancleReadOnly_(HWND hwnd) {
	SendMessage(hwnd, EM_SETREADONLY, 1, 0);
}
*/