#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<map>
#include<list>
#include<stack>
#include<regex>
using namespace std;

map<string, map<int, list<int>>> lexicon;
list<string> stopwords;



template<typename Map>
void PrintInFile(Map &m)
{
	fstream file;
	file.open("lexicon.txt");
	file << "[ \n";
    for (auto &item : m) {
		if(item.first == "")
		{
			continue;
		}
        file <<"\t"<< item.first << ":[\n";
		for (auto &item2 : item.second ) {
			file <<"\t\t"<< item2.first << ":{ ";
			for (auto &item3 : item2.second ) {
				file<< item3<<",";
			}
			file<<"},\n ";
		}
		file<<"]\n"<<endl;
    }
    file << "\t]\n";
	file.close();
}


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
            i++;
        }
    }
    for(int j = 0; j < 26;j++)
    {
        cout << stopwords[j] << endl;
    }

    myReadFile1.close();
    cout << endl;
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

template<typename Map>
void PrintMap(Map& m)
{
    cout << "[ ";
    for (auto &item : m) {
        cout << item.first << ":[";
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

void stop_words_remover()
{
	fstream file;
	file.open("Stopword-List.txt");
	string data;
	while(!file.eof()){
			file >> data;
			lexicon.erase(data);
		}
		lexicon.erase(" ");
	file.close();
}

void preprocessing()
{
	fstream file;
	string folder = "./ShortStories/";
	string ext = ".txt";
	

	for (int i=1; i<=50;i++)
	{
		string data;
		string curr = to_string(i);
		file.open(folder+curr+ext);
		int count = 0;
		while(!file.eof()){
			file >> data;
			data = cleaner(data);
			lexicon[data][i].push_back(count);
			count++;
		}
		file.close();
	}
	stop_words_remover();
	PrintInFile(lexicon);
	//PrintMap(lexicon); //uncomment to see the whole dictionary
	//cout<<endl<<lexicon.size()<<endl; // uncomment to see the dictionary size
}

int main()
{
    preprocessing();
}