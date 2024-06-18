// Copyright(c) 2017 René Hansen.

#include "hao/special_folders/special_folders.h"
#include <iostream>

using namespace hao::special_folders;
using namespace std;

int main()
{
    cout << "Preferences   : " << get_preferences_folder() << endl;
    cout << "AppData(User) : " << get_application_data_folder(Domain::kUser) << endl;
    cout << "AppData(Local): " << get_application_data_folder(Domain::kLocal) << endl;

    return 0;
}