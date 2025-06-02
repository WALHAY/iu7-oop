#pragma once

#include <Controller.hpp>

constexpr int OPENING_TIME = 1500;
constexpr int MOVE_TIME = 1500;
constexpr int OPENED_TIME = 2500;

constexpr int INITIAL_FLOOR = 1;
constexpr int FLOORS = 10;

#define FLOOR_INDICATOR_STYLESHEET                                                                                     \
    R"(
/* Style for radio buttons */
QRadioButton {
    spacing: 5px;  /* Space between radio button and text */
}

QRadioButton::indicator {
    width: 30px;
    height: 30px;
    border: 2px solid #555;
    border-radius: 15px;  /* Circular buttons */
    background: #ddd;
}

/* Selected floor (checked state) - MUST COME AFTER DEFAULT INDICATOR */
QRadioButton::indicator:checked {
    background: #4CAF50;  /* Green for selected floor */
    border: 2px solid #388E3C;
}
)"
