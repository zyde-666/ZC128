//pc.cpp
#include "../include/pc.h"

PC::PC() : value(0) {}

int PC::get() const {
    return value;
}

void PC::set(int val) {
    value = val;
}

void PC::increment() {
    ++value;
}

void PC::decrement() {
    --value;
}

void PC::res() {
    value = 0;
}

void PC::add(int val) {
    value += val;
}

bool PC::setsafe(int val) {
    if (val < 0) return false; // Prevent setting a negative value
    value = val;
    return true;
}

void PC::rollback(int val) {
    if (val < 0) return; // Prevent rolling back to a negative value
    value -= val;
    if (value < 0) value = 0; // Ensure value does not go below zero
}
