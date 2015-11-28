# tic-tac-toe-bruteforcer
Remnants of an old research project long since past. It brute-forces a tic-tac-toe game and outputs relevant statistics.
You can configure its parameters in src/Node.h - they're a couple of `const int`s. It doesn't load a configuration,
so you'll have to recompile every time you change a parameter.

Supports an experimental multithreading hack I made to speed up calculations. It's not 100% accurate, so don't use it to
get your best data. If you want to try it, uncomment all `//#define SDL_ENABLED`s. You'll need SDL2, specifically
SDL_Thread.h. I used it over a more proper threading library because I knew it better and it was more readily accessible.
I never put much effort into it, so don't be surprised when the numbers are off by a bit (so don't judge my
multithreading skill by it!).
