#include<iostream>
using namespace std;



void cleaner(string uncleaned)
{
    cout<<uncleaned.size()<<endl;
	for (int i = 0, len = uncleaned.size(); i < len; i++)
    {
        cout<<uncleaned[i]<<"  ";
        if(uncleaned[i]>=65 && uncleaned[i]<=90)
        {
            uncleaned[i] = uncleaned[i] + 32;
        }
        if (uncleaned[i]>122 || uncleaned[i]<97)
        {
            
            uncleaned.erase(i--, 1);
            len = uncleaned.size();
            
        }
        cout<<uncleaned[i]<<endl;
    }
    cout<<uncleaned<<endl;
    cout<<uncleaned.size()<<endl;
}

int main()
{
    //cout<<tolower("...""""Grandfather,",locale());
    cleaner("ΓÇ£....,,,,Grandfather'sS,");
}