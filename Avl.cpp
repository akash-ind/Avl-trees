#include<iostream>
using namespace std;
class Node
{
public:
    int data;
    Node *left;
    Node *right;
    int height;
    Node(int data)
    {
        this->data=data;
        left=nullptr;
        right=nullptr;
        height=1;
    }
};
int height_node(Node *node)
{
    if(!node)
        return 0;
    if(node->left&&node->right)
        node->height=max(node->left->height,node->right->height)+1;
    else if(node->left)
        node->height=node->left->height+1;
    else if(node->right)
        node->height=node->right->height+1;
    else
        node->height=1;
    return node->height;
}
Node* rotate_left(Node *node)
{
    Node *temp=node->right;
    node->right=temp->left;
    temp->left=node;
    temp->height=height_node(temp);
    node->height=height_node(node);
    return temp;
}
Node *rotate_right(Node *node)
{
    Node *temp=node->left;
    node->left=temp->right;
    temp->right=node;
    temp->height=height_node(temp);
    node->height=height_node(node);
    return temp;
}

/*You are required to complete this method */
Node* insertToAVL( Node* node, int data)
{
    if(!node)
    {
        Node *temp=new Node(data);
        return temp;
    }
    if(data<node->data)
    {
        node->left=insertToAVL(node->left,data);
    }
    else if(data>node->data)
    {
        node->right=insertToAVL(node->right,data);
    }
    else
    {
        return node;
    }
    node->height=height_node(node);
    int lh,rh;
    if(node->left)
        lh=node->left->height;
    else
        lh=0;
    if(node->right)
        rh=node->right->height;
    else
        rh=0;
    int bal=abs(lh-rh);
    if(bal>1)
    {
        if(data<node->data)
        {
            if(data<node->left->data)
            {
                node=rotate_right(node);
            }
            else if(data>node->left->data)
            {
                node->left=rotate_left(node->left);
                node=rotate_right(node);
            }
        }
        else if(data>node->data)
        {
            if(data>node->right->data)
            {
                node=rotate_left(node);
            }
            else if(data<node->right->data)
            {
                node->right=rotate_right(node->right);
                node=rotate_left(node);
            }
        }

        return node;
    }
    return node;
}
void traverse(Node *root)
{
    if(!root)
        return;
    cout<<root->data<<" ";
    traverse(root->left);
    traverse(root->right);
}
void balance(Node *root)
{
    if(!root)
        return;
    balance(root->left);
    cout<<abs(height_node(root->left)-height_node(root->right))<<" ";
    balance(root->right);
}
int main()
{
    Node *root=nullptr;
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int a;
        cin>>a;
        root=insertToAVL(root,a);
    }
    traverse(root);
    cout<<endl;
    balance(root);
}
