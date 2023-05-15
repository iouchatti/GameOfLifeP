
##Please compile using command bellow :

    g++ -std=c++17 GameOfLife.cpp main.cpp -o gameoflife

##To launch the game of life you can use options bellow : 

    --input: A string representing the input file path, that should refer to a file using the board format. This parameter is mandatory.

    --iterations: A positive integer representing the number of iterations to apply the rules. This parameter is mandatory.

    --all: Print all the iterations. This parameter is optional. If absent, only the last step is printed.

 To generate a random file you can use the option :
    --gen it will generate a random valid matrix in the file at the path you provided. You need to precise the text file name. 

 Example of command line could be : 
    gameoflife.exe --input input_Sample.txt --iterations 3 --all --gen

 You can modify the script "modifyMeToRunGame.bat" if you are on windows.  