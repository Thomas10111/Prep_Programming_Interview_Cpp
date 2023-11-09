// ProgrammingInterview.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

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


int main()
{
    //std::cout << is_palindrome_2(123) << "\n";
    //std::cout << is_palindrome_2(121) << "\n";
    // std::cout << random_with_2_headed_coin(6) << "\n";
    std::cout << check_sudoku() << "\n";

 //   bool b[3] = { false, false, false };
 //   b[1] = true;
 //   std::cout << b[1] << "\n";

}