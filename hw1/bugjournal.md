# Bug 1

## A) How is your program acting differently than you expect it to?
- Push Pop is causing a Segmentation fault

## B) Brainstorm a few possible causes of the bug
- I think my handling of malloc is probly wrong
- Or I don't have enough safe guards in place
- Or possibly I am not doing enough false malloc cheaks

## C) How you fixed the bug and why the fix was necessary
- I freed the pointer too early and once I moved the free() to the end of the function it worked.


# Bug 2

## A) How is your program acting differently than you expect it to?
- LLIterator is not trowing out Iteratiors that it's supost to.

## B) Brainstorm a few possible causes of the bug
- I might not be removing node correctly in my iter remove function
- I might have missread the spec and returning true when I should be returning false
- I might not doing enough cheaks which is causing the problem

## C) How you fixed the bug and why the fix was necessary
- I missread the spec and had to redo my whole iterator


# Bug 3

## A) How is your program acting differently than you expect it to?
- My HTIterator_IsValid() is returning the wrong value

## B) Brainstorm a few possible causes of the bug
- My HTIterator_Next() function is not working so my vaild funciton is wrong
- My HTIterator_IsValid() might not be robust enough to handle what I am soposed to do
- It could be a misread spec that is returning wrong

## C) How you fixed the bug and why the fix was necessary
- 
