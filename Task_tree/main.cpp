#include <iostream>
#include <string>
#include "tree.h"


using namespace std;

int main()
{

    Tree a("12/2+3*4");
    cout<<a.calculate()<<endl;
    cout<<a.calculate("404")<<endl;
    cout<<a.calculate("   404  ")<<endl;
    cout<<a.calculate("3 * 3 * 3")<<endl;
    cout<<a.calculate("12 / 12 / 12")<<endl;
    cout<<a.calculate("25 + 17 / 45 / 2")<<endl;
    cout<<a.calculate("42 + 42 / 2 * 2")<<endl;
    cout<<a.calculate(" 4 * 4 + 3 * 3 + 2 * 2 ")<<endl;

    return 0;
}
