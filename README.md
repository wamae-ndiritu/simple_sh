# Simple Shell.

## 9. setenv & unsetenv

Trying to implement a custom function _setenv and _unsetenv has encountered a number of issues. Firstly, we need to check whether the environment variable being set exist in the environment variables. This was quite easier, since we can go through all the variables and see whether there is one that matches the one we want to set. If the variable exist, the function should update it.

If else the variable does not exist, the the function should add it to the variables. To access these environment variables we use **environ** which is an `extern variable` in the C Library.

Modifying `environ` directly may have unexpected behavior or be non-portable in some programming environments. It's generally better to use platform-specific functions or libraries for managing environment variables. This is the issue that result to our program having `Invalid read and write buffers`. And if the environ was modified, then we would have unexpected characters being printed as the set variable whenever we print the variables after calling `_setenv()`.

### Unexpected string as the set variable
![_setenv_error](https://drive.google.com/file/d/1PxjXjBNxwKtXJ8-nrijcBz5Kcj4N5zs9/view?usp=sharing)

### The custom _setenv & _unsetenv usage

`setenv VARIABLE_NAME VARIABLE_VALUE` || `unsetenv VARRIABLE_NAME`

Whenever the first argument passed on the program arguments is `setenv` || `unsetenv` then the functions _setenv() and _unsetenv are called respectively with the rest of the arguments. 

 
