![prelude](img/logo.png?raw=true "logo")

`prelude` is a tiny package, that contains essential definitions for
higher-level but low-cost abstractions in C. It is conforming and portable.
The types, their methods and unified values can be used to decide comparison
ordering; to indicate proxy objects' ownership on their members; to store
any pointer in a truly generic pointer type; and to pass message along with the
scalar expression to assert.

- Dependencies
- Installation
- [Comparison Order](#comparison-order)
- [Ownership of Members](#ownership-of-members)
- [Generic Pointer](#generic-pointer)
- [Assertion](#assertion)

Comparison Order
----------------

The `pr_Order` type can be used to compare complex, user-defined data types. The
type is guaranteed to be an unsigned integer type, capable of storing a single
ordering constant.

The ordering constants are unique and can be used in both conditional statements
and bit-mask unfolding.

**Usage**

```C
#include <prelude/order.h>
```

**Available `pr_Order` constants**

- `pr_EQUAL`: indicates that left and right values are equal
- `pr_NOT_EQUAL`: indicates that left and right values are not equal
- `pr_GREATER`: indicates that left value is greater than right value
- `pr_LESSER`: indicates that left value is lesser than right value
- `pr_UNCOMPARABLE`: indicates that left and right values cannot be compared
- `pr_UNCOMPARABLE_LEFT`: indicates that left value cannot be compared to the
  right value
- `pr_UNCOMPARABLE_RIGHT`: indicates that right value cannot be compared to the
  left value

One can use them in a simple boolean comparison, as `pr_EQUAL`'s boolean value
is always `false`, while any other constant's value is `true`. For example:

```C
pr_Order order = /* comparison returns ordering */;
if (order)
    puts("A is not equal to B");
else
    puts("A is equal to B");
```

One can use the constants to express more complex statements, for example a
greater than equal condition would look like this:

```C
pr_Order order = /* comparison returns ordering */;
if ((order == pr_EQUAL) ||
    (order == pr_GREATER))
        puts("A is greater than or equal to B");
else
    puts("A is lesser than B");
```

One can use the constants for bit-mask unfolding, because all constants, except
`pr_EQUAL` folds the value `pr_NOT_EQUAL`. For example:

```C
pr_Order order = pr_GREATER;
if (order & pr_NOT_EQUAL)
    puts("A is not equal to B");
else
    puts("A is equal to B");
```

Also, both `pr_UNCOMPARABLE_LEFT` and `pr_UNCOMPARABLE_RIGHT` constants fold the
`pr_UNCOMPARABLE` constant. For example:

```C
pr_Order order = pr_UNCOMPARABLE_RIGHT;
if (order & pr_UNCOMPARABLE)
    puts("Cannot compare A to B");
```

**Available methods on `pr_Order` types:**

```C
const char*
pr_Order_str(pr_Order self);
```
Returns the string representation of a contant as a NULL-terminated static and
constant C string. For example: `pr_Equal` will be written as `"pr_Equal"`. If
the passed value to this function is not a valid constant, it will return
`"(UNKNOWN)"`.


```C
size_t
pr_Order_put(pr_Order self);
```
Writes *qualified* string representation of a constant to the `stdout` file
stream. Returns the number of bytes that has been successfully written to the
stream. For example: `pr_Equal` -> `<pr_Order pr_Equal>`. If the value passed to
this method is not a valid `pr_Order` constant, the method will write
`<pr_Order (UNKNOWN)>`.


```C
size_t
pr_Order_fput(pr_Order  self,
              FILE     *stream);
```
Same as `pr_Order_put`, but it writes the representation to the specified file
stream.


```C
size_t
pr_Order_sput(pr_Order  self,
              size_t    length,
              char     *buffer);
```
Same as `pr_Order_put`, except it writes the representation to a `length` size
`char` buffer. It will write as many bytes as it can before it hits the bound of
the passed buffer or reaches the end of the representation. If `buffer` is not
`NULL` and `length` is not `0` it is guaranteed that the string in the buffer
will be a NULL-terminated C string.


```C
size_t
pr_Order_sput_len(pr_Order self);
```
Calculates and returns the size of the buffer which is required to store the
qualified representation of the passed order. The returned value contains the
NULL-termination.


```C
pr_Order
pr_Order_not(pr_Order self);
```
Negates the value of the order if it is reasonable. Returns the negated order
value.

| original                 | negated                  |
|--------------------------|--------------------------|
| `pr_Equal`               | `pr_NOT_EQUAL`           |
| `pr_NOT_EQUAL`           | `pr_EQUAL`               |
| `pr_GREATER`             | `pr_LESSER`              |
| `pr_LESSER`              | `pr_GREATER`             |
| `pr_UNCOMAPARABLE`       | `pr_UNCOMAPARABLE`       |
| `pr_UNCOMAPARABLE_LEFT`  | `pr_UNCOMAPARABLE_LEFT`  |
| `pr_UNCOMAPARABLE_RIGHT` | `pr_UNCOMAPARABLE_RIGHT` |


**Other constants**

```C
#define PR_ORDER_MAX_SPUT_LEN
```
Specifies the maximum size of a buffer which is big enough to contain any
possible outputs of the `pr_Order_sput` method.


Ownership of Members
--------------------

The `pr_Ownership` type can be used to indicate ownership over members of a
complex, user-defined, proxy data type. The type is guaranteed to be an
unsingned integer type, capable of storing a single or more bitmasked ownership
constants.

In practice, `pr_Ownership` is a way of storing which pointers of the owner
object are borrowed and which ones are owned by it. This approach makes it easy
to decide which pointers should be `free`'d by the *deallocator*/*destructor*
method, and because of this flexibility, objects which are using `pr_Ownership`
can be allocated completely statically or completely dynamically or mixed.

**Usage:**

```C
#include <prelude/ownership.h>
```

**Available `pr_Ownership` constants:**

- `pr_OWNS_NONE`: indicates that the owner borrowed all of its pointers
- `pr_OWNS_ALL`: indicates that the owner owns all of its pointers
- `pr_OWNS_SELF`: indicates that the owner owns itself
- `pr_OWNS_ATTR_n`: indicates that the owner owns *n*th pointer (where *n* can
   be 1 to 15)

> **NOTE:** Identifiers start with the `pr_OWNS_ATTR_` prefix are all reserved
  for future values by `prelude`.

**Best practice:**

It can be a good idea, to *alias* the provided constants for each type as the
predefined constant names are very generic and meaningless (especially the
`pr_OWNS_ATTR_n` ones. Therefore, if there is a type called `Entry`:

```C
typedef struct
{
    py_Ownership  owns;
    const char   *forename;
    const char   *surname;
} Entry;
```

Then it may define the following preprocessor contants:

```C
#define Entry_OWNS_NONE     pr_OWNS_NONE
#define Entry_OWNS_ALL      pr_OWNS_ALL
#define Entry_OWNS_SELF     pr_OWNS_SELF
#define Entry_OWNS_FORENAME pr_OWNS_ATTR_1
#define Entry_OWNS_SURNAME  pr_OWNS_ATTR_2
```

**Available methods on `pr_Ownership`:**

```C
const char*
pr_Ownership_str(pr_Ownership self);
```
Returns the string representation of ownership as a NULL-terminated static and
constant C string.  For example: `pr_OWNS_NONE` will be written as
`"pr_OWNS_NONE"`. If the passed value to this method is not a valid constant, it
will write `"(UNKNOWN)"`. Because `pr_Ownership` can be a bit-masked value, this
method will return only the lowest value folded into 'self'. For example:
`pr_OWNS_SELF | pr_OWNS_ATTR_1` wil be written as `"pr_OWNS_SELF"`. If all the
folded values are needed, one can use `pr_Ownership_sput` (but it will produce a
*qulaified* representation), or one can unfold the possible values separately
and pass them to this method if they are present.

```C
size_t
pr_Ownership_put(pr_Ownership self);
```
Writes *qualified* string representation of one or several folded constants to
the `stdout` file stream. For example: `pr_OWNS_SELF | pr_OWNS_ATTR_2` will be
written as `<pr_Ownership pr_OWNS_SELF|pr_OWNS_ATTR_2>`. If the value passed to
this method is not a valid `pr_Ownership` constant, the method will write
`<pr_Ownership (UNKNOWN)>`.

```C
size_t
pr_Ownership_fput(pr_Ownership  self,
                  FILE         *stream);
```
Same as `pr_Ownership_put`, but it writes the representation to the specified
file stream.

```C
size_t
pr_Ownership_sput(pr_Ownership  self,
                  size_t        length,
                  char         *buffer);
```
Same as `pr_Ownership_put`, except it writes the representation to a length size
char buffer. It will write as many bytes as it can before it hits the bound of
the passed buffer or reaches the end of the representation. If buffer is not
`NULL` and length is not `0` it is guaranteed that the string in the buffer will
be a NULL-terminated C string.

```C
size_t
pr_Ownership_sput_len(pr_Ownership self);
```
Calculates and returns the size of the buffer which is required to store the
qualified representation of the passed ownership. The returned value contains
the NULL-termination.

**Other constants**

```C
#define PR_OWNERSHIP_MAX_SPUT_LEN
```
Specifies the maximum size of a buffer which is big enough to contain any
possible outputs of the `pr_Ownership_sput` method.


Generic Pointer
---------------

> **TODO:** Write documentation for this type!



Assertion
---------

**Usage**

```C
#include <prelude/assert.h>
```

**Available macros**

```C
void pr_assert(<scalar>    expression,
               const char *message);
```
Works the same way, as the standard library's `assert` (can be muted by defining
`NDEBUG`) but it is capable of printing an additional message out. The `message`
should not be a pointer to `NULL`. The passed message will be printed to the
`stderr` file stream.

```C
void pr_assert_x(<scalar>    expression,
                 const char *expression_string,
                 const char *message);
```
Works the same as `pr_assert_x`, except it takes the expression as a string for
its second argument. This form can be be used, to prevent macro replacement,
when `pr_assert_x` is wrapped with a macro.  The `expression_string` should not
be a pointer to `NULL`.

> **NOTE:** Using this header alone does not require to link against either
> `libprelude.a` or `libprelude.so`.



License
-------

Copyright &copy; 2016 **Peter Varo**

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program, most likely a file in the root directory, called 'LICENSE'.
If not, see <http://www.gnu.org/licenses>.

- - -

The font used in the logo is called **Cinzel**. It is licensed under the
[SIL Open Font License v1.10](http://scripts.sil.org/OFL).

Copyright &copy; 2012 **Natanael Gama**
