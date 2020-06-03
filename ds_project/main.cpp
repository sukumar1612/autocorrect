#include <iostream>
#include <stdio.h>
#include<string.h>
#include<windows.h>
#include <bits/stdc++.h>

using namespace std;

#define nullptr 0

class trie
{
public:
    bool endx;
    trie *chr[256];
    trie()
    {
        for(int i=0;i<256;i++)
        {
            chr[i]=nullptr;
        }
        endx=false;
    }
    void insert_ele(char ch[],int n);
    int search_ele(char ch[],int n);
    char* get_ele(char ch[],int n);
    int remove_ele(char ch[], int n);
};

void trie::insert_ele(char ch[],int n)
{
    trie *t=this;
    for (int i=0;i<n;i++)
    {
        if(t->chr[ch[i]] == nullptr)
        {
            t->chr[ch[i]]=new trie();
        }
        t=t->chr[ch[i]];
    }
    t->endx=true;
}

int trie::search_ele(char ch[],int n)
{
    if (this == nullptr)
	{
	    return 0;
	}
    trie *t=this;
    for (int i=0;i<n;i++)
	{
		t=t->chr[ch[i]];
		if ( t== nullptr)
		{
		    return 0;
		}
	}
    return int(t->endx);
}

bool is_last_node(trie *t)
{
    return t->endx;
}

char* trie::get_ele(char ch[], int n)
{
//    cout<<"In get_ele : "<<ch<<endl;
    trie *t = this;
    int i, cnt=1;
    static char ret[50];
    for(i=0;i<n;i++)
    {
        if(t->chr[ch[i]]!=nullptr)
        {
            //cout<<"In trie : "<<ch[i]<<endl;
            t = t->chr[ch[i]];
            cnt++;
        }
        else
        {
            //cout<<"Not in trie : "<<ch[i]<<endl;
            if(is_last_node(t))                    //A part of the given word is in the dictionary
            {
                //cout<<"In last node"<<endl;
                int k;
                for(k=0;k<cnt-1;k++)
                {
                    ret[k] = ch[k];
                }
                ret[k] = '\0';
                //cout<<"Ret : "<<ret<<endl;
                return ret;
            }
            else
            {
                //cout<<"Not in last node "<<endl;
                int k;
                for(k=0;k<cnt-1;k++)
                {
                    ret[k] = ch[k];
                }
                while(!is_last_node(t))
                {
                    char j = 'a';
                    while(j<='z')
                    {
                        if(t->chr[j]!=nullptr)
                        {
                            ret[k] = j;
                            k++;
                            t = t->chr[j];
                        }
                        else
                        {
                            j = (int)j +1;
                        }
                    }
                }
                ret[k] = '\0';
                //cout<<"ret : "<<ret<<endl;
                return ret;
            }
        }

    }
    if(cnt==n+1) // If the given string isn't a word but a part of an actual word
    {
        //cout<<"Sub-string : "<<ch<<endl;
        int k = n;
        strcpy(ret,ch);
        while(! is_last_node(t))
        {
            char j='a';
            while(j<='z')
            {
                if(t->chr[j]!=nullptr)
                {
                    ret[k] = j;
                    k++;
                    t = t->chr[j];
                    break;
                }
                else
                {
                    j = (int)j + 1;
                }
            }
        }
        ret[k] = '\0';
        //cout<<"Ret in prefix : "<<ret<<endl;
        return ret;
    }
}

int trie::remove_ele(char ch[], int n)
{
    int cnt=0;
    trie *t = this;
    for(int i=0;i<n;i++)
    {
        t = t->chr[ch[i]];
        if(t->endx)
        {
            cnt++;
        }
    }
    for(int i=0;i<26;i++) // The given word is a part of another word so only endx is changed
    {
        if(t->chr['a'+i]!=nullptr)
        {
            t->endx = false;
            return 1;
        }
    }
    t = this;
    if(cnt>1) //a part of the given word is a word, suffix needs to be deleted
    {

        return 2;
    }
    else if(cnt==1) // No part of the word is a word
    {
        for(int j=0;j<n;j++)
        {
            int temp=0;
            for(int i=0;i<26;i++)
            {
                if(t->chr['a'+i]!=nullptr && 'a'+i!=ch[j+1])
                {
                    temp++;
                    break;
                }
            }
            if(temp==0)
            {
                delete t;
                break;
            }
            t = t->chr[ch[j]];
        }
        return 3;
    }
}

struct words
{
    char x[50];
};

int main()
{
    words w;
    trie t;
    char ch[50];
    cout<<"Loading..."<<endl;
    fstream q;
    string input_file;
    input_file = "english3.txt";
    q.open(input_file.c_str());
    unsigned int j, count=0;
    while(q>>ch)
    {
        //cout<<count;
        //count++;
        for(j=0;j<strlen(ch);j++)
        {
            ch[j] = tolower(ch[j]);
        }
        ch[0] -= 32;
        ch[strlen(ch)]='\0';
        t.insert_ele(ch,strlen(ch));
    }
    system("cls");
    int fl=0;
    fstream p;
    string filename;
    filename = "text.txt";
    p.open(filename.c_str());
    ofstream outfile;
    outfile.open("out.txt");
    while(p>>ch)
    {
        int l = strlen(ch);
        char temp1[50];
        strcpy(temp1,ch);
        if(!(ch[l-1]>='a' && ch[l-1]<='z' || ch[l-1]>='A' && ch[l-1]<='Z'))
        {
            cout<<"last : "<<ch<<endl;
            int i;                              //Error when a word is followed by punctuation
            for(i=0;i<l-1;i++)
            {
                temp1[i] = ch[i];
            }
            //cout<<"tmp : "<<temp1<<endl;
            //cout<<"size : "<<sizeof(temp1)<<endl;
        }
        strcpy(ch,temp1);
        for(j=0;j<l;j++)
        {
            ch[j] = tolower(ch[j]);
        }
        ch[l]='\0';
        ch[0] -= 32;
        cout<<"input : "<<ch<<endl;
        char temp[150] = "*", hold[5][50];
        if(!bool(t.search_ele(ch,l)))
        {
            cout<<"Not_in_dic : "<<ch<<endl;
            int k=0;
            while(k<5)
            {
                char *st = t.get_ele(ch,l);
                cout<<"Output : "<<st<<endl;
                strcat(temp,st);
                strcat(temp,",");
                strcpy(hold[k],st);
                t.remove_ele(st,strlen(st));
                k++;
                fl++;
            }
            for(int i=0;i<5;i++)
            {
                t.insert_ele(hold[i],strlen(hold[i]));
            }
            strcat(temp,"*");
            outfile<<temp<<" ";
        }
        else
        {
            ch[0] +=32;
            outfile<<ch<<" ";
        }
    }
    q.close();
    p.close();
    outfile.close();
    cout<<"\n\t\t\t\t*** File free of linguistic errors ***\n";
    return 0;
}
