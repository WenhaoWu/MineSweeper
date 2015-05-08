# MineSweeper

##FlowChart 
![](https://github.com/WenhaoWu/MineSweeper/blob/master/FlowChart.jpg?raw=true)

##Idea 
As seen from the flow chart, the logic behind the game working is quite simple. Wining logic is the user set the flags on top of every mine position. Losing condition is the user guess a number that there is a mine beneath the board.

In my implementation there are together five possible situation for one block in the board. 
* The “+” sign means this block is safe and there is no mines surrounding it. 
* The number means this block is a edge, and the number indicates how many mines are surrounding this block (8 maximum). 
* The “#” sign means this block is being flagged.
* The “?” sign means this block is not guessed nor flagged.
* The “*” sign means there is a mine behind this block (Only shows when the user lose). 


The main challenge here is to extend the edge when user guess a safe zone (“+” sign). We have to extend the edge to the nearest mine, and show the edge by number while adding the rest to the safe zone (“+” sign).

This implementation is not perfect yet cause it only shows the number 1 for edges, which means the extension of the edges stop when it finds out there is a mine around it. In true situation it should go over it and make a close circle.
