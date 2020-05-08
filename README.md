# CMSTROM led control for Linux

Code designed for this specific keyboard, but easily modifiable for others, modify variables: `led_path` and `kbd`
<img width="80" src="./img/cm-storm-devastator-teclado-raton.jpg" />

### Sources:

- https://stackoverflow.com/questions/9015506/how-to-identify-shift-ctrl-keys-were-pressed-in-the-linux-world-without-using-g
- https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h

### Install

- Build: `g++ cmstrom_led.cpp -o key -lncurses`
- Install: `sudo cp cmstrom_led /bin/`

##### Option 1 - Create: `/etc/systemd/system/cmstrom_led.service`
```
iption=/bin/cmstrom_led
ConditionPathExists=/bin/cmstrom_led
 
[Service]
Type=simple
ExecStart=/bin/cmstrom_led
TimeoutSec=0
StandardOutput=tty
RemainAfterExit=yes
SysVStartPriority=99
 
[Install]
WantedBy=multi-user.target
```

Enable unit: `sudo systemctl enabled cmstrom_led`


##### Option 2 - Create: `/etc/rc3.d/S01cmstrom_led.sh`
```
#!/bin/sh -e
/bin/cmstrom_led &
exit 0
```

Permissions: `chmod +x /etc/rc3.d/cmstrom_led.sh`
