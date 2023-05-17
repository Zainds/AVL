#include<iostream>
using namespace std;

struct node // структура узла АВЛ дерева
{
    int data;
    node* left;
    node* right;
    int height;
};

struct BST
{
    node* root;

    BST()
    {
        root = nullptr;
    }

    node* add(int x, node* t)
    {   //функция добавления узла в дерево
        if(t == NULL)
        {   //если нет корня
            t = new node;
            t->data = x;
            t->height = 0;
            t->left = t->right = NULL;
        }
        else if(x < t->data)
        {   //если дерево не пустое и ключ меньше ключа
            //текущего узла
            t->left = add(x, t->left);
            if(height(t->left) - height(t->right) == 2)
            {   //если разница высот потомков 2 делаем балансировку
                if(x < t->left->data)
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if(x > t->data)
        {   //если дерево не пустое и ключ больше ключа
            //текущего узла
            t->right = add(x, t->right);
            if(height(t->right) - height(t->left) == 2)
            {   //если разница высот потомков 2 делаем балансировку
                if(x > t->right->data)
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }
        //определяем высоту добавленного узла
        t->height = max(height(t->left), height(t->right))+1;
        return t;
    }

    node* singleRightRotate(node* &t)
    {   //правый поворот
        node* u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = max(height(t->left), height(t->right))+1;
        u->height = max(height(u->left), t->height)+1;
        return u;
    }

    node* singleLeftRotate(node* &t)
    {   //левый поворот
        node* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right))+1;
        u->height = max(height(t->right), t->height)+1 ;
        return u;
    }

    node* doubleLeftRotate(node* &t)
    {   //двойной левый поворот
        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    node* doubleRightRotate(node* &t)
    {   //двойной правый поворот
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    int height(node* t)
    {   //возвращает высоту узла
        return (t == NULL ? -1 : t->height);
    }

    int getBalance(node* t)
    {   //возвращает разницу высот потомков
        if(t == NULL)
            return 0;
        else
            return height(t->left) - height(t->right);
    }

    void add(int x)
    {   //добавляет узел в дерево
        root = add(x, root);
    }

    void print_Tree(node* p, int level)     //Функция симметричного обхода
    {
        if (p)  //Пока не встретится пустое звено
        {
            print_Tree(p->right, level + 1);    //Рекурсивная функция для вывода левого поддерева
            for (int i = 0; i < level; i++) cout << "   "; // Выставляем пробелами визуальное дерево
            cout << p->data << endl;     //Отображаем корень дерева
            print_Tree(p->left, level + 1);     //Рекурсивная функци для вывода правого поддерева
        }
    }
    bool IsStrictlyBinary(node* root) { // Проверить является ли дерево строгим
        //если нет потомков считаем узел строгим
        if (root->left == NULL && root->right == NULL)
            return true;
        //если есть один потом считаем узел нестрогим
        else if ((root->left == NULL && root->right != NULL) ||
            (root->right == NULL && root->left != NULL))
            return false;
        //если и левый и правый узлы не имеют потомков считаем дерево строгим
        else
            return IsStrictlyBinary(root->left) && IsStrictlyBinary(root->right);
    }
};

int main()
{
    setlocale(LC_ALL, "");
    BST t;
    int elements;
    /*t.add(6);
    t.add(9);
    t.add(3);
    t.add(12);
    t.add(15);
    t.add(8);*/
    cout << "Введите кол-во элементов дерева:  ";
    cin >> elements; cout << "\n";
    for (int i = 0; i < elements; i++) { //Заполнение дерева
        int x;
        cout << "Введите " << i + 1 << " элемент дерева:  ";
        cin >> x;
        t.add(x);
    }
    t.print_Tree(t.root, 2);
    if(t.IsStrictlyBinary(t.root))cout << "Дерево является строгим";
    else cout << "Дерево не является строгим";
    
}