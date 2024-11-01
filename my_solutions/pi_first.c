#include <stdio.h>
#include <omp.h>
static long num_steps = 100000000;
double step;
int main()
{
    // double x, pi, sum = 0.0;
    double start_time, run_time;
    double pi, sum = 0.0;
    step = 1.0 / (double)num_steps;
    const int NUM_THREADS = 4;
    int threads = NUM_THREADS;
    omp_set_num_threads(NUM_THREADS);
    double sum_threads[NUM_THREADS] = {0.0};
    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        int n_t = omp_get_num_threads();
        int id = omp_get_thread_num();
        // printf("Thread %d \n", id);
        int i;
        double x;
        int top_border = num_steps/n_t *(id+1);
        if (id == 0)
        {
            threads = n_t;
        }
        for (i = num_steps/n_t * id + 1; i <= top_border; i++)
        {
            x = (i - 0.5) * step;
            sum_threads[id] = sum_threads[id] + 4.0 / (1.0 + x * x);
        }
    }
    for (int i = 0; i < threads; i++)
        sum += sum_threads[i];
    pi = step * sum;
    run_time = omp_get_wtime() - start_time;
    printf("\n pi with %ld steps is %lf in %lf seconds\n ", num_steps, pi, run_time);
}