#include <omp.h>
#include <iostream>


int main(){
    // RiemannSum
    // static long num_steps = 100000;
    // double step;
    // int main ()
    // {
    //     int i;
    //     double x, pi, sum = 0.0;

    //     step = 1.0 / (double) num_steps;

    //     for (i = 0; i < num_steps; i++) {
    //         x = (i + 0.5) * step;
    //         sum = sum + 4.0 / (1.0 + x * x);
    //     }
    //     pi = step * sum;
    // }

    double st, end;
    double sum;
    size_t steps = 1000000;
    double steps_double = static_cast<double>(steps);
    const size_t NTHREAD = 12;

    st = omp_get_wtime();
    sum = 0;
    for (size_t i=0; i<steps ; ++i){
        double x = static_cast<double>(i+0.5) / steps_double;
        sum += 4 / (1.0 + pow(x, 2));
    }
    sum /= steps_double;
    end = omp_get_wtime();
    std::cout << "sum: " << sum <<std::endl;
    std::cout << "c++ time: " << end - st <<std::endl;



    st = omp_get_wtime();
    sum = 0;
    #pragma omp parallel for num_threads(NTHREAD) 
    for (size_t i=0; i<steps ; ++i){
        double x = static_cast<double>(i+0.5) / steps_double;
        #pragma omp atomic
        sum += 4 / (1.0 + pow(x, 2));
    }
    sum /= steps_double;
    end = omp_get_wtime();
    std::cout << "sum: " << sum <<std::endl;
    std::cout << "openmp atomic time: " << end - st <<std::endl;
    


    st = omp_get_wtime();
    sum = 0;
    #pragma omp parallel for num_threads(NTHREAD) reduction(+:sum)
    for (size_t i=0; i<steps ; ++i){
        double x = static_cast<double>(i+0.5) / steps_double;
        sum += 4 / (1.0 + pow(x, 2));
    }
    sum /= steps_double;
    end = omp_get_wtime();
    std::cout << "sum: " << sum <<std::endl;
    std::cout << "openmp reduction time: " << end - st <<std::endl;


    st = omp_get_wtime();
    sum = 0;
    double local_sums[NTHREAD];
    #pragma omp parallel num_threads(NTHREAD)
    {
        size_t tid = omp_get_thread_num();
        double local_sum = 0;
        for (size_t i=tid; i< steps; i+=NTHREAD){
            double x = static_cast<double>(i+0.5) / steps_double;
            local_sum += 4 / (1.0 + pow(x, 2));
        }
        local_sums[tid] = local_sum;
    }
    for (size_t i=0; i<NTHREAD; ++i){
        sum += local_sums[i];
    }
    sum /= steps_double;
    end = omp_get_wtime();
    std::cout << "sum: " << sum <<std::endl;
    std::cout << "openmp block local_sums time: " << end - st <<std::endl;



    st = omp_get_wtime();
    sum = 0;
    #pragma omp parallel num_threads(NTHREAD)
    {
        size_t tid = omp_get_thread_num();
        double local_sum = 0;
        for (size_t i=tid; i< steps; i+=NTHREAD){
            double x = static_cast<double>(i+0.5) / steps_double;
            local_sum += 4 / (1.0 + pow(x, 2));
        }

        #pragma omp atomic
        sum += local_sum;
    }
    sum /= steps_double;
    end = omp_get_wtime();
    std::cout << "sum: " << sum <<std::endl;
    std::cout << "openmp block atomic time: " << end - st <<std::endl;
}