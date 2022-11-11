Ivan Lin
Partner: Lucia Wang

Problems and Solutions:
We first encountered memory allocation error.
We did not allocate the correct amount of memory which caused multiple instances of seg fault.
This was resolved by swapping width and height numbers.
Next, our negative image did not appear correctly on screen.
This problem was caused by us not printing the value in binary using fwrite.
The problem was resolved using fwrite.
Lastly, our resized image look distorted.
This problem was caused by casting a double prematurely before multiplying it.
The problem was resolved by implicit casting the multiplied index into an int.

Thoughts on assignment:
This assignment required us to think more logically through each step.
The collaboration aspect made programming more interesting since it
involved understanding and communication. Conforming to certain coding
styles was something that we never thought about until this project.
Seeing the work visually makes the effort more rewarding. I loved that
we had freedom in creating our own functions making us more innovative.
It forces us to think about design patterns and architecture.