// By Tedezed

#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <linux/input.h>

using namespace std;

/*
Sources:
- https://stackoverflow.com/questions/9015506/how-to-identify-shift-ctrl-keys-were-pressed-in-the-linux-world-without-using-g
- https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h

*/

int main (int argc, char *argv[])
{
  ofstream brightness; // Write
  bool led_state = true;

  struct input_event ev;
  FILE *kbd = fopen("/dev/input/by-id/usb-SINO_WEALTH_USB_KEYBOARD-event-kbd", "r");
  
  // Check argument for /sys/class/leds/input
  if (argc < 2 || (argc > 2))
  {
      cerr << "Need one argument" << endl;
      return -1;
  }
  else
  {
      cout <<  "input: " << argv[1] << endl;
  }
  string led_path = "/sys/class/leds/input" + string(argv[1]) + "::scrolllock/brightness";
  cout << led_path << endl;

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
    
    std::this_thread::sleep_for(std::chrono::nanoseconds(10000000));
  }
  
  fclose(kbd);
  return 0;
}