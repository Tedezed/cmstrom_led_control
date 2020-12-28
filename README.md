# CMSTROM led control for Linux

Code designed for this specific keyboard **Cooler Master CM Storm Devastator**, but easily modifiable for others, modify variables: `led_path` and `kbd`

<img src="./img/cm-storm-devastator-teclado-raton.jpg" />

### Install

- Build: `g++ cmstrom_led.cpp -o cmstrom_led -lncurses`
- Install: `sudo cp -f cmstrom_led /bin/`

Get input id:
```
$ ls /sys/class/leds/
input7::capslock  input7::numlock  input7::scrollloc
```

Check path:
```
$ ls /sys/class/leds/input7::scrolllock/brightness
/sys/class/leds/input7::scrolllock/brightness
```

Input is 7 in my case.

##### Option 1 - Create: `/etc/systemd/system/cmstrom_led.service`
```
iption=/bin/cmstrom_led
ConditionPathExists=/bin/cmstrom_led
 
[Service]
Type=simple
ExecStart=/bin/cmstrom_led 7
TimeoutSec=0
StandardOutput=tty
RemainAfterExit=yes
SysVStartPriority=99
 
[Install]
WantedBy=multi-user.target
```

Reload units: `systemctl daemon-reload`
Enable unit: `sudo systemctl enabled cmstrom_led && systemctl start cmstrom_led`


##### Option 2 - Create: `/etc/rc3.d/S01cmstrom_led.sh`
```
#!/bin/sh -e
/bin/cmstrom_led 7 &
exit 0
```

Permissions: `chmod +x /etc/rc3.d/cmstrom_led.sh`
