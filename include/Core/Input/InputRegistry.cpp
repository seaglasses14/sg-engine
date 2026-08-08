#include "InputRegistry.h"
#include <unordered_map>

namespace
{
    const std::vector<InputInfo> inputInfos =
    {
        // Keyboard

        { Key_Space, "Space" },
        { Key_Apostrophe, "Apostrophe" },
        { Key_Comma, "Comma" },
        { Key_Minus, "Minus" },
        { Key_Period, "Period" },
        { Key_Slash, "Slash" },

        { Key_0, "0" },
        { Key_1, "1" },
        { Key_2, "2" },
        { Key_3, "3" },
        { Key_4, "4" },
        { Key_5, "5" },
        { Key_6, "6" },
        { Key_7, "7" },
        { Key_8, "8" },
        { Key_9, "9" },

        { Key_Semicolon, "Semicolon" },
        { Key_Equal, "Equal" },

        { Key_A, "A" },
        { Key_B, "B" },
        { Key_C, "C" },
        { Key_D, "D" },
        { Key_E, "E" },
        { Key_F, "F" },
        { Key_G, "G" },
        { Key_H, "H" },
        { Key_I, "I" },
        { Key_J, "J" },
        { Key_K, "K" },
        { Key_L, "L" },
        { Key_M, "M" },
        { Key_N, "N" },
        { Key_O, "O" },
        { Key_P, "P" },
        { Key_Q, "Q" },
        { Key_R, "R" },
        { Key_S, "S" },
        { Key_T, "T" },
        { Key_U, "U" },
        { Key_V, "V" },
        { Key_W, "W" },
        { Key_X, "X" },
        { Key_Y, "Y" },
        { Key_Z, "Z" },

        { Key_LeftBracket, "Left Bracket" },
        { Key_Backslash, "Backslash" },
        { Key_RightBracket, "Right Bracket" },
        { Key_GraveAccent, "Grave Accent" },
        { Key_World1, "World 1" },
        { Key_World2, "World 2" },

        { Key_Escape, "Escape" },
        { Key_Enter, "Enter" },
        { Key_Tab, "Tab" },
        { Key_Backspace, "Backspace" },
        { Key_Insert, "Insert" },
        { Key_Delete, "Delete" },

        { Key_Right, "Right Arrow" },
        { Key_Left, "Left Arrow" },
        { Key_Down, "Down Arrow" },
        { Key_Up, "Up Arrow" },

        { Key_PageUp, "Page Up" },
        { Key_PageDown, "Page Down" },
        { Key_Home, "Home" },
        { Key_End, "End" },

        { Key_CapsLock, "Caps Lock" },
        { Key_ScrollLock, "Scroll Lock" },
        { Key_NumLock, "Num Lock" },
        { Key_PrintScreen, "Print Screen" },
        { Key_Pause, "Pause" },

        { Key_F1, "F1" },
        { Key_F2, "F2" },
        { Key_F3, "F3" },
        { Key_F4, "F4" },
        { Key_F5, "F5" },
        { Key_F6, "F6" },
        { Key_F7, "F7" },
        { Key_F8, "F8" },
        { Key_F9, "F9" },
        { Key_F10, "F10" },
        { Key_F11, "F11" },
        { Key_F12, "F12" },
        { Key_F13, "F13" },
        { Key_F14, "F14" },
        { Key_F15, "F15" },
        { Key_F16, "F16" },
        { Key_F17, "F17" },
        { Key_F18, "F18" },
        { Key_F19, "F19" },
        { Key_F20, "F20" },
        { Key_F21, "F21" },
        { Key_F22, "F22" },
        { Key_F23, "F23" },
        { Key_F24, "F24" },
        { Key_F25, "F25" },

        { Key_KP_0, "Keypad 0" },
        { Key_KP_1, "Keypad 1" },
        { Key_KP_2, "Keypad 2" },
        { Key_KP_3, "Keypad 3" },
        { Key_KP_4, "Keypad 4" },
        { Key_KP_5, "Keypad 5" },
        { Key_KP_6, "Keypad 6" },
        { Key_KP_7, "Keypad 7" },
        { Key_KP_8, "Keypad 8" },
        { Key_KP_9, "Keypad 9" },

        { Key_KP_Decimal, "Keypad Decimal" },
        { Key_KP_Divide, "Keypad Divide" },
        { Key_KP_Multiply, "Keypad Multiply" },
        { Key_KP_Subtract, "Keypad Subtract" },
        { Key_KP_Add, "Keypad Add" },
        { Key_KP_Enter, "Keypad Enter" },
        { Key_KP_Equal, "Keypad Equal" },

        { Key_LeftShift, "Left Shift" },
        { Key_LeftControl, "Left Control" },
        { Key_LeftAlt, "Left Alt" },
        { Key_LeftSuper, "Left Super" },

        { Key_RightShift, "Right Shift" },
        { Key_RightControl, "Right Control" },
        { Key_RightAlt, "Right Alt" },
        { Key_RightSuper, "Right Super" },

        { Key_Menu, "Menu" },

        // Mouse

        { Mouse_Left, "Left Mouse" },
        { Mouse_Right, "Right Mouse" },
        { Mouse_Middle, "Middle Mouse" },
        { Mouse_4, "Mouse 4" },
        { Mouse_5, "Mouse 5" },
        { Mouse_6, "Mouse 6" },
        { Mouse_7, "Mouse 7" },
        { Mouse_8, "Mouse 8" },

        { Mouse_Delta, "Mouse 2D Axis" },
        { Mouse_Scroll, "Mouse Scroll" },

        // Joysticks

        { Joystick_1, "Joystick 1" },
        { Joystick_2, "Joystick 2" },
        { Joystick_3, "Joystick 3" },
        { Joystick_4, "Joystick 4" },
        { Joystick_5, "Joystick 5" },
        { Joystick_6, "Joystick 6" },
        { Joystick_7, "Joystick 7" },
        { Joystick_8, "Joystick 8" },
        { Joystick_9, "Joystick 9" },
        { Joystick_10, "Joystick 10" },
        { Joystick_11, "Joystick 11" },
        { Joystick_12, "Joystick 12" },
        { Joystick_13, "Joystick 13" },
        { Joystick_14, "Joystick 14" },
        { Joystick_15, "Joystick 15" },
        { Joystick_16, "Joystick 16" },

        // Gamepad

        { Gamepad_A, "Gamepad A" },
        { Gamepad_B, "Gamepad B" },
        { Gamepad_X, "Gamepad X" },
        { Gamepad_Y, "Gamepad Y" },

        { Gamepad_LeftBumper, "Left Bumper" },
        { Gamepad_RightBumper, "Right Bumper" },

        { Gamepad_Back, "Back" },
        { Gamepad_Start, "Start" },
        { Gamepad_Guide, "Guide" },

        { Gamepad_LeftThumb, "Left Thumb" },
        { Gamepad_RightThumb, "Right Thumb" },

        { Gamepad_DpadUp, "D-Pad Up" },
        { Gamepad_DpadRight, "D-Pad Right" },
        { Gamepad_DpadDown, "D-Pad Down" },
        { Gamepad_DpadLeft, "D-Pad Left" },

        { Gamepad_LeftX, "Left Stick X" },
        { Gamepad_LeftY, "Left Stick Y" },
        { Gamepad_RightX, "Right Stick X" },
        { Gamepad_RightY, "Right Stick Y" },
        { Gamepad_LeftTrigger, "Left Trigger" },
        { Gamepad_RightTrigger, "Right Trigger" }
    };

    const std::unordered_map<InputCode, InputInfo> inputInfoLookup =
    {
        // Keyboard

        { Key_Space,             { Key_Space,             "Space" } },
        { Key_Apostrophe,        { Key_Apostrophe,        "Apostrophe" } },
        { Key_Comma,             { Key_Comma,             "Comma" } },
        { Key_Minus,             { Key_Minus,             "Minus" } },
        { Key_Period,            { Key_Period,            "Period" } },
        { Key_Slash,             { Key_Slash,             "Slash" } },

        { Key_0,                 { Key_0,                 "0" } },
        { Key_1,                 { Key_1,                 "1" } },
        { Key_2,                 { Key_2,                 "2" } },
        { Key_3,                 { Key_3,                 "3" } },
        { Key_4,                 { Key_4,                 "4" } },
        { Key_5,                 { Key_5,                 "5" } },
        { Key_6,                 { Key_6,                 "6" } },
        { Key_7,                 { Key_7,                 "7" } },
        { Key_8,                 { Key_8,                 "8" } },
        { Key_9,                 { Key_9,                 "9" } },

        { Key_Semicolon,         { Key_Semicolon,         "Semicolon" } },
        { Key_Equal,             { Key_Equal,             "Equal" } },

        { Key_A,                 { Key_A,                 "A" } },
        { Key_B,                 { Key_B,                 "B" } },
        { Key_C,                 { Key_C,                 "C" } },
        { Key_D,                 { Key_D,                 "D" } },
        { Key_E,                 { Key_E,                 "E" } },
        { Key_F,                 { Key_F,                 "F" } },
        { Key_G,                 { Key_G,                 "G" } },
        { Key_H,                 { Key_H,                 "H" } },
        { Key_I,                 { Key_I,                 "I" } },
        { Key_J,                 { Key_J,                 "J" } },
        { Key_K,                 { Key_K,                 "K" } },
        { Key_L,                 { Key_L,                 "L" } },
        { Key_M,                 { Key_M,                 "M" } },
        { Key_N,                 { Key_N,                 "N" } },
        { Key_O,                 { Key_O,                 "O" } },
        { Key_P,                 { Key_P,                 "P" } },
        { Key_Q,                 { Key_Q,                 "Q" } },
        { Key_R,                 { Key_R,                 "R" } },
        { Key_S,                 { Key_S,                 "S" } },
        { Key_T,                 { Key_T,                 "T" } },
        { Key_U,                 { Key_U,                 "U" } },
        { Key_V,                 { Key_V,                 "V" } },
        { Key_W,                 { Key_W,                 "W" } },
        { Key_X,                 { Key_X,                 "X" } },
        { Key_Y,                 { Key_Y,                 "Y" } },
        { Key_Z,                 { Key_Z,                 "Z" } },

        { Key_LeftBracket,       { Key_LeftBracket,       "Left Bracket" } },
        { Key_Backslash,         { Key_Backslash,         "Backslash" } },
        { Key_RightBracket,      { Key_RightBracket,      "Right Bracket" } },
        { Key_GraveAccent,       { Key_GraveAccent,       "Grave Accent" } },
        { Key_World1,            { Key_World1,            "World 1" } },
        { Key_World2,            { Key_World2,            "World 2" } },

        { Key_Escape,            { Key_Escape,            "Escape" } },
        { Key_Enter,             { Key_Enter,             "Enter" } },
        { Key_Tab,               { Key_Tab,               "Tab" } },
        { Key_Backspace,         { Key_Backspace,         "Backspace" } },
        { Key_Insert,            { Key_Insert,            "Insert" } },
        { Key_Delete,            { Key_Delete,            "Delete" } },

        { Key_Right,             { Key_Right,             "Right Arrow" } },
        { Key_Left,              { Key_Left,              "Left Arrow" } },
        { Key_Down,              { Key_Down,              "Down Arrow" } },
        { Key_Up,                { Key_Up,                "Up Arrow" } },

        { Key_PageUp,            { Key_PageUp,            "Page Up" } },
        { Key_PageDown,          { Key_PageDown,          "Page Down" } },
        { Key_Home,              { Key_Home,              "Home" } },
        { Key_End,               { Key_End,               "End" } },

        { Key_CapsLock,          { Key_CapsLock,          "Caps Lock" } },
        { Key_ScrollLock,        { Key_ScrollLock,        "Scroll Lock" } },
        { Key_NumLock,           { Key_NumLock,           "Num Lock" } },
        { Key_PrintScreen,       { Key_PrintScreen,       "Print Screen" } },
        { Key_Pause,             { Key_Pause,             "Pause" } },

        { Key_F1,                { Key_F1,                "F1" } },
        { Key_F2,                { Key_F2,                "F2" } },
        { Key_F3,                { Key_F3,                "F3" } },
        { Key_F4,                { Key_F4,                "F4" } },
        { Key_F5,                { Key_F5,                "F5" } },
        { Key_F6,                { Key_F6,                "F6" } },
        { Key_F7,                { Key_F7,                "F7" } },
        { Key_F8,                { Key_F8,                "F8" } },
        { Key_F9,                { Key_F9,                "F9" } },
        { Key_F10,               { Key_F10,               "F10" } },
        { Key_F11,               { Key_F11,               "F11" } },
        { Key_F12,               { Key_F12,               "F12" } },
        { Key_F13,               { Key_F13,               "F13" } },
        { Key_F14,               { Key_F14,               "F14" } },
        { Key_F15,               { Key_F15,               "F15" } },
        { Key_F16,               { Key_F16,               "F16" } },
        { Key_F17,               { Key_F17,               "F17" } },
        { Key_F18,               { Key_F18,               "F18" } },
        { Key_F19,               { Key_F19,               "F19" } },
        { Key_F20,               { Key_F20,               "F20" } },
        { Key_F21,               { Key_F21,               "F21" } },
        { Key_F22,               { Key_F22,               "F22" } },
        { Key_F23,               { Key_F23,               "F23" } },
        { Key_F24,               { Key_F24,               "F24" } },
        { Key_F25,               { Key_F25,               "F25" } },

        { Key_KP_0,              { Key_KP_0,              "Keypad 0" } },
        { Key_KP_1,              { Key_KP_1,              "Keypad 1" } },
        { Key_KP_2,              { Key_KP_2,              "Keypad 2" } },
        { Key_KP_3,              { Key_KP_3,              "Keypad 3" } },
        { Key_KP_4,              { Key_KP_4,              "Keypad 4" } },
        { Key_KP_5,              { Key_KP_5,              "Keypad 5" } },
        { Key_KP_6,              { Key_KP_6,              "Keypad 6" } },
        { Key_KP_7,              { Key_KP_7,              "Keypad 7" } },
        { Key_KP_8,              { Key_KP_8,              "Keypad 8" } },
        { Key_KP_9,              { Key_KP_9,              "Keypad 9" } },

        { Key_KP_Decimal,        { Key_KP_Decimal,        "Keypad Decimal" } },
        { Key_KP_Divide,         { Key_KP_Divide,         "Keypad Divide" } },
        { Key_KP_Multiply,       { Key_KP_Multiply,       "Keypad Multiply" } },
        { Key_KP_Subtract,       { Key_KP_Subtract,       "Keypad Subtract" } },
        { Key_KP_Add,            { Key_KP_Add,            "Keypad Add" } },
        { Key_KP_Enter,          { Key_KP_Enter,          "Keypad Enter" } },
        { Key_KP_Equal,          { Key_KP_Equal,          "Keypad Equal" } },

        { Key_LeftShift,         { Key_LeftShift,         "Left Shift" } },
        { Key_LeftControl,       { Key_LeftControl,       "Left Control" } },
        { Key_LeftAlt,           { Key_LeftAlt,           "Left Alt" } },
        { Key_LeftSuper,         { Key_LeftSuper,         "Left Super" } },

        { Key_RightShift,        { Key_RightShift,        "Right Shift" } },
        { Key_RightControl,      { Key_RightControl,      "Right Control" } },
        { Key_RightAlt,          { Key_RightAlt,          "Right Alt" } },
        { Key_RightSuper,        { Key_RightSuper,        "Right Super" } },

        { Key_Menu,              { Key_Menu,              "Menu" } },

        { Mouse_Left,            { Mouse_Left,            "Left Mouse" } },
        { Mouse_Right,           { Mouse_Right,           "Right Mouse" } },
        { Mouse_Middle,          { Mouse_Middle,          "Middle Mouse" } },
        { Mouse_4,               { Mouse_4,               "Mouse 4" } },
        { Mouse_5,               { Mouse_5,               "Mouse 5" } },
        { Mouse_6,               { Mouse_6,               "Mouse 6" } },
        { Mouse_7,               { Mouse_7,               "Mouse 7" } },
        { Mouse_8,               { Mouse_8,               "Mouse 8" } },

        { Mouse_Delta,           { Mouse_Delta,           "Mouse 2D Axis" } },
        { Mouse_Scroll,          { Mouse_Scroll,          "Mouse Scroll" } },

        { Joystick_1,            { Joystick_1,            "Joystick 1" } },
        { Joystick_2,            { Joystick_2,            "Joystick 2" } },
        { Joystick_3,            { Joystick_3,            "Joystick 3" } },
        { Joystick_4,            { Joystick_4,            "Joystick 4" } },
        { Joystick_5,            { Joystick_5,            "Joystick 5" } },
        { Joystick_6,            { Joystick_6,            "Joystick 6" } },
        { Joystick_7,            { Joystick_7,            "Joystick 7" } },
        { Joystick_8,            { Joystick_8,            "Joystick 8" } },
        { Joystick_9,            { Joystick_9,            "Joystick 9" } },
        { Joystick_10,           { Joystick_10,           "Joystick 10" } },
        { Joystick_11,           { Joystick_11,           "Joystick 11" } },
        { Joystick_12,           { Joystick_12,           "Joystick 12" } },
        { Joystick_13,           { Joystick_13,           "Joystick 13" } },
        { Joystick_14,           { Joystick_14,           "Joystick 14" } },
        { Joystick_15,           { Joystick_15,           "Joystick 15" } },
        { Joystick_16,           { Joystick_16,           "Joystick 16" } },

        { Gamepad_A,             { Gamepad_A,             "Gamepad A" } },
        { Gamepad_B,             { Gamepad_B,             "Gamepad B" } },
        { Gamepad_X,             { Gamepad_X,             "Gamepad X" } },
        { Gamepad_Y,             { Gamepad_Y,             "Gamepad Y" } },

        { Gamepad_LeftBumper,    { Gamepad_LeftBumper,    "Left Bumper" } },
        { Gamepad_RightBumper,   { Gamepad_RightBumper,   "Right Bumper" } },

        { Gamepad_Back,          { Gamepad_Back,          "Back" } },
        { Gamepad_Start,         { Gamepad_Start,         "Start" } },
        { Gamepad_Guide,         { Gamepad_Guide,         "Guide" } },

        { Gamepad_LeftThumb,     { Gamepad_LeftThumb,     "Left Thumb" } },
        { Gamepad_RightThumb,    { Gamepad_RightThumb,    "Right Thumb" } },

        { Gamepad_DpadUp,        { Gamepad_DpadUp,        "D-Pad Up" } },
        { Gamepad_DpadRight,     { Gamepad_DpadRight,     "D-Pad Right" } },
        { Gamepad_DpadDown,      { Gamepad_DpadDown,      "D-Pad Down" } },
        { Gamepad_DpadLeft,      { Gamepad_DpadLeft,      "D-Pad Left" } },

        { Gamepad_LeftX,         { Gamepad_LeftX,         "Left Stick X" } },
        { Gamepad_LeftY,         { Gamepad_LeftY,         "Left Stick Y" } },
        { Gamepad_RightX,        { Gamepad_RightX,        "Right Stick X" } },
        { Gamepad_RightY,        { Gamepad_RightY,        "Right Stick Y" } },
        { Gamepad_LeftTrigger,   { Gamepad_LeftTrigger,   "Left Trigger" } },
        { Gamepad_RightTrigger,  { Gamepad_RightTrigger,  "Right Trigger" } }
    };
}

const std::vector<InputInfo>& InputRegistry::GetInputs()
{
    return inputInfos;
}


// This method returns a reference to temporary value
InputInfo InputRegistry::GetInputInfo(const InputCode& code)
{
    if(inputInfoLookup.contains(code))
    {
        return inputInfoLookup.at(code);
    }
    return { Invalid, "" };
}