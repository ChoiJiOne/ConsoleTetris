#pragma once

#include "Common.h"

class StringUtil
{
public:
    /*
     * 코드 출처 : https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
     */
    template<typename ... Args>
    static inline std::string StringFormat(const std::string& format, Args ... _args)
    {
        size_t size = static_cast<size_t>(std::snprintf(nullptr, 0, format.c_str(), _args ...)) + 1;

        if (size <= 0)
        {
            throw std::runtime_error("Error during formatting.");
        }

        auto buffer = std::make_unique<char[]>(size);
        std::snprintf(buffer.get(), size, format.c_str(), _args ...);

        return std::string(buffer.get(), buffer.get() + size - 1);
    }

    /*
     * 코드 출처 : https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
     */
    static inline std::wstring ConvertUTF8ToUTF16(const std::string& utf8String)
    {
        static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(utf8String);
    }

    /*
     * 코드 출처 : https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
     */
    static inline std::string ConvertUTF16ToUTF8(const std::wstring& utf16String)
    {
        static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.to_bytes(utf16String);
    }
};