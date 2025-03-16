#include "types.h"

#include "upgrades.h"

void unlock_upgrades(struct CookieData *data) {

    // cursor upgrades

    if (data->buildings[TYPE_CURSOR].owned >= 1) {
        data->upgrades_unlocked[0] = true;
        data->upgrades_unlocked[1] = true;
    }
    if (data->buildings[TYPE_CURSOR].owned >= 10)
        data->upgrades_unlocked[2] = true;
    if (data->buildings[TYPE_CURSOR].owned >= 25)
        data->upgrades_unlocked[3] = true;

    if (data->upgrades[3]) {
        if (data->buildings[TYPE_CURSOR].owned >= 50)
            data->upgrades_unlocked[4] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 100)
            data->upgrades_unlocked[5] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 150)
            data->upgrades_unlocked[6] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 200)
            data->upgrades_unlocked[7] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 250)
            data->upgrades_unlocked[8] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 300)
            data->upgrades_unlocked[9] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 350)
            data->upgrades_unlocked[10] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 400)
            data->upgrades_unlocked[11] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 450)
            data->upgrades_unlocked[12] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 500)
            data->upgrades_unlocked[13] = true;
        if (data->buildings[TYPE_CURSOR].owned >= 550)
            data->upgrades_unlocked[14] = true;
    }

    // other building upgrades

    for (int i = 1; i < 20; i++) {
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

    // mouse upgrades

    if (data->handmade_cookies >= 1E3)
        data->upgrades_unlocked[(TYPE_MOUSE * 15)] = true;
    if (data->handmade_cookies >= 1E5)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 1] = true;
    if (data->handmade_cookies >= 1E7)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 2] = true;
    if (data->handmade_cookies >= 1E9)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 3] = true;
    if (data->handmade_cookies >= 1E11)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 4] = true;
    if (data->handmade_cookies >= 1E13)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 5] = true;
    if (data->handmade_cookies >= 1E15)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 6] = true;
    if (data->handmade_cookies >= 1E17)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 7] = true;
    if (data->handmade_cookies >= 1E19)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 8] = true;
    if (data->handmade_cookies >= 1E21)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 9] = true;
    if (data->handmade_cookies >= 1E23)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 10] = true;
    if (data->handmade_cookies >= 1E25)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 11] = true;
    if (data->handmade_cookies >= 1E27)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 12] = true;
    if (data->handmade_cookies >= 1E29)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 13] = true;
    if (data->handmade_cookies >= 1E31)
        data->upgrades_unlocked[(TYPE_MOUSE * 15) + 14] = true;

    // golden cookie upgrades

    if (data->gold_click_count >= 7)
        data->upgrades_unlocked[(TYPE_GOLDEN * 15)] = true;
    if (data->gold_click_count >= 27)
        data->upgrades_unlocked[(TYPE_GOLDEN * 15) + 1] = true;
    if (data->gold_click_count >= 77)
        data->upgrades_unlocked[(TYPE_GOLDEN * 15) + 2] = true;
}

void enable_upgrade(struct CookieData *data, int id) {

    uint8_t building_id = id / 15;

    if (id == 3)
        // Thousand fingers
        data->buildings[TYPE_CURSOR].modifier += 0.1;
    else if (id == 4)
        // Million fingers
        data->buildings[TYPE_CURSOR].modifier *= 5.0;
    else if (id == 5)
        // Billion fingers
        data->buildings[TYPE_CURSOR].modifier *= 10.0;
    else if (id > 5 && id <= 14)
        // Trillion - Undecillion fingers
        data->buildings[TYPE_CURSOR].modifier *= 20.0;
    else if (id < 3 || (id > 14 && id < 300))
        // multiply building cps by 2
        data->buildings[building_id].multiplier *= 2.0;
    else if (id >= 300 && id < 315)
        // Clicking gains +1% of your CpS.
        data->buildings[TYPE_CURSOR].percent_cps += 0.01;
    else if (id >= 315 && id < 317) {
        // Golden cookies appear twice as often and last twice as long on screen.
    } else {
        // Golden cookie effects last twice as long.
    }
}