# Anti-cheat-chess-tool
SECURE'IT CUP'22. Solution for chess case. 

## Short description
This is a program that allows you to detect anomalies in the suspect's game by calculating the **_average accuracy_** of the suspect's game and the entire database for each **_set_** of **_position attributes_** encountered in the suspect's games. Simply put, **_game accuracy_** is how well the engine thinks a person is playing (as a percentage from 0% to 100%). An **_attribute_** is the number of certain pieces on the board, such as 5 queens on the board. An **_attribute set_** is a collection of such attributes for each type of piece, for example, {0 pawns, 2 knights, 3 bishops, 2 rooks, 0 queens}. Suppose, for the set of attributes considered above, the average accuracy of the game of the suspect is 70% and the number of moves played for this attribute is enough for statistics (> 14 - 20), then if on his rating the average accuracy of the game is 44%, then there is a suspicion of cheating.

### Input
Name of suspect, paths to database an engeni and other options (see /example folder).

### Output
Sets of attributes with average accuracy and count of moves for that set (see /example folder).

## Limitations and remarks
1) First of all, the tool in its current form (console application) does not have additional tools for analyzing the information received, which means **it cannot automatically determine whether a cheater is or not**. Later, a graphical interface will be added, which will provide filters, ranks of information for effective analysis.
2) The variant tree (debut tree) is not implemented in the analyzer, which means that the accuracy is calculated even for the debut stage. This will be fixed later.
3) It is highly recommended _**not to use databases larger than 1 Gigabyte**_, since for independent analysis with a computer capacity of up to 4 - 5 cores, a database of up to 1 Gigabyte will suffice.
4) The analysis time can be calculated with an accuracy of 10 seconds, since the most time-consuming operation (position analysis by the engine) has a fixed execution time. Automatic calculation of the analysis time will be added later, but for now it is **_recommended to use the analysis parameters presented in the example folder_**, then the average analysis time will be ~ 9 hours. Also, to calculate the minimum time, you can use the formula: number_of_moves (input parameter) * 100 (average number of attribute sets) * move_time (input parameter in seconds).
5) The tool so far only supports parallel operation of **one engine at a time**. Later, the ability to run several engines for parallel analysis will be added (effective if there are > 2 physical cores).
