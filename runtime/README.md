
# Prerequisites
## Install Bison:
If you're on Ubuntu, you can install Bison using the package manager:

```sh
sudo apt-get update
sudo apt-get install bison
```
On Windows, you can download Bison from GNUWin32 or use a package manager like Chocolatey or Cygwin.

Write Your Grammar File:

Use the provided grammar as a starting point and save it to a file called simple_lang.y.
### Run Bison:

Open a terminal (or command prompt in Windows) and navigate to the directory where your simple_lang.y file is located.
Run Bison to generate the parser code with the following command:
```sh
bison -d simple_lang.y
```
This will generate two files: simple_lang.tab.c (the C source code for the parser) and simple_lang.tab.h (header file with token definitions).

Install Flex:
On Ubuntu, you can install Flex using the package manager:

```sh
sudo apt-get update
sudo apt-get install flex
```

## Install Flex

On Windows, you can download Flex from WinFlexBison or use a package manager like Chocolatey or Cygwin.

### Write Your Lexer File:

Use the provided Flex specification as a starting point and save it to a file called simple_lang.l.
### Run Flex:

Open a terminal (or command prompt in Windows) and navigate to the directory where your simple_lang.l file is located.
Run Flex to generate the lexer code with the following command:

``` sh
flex simple_lang.l
```
This will generate a file called lex.yy.c, which contains the code for your lexer.
### Compile Your Lexer and Parser:
First, run Bison to generate the parser if you haven't already:
```sh
bison -d simple_lang.y
```
Then compile both the lexer and the parser with GCC (or your chosen compiler):
```sh
gcc -o simple_lang simple_lang.tab.c lex.yy.c -lfl
```