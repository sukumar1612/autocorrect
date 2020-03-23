#include <iostream>
#include <stdio.h>
#include<string.h>
#include<windows.h>

using namespace std;

#define nullptr 0
class trie{
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
};
void trie::insert_ele(char ch[],int n)
{
    trie *t=this;

    for (int i=0;i<n;i++)
    {
        if(t->chr[ch[i]]==nullptr)
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
		return 0;

    trie *t=this;

    for (int i=0;i<n;i++)
	{
		t=t->chr[ch[i]];
		if ( t== nullptr)
			return 0;
	}
    return int(t->endx);
}


struct words {
                char x[50];
};

int main()
{
    char x[50];
    words w;
    FILE *q;

    trie t;
    char ch[50];
    cout<<"loading"<<endl;
    q=fopen("words2.txt","r+");

    while(!feof(q))
    {
        fread(&w,sizeof(words),1,q);
        strcpy(ch,w.x);
        ch[strlen(ch)-1]='\0';
        t.insert_ele(ch,strlen(ch));
    }
    system("cls");
    cout<<"enter element to be searched :"<<endl;
    fflush(stdin);
    gets(ch);
    cout<<bool(t.search_ele(ch,strlen(ch)))<<endl;
    return 0;
}
