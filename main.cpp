#include <iostream>

class Sequence {
protected:
    double start, changer;

public:
    Sequence() : start(0), changer(0) {}

    Sequence(Sequence &obj) {
        start = obj.start;
        changer = obj.changer;
    }

    Sequence(Sequence &&obj) {
        start = obj.start;
        obj.start = 0;
        changer = obj.changer;
        obj.changer = 0;
    }

    Sequence(int start, int changer) : start(start), changer(changer) {}

    virtual double getSum(long long n) = 0;

    virtual Sequence *toPointer() = 0;
};

class Arithmetical : public Sequence {

public:
    Arithmetical(int start, int changer) : Sequence(start, changer) {}

    double getSum(long long n) override {

        double tmp = start, result = tmp;

        for (int i = 1; i < n; i++) {
            result += (tmp += changer);
        }

        return result;
    }

    Sequence *toPointer() override {
        return new Arithmetical(std::move(*this));
    }
};

class Geometrical : public Sequence {
public:
    Geometrical(int start, int changer) : Sequence(start, changer) {}

    double getSum(long long n) override {
        double tmp = start, result = tmp;

        for (int i = 1; i < n; i++) {
            result += (tmp *= changer);
        }

        return result;
    }

    Sequence *toPointer() override {
        return new Geometrical(std::move(*this));
    }
};

class Fibbonachi : public Sequence {
public:
    Fibbonachi(int start, int changer) : Sequence(start, changer) {}

    Fibbonachi() {
        start = 1;
        changer = 0;
    };

    double getSum(long long n) override {

        double tmp = start, result = tmp;

        for (int i = 1; i < n; i++) {
            result += (tmp += changer);

            changer = result;
        }

        changer = 0;

        return result;
    }

    Sequence *toPointer() override {
        return new Fibbonachi(std::move(*this));
    }
};

class Container {
private:
    Sequence **lst = nullptr;
    int curLen = 0, maxLen = 10;

public:
    Container() = default;

    ~Container() {
        delete[] lst;
    }

    void expand() {
        lst = new Sequence *[maxLen *= 2];
    }

    void push(Sequence &obj) {
        push(obj.toPointer());
    }

    void push(Sequence *obj) {
        if (lst == nullptr)
            expand();

        if (curLen == maxLen) {
            Sequence **saved = lst;
            expand();
            for (int i = 0; i < curLen; i++)
                lst[i] = saved[i];

            delete saved;
        }

        lst[curLen] = obj;

        curLen += 1;
    }

    double caclSum(int n) {
        double res = 0;

        for (int i = 0; i < curLen; res += lst[i]->getSum(n), i++) {}

        return res;
    }

};

int main() {
    Container c;
    c.push(new Fibbonachi());
    c.push(new Arithmetical(1, 2));
    c.push(new Geometrical(1, 1/3));

    std::cout << c.caclSum(2) << std::endl;

    return 0;
}