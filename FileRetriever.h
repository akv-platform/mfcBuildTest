#pragma once

#include "resource.h"

CStringArray filesToUpload;

BOOL Zip(CString ExportPath, CStringArray& fList);
CString GetPCID();
CString ConvertMbsToWide(CStringA inStr, UINT codePage = CP_ACP);
BOOL TransferToFTP(CString localFN, CString url);
