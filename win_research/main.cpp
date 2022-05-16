


#include <Windows.h>
#include <iostream>


int main() {

	
	return 0;
}

void spt() {

	int rtCode = MessageBox(NULL,
		(LPCWSTR)L"内存地址越界,程序已经被终止!",
		(LPCWSTR)L"程序出现了错误",
		MB_ICONEXCLAMATION | MB_OK);
	std::cout << rtCode << std::endl;
	switch (rtCode) {
	case 1:
		std::cout << "选择了确定按钮!" << std::endl;
		break;
	case 2:
		std::cout << "选择了取消按钮!" << std::endl;
		break;
	default:
		std::cout << "其他操作!" << std::endl;
	}

}