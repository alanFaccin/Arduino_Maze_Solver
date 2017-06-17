Maze Solver - Instructions (botnroll.com 2015)


The first time you use this program you have to set up the Speed and the pause of the robot.

1. On Menu select each parameter and set as follows:

speed = 40
pause = 300
debug = OFF

Note: You might need to adjust these values later on, but these standard values work on most of the cases using a 12V charged battery.

2. Select "Start Run" and press Enter button (at the bottom right).

3. The Robot enters the "Exploring Maze" step and explores the maze turning left whenever possible, using the "Left Hand on The Wall" algorithm. It saves the path on the way and beeps on every recognised intersection.

4. When it reaches the goal (a big black square) it plays a music a displays FINISHED on the LCD.

5. Then, 2s later, it shows the recorded path on line 1 of the lcd and the new computed shortest path on line 2.

6. Press any key to go back to the Menu. You can change any parameter if you need to. 

7. Put the robot back on the same starting position and select "Start Run".

8. The robot now enters the "Shortest Path" mode and solves the maze using the leaned path, which should be the shortest path.

9. When reaching the goal it plays the music again.



Notes:
1) At the end of the "Shortest Path" mode it goes back to "Exploring Maze" mode and you can now start the robot at a different location in the maze.

2) The Robot is doing obstacle avoidance. Be carefull to take out of the way any obstacles that may interfere with the robot otherwise it will not record the correct path.

3) Have fun!