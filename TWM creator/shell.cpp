#include "SFML/Graphics.hpp"
#include <iostream>
#include <map>
#include <string>
#include <windows.h>
#include <shlobj.h>
#include <string>


void shell(std::string &pathUser){
    //std::system("data\\diskChek.bat");
  
    BROWSEINFO bi = { 0 };
    bi.lpszTitle = L"choose a folder:";
    bi.ulFlags = BIF_EDITBOX | BIF_NEWDIALOGSTYLE; // Использовать стандартный стиль проводника

    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

    if (pidl != NULL) {
        TCHAR path[MAX_PATH];
        SHGetPathFromIDList(pidl, path);

        // Путь к выбранной папке находится в переменной 'path'
        MessageBox(NULL, path, L"selected folder", MB_OK | MB_ICONINFORMATION);
     

        // Освобождаем ресурсы
        IMalloc* imalloc = 0;
        if (SUCCEEDED(SHGetMalloc(&imalloc))) {
            imalloc->Free(pidl);
            imalloc->Release();
        }
        std::wstring widePath(path);
        std::string stringPath(widePath.begin(), widePath.end());
        pathUser = stringPath;
    }
    else {
        MessageBox(NULL, L"folder selection canceled", L"cancel", MB_OK | MB_ICONEXCLAMATION);
    }

   
}



