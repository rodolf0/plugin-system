#include <stdio.h>
#include <dlfcn.h> // Need this for dl functions

int main() {

    char *(*entry)();  // Pointer to function from Plugin
    void * module;     // Pointer to Plugin
    
    // load the module (plugin.so), and resolve symbols now
    module = dlopen( "./plugin.so", RTLD_NOW );
    if(!module)  {
        fprintf(stderr, "[error]: dlopen() failed while resolving symbols.\n" );
        return -1;
    }

    // retrieve address of entry point (the plugin function - function())
    entry = (char*(*)())dlsym(module, "function");
    if( entry == NULL ) {
        dlclose(module);
        fprintf(stderr, "[error]: dlerror() failed while  retrieving address.\n" ); 
        return -1;
    }

    // Call Plugin function
    entry();

    return 0;
}
