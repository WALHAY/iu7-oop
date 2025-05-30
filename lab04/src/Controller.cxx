#include "../inc/Controller.hpp"

Controller::Controller(QObject *parent) : QObject(parent), state(WAITING) {}

void Controller::handleRequest() {}
void Controller::handleMove() {}
void Controller::handleStop() {}
void Controller::handleWaiting() {}
