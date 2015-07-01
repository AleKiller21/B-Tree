#ifndef BTREE_H
#define BTREE_H
#endif // BTREE_H
#include <iostream>
#include <QDebug>
#include <QList>
#include "treescene.h"
using namespace std;

class BNode
{

public:
    int *keys;
    int t;
    BNode **C;
    int n;
    int cant_childs;
    bool go_split;
    bool leaf;
    static int number_keys;
    static QList<int> nodeslist;
    static bool isleaf;
    static QList<BNode*> childs;
    BNode(int mindegree, bool _leaf);
    void cross(TreeScene* scene);
    void save(TreeScene* scene);
    BNode *search(int k);
    int findKey(int k);
    void insertNonFull(int k);

    void split(int i, BNode *y);

    void remove(int k);

    void removeFromLeaf(int index);

    void removeFromNonLeaf(int index);

    int calcularPadding();

    int calcularPaddingIzquierda();

    int calcularPaddingDerecha();

    int getPred(int index);

    int getSucc(int index);

    void fill(int index);

    void borrowFromPrev(int index);

    void borrowFromNext(int index);

    void merge(int index);

    friend class BTree;
};

QList<int> BNode::nodeslist = QList<int>();
int BNode::number_keys = 0;
bool BNode::isleaf = true;
QList<BNode*> BNode::childs;
class BTree
{

public:
    BNode *root;
    int t;
    bool inserted = false;

    BTree(int mindegree)
    {
        root = NULL;
        t = mindegree;
    }

    void cross(TreeScene* scene)
    {
        if (root != NULL)
            root->cross(scene);
    }

    void save(TreeScene* scene){
        if(root!=NULL)
            root->save(scene);
    }

    BNode* search(int k)
    {
        return (root == NULL)? NULL : root->search(k);
    }

    void insert(int k);

    void remove(int k);

    int height();

};

BNode::BNode(int degree, bool isleaf){
    t = degree;
    leaf = isleaf;
    go_split = false;
    keys = new int[2*t-1];
    C = new BNode *[2*t];

    n = 0;
}

int BNode::findKey(int k)
{
    int index=0;
    while (index<n && keys[index] < k)
        ++index;
    return index;
}

void BNode::remove(int k)
{
    int index = findKey(k);

    if (index < n && keys[index] == k)
    {

        if (leaf)
            removeFromLeaf(index);
        else
            removeFromNonLeaf(index);
    }
    else
    {

        if (leaf)
        {
            qDebug()<< "The key "<<k<<" is does not exist in the tree\n";
            return;
        }

        bool flag = ( (index==n)? true : false );

        if (C[index]->n < t)
            fill(index);

        if (flag && index > n)
            C[index-1]->remove(k);
        else
            C[index]->remove(k);
    }
    return;
}

void BNode::removeFromLeaf (int index)
{

    for (int i=index+1; i<n; ++i)
        keys[i-1] = keys[i];

    n--;

    return;
}

void BNode::removeFromNonLeaf(int index)
{

    int k = keys[index];


    if (C[index]->n >= t)
    {
        int pred = getPred(index);
        keys[index] = pred;
        C[index]->remove(pred);
    }

    else if  (C[index+1]->n >= t)
    {
        int succ = getSucc(index);
        keys[index] = succ;
        C[index+1]->remove(succ);
    }


    else
    {
        merge(index);
        C[index]->remove(k);
    }
    return;
}

int BNode::calcularPadding()
{
    int padding = 0;



        if(leaf)
        {
            for(int i = 0; i < n; i++)
            {
                padding+= 35;
            }

            return padding;
        }

        for(int i = 0; i < n+1; i++)
        {
            padding+= C[i]->calcularPadding();
        }

        padding+= 35;

        return padding;
}

int BNode::calcularPaddingIzquierda()
{
    int padding = 0;

        //    for(int i = 0; i < C[n]->n; i++)
        //    {
        //        padding+= 35;
        //    }

        if(leaf)
        {
            for(int i = 0; i < n; i++)
            {
                padding+= 35;
            }

            return padding;
        }

        for(int i = 0; i < n+1; i++)
        {
            padding+= C[i]->calcularPaddingIzquierda();
        }

        for(int i = 0; i < n; i++)
        {
            padding+= 35;
        }

        return padding;
}

int BNode::calcularPaddingDerecha()
{
    //    int padding = 0;

    //    for(int i = 0; i < C[0]->n; i++)
    //    {
    //        padding+= 35;
    //    }

    //    return padding;

        int padding = 0;

        if(leaf)
        {
            for(int i = 0; i < n; i++)
            {
                padding+= 35;
            }

            return padding;
        }

        for(int i = 0; i < n+1; i++)
        {
            padding+= C[i]->calcularPaddingDerecha();
        }

        for(int i = 0; i < n; i++)
        {
            padding+= 35;
        }

        return padding;
}

int BNode::getPred(int index)
{
    BNode *cur=C[index];
    while (!cur->leaf)
        cur = cur->C[cur->n];

    return cur->keys[cur->n-1];
}

int BNode::getSucc(int index)
{

    BNode *cur = C[index+1];
    while (!cur->leaf)
        cur = cur->C[0];

    return cur->keys[0];
}

void BNode::fill(int index)
{

    if (index!=0 && C[index-1]->n>=t)
        borrowFromPrev(index);

    else if (index!=n && C[index+1]->n>=t)
        borrowFromNext(index);

    else
    {
        if (index != n)
            merge(index);
        else
            merge(index-1);
    }
    return;
}

void BNode::borrowFromPrev(int index)
{

    BNode *child=C[index];
    BNode *brother=C[index-1];

    for (int i=child->n-1; i>=0; --i)
        child->keys[i+1] = child->keys[i];

    if (!child->leaf)
    {
        for(int i=child->n; i>=0; --i)
            child->C[i+1] = child->C[i];
    }

    child->keys[0] = keys[index-1];

    if (!leaf)
        child->C[0] = brother->C[brother->n];

    keys[index-1] = brother->keys[brother->n-1];

    child->n += 1;
    brother->n -= 1;

    return;
}

void BNode::borrowFromNext(int index)
{

    BNode *child=C[index];
    BNode *brother=C[index+1];

    child->keys[(child->n)] = keys[index];

    if (!(child->leaf))
        child->C[(child->n)+1] = brother->C[0];

    keys[index] = brother->keys[0];

    for (int i=1; i<brother->n; ++i)
        brother->keys[i-1] = brother->keys[i];

    if (!brother->leaf)
    {
        for(int i=1; i<=brother->n; ++i)
            brother->C[i-1] = brother->C[i];
    }

    child->n += 1;
    brother->n -= 1;

    return;
}

void BNode::merge(int index)
{
    BNode *child = C[index];

    BNode *brother = C[index+1];
    child->keys[t-1] = keys[index];

    for (int i=0; i<brother->n; ++i)
        child->keys[i+t] = brother->keys[i];

    if (!child->leaf)
    {
        for(int i=0; i<=brother->n; ++i)
            child->C[i+t] = brother->C[i];
    }

    for (int i=index+1; i<n; ++i)
        keys[i-1] = keys[i];

    for (int i=index+2; i<=n; ++i)
        C[i-1] = C[i];

    child->n += brother->n+1;
    n--;

    delete(brother);
    return;
}

void BTree::insert(int k)
{


    if (root == NULL)
    {
        root = new BNode(t, true);
        BNode::childs.append(root);
        root->keys[0] = k;
        root->n = 1;
    }else{
        if (root->n == 2*t-1)
        {

                BNode *s = new BNode(t, false);
                BNode::childs.append(s);
                s->C[0] = root;

                s->split(0, root);

                int i = 0;
                if (s->keys[0] < k)
                    i++;
                s->C[i]->insertNonFull(k);

                root = s;

        }else{
            root->insertNonFull(k);
        }
        if(root->n == 2*t - 1)
                {
                    qDebug() << "Split" << endl;
                    root->go_split = true;
                }

                if(root->go_split)
                {
                    root->go_split = false;
                    BNode *s = new BNode(t, false);
                    // BNode::childs.append(s);
                    s->C[0] = root;

                    s->split(0, root);

                    int i = 0;
                    if (s->keys[0] < k)
                        i++;
                    //s->C[i]->insertNonFull(k);

                    root = s;
                }
        }

}

void BNode::insertNonFull(int k)
{
    int i = n-1;
    int x = n-1;
   if (leaf == true)
    {
        while (i >= 0 && keys[i] > k)
        {
            keys[i+1] = keys[i];
            i--;
        }

        keys[i+1] = k;
        n = n+1;

        if(n == 2*t-1){
            qDebug()<<"Split Me!";
            go_split = true;
        }

    }
    else
    {
        while (i >= 0 && keys[i] > k)
            i--;

        if (C[i+1]->n == 2*t-1)
        {

            split(i+1, C[i+1]);

            if (keys[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }

    if(this->leaf != true){
        if(C[i+1]->go_split){

            C[i+1]->go_split = false;
            split(i+1, C[i+1]);
            if (keys[i+1] < k)
                i++;

            if(n == 2*t-1){
                go_split = true;
            }
        }
    }
}

void BNode::split(int i, BNode *y)
{

    BNode *z = new BNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];

    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }

    y->n = t - 1;

    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];

    C[i+1] = z;

    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];

    keys[i] = y->keys[t-1];

    n = n + 1;
}

void BNode::cross(TreeScene* scene)
{

    int i;
    //Testing ting
    int posiciones[2];
    int pos_arr = 0;
    QList<QGraphicsLineItem*> lines;
    QList<int> nodes_value;
    for (i = 0; i <n; i++)
        {

            if (leaf == false)
            {
                scene->y+= 105;

                C[i]->cross(scene);

                if(i == 0 || i == (n - 1))
                {
                    posiciones[pos_arr] = scene->x;
                    pos_arr++;
                }
            }

            scene->setMode(TreeScene::InsertItem);
            nodes_value.append(scene->x);
            if(leaf == false)
            {
                if(n > 1 && i != 0)
                {
                    if(C[i]->leaf)
                    {
                        lines.append(scene->addLine(scene->x - ((C[i]->n * 35) / 2), scene->y + 35, scene->x - ((C[i]->n * 35) / 2), scene->y + 105));
                    }

                    else
                    {
//                        int padding = C[i]->C[1]->calcularPadding();
                        //lines.append(scene->addLine(scene->x - ((padding / 2) + 15), scene->y + 35, scene->x - ((padding / 2) + 15), scene->y + 105));
//                        lines.append(scene->addLine(scene->x - padding+17, scene->y + 35, scene->x - padding+17, scene->y + 105));
                        lines.append(scene->addLine(scene->x - ((nodes_value.at(i) - nodes_value.at(i-1))/2)+17, scene->y+35,scene->x - ((nodes_value.at(i) - nodes_value.at(i-1))/2)+17,scene->y+105));
                    }
                }

                else
                {
                    if(C[i]->leaf == false)
                    {
                        int padding = C[i]->C[C[i]->n]->calcularPaddingIzquierda();
                        lines.append(scene->addLine(scene->x + 5, scene->y + 35, scene->x - padding, scene->y + 105));
                    }

                    else
                    {
                        lines.append(scene->addLine(scene->x + 5, scene->y + 35, scene->x - ((C[i]->n * 35) / 2), scene->y + 105));
                    }
                }

            }

            scene->UpdateScene(QString::number(keys[i]), scene->x, scene->y);
            scene->x+= 35;
        }

        if (leaf == false)
        {
            posiciones[1]+= 35;
            //lines.append(scene->addLine(scene->x - 5, scene->y + 35, scene->x + ((C[i]->n * 35) / 2), scene->y + 105));
            if(C[i]->leaf == false)
            {
                //int padding = C[i]->calcularPaddingDerecha();
                int padding = C[i]->C[0]->calcularPaddingDerecha();
                lines.append(scene->addLine(scene->x - 5, scene->y + 35, scene->x + padding, scene->y + 105));

            }

            else
            {
                lines.append(scene->addLine(scene->x - 5, scene->y + 35, scene->x + ((C[i]->n * 35) / 2), scene->y + 105));
            }

            if(n > 1)
            {
                scene->addRect(posiciones[0], scene->y, (posiciones[1] - posiciones[0]), 35,QPen(), QBrush(Qt::darkGreen))->setOpacity(0.4);
            }

            scene->y+= 105;
            C[i]->cross(scene);
        }

        scene->y-= 105;

}

void BNode::save(TreeScene *scene)
{

    int i;
    for(i = 0; i<n; i++){

        if(leaf == false){
            C[i]->save(scene);
        }

        BNode::nodeslist.append(keys[i]);
    }

    if(leaf == false){
        C[i]->save(scene);
    }

}

BNode *BNode::search(int k)
{
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    if (keys[i] == k)
        return this;

    if (leaf == true)
        return NULL;

    return C[i]->search(k);
}

void BTree::remove(int k)
{
    if (!root)
    {
        qDebug()<< "The tree is empty\n";
        return;
    }

    root->remove(k);

    if (root->n==0)
    {
        BNode *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];

        delete tmp;
    }
    return;
}

int BTree::height()
{


}
