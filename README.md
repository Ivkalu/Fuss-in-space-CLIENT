"# Fuss-in-space" 


This is work-in-progress project.
Goal is to make a cool game Fuss in space using SDL2.

Second goal of the project is to make a framework for easier making of other games.


Autor notes:
#PROBLEM 1
One of the biggest problems currently is the need to declare variables static so they can be accesed later in functions and methods.
It is bad because they need to be first declared static, and after that constructed in another place.

Possible solution:
Each sprite with it's constructor is added to a big sprite collection that parents all the sprites.
Sprites have a new "init" method that is called only after subsystems have been initialised (renderer, and window are created, which are needed for texture loading).

Sprites are defined in a big Sprite Collection class, all are public and can be used anywhere.
They are later init in it's init method...

----Coll.h----
struct Collection {
	Sprite* a = new Sprite("k", nullptr, nullptr); //with Sprite() constructor they are automatically added to allSprites vector.

    vector<Sprite*> allSprites;

    void init();

};
extern Collection c; //extern so other files can use it without redefinition

----Coll.cpp----
Collection c;

void Collection::init(){
    for(auto s : allSprites){
        s->init();
    }
}

