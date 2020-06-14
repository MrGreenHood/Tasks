#include <iostream>
#include <string>
#include "tree.h"


using namespace std;

int main()
{
    setlocale(LC_ALL,"RUS");
    string str;
    Tree a("(123/(2+3*(5+5))*4)");
    cout<<a.calculate()<<endl;
    cout<<a.calculate("(123/(2+3*(5))*4)")<<endl;
    cout<<a.calculate("(123/(2+3)*4)")<<endl;
    cout<<a.calculate("404")<<endl;
    cout<<a.calculate("   404  ")<<endl;
    cout<<a.calculate("3 * 3 * 3")<<endl;
    cout<<a.calculate("12 / 12 / 12")<<endl;
    cout<<a.calculate("25 + 17 / 45 / 2")<<endl;
    cout<<a.calculate("42 + 42 / 2 * 2")<<endl;
    cout<<a.calculate(" 4 * 4 + 3 * 3 + 2 * 2 ")<<endl<<endl;
    cout<<"¬ведите выражение:"<<endl;
    cin>>str;
    cout<<a.calculate(str)<<endl;


    return 0;
}
