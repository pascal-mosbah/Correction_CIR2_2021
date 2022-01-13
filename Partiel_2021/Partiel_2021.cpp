#include <vector>
#include <iostream>
#include <complex>
#include <thread>

using std::complex;
using std::cout;
using std::endl;
using std::ostream;


#include <string>
#include <vector>
#include <random>
#include <map>
#include <algorithm>
#include <iostream>

struct comp_functor {
    bool operator()(const int& v1, const int& v2) {
        return v1 > v2;
    }
} comp_functor;

bool comp_function(const int& v1, const int& v2) {
    return v1 > v2;
}


struct Dictionary {
    std::string given_name;
    std::string address;
};


template <typename _T, size_t _SIZE>
class My_vector
{
private:
    _T *vec_;

public:
    typedef _T value_type;
    size_t get_size() const; // taille du vecteur

    My_vector(); // Constructeur, allocation mémoire (vec_)

    ~My_vector(); // destructeur, libération mémoire

    _T &operator[](const size_t &ind);      // retourne une référence sur le ième élément de vec_
    _T operator[](const size_t &ind) const; // retourne le ième élément de vec_

    template <typename _T1>
    _T1 operator*(const My_vector<_T1, _SIZE> &v); // produit scalaire de 2 vecteurs de type _T (de base) et type _T1 retournant un scalaire de type _T1 par défaut

    template <typename _T1>
    My_vector<_T1, _SIZE> operator*(const _T1 &val); // produit d'un vecteur de type _T par un scalaire de type _T1 retournant un My_vector par défaut de type T1 (imposé)

    template <typename T, size_t SIZE>
    friend std::ostream &operator<<(std::ostream &os, const My_vector<T, SIZE> &v); // Surcharge de l'opérateur <<
};

template <typename _T, size_t _SIZE>
class My_square_matrix
{
    My_vector<_T, _SIZE> *mat_;

public:
    size_t get_size() const;

    My_square_matrix(); // Constructeur, allocation mémoire (mat_)

    ~My_square_matrix(); // destructeur, libération mémoire

    My_vector<_T, _SIZE> &operator[](const size_t &ind); // retourne une référence sur le ième élément de mat_

    My_vector<_T, _SIZE> &operator[](const size_t &ind) const; // retourne le ième élément de mat_

    template <typename _T1>
    My_vector<_T1, _SIZE> operator*(My_vector<_T1, _SIZE> &v); // produit d'une matrice de type _T par un vecteur de type _T1 retournant un My_vector par défaut de type T1 (imposé)

    template <typename _T1>
    My_square_matrix<_T1, _SIZE> operator*(My_square_matrix<_T1, _SIZE> &m); // produit d'une matrice de type _T par une matrice de type de base _T1 retournant un My_vector par défaut de type T1 (imposé)

    template <typename T, size_t SIZE>
    friend std::ostream &operator<<(std::ostream &os, const My_square_matrix<T, SIZE> &v); // Surcharge de l'opérateur <<
};

template <typename _T, size_t _SIZE>
My_vector<_T, _SIZE>::My_vector()
{
    vec_ = new _T[_SIZE];
}

template <typename _T, size_t _SIZE>
My_vector<_T, _SIZE>::~My_vector()
{
    delete[] vec_;
}

template <typename _T, size_t _SIZE>
size_t My_vector<_T, _SIZE>::get_size() const
{
    return _SIZE;
}

template <typename _T, size_t _SIZE>
_T &My_vector<_T, _SIZE>::operator[](const size_t &ind)
{
    return vec_[ind];
}

template <typename _T, size_t _SIZE>
_T My_vector<_T, _SIZE>::operator[](const size_t &ind) const
{
    return vec_[ind];
}

template <typename _T, size_t _SIZE>
template <typename _T1>
_T1 My_vector<_T, _SIZE>::operator*(const My_vector<_T1, _SIZE> &v)
{
    _T1 sum = 0;
    for (size_t i = 0; i < v.get_size(); ++i)
    {
        sum += vec_[i] * v[i];
    }
    return sum;
}

template <typename _T, size_t _SIZE>
template <typename _T1>
My_vector<_T1, _SIZE> My_vector<_T, _SIZE>::operator*(const _T1 &val)
{
    My_vector<_T1, _SIZE> v;
    _T1 sum = 0;
    for (size_t i = 0; i < get_size(); ++i)
    {
        v[i] = vec_[i] * val;
    }
    return v;
}

template <typename _T, size_t _SIZE>
std::ostream &operator<<(std::ostream &os, const My_vector<_T, _SIZE> &v)
{
    for (unsigned i = 0; i < _SIZE; ++i)
    {
        os << v[i] << " ";
    }
    return os;
}

template <typename _T, size_t _SIZE>
My_square_matrix<_T, _SIZE>::My_square_matrix()
{
    mat_ = new My_vector<_T, _SIZE>[_SIZE];
}

template <typename _T, size_t _SIZE>
My_square_matrix<_T, _SIZE>::~My_square_matrix()
{
    delete[] mat_;
}

template <typename _T, size_t _SIZE>
template <typename _T1>
My_vector<_T1, _SIZE> My_square_matrix<_T, _SIZE>::operator*(My_vector<_T1, _SIZE> &v)
{
    My_vector<_T1, _SIZE> r;
    for (size_t i = 0; i < _SIZE; ++i)
    {
        r[i] = mat_[i] * v;
    }
    return r;
}

template <typename _T, size_t _SIZE>
template <typename _T1>
My_square_matrix<_T1, _SIZE> My_square_matrix<_T, _SIZE>::operator*(My_square_matrix<_T1, _SIZE> &m)
{
    My_square_matrix<_T1, _SIZE> r;
    My_vector<_T1, _SIZE> v;
    for (size_t i = 0; i < _SIZE; ++i)
    {
        for (size_t j = 0; j < _SIZE; ++j)
        {
            for (size_t k = 0; k < _SIZE; ++k)
            {
                v[k] = m[k][j];
            }
            r[i][j] = mat_[i] * v;
        }
    }
    return r;
}

template <typename _T, size_t _SIZE>
size_t My_square_matrix<_T, _SIZE>::get_size() const
{
    return _SIZE;
}

template <typename _T, size_t _SIZE>
My_vector<_T, _SIZE> &My_square_matrix<_T, _SIZE>::operator[](const size_t &i)
{
    return mat_[i];
}

template <typename _T, size_t _SIZE>
My_vector<_T, _SIZE> &My_square_matrix<_T, _SIZE>::operator[](const size_t &i) const
{
    return mat_[i];
}

template <typename _T, size_t _SIZE>
ostream &operator<<(ostream &os, const My_square_matrix<_T, _SIZE> &m)
{
    for (size_t imat = 0; imat < m.get_size(); ++imat)
    {
        os << m[imat] << " ";
    }
    return os;
}

int main()
{
    std::default_random_engine rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-100, 100);  //(min, max)
    std::vector<int> v;
    v.reserve(100);
    auto comp_lambda = [](const int& a, const int& b) {return a > b; };
    for (int i = 0; i < 100; ++i) {
        v.push_back(dist(rng)); //génération alléatoire de valeurs
    }
    std::sort(v.begin(), v.end(), comp_lambda);
    std::sort(v.begin(), v.end(), comp_functor);
    std::sort(v.begin(), v.end(), comp_function);

    constexpr size_t size = 3;
    My_vector<float, size> v1;
    My_vector<float, size> v2;
    My_vector<complex<float>, size> v3;
    My_square_matrix<float, size> m1;
    My_square_matrix<float, size> m2;
    for (size_t i = 0; i < size; ++i)
    {
        v1[i] = i;
        v2[i] = i + 1;
        v3[i] = complex<float>(i + 1, i);
        for (size_t j = 0; j < size; ++j)
        {
            m1[i][j] = 1;
            m2[i][j] = i * m1.get_size() + j;
        }
    }

    cout << "get_size :" << v1.get_size() << endl;
    cout << "V1 : " << v1 << endl;

    cout << "get_size :" << v1.get_size() << endl;
    cout << "V2 : " << v2 << endl;

    cout << "get_size :" << v3.get_size() << endl;
    cout << "V3 : " << v3 << endl;

    cout << "V1*V2 : " << v1 * v2 << endl;
    cout << "V1*V3 : " << v1 * v3 << endl;

    cout << "V1*(2,1) : " << v1 * complex<float>(2, 1) << endl;
    // Voir également question (2.a), la définition de my_vector et l'affichage du contenu de v1, v2 et v3
    cout << "M1 : " << m1 << endl;
    cout << "M2 : " << m2 << endl;
    cout << "M2*V1 : " << m2 * v1 << endl;
    cout << "M2*V3 : " << m2 * v3 << endl;
    cout << "M1*M2 : " << m1 * m2 << endl;
    return EXIT_SUCCESS;
}

