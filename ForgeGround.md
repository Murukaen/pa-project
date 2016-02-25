# Forge Ground #



## Prerequisites ##

### C Programming Language ###

We will use 95% the C that was thought at PC and SD courses. Thus I won't post any material related to this. If someone needs those courses or other resources please email me on razzvan.savu@gmail.com

### XBoard Protocol ###

The main source can be found [here](http://home.hccnet.nl/h.g.muller/engine-intf.html). More information about SAN Standard is [here](http://en.wikipedia.org/wiki/Algebraic_chess_notation).

### Basic Linux Commands ###

For all of us who forgot something look [here](http://books.google.com/books?id=KNvQniXULV4C&printsec=frontcover&dq=utilizarea+sistemelor+de+operare&ei=vDuSS8n5Aqq6yQTVxNi7BA&cd=1#v=onepage&q=&f=true)

### SVN ###

We use subversion as version control system here. All about SVN can be found [here](http://svnbook.red-bean.com/en/1.5/index.html). Knowing the [Basic SVN Usage](http://svnbook.red-bean.com/en/1.5/svn.tour.html) should be enough for now.

### Rules of chess ###

You will find a general description [here](http://en.wikipedia.org/wiki/Rules_of_chess).

## Project Standards ##

### Coding style ###

I have uploaded begin.c and begin.h as frameworks for the project sources. They contain the code structures that will occur. It is very important to keep these standards because no one wants to spend hours reading somebody else's source codes. The scope is to write the program in an organized hierarchical manner.

Key factors:
  * Commentaries should be emphasized according to the block of code they open/end.This is an example with great ambiguity :
```
/* --- MACROS - #define --- */
#define ONE 1
#define TWO 2
/* One should look over this : */
#define THREE 4 
```

  * Short descriptions of commands shall be commented after the command using // :
```
int cont; // cont counts something
```
  * Block descriptions should be implemented as `/* Name_of_Block */` :
```
int main ( void ) {

     /* Variables */
     int n;
     Stack s;
     /* Initialization */
     s = new_stack();
     ...
```
  * If there is a quite large block of code it will be limited by two comments as follows :
```
/* START Check the borders */
...
/* END Check the borders */
```

### Modular strategy ###

The project shall be assimilated with a PC. Why ? Because when you write the main function let's say, you program your PC in C, not being aware of what is done beneath. As a matter of fact your are not even interested of that as long as the underlying structure does its job well. The same should apply here. However, it would be wrong to say that the writer of the main function doesn't know what is under. We need a definition here. Let's call the universe of a module ( .c + .h / .o ) everything that is know by the module ( not by the one who created it ). Thus the main module clearly doesn't even need to know how to handle input for instance. It just knows that there is a procedure that does this and the communication with that procedure. Without degenerating I want to point out several concepts :
  * The more divided the main task is, the more easier is for us to resolve it ( remember Divide and Conquer )
  * Every module/procedure/global variable should be carefully commented. The minimum would be :
    * For modules : The documentation shall be commented in the .h file.
    * For procedures : Comment the description in .h just before the function declaration :
```
/*Description:
 *Determines the actual state of the game based on the past state and the last move
 *Input:1:move
 *Output:1:updated_state [state]
 */
state update_state ( move );
```
    * For global variables : comment just before the variable :
```
/*Description : Determines whether or not the engine is on move
 *0 - not on move
 *1 - on move
 */
int f_ENG_ON_MOVE;
```

### Notation Agreements ###

We shall keep the following minimal standards regarding notation throughout the project sources:
  * Pointers that can't be assigned an intuitive/generic name shall be prefixed with **p
  * Flags will have the _f_** prefix
  * Functions describing operations with a certain "object" shall be prefixed by that object's name
  * Functions that **get** some information from a structure / generic pointer should contain the tag `get_`
  * Functions that **set** a variable within a structure / generic pointer should contain the tag `set_`
  * Functions should have a suggesting name regarding the variable / state that it processes

Examples:
```
bitmap state_get_bitmap ( state , int );

void state_set_bitmap ( state , bitmap , int );
```

## General Structure ##

The project is consisted of several interrelated structures of modules, each with its own finality :

### Xboard - Engine Flow ###

![http://i44.tinypic.com/bjbfig.jpg](http://i44.tinypic.com/bjbfig.jpg)

### Main method ###

![http://i43.tinypic.com/21cigav.jpg](http://i43.tinypic.com/21cigav.jpg)

## Common issues ##

Since the beginning of this project we've come up to a series of common mistakes. I will state the most important ones :
  1. Pay attention to cast. Several functions have the **void `*`** return type.
  1. For each main function ( in test modules ) the initialization Init(INIT\_ALL) **must** be used.
  1. Every commit of non-test modules must include no test-purpose printf calls.

