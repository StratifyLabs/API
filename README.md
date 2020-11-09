# Stratify API

![Build](https://github.com/StratifyLabs/StratifyAPI/workflows/Build/badge.svg) [![Coverity](https://scan.coverity.com/projects/10992/badge.svg)](https://scan.coverity.com/projects/stratifylabs-stratifyapi) 

## Overview

- API Documentation
- Naming Conventions
- Building and Installing the Stratify API

If you want to write programs using the Stratify API, you should read through the naming conventions then dive into the API documentation. Also, please look at the Stratify OS programs that are published on Github as they make use of the API.

- [HelloWorld](https://github.com/StratifyLabs/HelloWorld)
- [gpiotool](https://github.com/StratifyLabs/gpiotool)
- [i2ctool](https://github.com/StratifyLabs/i2ctool)

## API Documenation

If you want to write applications using the Stratify API, please see the [API documentation](https://docs.stratifylabs.co/reference/StratifyAPI/api/).

## Naming Conventions

Stratify API uses the following naming conventions

### Classes and Namespaces

Classes use upper CamelCase with a strong preference for a single word. Namespaces use all lowercase letters and are preferably concise and a single word.

### File and Directory Names

File names follow the class names and namespace names with hpp appended to header files and cpp appended to C++ source files.  Namespaces have their own directories which contain the header files of all the classes in the namespace.  The namespaces include a header file named after the namespace which includes all classes and declares 'using namespace <namespace>'.
	
```c++
/*! \brief Standard Calculation and Software Routines
*
*/
namespace calc {}
#include "calc/Base64.hpp"
#include "calc/Ema.hpp"
#include "calc/Lookup.hpp"
#include "calc/Pid.hpp"
#include "calc/Rle.hpp"

using namespace calc;
```

In an application, #include <sapi/calc.hpp> will allow you to declare Pid objects without using calc::Pid.  If you don't want to use the namespace (that is you need to avoid scope conflicts), just #include <sapi/calc/Pid.hpp> instead.  All library headers (including those in Stratify API) should use this approach and should never include a namespace header (or 'using namespace') in any header file other than the namespace's hpp file. The application developer can then decide to include <sapi/calc.hpp> or the individual classes <sapi/calc/Pid.hpp>.

### Methods and Functions

Methods and functions follow traditional C and C++ naming styles with lowercase and underscores to separate words.  Methods and functions should start with a verb except when directly accessing a variable.

```c++
Class Object {
public:
  int amount() const { return m_amount; } //this just returns the amount (no calculating, no fetching)
  int set_amount(int v){ m_amount = v; } //this sets the value of amount
  int calculate_amount() const; //this is an action that does something
  int get_amount() const; //since this starts with a verb it needs to do something--like load amount from a file
private:
  int m_amount; //member variables have an m_ prefix
}
```

The above code uses `set_*` and `get_*` but not perhaps in the traditional way.  If `get_` is used, it implies the value is not immediately available and must be loaded from somewhere.  The convention used by the method `amount()` (no action word) is used if the value is immediately ready or ready with a trivial calculation such as

```c++
area(){ return m_width*m_height; }
```

#### References and Pointers

Parameters passed to methods and functions should be passed as references unless a pointer is more appropriate.  For example, if the item is a member of an array then a pointer would be appropriate. However, if the item will be operated on as a stand alone entity, a reference is preferred.  Also if the object uses only read-only methods, a const reference is best.

```c++
void copy_memory(const char * src, char * dest, int nbytes); //a pointer here is best because src points to the data
void print_string(const String & str); //this is better as a reference because we are just reading str
```
	
Pointers are also appropriate if `nullptr` is a valid value even if there is only one item.

### Variables and Member Variables

Variables are named the same way functions are except they don't start with an action verb.  Member variables have `m_` prefixed to the description variable name.  See the `amount()` and `m_amount` example above.

### Type Definitions

To maintain compatibility and interoperability with C (i.e. Stratify OS), type definitions are declared in `.h` files and follow C naming conventions.  Whenever typedef is used, `_t` should be appended to the type name like `size_t` or `pthread_t`.

### Enums and Macros

Macros are written in all caps with words separated by underscores. Enums are written in all lower case separated by underscores and prefixed the the singular of the enum name (enum names should be the plural version). Enums are preferred to macros when defining constants because this allows them to auto-populate when using code completion software.  Here is an example from the `fs::File` class:

```c++
enum flags {
    flag_read_only /*! Open as read-only */ = LINK_O_RDONLY,
    flag_write_only /*! Open as write-only */ = LINK_O_WRONLY,
    flag_create /*! Create when opening (files) */ = LINK_O_CREAT,
    flag_truncate /*! Truncate when opening (files) */ = LINK_O_TRUNC
};
```

## Building the Stratify API

The latest API is built and distributed with the [Stratify Labs SDK](https://app.stratifylabs.co/). You only need to build and install the source code if you want to debug, contribute new features, or equip your local SDK with a previous or customized version.

Here are the steps to build and install the API using the Stratify Labs command line tool `sl`.

```
sl sdk.install # install the SDK (if it isn't already installed)
sl sdk.bootstrap
sl sdk.update # this will pull, build, and install StratifyOS and StratifyAPI
```
