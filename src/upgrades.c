#include "types.h"

#include "upgrades.h"

void unlock_upgrades(struct CookieData *data) {

    // cursor upgrades
    if (data->buildings[BUILDING_CURSOR].owned >= 1) {
        data->upgrades_unlocked[0] = true;
        data->upgrades_unlocked[1] = true;
    }
    if (data->buildings[BUILDING_CURSOR].owned >= 10)
        data->upgrades_unlocked[2] = true;
    if (data->buildings[BUILDING_CURSOR].owned >= 25)
        data->upgrades_unlocked[3] = true;
    if (data->buildings[BUILDING_CURSOR].owned >= 50)
        data->upgrades_unlocked[4] = true;
    if (data->buildings[BUILDING_CURSOR].owned >= 100)
        data->upgrades_unlocked[5] = true;
    if (data->buildings[BUILDING_CURSOR].owned >= 150)
        data->upgrades_unlocked[6] = true;
    if (data->buildings[BUILDING_CURSOR].owned >= 200)
        data->upgrades_unlocked[7] = true;
    if (data->buildings[BUILDING_CURSOR].owned >= 250)
        data->upgrades_unlocked[8] = true;
    if (data->buildings[BUILDING_CURSOR].owned >= 300)
        data->upgrades_unlocked[9] = true;
    if (data->buildings[BUILDING_CURSOR].owned >= 350)
        data->upgrades_unlocked[10] = true;
    if (data->buildings[BUILDING_CURSOR].owned >= 400)
        data->upgrades_unlocked[11] = true;
    if (data->buildings[BUILDING_CURSOR].owned >= 450)
        data->upgrades_unlocked[12] = true;
    if (data->buildings[BUILDING_CURSOR].owned >= 500)
        data->upgrades_unlocked[13] = true;
    if (data->buildings[BUILDING_CURSOR].owned >= 550)
        data->upgrades_unlocked[14] = true;


    for (int i = 1; i < 20; i++) {
        // other upgrades
        if (data->buildings[i].owned >= 1)
            data->upgrades_unlocked[(i * 15)] = true;
        if (data->buildings[i].owned >= 5)
            data->upgrades_unlocked[(i * 15) + 1] = true;
        if (data->buildings[i].owned >= 25)
            data->upgrades_unlocked[(i * 15) + 2] = true;
        if (data->buildings[i].owned >= 50)
            data->upgrades_unlocked[(i * 15) + 3] = true;
        if (data->buildings[i].owned >= 100)
            data->upgrades_unlocked[(i * 15) + 4] = true;
        if (data->buildings[i].owned >= 150)
            data->upgrades_unlocked[(i * 15) + 5] = true;
        if (data->buildings[i].owned >= 200)
            data->upgrades_unlocked[(i * 15) + 6] = true;
        if (data->buildings[i].owned >= 250)
            data->upgrades_unlocked[(i * 15) + 7] = true;
        if (data->buildings[i].owned >= 300)
            data->upgrades_unlocked[(i * 15) + 8] = true;
        if (data->buildings[i].owned >= 350)
            data->upgrades_unlocked[(i * 15) + 9] = true;
        if (data->buildings[i].owned >= 400)
            data->upgrades_unlocked[(i * 15) + 10] = true;
        if (data->buildings[i].owned >= 450)
            data->upgrades_unlocked[(i * 15) + 11] = true;
        if (data->buildings[i].owned >= 500)
            data->upgrades_unlocked[(i * 15) + 12] = true;
        if (data->buildings[i].owned >= 550)
            data->upgrades_unlocked[(i * 15) + 13] = true;
        if (data->buildings[i].owned >= 600)
            data->upgrades_unlocked[(i * 15) + 14] = true;
    }
}

void enable_upgrade(struct CookieData *data, int id) {

    uint8_t building_id = id / 15;

    switch (id) {
        case 3:
            // Thousand fingers
            data->buildings[building_id].modifier += 0.1;
            break;
        case 4:
            data->buildings[building_id].modifier *= 5;
            break;
        case 5:
            data->buildings[building_id].modifier *= 10;
            break;
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            data->buildings[building_id].modifier *= 20;
            break;
        default:
            // multiply building cps by 2
            data->buildings[building_id].multiplier *= 2;
            break;
    }

    // if (id == 3)
    //     // Thousand fingers
    //     data->buildings[building_id].modifier += 0.1;
    // else if (id == 4)
    //     // Million fingers
    //     data->buildings[building_id].modifier *= 5;
    // else if (id == 5)
    //     // Billion fingers
    //     data->buildings[building_id].modifier *= 10;
    // else if (id > 5 && id <= 14)
    //     // Trillion - Undecillion fingers
    //     data->buildings[building_id].modifier *= 20;
    // else if (id < 3 || id > 14)
    //     // multiply building cps by 2
    //     data->buildings[building_id].multiplier *= 2;

    //         data->buildings[upgrades[id].building].multiplier *= upgrades[id].modifier;
    //         break;
    //     case MODE_ADD:
    //         data->buildings[upgrades[id].building].modifier += upgrades[id].modifier;
    //         break;
    //     case MODE_MODIFY:
    //         data->buildings[upgrades[id].building].modifier *= upgrades[id].modifier;
    //         break;
    //     case MODE_CPS_PERCENT:
    //         data->buildings[upgrades[id].building].percent_cps += upgrades[id].modifier;
    //         break;
    //     default:
    //         break;
    // }
}