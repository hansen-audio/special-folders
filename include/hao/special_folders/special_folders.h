// Copyright(c) 2017 René Hansen.

#pragma once

#include <string>

namespace hao::special_folders {

//------------------------------------------------------------------------
// https://learn.microsoft.com/en-us/windows/win32/shell/knownfolderid
//-----------------------------------------------------------------------------
using FolderType = std::string;

//! Win32: <user>/AppData/Roaming/
//! Linux: /home/<user>/
FolderType get_user_application_data_folder();

//! Win: get_user_application_data_folder
//! Linux: get_user_application_data_folder
//! Mac: ~/Library/Preferences
FolderType get_preferences_folder();

//! Program Files/
//! plug-in.vst3/Content/
FolderType get_application_data_folder();

enum class Domain
{
	kUser,	// For current user only
	kLocal	// For all users
};

FolderType get_application_data(const Domain& domain);

//-----------------------------------------------------------------------------
} // namespace hao::special_folders
