// C++ program  for Tournament Tree (Winner Tree).
//To find the second best player using minimum number of comparisons 
// between two player , one with smaller value is winner.
#include <iostream.h> 
using namespace std; 

// Tournament Tree node 
struct Node 
{ 
	int val; 
	Node *left, *right; 
}; 


Node *createNode(int val) 
{ 
	Node *t = new Node; 
	t->left = t->right = NULL; 
	t->val = val; 
	return t; 
} 

// For  traversing  tree across height to 
// find second smallest element in tournament tree. 

void traverseHeight(Node *root, int arr[], int &res) 
{ 
	//for root
	if (root == NULL || (root->left == NULL && 
						root->right == NULL)) 
		return; 

	// left
	if (res > arr[root->left->val] && 
	root->left->val != root->val) 
	{ 
		res = arr[root->left->val]; 
		traverseHeight(root->right, arr, res); 
	} 

	// right
	else if (res > arr[root->right->val] && 
			root->right->val != root->val) 
	{ 
		res = arr[root->right->val]; 
		traverseHeight(root->left, arr, res); 
	} 
} 


void findSecondBest(int arr[], int n) 
{ 
	
	list<Node *> li; 

	Node *root = NULL; 
	for (int i = 0; i < n; i += 2) 
	{ 
		Node *t1 = createNode(i); 
		Node *t2 = NULL; 
		if (i + 1 < n) 
		{ 
			
			t2 = createNode(i + 1); 

			// Making smaller one root.
			root = (arr[i] < arr[i + 1])? createNode(i) : 
									createNode(i + 1); 

			// children of root.
			root->left = t1; 
			root->right = t2; 

			// Add root 
			li.push_back(root); 
		} 
		else
			li.push_back(t1); 
	} 

	int lsize = li.size(); 

	// Construct the complete tournament tree 
	
	while (lsize != 1) 
	{ 
		
		int last = (lsize & 1)? (lsize - 2) : (lsize - 1); 

		
		for (int i = 0; i < last; i += 2) 
		{ 
			 
			Node *f1 = li.front(); 
			li.pop_front(); 

			Node *f2 = li.front(); 
			li.pop_front(); 
			root = (arr[f1->val] < arr[f2->val])? 
				createNode(f1->val) : createNode(f2->val); 

			
			root->left = f1; 
			root->right = f2; 

		
			li.push_back(root); 
		} 
		if (lsize & 1) 
		{ 
			li.push_back(li.front()); 
			li.pop_front(); 
		} 
		lsize = li.size(); 
	} 

	// Traverse tree from root to find second best 

	int res = INT_MAX; 
	traverseHeight(root, arr, res); 
	cout << "Best Player: " << arr[root->val] 
		<< ", Second Best Player: " << res << endl; 
} 

// main
int main() 
{ 
	int arr[] = {55, 7, 100, 99, 11, 15, 17}; 
	int n = sizeof(arr)/sizeof(arr[0]); 
	findSecondBest(arr, n); 
	return 0; 
} 
