# Battleship

Battleship game in pure C++ / console version, local versus the computer or network game.

# Invocation

## Launch solo game

```
battleship
```

## Launch network game

Launch one instance first (IP arguments are: own IP, opponent IP)

```
./battleship 127.0.0.1 127.0.0.1 my
```

Then start first player:

```
./battleship 127.0.0.1 127.0.0.1 start
```

# Directory organisation

- `tui` contains the terminal (console) version of the game
- `gui` contains the graphical version of the game (desktop/mobile)
