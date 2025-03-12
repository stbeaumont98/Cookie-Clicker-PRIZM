#include "types.h"

#include "upgrades.h"

void unlock_upgrades(struct CookieData data, struct Upgrade *upgrades) {
    if (data.buildings[0].owned >= 1) {
        upgrades[0].unlocked = true;
        upgrades[1].unlocked = true;
    }
    
    // cursor upgrades
    if (data.buildings[BUILDING_CURSOR].owned >= 10)
        upgrades[2].unlocked = true;
    if (data.buildings[BUILDING_CURSOR].owned >= 25)
        upgrades[3].unlocked = true;
    if (data.buildings[BUILDING_CURSOR].owned >= 50)
        upgrades[4].unlocked = true;
    if (data.buildings[BUILDING_CURSOR].owned >= 100)
        upgrades[5].unlocked = true;
    if (data.buildings[BUILDING_CURSOR].owned >= 150)
        upgrades[6].unlocked = true;
    if (data.buildings[BUILDING_CURSOR].owned >= 200)
        upgrades[43].unlocked = true;
    if (data.buildings[BUILDING_CURSOR].owned >= 250)
        upgrades[82].unlocked = true;
    if (data.buildings[BUILDING_CURSOR].owned >= 300)
        upgrades[109].unlocked = true;
    if (data.buildings[BUILDING_CURSOR].owned >= 350)
        upgrades[188].unlocked = true;
    if (data.buildings[BUILDING_CURSOR].owned >= 400)
        upgrades[189].unlocked = true;
    if (data.buildings[BUILDING_CURSOR].owned >= 450)
        upgrades[660].unlocked = true;
    if (data.buildings[BUILDING_CURSOR].owned >= 500)
        upgrades[764].unlocked = true;
    if (data.buildings[BUILDING_CURSOR].owned >= 550)
        upgrades[873].unlocked = true;
        
    // grandma upgrades
    if (data.buildings[BUILDING_GRANDMA].owned >= 1)
        upgrades[7].unlocked = true;
    if (data.buildings[BUILDING_GRANDMA].owned >= 5)
        upgrades[8].unlocked = true;
    if (data.buildings[BUILDING_GRANDMA].owned >= 25)
        upgrades[9].unlocked = true;

    // farm upgrades
    if (data.buildings[BUILDING_FARM].owned >= 1)
        upgrades[10].unlocked = true;
    if (data.buildings[BUILDING_FARM].owned >= 5)
        upgrades[11].unlocked = true;
    if (data.buildings[BUILDING_FARM].owned >= 25)
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