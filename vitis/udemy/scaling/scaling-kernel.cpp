extern "C" {
void scaling_kernel(float *x, float *y, float alpha, float beta, int n) {

	for (int i = 0; i < n; i++) {
		y[i] = alpha*x[i]+beta;
	}

}
}
