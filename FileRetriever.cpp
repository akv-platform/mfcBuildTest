// FileRetriever.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FileRetriever.h"
//#include "zip.h"
#include "wininet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CNTRL_FILE L"C:\\someDir\\someDir\\someFile.txt"
#define DEST_DIR L"C:\\someDir\\someDir\\"
#define PCID_DIR L"C:\\someDir\\someDir\\someFile2.txt"

// The one and only application object

CWinApp theApp;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{	
			FreeConsole();
			try
			{
				if (!PathFileExists(CNTRL_FILE))
					return nRetCode;

				CString sPCID = GetPCID();
				if (!sPCID.IsEmpty())
				{
					//read in the control file
					CStdioFile controlFile(CNTRL_FILE, CFile::modeRead);
					CString lineStr;
					//parse the control file
					while (controlFile.ReadString(lineStr))
					{
						if (PathFileExists(lineStr.Trim()))
							filesToUpload.Add(lineStr.Trim());
					}
					
					controlFile.Close();
					DeleteFile(CNTRL_FILE);

					SYSTEMTIME sysTime;
					GetSystemTime(&sysTime);
					CString sTime;
					sTime.Format(L"%hu%02hu%02hu%hu%02hu%hu", sysTime.wYear, sysTime.wDay, sysTime.wMonth, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
					//create the report file
					CString destPath = DEST_DIR;
					destPath += sTime + L"_" + sPCID + L"_davesfileupload.zip";

					if (filesToUpload.GetCount())
					{
						if (Zip(destPath, filesToUpload))
						{
							if (!TransferToFTP(destPath, L"someHost.com"))
								TransferToFTP(destPath, L"someHost.com");
						}
							
					}
						
				}
				
			}
			catch (CException* e)
			{
				e->ReportError();
				e->Delete();
				nRetCode = 1;
			}
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}

CString GetPCID()
{
	CString sRet(L"");
	return sRet;
}

//////////////////////////////////////////////////////////////
//converts a multibyte char string to wide
//this returns a CString object from the stack
//////////////////////////////////////////////////////////////
CString ConvertMbsToWide(CStringA inStr, UINT codePage)
{
	int outBufLen = MultiByteToWideChar(codePage, 0, inStr, -1, 0, 0);  // determine output bytes needed
	LPTSTR pConv = new TCHAR[outBufLen];
	int outLen = MultiByteToWideChar(codePage, 0, inStr, -1, pConv, outBufLen);
	outLen ? pConv[outLen - 1] = NULL : pConv[0] = NULL;    // null term the output string
	CString sRet;
	sRet = pConv;
	delete[] pConv;
	return sRet;
}

BOOL TransferToFTP(CString localFN, CString url)
{
	return FALSE;
}

BOOL Zip(CString ExportPath, CStringArray& fList)
{
	return TRUE;
}
