# meat-arena
A server-client multiplayer game inspired by Jump 'n Bump

This repository is the client, the server is at: https://github.com/jacekmcp/jumpServer.git


# Usage
This program requires SDL2, SDL2-image and SDL2-ttf.
You can get them by using:
```
sudo apt install libsdl2-dev, libsdl2-image-dev, libsdl2-ttf-dev
```
(You can probably use the non-dev versions when just running the program, but I'm giving the libraries I used just to be safe)

Clone the repository:
```
git clone https://github.com/Loqaritm/meat-arena.git
```
**Local:** If you want to play locally (wsad, arrows, ijkl, numpad) skip the next step and don't worry about setting up ip and port.

**Network:**
Pull the correct branch:
```
cd meat-arena
git pull origin network
```
Run the program:
```
./client.exe
```
**Important for network version!** Before starting the program, navigate to Client/Config/ and open config.txt.
Be sure to put the proper ip address and port of the server into the file (each on different line).

# Examples

<p float="center">
  <img src="https://raw.githubusercontent.com/Loqaritm/meat-arena/network/Examples/example1.png" width="40%" /> 
</p>

# Credits

The tileset used for the level graphics is cheekily taken from Cave Story, as there was not enough time to make my own. It will maybe be updated to original art in the future, when I have time for it. 
I hope You will forgive me Pixel.

All player sprites are done by me. As simple as they are, you can use them anywhere you want, though I would appreciate a message. All the spritesheets and gimp files for players are located in Client/Content/Sprites/ .
