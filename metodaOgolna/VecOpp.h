#ifndef VECOPP_H_INCLUDED
#define VECOPP_H_INCLUDED

#include <vector>
#include <iostream>


class VecOpp
{
    public:
        template <typename T>
        static std::vector<T> add (const std::vector<T>& x1,const std::vector<T>& x2)
        {
            std::vector<T> res;
            res.reserve(x1.size());

            for(size_t i = 0; i < x1.size(); i++)
            {
                res.push_back( x1[i] + x2[i] );
            }
            return res;
        }

        template <typename T>
        static std::vector<T> subt (const std::vector<T>& x1,const std::vector<T>& x2)
        {
            std::vector<T> res;
            res.reserve(x1.size());

            for(size_t i = 0; i < x1.size(); i++)
            {
                res.push_back( x1[i] - x2[i] );
            }
            return res;
        }

        template <typename T>
        static std::vector<T> mult (const std::vector<T>& x1,const double a)
        {
            std::vector<T> res;
            res.reserve(x1.size());

            for(size_t i = 0; i < x1.size(); i++)
            {
                res.push_back( x1[i] * a );
            }
            return res;
        }

        template <typename T>
        static std::vector<T> mult (const double a,const std::vector<T>& x1)
        {
            std::vector<T> res;
            res.reserve(x1.size());

            for(size_t i = 0; i < x1.size(); i++)
            {
                res.push_back( x1[i] * a );
            }
            return res;
        }

        template <typename T>
        static void print(const std::vector<T>& x)
        {
            for(const auto& val : x)
            {
                std::cout<<val<<'\t';
            }
            std::cout<<std::endl;
        }

        template <typename T>
        static std::vector<T> mult (const std::vector<std::vector<T>>& m,const std::vector<T>& x)
        {
            std::vector<T> res(x.size(),0);

            for(size_t i = 0; i < x.size(); i++)
            {
                //res[i] = 0;
                for(size_t j = 0; j < x.size(); j++)
                {
                    res[i] += x[j] * m[i][j];
                }
            }
            return res;
        }

        template <typename T>
        static double innerProd (const std::vector<T>& x1,const std::vector<T>& x2)
        {
            double res=0;

            for(size_t i = 0; i < x1.size(); i++)
            {
                res += x1[i] * x2[i];
            }
            return res;
        }

    protected:

    private:
};

#endif // VECOPP_H_INCLUDED
