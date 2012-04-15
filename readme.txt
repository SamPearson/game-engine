Part of an RPG engine. written in C using allegro for graphics

	Requirements:
Compilation requires liballegro4.2-dev 
Running requires liballegro4.2

	Credits:
Backgrounds taken from here:
http://www.lorestrome.com/pixel_archive/main.htm
(If you have any idea how to find this guy, I'd be glad to hear it, these backgrounds are nice.)

Character sprites taken from here:
http://www.sheezyart.com/art/view/407111/


	Setting the game up:
The game itself stores all external functions in .h files,
so it can be compiled thusly:
g++ main.c `allegro-config --libs`

The map editor holds external functions in other .c files,
so they all must be compiled as well:
g++ *.c `allegro-config --libs'

All testing so far has been done in a linux environment.
The game should work in any OS provided that a recent enough
version of the allegro library has been installed.

	Playing the game:
w,a,s,d move around. That's pretty much all you can do at this point. 

