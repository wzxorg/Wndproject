#include "func.h"

window_ win1;
window_ win2;
//control_1 c1;
Text_ t1;
ListBox_ l1;
Button_ b1;
Button_ b2;
ComboBox_ c1;
SimpleText_ t2;
Button_ b3;
Label_ la1;
Button_ b4;
Button_ b5;
Button_ b6;
Button_ b7;
Topmenu_ m1;
childMenu_ cm[4];
RtMenu_ rtm1;
childMenu_ rtm2;
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	//以上两行为WM_PAINT做准备

	switch (Message) {

		/* Upon destruction, tell the main thread to stop 一旦破坏，告诉主线停止 */
	case WM_DESTROY: {
		
			PostQuitMessage(0);
		
		break;
	}
	case WM_SIZE: { //必须放在  case WM_CREATE 的前面
		if (wParam != SIZE_MINIMIZED) {

			//TODO:MoveWindow等函数放在这。
			t1.Setlocation(0, 0, LOWORD(lParam), 50);

			l1.Setlocation(0, 51, LOWORD(lParam), 70);
			b1.setLocation(0, 121, 40, 30);
			b2.setLocation(50, 121, 40, 30);
			c1.setLocation(0, 161, 120, 90);
			t2.Setlocation(150, 161, 120, 20);
			b3.setLocation(300, 161, 100, 30);
			b4.setLocation(410, 161, 100, 30);
			la1.setLocation(0, 260, 300, 90);
			b5.setLocation(515, 161, 60, 30);
			b6.setLocation(580, 161, 60, 30);
			b7.setLocation(150,192,120,30);
			cout << endl<<"SIZED   "<< t1.id<<"   "<<t1.hwnd << endl;
			cout << endl << "SIZED  l1 " << l1.id << "   " << l1.hwnd << endl;

		}
		break;
	}
	case WM_CREATE: {//创建窗口时响应
		if (hwnd==win1.hwnd)alert("hwnd","");
		else alert("!hwnd","");
		t2.create("",1006,hwnd);
		l1.create(1003, hwnd);
		t1.create("TEXT", 1001, hwnd);
		b1.create("Button", 1002, hwnd);
		b2.create("clean",1004,hwnd);
		c1.create(1005, hwnd);
		b3.create("Add", 1007, hwnd);
		la1.create("123", 1008, hwnd);
		b4.create("remove", 1009, hwnd);
		b5.create("Change",1010,hwnd);
		b6.create("Apply", 1011, hwnd);
		b7.create("Count", 1012, hwnd);
		cout << endl << "Created   " << t1.id << "   " << t1.hwnd_parent << endl;
		cout << "Parent:   "<< win1.hwnd <<endl;
		
		cout << endl << "Created  l1 " << l1.id << "   " << l1.hwnd_parent << endl;
		cout << "Parent:   " << win1.hwnd << endl;

		//menu
		cm[0].create(m1.h_menu, "a");
		cm[0].addItem(2001, "b");
		cm[1].create(cm[0].h_menu, "c");
		cm[1].addItem(2002, "ca");
		m1.show(hwnd);

		rtm1.addItem(4001, "a");
		rtm2.create(rtm1.h_menu, "b");
		rtm2.addItem(4002, "ba");

		cm[3].create(m1.h_menu, "edit");
		cm[3].addItem(5001,"Disable");
		cm[3].addItem(5002, "Enable");
		if (win1.confirm("ok?","")) {
			win1.alert("YES", "");
			
			//c1.create(hwnd);
		}
		else {
			win1.alert("NO", "");
		
		}
		
		cout << t1.id <<"     "<< t1.hwnd_parent << endl;
		break;
		
	}
	case WM_CONTEXTMENU:		//右击屏幕时，弹出菜单
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		//TrackPopupMenu(g_hRKeyMenu, TPM_RIGHTBUTTON, LOWORD(lParam), HIWORD(lParam), 0, hwnd, &rect);

		rtm1.showRectMenu(hwnd, lParam);
		break;

	}
	case WM_PAINT: {
		hdc = BeginPaint(hwnd, &ps);
		hdc = GetDC(hwnd);

		//TODO:在此放置代码


		EndPaint(hwnd, &ps);
		ReleaseDC(hwnd, hdc);
		break;
	}
	case WM_COMMAND: {//相应事件，所有的按钮响应全在这。
		switch (wParam)
		{
			//list an example
			case 1001:{

				break;
			}
			case 1003: {
				t1.set_text(l1.getItemText(l1.getindex(),MAX_STRING_SIZE));
				win1.alert("clicked","");
				break;
			}
			case 1002: {
				t1.set_text(l1.getItemText(l1.getindex(), MAX_STRING_SIZE));
				break;
			}
			case 1004: {
				l1.clean();
				c1.clean();
				break;
			}
			case 1007: {
				c1.add(t2.get_str());
				break;
			}
			case 1009: {
				c1.removeItem(c1.getindex());
				break;
			}
			case 1010: {
				c1.setItemText(c1.getindex(), t2.get_str());
				break;
			}
			case 1011: {
				t1.set_text(c1.getText(MAX_STRING_SIZE));
				win1.alert(c1.getItemText(c1.getindex(),MAX_STRING_SIZE),"");
				win1.alert(la1.getText(), "");
				win1.alert(get_Win_Text(c1.hwnd),"");
				break;
			}
			case 1012:{
				cout << endl << c1.getCount() << "  " <<l1.getCount()<< endl;
				break;
			}
			case 2001: {
				win1.alert("b", "");
				break;
			}
			case 2002: {
				win1.alert("ca", "");
				break;
			}
			case 4001: {
				win1.alert("a","");
				break;
			}
			case 5001: {
				//setReadOnly_(t1.id,hwnd);
				alert("","");
				break;
			}
			case 5002: {
				//cancleReadOnly_(t1.hwnd);
				break;
			}
			default: {

				break;
			}
		}
		break;
	}
	case WM_KEYDOWN: {//响应键盘按下
		if (win1.confirm("ok?", "")) {
			win1.alert("YES", "");
			char str1[]="Form1";
			win1.set_text(str1);
			t1.set_text("text1");
			cout << t1.get_str();
			l1.add("dffghfghfghghhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh");
			//SendMessage(l1.hwnd, LB_ADDSTRING, (LPARAM)"123123", (LPARAM)"123123");
			//cout << (CHAR)(LPARAM)"123123";
			cout << l1.getindex()<<l1.getText(MAX_STRING_SIZE);
			
		}
		else {
			win1.alert("NO", "");
			
			l1.setItemText(l1.getindex(),"123");
			
		}
		
		
		break;
	}
	case WM_CLOSE: {
		if(!win1.confirm("确认退出？", ""))return 0;
		else return DefWindowProc(hwnd, Message, wParam, lParam);
		break;
	}
					 /* All other messages (a lot of them) are processed using default procedures 所有其他消息（很多）都是使用默认过程处理的*/
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	cout << hInstance << endl << win1.hwnd << endl << win2.hwnd << "This program will create a window.";

	win1.histance_(hInstance);
	win1.callback_(WndProc);
	win1.create_wind(700,480);
	
	cout << hInstance << endl << win1.hwnd << endl << win2.hwnd;
	
	char* abc = gfn1();
	
	cout << abc<<endl;
	if (abc != "\0") {
		system (abc);
	}
		
	system("pause");
	return 0;
	

}
/*
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	win1.histance_(hInstance);
	win1.callback_(WndProc);
	win1.create_wind();
	char* abc = gfn1();
	cout << abc << endl;
	system(abc);
	system("pause");
	return 0;
}*/