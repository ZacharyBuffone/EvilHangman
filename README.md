# Evil Hangman #
Originally wrote as an assignment of Computing II at UMASS Lowell.


### Problems ###
1. Binary Search tree not working properly.
  - May have to do with string_compare() not working well with the word keys.
2. Memory leaks
  - Leaks are caused in functions called at main.c:56,57,59,81.
  - May have to do with binary search tree not destroying correctly.
