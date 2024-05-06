#include <bits/stdc++.h>

using namespace std;

struct node {
    string keyword;
    string definition;
    struct node * left;
    struct node * right;
    int balance_factor; //height of the node
};

struct node * root = NULL;

void initial(string word, string def) {
    struct node * t = root;
    struct node * r = NULL;
    struct node * p;
    if (root == NULL) {
        p = new node();
        p -> keyword = word;
        p -> definition = def;
        p -> balance_factor = 0;
        p -> left = NULL;
        p -> right = NULL;
        root = p;
        return;
    }
    while (t != NULL) {
        r = t;
        if (word < t -> keyword) {
            t = t -> left;
        } else if (word > t -> keyword) {
            t = t -> right;
        } else {
            return;
        }
    }
    p = new node();
    p -> keyword = word;
    p -> definition = def;
    p -> balance_factor = 0;
    p -> left = NULL;
    p -> right = NULL;
    if (word < r -> keyword) {
        r -> left = p;
    } else {
        r -> right = p;
    }
}

int height(struct node * root) {
    if (!root) {
        return 0;
    }
    int left = height(root -> left);
    int right = height(root -> right);
    return 1 + max(left, right);
}

struct node * RLRotation(struct node * p) {
    int left_balance_factor;
    int right_balance_factor;
    struct node * pR = p -> right;
    struct node * pRL = pR -> left;
    pRL -> balance_factor = 0;
    p -> right = pRL -> left;
    pR -> left = pRL -> right;
    pRL -> right = pR;
    pRL -> left = p;
    left_balance_factor = height(p -> left) + 1;
    right_balance_factor = height(p -> right) + 1;
    p -> balance_factor = left_balance_factor - right_balance_factor;
    left_balance_factor = height(pR -> left) + 1;
    right_balance_factor = height(pR -> right) + 1;
    pR -> balance_factor = left_balance_factor - right_balance_factor;
    if (p == root) {
        root = pRL;
    }
    return pRL;
}

struct node * LRRotation(struct node * p) {
    int left_balance_factor;
    int right_balance_factor;
    struct node * pL = p -> left;
    struct node * pLR = pL -> right;
    pLR -> balance_factor = 0;
    p -> left = pLR -> right;
    pL -> right = pLR -> left;
    pLR -> left = pL;
    pLR -> right = p;

    left_balance_factor = height(p -> left) + 1;
    right_balance_factor = height(p -> right) + 1;
    p -> balance_factor = left_balance_factor - right_balance_factor;

    left_balance_factor = height(pL -> left) + 1;
    right_balance_factor = height(pL -> right) + 1;
    pL -> balance_factor = left_balance_factor - right_balance_factor;
    if (p == root) {
        root = pLR;
    }
    return pLR;
}

struct node * LLRotation(struct node * p) {
    int left_balance_factor;
    int right_balance_factor;
    struct node * p_left_child = p -> left;
    p_left_child -> balance_factor = 0;
    p -> left = p_left_child -> right;
    p_left_child -> right = p;
    left_balance_factor = height(p -> left) + 1;
    right_balance_factor = height(p -> right) + 1;
    p -> balance_factor = left_balance_factor - right_balance_factor;
    if (p == root) {
        root = p_left_child;
    }
    return p_left_child;
}

struct node * RRRotation(struct node * p) {
    int left_balance_factor;
    int right_balance_factor;
    struct node * p_right_child = p -> right;
    p_right_child -> balance_factor = 0;
    p -> right = p_right_child -> left;
    p_right_child -> left = p;
    left_balance_factor = height(p -> left) + 1;
    right_balance_factor = height(p -> right) + 1;
    p -> balance_factor = left_balance_factor - right_balance_factor;
    if (p == root) {
        root = p_right_child;
    }
    return p_right_child;
}

struct node * insert(struct node * p, string key, string def) {
    struct node * temp = new node;
    temp -> keyword = key;
    temp -> definition = def;
    temp -> left = NULL;
    temp -> right = NULL;
    temp -> balance_factor = 0;
    if (p == NULL) {
        return temp;
    }
    if (key > p -> keyword) {
        p -> right = insert(p -> right, key, def);
    } else if (key < p -> keyword) {
        p -> left = insert(p -> left, key, def);
    }
    int left_balance_factor = height(p -> left) + 1;
    int right_balance_factor = height(p -> right) + 1;
    p -> balance_factor = left_balance_factor - right_balance_factor;
    if (p -> balance_factor == 2 && p -> left -> balance_factor == 1) {
        return LLRotation(p);
    }
    if (p -> balance_factor == 2 && p -> left -> balance_factor == -1) {
        return LRRotation(p);
    }
    if (p -> balance_factor == -2 && p -> right -> balance_factor == -1) {
        return RRRotation(p);
    }
    if (p -> balance_factor == -2 && p -> right -> balance_factor == 1) {
        return RLRotation(p);
    }
    return p;
}

void search(string word) {
    if (!root) {
        cout << "The dictionary is empty." << endl;
    } else {
        struct node * p = root;
        while (p) {
            if (p -> keyword < word) {
                p = p -> right;
            } else if (p -> keyword > word) {
                p = p -> left;
            } else {
                cout << "Definition of " << word << " : " << p -> definition << endl;
                return;
            }
        }
        cout << "This keyword does not exist" << endl;
    }
}

void change(string word, string def) {
    if (!root) {
        cout << "The dictionary is empty." << endl;
    } else {
        struct node * p = root;
        while (p) {
            if (p -> keyword < word) {
                p = p -> right;
            } else if (p -> keyword > word) {
                p = p -> left;
            } else {
                p -> definition = def;
                cout << "Definition changed" << endl;
                return;
            }
        }
        cout << "This keyword does not exist" << endl;
    }
}

void InOrder_Display(struct node * root) {
    stack < struct node * > st;
    struct node * curr = root;
    while (curr || !st.empty()) {
        while (curr) {
            st.push(curr);
            curr = curr -> left;
        }
        curr = st.top();
        cout << curr -> keyword << ": " << curr -> definition << endl;
        st.pop();
        curr = curr -> right;
    }
}
int main() {
    while (true) {
        cout << "1. Add new Keyword" << endl;
        cout << "2. Search keyword" << endl;
        cout << "3. Change meaning of a keyword" << endl;
        cout << "4. Break" << endl;
        int ch;
        cout << "Enter your choice: " << endl;
        cin >> ch;
        if (ch == 1) {
            string word;
            string meaning;
            cout << "Enter keyword: " << endl;
            cin >> word;
            cout << "Enter definition: " << endl;
            cin >> meaning;
            if (root == NULL) {
                initial(word, meaning);
            } else {
                insert(root, word, meaning);
            }
            cout << "Tree: " << endl;
            InOrder_Display(root);
            cout << endl;
            cout << "Root: " << root -> keyword << endl;
        } else if (ch == 2) {
            string word;
            cout << "Enter keyword to be searched: " << endl;
            cin >> word;
            search(word);
        } else if (ch == 3) {
            string def;
            string word;
            cout << "Enter the word to be searhced: " << endl;
            cin >> word;
            cout << "Enter the new definition: " << endl;
            cin >> def;
            change(word, def);
        } else {
            break;
        }
    }
}
