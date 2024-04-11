#pragma once

namespace Rake::core {

enum class KeyboardKeys : uint8_t {
    backspace = 0x08,
    tab = 0x09,
    clear = 0x0C,
    returnKey = 0x0D,
    shift = 0x10,
    control = 0x11,
    menu = 0x12,
    pause = 0x13,
    capital = 0x14,
    escape = 0x1B,
    space = 0x20,
    pageUp = 0x21,
    pageDown = 0x22,
    end = 0x23,
    home = 0x24,
    left = 0x25,
    up = 0x26,
    right = 0x27,
    down = 0x28,
    select = 0x29,
    print = 0x2A,
    execute = 0x2B,
    snapshot = 0x2C,
    insert = 0x2D,
    deleteKey = 0x2E,
    help = 0x2F,
    zero = 0x30,
    one = 0x31,
    two = 0x32,
    three = 0x33,
    four = 0x34,
    five = 0x35,
    six = 0x36,
    seven = 0x37,
    eight = 0x38,
    nine = 0x39,
    a = 0x41,
    b = 0x42,
    c = 0x43,
    d = 0x44,
    e = 0x45,
    f = 0x46,
    g = 0x47,
    h = 0x48,
    i = 0x49,
    j = 0x4A,
    k = 0x4B,
    l = 0x4C,
    m = 0x4D,
    n = 0x4E,
    o = 0x4F,
    p = 0x50,
    q = 0x51,
    r = 0x52,
    s = 0x53,
    t = 0x54,
    u = 0x55,
    v = 0x56,
    w = 0x57,
    x = 0x58,
    y = 0x59,
    z = 0x5A,
    leftWin = 0x5B,
    rightWin = 0x5C,
    apps = 0x5D,
    sleep = 0x5F,
    numpad0 = 0x60,
    numpad1 = 0x61,
    numpad2 = 0x62,
    numpad3 = 0x63,
    numpad4 = 0x64,
    numpad5 = 0x65,
    numpad6 = 0x66,
    numpad7 = 0x67,
    numpad8 = 0x68,
    numpad9 = 0x69,
    multiply = 0x6A,
    add = 0x6B,
    separator = 0x6C,
    subtract = 0x6D,
    decimal = 0x6E,
    divide = 0x6F,
    f1 = 0x70,
    f2 = 0x71,
    f3 = 0x72,
    f4 = 0x73,
    f5 = 0x74,
    f6 = 0x75,
    f7 = 0x76,
    f8 = 0x77,
    f9 = 0x78,
    f10 = 0x79,
    f11 = 0x7A,
    f12 = 0x7B,
    numLock = 0x90,
    scroll = 0x91,
    lShift = 0xA0,
    rShift = 0xA1,
    lControl = 0xA2,
    rControl = 0xA3,
    lMenu = 0xA4,
    rMenu = 0xA5,
    oem1 = 0xBA,
    oemPlus = 0xBB,
    oemComma = 0xBC,
    oemMinus = 0xBD,
    oemPeriod = 0xBE,
    oem2 = 0xBF,
    oem3 = 0xC0,
    oem4 = 0xDB,
    oem5 = 0xDC,
    oem6 = 0xDD,
    oem7 = 0xDE,
    oem8 = 0xDF,
    oem9 = 0xE2,
    processKey = 0xE5,
    packet = 0xE7,
    attn = 0xF6,
    crsel = 0xF7,
    exsel = 0xF8,
    ereof = 0xF9,
    play = 0xFA,
    zoom = 0xFB,
    noname = 0xFC,
    pa1 = 0xFD,
    oemClear = 0xFE
};

enum class MouseButtons : uint8_t { left = 0, middle = 1, right = 2, button4 = 3, button5 = 4 };

enum class MouseAxis : uint8_t { x = 0, y = 1 };

enum class ControllerButtons : uint8_t {
    a = 0,
    b = 1,
    x = 2,
    y = 3,
    ex = 0,
    circle = 1,
    square = 2,
    triangle = 3,
    left = 4,
    right = 5,
    up = 6,
    down = 7,
    leftThumbstick = 8,
    rightThumbstick = 9,
    leftShoulder = 10,
    rightShoulder = 11
};

enum class ControllerSticks : uint8_t { left = 0, right = 1 };

enum class ControllerAxis : uint8_t { left = 0, right = 1 };

enum class ControllerTriggers : uint8_t { left = 0, right = 1 };

}  // namespace Rake::core

#define RK_KEYBOARD_KEY_0          Rake::core::KeyboardKeys::zero
#define RK_KEYBOARD_KEY_1          Rake::core::KeyboardKeys::one
#define RK_KEYBOARD_KEY_2          Rake::core::KeyboardKeys::two
#define RK_KEYBOARD_KEY_3          Rake::core::KeyboardKeys::three
#define RK_KEYBOARD_KEY_4          Rake::core::KeyboardKeys::four
#define RK_KEYBOARD_KEY_5          Rake::core::KeyboardKeys::five
#define RK_KEYBOARD_KEY_6          Rake::core::KeyboardKeys::six
#define RK_KEYBOARD_KEY_7          Rake::core::KeyboardKeys::seven
#define RK_KEYBOARD_KEY_8          Rake::core::KeyboardKeys::eight
#define RK_KEYBOARD_KEY_9          Rake::core::KeyboardKeys::nine
#define RK_KEYBOARD_KEY_A          Rake::core::KeyboardKeys::a
#define RK_KEYBOARD_KEY_B          Rake::core::KeyboardKeys::b
#define RK_KEYBOARD_KEY_C          Rake::core::KeyboardKeys::c
#define RK_KEYBOARD_KEY_D          Rake::core::KeyboardKeys::d
#define RK_KEYBOARD_KEY_E          Rake::core::KeyboardKeys::e
#define RK_KEYBOARD_KEY_F          Rake::core::KeyboardKeys::f
#define RK_KEYBOARD_KEY_G          Rake::core::KeyboardKeys::g
#define RK_KEYBOARD_KEY_H          Rake::core::KeyboardKeys::h
#define RK_KEYBOARD_KEY_I          Rake::core::KeyboardKeys::i
#define RK_KEYBOARD_KEY_J          Rake::core::KeyboardKeys::j
#define RK_KEYBOARD_KEY_K          Rake::core::KeyboardKeys::k
#define RK_KEYBOARD_KEY_L          Rake::core::KeyboardKeys::l
#define RK_KEYBOARD_KEY_M          Rake::core::KeyboardKeys::m
#define RK_KEYBOARD_KEY_N          Rake::core::KeyboardKeys::n
#define RK_KEYBOARD_KEY_O          Rake::core::KeyboardKeys::o
#define RK_KEYBOARD_KEY_P          Rake::core::KeyboardKeys::p
#define RK_KEYBOARD_KEY_Q          Rake::core::KeyboardKeys::q
#define RK_KEYBOARD_KEY_R          Rake::core::KeyboardKeys::r
#define RK_KEYBOARD_KEY_S          Rake::core::KeyboardKeys::s
#define RK_KEYBOARD_KEY_T          Rake::core::KeyboardKeys::t
#define RK_KEYBOARD_KEY_U          Rake::core::KeyboardKeys::u
#define RK_KEYBOARD_KEY_V          Rake::core::KeyboardKeys::v
#define RK_KEYBOARD_KEY_W          Rake::core::KeyboardKeys::w
#define RK_KEYBOARD_KEY_X          Rake::core::KeyboardKeys::x
#define RK_KEYBOARD_KEY_Y          Rake::core::KeyboardKeys::y
#define RK_KEYBOARD_KEY_Z          Rake::core::KeyboardKeys::z
#define RK_KEYBOARD_KEY_NUMPAD0    Rake::core::KeyboardKeys::numpad0
#define RK_KEYBOARD_KEY_NUMPAD1    Rake::core::KeyboardKeys::numpad1
#define RK_KEYBOARD_KEY_NUMPAD2    Rake::core::KeyboardKeys::numpad2
#define RK_KEYBOARD_KEY_NUMPAD3    Rake::core::KeyboardKeys::numpad3
#define RK_KEYBOARD_KEY_NUMPAD4    Rake::core::KeyboardKeys::numpad4
#define RK_KEYBOARD_KEY_NUMPAD5    Rake::core::KeyboardKeys::numpad5
#define RK_KEYBOARD_KEY_NUMPAD6    Rake::core::KeyboardKeys::numpad6
#define RK_KEYBOARD_KEY_NUMPAD7    Rake::core::KeyboardKeys::numpad7
#define RK_KEYBOARD_KEY_NUMPAD8    Rake::core::KeyboardKeys::numpad8
#define RK_KEYBOARD_KEY_NUMPAD9    Rake::core::KeyboardKeys::numpad9
#define RK_KEYBOARD_KEY_MULTIPLY   Rake::core::KeyboardKeys::multiply
#define RK_KEYBOARD_KEY_ADD        Rake::core::KeyboardKeys::add
#define RK_KEYBOARD_KEY_SEPARATOR  Rake::core::KeyboardKeys::separator
#define RK_KEYBOARD_KEY_SUBTRACT   Rake::core::KeyboardKeys::subtract
#define RK_KEYBOARD_KEY_DECIMAL    Rake::core::KeyboardKeys::decimal
#define RK_KEYBOARD_KEY_DIVIDE     Rake::core::KeyboardKeys::divide
#define RK_KEYBOARD_KEY_UP         Rake::core::KeyboardKeys::up
#define RK_KEYBOARD_KEY_DOWN       Rake::core::KeyboardKeys::down
#define RK_KEYBOARD_KEY_LEFT       Rake::core::KeyboardKeys::left
#define RK_KEYBOARD_KEY_RIGHT      Rake::core::KeyboardKeys::right
#define RK_KEYBOARD_KEY_SHIFT      Rake::core::KeyboardKeys::shift
#define RK_KEYBOARD_KEY_CONTROL    Rake::core::KeyboardKeys::control
#define RK_KEYBOARD_KEY_SPACE      Rake::core::KeyboardKeys::space
#define RK_KEYBOARD_KEY_ESCAPE     Rake::core::KeyboardKeys::escape
#define RK_KEYBOARD_KEY_CAPITAL    Rake::core::KeyboardKeys::capital
#define RK_KEYBOARD_KEY_TAB        Rake::core::KeyboardKeys::tab
#define RK_KEYBOARD_KEY_F1         Rake::core::KeyboardKeys::f1
#define RK_KEYBOARD_KEY_F2         Rake::core::KeyboardKeys::f2
#define RK_KEYBOARD_KEY_F3         Rake::core::KeyboardKeys::f3
#define RK_KEYBOARD_KEY_F4         Rake::core::KeyboardKeys::f4
#define RK_KEYBOARD_KEY_F5         Rake::core::KeyboardKeys::f5
#define RK_KEYBOARD_KEY_F6         Rake::core::KeyboardKeys::f6
#define RK_KEYBOARD_KEY_F7         Rake::core::KeyboardKeys::f7
#define RK_KEYBOARD_KEY_F8         Rake::core::KeyboardKeys::f8
#define RK_KEYBOARD_KEY_F9         Rake::core::KeyboardKeys::f9
#define RK_KEYBOARD_KEY_F10        Rake::core::KeyboardKeys::f10
#define RK_KEYBOARD_KEY_F11        Rake::core::KeyboardKeys::f11
#define RK_KEYBOARD_KEY_F12        Rake::core::KeyboardKeys::f12
#define RK_KEYBOARD_KEY_SHIFT_L    Rake::core::KeyboardKeys::lShift
#define RK_KEYBOARD_KEY_SHIFT_R    Rake::core::KeyboardKeys::rShift
#define RK_KEYBOARD_KEY_CONTROL_L  Rake::core::KeyboardKeys::lControl
#define RK_KEYBOARD_KEY_CONTROL_R  Rake::core::KeyboardKeys::rControl
#define RK_KEYBOARD_KEY_MENU_L     Rake::core::KeyboardKeys::lMenu
#define RK_KEYBOARD_KEY_MENU_R     Rake::core::KeyboardKeys::rMenu
#define RK_KEYBOARD_KEY_OEM_1      Rake::core::KeyboardKeys::oem1
#define RK_KEYBOARD_KEY_OEM_PLUS   Rake::core::KeyboardKeys::oemPlus
#define RK_KEYBOARD_KEY_OEM_COMMA  Rake::core::KeyboardKeys::oemComma
#define RK_KEYBOARD_KEY_OEM_MINUS  Rake::core::KeyboardKeys::oemMinus
#define RK_KEYBOARD_KEY_OEM_PERIOD Rake::core::KeyboardKeys::oemPeriod
#define RK_KEYBOARD_KEY_OEM_2      Rake::core::KeyboardKeys::oem2
#define RK_KEYBOARD_KEY_OEM_3      Rake::core::KeyboardKeys::oem3
#define RK_KEYBOARD_KEY_OEM_4      Rake::core::KeyboardKeys::oem4
#define RK_KEYBOARD_KEY_OEM_5      Rake::core::KeyboardKeys::oem5
#define RK_KEYBOARD_KEY_OEM_6      Rake::core::KeyboardKeys::oem6
#define RK_KEYBOARD_KEY_OEM_7      Rake::core::KeyboardKeys::oem7
#define RK_KEYBOARD_KEY_OEM_8      Rake::core::KeyboardKeys::oem8
#define RK_KEYBOARD_KEY_OEM_9      Rake::core::KeyboardKeys::oem9
#define RK_KEYBOARD_KEY_PROCESSKEY Rake::core::KeyboardKeys::processKey
#define RK_KEYBOARD_KEY_PACKET     Rake::core::KeyboardKeys::packet
#define RK_KEYBOARD_KEY_ATTN       Rake::core::KeyboardKeys::attn
#define RK_KEYBOARD_KEY_CRSEL      Rake::core::KeyboardKeys::crsel
#define RK_KEYBOARD_KEY_EXSEL      Rake::core::KeyboardKeys::exsel
#define RK_KEYBOARD_KEY_EREOF      Rake::core::KeyboardKeys::ereof
#define RK_KEYBOARD_KEY_PLAY       Rake::core::KeyboardKeys::play
#define RK_KEYBOARD_KEY_ZOOM       Rake::core::KeyboardKeys::zoom
#define RK_KEYBOARD_KEY_NONAME     Rake::core::KeyboardKeys::noname
#define RK_KEYBOARD_KEY_PA1        Rake::core::KeyboardKeys::pa1
#define RK_KEYBOARD_KEY_OEM_CLEAR  Rake::core::KeyboardKeys::oemClear

#define RK_MOUSE_BUTTON_L Rake::core::MouseButtons::left
#define RK_MOUSE_BUTTON_R Rake::core::MouseButtons::right
#define RK_MOUSE_BUTTON_M Rake::core::MouseButtons::middle
#define RK_MOUSE_BUTTON_4 Rake::core::MouseButtons::button4
#define RK_MOUSE_BUTTON_5 Rake::core::MouseButtons::button5

#define RK_MOUSE_AXIS_X Rake::core::MouseAxis::x
#define RK_MOUSE_AXIS_Y Rake::core::MouseAxis::x

#define RK_CONTROLLER_BUTTON_A        Rake::core::ControllerButtons::a
#define RK_CONTROLLER_BUTTON_B        Rake::core::ControllerButtons::b
#define RK_CONTROLLER_BUTTON_X        Rake::core::ControllerButtons::x
#define RK_CONTROLLER_BUTTON_Y        Rake::core::ControllerButtons::y
#define RK_CONTROLLER_BUTTON_EX       Rake::core::ControllerButtons::ex
#define RK_CONTROLLER_BUTTON_CIRCLE   Rake::core::ControllerButtons::circle
#define RK_CONTROLLER_BUTTON_SQUARE   Rake::core::ControllerButtons::square
#define RK_CONTROLLER_BUTTON_TRIANGLE Rake::core::ControllerButtons::triangle
#define RK_CONTROLLER_BUTTON_L        Rake::core::ControllerButtons::left
#define RK_CONTROLLER_BUTTON_R        Rake::core::ControllerButtons::right
#define RK_CONTROLLER_BUTTON_UP       Rake::core::ControllerButtons::up
#define RK_CONTROLLER_BUTTON_DOWN     Rake::core::ControllerButtons::down
#define RK_CONTROLLER_THUMBSTICK_L    Rake::core::ControllerButtons::leftThumbstick
#define RK_CONTROLLER_THUMBSTICK_R    Rake::core::ControllerButtons::rightThumbstick
#define RK_CONTROLLER_SHOULDER_L      Rake::core::ControllerButtons::leftShoulder
#define RK_CONTROLLER_SHOULDER_R      Rake::core::ControllerButtons::rightShoulder

#define RK_CONTROLLER_STICK_L Rake::core::ControllerSticks::left
#define RK_CONTROLLER_STICK_R Rake::core::ControllerSticks::right

#define RK_CONTROLLER_AXIS_L Rake::core::ControllerAxis::left
#define RK_CONTROLLER_AXIS_R Rake::core::ControllerAxis::right

#define RK_CONTROLLER_TRIGGER_L Rake::core::ControllerTriggers::left
#define RK_CONTROLLER_TRIGGER_R Rake::core::ControllerTriggers::right