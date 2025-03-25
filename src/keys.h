#ifndef KEYS_H_
#define KEYS_H_

int PRGM_GetKey();

void keyupdate(void);

int keydownlast(int basic_keycode);
int keydownhold(int basic_keycode);

int keyPressed(int basic_keycode);

int key_press(int keycode);

#endif