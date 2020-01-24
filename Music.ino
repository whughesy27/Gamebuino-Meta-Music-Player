#include <Gamebuino-Meta.h>


const char* entries[] = {
  ""

};

const char* tracks[] = {
  ""

};

bool    menuUp = false;
int8_t  track  = -1;
uint8_t entry  = 0;

void menu() {
  if (!menuUp) {
    menuUp = true;
    entry = gb.gui.menu("Songs", entries, 0);
    menuUp = false;

    gb.display.clear();

    gb.display.fill(BROWN);
    track = gb.sound.play(tracks[entry]);
    gb.gui.popup("Music Playing", 50);
    gb.display.printf("Now Playing:\n\n%s", entries[entry]);
  }
}


void setup() {
  gb.begin();
  menu();
}


void loop() {
  while(!gb.update());

  if (gb.buttons.pressed(BUTTON_B)) {
    if (track != -1) {
      gb.sound.stop(track);
      track = -1;
      gb.gui.popup("Music Stopped", 50);
      gb.sound.playTick();
    }

    menu();
  }

  //if (gb.buttons.pressed(BUTTON_LEFT))  gb.gui.popup("Button left", 50);
  //if (gb.buttons.pressed(BUTTON_RIGHT)) gb.gui.popup("Button right", 50);
  
  if (!menuUp) {
    if (gb.buttons.pressed(BUTTON_RIGHT)) {
      entry = entry + 1;
      if (entry > 0) entry = 0;
      gb.display.clear();
      gb.display.fill(BROWN);
      gb.gui.popup("Next Track", 50);
      gb.display.printf("Now Playing:\n\n%s", entries[entry]);
      if (track != -1) {
      gb.sound.stop(track);
      track = -1;
      track = gb.sound.play(tracks[entry]);
    }

    }

    if (gb.buttons.pressed(BUTTON_LEFT)) {
      if (entry == 0) entry = 0; else entry = entry - 1;
      gb.display.clear();
      gb.display.fill(BROWN);
      gb.gui.popup("Previous Track", 50);
      gb.display.printf("Now Playing:\n\n%s", entries[entry]);
      if (track != -1) {
      gb.sound.stop(track);
      track = -1;
      track = gb.sound.play(tracks[entry]);
    }
  }
}
}
