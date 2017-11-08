/*
 * File:   CoCC.P1
 * Name: Daniel Lok
 * Purpose: Calculates the amount of time it takes to generate a specific amount of gold inputed by the user,
 * based on how many gold mines they have, and what level their gold mines are.
 * STATUS: DONE
 *
 *  Created on October 29, 2015, 11:13 AM
 *
 */

#include <stdio.h>
#include <stdlib.h>

char inputFileName[100];
int LEVEL = 0; //*
int RATE = 1; //*
const int maxMines = 7;
int goldMine[maxMines][2]; // Array is global variable since we cannot return them through functions at the moment.
int FILE_EXIST = 4; //*
int FILE_NOT_EXIST = 5; //*
double HOWMANYHOURSINONEMINUTE = 0.0166666; //* Gave these global variables with '//*' marked a name so that the
double HOWMANYHOURSINONESECOND = 0.000277778; //* functions below that use it can be more readable.
double HOWMANYHOURSINONEDAY = 24; //*
double HOWMANYHOURSINONEWEEK = 168;//*

/*
 * Purpose: To get the name of the file that contains the values needed for our calculations.
 *
 * Parameters: None.
 *
 * Return Value: None. The file name is inputted as a global variable, so the char
 * can be passed through multiple functions.
 *
 * Side Effects: Changes/edits the global variable inputFileName, based accordingly
 * on whatever the user types as the file name.
 */
void getFileName() {


    printf("\nPlease enter the name of the file that contains the values: ");
    scanf("%[^\n]s", inputFileName);
    fgetc(stdin);


}

/*
 * Purpose: To check whether or not the name of the file inputed by the user exists or not. If the file exists
 * but is empty, the function will treat the file as if it does not exist.
 *
 * Parameters:
 * inputFile: The input File Name.
 *
 * Return Value: File: Returns a variable with a specific integer based on
 * whether or not the file exists. The integer is represented by global variables named FILE_NOT_EXIST (5)
 * and FILE_EXIST. (4)
 *
 * Side Effects: None.
 */

int CheckFileExist(FILE *inputFile) {


    int File = 0;

    inputFile = fopen(inputFileName, "r");

    if (inputFile == NULL) {
        File = FILE_NOT_EXIST;
    } else {
        File = FILE_EXIST;

        fgetc(inputFile);

        if (feof(inputFile)) {
            File = FILE_NOT_EXIST;
        }
    }


    return File;
}

/*
 * Purpose: Notifies and asks the user whether or not the data is correct.
 * 'y' for yes, 'n' for no. If the answer is not 'y' or 'n', keep asking until it is.
 *
 * Parameters: None.
 *
 * Return Value:
 * CheckCorrect: The character that the user inputted.
 * (y for yes, n for no)
 *
 * Side Effects: None.
 */

char CheckIfDataCorrect() {
    char checkCorrect;

    printf("\nAre you sure this data is correct? (y/n): ");
    scanf("%c", &checkCorrect);
    fgetc(stdin);


    while (checkCorrect != 'y' && checkCorrect != 'n') {
        printf("\nInvalid input, please try again: ");
        scanf("%c", &checkCorrect);
        fgetc(stdin);
    }

    return checkCorrect;

}

/*
 * Purpose: To gather how many gold mines the user has through the keyboard.
 * If the number is less than 0 and greater than 7 keep asking until it is between 1-7.
 *
 * Parameters: None.
 *
 * Return Value: NumGoldMines: The number of gold mines the user has.
 *
 * Side Effects: None.
 */

int getnumGoldMines() {
    int numGoldMines = 0;

    printf("Please enter the number of gold mines you have: ");
    scanf("%d", &numGoldMines);
    fgetc(stdin);

    while (numGoldMines <= 0 || numGoldMines > 7) {
        printf("Invalid input for the number of mines, please try again: ");
        scanf("%d", &numGoldMines);
        fgetc(stdin);
    }

    return numGoldMines;
}

/*
 * Purpose: Reads the information contained within the file. The information includes:
 * the number of gold mines (First number) and the level of each gold mine. (The numbers below first number)
 * It will only print the values if the number of gold mines is within the specified boundaries. (1-7)
 *
 * Parameters:
 * inputFile: The inputFile that has to be opened for reading.
 *
 * Return Value: numGoldMines: The number of gold mines that was found in the
 * file (Always the first number at the top within the file)
 *
 * Side Effects: Modifies a section of the global variable in my 2D array based on what the file reads as the levels.
 * The section is one part of a dimension in the array (The array column that stores the levels of my gold mines)
 */

int ReadFileInfo(FILE *inputFile) {
    int numGoldMines = 0;
    int counter = 0;


    fscanf(inputFile, "%d", &numGoldMines);
    fgetc(inputFile);

    if (numGoldMines > 0 && numGoldMines <= 7) { // It will only print the values if the first value
        //(number of gold mines) is within the boundaries.
        printf("The number of gold mines you have is: %d ", numGoldMines);



        for (counter = 0; counter < numGoldMines; counter++) {
            fscanf(inputFile, "%d", &goldMine[counter][LEVEL]);
            fgetc(inputFile);
            if (goldMine[counter][LEVEL] <= 0 || goldMine[counter][LEVEL] > 12) { // If the gold mine levels are over
                // the boundaries
                printf("The values above for your amount of gold mines, and gold mine levels are invalid.\n");
                numGoldMines = 14; //Since we can't return both the array and the numGoldMines, set
                //numGoldMines over the boundaries so within the main function when it checks if numGoldMines is
                //within the boundaries, it will still assume the data is not correct.
                break; // break out of loop.
            }
            printf("\nGold Mine level #%d is: %d", counter + 1, goldMine[counter][LEVEL]);
        }
    }



    return numGoldMines;
}

/*
 * Purpose: Asks the user for the level of each of his gold mines. It gets these numbers
 * through the keyboard and stores it in one section of the 2D array.
 *
 * Parameters:
 * numGoldMines:The number of gold mines the user has.
 *
 * Return Value: None.
 *
 * Side Effects: Modifies a section of the global variable in my 2D array based on the levels the user types in.
 * The section is one part of a dimension in the array (The array column that stores the levels of my gold mines)
 */

void getGoldMineLevels(int numGoldMines) {
    int counter = 0;
    int goldMineCounter = 1;

    for (counter = 0; counter < numGoldMines; counter++) {
        printf("Please enter the level of goldmine # %d: ", goldMineCounter);
        scanf("%d", &goldMine[counter][LEVEL]);
        fgetc(stdin);

        while (goldMine[counter][LEVEL] <= 0 || goldMine[counter][LEVEL] > 12) {
            printf("Invalid input for the gold mine levels, please try again: ");
            scanf("%d", &goldMine[counter][LEVEL]);
            fgetc(stdin);
        }
        goldMineCounter++;
    }

}

/*
 * Purpose: Providing any level of a gold mine within our boundaries (1-12),
 * this function matches the correct level with its corresponding rate.
 *
 * Parameters:
 * level: The level of a gold mine.
 *
 * Return Value: rate: The rate of a gold mine level.
 *
 * Side Effects: None.
 */
int getRates(int level) {
    int rate = 0;

    if (level == 1) {
        rate = 200;
    } else if (level == 2) {
        rate = 400;
    } else if (level == 3) {
        rate = 600;
    } else if (level == 4) {
        rate = 800;
    } else if (level == 5) {
        rate = 1000;
    } else if (level == 6) {
        rate = 1300;
    } else if (level == 7) {
        rate = 1600;
    } else if (level == 8) {
        rate = 1900;
    } else if (level == 9) {
        rate = 2200;
    } else if (level == 10) {
        rate = 2500;
    } else if (level == 11) {
        rate = 3000;
    } else if (level == 12) {
        rate = 3500;
    }

    return rate;
}

/*
 * Purpose: This function calls the function that gets the rates, and stores that specific
 * value into the section of the 2D array for the rates. This is looped to find all of
 * the rates of each gold mine.
 *
 *
 * Parameters:
 * numGoldMines: The number of gold mines. The level of the gold mine in the function is now not an
 * integer like the function above, but we put the part of the 2D array that stores our levels
 * as the parameter for the function we call getRates.
 *
 * Return Value: None.
 *
 * Side Effects: Modifies a section of the global variable in my 2D array based on the specific rates
 * that matches with the corresponding levels of each of the users gold mines .
 * The section is one part of a dimension in the array
 * (The array column that stores the rates of my gold mines)
 */

void getGoldMineRates(int numGoldMines) {
    int counter = 0;

    for (counter = 0; counter < numGoldMines; counter++) {
        goldMine[counter][RATE] = getRates(goldMine[counter][LEVEL]);
    }
}

/*
 * Purpose: This function prints the number of gold mines and the levels of the
 * gold mines into the input file given.
 *
 * Parameters:
 * inputFile: The input file name.
 * numGoldMines: the number of gold mines.
 * The levels are not a parameter because it is placed within a global variable that can be
 * accessed in any function.
 *
 * Return Value: None.
 *
 * Side Effects: None. (Doesn't modify the value of the global variable with our 2D array,
 * only prints it in the file.)
 */

void printGoldMineInfoInFile(FILE *inputFile, int numGoldMines) {

    int counter = 0;

    fprintf(inputFile, "%d", numGoldMines);
    for (counter = 0; counter < numGoldMines; counter++) {
        fprintf(inputFile, "\n%d", goldMine[counter][LEVEL]);
    }
}

/*
 * Purpose: Asks how much gold the user currently has. The max is 8001000,
 * and they can't have less than 0, so while they input a value greater than 8001000
 * or less than 0 prompt them to input again.
 *
 * Parameters: None.
 *
 * Return Value: CurrentAmountGold: The amount of gold that the user currently has.
 *
 * Side Effects: None.
 */

int getGoldHave() {
    int CurrentAmountGold = 0;

    printf("\nHow much gold do you have?");
    scanf("%d", &CurrentAmountGold);
    fgetc(stdin);

    while (CurrentAmountGold < 0 || CurrentAmountGold > 8001000) {
        printf("\nInvalid amount of current gold, please try again: ");
        scanf("%d", &CurrentAmountGold);
        fgetc(stdin);
    }

    return CurrentAmountGold;
}

/*
 * Purpose: Asks the user how much gold they want to gain from their gold mines.
 * The amount of gold they want cannot be lower than the amount of gold they actually have.
 * The max is also 8 million, and they can't have less than 0, so while they input a
 * value greater than 8001000, less than 0 , or less than
 * their current amount of gold, prompt them to input again.
 *
 * Parameters: The amount of gold they want. (CurrentAmountGold)
 *
 * Return Value: AmountGoldWant: Returns the amount of gold the user wants.
 *
 * Side Effects: None.
 */

int getGoldWant(int CurrentAmountGold) {
    int AmountGoldWant = 0;

    printf("\nHow much gold do you want?");
    scanf("%d", &AmountGoldWant);
    fgetc(stdin);

    while (AmountGoldWant < CurrentAmountGold || AmountGoldWant < 0 || AmountGoldWant > 8001000) {
        printf("\nInvalid input for the amount of gold that you want, please try again: ");
        scanf("%d", &AmountGoldWant);
        fgetc(stdin);
    }


    return AmountGoldWant;
}

/*
 * Purpose: Calculates the amount of money that the gold mines will need to produce.
 *
 * Parameters:
 * CurrentAmountGold: The current amount of gold the user currently has.
 * AmountGoldWant: The amount of gold that that user wants.
 *
 * Return Value: MoneyNeedToProduce: The total gold that the gold mines will need to produce
 * to reach the users goal.
 *
 * Side Effects: None.
 *
 */

int MoneyNeedToProduce(int CurrentAmountGold, int AmountGoldWant) {
    int MoneyNeedToProduce = 0;

    MoneyNeedToProduce = AmountGoldWant - CurrentAmountGold;

    printf("\nYou need %d gold to reach your goal", MoneyNeedToProduce);

    return MoneyNeedToProduce;
}

/*
 * Purpose: Calculates the total rate of all the levels of the users gold mines.
 *
 * Parameters:
 * numGoldMines: The number of gold mines that the user has.
 *
 * Return Value: TotalRate: Returns the total rate of all the user's gold mines combined.
 *
 * Side Effects:  None.
 *
 */
int GetTotalRate(int numGoldMines) {
    int counter = 0;
    int TotalRate = 0;

    for (counter = 0; counter < numGoldMines; counter++) {
        TotalRate = TotalRate + goldMine[counter][RATE];
    }

    printf("\nYour total production rate is %d gold / hour \n", TotalRate);

    return TotalRate;
}

/*
 * Purpose: This function calculates the time needed to gain the amount of money
 * that the user wants. With this time total time needed in hours, it is then
 * split into other units of time (Weeks, days, minutes, seconds). It will only
 * print the specific unit if it is not equal to zero. (If the unit has a value)
 *
 * Parameters:
 * MoneyNeedToProduce: The total amount of money that the user needs to produce
 * from his mines
 *
 * TotalRate: The total rate of all the users gold mines combined.
 *
 * Return Value: None.
 *
 * Side Effects:  None.
 *
 */

void printTime(int MoneyNeedToProduce, int TotalRate) {
    double timeNeeded = 0;
    double timeNeededOriginal = 0;
    int secondsCounter = 0;
    int minutesCounter = 0;
    int hourCounter = 0;
    int daysCounter = 0;
    int weeksCounter = 0;



    timeNeeded = (double) MoneyNeedToProduce / TotalRate;
    timeNeededOriginal = timeNeeded;


    while (timeNeeded >= HOWMANYHOURSINONESECOND) { // while the amount of time in hours is greater than our smallest
        //unit of measurement,how many hours within a second, keep looping as it means the time can still be converted to a unit.
        if (timeNeeded >= HOWMANYHOURSINONEWEEK) { // Checks to see if the time in hours is greater than how many
            // hours within a week.
            weeksCounter++; // If it is that means you can covert those 168 hours into a week.
            timeNeeded = timeNeeded - HOWMANYHOURSINONEWEEK; // Subtract that value from your original number.
            // Keeps checking to see if the number if greater than how many hours in a week, if it is not anymore
            // it moves on to the else if statements in order to check.
        } else if (timeNeeded >= HOWMANYHOURSINONEDAY) { // Repeat using all the other units of time.
            daysCounter++;
            timeNeeded = timeNeeded - HOWMANYHOURSINONEDAY;
        } else if (timeNeeded >= 1) {
            hourCounter++;
            timeNeeded = timeNeeded - 1;
        } else if (timeNeeded >= HOWMANYHOURSINONEMINUTE) {
            minutesCounter++;
            timeNeeded = timeNeeded - HOWMANYHOURSINONEMINUTE;
        } else if (timeNeeded >= HOWMANYHOURSINONESECOND) {
            secondsCounter++;
            timeNeeded = timeNeeded - HOWMANYHOURSINONESECOND;
        }
    }


    if (timeNeededOriginal == 0) { // If the original time needed was 0 seconds,
        //we don't need to print time as they have already reached their goal.
        printf("\nYou already have your desired amount of gold, congratulations!");
    } else { // Otherwise print the time needed with different units if needed.
        printf("\nYou will get your desired amount of gold in: ");

        if (weeksCounter != 0) {
            printf("\n%d week(s)", weeksCounter); // Only print this unit if its greater than zero.
        }
        if (daysCounter != 0) {
            printf("\n%d day(s)", daysCounter); // Only print this unit if its greater than zero.
        }
        if (hourCounter != 0) {
            printf("\n%d hour(s)", hourCounter); // Only print this unit if its greater than zero.
        }
        if (minutesCounter != 0) {
            printf("\n%d minute(s)", minutesCounter); // Only print this unit if its greater than zero.
        }
        if (secondsCounter != 0) {
            printf("\n%d second(s)", secondsCounter); // Only print this unit if its greater than zero.
        }

        printf(".");
    }
}

int main(int argc, char** argv) {
    int FileExist = 0;
    int getGoldMines = 0;
    char CorrectData;
    int goldHave = 0;
    int goldWant = 0;
    int MoneyToProduce = 0;
    int TotalRate = 0;
    int counter = 0;
    //Initialize all variables, except for the char.

    FILE *inputFile;

    printf("Welcome to the Clash of Clans Calculator! ");
    getFileName();
    FileExist = CheckFileExist(inputFile);

    if (FileExist == FILE_EXIST) { // FILE_EXIST is a global variable.
        inputFile = fopen(inputFileName, "r"); // If the file exists, only open the file for read, as we don't need
        // to overwrite anything yet.
        getGoldMines = ReadFileInfo(inputFile);
        fclose(inputFile); // Closes the file after you are done looking into it.
        if (getGoldMines < 1 || getGoldMines > 7) { // If the number of gold mines is not
            //within the boundaries, assume data is not correct.
            CorrectData = 'n';
        } else {
            CorrectData = CheckIfDataCorrect(); // If the data is within the boundaries,
            // ask if the data is correct.
        }
        if (CorrectData == 'y') {
            getGoldMineRates(getGoldMines);
            goldHave = getGoldHave();
            goldWant = getGoldWant(goldHave);
            MoneyToProduce = MoneyNeedToProduce(goldHave, goldWant);
            TotalRate = GetTotalRate(getGoldMines);
            printTime(MoneyToProduce, TotalRate);

        } else if (CorrectData == 'n') {
            inputFile = fopen(inputFileName, "w"); // If the file is not correct, reopen the file as write,
            // as we need to overwrite the old data with the new inputted data from the keyboard.
            getGoldMines = getnumGoldMines();
            getGoldMineLevels(getGoldMines);
            getGoldMineRates(getGoldMines);
            printGoldMineInfoInFile(inputFile, getGoldMines);
            fclose(inputFile);
            goldHave = getGoldHave();
            goldWant = getGoldWant(goldHave);
            MoneyToProduce = MoneyNeedToProduce(goldHave, goldWant);
            TotalRate = GetTotalRate(getGoldMines);
            printTime(MoneyToProduce, TotalRate);
        }
    } else if (FileExist == FILE_NOT_EXIST) { // FILE_NOT_EXIST is a global variable.
        inputFile = fopen(inputFileName, "w"); // If the file does not exist, open the file as write
        // because if it doesn't exist it will create a file with the same name as the input File.
        getGoldMines = getnumGoldMines();
        getGoldMineLevels(getGoldMines);
        getGoldMineRates(getGoldMines);
        printGoldMineInfoInFile(inputFile, getGoldMines);
        fclose(inputFile);
        goldHave = getGoldHave();
        goldWant = getGoldWant(goldHave);
        MoneyToProduce = MoneyNeedToProduce(goldHave, goldWant);
        TotalRate = GetTotalRate(getGoldMines);
        printTime(MoneyToProduce, TotalRate);
    }

    return (EXIT_SUCCESS);
}
