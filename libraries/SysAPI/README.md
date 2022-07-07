# SysAPI

## Overview

The `SysAPI` library has a few classes used for system integration.

## System

The `System` class has only `static` methods used for:

- getting the operating system name
- getting the processor name
- getting a path for user data storage

## Command Line Interface

The `Cli` class is used for parsing command-line arguments.

```cpp
#include <sys.hpp>

int main(int argc, char * argv[]){
  Cli cli(argc, argv);
  if( cli.get_option("test") == "true" ){
    //do the test
  }
  return 0;
}
```

The `Cli` class expects arguments to be of the form `--<switch>[=<value>]`. If just `--<switch>` is used
then `cli.get_option("<switch">) == "true"` is true. If the `<switch>` is not
present, `cli.get_option("<switch>").is_empty()` is true.

You can also use `const auto action = cli.get_option("action")` where if `--action=program` is passed as a command line
argument, `action == "program"` is true.

## Version

The `Version` class manages semantic version values. It converts between BCD versions and string versions as well as
compares versions.

```cpp
#include <sys.hpp>

Version str_version("1.0");
const auto bcd_version = Version::from_u16(0x0100);

if(str_version == bcd_version){
  //this is true
}
```
