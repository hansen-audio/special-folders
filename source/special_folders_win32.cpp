// Copyright(c) 2017 René Hansen.

#include "hao/special_folders/special_folders.h"
#include <shlobj.h>
#include <stdexcept>

#if _WIN32_WINNT < _WIN32_WINNT_VISTA
#error "Only Win Vista or higher"
#endif

namespace hao::special_folders {

//------------------------------------------------------------------------
static std::string convert(const std::wstring& wide_string)
{
    if (wide_string.empty())
    {
        return "";
    }

    const auto size_needed = WideCharToMultiByte(CP_UTF8, 0, &wide_string.at(0),
                                                 (int)wide_string.size(),
                                                 nullptr, 0, nullptr, nullptr);
    if (size_needed <= 0)
    {
        throw std::runtime_error("WideCharToMultiByte() failed: " +
                                 std::to_string(size_needed));
    }

    std::string result(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wide_string.at(0), (int)wide_string.size(),
                        &result.at(0), size_needed, nullptr, nullptr);
    return result;
}

//------------------------------------------------------------------------
FolderType get_known_folder(const GUID folder_id)
{
    LPWSTR wsz_path = NULL;
    HRESULT result =
        SHGetKnownFolderPath(folder_id, KF_FLAG_CREATE, NULL, &wsz_path);

    if (SUCCEEDED(result))
    {
        std::wstring tmp(wsz_path);
        CoTaskMemFree(wsz_path);
        return convert(tmp);
    }

    return {};
}

//------------------------------------------------------------------------
FolderType get_user_application_data_folder()
{
    return get_known_folder(FOLDERID_RoamingAppData);
}

//------------------------------------------------------------------------
FolderType get_application_data_folder()
{
    return get_known_folder(FOLDERID_ProgramFiles);
}

//------------------------------------------------------------------------
FolderType get_preferences_folder()
{
    return get_user_application_data_folder();
}

//------------------------------------------------------------------------
FolderType get_application_data(const Domain& domain)
{
    switch (domain)
    {
        case Domain::kUser:
            return get_known_folder(FOLDERID_ProgramFiles);
        case Domain::kLocal:
            return get_known_folder(FOLDERID_ProgramData);
        default:
            break;
    }

    return {};
}

//------------------------------------------------------------------------
} // namespace hao::special_folders
