// Copyright(c) 2017 René Hansen.

#include "hao/special_folders/special_folders.h"
#include <iostream>

int main()
{
    const auto app_data_folder =
        hao::special_folders::get_application_data_folder();
    const auto prefs_folder = hao::special_folders::get_preferences_folder();
    const auto usr_app_data =
        hao::special_folders::get_user_application_data_folder();

    std::cout << app_data_folder << std::endl;
    std::cout << prefs_folder << std::endl;
    std::cout << usr_app_data << std::endl;
    std::cout << hao::special_folders::get_application_data(
                     hao::special_folders::Domain::kUser)
              << std::endl;
    std::cout << hao::special_folders::get_application_data(
                     hao::special_folders::Domain::kLocal)
              << std::endl;

    return 0;
}