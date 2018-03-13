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
        if(isdigit(notation[i]) && isdigit(notation[i+1]))
            height += (notation[i] - '0') * 10;
        else if(isdigit(notation[i]) && !isdigit(notation[i+1]))
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

    for(int w = 0; w < width; w++)
    {
        array.push_back(vector<int>());
        for(int h = 0; h < height; h++)
        {
            array[w].push_back(1);
        }
    }
       
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
                
            if(isdigit(notation[counter]) && isdigit(notation[counter+1]))
            {
                w += ((((int)notation[counter] - '0') * 10) + ((int)notation[counter] - '0') - 1);
                counter++;
            }
            else if(isdigit(notation[counter]) && !isdigit(notation[counter+1]))
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
            else if(notation[counter] == 'o')
            {
                representation[h][w] = 0;
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
    

    //for(int wi = 0; wi < height; wi++)        
    //{                                         
    //    for(int he = 0; he < width; he++)            
    //    { 
    //        cout << representation[wi][he]; 
    //    } 
    //    cout << endl;
    //}

    //cout << endl;

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

    //for(int length = 0; length < moveCollection.size(); length++)
    //{
    //    cout << moveCollection[length];
    //}
    //cout << endl;

    return moveCollection;
}

string chooseMoveFromCollection(vector<int> moveCollection)
{
    if(moveCollection.size() == 0)
        return "up";

    int randomMove = 0;
    randomMove = rand() % moveCollection.size();
 
    if(moveCollection[randomMove] == 1)
        return "up";

    if(moveCollection[randomMove] == 2)
        return "down";

    if(moveCollection[randomMove] == 3)
        return "left";

    if(moveCollection[randomMove] == 4)
        return "right";

    return "up";
}

string chooseMove(vector<vector<int>> representation, player presentTurn)
{
    vector<int> usableCollection = availablePositionCollection(representation, presentTurn);
    string choosenMove = chooseMoveFromCollection(usableCollection);
    //if 0 return err
    //if > 0 rand move, save representation, parse to string;

    return choosenMove;
}

int main()
{
    player presentColor;
    string move = "";

    srand (time(NULL));
    for(;;)
    {
        string incomingState;
        getline(cin, incomingState);

        if(incomingState == "exit")
            return 0;

        if(incomingState == "tbi")
            cout << "tbi ok";

        if(incomingState == "tbi v1")
            cout << "tbi v1 ok";

        if(incomingState == "color red")
        {
            presentColor = RED;
            cout << "color ok";
            break;
        }

        if(incomingState == "color blue")
        {
            presentColor = BLUE;
            cout << "color ok";
            break;
        }

    }

    for(;;)
    {
        string incomingState;
        getline(cin, incomingState);

        if(incomingState == "exit")
            return 0;
        
        if((((incomingState[0] == 'm') && (incomingState[1] == 'o')) && (incomingState[2] == 'v')) && (incomingState[3] == 'e'))
        {
            for(int i = 5; i < incomingState.length(); i++)
                move += incomingState[i];
        }
       // cout << presentColor << endl;
       // cout << move << endl;
        
        vector<vector<int>> stateAfterMove = 
            notationToRepresentation(move);
        cout << chooseMove(stateAfterMove, presentColor);
    }

    return 0;
}
