#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
bool read(string input,vector<int> &start,vector<int> &end);
bool find(int a,int b,int &count);
bool write(string output,int e[][2],int chord);
#define max(a,b) (a>b?a:b)
int (*m)[20000] = new int[20000][20000];
int e[20000][2];
int *n = new int[20000];
int count = 0;
int main(int argc, char** argv)
{
    vector<int> start;
    vector<int> end;
    string t = argv[0];
    if(t == "./mps") 
    {  
        if(argc == 3) 
        {
            if (!read(argv[1],start,end)) 
            {
                cerr << "Error: cannot read in file \"" << argv[1] << "\"!!" << endl;
                return 0;
            }
        }
        else 
        {
            cerr << "Error: wrong command !!" << endl;
            return 0;
        }
    }
    else
    {
        cerr << "Error: wrong command !!" << endl;
        return 0;
    }
    int v = 2*start.size();
    for(int i = 0;i<v;i++){for(int j = 0;j<v;j++){m[i][j] = 0;}}
    for(int f = 0;f<start.size();f++)
    {
        if(start[f]>end[f])
        {
            int t = start[f];
            start[f] = end[f];
            end[f] = t;
        }
    }
    for(int f = 0;f<start.size();f++)
    {
        n[end[f]] = start[f];
        n[start[f]] = end[f];
    }
    for(int d = 1;d<v;d++)
    {
        for(int i = 0;i<v-d;i++)
        {
            if(n[i+d] > i+d || n[i+d] < i){m[i][i+d] = m[i][i+d-1];}
            else if(n[i+d] < i+d && n[i+d] > i){m[i][i+d] = max(m[i][n[i+d]-1]+1+m[n[i+d]+1][i+d-1],m[i][i+d-1]);}
            else if(n[i+d] == i){m[i][i+d] = m[i+1][i+d-1] +1;}
        }
    }
    find(0,v-1,count);
    int chord = m[0][v-1];
    for(int f = 0;f<m[0][v-1];f++)
    {
        for(int g = f+1;g<m[0][v-1];g++)
        {
            if(e[f][0] > e[g][0])
            {
                int t = e[f][0];
                e[f][0] = e[g][0];
                e[g][0] = t;
                t = e[f][1];
                e[f][1] = e[g][1];
                e[g][1] = t;
            }
        }
    }
    write(argv[2],e,chord);
}
bool read(string input,vector<int> &start,vector<int> &end)
{
    string temp;
    fstream file;
    file.open(input);
    int c = 0;
    if(file.is_open())
    {
        getline(file,temp);
        while(getline(file,temp))
        {
            if(temp == "0"){break;}
            for(int i = 0;i<temp.size();i++)
            {
                if(temp[i] == ' ')
                {
                    start.push_back(std::stoi(temp.substr(0,i)));
                    end.push_back(std::stoi(temp.substr(i+1,temp.size()-i)));
                    break;
                }
            }
        }
        file.close();
    }
    else
    {
        return false;
    }
    return true;
}
bool find(int a,int b,int &count)
{
    if(m[a][b] == 0){return true;}
    if(m[a][b] > m[a][b-1])
    {
        e[count][0] = n[b];
        e[count][1] = b;
        count++;
        find(a,n[b]-1,count);
        find(n[b]+1,b-1,count);
    }
    else{find(a,b-1,count);}
}
bool write(string output,int e[][2],int chord)
{
    std::ofstream outfile(output);
    if (outfile.is_open())
    {
        outfile << chord << "\n";
        for(int a = 0;a<chord;a++)
        {
            outfile << e[a][0] << " " << e[a][1] << "\n";
        }
        outfile.close();
    }
}