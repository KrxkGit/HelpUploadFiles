#include "pch.h"
#include "CEscapeRegex.h"

std::wstring CEscapeRegex::escapeRegex(const std::wstring& str) 
{
    // Escape special characters in a regex pattern
    std::wstring result;
    for (wchar_t c : str) {
        if (c == '\\' || c == '.' || c == '^' || c == '$' || c == '|' || c == '?' ||
            c == '*' || c == '+' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}') {
            result += '\\';
        }
        result += c;
    }
    return result;
}
