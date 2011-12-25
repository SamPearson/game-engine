	Credits:

Backgrounds taken from here:
http://www.lorestrome.com/pixel_archive/main.htm
(If you have any idea how to find this guy, I'd be glad to hear it, these backgrounds are nice.)

Character sprites taken from here:
http://www.sheezyart.com/view/407111/


	Setting the game up:


Ubuntu:
All necessary allegro libraries can be found in the repos. To get them, try 
$ sudo apt-get install allegro allegro-config
Compiling in ubuntu is as easy as 
$ g++ main.c `allegro-config --libs`
And running is simply
$ ./a.out


Other OSs:
No OS-specific libraries were used, so any OS should be able to compile and run this game. Just make sure you have allegro installed and compile main.c 



	Playing the game:

w,a,s,d move around. That's pretty much all you can do at this point. 
