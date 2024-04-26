// Copyright(c) 2017 René Hansen.

#include "ha/platform/special_folders.h"
#include "ha/platform/string_convert.h"
#include <shlobj.h>

#if _WIN32_WINNT < _WIN32_WINNT_VISTA
#error "Only Win Vista or higher"
#endif

namespace hao::special_folders {

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
        return StringUtils::Convert::convert(tmp);
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
} // namespace hao::special_folders
