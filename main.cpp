#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include "matplotlibcpp.h"

#define N 100
#define MAX 100000

namespace plt = matplotlibcpp;

using namespace std;


//随机打乱权重数组
void random(int w[])
{
    int index, tmp, i;
    srand(time(NULL));//随机数种子为time

    for (i = 0; i < N; i++)
    {
        index = rand() % (N - i) + i;
        if (index != i)
        {
            tmp = w[i];
            w[i] = w[index];
            w[index] = tmp;
        }
    }
}


int main()
{
    //开辟两个动态数组分别记录权重与k次取得最大值的次数
    int* w = new int[N];
    int* k_times = new int[N + 1];
    for (int i = 0; i < N; i++) {
        w[i] = i;
        k_times[i] = 0;
    }
    k_times[N] = 0;

    for (int s = 0; s < MAX; s++)
    {
        //打乱w权重的次序
        random(w);

        //进行抽奖模拟
        for (int k = 1; k < 101; k++)
        {
            int flag = 0;

            //设置最大值
            int max = 0;

            //遍历K个礼物，从中选出价值最大的礼物
            for (int stop = 0; stop < k; stop++)
            {
                if (w[stop] > max) max = w[stop];
            }


            //遍历后100-K个礼物，选出第一个价值大于max的礼物
            for (int stop = k; stop < N; stop++)
            {
                if (w[stop] > max)
                {
                    flag = 1;
                    max = w[stop];
                    break;
                }
            }

            //当flag == 0,没有找到大于max的数，只能选择最后那个
            if (flag == 0)max = w[N - 1];

            //当k==100时，没得选择，只能选最后那个
            if (k == 100) max = w[N - 1];

            //如果选出的价值最大,则记录K的值+1
            if (max == 99)
            {
                k_times[k]++;
            }


        }
    }

    for (int i = 0; i < N + 1; i++)
    {
        cout << k_times[i] << " ";
    }

    //对绘制K等于1到99的概率曲线
    
    std::vector<int> x(N), y(N);
    
    //给横坐标与纵坐标赋值

    for (int i = 0; i < N; i++)
    {
        x.at(i) = i + 1;
        y.at(i) = k_times[i + 1];
    }

    //开始绘图
    plt::figure_size(1200, 780);

    plt::plot(x, y);

    plt::xlim(0, 100);

    plt::title("K_times");

    plt::show();


    delete[]w;
    delete[]k_times;

    return 0;
}