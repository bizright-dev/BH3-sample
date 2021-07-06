This repository contains following sample source program.

・Sample source program using a general-purpose switch.

・Sample source program using general-purpose LEDs.

These programs are intended to run on BH3 manufactured by BiZright Technology Inc.

![DSCF0562](./DSCF0562.JPG)


### General switch

Build and run:

```
% gcc -lwiringPi -o bhButton bhButton.c
% sudo ./bhButton
```

Pyton script:					

```
% sudo python bhButton.py
```



### General LED

Build and run:			

```
% gcc -lwiringPi -o bhLED bhLED.c
% sudo ./bhLED
```

Pyton script:					

```
% sudo python bhLED.py
```


