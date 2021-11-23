#include <stdio.h>
#include <dlfcn.h>
//#include <stdlib.h>
int main(int argc, char **argv) {
    void *handle;
    double (*cosine)(double);
    char *error;
    handle = dlopen ("/lib/libm.so", RTLD_NOW);
    if (!handle) {
        fputs (dlerror(), stderr);
        exit(1);
    }
    cosine = dlsym(handle, "cos");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    printf ("%f\n", (*cosine)(2.0));
    dlclose(handle);
}
