Goal : implement game of life using text files

Steps : 
- Validation of input parameters that are used for running the script.
    --input : mandatory
        - input file is mandatory
        - input represents a path to a text file  
    --iterations: mandatory
        - iterations is an integer and it is positive. 
        - if iterations not provided : default to 1. ( could be printed error instead )
    -- all : is optional
        - if provided print every iteration. 
        - if not print only the last iteration. 
- Verification of inputs :    
    - file empty is valid : return empty without iterations. 
    - input file contains only (_, *,\n)
    - all lines are the same length
- Building output format : 
    - The output file should be cut to the smallest containing all alive cells. 
    - The output file should be renamed and includes number of iterations in the name. 
    - Extention is optional : check if extension is explicitly set in the input file. 

Rules of the game :
    - Next iteration is generated using algo of game of life. 
    - for d : List N neighbors => x alive * and y dead _:
        Option 1 :
        - if d=* and (x=2 or x=3) : d=*
        - if d=_ and x=3 : resusitate => d=*
        Option 2 :
        - if x=3 : d=*
        - if x=2 and d=* : d=*
        - else : d=_ 

The board is supposed infinite in all directions:
    - As it is not precised, we can consider that all surrounding cells are dead to be able to extend the grid. 
    
Tests elements :

- Build random input files for testing. 
    


    Classes : 
    - People equivalent to a cell. it should be able to live die and born and it knows her adresse. Perhaps should know her neighbours. 
    - Population contains a certain number of people it can be extended or reduced or initialized
    - game of life it can start it can stop it can pause and initialize rules
    - grid it contains the population it can be supposed infinit but we adapt it to just contain the population, each cell of the grid contains only one people. 

