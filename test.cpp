#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<list>
using namespace std;
void fileread()
{
	cout<<"hello"<<endl;
    string stopwords[35];
    ifstream myReadFile1;
    string dirname = "./Stopword-List.txt";
    myReadFile1.open(dirname);
    string output;
    int i = 0;
    if (myReadFile1.is_open())
    {
        while (!myReadFile1.eof())
        {
            myReadFile1 >> output;
            stopwords[i] = output;
			//cout<<stopwords[i]<<endl;
            i++;
        }
    }
	//cout<<stopwords[0]<<endl;
    for(int j = 0; j < 26;j++)
    {
        cout << stopwords[j] << endl;
    }

    myReadFile1.close();
    cout << endl;
}

template<typename Map>
void PrintMap(Map& m)
{
    cout << "[ ";
    for (auto &item : m) {
        cout << item.first << ":[";// << item.second << " ";
		for (auto &item2 : item.second ) {
			cout << item2.first << ":{ ";
			for (auto &item3 : item2.second ) {
				cout<< item3<<",";
			}
			cout<<"}, ";
		}
		cout<<"]"<<endl;
    }
    cout << "]\n";
}

string cleaner(string uncleaned)
{
	for (int i = 0, len = uncleaned.size(); i < len; i++)
    {
        if(uncleaned[i]>=65 && uncleaned[i]<=90)
        {
            uncleaned[i] = uncleaned[i] + 32;
        }
        if (uncleaned[i]>122 || uncleaned[i]<97)
        {
            
            uncleaned.erase(i--, 1);
            len = uncleaned.size();
            
        }
    }
    return uncleaned;
}

class DocID {
	public:
		int DocNo;
		list<int> posInd;
};
// {
// 	//cout<<uncleaned.size()<<endl;
// 	for (int i = 0, len = uncleaned.size(); i < len; i++)
//     {
//         if (ispunct(uncleaned[i]) || uncleaned[i]=="“" ||uncleaned[i]=='’'|| uncleaned[i]=='“' )
//         {
//             uncleaned.erase(i--, 1);
//             len = uncleaned.size();
//         }
//     }
// 	return uncleaned;
//     // cout<<uncleaned<<endl;
//     // cout<<uncleaned.size()<<endl;
// }

int main()
{
	
	fstream file;
	string folder = "./ShortStories/";
	string ext = ".txt";
	//string all_of_it;
	map<string, map<int, list<int>>> lexicon;

	for (int i=1; i<=50;i++)
	{
		string data;
		string curr = to_string(i);
		file.open(folder+curr+ext);
		//cout<<i<<endl;
		int count = 0;
		while(!file.eof()){
			file >> data;
			data = cleaner(data);
			lexicon[data][i].push_back(count);
			//lexicon[data]++;
			//all_of_it.append(data);
			//cout << data <<endl;
			count++;
		}
		
		file.close();
	}
	lexicon[" "].~map();
	lexicon.erase(" ");
	PrintMap(lexicon);
	cout<<endl<<lexicon.size()<<endl;
	// cout << all_of_it;
	cout<<"THE END!";
	//fileread();
}
