


### Instructions

We need to compile the hook into so file. then set the env varible of LD_PRELOAD
```bash 
gcc -fPIC -shared -o ./bin/hide_file.so hide_file.c -ldl

LD_PRELOAD=$PWD/bin/hide_file.so ls 
```

### Test it:

```bash
mkdir test ||  for i in a b c malay_secret ; do touch  test/$i; done;

ls test
```


### Explanation of How LD_PRELOAD Works
The LD_PRELOAD environment variable tells the dynamic linker to load the specified shared library before any other libraries.
When the ls command calls the readdir function, it will use your overridden version of the function from hide_file.so.
As a result, the file named malay_secret will be hidden when you list the directory contents.




When examining the ls source code, we can see the use of libc’s readdir function. ls reads the directory entries one by one using the readdir function inside a loop.

The readdir function returns a pointer to a dirent struct which contains information about the directory entry, such as the name. Once it returns NULL, it indicates the end of the directory. 