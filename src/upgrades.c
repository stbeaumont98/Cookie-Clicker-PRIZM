#include "types.h"

#include "upgrades.h"

void unlock_upgrades(struct CookieData data, struct Upgrade *upgrades) {
    if (data.buildings[0].owned >= 1) {
        upgrades[0].unlocked = true;
        upgrades[1].unlocked = true;
    }
    
    if (data.buildings[0].owned >= 10)
        upgrades[2].unlocked = true;
    
    if (data.buildings[0].owned >= 25)
        upgrades[3].unlocked = true;

    if (data.buildings[0].owned >= 50)
        upgrades[4].unlocked = true;
    
    if (data.buildings[0].owned >= 100)
        upgrades[5].unlocked = true;
    
    if (data.buildings[0].owned >= 150)
        upgrades[6].unlocked = true;

    if (data.buildings[1].owned >= 1)
        upgrades[7].unlocked = true;

    if (data.buildings[1].owned >= 5)
        upgrades[8].unlocked = true;
    
    if (data.buildings[1].owned >= 25)
        upgrades[9].unlocked = true;

    if (data.buildings[2].owned >= 1)
        upgrades[10].unlocked = true;

    if (data.buildings[2].owned >= 5)
        upgrades[11].unlocked = true;

    if (data.buildings[2].owned >= 25)
        upgrades[12].unlocked = true;
}

void enable_upgrade(struct CookieData *data, int id) {
    switch(upgrades[id].mode) {
        case MODE_MULTIPLY:
            data->buildings[upgrades[id].building].multiplier *= upgrades[id].modifier;
            break;
        case MODE_MODIFY:
            data->buildings[upgrades[id].building].modifier *= upgrades[id].modifier;
            break;
        default:
            break;
    }
}