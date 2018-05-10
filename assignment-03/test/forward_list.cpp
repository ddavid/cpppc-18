#include <forward_list>
#include <iostream>

int main (int argc, char * argv[])
{
    std::forward_list<int> list;

    list.push_front(10);

    int & elem = list.front();
    std::cout <<  elem << std::endl;
}
