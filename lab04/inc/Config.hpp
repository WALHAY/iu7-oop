#ifndef TIMERINFO_HPP
#define TIMERINFO_HPP

constexpr int DOOR_OPENING_CLOSING_TIME = 1500;
constexpr int ONE_FLOOR_MOVING_TIME = 1500;
constexpr int DOOR_WAITING_TIME = 2500;

constexpr int INITIAL_FLOOR = 1;
constexpr int FLOORS = 8;

#define FLOOR_INDICATOR_STYLESHEET R"(
QRadioButton {
spacing: 5px; /* Расстояние между кружком и текстом */
color: #333333; /* Цвет текста */
}

/* Активная выбранная кнопка (ярко-зеленая) */
QRadioButton::indicator:checked {
background-color: #2ecc71;
border: 2px solid #27ae60;
border-radius: 7px;
width: 14px;
height: 14px;
}

/* Невыбранная кнопка (прозрачная с серой границей) */
QRadioButton::indicator:unchecked {
background-color: transparent;
border: 2px solid #95a5a6;
border-radius: 7px;
width: 14px;
height: 14px;
}

/* Отключенная НО выбранная кнопка (зеленая, но бледнее) */
QRadioButton::indicator:disabled:checked {
background-color: #a5d6a7; /* Светло-зеленый */
border: 2px solid #81c784; /* Граница светлее */
border-radius: 7px;
width: 14px;
height: 14px;
}

/* Отключенная + невыбранная кнопка (серый кружок) */
QRadioButton::indicator:disabled:unchecked {
background-color: transparent;
border: 2px solid #bdc3c7; /* Светло-серая граница */
border-radius: 7px;
width: 14px;
height: 14px;
}

/* Текст отключенной кнопки (серый, но не "размытый") */
QRadioButton:disabled {
color: #7f8c8d;
}
)"

#endif //TIMERINFO_HPP
