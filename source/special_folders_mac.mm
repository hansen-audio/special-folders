// Copyright(c) 2017 René Hansen.

#import "hao/special_folders/special_folders.h"
#import <Cocoa/Cocoa.h>
#import <CoreFoundation/CoreFoundation.h>
#import <string>
#import <dlfcn.h>

extern void* moduleHandle;
extern CFBundleRef ghInst;

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

//------------------------------------------------------------------------
static size_t findSecondToLastSlash (const FolderType& binary_path)
{
    auto pos = binary_path.find_last_of("/");
    pos = binary_path.find_last_of("/", pos - 1);
    return pos;
}
    
//------------------------------------------------------------------------
static FolderType get_bundle_contents_dir (const FolderType& binary_path)
{
    FolderType contentsPath = binary_path.substr(0, findSecondToLastSlash(binary_path));
    return contentsPath;
}
    
//------------------------------------------------------------------------
static FolderType get_bundle_resources()
{
    auto binary_path = get_binary_file_path();
    auto contents_path = get_bundle_contents_dir(binary_path);
    auto resources_path = contents_path + FolderType{"/Resources"};
    
    return resources_path;
}

//------------------------------------------------------------------------
// public interface
//------------------------------------------------------------------------
FolderType get_preferences_folder()
{
    NSURL* url = [[NSFileManager defaultManager] URLForDirectory:NSLibraryDirectory
                                                        inDomain:NSUserDomainMask
                                               appropriateForURL:nil
                                                          create:NO
                                                           error:nil];
    
    FolderType url_str {[url.path UTF8String]};
    url_str += "/Preferences";
    return url_str;
}

//------------------------------------------------------------------------
FolderType get_application_data_folder(const Domain& domain)
{
    switch (domain)
    {
        case Domain::kUser:
        {
            NSURL* url = [[NSFileManager defaultManager] URLForDirectory:NSApplicationSupportDirectory
                                                                inDomain:NSUserDomainMask
                                                       appropriateForURL:nil
                                                                  create:NO
                                                                   error:nil];
            
            FolderType url_str {[url.path UTF8String]};
            return url_str;
        }
        case Domain::kLocal:
        {
            NSURL* url = [[NSFileManager defaultManager] URLForDirectory:NSApplicationSupportDirectory
                                                                inDomain:NSLocalDomainMask
                                                       appropriateForURL:nil
                                                                  create:NO
                                                                   error:nil];
            
            FolderType url_str {[url.path UTF8String]};
            return url_str;
        }
        default:
            break;
    }
}
//------------------------------------------------------------------------
} // namespace SpecialFolders
