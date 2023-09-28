//doesn't work on non windows system
//should return ascii_value for system

#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;
int main()
{
    char key_press;
    int ascii_value;
    cout<<"\n\t\t\tPress Any Key To Check  Its ASCI Value\n\n\t\t\tPress ESC to EXIT\n\n\n";
    while(1)
    {
    key_press=getch();
    cout << key_press;
    return 0;
}
