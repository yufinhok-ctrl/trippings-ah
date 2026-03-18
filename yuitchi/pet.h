#ifndef PET_H
#define PET_H

class Pet {
public:
    Pet();
    void update(unsigned long dt); // dt in milliseconds
    void feed();
    int getHunger();
    int getHappiness();
    const char* getStateString(); // for display: e.g., "Happy", "Hungry", etc.

private:
    int hunger;
    int happiness;
    unsigned long lastUpdate;
};

#endif