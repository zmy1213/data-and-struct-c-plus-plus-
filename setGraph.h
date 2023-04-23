#ifndef SETGRAPH_H
#define SETGRAPH_H

#include<unordered_map>
#include<stack>
using namespace std;
template<typename T>
struct Element
{
	T val;
	Element() = default;
	Element(T value) :val(value) {}
};
template<typename T>
class UnionFindSet
{
private:
	
	unordered_map<T, Element<T>*> elementMap;
	unordered_map<Element<T>*, Element<T>*>fatherMap;
	unordered_map<Element<T>*, int> sizeMap;

public:
	UnionFindSet(vector<T>& list)
	{
		for (auto& value : list)
		{
			Element<T>* element = new Element<T>(value);
			elementMap.emplace(value, element);
			fatherMap.emplace(element, element);
			sizeMap.emplace(element, 1);
		}
	}

	Element<T>* findHead(Element<T>* element)
	{
		stack<Element<T>*> path;
		while (element != (fatherMap.find(element))->second)
		{
			path.push(element);
			element = fatherMap.find(element)->second;
		}

		while (!path.empty())
		{
			fatherMap[path.top()] = element;
			path.pop();
		}
		return element;
	}

	bool isSameSet(T a, T b)
	{
		if ((elementMap.find(a) != elementMap.end()) && (elementMap.find(b) != elementMap.end()))
		{
			return findHead(elementMap.find(a)->second) == findHead(elementMap.find(b)->second);
		}
		return false;
	}

	void Union(T a, T b)
	{
		if (elementMap.count(a) && elementMap.count(b))
		{
			Element<T>* aF = findHead(elementMap.find(a)->second);
			Element<T>* bF = findHead(elementMap.find(b)->second);

			if (aF != bF)
			{
				Element<T>* big = sizeMap.find(aF)->second >= sizeMap.find(bF)->second ? aF : bF;
				Element<T>* small = big == aF ? bF : aF;
				fatherMap[small] = big;
				sizeMap.emplace(big, sizeMap.find(aF)->second + sizeMap.find(bF)->second);
				sizeMap.erase(small);
			}
		}
	}
};

#endif // !

