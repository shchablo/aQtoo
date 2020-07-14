# Armo-Qt-OmniOrb (aQtoo)
 A simple example of a client-server app. This app base on eg_2 (https://github.com/liangqi/qt-omniorb) 

#### SYSTEM REQUIREMENTS:
  - Linux (ncurses)
  - QMAKE (https://www.qt.io/)
  - OMNIORB (http://omniorb.sourceforge.net/) 

#### HOW TO BUILD:
```sh
$ export OMNIORB_PATH=/path/to/omniorb
$ mkdir build
$ cd build
$ qmake ..
$ make
```
#### HOW TO RUN:
```sh
$ <first terminal>
$ cd /path/to/project/aQtoo/bin
$  ./server
$  IOR:0100...00
$  <second terminal>
$  cd /path/to/project/aQtoo/bin
$  ./client IOR:0100...00
```
#### ANY QUESTIONS:

  shchablo@gmail.com
--------------------------------------------------------------------------------

![helloWorld](https://github.com/shchablo/aQtoo/blob/master/etc/helloWorld.gif)
