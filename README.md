![](./images/pooh.png)

## Description
This program creates an inverted image and a resized image from a ppm file

## Requirements
gcc <br>
make

## Usage
```shell
    make run
```
Enter height and width for resized image

## Commands
```shell
    make <target>
```

target:
- all - compiles program
- run - compiles and executes the program
- clean - removes .out .exe .o files
- tar - tars program

```shell
    make run ARGS="<input> <resized> <negative>"
```
- input - name of input ppm file
- resized - name of resized output ppm file
- negative - name of inverted output ppm file