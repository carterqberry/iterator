#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Linked_list.h"
using namespace std;



int main(int argc, char * argv[]) {
    Linked_list<string> linked_list;
    Linked_list<string> newList;
    newList.clear();
    if (argc < 3)
    {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in)
    {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out)
    {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }



    for (string line; getline(in, line);)
    {
        string item1, item2;
        if (line.size() == 0) continue;

        istringstream iss(line);
        iss >> item1;
        out  <<item1;
        if (item1 == "Insert")
        {
            while (iss >> item2)
            {
                out  << " " << item2;
                linked_list.push_front(item2);
            }
        }
        else if (item1 == "PrintList")
        {
            if(!linked_list.empty())
            {
                out << " " << linked_list.toString();
            }
            else
            {
                out << " Empty!";
            }

        }
        else if (item1 == "Clear")
        {
            linked_list.clear();
            out << " OK";
        }
        else if (item1 == "Empty")
        {
            if(linked_list.empty())
            {
                out << " true";
            }
            else
            {
                out << " false";
            }

        }
        else if (item1 == "Delete")
        {
            if(linked_list.size() == 0)
            {
                out << " Empty!";
            }
            else
            {
                linked_list.pop_front();
                out << " OK";
            }

        }
        else if (item1 == "First")
        {
                out << " " << linked_list.front();
        }
        else if (item1 == "Remove")
        {
            while (iss >> item2)
            {
                while(linked_list.find(item2))
                {
                    linked_list.remove(item2);
                }
                out << " " << item2;
            }
        }
        else if (item1 == "Reverse")
        {
            linked_list.reverse();
            out << " OK";
        }
        else if (item1 == "Size")
        {
            out << linked_list.size();
        }
        else if (item1 == "Copy")
        {
             newList = linked_list;
             out << " OK";
        }
        else if (item1 == "PrintCopy")
        {
            if(!newList.size())
            {
                out << " Empty!";
            }
            else
            {
                out << " " << newList.toString();
            }

        }
        else if(item1 == "Find")
        {
            while (iss >> item2)
            {
                if(linked_list.find(linked_list.begin(), linked_list.end(), item2))
                {
                    out << " " << item2 << " OK";
                }
                else
                {
                    out <<" " << item2 << " Not Found";
                }
            }

        }
        else if(item1 == "InsertAfter")
        {
            while(iss >> item2)
            {
                string item3;
                iss >> item3;
                if(linked_list.find(linked_list.begin(), linked_list.end(), item3))
                {
                    out  << " " << item2 << " " << item3 << " " << "OK";
                    linked_list.insertAfter(linked_list.findPosition(linked_list.begin(), linked_list.end(), item3), item2);
                }
                else
                {
                    out <<" " << item2 << " " << item3 << " Not Found";
                }


            }

        }
        else if(item1 == "InsertBefore")
        {
            while(iss >> item2)
            {
                string item3;
                iss >> item3;
                if(linked_list.find(linked_list.begin(), linked_list.end(), item3))
                {

                    out  << " " << item2<< " " << item3 << " " << "OK";
                    linked_list.insertBefore(linked_list.findPositionBefore(linked_list.begin(), linked_list.end(), item3), item2);
                }
                else
                {
                    out <<" " << item2 << " " << item3 << " Not Found";
                }

            }

        }
        else if(item1 == "Erase")
        {
            while(iss >> item2)
            {
                if(linked_list.find(linked_list.begin(), linked_list.end(), item2))
                {
                    out  << " " << item2 << " " << "OK";
                    if(item2 == linked_list.begin().getNode()->data)
                    {
                        linked_list.pop_front();
                    }
                    else
                    {
                        linked_list.erase(linked_list.findPosition(linked_list.begin(), linked_list.end(), item2), linked_list.findPositionBefore(linked_list.begin(), linked_list.end(), item2));
                    }
                }
                else
                {
                    out <<" " << item2 << " Not Found";
                }

            }
        }
        else if(item1 == "Replace")
        {
            while(iss >> item2)
            {
                string item3;
                iss >> item3;
                if(linked_list.find(linked_list.begin(), linked_list.end(), item2))
                {
                    out  << " " << item2 << " " << item3 << " " << "OK";
                }
                if(item2 == item3)
                {
                    break;
                }
                if(item2 == linked_list.begin().getNode()->data)
                {
                    linked_list.replaceHead(linked_list.begin(), linked_list.end(), item2, item3);
                }
                while (linked_list.find(linked_list.begin(), linked_list.end(), item2))
                {
                    if(linked_list.find(linked_list.begin(), linked_list.end(), item2))
                    {
                        linked_list.replace(linked_list.begin(), linked_list.end(), item2, item3);
                    }
                    else
                    {
                        out <<" " << item2 << " Not Found";
                    }
                }
            }
        }
        else if(item1 == "Iterate")
        {
            if(linked_list.size() != 0)
            {
                out << linked_list.iterate();
            }
            else
            {
                out <<" Empty!";
            }

        }

        out << endl;
    }

//    if(linked_list.find(linked_list.begin(), linked_list.end(), item2))
//    {
//
//    }
//    else
//    {
//        out <<" " << item2 << " Not Found";
//    }

    return 0;
}
