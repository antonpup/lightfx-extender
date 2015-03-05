#ifndef LFXE_EXPORTS
#define LFXE_EXPORTS
#endif

#include "FileIO.h"

// Windows includes
#include "../Common/Windows.h"
#include <Windows.h>
#include <ShlObj.h>


#define STORAGEFOLDER L"LightFX Extender"

using namespace std;

namespace lightfx {
    namespace utils {

        LFXE_API bool DirExists(const wstring& path) {
            DWORD fileType = GetFileAttributesW(path.c_str());
            if (fileType == INVALID_FILE_ATTRIBUTES) {
                return false;
            } else if (fileType & FILE_ATTRIBUTE_DIRECTORY) {
                return true;
            }
            return false;
        }

        LFXE_API bool FileExists(const wstring& path) {
            DWORD fileType = GetFileAttributesW(path.c_str());
            return fileType != INVALID_FILE_ATTRIBUTES;
        }

        LFXE_API wstring GetDataStorageFolder() {
            wstring path = L"";
            wchar_t* appData = nullptr;
            if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &appData))) {
                path = wstring(appData);
            }
            CoTaskMemFree(appData);

            if (!path.empty()) {
                return path + L"/" + STORAGEFOLDER;
            } else {
                return L"";
            }
        }

    }
}