// ProgrammingInterview.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "ListNode.h"
#include <queue>
#include <sstream>
#include <stack>

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

int main()
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
    use_queue();
}