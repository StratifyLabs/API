# PrinterAPI

The PrinterAPI enables an application to print (or otherwise write) variables and classes in a structured manner.

The default `Printer` class is yaml-like but not structured. The `JsonPrinter` class prints properly formed JSON. To support this, the `Printer` class makes use of structured data principles such as printing objects, arrays, and key-value pairs.

The `print_final()` is virtual and can be overridden. By default, it writes to the standard output but could be modified to write to a file or web socket or anything.

The `Printer` class makes heavy usage of the `<<` operator. It provides operators for upstream types such as those defined in VarAPI.

```cpp
#include <printer.hpp>
#include <var.hpp>

Array<u8, 16> data;
data.fill(0xff);

Printer p;
p << data;

//any type supporting << can be encapsulated in an object
p.object("dataObject", data);

//or an array (no keys printed)
p.array("dataArray", data);
```

Downstream classes can define the `<<` operator to seamlessly integrate with the printer class.  The ChronoAPI does this to print `chrono::ClockTime`.

```cpp
namespace printer {
Printer & operator<<(Printer &printer, const chrono::ClockTime &a){
  printer.key("seconds", var::NumberString(a.seconds())
    .key("nanoseconds", var::NumberString(a.nanoseconds());
  return printer;
}
} // namespace printer
```

Now we can do:

```
JsonPrinter().object("clockTime", ClockTime::get_system_time());
```

This will give us:

```json
  "clockTime": {
    "seconds": 1234,
    "nanoseconds": 5678
  }
```
