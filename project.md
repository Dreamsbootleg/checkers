# communicates to checkers ai via standared in and out.

- baised off of UCI (Universial Chess Inerface)
  uses pdn?
  uses sockets or files?
- users keep track of their own board state with the referee enforcing board states. Ie if an invalid move is returned, game is forfitted.
- can play either international or american checkers

# board class

- Uses a vector structure
- numbers them 1 - x; for a checkers board we are only using 32 squares.
  For chess, use 64.
