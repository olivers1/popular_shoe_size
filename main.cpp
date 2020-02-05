#include <iostream>
#include <vector>
#include <map>

using namespace std;

class API
{
private:
	struct Person
	{
		int shoeSize;
		string name;
	};
	vector<Person> m_vecNameShoeSize;
public:
	API() : m_vecNameShoeSize(10)	// set vector size
	{
		string arrName[] = { "Bob", "Luuk", "Charles", "Jan", "Jenny", "Sue", "Karen", "Filippa", "Mike", "Charles" };
		int arrShoeSize[] = { 42, 39, 45, 41, 36, 42, 37, 45, 44, 45 };

		// create vector containing name and shoe size for each item in vector
		for (int i = 0; i < sizeof(arrName) / sizeof(arrName[0]); i++)
		{
			m_vecNameShoeSize[i].name = arrName[i];
			m_vecNameShoeSize[i].shoeSize = arrShoeSize[i];
		}
	}

	const int& GetShoeSize(int i)
	{
		return m_vecNameShoeSize[i].shoeSize;
	}

	const string& GetName(int i)
	{
		return m_vecNameShoeSize[i].name;
	}

	const int& GetVectorSize() const
	{
		return m_vecNameShoeSize.size();
	}
};

int main()
{
	API API;
	
	map<int, int> mapShoeSize;
	map<int, int>::iterator it;
	for (int i = 0; i < API.GetVectorSize(); i++)
	{
		it = mapShoeSize.find(API.GetShoeSize(i));
		if (it != mapShoeSize.end())
		{
			it->second += 1;	// increase the keys counter value
		}
		else
		{
			mapShoeSize.insert(pair<int, int>(API.GetShoeSize(i), 1));	// insert all unique keys from vector in API, set count value to 1
		}
	}
	
	// check which shoe size that is most popular and store its value into variable
	int ShoeSizeCountMax = 1;
	int mostPopularSize = -1;
	for (auto it = mapShoeSize.begin(); it != mapShoeSize.end(); it++)
	{
		if (it->second > ShoeSizeCountMax)
		{
			ShoeSizeCountMax = it->second;
			mostPopularSize = it->first;
		}
	}

	// check which name that is most popular among the persons with the most popular shoe size
	map<string, int> mapNamePopularSize;
	map<string, int>::iterator it2;
	for (int i = 0; i < API.GetVectorSize(); i++)
	{
		if (API.GetShoeSize(i) == mostPopularSize)
		{
			it2 = mapNamePopularSize.find(API.GetName(i));
			// check if name (key) is already inserted into the map
			if (it2 != mapNamePopularSize.end())
			{
				it2->second += 1;	// key already exists, increase its second counter value
			}
			else
			{
				mapNamePopularSize.insert(pair<string, int>(API.GetName(i), 1));	// key were not found in the list, add name (key) to the map
			}
		}
	}

	int nameCountMax = 1;
	string mostPopularNameForShoeSize = "";
	for (auto it = mapNamePopularSize.begin(); it != mapNamePopularSize.end(); it++)
	{
		if (it->second > nameCountMax)
		{
			nameCountMax = it->second;
			mostPopularNameForShoeSize = it->first;
		}
	}

	// print the map containing all unique shoe sizes that are provided and their frequency of occurrence
	for (auto it = mapShoeSize.begin(); it != mapShoeSize.end(); it++)
	{
		cout << it->first << ", " << it->second << endl;
	}

	cout << "-----------------" << endl;

	// print the map containing all unique names and their frequency of occurrence for the most popular shoe size
	for (auto it = mapNamePopularSize.begin(); it != mapNamePopularSize.end(); it++)
	{
		cout << it->first << ", " << it->second << endl;
	}

	cout << "-----------------" << endl;
	
	// answer problem #1
	cout << mostPopularSize << endl;

	// answer problem #2
	cout << mostPopularNameForShoeSize << endl;

	return 0;
}