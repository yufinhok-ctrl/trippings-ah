#include "pet.h"

Pet::Pet() : hunger(50), happiness(50), lastUpdate(0) {}

void Pet::update(unsigned long dt) {
    lastUpdate += dt;
    // Every 10 seconds, decrease happiness and increase hunger
    if (lastUpdate >= 10000) {
        if (hunger + 5 > 100) hunger = 100;
        else hunger = hunger + 5;
        if (happiness - 5 < 0) happiness = 0;
        else happiness = happiness - 5;
        lastUpdate = 0;
    }
}

void Pet::feed() {
    if (hunger - 20 < 0) hunger = 0;
    else hunger = hunger - 20;
    if (happiness + 10 > 100) happiness = 100;
    else happiness = happiness + 10;
}

int Pet::getHunger() {
    return hunger;
}

int Pet::getHappiness() {
    return happiness;
}

const char* Pet::getStateString() {
    if (happiness > 70 && hunger < 30) {
        return "Happy";
    } else if (hunger > 70) {
        return "Hungry";
    } else if (happiness < 30) {
        return "Sad";
    } else {
        return "Okay";
    }
}