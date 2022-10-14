**Prerequisites**

CMake, Makefile, C++ compiler

**How to use**
- Navigate to the root project directory
- In order to generate a Makefile for the project, use `cmake CMakeLists.txt`.
- To compile the program, use `cmake --build .`
- Run the proram using `./DI_RPG`

**About the game**

DI_RPG is a terminal based, role-playing game. You control a party of heroes as they fight their way through a grid infested with monsters. 

![image](https://user-images.githubusercontent.com/59566389/195812934-00f2c551-abac-4197-8215-e9d3fa2462c7.png)

After starting a new game, you are greeted with a hero creation menu. 

![image](https://user-images.githubusercontent.com/59566389/195813593-a2a32dfc-cc5f-4025-9f5e-9ad112684751.png)

Each class has different stats. For example, warrior specializes in strength. Additionally, each class has a different starting weapon and spell.

![image](https://user-images.githubusercontent.com/59566389/195814013-9da555c8-b83c-460c-b524-09b75eec0bf0.png)

You can create up to 3 heroes. If you have more than oen you hero will control each one separately during battle. However, you will always be moving as a group
during map traversal.

As soon you are done with the hero creation, you are greeted with the _Block Menu_, in which you have the options to check the inventory, move around the map, or
go back to the main menu.

![image](https://user-images.githubusercontent.com/59566389/195815286-03c1a76d-1212-45fd-8923-6ff8eaea6f27.png)

In the inventory screen, you can change your equipped weapon and armor and also use a potion.

If you choose to move on the map, the Map is first displayed in the console window (H indicates the hero group position, # forbids  you from entering
the block, M is a Market location). 

![image](https://user-images.githubusercontent.com/59566389/195816110-0c7dab95-40bd-4d32-9985-1f26fcee8d05.png)

As you are moving in the wild, you may happen to encounter random monsters. The encounter menu looks something like this:

![image](https://user-images.githubusercontent.com/59566389/195816360-c5515909-b4af-4050-837f-e20431c42216.png)

Each round consists of a character attacking and the AI monsters reacting to it. The characters act in circular rotation. In the above example, Joveno attacks first,
then Julia. The [1 to X] signifies all the possible targets your character can attack. X is the last AI enemy.

![image](https://user-images.githubusercontent.com/59566389/195817038-9c9c5e04-60c7-4c9a-a40e-98f384bef5d7.png)

Round ends when either party (heroes or monsters) are all defeated. If the heroes win, they receive gold, which they can use in the marketplace to purchase better gear
and potions, and XP. If enough XP is gathered, heroes level up and their stats improve.

![image](https://user-images.githubusercontent.com/59566389/195818310-3223fa7d-5069-454d-a14b-8b5d57d39822.png)

Finally, the market menu displays the amount of available gold per hero and allows you to buy or sell items.

![image](https://user-images.githubusercontent.com/59566389/195818619-ca707c55-aec7-418b-90ae-30158a1c39f6.png)

Each market has different items for sale.

![image](https://user-images.githubusercontent.com/59566389/195818752-1b72b0d8-1204-4863-b316-2ad2365d578c.png)







