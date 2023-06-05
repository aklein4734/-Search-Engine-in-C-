# Bug 1

## A) How is your program acting differently than you expect it to?
- It was stuck in an infinate loop at GetNextRequest

## B) Brainstorm a few possible causes of the bug
- my loop checking might not be working
- I might be failing a wrapped read and keep looping
- I might have forgotten a loop edge case.

## C) How you fixed the bug and why the fix was necessary
- I decreased my buffer size so that a failed read would not happen. 


# Bug 2

## A) How is your program acting differently than you expect it to?
- I am failing a IsPathSafe()

## B) Brainstorm a few possible causes of the bug
- I could not be understanding what a safe file is and not checking for it.
- I could not be finding the right directory in the path
- I could not be reading the file properly.

## C) How you fixed the bug and why the fix was necessary
- I added a "/" to the end of root directory when I was checking for it in my path. It was neccicary because
 the directory name could be elsewhere in the path so it it was returning true when it wasn't suppost to.


# Bug 3

## A) How is your program acting differently than you expect it to?
- My serverSocket wasn't consitantly working.

## B) Brainstorm a few possible causes of the bug
- It could be I was using a method wrong.
- I could be not reciving the right sock.
- I could not be distiguishing between IvP4 and IvP6.

## C) How you fixed the bug and why the fix was necessary
- I was using a general sock when reading the server's sock insted of having 2 different cases for the 2 different kinds of socks 
  so I put my getsockname in two branches of an if else and it worked.
