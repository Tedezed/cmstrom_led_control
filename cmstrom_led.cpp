// By Tedezed

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <linux/input.h>

using namespace std;

/*

- Build: g++ cmstrom_led.cpp -o key -lncurses
- Install: sudo cp cmstrom_led /bin/
- Create: /etc/rc.local

#!/bin/sh -e
cmstrom_led
exit 0

*/

int main (int argc, char *argv[])
{
  ofstream brightness; // Write
  bool led_state = true;
  string led_path = "/sys/class/leds/input6::scrolllock/brightness";

  struct input_event ev;
  FILE *kbd = fopen("/dev/input/by-id/usb-SINO_WEALTH_USB_KEYBOARD-event-kbd", "r");
  
  while (fread(&ev, sizeof(ev), 1, kbd) == 1)
  {
    if (ev.type == EV_KEY && (ev.code == KEY_SCROLLLOCK && ev.value == 0))
    {
        //cout << led_state << endl;
        if (led_state)
        {
            led_state = false;
        }
        else
        {
            led_state = true;
        }
    }
    brightness.open(led_path);
    if (led_state)
    {
        brightness << "0";
    }
    else
    {
        brightness << "1";
    }
    brightness.close();
    
  }
  
  fclose(kbd);
  return 0;
}