# Bulls and Cows (숫자 야구)

## Rules
1. The program has a vector of four different integers (0~9)
ex) 1122 (x) 1472 (o)

2. The user has to find out the numbers.

3. 'Bull' means the user got right digit and position. 
   
   'Cow' means the user got right digit but wrong position.
   
        ex) Answer : 1234
            Numbers that user guesses : 1792     
            => 1 bull and 1 cow 
         
         
## Requirements
1. I used vector of C++ instead of array of C.<br/>Also, use cin , cout to get numbers from user and print the result to console.
2. I generate the random numbers by using randint from std_lib_facilities.h 
3. The number of chance to find out the answer is 10.<br/>If the user succeeds before 10 try, print a congratulation message.<br/>Else, print a failure message and the answer.<br/> Then program asks the user to keep playing. 


4. Exception handling<br/>If the user input non-number (like letter or character) or number which is out of range, print error message. 


## Capture
![Test1](/Advanced-C-Programming/img/hw1 test.png)
