#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

class edge
{
public:
    int weight;
    int in1;
    int in2;
};

using namespace std;
void read(string input);
void undirected();
void directed();
void write(string output);
bool dfs(int &i);
int find(int &i);
string sit;
int v;
int e;
vector<int> w;
vector<int> i1;
vector<int> i2;
vector<int> ow;
vector<int> o1;
vector<int> o2;
vector<vector<int>> c;
int* explored;
int* current;
vector<int> parent;
vector<int> r;
vector<edge> a;
bool sortfunction (edge i,edge j) { return i.weight > j.weight; }


int main(int argc, char** argv)
{
    read(argv[1]);
    std::sort(a.begin(),a.begin()+e,sortfunction);
    for(int i=0;i<e;i++)
    {
        ow.push_back(a[i].weight);
        o1.push_back(a[i].in1);
        o2.push_back(a[i].in2);
    }
    if(sit == "u")
    {
        undirected();
    }
    else if(sit == "d")
    {
        directed();
    }
    write(argv[2]);
}

void read(string input)
{
    fstream file;
    string temp;
    file.open(input);
    if(file.is_open())
    {
        getline(file,sit);
        getline(file,temp);
        v = stoi(temp);
        getline(file,temp);
        e = stoi(temp);
        
        while(getline(file,temp))
        {
            if(temp == "0"){return;}
            int n = 0;
            int t = 0;
            edge ed;
            for(int i=0;i<temp.size();i++)
            {
                if(temp[i] == ' ' && t == 0)
                {
                    ed.in1 = stoi(temp.substr(n,i-n));
                    n = i+1;
                    t = 1;
                }
                else if(temp[i] == ' ' && t == 1)
                {
                    ed.in2 = stoi(temp.substr(n,i-n));
                    n = i+1;
                }
                else if(i == temp.size()-1)
                {
                    ed.weight = stoi(temp.substr(n,i-n+1));
                }
            }
            a.push_back(ed);
        }
    }
}

void undirected()
{
    vector<int> index;
    for(int i=0;i<v;i++)
    {
        parent.push_back(i);
        r.push_back(0);        
    }
    for(int i=0;i<ow.size();i++)
    {
        int c1 = find(o1[i]);
        int c2 = find(o2[i]);
        if(c1 != c2)
        {
            w.push_back(ow[i]);
            i1.push_back(o1[i]);
            i2.push_back(o2[i]);
            index.push_back(i);
            if(w.size() == v-1){break;}
            if (r[c1] < r[c2]) 
            {
                parent[c1] =  parent[c2];
            } 
            else if(r[c1] > r[c2]) 
            {
                parent[c2] =  parent[c1];
            } 
            else
            {
                parent[c1] =  parent[c2];
                r[c2]++;
            }
        }
    }
    
    int s = ow.size();
    int** arr;
    arr = new int*[s];
    
    for(int i=0;i<s;i++)
    {
        arr[i] = new int[3];
    }
    for(int i=0;i<s;i++)
    {
        arr[i][0] = ow[i];
        arr[i][1] = o1[i];
        arr[i][2] = o2[i];
    }
    for(int i=0;i<index.size();i++)
    {
        arr[index[i]][0] = 101;
    }
    ow.clear();
    o1.clear();
    o2.clear();
    for(int i=0;i<s;i++)
    {
        if(arr[i][0] != 101)
        {
            ow.push_back(arr[i][0]);
            o1.push_back(arr[i][1]);
            o2.push_back(arr[i][2]);
        }
    }
}

void directed()
{
    undirected();
    for(int i=0;i<v;i++)
    {
        vector<int> t;
        c.push_back(t);
    }
    for(int i=0;i<w.size();i++)
    {
        c[i1[i]].push_back(i2[i]);
    }
    vector<int> index;
    explored = new int[v];
    current = new int[v];
    for(int i=0;i<v;i++)
    {
        explored[i] = 0;
        current[i] = 0;
    }
    for(int i=0;i<ow.size();i++)
    {
        if(ow[i] > 0)
        {
            for(int i=0;i<v;i++)
            {
                explored[i] = 0;
                current[i] = 0;
            }
            w.push_back(ow[i]);
            i1.push_back(o1[i]);
            i2.push_back(o2[i]);
            index.push_back(i);
            c[o1[i]].push_back(o2[i]);
            for(int j=0;j<v;j++)
            {
                if(!dfs(j))
                {
                    w.pop_back();
                    i1.pop_back();
                    i2.pop_back();
                    index.pop_back();
                    c[o1[i]].pop_back();
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }
    
    int s = ow.size();
    int** arr;
    arr = new int*[s];
    
    for(int i=0;i<s;i++)
    {
        arr[i] = new int[3];
    }
    for(int i=0;i<s;i++)
    {
        arr[i][0] = ow[i];
        arr[i][1] = o1[i];
        arr[i][2] = o2[i];
    }
    for(int i=0;i<index.size();i++)
    {
        arr[index[i]][0] = 101;
    }
    ow.clear();
    o1.clear();
    o2.clear();
    for(int i=0;i<s;i++)
    {
        if(arr[i][0] != 101)
        {
            ow.push_back(arr[i][0]);
            o1.push_back(arr[i][1]);
            o2.push_back(arr[i][2]);
        }
    }
}

void write(string output)
{
    std::ofstream outfile(output);
    int sum = 0;
    for(int i=0;i<ow.size();i++)
    {
        sum += ow[i];
    }
    outfile << sum << endl;
    for(int i=0;i<ow.size();i++)
    {
        outfile << o1[i] << " " << o2[i] << " " << ow[i] << endl;
    }
}

bool dfs(int &i)
{ 
    if(explored[i] == 0)
    {
        explored[i] = 1; 
        current[i] = 1; 
        for(int j=0;j<c[i].size();j++)
        {
            if(current[c[i][j]] == 1)
            {
                return false;
            }
            else if(explored[c[i][j]] == 0)
            {
                if(!dfs(c[i][j]))
                {return false;}
            }
        }
    }
    current[i] = 0;
    return true;
}

int find(int &i)
{
    if(parent[i] == i)
    {
        return i;
    }
    int root = find(parent[i]);
    parent[i] = root;
    return root;
}