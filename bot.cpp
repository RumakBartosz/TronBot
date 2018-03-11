#include <iostream>
#include <string.h>
#include <vector>
#include <ctype.h>
#include <time.h>

using namespace std;

vector<vector<int>> initArrayFromNotation(string notation)
{
    vector<vector<int>> array;
    int height = 0;
    int width = 1;

    for(int i = 0; i < notation.length(); i++)
    {
        if(isdigit(notation[i]))
            height += notation[i] - '0';
        if(isalpha(notation[i]))
            height++;
        if(notation[i] == '/')
            break;
    }

    for(int i = 0; i < notation.length(); i++)
    {
        if(notation[i] == '/')
            width++;
    }

    cout << height;
    cout << width;
    cout << endl;

    for(int w = 0; w < width; w++)
    {
        array.push_back(vector<int>());
        for(int h = 0; h < height; h++)
        {
            array[w].push_back(1);
        }
    }

    cout << height;
    cout << array.size();
    cout << width;
    cout << array[0].size();
    cout << endl;
    
    return array;
}

vector<vector<int>> notationToRepresentation(string notation)
{
    vector<vector<int>> representation = 
        initArrayFromNotation(notation);
    int height = representation.size();
    int width = representation[0].size();
    
        int counter = 0;

    for(int h = 0; h < height; h++)
    {

        for(int w = 0; w < width; w++)
        {
                
            if(isdigit(notation[counter]))
            {
                w += ((int)notation[counter] - '0') - 1;
                counter++;
            }
            else if(notation[counter] == 'R')
            {
                representation[h][w] = 2;
                counter++;
            }
            else if(notation[counter] == 'r')
            {
                representation[h][w] = 3;
                counter++;
            }
            else if(notation[counter] == 'B')
            {
                representation[h][w] = 4;
                counter++;
            }
            else if(notation[counter] == 'b')
            {
                representation[h][w] = 5;
                counter++;
            }
            else if(notation[counter] == '/')
            {
                w -= 1;
                counter++;
                //break;
            }
            else
            {
                counter++;
            }

        }
    }
    

    for(int wi = 0; wi < height; wi++)        
    {                                         
        for(int he = 0; he < width; he++)            
        { 
            cout << representation[wi][he]; 
        } 
        cout << endl;
    }

    cout << endl;

    return representation;
}

string representationToNotation(vector<vector<int>> representation)
{
    return "";
}

enum player 
{
    RED = 2,
    BLUE = 4
};

enum direction
{
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4
};

vector<int> availablePositionCollection(vector<vector<int>> representation, player presentTurn)
{
    int height = representation.size();
    int width = representation[0].size();
    
    vector<int> moveCollection;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(representation[i][j] == presentTurn)
            {
                if((i > 0) && (representation[i-1][j] == 1))
                    moveCollection.push_back(UP);

                if((i < height - 1) && (representation[i+1][j] == 1))
                    moveCollection.push_back(DOWN);

                if((j > 0) && (representation[i][j-1] == 1))
                    moveCollection.push_back(LEFT);

                if((j < width - 1) && (representation[i][j+1] == 1))
                    moveCollection.push_back(RIGHT);
            }
        }
    }

    for(int length = 0; length < moveCollection.size(); length++)
    {
        cout << moveCollection[length];
    }
    cout << endl;

    return moveCollection;
}

int chooseMoveFromCollection(vector<int> moveCollection)
{
    int randomMove = rand() % moveCollection.size();

    return moveCollection[randomMove];
}

int chooseMove(vector<vector<int>> representation, player presentTurn)
{
    int height = representation.size();
    int width = representation[0].size();
    int presentPositionHeight = 0;
    int presentPositionWidth = 0;
    int moveCounter = 0;
    

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(representation[i][j] == presentTurn)
            {
                representation[i][j] == 3;
                int presentPositionHeight = i;
                int presentPositionWidth = j;
                break;
            }
        }
    }

    if((presentPositionHeight < height) && (representation[presentPositionHeight+1][presentPositionWidth] == 1))
        moveCounter++;

    if((presentPositionHeight > 0) && (representation[presentPositionHeight-1][presentPositionWidth] == 1))
        moveCounter++;

    if((presentPositionWidth < width) && (representation[presentPositionHeight][presentPositionWidth+1] == 1))
        moveCounter++;

    if((presentPositionWidth > 0) && (representation[presentPositionHeight][presentPositionWidth-1] == 1))
        moveCounter++;

    int randValue = rand() % moveCounter + 1;

    vector<int> usableCollection = availablePositionCollection(representation, RED);
    int choosenMove = chooseMoveFromCollection(usableCollection);
    //if 0 return err
    //if > 0 rand move, save representation, parse to string;

    return choosenMove;
}

int main()
{
    srand (time(NULL));
    for(;;)
    {
        string incomingState;
        cin >> incomingState;
        vector<vector<int>> stateAfterMove = 
            notationToRepresentation(incomingState);
        cout << chooseMove(stateAfterMove,RED);
    }

    return 0;
}
