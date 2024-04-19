#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include "stb_image/stb_image.h"
#include <GL/glew.h>

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

    inline void generateTexture(std::string imagePath, GLuint& texture)
    {
        int temp_size;
        int channels;
        unsigned char* my_image_data = stbi_load(imagePath.c_str(), &temp_size, &temp_size, &channels, 4);
        assert(my_image_data != NULL);

        // Turn the RGBA pixel data into an OpenGL texture:
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, temp_size, temp_size, 0, GL_RGBA, GL_UNSIGNED_BYTE, my_image_data);

        stbi_image_free(my_image_data);
    }
}