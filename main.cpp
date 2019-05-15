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
        for (int *i = current; i < start + curLen; i++) {
            i[0] = i[1];
        }
        curLen--;
        if(current == start + curLen)
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

    int operator>(int){
        return read();
    }

    int operator>>(int){
        return pop();
    }

    NumberCircle &operator<(int value){
        insert(value);
        return *this;
    }

    NumberCircle &operator++(){
        forward();
        return *this;
    }

    NumberCircle &operator++(int){
        forward();
        return *this;
    }

    NumberCircle &operator--(){
        backward();
        return *this;
    }

    NumberCircle &operator--(int){
        backward();
        return *this;
    }
};

int main() {
    NumberCircle c;
    c < 16;
    c.insert(15);
    c.insert(14);
    c.insert(13);
    c.insert(12);
    c.insert(11);
    c.insert(10);
    c.insert(9);
    c.insert(8);
    c.insert(7);
    c.insert(6);
    c.insert(5);
    c.insert(4);
    c.insert(3);
    c.insert(2);
    c.insert(1);

    for (int i = 0; i < 20; i++) {
        std::cout << c.pop() << std::endl;
        c++;
    }

    return 0;
}
