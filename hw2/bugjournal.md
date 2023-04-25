# Bug 1

## A) How is your program acting differently than you expect it to?
- My word is not showing up in the HT

## B) Brainstorm a few possible causes of the bug
- My own hash table might not be up to the task.
- I might be losing my word by some means
- I might have forgot a null terminator

## C) How you fixed the bug and why the fix was necessary
- I didn't malloc space for the word so the pointer which was in the malloced char * was being lost when the char * was freed so I malloced space for the word.


# Bug 2

## A) How is your program acting differently than you expect it to?
- I am not finding the right char * for id->name

## B) Brainstorm a few possible causes of the bug
- I might not be allocating the name correctly
- I might not be using the right key
- I might not be setting the name correctly

## C) How you fixed the bug and why the fix was necessary
- I wasn't copying the copy of the char* so I copyed the char * using a for loop and it worked


# Bug 3

## A) How is your program acting differently than you expect it to?
- My code for search shell is saying I am passing a NULL into a function which is causing a Verify333 to trip in Hashtable

## B) Brainstorm a few possible causes of the bug
- It seems to come from Doctable so I might not be cheaking for NULLs propery in there
- I could be passing in bad values into MemIndex_Search() which could be causing the bug
- I could be not cheaking for NULLs in Search Shell

## C) How you fixed the bug and why the fix was necessary
- I had my gitline in my main method which somehow wiped my local varibles so I put it into the helper method and it all worked
