// prog1.cl

__kernel void mydot(__global float *c,__global float *a,__global float *b)
{
unsigned int n;

n = get_global_id(0);

printf("Hello from thread %d\n",n);
c[n] = a[n] * b[n];
}
