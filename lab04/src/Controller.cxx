#include "../inc/Controller.hpp"

Controller::Controller(QObject *parent) : QObject(parent), state(WAITING) {}
