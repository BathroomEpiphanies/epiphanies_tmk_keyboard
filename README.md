Epiphanies TMK Keyboard Firmware Collection
================================

This repository includes keyboard and controller firmware projects
built with [`tmk_core`][tmk_core] keyboard library.

The latest source code for the core library is available here:
<http://github.com/tmk/tmk_keyboard>

The latest source code for the individual projects is available here:
<https://github.com/BathroomEpiphanies/epiphanies_tmk_keyboard>

Projects
--------
### keyboard
* [The Sane Matrix](keyboard/sane_matrix_20151027/) - [geekhack forum](https://geekhack.org/index.php?topic=78059.0)
* [The Firefly](keyboard/firefly_20141024/)         - [geekhack forum](https://geekhack.org/index.php?topic=74907.0)

### controller
* [Black Petal 2013](controller/black_petal_20131001/)    - [geekhack forum](https://geekhack.org/index.php?topic=46700.0)
* [Cool Talk 2015](controller/cool_talk_20151102/)        - [geekhack forum](https://geekhack.org/index.php?topic=46700.0)
* [Frosty Flake 2013](controller/frosty_flake_20130602/)  - [geekhack forum](https://geekhack.org/index.php?topic=46700.0)
* [Frosty Flake 2014](controller/frosty_flake_20140521/)  - [geekhack forum](https://geekhack.org/index.php?topic=46700.0)
* [Ghost Squid 2014](controller/ghost_squid_20140518/)    - [geekhack forum](https://geekhack.org/index.php?topic=46700.0)
* [Hid Liberation Device](controller/hid_liber_20120911/) - [geekhack forum](https://geekhack.org/index.php?topic=46700.0)
* [Kitten Paw 2013](controller/kitten_paw_20130602/)      - [geekhack forum](https://geekhack.org/index.php?topic=46700.0)
* [Kitten Paw 2016](controller/kitten_paw_20160418/)      - [geekhack forum](https://geekhack.org/index.php?topic=46700.0)
* [Pegasus Hoof 2013](controller/pegasus_hoof_20131001/)  - [geekhack forum](https://geekhack.org/index.php?topic=46700.0)
* [Pegasus Hoof 2015](controller/pegasus_hoof_20150108/)  - [geekhack forum](https://geekhack.org/index.php?topic=46700.0)



License
-------
**GPLv2** or later. Some protocol files are under **Modified BSD License**.

Third party libraries like LUFA, PJRC and V-USB have their own license respectively.



Build Firmware and Program Controller
-------------------------------------
See [tmk_core/doc/build.md](tmk_core/doc/build.md).



Change your keymap
------------------
See [tmk_core/doc/keymap.md](tmk_core/doc/keymap.md).



Magic Commands
--------------
To see help press `Magic` + `H`.

`Magic` key combination is `LShift` + `RShift` in many projects, but `Power` key on ADB converter.
`Magic` keybind can be vary on each project, check `config.h` in project directory.

Following commands can be also executed with `Magic` + key. In console mode `Magic` keybind is not needed.

    ----- Command Help -----
    c:      enter console mode
    d:      toggle debug enable
    x:      toggle matrix debug
    k:      toggle keyboard debug
    m:      toggle mouse debug
    v:      print device version & info
    t:      print timer count
    s:      print status
    e:	    print eeprom config
    n:	    toggle NKRO
    0/F10:  switch to Layer0
    1/F1:   switch to Layer1
    2/F2:   switch to Layer2
    3/F3:   switch to Layer3
    4/F4:   switch to Layer4
    PScr:   power down/remote wake-up
    Caps:   Lock Keyboard(Child Proof)
    Paus:   jump to bootloader



Boot Magic Configuration - Virtual DIP Switch
---------------------------------------------
Boot Magic are executed during boot up time. Press Magic key below then plug in keyboard cable.
Note that you must use keys of **Layer 0** as Magic keys. These settings are stored in EEPROM so that retain your configure over power cycles.

To avoid configuring accidentally additive salt key `KC_SPACE` also needs to be pressed along with the following configuration keys. The salt key is configurable in `config.h`. See [tmk_core/common/bootmagic.h](tmk_core/common/bootmagic.h).

#### General
- Skip reading EEPROM to start with default configuration(`ESC`)
- Clear configuration stored in EEPROM to reset configuration(`Backspace`)

#### Bootloader
- Kick up Bootloader(`B`)

#### Debug
- Debug enable(`D`)
- Debug matrix enable(`D`+`X`)
- Debug keyboard enable(`D`+`K`)
- Debug mouse enable(`D`+`M`)

#### Keymap
- Swap Control and CapsLock(`Left Control`)
- Change CapsLock to Control(`Caps Lock`)
- Swap LeftAlt and Gui(`Left Alt`)
- Swap RightAlt and Gui(`Right Alt`)
- Disable Gui(`Left Gui`)
- Swap Grave and Escape(`Grave`)
- Swap BackSlash and BackSpace(`Back Slash`)
- Enable NKRO on boot(`N`)

#### Default Layer
- Set Default Layer to 0(`0`)
- Set Default Layer to 1(`1`)
- Set Default Layer to 2(`2`)
- Set Default Layer to 3(`3`)
- Set Default Layer to 4(`4`)
- Set Default Layer to 5(`5`)
- Set Default Layer to 6(`6`)
- Set Default Layer to 7(`7`)



Mechanical Locking support
--------------------------
This feature makes it possible for you to use mechanical locking switch for `CapsLock`, `NumLock`
or `ScrollLock`. To enable this feature define these macros in `config.h` and use `KC_LCAP`, `KC_LN
UM` or `KC_LSCR` in keymap for locking key instead of normal `KC_CAPS`, `KC_NLCK` or `KC_SLCK`. Res
ync option tries to keep switch state consistent with keyboard LED state.

    #define LOCKING_SUPPORT_ENABLE
    #define LOCKING_RESYNC_ENABLE



Start Your Own Project
-----------------------
1. Add `tmk_core` into your repository using `git submodule` or `git subtree`.
2. Copy files from `tmk_keybaord` or other project similar to yours
3. Edit those files to support your keyboard.

See these as examples.
- https://github.com/tmk/infinity_ergodox
- https://github.com/tmk/whitefox



Debugging
--------
Use PJRC's `hid_listen` to see debug messages. You can use xprintf() to display debug info, see `tmk_core/common/xprintf.h`.

- https://www.pjrc.com/teensy/hid_listen.html



Files and Directories
-------------------
### Top
* keyboard/     - keyboard projects
* controller/   - keyboard controller projects
* tmk_core/     - core library
* tmk_core/doc/ - documents
