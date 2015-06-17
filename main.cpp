#include <iostream>
#include <stdio.h>
#include <list>
#include <string.h>
#include <vector>

using namespace std;

int main()
{
    int the_size,x,y;
    string a, b;
    cin >> the_size; // get size

    // assign initial blocks
    int ** the_blocks = new int*[the_size];
    for(int i = 0; i< the_size;++i)
        the_blocks[i] = new int[2];

    //int the_blocks [the_size][2]; //the blocks
    //int the_line [the_size][the_size+1]; //the line
    int ** the_line = new int*[the_size];
    for(int i = 0; i< the_size;++i)
        the_line[i] = new int[the_size+1];

    vector<int> the_queue;// the queue to return the excess blocks

    for (int i = 0; i< the_size; i++){
        the_blocks[i][0] = the_line[i][0] = i; // the position to both the blocks and the line
        the_blocks[i][1] = 0; // the level
        the_line[i][the_size] = 1; // initial number of blocks on each line
    }//assign initial blocks

    cin >> a ;
    while (a!="quit"){
         cin >> x >> b >> y;
         if (x==y || the_blocks[x][0]==the_blocks[y][0] || !(a == "move" || a == "pile") || !(b=="onto" || b=="over")){
                //cout << "invalid move! type write command again" <<endl;
                cin >> a;
             continue;//continue
         }else{//command and move is legal

              int originalPos = the_blocks[x][0];
              int destPos = the_blocks[y][0];
              int originalLvl = the_blocks[x][1];
              int destLvl = the_blocks[y][1];


         if (a=="move" ){//move command
                for(int j = (the_line[originalPos][the_size]-1);j>originalLvl;j--){//get rid of blocks over block a
                    the_queue.push_back(the_line[originalPos][j]);//store one block to the queue
                    the_line[originalPos][the_size]--;//one that lane of the line, elements go down by one
                    //cout << "store:"<<the_line[the_blocks[x][0]][j] <<endl;
                }//get rid of blocks over block a
                if ( b == "onto"){
                    for(int k = (the_line[destPos][the_size]-1);k>destLvl;k--){//get rid of blocks over block a
                        the_queue.push_back(the_line[destPos][k]);//store one block to the queue
                        the_line[destPos][the_size]--;//one that lane of the line, elements go down by one
                    }//get rid of blocks over block a
                }
                //now is the real work
                the_line[originalPos][the_size]--; //delete one unit of the original lane
                the_blocks[x][0] = destPos; // change position of x
                the_blocks[x][1] = the_line[destPos][the_size]; //change its level
                the_line[destPos][the_line[destPos][the_size]] = x; // place block x onto the line
                the_line[destPos][the_size] ++; //change the line

         }else{//pile command
              int beginIter = the_blocks[x][1];
              int endIter = the_line[the_blocks[x][0]][the_size];
              if ( b == "onto"){
                    for(int k = (the_line[destPos][the_size]-1);k>destLvl;k--){//get rid of blocks over block a
                        the_queue.push_back(the_line[destPos][k]);//store one block to the queue
                        the_line[destPos][the_size]--;//one that lane of the line, elements go down by one
                    }//get rid of blocks over block a
              }//end of get rid of
              //now it is the real work


              for ( int i = beginIter;i< endIter;i++){//move the whole pile
                   the_line[originalPos][the_size]--; //delete one unit of the original lane

                   the_blocks[the_line[originalPos][i]][0] = destPos; //change the position for the block
                   the_blocks[the_line[originalPos][i]][1] = the_line[destPos][the_size];//change its level
                   the_line[destPos][the_line[destPos][the_size]] = the_line[originalPos][i];//change the line
                   the_line[destPos][the_size] ++; //change the line
              }
         }
         //now is to put the queue into the line
         //cout << "Queue size:" << the_queue.size()<<endl;
         int temp2 = the_queue.size();
         for (int i = 0; i < temp2;i++){
            int temp = the_queue.back();//get the last element
            //cout << "temp:" << temp;
            //cout << "2 Queue size:" << the_queue.size()<<endl;
            the_blocks[temp][0] = temp;//place it to its own position
            the_blocks[temp][1] = the_line[temp][the_size];//set its level
            the_line[temp][the_line[temp][the_size]] = temp; // change the line
            the_line[temp][the_size] ++; // change the line
            the_queue.pop_back();//delete the last element
         }


    }//end of the if loop
    cin >> a; // get the next line



    }// end of the command loop
    //return the final state of the line
  //  cout<<"here is the results:" << endl;
    for(int n = 0; n < the_size;n++){
        cout << n << ":";
        for (int i = 0;i<the_line[n][the_size];i++){
            cout << " " << the_line[n][i];
        }
        cout << endl;
    }

    return 0;
}
