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


//reads file for stop words
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

//prints whole dictionary wuth positional index
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

//utility function for printing list
void printlist(list<string> const &list)
{
    for (auto const& i: list) {
        std::cout << i << "\n";
    }
}

void printlist(list<string> const &list,int f)
{
    for (auto const& i: list) {
        std::cout << i << " ";
    }
	cout<<endl;
}

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

//cleans the punctuation from words
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

//removes stop words
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

// reads all the files and makes a lexicon 
// then cleans the words and removes stop words
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

map<int, list<int>> getIncidentDocIDs(string query_word)
{
	return lexicon[query_word];

}

void printList(list<int> s)
{
	for (auto const& i: s) {
        cout << i << " ";
    }
	cout<<endl;
 }

 void printList(list<map<int, list<int>>> s)
{
	for (auto const& i: s) {
		cout << "[ ";
        for (auto &item : i) {
			cout << item.first << ":{";
			for (auto &item2 : item.second ) {
				cout << item2 << ", ";
			}
			cout<<"}, ";
		}
		cout<<"]\n";
    }
 }


// retuns list of the words if they in in the proximity of "prox"
list<int> proximity(map<int, list<int>> t1,map<int, list<int>>t2, int prox)
{
	list<int> answer;
	for(auto &p1: t1)
	{
		for(auto &p2: t2)
		{
			if(p1.first == p2.first)
			{
				for(auto &v1: p1.second)
				{
					for(auto &v2:p2.second )
					{
						int distance = abs(v1-v2);
						if(distance && distance <= prox)
						{
							answer.push_back(p1.first);
							//cout<<p1.first<<endl;
						}
					}
				}
			}
		}
	}
	return answer;
}

list<string> get_query()
{
	string query ;
	list<string> query_list;
	getline(cin,query);

	if(query == "end")
	{
		return query_list;
	}
	
	char * cstr = new char [query.length()+1];
	std::strcpy (cstr, query.c_str());


	char * p = std::strtok (cstr," ");
	while (p!=0)
  	{
    	//std::cout << p << '\n';
		query_list.push_back(p);
    	p = std::strtok(NULL," ");
  	}
  	delete[] cstr;

	return query_list;
}


bool Precedence(string a , string b)//returns true if precedence of b is greater than a , a is the stacks peek operator and b is the operator from string
{
	
	if(b=="not")
	{
		return true;
	}
	else if(b=="and" && a!="not" )
	{
		return true;
	}
	else if(b=="or" &&(a!="not" || a!="and"))
	{
		return true;
	}

	return false;
}

list<int> get_list(string str)
{
	list<int> keys;
	for(map<int,list<int>>::iterator it = lexicon[str].begin(); it != lexicon[str].end(); ++it) {
  		keys.push_back(it->first);
	}
	return keys;
}

// template<typename Map>
// void loading(Map &m)
// {
// 	fstream file;
// 	file.open("lexicon.txt");
// 	file >> "[ \n";
//     for (auto &item : m) {
// 		string word;
//         file >>"\t">> word >> ":[\n";
// 		for (auto &item2 : item.second ) {
// 			int num1;
// 			file >>"\t\t">> num1 >> ":{ ";
// 			for (auto &item3 : item2.second ) {
// 				int num2;
// 				file>> num2>>",";
// 			}
// 			file>>"},\n ";
// 		}
// 		file>>"]\n\n";
//     }
//     file >> "\t]\n";
// 	file.close();
// }

list<string> make_postfix(list<string> query)
{
	list<string> stack1;
	list<string> postfix;
	int n;
	int i;
	for(auto &str : query)
	{
		
		if(str != "and" && str != "not" && str != "or" )
		{
			postfix.push_back(str);
		}
		else
		{
			if(stack1.empty() || Precedence(stack1.back(), str))
			{
				stack1.push_back(str);
			}
			else
			{
				
				while( !stack1.empty()  )
				{
					if(!Precedence(stack1.back(),str))
					{
						postfix.push_back(stack1.back());
						string c = stack1.back();
						stack1.pop_back();
					}
					
				}
				
				stack1.push_back(str);
			}
		}
	}
	while(!stack1.empty())
	{
		postfix.push_back(stack1.back());
		stack1.pop_back();
	}
		
	
	return postfix;
}

list<int> NOT(list<int> a)
{
	list<int> temp;
	list<int>::iterator it = a.begin();
	for(int i=1; i<50 ;i++)
	{
		if(i == *it && it != a.end())
		{
			it++;
		}
		else
		{
			temp.push_back(i);
		}
	}
	return temp;
}

list<int> AND(list<int> a, list<int> b)
{
	list<int>::iterator first1= a.begin(), first2 = b.begin(), last1 = a.end(), last2 = b.end();
	list<int> result;
	while (first1!=last1 && first2!=last2)
  	{
    	if 
			(*first1<*first2) ++first1;
    	else if 
			(*first2<*first1) ++first2;
    	else {
      		result.push_back(*first1); ++first1; ++first2;
    	}
  	}
	  return result;
}

list<int> OR(list<int> a, list<int> b)
{
	list<int>::iterator first1= a.begin(), first2 = b.begin(), last1 = a.end(), last2 = b.end();
	list<int> result;
	while (first1!=last1 && first2!=last2)
  	{
    	if (*first1<*first2) 
		{
			result.push_back(*first1); ++first1; 
		}
    	else if (*first2<*first1) 
		{ 
			result.push_back(*first2); ++first2; 
		}
    	else 
		{ 
			result.push_back(*first1); ++first1; ++first2; 
		}
  	}
	  return result;
}

//start from here 
list<int> Evaluate(list<string> postfix)
{
	list<list<int>> stack_h;
	list<string> stack_h2;
	int n;
	for(auto &str : postfix)
	{
		
		if(str != "and" && str != "not" && str != "or")
		{
			stack_h.push_back(get_list(str));
			stack_h2.push_back(str);
		}
		else if(str == "not")
		{
			string a = stack_h2.back();
			stack_h2.pop_back();
			list<int> temp = stack_h.back();
			stack_h.pop_back();
			stack_h.push_back(NOT(temp));
			stack_h2.push_back("not "+ a);
		}
		else if(str == "and")
		{
			string a = stack_h2.back();
			stack_h2.pop_back();
			list<int> temp1 = stack_h.back();
			stack_h.pop_back();
			
			string b = stack_h2.back();
			stack_h2.pop_back();
			list<int> temp2 = stack_h.back();
			stack_h.pop_back();
			stack_h.push_back(AND(temp1,temp2));
			stack_h2.push_back(b + " and " + a);
		}
		else if(str == "or")
		{
			string a = stack_h2.back();
			stack_h2.pop_back();
			list<int> temp1 = stack_h.back();
			stack_h.pop_back();
			string b = stack_h2.back();
			stack_h2.pop_back();
			list<int> temp2 = stack_h.back();
			stack_h.pop_back();
			stack_h.push_back(OR(temp1,temp2));
			stack_h2.push_back(b + " or " + a);
		}
	}
	return stack_h.back();
}


int main()
{
	preprocessing();
	//loading();
	list<int> result;

	while(true)
	{
		list<string> query_list = get_query();
		if(query_list.empty())
		{
			break;
		}
		if(regex_match (query_list.back(),regex("(/)(.*)") ))
		{
			string temp = query_list.back();
			query_list.pop_back();
			int prox = temp[1] - '0';

			string a = query_list.front();
			map<int,list<int>> term1 = lexicon[a];
			query_list.pop_front();

			string b = query_list.front();
			map<int, list<int>> term2 = lexicon[b] ;
			query_list.pop_front();

			result = proximity(term1,term2,prox);
		}
		else
		{
			list<string> query_postfix = make_postfix(query_list);
		
			//printlist(query_postfix,0);

			result = Evaluate(query_postfix);
		}
		
		printList(result);



	}

	cout<<"THE END!";
}
