#include <dirent.h>
#include <stdio.h>
#include <unistd.h> 
#include <limits.h>
#include <stdlib.h> 

// gcc -o test_rootkit.elf ./bin/test_rootkit.c



void printCWD() {

    /*
    If the call to getcwd(NULL, 0) is successful, it returns a pointer to a dynamically allocated buffer that contains the current working directory path. You are responsible for freeing this memory using free() when you're done with it.

    If the call fails, it returns NULL, and an error code is set in errno to indicate the reason for the failure.
    
    */
    char *cwd  = getcwd(NULL, 0);

    if(cwd == NULL){
        perror("cannot printCWD ");
    } 

    printf("%s\n", cwd);

    free(cwd);

}

int main() { 
    DIR *dir; 
    struct dirent  *entry ;

    dir = opendir(".");

    if(dir == NULL) {
        perror("opendir");
        
        return 1;
    }


    printCWD();

    printf("\ndir entries:\n----------\n");
    while((entry = readdir(dir)) != NULL){ 
        printf("%s\n", entry->d_name);
    }

    closedir(dir);

    return 1;
}



