# sSinplotter
A simple tool to render sine waves I made to learn C and SDL2. Lacks any practical use.  

The text is not rendered in a font, rather hard coded in an atlas (View /img/atlas.png). The atlas then is converted to a C header to use straight from code.  

The Makefile is configured for static linking, so the output is (Almost) always a standalone file.
# Building
```bash
git clone https://github.com/danilaxila3/sSinplotter.git
cd sSinplotter
make
./build/main
```