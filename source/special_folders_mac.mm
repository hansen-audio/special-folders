// Copyright(c) 2017 René Hansen.

#import "ha/platform/special_folders.h"
#import "ha/platform/binary.h"
#import <Cocoa/Cocoa.h>
#import <CoreFoundation/CoreFoundation.h>
#import <string>

extern void* moduleHandle;
extern CFBundleRef ghInst;

namespace hao::special_folders {
    
//------------------------------------------------------------------------
FolderType getUserApplicationDataFolder()
{
   	NSURL* url = [[NSFileManager defaultManager] URLForDirectory:NSApplicationSupportDirectory
                                                               inDomain:NSUserDomainMask
                                                      appropriateForURL:nil
                                                                 create:NO
                                                                  error:nil];
    
    FolderType url_str {[url.path UTF8String]};
    return url_str;
}

//------------------------------------------------------------------------
FolderType getPreferencesFolder()
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
static size_t findSecondToLastSlash (const FolderType& binary_path)
{
    auto pos = binary_path.find_last_of("/");
    pos = binary_path.find_last_of("/", pos - 1);
    return pos;
}
    
//------------------------------------------------------------------------
static FolderType getBundleContentsDir (const FolderType& binary_path)
{
    FolderType contentsPath = binary_path.substr(0, findSecondToLastSlash(binary_path));
    return contentsPath;
}
    
//------------------------------------------------------------------------
FolderType getApplicationDataFolder()
{
    auto binarybinary_pathPath = Platform::getBinaryFilePath();
    auto contents_path = getBundleContentsDir(binary_path);
    auto resources_path = contents_path + FolderType{"/Resources"};
    
    return resources_path;
}

//------------------------------------------------------------------------
} // namespace SpecialFolders
