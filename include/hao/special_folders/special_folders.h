// Copyright(c) 2017 René Hansen.

#pragma once

#include <string>

namespace hao::special_folders {

//-----------------------------------------------------------------------------
using FolderType = std::string;

//! Win32: <user>/AppData/Roaming
//! Linux: /home/<user>
//! macOS: ~/Library/Preferences
auto get_preferences_folder() -> FolderType;

enum class Domain
{
    kUser, // For current user only
    kLocal // For all users
};

//! Win32 (User) : C:\Program Files
//! Win32 (Local): C:\ProgramData
//! Linux (User) : /home/<user>
//! Linux (Local): /home/<user>
//! macOS (User) : ~/Library/Application Support
//! macOS (Local): /Library/Application Support
auto get_application_data_folder(const Domain& domain) -> FolderType;

//-----------------------------------------------------------------------------
} // namespace hao::special_folders
