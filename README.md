# CMSTROM led control for Linux

Code designed for this specific keyboard **Cooler Master CM Storm Devastator**, but easily modifiable for others, modify variables: `led_path` and `kbd`

<img src="./img/cm-storm-devastator-teclado-raton.jpg" />

### Install

- Build: `g++ cmstrom_led.cpp -o cmstrom_led -lncurses`
- Check that it works correctly: `./cmstrom_led`
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
User=root
ExecStart=/bin/bash -c "/bin/cmstrom_led $(ls /sys/class/leds/ | grep scroll | cut -d ':' -f1 | sed 's/input//g')"
TimeoutSec=0
StandardOutput=tty
RemainAfterExit=yes
SysVStartPriority=99
 
[Install]
WantedBy=multi-user.target
```

Reload units: `systemctl daemon-reload`
Enable unit: `sudo systemctl enable cmstrom_led && systemctl start cmstrom_led`


##### Option 2 - Create: `/etc/rc3.d/S01cmstrom_led.sh`
```
#!/bin/sh -e
/bin/bash -c "/bin/cmstrom_led $(ls /sys/class/leds/ | grep scroll | cut -d ':' -f1 | sed 's/input//g')" &
exit 0
```

Permissions: `chmod +x /etc/rc3.d/cmstrom_led.sh`

### Bonus

You can see which key you are pressing, uncomment the following line: https://github.com/Tedezed/cmstrom_led_control/blob/master/cmstrom_led.cpp#L33
