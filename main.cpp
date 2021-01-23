#include<iostream>
#include <fstream>
#include <iomanip>
#include<cstdio>
#include<sstream>
#include<algorithm>
#include<string>
#include<cstring>
#define pow2(n) (1 << (n))
using namespace std;
struct avl {
   int d;
   int pay;
   char name[15];
   char desg[15];
   char email[20];
   struct avl *l;
   struct avl *r;
   int he;
}*r;
class avl_tree {
   public:
      int height(avl *);
      int difference(avl *);
      avl *minValue(avl *);
      avl *rr_rotat(avl *);
      avl *ll_rotat(avl *);
      avl *lr_rotat(avl*);
      avl *rl_rotat(avl *);
      avl * balance(avl *);
      avl * insert(avl*, int, int, char na[], char de[],char em[]);
      avl * del(avl* , int);
      void Search(avl* , int);
      void show(avl*, int);
      void inorder(avl *);
      void preorder(avl *);
      void postorder(avl*);
      avl_tree() {
         r = NULL;
      }
};
int avl_tree::height(avl *t) {
   int h = 0;
   if (t != NULL) {
      int l_height = height(t->l);
      int r_height = height(t->r);
      int max_height = max(l_height, r_height);
      h = max_height + 1;
   }
   return h;
}
int avl_tree::difference(avl *t) {
   int l_height = height(t->l);
   int r_height = height(t->r);
   int b_factor = l_height - r_height;
   return b_factor;
}
avl *avl_tree::minValue(avl *m)
{
    avl *current = m;
    while (current->l != NULL)
		current = current->l;

	return current;
}
avl *avl_tree::rr_rotat(avl *parent) {
   avl *t;
   t = parent->r;
   parent->r = t->l;
   t->l = parent;
   cout<<"Right-Right Rotation";
   return t;
}
avl *avl_tree::ll_rotat(avl *parent) {
   avl *t;
   t = parent->l;
   parent->l = t->r;
   t->r = parent;
   cout<<"Left-Left Rotation";
   return t;
}
avl *avl_tree::lr_rotat(avl *parent) {
   avl *t;
   t = parent->l;
   parent->l = rr_rotat(t);
   cout<<"Left-Right Rotation";
   return ll_rotat(parent);
}
avl *avl_tree::rl_rotat(avl *parent) {
   avl *t;
   t = parent->r;
   parent->r = ll_rotat(t);
   cout<<"Right-Left Rotation";
   return rr_rotat(parent);
}
avl *avl_tree::balance(avl *t) {
   int bal_factor = difference(t);
   if (bal_factor > 1) {
      if (difference(t->l) > 0)
         t = ll_rotat(t);
      else
         t = lr_rotat(t);
   } else if (bal_factor < -1) {
      if (difference(t->r) > 0)
         t = rl_rotat(t);
      else
         t = rr_rotat(t);
   }
   return t;
}
avl *avl_tree::insert(avl *r, int v,int p ,char na[],char de[],char em[]) {
   if (r == NULL) {
      ofstream write ("Record.txt", ios::app);
      r = new avl;
      r->d = v;
      r->pay=p;
      strcpy(r->name,na);
      strcpy(r->desg,de);
      strcpy(r->email,em);
      r->l = NULL;
      r->r = NULL;
      write << v << setw(10) << na << setw(10) << de << setw(10) << p << setw(10) << em << endl;
      return r;
   } else if (v < r->d) {
      r->l = insert(r->l, v, p, na, de, em);
      r = balance(r);
   } else if (v >= r->d) {
      r->r = insert(r->r, v, p, na, de, em);
      r = balance(r);
   } return r;
}
void avl_tree::Search(avl *te,int n)
{
    avl *pt;
    int flag=0;
    if(te==NULL)
    {
        cout << "Tree is Empty: " << endl;
        return ;
    }
    if(te->d==n)
    {
        cout << te->d << ": Name: " << te->name << ": Designation: " << te->desg << ": Pay: " << te->pay << ": Email: " << te->email<< endl;
        return ;
    }
    else if(n<te->d)
    {
        pt=te->l;
    }
    else{
        pt=te->r;
    }
    while(pt!=NULL)
    {
        if(n==pt->d)
        {
            cout << pt->d << ": Name: " << pt->name << ": Designation: " << pt->desg << ": Pay: " << pt->pay << ": Email: " << pt->email<< endl;
            flag=1;
        }
        if(n<pt->d)
        {
            pt=pt->l;
        }
        else{
            pt=pt->r;
        }
    }
    if(flag!=1)
    {
        cout << "Their is no employ having id: " << n << endl;
    }
}
avl *avl_tree::del(avl *root,int va)
{
    if (root == NULL)
		return root;
    if (va < root->d)
		root->l = del(root->l, va);
    else if (va > root->d)
		root->r = del(root->r, va);
    else
	{
		if ((root->l == NULL) || (root->r == NULL))
		{
			avl *tem = root->l ?root->l :root->r;
			if (tem == NULL)
			{
				tem = root;
				root = NULL;
			}
			else
				*root = *tem;
			free(tem);
		}
		else
		{
			avl* tem = minValue(root->r);
			root->d = tem->d;
			root->r = del(root->r,tem->d);
		}
		cout << "Data Deleted: " << endl;
	}
	if (root == NULL)
		return root;
	root->he = 1 + max(height(root->l),height(root->r));
	root=balance(root);
	return root;
}
void avl_tree::show(avl *p, int l) {
   int i;
   if (p != NULL) {
      show(p->r, l+ 1);
      cout<<" ";
      if (p == r)
         cout << "Root -> ";
      for (i = 0; i < l&& p != r; i++)
         cout << " ";
         cout << p->d;
         show(p->l, l + 1);
   }
}
void avl_tree::inorder(avl *t) {
   if (t == NULL)
      return;
      inorder(t->l);
      cout << t->d << ": Name: " << t->name << ": Designation: " << t->desg << ": Pay: " << t->pay << ": Email: " << t->email<< endl;
      inorder(t->r);
}
void avl_tree::preorder(avl *t) {
   if (t == NULL)
      return;
      cout << t->d << ": Name: " << t->name << ": Designation: " << t->desg << ": Pay: " << t->pay << ": Email: " << t->email<< endl;
      preorder(t->l);
      preorder(t->r);
}
void avl_tree::postorder(avl *t) {
   if (t == NULL)
      return;
      postorder(t ->l);
      postorder(t ->r);
      cout << t->d << ": Name: " << t->name << ": Designation: " << t->desg << ": Pay: " << t->pay << ": Email: " << t->email<< endl;
}

int main() {
   int c, i,p,j;
   char n[15],d[15],e[20];
   avl_tree avl;
   while (1) {
      cout << "1.Insert Data" << endl;
      cout << "2.Search using ID number: " << endl;
      cout << "3.Delete using ID number: " << endl;
      cout << "4.show Balanced AVL Tree" << endl;
      cout << "5.InOrder traversal" << endl;
      cout << "6.PreOrder traversal" << endl;
      cout << "7.PostOrder traversal" << endl;
      cout << "8.Exit" << endl;
      cout << "Enter your Choice: ";
      cin >> c;
      switch (c) {
         case 1:
            cout << "Enter Id of Employee: ";
            cin >> i;
            cout << "Enter name of Employee: ";
            cin >> n;
            cout << "Enter Employee designation: ";
            cin >> d;
            cout << "Enter pay: ";
            cin >> p;
            cout << "Enter Employee Email: ";
            cin >> e;
            r = avl.insert(r, i, p , n , d ,e);
         break;
         case 2:
            cout << "Enter id number of employee to search for data: ";
            cin >> i;
            for(j=0;j<120;j++)
            {
                cout << "-";
            }
            avl.Search(r,i);
            for(j=0;j<120;j++)
            {
                cout << "-";
            }
            break;
         case 3:
            cout << "Enter id number to delete data of employee: ";
            cin >> i;
            for(j=0;j<120;j++)
            {
                cout << "-";
            }
            r=avl.del(r,i);
            for(j=0;j<120;j++)
            {
                cout << "-";
            }
            break;
         case 4:
            for(j=0;j<60;j++)
            {
                cout << "-";
            }
            cout << endl;
            if (r == NULL) {
               cout << "Tree is Empty" << endl;
               continue;
            }
            cout << "Balanced AVL Tree:" << endl;
            avl.show(r, 1);
            cout<<endl;
            for(j=0;j<60;j++)
            {
                cout << "-";
            }
            cout << endl;
         break;
         case 5:
            for(j=0;j<120;j++)
            {
                cout << "-";
            }
            cout << endl;
            cout << "Inorder Traversal:" << endl;
            avl.inorder(r);
            cout << endl;
            for(j=0;j<120;j++)
            {
                cout << "-";
            }
            cout << endl;
         break;
         case 6:
            for(j=0;j<120;j++)
            {
                cout << "-";
            }
            cout << endl;
            cout << "Preorder Traversal:" << endl;
            avl.preorder(r);
            cout << endl;
            for(j=0;j<120;j++)
            {
                cout << "-";
            }
            cout << endl;
         break;
         case 7:
            for(j=0;j<120;j++)
            {
                cout << "-";
            }
            cout << endl;
            cout << "Postorder Traversal:" << endl;
            avl.postorder(r);
            cout << endl;
            for(j=0;j<120;j++)
            {
                cout << "-";
            }
            cout << endl;
         break;
         case 8:
            exit(1);
         break;
         default:
            cout << "Wrong Choice" << endl;
      }
   }
   return 0;
}

