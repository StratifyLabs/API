# VarAPI

The `VarAPI` library manages data objects for the `API` framework.

## Binary Data Management

- [View](include/var/View.hpp): View of any data on the stack/heap/static
- [Data](include/var/Data.hpp): Dynamic heap data

A `View` can only refer to data that already exists. It doesn't allocate memory in any way. It will automatically figure out the size of the target. It can be implicitly constructed from `Data`, `String`, `StringView`, and `const char *` (c-style string). They can be explicitly constructed from fundamental types where the size is known at compile time. 

> A `View` is used when passing data to [file operations](../fsAPI/README.md)

```c++
#include <fs.hpp>
#include <var.hpp>

typedef struct {
  int version;
  char name[32];
} my_header_t;

my_header_t header;

//fill header
View(header).fill<u8>(0xaa);

//Use view to read data into header
File("path.data").read(View(header));
```

A `View` cannot be constructed from a class or any type where the size is not known at runtime. The following won't compile:

```c++
#include <var.hpp>

int my_function(int size){
  char buffer[size];
  
  //can't compile this
  View(buffer).fill(0);


  char buffer2[64];
  View buffer_view(buffer2); // this is OK
  View(buffer_view).fill(0); //this won't compile (static_assert)
}
```

The `Data` class uses the heap to dynamically allocate memory. Generally, it should be used sparingly if you are trying to maximize performance.


```c++
#include <var.hpp>

//converts the string to 16 bytes of data
Data hex = Data::from_string("00112233445566778899AABBCCDDEEFF");
```

## Containers

These classes are all API-style wrappers for the equivalent `std::container`. 

> Other than `Array` these use `malloc`/`free` under the hood.

- [Vector](include/var/Vector.hpp)
- [Array](include/var/Array.hpp)
- [Queue](include/var/Queue.hpp)
- [Stack](include/var/Stack.hpp)
- [Deque](include/var/Deque.hpp)


## Strings

Strings use one of three types:

- `StringView`: wrapper for C++17 `std::string_view`
- `StackString<int size>`: Template class for fixed buffer-sized strings (on the)
- `String`: wrapper for C++ `std::string` (uses dynamic memory allocation for longer strings)

**StringView**

The `StringView` is just a view (pointer and length) of the string. The data must be held elsewhere. The length is a fixed maximum size at construction though you can narrow the view through other methods.

VarAPI is designed to use `StringView` as the most basic string. Any and all string types (including `const char*`) are easily converted to `StringView`.

> All these guidelines also apply to `std::string_view`.

- Always pass `StringView` by value
- Always use `const StringView` when passing a string parameter to a method
- Avoid using `StringView` as a local variable (use `auto` instead)
- Don't return a `StringView` unless you are sure about the lifetime of the string being viewed and the lifetime of the owner taking the return.

`StringView` does not guarantee null-termination.

**StackString**

There are several standard `StackString` declarations for common usage:

- `IdString` short string (up to 24 bytes) for unique (random or time-based) string ids
- `KeyString` short string (up to 48 bytes) for things like JSON keys
- `PathString` for file paths
  - Size is OS dependent (`PATH_MAX`)
  - The `&` operator is used for concatenation
  - The `/` operator concatenates by inserting '/'
- `GeneralString` for larger strings
  - Size is up to 256 bytes for embedded and 2048 for win/mac/linux.
  - The `|` operator is used for concatenation
- `NumberString` for easily converting a number to a string (up to 64 bytes length)
  - Special constructor to immediately convert numbers to strings

Here are the `StackString` basic examples:

```c++
#include <fs.hpp>
#include <var.hpp>
#include <chrono.hpp>

int i = 0;
const auto key = KeyString().format("key-%d", i++);
//or with a NumberString()
const KeyString key = NumberString(i++, "key-%d").string_view();

// creates "directory/key-0.txt"
const auto path = "directory" / key & ".txt";

//implicit conversion to StringView is built-in
//File(const StringView path) opens a file
File("directory" / key & ".txt");

const StringView name = "general";
GeneralString general = "this is a " | name | " string.";

GeneralString with_numbers = "there are " | NumberString(general.length())
  | " characters in general".

//This is really bad -- never do this
//`discard_string` will refer to a PathString rvalue that is destroyed
const StringView discard_string = "directory" / key & ".txt";

//This is the way to do it (let the compiler worry about the type)
const auto make_it_happen_string0 = "directory" / key & ".txt";
const auto make_it_happen_string1 = "directory" | key | ".txt";
```

Stack strings are always null-terminated and provide a `cstring()` method to access a `const char *`.

**String**

The `String` class (a wrapper for std::string) should only be used when the string length is unknown and definitely will not fit in a `StackString` type.

`String` class uses the `+` operator to concatenate.

`String` comes with a performance penalty (`malloc`/`free`). So it is never created implicitly. `StringView::to_string()` will promote just about anything to `String`.

`String` is always null-terminated and provides a `cstring()` method to access a `const char *`.

```c++

#include <var.hpp>

//PathString used
printf("%s\n", ("path" & "string").cstring());
//GeneralString used
printf("%s\n", ("path" | "string").cstring());

//String used
printf("%s\n", ("just a " + "string").cstring());

typedef struct {
  int version;
  char name[32];
} my_header_t;

my_header_t header;

//Use a string with View::to_string() because
//the length is unknown and can exceed StackString lengths
String view_string = View(header).to_string();
```