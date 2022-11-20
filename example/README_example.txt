DataBase source: https://database.lichess.org/
Chess engine source: https://stockfishchess.org/download/
Account link for experiment (where I cheated): https://lichess.org/@/all_for_science

Sorry list (players players I cheated against):
1) ashtipaix
2) mladenc
3) toti2020
4) TacoDeCereal
5) KerimShirinov1954
6) Jackrull95
7) felixfarid13
8) RajaSakti
9) shade_of_ox
10) vanAR10
11) HerGan57
12) JimuraSan
14) Mparsa123
15) ayt13
16) daddyeugene

More about input:

1) Path to database. 
Download or create a chess database in PGN format and drag it to the console with the mouse cursor.
2) Name/nick-name of player. 
Simply write name/nick in console. That is suspect, and his games will be analyzed.
3) Path to engine.
Download any UCI engine you want from offisial site and drag .exe file to the console with the mouse cursor.
4) Count of CPU threads.
Find out how many phisical cores (NOT LOGICAL CORES) your computer has, and then write down that number.
You can use only one core, but it's recommended to use 2 cores and more.
The more cores you provide, the more accurate analysis you will get.
5) Max count of lines.
This means, how many lines wich engine generated will participate in the calculation of the average accuracy.
It's recommended to set this value to 4.
6) Hash size in MB.
This is simply a capacity of RAM memory, that you can suggest to engine.
It is recommended to set the value to a multiple of 1024, for example, 1024 MB, 2048 MB, 3072 MB.
The more RAM you provide, the more accurate analysis you will get.
7) Move time in seconds.
A time, that will spend for evaluating 1 move. So, you can set any value you want,
but It's recommended to calculate the time of analisis first. Recommended to set this value
no more that 6 sec.
8) Type of games.
That is a one of the parameters of filter. If you set BLITZ value,
than games that containes event BLITZ will be analyzed, and others not.
9 - 10) Min rating/Max rating.
Set the desired rating threshold for sorting.
11) Max count of moves.
Max count of moves, that will be analyzed. That filter implemented
ONLY for DATABASE analisis, and NOT for PLAYER analisis.
12) Max count of games.
Max count of games, that will be analyzed. That filter implemented
ONLY for PLAYER analisis, NOT for DATABASE analisis.

More about output:

"X" in set of attributes means, that in that "X" place can stay any possible number.
Count is the count of moves, that were analyzed.

If you aborted the programm before analisis ends, then manually close
the engine process using task manager.