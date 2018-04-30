LEGENDS OF ZELDA:
	The game is inspired by the original legends of zelda.

BUILD INSTRUCTIONS
	// using terminal go into the main directory
	mkdir build
	cd build
	cmake ..
	make
	./graphic_assign1

	// using qtcreator
	open the file
	run cmake
	ctrl+r // to run


CONTROLS:

	JUMP  		-> SPACE  
	LEFT  		-> LEFT_ARROW  
	RIGHT 		-> RIGHT_ARROW  
	FRONT 		-> FRONT_ARROW
	BACK  		-> BACK_ARROW
	FIREBALL 	-> F
	q/esc 		-> quit window

	BOAT-VIEW  	-> 1
	FOLLOW-CAM 	-> 2
	TOP-VIEW   	-> 3
	TOWER-VIEW 	-> 4
	Hele-VIEW	-> 5

	In heli view:
		you can control the heli with mouse drag.

Game features :

	Boat:
		The boat can be controlled using the arrow keys and can also jump and is able to throw fireballs.

	Cannon:
		The cannon is used for shooting fireballs in order to kill the monster or break the rocks.

	Fireballs:
		The fireball is released from the cannon as a projectile, it kills the monsters and break the rocks.

	Sail:
		The sail of the boat shows the direction of the wind by rotating in the direction of wind.

	Monsters and rocks and barrels:
		The monsters and rocks are placed randomly in the sea.
		By colliding with the monster, we loose a life.
		By colliding with the rock, we loose some points.
		By colliding with the barrels, our speed doubles.
		There is also 5 rocks on colliding with them you loose lives.
		And by breaking these 5 rocks you get extra lives.

	Score Criterian:
		Hitting the monster 	= +5
		Hitting the rock 		= +2
		Colliding with monster 	= -1 life
		Colliding with rock 	= -1

	Lives:
		The player has initially two lives.

	Levels:
		The game consists of 3 levels.
		In first level we get some time to score the required pnts, if scored we move forward to level 2.
		In 2nd level, we face the wind as well.
		In the 3rd level we face the boss monster, which can be killed using 3 fireballs.
