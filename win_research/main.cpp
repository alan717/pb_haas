


#include <Windows.h>
#include <iostream>


int main() {

	
	return 0;
}

void spt() {

	int rtCode = MessageBox(NULL,
		(LPCWSTR)L"�ڴ��ַԽ��,�����Ѿ�����ֹ!",
		(LPCWSTR)L"��������˴���",
		MB_ICONEXCLAMATION | MB_OK);
	std::cout << rtCode << std::endl;
	switch (rtCode) {
	case 1:
		std::cout << "ѡ����ȷ����ť!" << std::endl;
		break;
	case 2:
		std::cout << "ѡ����ȡ����ť!" << std::endl;
		break;
	default:
		std::cout << "��������!" << std::endl;
	}

}