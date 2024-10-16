#define _GNU_SOURCE
#include <dlfcn.h>
#include <dirent.h>
#include <string.h> 

const char *hidden_file = "malay_secret" ; 

// In this context, the asterisk before the function name readdir indicates that the function returns a pointer to a struct dirent.
struct dirent* readdir(DIR *dirp) {


}