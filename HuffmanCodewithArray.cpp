#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
typedef struct huff
{
    char c;
    int count;
    double prob;
}huff;
typedef struct fhuff
{
    char c;
    int count;
    double prob;
    string code;
}fhuff;
struct key
{
    inline bool operator() (const huff& struct1, const huff& struct2)
    {
        return (struct1.prob > struct2.prob);
    }
};
bool forSort(double i,double j){ return i>j; }
int main()
{
    string a;
    cout<<"Enter the String:-";
    cin>>a;
    vector<huff> my;
    for(int i=0;i<a.length();i++)
    {
        int found=0;
        for(int j=0;j<my.size();j++)
            if(my[j].c==a[i])
            {
                my[j].count=my[j].count+1;
                found=1;
            }
        if(found==0)
        {
            huff h={a[i],1,0};
            my.push_back(h);
        }
    }
    for(int i=0;i<my.size();i++)
        my[i].prob=my[i].count/(double)a.length();
    sort(my.begin(),my.end(),key());
    const int len=my.size();
    double d[len][len];
    for(int i=0;i<len;i++)
        for(int j=0;j<len;j++)
            d[i][j]=0;
    for(int i=0;i<len;i++)
        d[0][i]=my[i].prob;
    for(int i=1;i<len;i++)
    {
        for(int j=0;j<len-i;j++)
            d[i][j]=d[i-1][j];
        d[i][len-i-1]=d[i-1][len-1-i]+d[i-1][len-i];
        sort(d[i],d[i]+len,forSort);
    }
    string code[len][len];
    int done[len][len];
    for(int i=0;i<len;i++)
        for(int j=0;j<len;j++)
        {
            done[i][j]=0;
            if(d[i][j]==0)
                done[i][j]=1;
            code[i][j]="";
        }
    cout<<endl;
    for(int i=len-2;i>=0;i--)
    {
        int a[len];
        for(int j=0;j<len;j++) a[j]=0;
        for(int j=0;j<len;j++) if(d[i][j]==0) a[j]=1;
        for(int j=0;j<len;j++)
            if(done[i][j]==0)
                for(int k=0;k<len;k++)
                    if(d[i][j]==d[i+1][k]&&done[i+1][k]==0)
                    {
                        code[i][j]=code[i+1][k];
                        done[i+1][k]=1;
                        a[j]=1;
                        break;
                    }
        string newcode="";
        for(int j=0;j<len;j++)
            if(done[i+1][j]==0)
                newcode=code[i+1][j];
        if(i==len-1) newcode="";
        char read='0';
        for(int j=0;j<len;j++)
            if(a[j]==0)
            {
                code[i][j]=newcode+read;
                read='1';
            }
    }
    vector<fhuff> f;
    for(int j=0;j<len;j++)
    {
        f.push_back({my[j].c,my[j].count,my[j].prob,code[0][j]});
        cout<<my[j].c<<"\t"<<code[0][j]<<endl;
    }
    string encode="";
    cout<<endl<<"now encoded message"<<endl;
    for(int i=0;i<a.length();i++)
        for(int j=0;j<len;j++)
            if(a[i]==f[j].c)
                encode+=f[j].code;
    cout<<encode<<endl;
    cout<<"\n\nNow Decoded Message: ";
    for(int i=0;i<encode.length();i++)
    {
        for(int j=0;j<f.size();j++)
        {
            int l=f[j].code.length();
            string sub=encode.substr(i,l);
            if(sub==f[j].code)
            {
                cout<<f[j].c;
                i=i+l-1;
                break;
            }
        }
    }
}
