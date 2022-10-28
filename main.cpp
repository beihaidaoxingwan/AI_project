#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include "matplotlibcpp.h"

#define N 100
#define MAX 100000

namespace plt = matplotlibcpp;

using namespace std;


//�������Ȩ������
void random(int w[])
{
    int index, tmp, i;
    srand(time(NULL));//���������Ϊtime

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
    //����������̬����ֱ��¼Ȩ����k��ȡ�����ֵ�Ĵ���
    int* w = new int[N];
    int* k_times = new int[N + 1];
    for (int i = 0; i < N; i++) {
        w[i] = i;
        k_times[i] = 0;
    }
    k_times[N] = 0;

    for (int s = 0; s < MAX; s++)
    {
        //����wȨ�صĴ���
        random(w);

        //���г齱ģ��
        for (int k = 1; k < 101; k++)
        {
            int flag = 0;

            //�������ֵ
            int max = 0;

            //����K���������ѡ����ֵ��������
            for (int stop = 0; stop < k; stop++)
            {
                if (w[stop] > max) max = w[stop];
            }


            //������100-K�����ѡ����һ����ֵ����max������
            for (int stop = k; stop < N; stop++)
            {
                if (w[stop] > max)
                {
                    flag = 1;
                    max = w[stop];
                    break;
                }
            }

            //��flag == 0,û���ҵ�����max������ֻ��ѡ������Ǹ�
            if (flag == 0)max = w[N - 1];

            //��k==100ʱ��û��ѡ��ֻ��ѡ����Ǹ�
            if (k == 100) max = w[N - 1];

            //���ѡ���ļ�ֵ���,���¼K��ֵ+1
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

    //�Ի���K����1��99�ĸ�������
    
    std::vector<int> x(N), y(N);
    
    //���������������긳ֵ

    for (int i = 0; i < N; i++)
    {
        x.at(i) = i + 1;
        y.at(i) = k_times[i + 1];
    }

    //��ʼ��ͼ
    plt::figure_size(1200, 780);

    plt::plot(x, y);

    plt::xlim(0, 100);

    plt::title("K_times");

    plt::show();


    delete[]w;
    delete[]k_times;

    return 0;
}