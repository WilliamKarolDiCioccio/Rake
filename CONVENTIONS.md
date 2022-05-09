# CONVENTIONS

##### Code formatting

Rake uses code formatting tools. Below is clang-format configuration file (.clang-format).

```
BasedOnStyle: Microsoft
ColumnLimit: 250
SortIncludes: false
SortUsingDeclarations: false
ReflowComments: false
AlignConsecutiveMacros: true
Standard: c++20
```

---

Clang Power Tools: https://www.clangpowertools.com (For further informations)

##### Naming conventions

Variables are written in Camel's Notation.
Functions are written in Pascal's Notation.
Member variables prefix "m_" (Ex. "m_isRunning").
Global variables prefix "g_" (Ex. "g_applicationName").
No prefix for stack or heap allocated variables in functions.

---


