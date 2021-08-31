#include <iostream>
using namespace std;

struct Fraction
{
    private:
    void reduce()
    {
        long long g = gcd((t>0?t:-t),(b>0?b:-b));
        t /= g;
        b /= g;
    }
    long long gcd(long long x, long long y)
    {
        if(y==0) return x;
        return gcd(y, x%y);
    }
    public:
    long long t,b; // a/b
    Fraction(long long t=0, long long b=1)
    :t(t), b(b)
    {
        reduce();
        if(this->b < 0)
        {
            this->b = -b;
            this->t = -t;
        }
        else if(this->t==0) this->b = 1;
    }
    
    Fraction operator+(const Fraction& f)const
    {
        return Fraction(t*f.b + f.t*b, b*f.b);
    }
    Fraction& operator+=(const Fraction& f)
    {
        *this = *this + f;
        return *this;
    }
    Fraction operator-(const Fraction& f)const
    {
        return Fraction(t*f.b - f.t*b, b*f.b);
    }
    Fraction operator*(const Fraction& f)const
    {
        return Fraction(t*f.t, b*f.b);
    }
    Fraction& operator*=(const Fraction& f)
    {
        *this = *this * f;
        return *this;
    }
    Fraction operator/(const Fraction& f) const
    {
        return Fraction(t*f.b, b*f.t);
    }
    Fraction operator-()const
    {
        return Fraction(-t,b);
    }
    bool operator<(const Fraction& f) const
    {
        Fraction sub = *this-f;
        return sub.t < 0;
    }
    bool operator>(const Fraction& f)const
    {
        Fraction sub = *this-f;
        return sub.t > 0;
    }
    bool operator==(const Fraction& f)const
    {
        Fraction sub = *this-f;
        return sub.t == 0;
    }
    bool operator<(long long x)const
    {
        return t < b*x;
    }
    bool operator>(long long x)const
    {
        return t > x*b;
    }
    bool operator==(long long x)const
    {
        return t == x*b;
    }
    bool operator!=(long long x)const
    {
        return t != x*b;
    }

    Fraction inverse() const
    {
        return Fraction(b,t);
    }
};

ostream& operator<<(ostream& os, const Fraction& f)
{
    os << " [ " << f.t << " / " << f.b << " ] ";
    return os;
}

Fraction abs(const Fraction& f)
{
    return Fraction((f.t>0? f.t:-f.t),(f.b>0? f.b:-f.b));
}

Fraction operator/(long long x, const Fraction& f)
{
    return Fraction(x*f.b,f.t);
}
