// Resize_Images_To_Power_of_Two.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Magick++.h>
#include <windows.h>
#include <gdiplus.h>
#include <filesystem>

#pragma comment(lib, "gdiplus.lib")

unsigned int nextPowerOf2(unsigned int n)
{
    if (n == 0) return 1; // Handle 0 case
    n--; // Handle cases where n is already a power of 2
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16; // For 32-bit integers
    // For 64-bit integers, add more shifts (n |= n >> 32;)
    n++;
    return n;
}

bool isPowerOfTwo(unsigned int n)
{
    // A power of two must be a positive number
    // And the bitwise AND with (n-1) should be 0
    return (n > 0) && ((n & (n - 1)) == 0);
}

void resize()
{
    std::cout << "Starting resizer" << std::endl;
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
    auto source_file_path =
        std::filesystem::path(R"(C:\Development\Git\MGS2-PS2-Textures\zz - resized_for_upscaling)");
    Magick::InitializeMagick(NULL);
    for (const auto& entry : std::filesystem::directory_iterator(source_file_path))
    {
        if (!entry.is_regular_file())
        {
            continue;
        }
        std::wstring filePath = entry.path().wstring();
        unsigned int newWidth = 0;
        unsigned int newHeight = 0;
        std::filesystem::path targetPath;
        Gdiplus::Bitmap bitmap(filePath.c_str());
        if (bitmap.GetLastStatus() != Gdiplus::Ok)
        {
            continue;
        }
        UINT width = bitmap.GetWidth();
        UINT height = bitmap.GetHeight();
        if (!isPowerOfTwo(width))
        {
            newWidth = nextPowerOf2(width);
        }
        if (!isPowerOfTwo(height))
        {
            newHeight = nextPowerOf2(height);
        }
        if (!newWidth && !newHeight)
        {
            continue;
        }
        Magick::Image image;
        std::cout << "Resizing image: " << entry.path().filename() << " | " << height << "x" << width << " -> " << (newWidth ? std::to_string(newWidth) : std::to_string(width)) << "x" << (newHeight ? std::to_string(newHeight) : std::to_string(height)) << std::endl;
        image.read(entry.path().string());
        Magick::Geometry NewGeo(newWidth ? newWidth : width, newHeight ? newHeight : height);
        NewGeo.aspect(true);
        //image.filterType(Magick::FilterType::HermiteFilter);
        image.resize(NewGeo);
        image.write((source_file_path / "resized" / entry.path().filename().replace_extension(".resized.png")).string());
    }
    Gdiplus::GdiplusShutdown(gdiplusToken);
    std::cout << "Resizer finished." << std::endl;
}


int main()
{
    resize();
}
