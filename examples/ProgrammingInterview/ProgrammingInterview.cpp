// ProgrammingInterview.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "ListNode.h"
#include <queue>
#include <sstream>
#include <stack>
#include <memory>
#include <bitset>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <algorithm>

struct ContactList {
    bool operator==(const ContactList& that) const
    {
        return std::unordered_set<std::string>(names.begin(), names.end()) ==
            std::unordered_set<std::string>(that.names.begin(), that.names.end());
    }

    std::vector<std::string> names;
};

struct HashContactList {
    size_t operator()(const ContactList& contacts) const {
        size_t hash_code = 0;
        for (const std::string& name : std::unordered_set<std::string>(contacts.names.begin(), contacts.names.end()))
        {
            hash_code ^= std::hash<std::string>()(name);
        }
        return hash_code;
    }
};

std::vector<ContactList> MergeContactLists(const std::vector<ContactList>& contacts)
{
    std::unordered_set<ContactList, HashContactList> unique_contacts(
        contacts.begin(), contacts.end());
    return { unique_contacts.begin(), unique_contacts.end() };
};

void create_list_with_unique_contacts()
{
    ContactList cl1;
    cl1.names = { "abc", "def", "abc" };

    ContactList cl2;
    cl2.names = { "abc", "def", "abc" };

    std::vector<ContactList> v{ cl1, cl2 };
    
    std::vector<ContactList> v_merged = MergeContactLists(v);

    std::cout << "v_merged: " << std::endl;
}

void count_ones()
{
    // count number of "1"s in integer
    int count = 0;
    int number = 99729;
    for (int i = 0; i < 32; i++)
    {
        count += (number >> i) & 0x00000001;
    }
    std::cout << "count: " << count << "\n";

    count = 0;
    while (number > 0)
    {
        int comp = ~number + 1;
        int lowest_one = comp & number;
        count += bool(lowest_one);
        number = number ^ lowest_one;
    }
    std::cout << "count: " << count << "\n";
}

//6.1
void rearrange_2(int (& arr)[8], int index)
{
    int size = sizeof(arr) / sizeof(int);
    std::cout << "size: " << size << "\n";

    int pivot = arr[index];
    std::cout << "pivot: " << pivot << "\n";
    int idx_smaller = 0, idx_same = 0, idx_greater = 0;

    std::vector<int> smaller(size);
    std::vector<int> same(size);
    std::vector<int> greater(size);

    for (int i = 0; i < size; ++i)
    {
        if (arr[i] < pivot) smaller[idx_smaller++] = arr[i];
        if (arr[i] == pivot) same[idx_same++] = arr[i];
        if (arr[i] > pivot) greater[idx_greater++] = arr[i];
    }

    std::copy(smaller.cbegin(), smaller.cbegin() + idx_smaller, arr);
    std::copy(same.cbegin(), same.cbegin() + idx_same, arr+idx_smaller);
    std::copy(greater.cbegin(), greater.cbegin() + idx_greater, arr + idx_smaller + idx_same);
}

//6.1
void rearrange(int (& arr)[8], int index)
{
    int size = sizeof(arr) / sizeof(int);
    std::cout << "size: " << size << "\n";

    int pivot = arr[index];
    std::cout << "pivot: " << pivot << "\n";
    int idx_smaller = 0, idx_greater = size-1;

    for (int i = 0; i < size; ++i)
    {
        if (arr[i] < pivot)
        {
            int temp = arr[idx_smaller];
            arr[idx_smaller] = arr[i];
            arr[i] = temp;
            idx_smaller++;
        }
    }

    for (int i = size; i > idx_smaller; --i)
    {
        if (arr[i] > pivot)
        {
            int temp = arr[idx_greater];
            arr[idx_greater] = arr[i];
            arr[i] = temp;
            idx_greater--;
        }
    }
}

//6.1
int main_6_1()
{
    std::cout << "Hello World!\n";

    int arr[]{ 5, 8, 9, 1, 3, 3, 5, 9 };
    
    rearrange(arr, 0);

    int size = sizeof(arr) / sizeof(int);

    for (int i = 0; i < size; i++)
    {
        std::cout << " " << arr[i];
    }

    return 61;
}

//5.8
int main_5_8()
{
    int num = -9110;
    int num_flipped = 0;
    int remaining = abs(num);
    while (remaining > 0)
    {        
        int last_digit = remaining % 10;
        remaining = remaining / 10;
        num_flipped = num_flipped * 10 + last_digit;
    }
    std::cout << (num > 0 ? "" : "-") << num_flipped;
    return num_flipped;
}


//5.9 Palindrome?
bool is_palindrome(int num)
{
    //int num = 9118;   //yes
    //int num = 12321;   //yes
    //int num = 123;   //no

    //put number into array
    std::vector<int> num_array;
    int num_temp = num;
    while (num_temp > 0)
    {
        int last_digit = num_temp % 10;
        num_array.push_back(last_digit);
        num_temp = num_temp / 10;        
    }

    int first = 0;
    int last = num_array.size() - 1;
    int number_it = (num_array.size() + 1) / 2;
    
    for (int i = 0; i < number_it; i++)
    {
        if (num_array[first++] != num_array[last--]) return false;
    }
    return true;
}

bool is_palindrome_2(int num)
{
    //int num = 9118;   //yes
    //int num = 12321;   //yes
    //int num = 123;   //no

    int remaining = num;

    while (remaining > 0)
    {
        //highest digit
        int logar = int(std::log10(remaining));
        int highest_digit = remaining / std::pow(10, logar);
        int greatest = std::pow(10, logar) * highest_digit;

        //lowest digit
        int lowest_digit = remaining % 10;

        if (lowest_digit != highest_digit) return false;

        remaining = remaining - greatest;
        remaining = remaining / 10;
    }
    return true;
}

int RandomFunctionZeroOne()
{
     return rand() > RAND_MAX/2 ? 1 : 0;
}

// 5.10
int random_with_2_headed_coin(int num_of_result)
{
    int number;
    do
    {
        number = 0;
        for (int i = 0; (1 << i) < num_of_result; ++i)
        {
            int head = RandomFunctionZeroOne();
            number = number << 1 | head;
        }
    } while (number >= num_of_result);  // 0 is also an outcome. So 3 outcomes are 0, 1, 2  ( 3 would be too big)
    return number;
}

// 6.16
bool has_dublicats(const std::vector<std::vector<int>>(&partial_grid), int start_row, int end_row, int start_column, int end_column)
{
    const int size = 9 + 1; // 0-9 
    bool is_present[size] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = start_row; i < end_row; ++i)
    {
        for (int j = start_column; j < end_column; ++j)
        {
            if (partial_grid[i][j] > 0 && is_present[partial_grid[i][j]]) return true; // don't count 0s
            is_present[partial_grid[i][j]] = true;
        }
    }
    return false;
}


// 6.16
int check_sudoku()
{
    const int size = 9;
    std::vector<std::vector<int>> grid = {  {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 1, 0, 0, 0, 0, 0, 0},
                                            {1, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0} };

    for (int i = 0; i < size; ++i)
    {
        if (has_dublicats(grid, i, i+1, 0, 9)) return -1;   //rows
        if (has_dublicats(grid, 0, 9, i, i+1)) return -2;   //columns
    }

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            int row = i * 3;
            int column = j * 3;
            if (has_dublicats(grid, row, row + 3, column, column + 3)) return -3;   //3x3
        }
    }
    return 1;
}

//7.5
bool is_palandrome_sentence_2(std::string text)
{

    std::string text_cleaned;
    
    for (int i = 0; i < text.size(); ++i)
    {
        if (isalpha(text[i]))
        {
            text_cleaned = text_cleaned + static_cast<char>(std::tolower(text[i]));
        }
    }
    
    int start = 0;
    int end = text_cleaned.length() - 1;
    for (int i = 0; i < text_cleaned.length()/2; ++i)
    {
        char a = text_cleaned[start++];
        char b = text_cleaned[end--];
        if ( a != b) return false;
    }
    return true;
}

//7.5
bool is_palandrome_sentence(std::string text)
{
    int start = 0;
    int end = text.length() - 1;
    for (int i = 0; i < text.length() / 2; ++i)
    {
        while (!isalpha(text[start]) && start < end) { ++start; };  // while has a risk to run longer than expected
        while (!isalpha(text[end]) && start < end) { --end;};
        char a = static_cast<char> (std::tolower(text[start++]));
        char b = static_cast<char> (std::tolower(text[end--]));
        if (a != b) return false;
    }
    return true;
}


//7.6
std::string reverse_words_in_sentence(const std::string& sentence)
{
    std::string new_string;

    int end_word_idx = sentence.size() - 1;
    int begin_word_idx = end_word_idx;
    int sentence_idx = end_word_idx;

    while (begin_word_idx >= 0 )
    {
        while (sentence_idx > 0 && isalpha(sentence[--sentence_idx]))
        {
            begin_word_idx--;
        }
        std::string sub = sentence.substr(begin_word_idx, end_word_idx - begin_word_idx + 1);
        new_string.append(sub);
        new_string.append(" ");
        // set all indices to the last letter
        sentence_idx--;
        begin_word_idx = sentence_idx;
        end_word_idx = sentence_idx;
    }
    return new_string;
}

//8.5
void overlapping_list()
{
    //create list
    std::shared_ptr<Node> n1{ new Node(1) };
    auto n2 = std::make_shared<Node>(2);
    n1->SetNext(n2);
    auto n3 = std::make_shared<Node>(2);
    n1->GetNext()->SetNext(n3);
    auto n4 = std::make_shared<Node>(4);
    n1->GetNext()->GetNext()->SetNext(n4);

    std::shared_ptr<Node> n_it{ n1 };
    while (n_it->GetNext())
    {
        if (n_it->GetValue() == n_it->GetNext()->GetValue())
        {
            std::shared_ptr<Node> temp{ n_it->GetNext()->GetNext() };            
            n_it->SetNext(temp);
        }
        std::cout << n_it->GetValue() << std::endl;
        n_it = n_it->GetNext();
    }

    n_it = n1;
    while (n_it)
    {
        std::cout << n_it->GetValue() << std::endl;
        n_it = n_it->GetNext();
    }
}

//8.7
void remove_kth_last_element_from_list(int kth_last_element)
{
    //create list
    std::shared_ptr<Node> first_node{ new Node(0) };
    std::shared_ptr<Node> prev;
    prev = first_node;
    for (int i = 1; i < 10; ++i)
    {
        std::shared_ptr<Node> n{ new Node(i) };
        prev->SetNext(n);
        prev = n;
    }

    //move two pointers in kth_last_element distance
    std::shared_ptr<Node> ptr_ahead;
    std::shared_ptr<Node> ptr_behind;
    ptr_ahead = first_node;
    for (int i = 0; i < kth_last_element+1; ++i)
    {
        ptr_ahead = ptr_ahead->GetNext();
    }

    ptr_behind = first_node;
    while (ptr_ahead)
    {
        ptr_ahead = ptr_ahead->GetNext();
        ptr_behind = ptr_behind->GetNext();
    }

    std::cout << "ptr_behind - value: " << ptr_behind->GetValue() << std::endl;
    std::shared_ptr<Node> new_next = ptr_behind->GetNext()->GetNext();
    ptr_behind->SetNext(new_next);

    std::shared_ptr<Node> n_it;
    n_it = first_node;
    while (n_it)
    {
        std::cout << n_it->GetValue() << std::endl;
        n_it = n_it->GetNext();
    }
}

// 9.2
int eval_rpn(std::string& rpn)
{
    std::queue<std::string> buffer;
    //extraxt digits/operators
    std::stringstream substr;
    for (int i = 0; i < rpn.size(); ++i)
    {
        if (rpn[i] == ',')
        {
            buffer.push(substr.str());
            substr.str("");
        }
        else
        {
            substr << rpn[i];
        }        
    }
    buffer.push(substr.str());

    int result = 0;
    std::queue<int> buffer_num;
    while (!buffer.empty())
    {
        std::string ch = buffer.front();
        if (ch == "+")
        {
            int temp = 0;
            while (!buffer_num.empty())
            {
                temp += buffer_num.front();
                buffer_num.pop();
            }
            result += temp;
        }
        else if (ch == "*")
        {
            int temp = 1;
            while (!buffer_num.empty())
            {
                temp *= buffer_num.front();
                buffer_num.pop();
            }
            result *= temp;
        }
        else
        {
            buffer_num.push(stoi(ch));
        }
        buffer.pop();
    }
/*
    while(!buffer.empty())
    {        
        std::cout << buffer.front() << std::endl;
        buffer.pop();
    }
    */
    return result;
}

// 9.2
int eval_rpn_2(std::string& rpn)
{
    std::stringstream ss(rpn);
    std::string token;
    std::stack<int> buffer_num;
    while (std::getline(ss, token, ','))
    {
        std::string ch = token;
        if (ch == "+")
        {
            int x = buffer_num.top();
            buffer_num.pop();
            int y = buffer_num.top();
            buffer_num.pop();
            buffer_num.push(x + y);

        }
        else if (ch == "*")
        {
            int x = buffer_num.top();
            buffer_num.pop();
            int y = buffer_num.top();
            buffer_num.pop();
            buffer_num.push(x * y);
        }
        else
        {
            buffer_num.push(stoi(ch));
        }
    }
    return buffer_num.top();
}

void queue_vs_stack()
{
    std::queue<int> q;  //FIFO
    for (int i = 0; i < 5; ++i) q.push(i);
    std::cout << q.front() << std::endl;
    q.pop();
    std::cout << q.front() << std::endl;

    std::cout << "-----" << std::endl;
    std::stack<int> s; //LIFO
    for (int i = 0; i < 5; ++i) s.push(i);
    std::cout << s.top() << std::endl;
    s.pop();
    std::cout << s.top() << std::endl;
}

class MyQueue
{
public:
    MyQueue(int size) {
        queue.resize(size);
    }

    void enqueue(int elem)
    {                
        if (size == queue.size())
        {
            std::cout << "Resizing " << std::endl;
            std::rotate(queue.begin(), queue.begin() + front, queue.end());
            front = 0;
            rear = size;
            queue.resize(queue.size() * 2);
        }
        size++;
        queue[rear] = elem;
        rear = (rear + 1) % queue.size();
    }

    int dequeue()
    {
        if (size == 0)
        {
            std::cout << "empty" << std::endl;
        }
        size--;
        int val = queue[front];
        front = (front + 1) % queue.size();
        return val;        
    }

    void print()
    {
        int front_temp = front;
        for (int i = 0; i < size; ++i)
        {
            std::cout << queue[front_temp] << std::endl;
            front_temp = (front_temp + 1) % queue.size();
        }
    }

private:
    std::vector<int> queue;
    int rear = 0;
    int front = 0;
    int size = 0;
};

void use_queue()
{
    MyQueue Q(3);
    Q.enqueue(3);
    Q.enqueue(4);
    Q.enqueue(5);
    Q.print();
    Q.enqueue(6);
    Q.print();
    std::cout << "deqeued: " << Q.dequeue() << std::endl;
    Q.print();
    Q.enqueue(7);
    Q.enqueue(8);
    Q.print();
}

// 10.2 
class TreeNode
{
public:
    TreeNode(int value):
        value(value)
    {}

    TreeNode(int value, std::unique_ptr<TreeNode>& left, std::unique_ptr<TreeNode>& right):
        left_node(std::move(left)),
        right_node(std::move(right)),
        value(value)
    {}

    void append(std::unique_ptr<TreeNode>& left, std::unique_ptr<TreeNode>& right)
    {
        left_node = std::move(left);
        right_node = std::move(right);
    }

public:
    std::unique_ptr<TreeNode> left_node, right_node;
    int value;
};

bool nodes_equal(std::unique_ptr<TreeNode>& node1, std::unique_ptr<TreeNode>& node2)
{
    if (!node1 && !node2)
    {
        return true;
    }

    if (!node1 != !node2)
    {
        return false;
    }

    if (node1->value != node2->value)
    {
        return false;
    }

    if(nodes_equal(node1->left_node, node2->left_node) && nodes_equal(node1->right_node, node2->right_node))
    {
        return true;
    }

    return false;
}

bool check_equal(TreeNode& node)
{
    return nodes_equal(node.left_node, node.right_node);
}

void is_binary_tree_symmetric()
{
    // build a binary tree
    std::unique_ptr<TreeNode> left_root(new TreeNode(1));
    std::unique_ptr<TreeNode> right_root(new TreeNode(1));
    TreeNode root(0, left_root, right_root);

    std::unique_ptr<TreeNode> left1(new TreeNode(3));
    std::unique_ptr<TreeNode> right1(nullptr);
    root.left_node->append(left1, right1);

    std::unique_ptr<TreeNode> left2(new TreeNode(3));
    std::unique_ptr<TreeNode> right2(nullptr);
    root.right_node->append(left2, right2);

    std::cout << "Equal: " << check_equal(root) << std::endl;
}


//10.12

//11.3
void sort_almost_sorted(std::vector<int> array, int k)
{
    std::priority_queue<int, std::vector<int>, std::greater<>> pq;

    int i = 0;
    for ( ; i < k; ++i)
    {
        pq.emplace(array[i]);
    }

    for ( ; i< array.size(); ++i)
    {        
        pq.emplace(array[i]);
        std::cout << pq.top() << std::endl;
        pq.pop();
    }

    while (!pq.empty())
    {
        std::cout << pq.top() << std::endl;
        pq.pop();
    }
}

//12.3
bool sorted(std::vector<int>& array, int left, int right)
{
    bool ret = array[left] < array[right];
    return ret;
}

int find_unsorted(std::vector<int>& array, int left, int right)
{
    if (left + 1 == right)
    {
        if (array[left] < array[right]) return left;
        return right;
    }

    if (left == right)
    {
        return right;
    }
    
    if (!sorted(array, left, right))
    {
        int new_right = (left + right) / 2;
        if (!sorted(array, left, new_right))
        {
            return find_unsorted(array, left, new_right);
        }

        int new_left = ((left + right) + 0.5) / 2;
        if (!sorted(array, new_left, right))
        {
            return find_unsorted(array, new_left, right);
        }
    }
    else
    {
        return -1;
    }
}

int search_cyclically_sorted_array(std::vector<int>& array)
{
    int left = 0;
    int right = array.size() - 1;

    return find_unsorted(array, left, right);
}

int search_smallest(const std::vector<int>& a)
{
    int l = 0, r = a.size() - 1;

    while (l < r)
    {
        int mid = l + (r - l) / 2;
        if (a[mid] > a[r])
        {
            l = mid + 1;  // in right part
        }
        else
        {
            r = mid;
        }
    }
    return l;
}

int search_smallest_2(const std::vector<int>& a)
{
    int l = 0, r = a.size() - 1;

    while (l < r)
    {
        int mid = l + (r - l) / 2;
        if (a[l] > a[mid])
        {
            r = mid;  // in left part
        }
        else
        {
            l = mid + 1;
        }
    }
    return l;
}


//12.9
//find ip address that is not in the file

void create_file(std::vector<int>& f)
{
    for (int i = 0; i< f.size(); ++i)
    {
        f[i] = i;
    }
    f.erase(f.begin() + 64007);
}

void find_missing(std::vector<int>& f)
{
    // take the upper 8 bits of the 16bit numbers and count number of appearance
    std::vector<int> count( 1 << 8, 0 );
    
    for(int i =0; i < f.size(); ++i)
    {
        ++count[f[i] >> 8];
    }

    // get the index that does not have all possible possible variations of the lower 8 bits
    int missing_pre = 0;
    for (int i = 0; i < count.size(); ++i)
    {
        if (count[i] < (1 << 8))    // 8 bits -> 256 possible numbers
        {
            missing_pre = i;
            break;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        std::cout << count[i] << std::endl;
    }
    std::cout << "missing_pre: " << missing_pre << "  " << count[missing_pre] << std::endl;
    
    // find all numbers that match the higher 8 bits with missing_pre
    // create bitarray and set bit if lower 8 bit number is present
    std::bitset< 1<<8 > present;

    for (int i = 0; i < f.size(); ++i)
    {
        if (f[i] >> 8 == missing_pre)
        {
            present[f[i] & 0xFF] = true;
        }
    }

    // find the missing 8bit number
    for (int i = 0; i < present.size(); ++i)
    {
        if (present[i] == 0)
        {
            int missing = missing_pre << 8 | i;
            std::cout << "missing: " << missing << std::endl;
        }
    }
}

//13.1
bool palindrome_can_be_created(const std :: string str)
{
    std::unordered_map<char, int> count;
    bool uneven_found{ false };

    for (char c : str)
    {
        count[c]++;
    }

    for (auto c : count)
    {
        if (c.second % 2) {
            if (uneven_found) return false;
            uneven_found = true;
        }
    }

    for (auto c : count)
    {
        std::cout<< c.first << ": " << c.second << std::endl;
    }

    return true;
}

//13.6
void nearest_related_entries(std::vector<std::string> str)
{
    std::unordered_map<std::string, std::vector<int>> count_word_pos;
    std::unordered_map<std::string, std::vector<int>> count_word_dist;

    for (int pos = 0; pos < str.size(); ++pos)
    {
        if (count_word_pos.count(str[pos]) > 0)
        {
            int dist;
            dist = pos - count_word_pos[str[pos]][count_word_pos[str[pos]].size() - 1];
            count_word_dist[str[pos]].push_back(dist);
        }
        count_word_pos[str[pos]].push_back(pos);
    }

    for (auto& d : count_word_dist)
    {
        std::cout << d.first << ": ";
        for (int& s : d.second)
        {
            std::cout << s << ", ";
        }
        //std::vector<int>::iterator result = std::min_element(d.second.begin(), d.second.end());
        std::cout << "   min:" << *std::min_element(d.second.begin(), d.second.end());
        std::cout << std::endl;
    }
}


//13.6
int nearest_related_entries_2(std::vector<std::string> str)
{
    std::unordered_map<std::string, int> count_word_pos;
    int current_min = 99999;

    for (int pos = 0; pos < str.size(); ++pos)
    {
        auto current_word = count_word_pos.find(str[pos]);
        if (current_word != count_word_pos.end())   //word at str[pos] exists/was found
        {       
            //int dist = pos - (*current_word).second;   //works
            int dist = pos - current_word->second;       //works, too.
            current_min = std::min(dist, current_min);
        }
        count_word_pos[str[pos]] = pos;
    }
    return current_min;
}

// 14.4
// number of events in parallel

struct Event {
    Event(int start, int end): start(start), end(end) {}
    int start;
    int end;
};

struct Point {
    Point(int time, bool is_start): time(time), start(is_start) {};
    bool operator < (const Point& that) {
        return time < that.time;
    }
    int time;
    bool start;
};

int number_of_events_in_parallel(std::vector<Event> events)
{
    std::vector<Point> points;

    for (Event& e : events)
    {
        points.push_back(Point(e.start, true));
        points.push_back(Point(e.end, false));
    }

    std::sort(points.begin(), points.end());

    int concurrent_events = 0;
    for (Point& p : points)
    {
        if (p.start)         
        {
            concurrent_events++;
            std::cout << "start: " << p.time;
        }
        else
        {
            concurrent_events--;
            std::cout << "end: " << p.time;
        }
        std::cout << "  concurrent_events: " << concurrent_events << std::endl;        
    }

    return concurrent_events;
}

//15.4
struct BST_Node {
    BST_Node(std::string name, int key) : name(name), key(key), left(nullptr), right(nullptr) {};
    BST_Node() = default;
    BST_Node(const BST_Node& n) {
        this->name = n.name;
        this->key = n.key;
    };
    bool operator == (const BST_Node& that) { return key == that.key; }
    bool operator < (const BST_Node& that) { return key < that.key; }
    bool operator > (const BST_Node& that) { return key > that.key; }
    
    std::string name;
    int key;
    
    std::unique_ptr<BST_Node> left;
    std::unique_ptr<BST_Node> right;
    
};

std::vector<BST_Node> get_path(std::unique_ptr<BST_Node>& root, BST_Node& target)
{
    if (*root == target) {
        std::vector<BST_Node> temp;
        temp.push_back(target);
        return temp;
    }

    else if (target < *root && root->left) {
        std::vector<BST_Node> returned{ get_path(root->left, target) };
        std::vector<BST_Node> temp{ *root };
        for(BST_Node n: returned )
        { 
            temp.push_back(n);
        }       
        return temp;

    }
    else if (target > *root && root->right) {
        std::vector<BST_Node> returned{ get_path(root->right, target) };
        std::vector<BST_Node> temp{ *root };
        for (BST_Node n : returned)
        {
            temp.push_back(n);
        }
        return temp;
    }
    //error, node not found 
    return std::vector<BST_Node> {};
}

BST_Node& LCA(std::unique_ptr<BST_Node>& root, BST_Node& n1, BST_Node& n2)
{
    std::vector<BST_Node> v1 = get_path(root, n1);
    std::vector<BST_Node> v2 = get_path(root, n2);

    int i = 0;
    while (v1[i].name == v2[i].name) {
        i++;
    };
    std::cout << v1[i-1].name << std::endl;

    return v1[i-1];
}

BST_Node& LCA_2(std::unique_ptr<BST_Node>& root, BST_Node& n1, BST_Node& n2)
{
    /*
    - We found the LCA if n1 or n2 are equal to current root
    - if n1 and n2 are smaller than root, we need to look at the left subtree
    - if n1 and n2 are greater than root, we need to look at the right subtree
    - if n1 < root and n2 > root we found the LCA
    Assumption: n1 < n2
    */
    std::unique_ptr<BST_Node>& my_root = root;
    while (my_root->key < n1.key || my_root->key > n2.key)
    {
        while (my_root->key < n1.key)
        {
            my_root = std::move(my_root->right);
        }

        while (my_root->key > n2.key)
        {
            my_root = std::move(my_root->left);
        }
    }
    return *my_root;
}



BST_Node& LCA_3(std::unique_ptr<BST_Node>& root, BST_Node& n1, BST_Node& n2)
{
    /*
    - We found the LCA if n1 or n2 are equal to current root
    - if n1 and n2 are smaller than root, we need to look at the left subtree
    - if n1 and n2 are greater than root, we need to look at the right subtree
    - if n1 < root and n2 > root we found the LCA
    Assumption: n1 < n2
    */
    BST_Node* my_root = root.get();
    while (my_root->key < n1.key || my_root->key > n2.key)
    {
        while (my_root->key < n1.key)
        {
            my_root = my_root->right.get();
        }

        while (my_root->key > n2.key)
        {
            my_root = my_root->left.get();
        }
    }
    return *my_root;
}

// 15.8
std::unordered_map<std::string, std::shared_ptr<Node_15_8>> page_count;

struct cmp
{
    bool operator()(const std::shared_ptr<Node_15_8>& a, const std::shared_ptr<Node_15_8>& b) const
    {
        return a->value > b->value;
    }
};

std::set<std::shared_ptr<Node_15_8>, cmp> sorted_by_counts;

//now, get the k most visited pages
std::unordered_map<std::string, int> most_visited_pages(int k)
{
    std::unordered_map<std::string, int> temp;
    auto it = sorted_by_counts.begin();
    for (int i = 0; i<k; ++i)
    {
        temp[(*it)->name] = (*it)->value;
        it++;
    }
    return temp;
}

void count_visited_pages(std::string& log_line)
{
    if (page_count.find(log_line) == page_count.end())
    {        
        std::shared_ptr<Node_15_8> temp(new Node_15_8(0, log_line));
        page_count[log_line] = temp;
        sorted_by_counts.insert(temp);
    }
    page_count[log_line]->value++;
}

int main_1()
{
    //std::cout << is_palindrome_2(123) << "\n";
    //std::cout << is_palindrome_2(121) << "\n";
    // std::cout << random_with_2_headed_coin(6) << "\n";
    //std::cout << check_sudoku() << "\n";

 //   std::string text = { "a bcB7a" };
 //   std::cout << is_palandrome_sentence(text) << "\n";

 //   bool b[3] = { false, false, false };
 //   b[1] = true;
 //   std::cout << b[1] << "\n";

//    int index1 = 3;
//    int index2 = 3;
//    std::string str1{ "a_string1" };
//    std::string str2{ "a_string2" };
//    std::cout << "str1: " << str1[index1++] << "\n";
//    std::cout << "str2: " << str2[++index2] << "\n";


//    std::cout << reverse_words_in_sentence("this is a sentence") << "\n";

//    overlapping_list();
//    std::cout << overlapping_list() << "\n";
//    remove_kth_last_element_from_list(3);

    /*
    std::string rpn("2,2,+,3,*");
    std::cout<< eval_rpn_2(rpn) << std::endl;
    std::string rpn_1("2,2,+,3,3,*,*"); // (2 + 2) * (3 * 3)
    std::cout << eval_rpn_2(rpn_1) << std::endl;
    std::string rpn_2("123");
    std::cout << eval_rpn_2(rpn_2) << std::endl;
    std::string rpn_3("3,3,3,+,+");
    std::cout << eval_rpn_2(rpn_3) << std::endl;
    
    std::cout << std::endl << std::endl;
    
    queue_vs_stack();
    */
    // use_queue();
    // is_binary_tree_symmetric(); // 10.2

    //10.12

    //11.3
    /*
    std::vector<int> unsorted{ 3, -1, 2, 6, 4, 5, 8 };
    sort_almost_sorted(unsorted, 2); */

    //12.3
    //std::vector<int> cyclically_sorted{ 7, 8, 9, 10, 1, 2, 3, 4, 5, 6 };
    //std::vector<int> cyclically_sorted{ 5, 6, 1, 2, 3, 4};
    //std::cout << "position:" << search_cyclically_sorted_array(cyclically_sorted);
    //std::cout << "position:" << search_smallest(cyclically_sorted) << std::endl;
    //std::cout << "position:" << search_smallest_2(cyclically_sorted) << std::endl;

    //12.9
    /*
    std::vector<int> missing_numbers(1<<16, 0);
    create_file(missing_numbers);
    find_missing(missing_numbers);
    */

    //create_list_with_unique_contacts();
    // std::string s = { "aabbcccb" };
    // std::cout<<palindrome_can_be_created(s)<<std::endl;

    // std::vector<std::string> text = { "This", "is", "a", "string", "This", "is", "This" };
    // nearest_related_entries(text);
    // std::cout<<"nearest_related_entries_2: " << nearest_related_entries_2(text) << std::endl;

    // 14.4
    //std::vector<Event> events{Event(1,3), Event(2,3), Event(3,7), Event(4,7), Event(5,7) };
    //number_of_events_in_parallel(events);

    // 15.4
    //std::unique_ptr<BST_Node> root(new BST_Node("A", 20));
    //std::unique_ptr<BST_Node> n1(new BST_Node("B", 10));
    //std::unique_ptr<BST_Node> n2(new BST_Node("C", 30));
    //std::unique_ptr<BST_Node> n3(new BST_Node("D", 40));
    //std::unique_ptr<BST_Node> n4(new BST_Node("E", 25));
    //root->left = std::move(n1);
    //n2->right = std::move(n3);
    //n2->left = std::move(n4);
    //root->right = std::move(n2);

    //BST_Node find1("B", 26);
    //BST_Node find2("E", 35);

    //std::cout << LCA_2(root, find1, find2).name << std::endl;

    // 15.8
    std::vector<std::string> log_file = { "a", "b", "c", "a", "b", "c", "a", "a", "a", "b", "a", "b", "d" };

    for (std::string& log_line : log_file)
    {
        count_visited_pages(log_line);  //count pages
    }

    for (auto& page : page_count)
    {
        std::cout << page.first << ": " << page.second->value << std::endl;
    }

    for (auto& page : most_visited_pages(2))
    {
        std::cout << page.first << ": " << page.second << std::endl;
    }
    return 0;
}