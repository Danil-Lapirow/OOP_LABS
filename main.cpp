#include <iostream>
#include <sstream>

class Stack {
private:
    int *start;
    int maxLen = 10;
    int curLen = 0;

public:
    Stack() {
        start = new int[maxLen];
    }

    Stack(std::initializer_list<int> lst) {
        start = new int[maxLen];

        for (auto it : lst) {
            push(it);
        }
    }

    Stack(Stack &other) {
        start = new int[other.maxLen];
        curLen = other.curLen;
        maxLen = other.maxLen;
        for (int i = 0; i < curLen; i++)
            start[i] = other.start[i];
    }

    Stack(Stack &&other) {
        start = other.start;
        other.start = nullptr;
        curLen = other.curLen;
        maxLen = other.maxLen;
    }

    ~Stack() {
        delete start;
    }

    int read() {
        return curLen == 0 ? 0 : start[curLen - 1];
    }

    int size() {
        return curLen;
    }

    bool empty() {
        return curLen == 0;
    }

    Stack &operator=(const Stack& other)= default;

    void push(int value) {
        if (curLen + 1 == maxLen) {
            int *tmp = new int[maxLen *= 2];
            for (int i = 0; i < curLen; i++) {
                tmp[i] = start[i];
            }
            delete start;
            start = tmp;
        } else {
            start[curLen] = value;
        }
        curLen++;
    }

    int pop() {
        if (empty())
            return 0;

        int res = read();

        curLen--;

        return res;
    }

    Stack &operator>(int &var) {
        var = read();
        return *this;
    }

    Stack &operator>>(int &var) {
        var = pop();
        return *this;
    }

    Stack &operator<(int value) {
        push(value);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, Stack &other) {
        return os << other.pop();
    }

    friend std::istream &operator>>(std::istream &os, Stack &other) {
        int t = 0;
        std::cout << "Number to insert into stack: ";
        os >> t;
        other < t;
        return os;
    }

    friend std::ostream &operator<(std::ostream &os, Stack &other) {
        return os << other.read();
    }
};

int main() {
    Stack c{16, 15, 14, 13, 12, 11, 10};
    c < 9 < 8 < 7 < 6 < 5 < 4 < 3;

    std::cin >> c;
    std::cin >> c;

    std::cout << "| ";

    while (!c.empty()) {
        std::cout << c << " - ";
        (std::cout < c) << " | ";
    }


    return 0;
}
