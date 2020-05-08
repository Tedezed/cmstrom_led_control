# CMSTROM led control for Linux

Build: `g++ cmstrom_led.cpp -o key -lncurses`

Install: `sudo cp cmstrom_led /bin/`

Create: `/etc/rc.local`
```
#!/bin/sh -e
cmstrom_led
exit 0
```

Sources

- https://stackoverflow.com/questions/9015506/how-to-identify-shift-ctrl-keys-were-pressed-in-the-linux-world-without-using-g
- https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h