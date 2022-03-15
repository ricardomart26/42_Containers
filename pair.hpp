#ifndef PAIR_HPP
#define PAIR_HPP

template <typename T1, typename T2> 
class pair {
    public:
        pair() : _first(), _second() {}
        pair(T1 &arg1, T2 &arg2) : _first(arg1), _second(arg2) {}

        pair(const pair &copy);

    private:
        T1 _first;
        T2 _second;
};

#endif

const 
