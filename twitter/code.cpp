#include <bits/stdc++.h>
#define pb push_back
using namespace std;
map < string, int > mp1,mp2;
vector < vector < string > > vtr;
int main()
{
    freopen("inp.csv","r",stdin);
    freopen("out.txt","w",stdout);
    int t=91299;
    // t=3*t;
    int i=0,j=0;
    string s,s2,s3;
    vector < vector < string > > v;

    v.resize(91305); 
    vtr.resize(91305); 
    while(t--)
    {
        getline(cin,s);
        string str="";
        for(int i=0;i<s.length();i++)
        {
            if(i!=s.length()-1)
            {
                if(s[i]==',')
                {
                    v[j].pb(str);
                    str="";
                }
                else
                {
                    str+=s[i];
                }
            }
            else
            {
                str+=s[i];
                v[j].pb(str);
                str="";
            }
        }
        // cout<<v[j][0]<<" "<<v[j][1]<<" "<<v[j][2]<<endl;
        j++;
    }
    for(int i=1;i<91299;i++)
    {
        if(v[i][2][0]=='s')
        {
            v[i][2]="sarcastic";
        }
        else
        {
            v[i][2]="non-sarcastic";
        }
        int nn=v[i][1].size();
        string str="";
        for(int j=0;j<nn;j++)
        {
            if(j!=nn-1)
            {
                if(v[i][1][j]==' ')
                {
                    if(v[i][2]=="sarcastic")
                    {
                        mp1[str]++;
                    }
                    else if(v[i][2]=="non-sarcastic")
                    {
                        mp2[str]++;
                    }    
                    str="";
                }
                else
                {
                    str+=v[i][1][j];
                }       
            }
            else
            {
                str+=v[i][1][j];
                if(v[i][2]=="sarcastic\n")
                {
                    mp1[str]++;
                }
                else if(v[i][2]=="non-sarcastic\n")
                {
                    mp2[str]++;
                }
            }
        }
    }
    // cout<<mp1.size()<<" "<<mp2.size()<<endl;
    // for(std::map < string, int > :: iterator it=mp1.begin();it!=mp1.end();++it)
    // {
        // cout<<it->first<<" "<<it->second<<endl;
    // }
    freopen("inp2.csv","r",stdin);
    string ans[91305];
    
    for(int i=0;i<21000;i++)
    {
        double an=1.0;
        for(int j=0;j<vtr[i].size();j++)
        {
            if(mp1[vtr[i][j]]==0&&mp2[vtr[i][j]]==0)
            {
               an=an*(1.0/2.0); 
            }
            else
            {
                an=an*((double)(mp1[vtr[i][j]]+1)/(double)(mp1[vtr[i][j]]+mp2[vtr[i][j]])); 
            }
        }
        if(an<0.5)
        {
            ans[i]="sarcastic";
        }
        else
        {
            ans[i]="non-sarcastic";
        }
    }
    int coi=0;
    for(int i=0;i<21000;i++)
    {
        if(ans[i]==v[i+70299][2])
        {
            coi++;
        }
    }
    cout<<(double)coi/(double)21000.0<<endl;
    // long long int n,t,k;
    return 0;
}