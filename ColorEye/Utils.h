#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>

namespace Utils
{
    static bool CopyStringToClipboard(const std::string& str) {
        if (!OpenClipboard(NULL)) {
            std::cerr << "Failed to open clipboard." << std::endl;
            return false;
        }

        // Empty the clipboard
        EmptyClipboard();

        // Allocate global memory for the string
        HGLOBAL hClipboardData = GlobalAlloc(GMEM_MOVEABLE, str.size() + 1);
        if (!hClipboardData) {
            CloseClipboard();
            return false;
        }

        // Lock the memory and copy the string into it
        char* pBuffer = static_cast<char*>(GlobalLock(hClipboardData));
        if (!pBuffer) {
            GlobalFree(hClipboardData);
            CloseClipboard();
            return false;
        }
        memcpy(pBuffer, str.c_str(), str.size() + 1);
        GlobalUnlock(hClipboardData);

        // Set the clipboard data
        if (!SetClipboardData(CF_TEXT, hClipboardData)) {
            GlobalFree(hClipboardData);
            CloseClipboard();
            return false;
        }

        // Close the clipboard
        CloseClipboard();

        return true;
    }
}