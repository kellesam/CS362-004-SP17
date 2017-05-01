So it looks like we need to iterate through each if statement and produce thedesired input 
at that step before moving on

First thought for inputChar is to look up ASCII range

Lowest = 32 for '  '

Highest = 125 for '}'

Set up rand() to generate integers and then return the value

I originally planned to set a (min, max) range for rand(), but C is fast enough that I 
realized it would just take a few milliseconds longer if I only set a top range

Got to state 9 in about 2 seconds.

Now for inputString

Looks like a 6-index string with 5 chars and a null terminator

It's tempting to just return the string "reset"

I ended up allocating 6 bytes on the stack with "char myString[6], filled in the first 
5 indices with random integers, added a null terminator, and returned it.  This passed 
the value of string back into main() without losing the value as the stack returned

I realized that rand() could work quicker if I limited the values between 101 ('e') and 115 ('s')

Started wondering why it was taking so long, then I double-checked the ASCII chart and 
realized that I excluded the 't' value 116.  That would explain it

Fixed the issue and on the next run it finished on iteration 579,422

Thanks for reading!
