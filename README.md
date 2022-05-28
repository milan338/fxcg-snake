# fx-CG Snake

![issues](https://img.shields.io/github/issues/milan338/fxcg-snake?style=flat-square)
![release](https://img.shields.io/github/v/release/milan338/fxcg-snake?include_prereleases&style=flat-square)
![downloads](https://img.shields.io/github/downloads/milan338/fxcg-snake/total?style=flat-square)
![license](https://img.shields.io/github/license/milan338/fxcg-snake?style=flat-square)

###  ***Snake, on your graphics calculator***

## Installation

Download a binary from the [releases page](https://github.com/milan338/fxcg-snake/releases). Then connect your fx-cg graphics calculator to your pc with the USB cable. A popup will appear asking to select the connection mode. Choose `USB Flash : [F1]` - it should show up in your file explorer. Drag the downloaded binary into the root directory of the calculator flash. **Eject** the calculator from your computer, **then** unplug the cable. Snake should now appear on your home screen.

## Building it yourself

### Windows

First clone the repo

```
git clone https://github.com/milan338/fxcg-snake.git
```

Download the [libfxcg sdk](https://github.com/Jonimoose/libfxcg). In the fxcg-snake repo, run `setup.py` and select your downloaded libfxcg sdk directory. Then, run `.\make.bat`. That's it. The output file `snake.g3a` should be inside the `dist` directory.

## Media

![screenshot](/media/screenshot.png)

## License

[MIT License](/LICENSE)
