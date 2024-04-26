// Copyright(c) 2017 René Hansen.

#include "dlfcn.h"
#include "hao/special_folders/special_folders.h"
#include <cassert>
#include <pwd.h>
#include <unistd.h>

namespace hao::special_folders {

//-----------------------------------------------------------------------------
static FolderType get_binary_file_path()
{
    FolderType binary_path;
    Dl_info info;
    if (dladdr((const void*)get_binary_file_path, &info) == 0)
        return binary_path;

    if (info.dli_fname == nullptr)
        return binary_path;

    binary_path.assign(info.dli_fname);
    return binary_path;
}

//-----------------------------------------------------------------------------
FolderType get_user_application_data_folder()
{
    struct passwd* pw = getpwuid(getuid());
    if (!pw)
        return {};

    const char* home_dir = pw->pw_dir;
    return {home_dir};
}

//------------------------------------------------------------------------
FolderType get_preferences_folder()
{
    return get_user_application_data_folder();
}

//------------------------------------------------------------------------
static size_t find_second_to_last_slash(const FolderType& binary_path)
{
    auto pos = binary_path.find_last_of("/");
    pos      = binary_path.find_last_of("/", pos - 1);
    return pos;
}

//------------------------------------------------------------------------
static FolderType get_bundle_contents_dir(const FolderType& binary_path)
{
    FolderType contents_path =
        binary_path.substr(0, find_second_to_last_slash(binary_path));
    return contents_path;
}

//------------------------------------------------------------------------
FolderType get_application_data_folder()
{
    auto binary_path   = get_binary_file_path();
    auto contents_path = get_bundle_contents_dir(binary_path);
    auto resourcesPath = contents_path + FolderType{"/Resources"};

    return resourcesPath;
}

//-----------------------------------------------------------------------------
} // namespace hao::special_folders
