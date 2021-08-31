#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

#define rep(i,n) for(int (i)=0;(i)<(n);++(i))
typedef double E;

class Matrix
{
    
    public:
    vector<vector<E> > data;
    int rows,cols;

    Matrix(int r=1, int c=1)
    : rows(r), cols(c)
    {
        data = vector<vector<E> >(r, vector<E>(c));
    }

    void row_swap(int i, int j)
    {
        rep(c, cols) swap(data[i][c], data[j][c]);
    }
    void row_mul_c(int r, E c)
    {
        rep(k, cols) data[r][k] *= c;
    }
    void row_j_ic(int j, int i, E c)
    {
        rep(k, cols) data[j][k] += data[i][k]*c;
    }

    Matrix operator*(const Matrix& m) const
    {
        Matrix ret(rows, cols);
        rep(r, rows)
            rep(c, cols)
                rep(k, cols)
                {
                    ret.data[r][c] += data[r][k]*m.data[k][c];
                }
        return ret;
    }

    Matrix operator+(const Matrix& m) const
    {
        Matrix ret(rows, cols);
        rep(r, rows)
            rep(c, cols)
                ret.data[r][c] = data[r][c] + m.data[r][c];
        return ret;
    }

    Matrix operator-(const Matrix& m) const
    {
        Matrix ret(rows, cols);
        rep(r, rows)
            rep(c, cols)
                ret.data[r][c] = data[r][c] - m.data[r][c];
        return ret;
    }

    Matrix T()const
    {
        Matrix ret(cols, rows);
        rep(r, rows)
            rep(c, cols)
                ret.data[r][c] = data[c][r];
        return ret;
    }

    Matrix copy() const
    {
        Matrix ret(rows, cols);
        rep(r, rows)
            rep(c, cols)
                ret.data[r][c] = data[r][c];
        return ret;
    }

};

Matrix rref(const Matrix& A)
{
    Matrix R = A.copy();
    rep(pivot, R.rows)
    {
        int max_i = pivot;
        E max_e = abs(R.data[pivot][pivot]);
        for(int r=pivot+1; r<R.rows;++r)
        {
            if(max_e < abs(R.data[r][pivot]))
            {
                max_e = abs(R.data[r][pivot]);
            }
        }
        R.row_swap(pivot, max_i);
        if(R.data[pivot][pivot] == 0) continue;
        for(int r=pivot+1;r<R.rows;++r)
        {
            R.row_j_ic(r, pivot, -R.data[r][pivot]/R.data[pivot][pivot]);
        }
        R.row_mul_c(pivot, 1ll/R.data[pivot][pivot]);
    }
    return R;
}

ostream& operator<<(ostream& os, const Matrix& m)
{
    os << "rows : " << m.rows << " cols : " << m.cols << endl;
    rep(r, m.rows)
    {
        cout << "[ ";
        rep(c, m.cols) os << m.data[r][c] << ' ';
        cout << " ]";
        os << endl;
    }
    cout << endl;
    return os;
}

Matrix identity_matrix(int n)
{
    Matrix I = Matrix(n,n);
    rep(i,n) I.data[i][i] = 1;
    return I;
}

Matrix inverse(const Matrix& M)
{
    Matrix A = M.copy();
    Matrix I = identity_matrix(A.cols);
    
    rep(pivot, A.rows)
    {
        int max_i = pivot;
        E max_e = abs(A.data[pivot][pivot]);
        for(int r=pivot+1; r<A.rows;++r)
        {
            if(max_e < abs(A.data[r][pivot]))
            {
                max_e = abs(A.data[r][pivot]);
            }
        }

        A.row_swap(pivot, max_i);
        I.row_swap(pivot, max_i);

        if(A.data[pivot][pivot] == 0) continue;
        rep(r, A.rows) if(r != pivot)
        {
            E d = -A.data[r][pivot]/A.data[pivot][pivot];
            A.row_j_ic(r, pivot, d);
            I.row_j_ic(r, pivot, d);
        }
        E d = A.data[pivot][pivot];
        I.row_mul_c(pivot, 1/d);
        A.row_mul_c(pivot, 1/d);
        
    }
    return I;
}
