
//#include<iostream> 
#include <julia.h>
#include <stdio.h>
#include <time.h>
//gcc -o test -fPIC -I/mnt/s/projectDrone/Linux/julia-1.3.1/include/julia -L/mnt/s/projectDrone/Linux/julia-1.3.1/lib testing.c -ljulia
JULIA_DEFINE_FAST_TLS()
//using namespace std;



int main(int argc, char *argv[]){
	
	jl_init();
	
	/* required: setup the Julia context */
	
	/* create a 1D array of length 4 */
	 // jl_eval_string("print(pwd())");
	
    double length = 3;
    double *existingArray = (double*)malloc(sizeof(double)*length);
	/* create a *thin wrapper* around our C array */
    jl_value_t* array_type = jl_apply_array_type((jl_value_t*)jl_float64_type, 1);
    jl_array_t *x = jl_ptr_to_array_1d(array_type, existingArray, length, 0);
    JL_GC_PUSH1(&x);
	struct timespec start, end;
    /* fill in values */
    double *xData = (double*)jl_array_data(x);
    for (int i = 0; i < length; i++){
        xData[i] = i * i;
	}

	/* import `Hello` module from file Hello.jl */
	
     jl_eval_string("Base.include(Main, \"../test.jl\")");
     jl_eval_string("using Main.hamid");
     jl_module_t* test = (jl_module_t *)jl_eval_string("Main.hamid");
	
     /* get `the function */
    jl_function_t *llaToEcef = jl_get_function(test, "llaToEcef");
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	for(int i=0;i<200;i++){
	
	 // /* call the function */
	jl_value_t *a = jl_box_float64(3.0);
	jl_value_t *b = jl_box_float64(3.0);
	jl_value_t *c = jl_box_float64(3.0);
	jl_array_t *y = (jl_array_t*)jl_call3(llaToEcef,a,b,c);
	double *yData = (double*)jl_array_data(y);
	// for(size_t i=0; i<jl_array_len(y); i++){
		// printf("%.1f \n", yData[i]);
	 // }
	 // printf("done once \n");
	
	
	
	 // /* print new values of x */
    // for (int i = 0; i < length; i++)
        // printf("%.1f ", xData[i]);

    // printf("\n");
    // JL_GC_POP();

    // getchar();

    /* exit */
	}
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
	printf("took %lu us\n", delta_us);
    jl_atexit_hook(0);
	
	return 0;
	}
	
	
	

