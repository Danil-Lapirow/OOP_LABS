#include <iostream>

class NumberCircle {
private:
    int *start;
    int *current;
    int maxLen = 10;
    int curLen = 0;

public:
    NumberCircle() {
        start = new int[maxLen];
        current = start;
    }

    NumberCircle(std::initializer_list<int> lst) {
        start = new int[maxLen];
        current = start;

        for (auto it : lst) {
            insert(it);
//            forward();
        }
        current = start;
    }

    NumberCircle(NumberCircle &other) {
        start = new int[other.maxLen];
        current = start + (other.current - other.start);
        curLen = other.curLen;
        maxLen = other.maxLen;
        for (int i = 0; i < curLen; i++)
            start[i] = other.start[i];
    }

    NumberCircle(NumberCircle &&other) {
        start = other.start;
        other.start = nullptr;
        current = start + (other.current - other.start);
        curLen = other.curLen;
        maxLen = other.maxLen;
    }

    ~NumberCircle() {
        delete start;
//        delete current;
    }

    int read() {
        return *current;
    }

    int size() {
        return curLen;
    }

    bool empty() {
        return curLen == 0;
    }

    void insert(int value) {
        if (curLen + 1 == maxLen) {
            int *tmp = new int[maxLen *= 2];
            bool greater = false;
            for (int i = 0; i < curLen; i++) {
                if (start + i == current) {
                    tmp[i] = value;
                    greater = true;
                }

                tmp[i + greater] = start[i];
            }
            delete start;
            start = tmp;
            current = start;
        } else {

            int prev = value;
            for (int *i = current; i < start + curLen + 1; i++) {
                int tmp = *i;
                i[0] = prev;
                prev = tmp;
            }
        }
        curLen++;
    }

    int pop() {
        if (empty())
            return 0;
        int res = *current;
        for (int *i = current; i < start + curLen; i++)
            i[0] = i[1];

        curLen--;
        if (current == start + curLen)
            current = start;

        return res;
    }

    int forward(int i = 0) {
        if (i > 0)
            forward(i - 1);

        if (current == start + curLen - 1)
            current = start;
        else
            current++;

        return *current;
    }

    int backward(int i = 0) {
        if (i > 0)
            backward(i - 1);

        if (current == start)
            current = start + curLen - 1;
        else
            current--;

        return *current;
    }

    NumberCircle &operator>(int &var) {
        var = read();
        return *this;
    }

    NumberCircle &operator>>(int &var) {
        var = pop();
        return *this;
    }

    NumberCircle &operator<(int value) {
        insert(value);
        return *this;
    }

    NumberCircle &operator++() {
        forward();
        return *this;
    }

    NumberCircle operator++(int) {
        NumberCircle saved(*this);
        forward();
        return saved;
    }

    NumberCircle &operator--() {
        backward();
        return *this;
    }

    NumberCircle operator--(int) {
        NumberCircle saved(*this);
        backward();
        return saved;
    }

    friend std::ostream &operator<<(std::ostream &os, NumberCircle &circle) {
        return os << circle.pop();
    }

    friend std::ostream &operator<(std::ostream &os, NumberCircle &circle) {
        return os << circle.read();
    }
};

int main() {
    NumberCircle c{16, 15, 14, 13, 12, 11, 10};
    c < 9 < 8 < 7 < 6 < 5 < 4 < 3 < 2 < 1;

    int t;

    for (int i = 0; i < 20; i++) {
        std::cout << c << " |";
        std::cout << (c++ >> t) << "-";
        std::cout << t << "| ";
    }


    return 0;
}
