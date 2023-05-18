# Bug 1

## A) How is your program acting differently than you expect it to?
- My table offsets and file size were not matching

## B) Brainstorm a few possible causes of the bug
- I could be not writing enough data
- I could be not counting the right amount of data
- I could be not returning the right value

## C) How you fixed the bug and why the fix was necessary
- I found that I was not returning the hash table bytes in the WriteWordToPostingsFn method, so I was loosing the size of the hash table which caused a lot of problems, so I added the hash table bytes to my returned and it worked.


# Bug 2

## A) How is your program acting differently than you expect it to?
- My doctable reader was returning a shifted stings

## B) Brainstorm a few possible causes of the bug
- I might be reading too many bytes
- I might be getting the wrong size of the string
- I might be saving the wrong number

## C) How you fixed the bug and why the fix was necessary
- I was taking the size of DocIDElementHeader instead of DoctableElementHeader which meant I read 2 extra bytes. So when I made my sizeof it wasn't getting the right amount of bytes.


# Bug 3

## A) How is your program acting differently than you expect it to?
- My fileserchshell was only prossesing 1 word at a time

## B) Brainstorm a few possible causes of the bug
- I could not be prossing the whole line
- My QueryProcessor could be wrong
- 

## C) How you fixed the bug and why the fix was necessary
- I wasn't reading the whole line so I used the getline method to get the entire line instead of 1 word.
