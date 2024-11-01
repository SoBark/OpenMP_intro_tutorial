#include <stdio.h>
#include <omp.h>
static long num_steps = 100000000;
double step;
#define NUM_THREADS 16
int main()
{
    double start_time, run_time;
    double pi;
    step = 1.0 / (double)num_steps;
    omp_set_num_threads(NUM_THREADS);
    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        int n_t = omp_get_num_threads();
        int id = omp_get_thread_num();
        // printf("Thread %d \n", id);
        int i;
        double x, sum = 0.0;
        int top_border = num_steps/n_t *(id+1);
        for (i = num_steps/n_t * id + 1; i <= top_border; i++)
        {
            x = (i - 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
            // sum_threads[id] = sum_threads[id] + 4.0 / (1.0 + x * x);
        }
        sum *= step;
        #pragma omp atomic
        pi += sum;
    }
    // pi = step * sum;
    run_time = omp_get_wtime() - start_time;
    printf("\n pi with %ld steps is %lf in %lf seconds\n ", num_steps, pi, run_time);
}
