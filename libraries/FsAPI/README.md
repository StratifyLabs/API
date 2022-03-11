# FsAPI

The `FsAPI` defines a C++ abstraction layer for accessing the filesystem and other file-like constructs.

## The `FileObject`

The `FileObject` is an integral part `API` framework. It defines a pure virtual class for accessing files and file-like
constructs. Many other classes use `FileObject`s to manage data.

- The File class provides access to a standard file.
- The DataFile class creates a file like storage object on the heap
- The ViewFile lets any variable serve as a fixed size file
- The LambdaFile manages file contents using callbacks

`FileObject` contains a method allowing you to write a file from the contents of another file. Here are some useful
examples:

```cpp
//load a file from the disk
DataFile().write(File("myfile.txt"));

//save a variable to disk
char save_this_buffer[64];
File(File::IsOverwrite::yes, "myfile.txt").write(View(save_this_buffer));

//read a section of a file to a variable
struct my_header header;
constexpr int location_of_header = 64;
ViewFile(View(my_header)).write(File("header.bin").seek(location_of_header));

//OR read header as a view
File("header.bin").seek(location_of_header).read(View(header));
```

You can also perform file operations using a View object.

```cpp
#include <fs.hpp>
#include <var.hpp>

File file(File::IsOverwrite::yes, "myfile.txt");

char buffer[32];

file.write(View(buffer)); //explicit View from fundamental type
file.write("Hello World\n"); //implicit View from const char *
file.seek(0).read(View(buffer)); //read the contents of buffer back

if( file.is_error() ){
  //something didn't work
}
```


