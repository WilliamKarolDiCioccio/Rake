-- The only purpose of this file is to remove lua warnings in vscode

ignore = {
    "112", -- Undefined global
    "111", -- Setting an undefined global variable.
    "112", -- Mutating an undefined global variable.
    "113", -- Accessing an undefined global variable.
    "121", -- Setting a read-only global variable.
    "122", -- Setting a read-only field of a global variable.
    "131", -- Unused implicitly defined global variable.
    "142", -- Setting an undefined field of a global variable.
    "143" -- Accessing an undefined field of a global variable
}
