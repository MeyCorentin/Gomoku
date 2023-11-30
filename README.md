 ██████╗  ██████╗ ███╗   ███╗ ██████╗ ██╗  ██╗██╗   ██╗
██╔════╝ ██╔═══██╗████╗ ████║██╔═══██╗██║ ██╔╝██║   ██║
██║  ███╗██║   ██║██╔████╔██║██║   ██║█████╔╝ ██║   ██║
██║   ██║██║   ██║██║╚██╔╝██║██║   ██║██╔═██╗ ██║   ██║
╚██████╔╝╚██████╔╝██║ ╚═╝ ██║╚██████╔╝██║  ██╗╚██████╔╝
 ╚═════╝  ╚═════╝ ╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ 
 
## Install prerequises

Linux :
```
sudo pacman -Sy cmake
```

Windows :
```

```

### Bonus prerequises : 
```
wget https://github.com/SFML/SFML/archive/2.6.1.tar.gz
tar -xzf 2.6.1.tar.gz
cd SFML-2.6.1
mkdir build
cd build
cmake ..
sudo make install
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
```

## Compilation

Linux :
```
git clone git@github.com:EpitechPromo2026/B-AIA-500-LYN-5-1-gomoku-nathan.donat-filliod.git
cd B-AIA-500-LYN-5-1-gomoku-nathan.donat-filliod
make
```

Windows :
```
git clone https://github.com/EpitechPromo2026/B-AIA-500-LYN-5-1-gomoku-nathan.donat-filliod.git
cd B-AIA-500-LYN-5-1-gomoku-nathan.donat-filliod
make
```

## Launch the brain

Linux :
```
./pbrain-gomoku-ai
```

Windows :
```
./pbrain-gomoku-ai.exe
```

# Protocol 

## Manager commands

Name command | Description | Arguments | Brain answers
------------ | ----------- | --------- | -------------
START | Brain create an empty board | [size]: The size of the board | OK or ERROR [message]
TURN | Coordinates of the opponent move | [x]: Position x [y]: Position y | Brain move (x,y)
BEGIN | Inform brain that is supposed to start | - | Brain move (x,y)
BOARD | This command imposes entirely new playing field | - |
INFO | The manager send informations to the brain | [key] [value] |
END | Inform the brain that he must terminate | - |
ABOUT | The brain is expected to send some information about itself | - |
RECSTART | This command is similar to START, but the board is rectangular | [width] [height] |
RESTART | Restart the game | - |
TAKEBACK | This command is used to undo last move | [x] [y] |
PLAY | It imposes move [X],[Y] to the brain | [x] [y] |
SWAP2BOARD | This command is used to deal with the opening stage of Swap2 rule | - |

## Brain commands

Name command | Description | Arguments
------------ | ----------- | ---------
UNKNOWN | Send this command if brain receive an unknown command | [error message] |
ERROR | Send this command if brain receive an invalid command | [error message] |
MESSAGE | Response to a command send to all players | [message] |
DEBUG | Response to a command | [message] |
SUGGEST | Suggest a position | [x] [y] |
